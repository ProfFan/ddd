// $Id$ -*- C++ -*-
// Arc edges

// Copyright (C) 1997 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@gnu.org>.
// 
// This file is part of DDD.
// 
// DDD is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// 
// DDD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with DDD -- see the file COPYING.
// If not, see <http://www.gnu.org/licenses/>.
// 
// DDD is the data display debugger.
// For details, see the DDD World-Wide-Web page, 
// `http://www.gnu.org/software/ddd/',
// or send a mail to the DDD developers <ddd@gnu.org>.

char ArcGraphEdge_rcsid[] = 
    "$Id$";

#include "ArcGraphE.h"
#include "HintGraphN.h"
#include "base/misc.h"
#include "box/printBox.h"

#include <math.h>
#include <stdlib.h>
#include "base/pi.h"
#include "base/hypot.h"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

DEFINE_TYPE_INFO_1(ArcGraphEdge, LineGraphEdge);

inline double hypot(const BoxPoint& p)
{
    return hypot(p[X], p[Y]);
}

// Compute the center of the arc enclosing P1, P2, and P3.
// Return false iff P1, P2, and P3 form a line (i.e. there is no arc)
bool ArcGraphEdge::center(const BoxPoint& p1, const BoxPoint& p2, 
			  const BoxPoint& p3, double& x, double& y)
{
    if (p1[X] == p3[X] && p1[Y] == p3[Y])
	return false;

    BoxPoint d12 = p1 - p2;
    BoxPoint d13 = p1 - p3;

    double s12 = asin(d12[Y] / hypot(d12));
    double s13 = asin(d13[Y] / hypot(d13));
    const double epsilon = 0.01;
    if (fabs(s12 - s13) < epsilon)
	return false;

    double l1 = p1[X] * p1[X] + p1[Y] * p1[Y];
    double l2 = p2[X] * p2[X] + p2[Y] * p2[Y];
    double l3 = p3[X] * p3[X] + p3[Y] * p3[Y];

    y = (d12[X] * (l3 - l1) - d13[X] * (l2 - l1))
	/ (2.0 * (d13[X] * d12[Y] - d12[X] * d13[Y]));

    if (p1[X] != p3[X])
	x = (l3 + 2.0 * y * d13[Y] - l1) / (2.0 * -d13[X]);
    else
	x = (l2 + 2.0 * y * d12[Y] - l1) / (2.0 * -d12[X]);

    return true;
}

void ArcGraphEdge::drawLine(Widget w, 
			    const BoxRegion& exposed, 
			    const GraphGC& gc) const
{
    makeLine(w, exposed, std::cout, gc);
}

void ArcGraphEdge::_print(std::ostream& os,
			  const GraphGC& gc) const
{
    makeLine(0, BoxRegion(), os, gc);
}

void ArcGraphEdge::makeLine(Widget w,
			    const BoxRegion& exposed,
			    std::ostream& os,
			    const GraphGC& gc) const
{
    HintGraphNode   *arc_hint = 0;
    RegionGraphNode *arc_from = 0;
    RegionGraphNode *arc_to   = 0;

    bool make_arc = true;
    if (from()->isHint() && to()->isHint())
    {
	// Edge between two hints
	make_arc = false;
    }
    else if (from()->isHint() && from()->firstTo() != 0)
    {
	arc_hint = ptr_cast(HintGraphNode, from());
	arc_from = ptr_cast(RegionGraphNode, arc_hint->firstTo()->from());
	arc_to   = ptr_cast(RegionGraphNode, to());

	if (arc_hint == 0 || arc_from == 0 || arc_to == 0 
	    || arc_hint->nextTo(arc_hint->firstTo()) != 0)
	{
	    // Bad nodes or hint with multiple edges
	    make_arc = false;
	}
    }
    else if (to()->isHint() && to()->firstFrom() != 0)
    {
	arc_hint = ptr_cast(HintGraphNode, to());
	arc_to   = ptr_cast(RegionGraphNode, arc_hint->firstFrom()->to());
	arc_from = ptr_cast(RegionGraphNode, from());

	if (arc_hint == 0 || arc_from == 0 || arc_to == 0
	    || arc_hint->nextFrom(arc_hint->firstFrom()) != 0)
	{
	    // Bad nodes or hint with multiple edges
	    make_arc = false;
	}
    }
    else
    {
	// Edge between two ordinary nodes
	make_arc = false;
    }

    if (!make_arc)
    {
 	if (w != 0)
	    LineGraphEdge::drawLine(w, exposed, gc);
	else
	    LineGraphEdge::_print(os, gc);
	return;
    }

    BoxPoint pos_from     = arc_from->pos();
    BoxRegion region_from = arc_from->region(gc);
    if (arc_from->selected())
    {
	pos_from             += gc.offsetIfSelected;
	region_from.origin() += gc.offsetIfSelected;
    }

    BoxPoint pos_to     = arc_to->pos();
    BoxRegion region_to = arc_to->region(gc);
    if (arc_to->selected())
    {
	pos_to             += gc.offsetIfSelected;
	region_to.origin() += gc.offsetIfSelected;
    }

    BoxPoint pos_hint     = arc_hint->pos();
    BoxRegion region_hint = arc_hint->region(gc);
    if (arc_hint->selected())
    {
	pos_hint             += gc.offsetIfSelected;
	region_hint.origin() += gc.offsetIfSelected;
    }

    if (pos_hint <= region_from || pos_hint <= region_to)
    {
	// Hint within region
 	if (w != 0)
	    LineGraphEdge::drawLine(w, exposed, gc);
	else
	    LineGraphEdge::_print(os, gc);
	return;
    }

    BoxPoint new_pos_from, new_pos_to, dummy;
    findLine(pos_from, pos_hint, region_from, region_hint,
	     new_pos_from, dummy, gc);
    findLine(pos_hint, pos_to, region_hint, region_to,
	     dummy, new_pos_to, gc);
    pos_from = new_pos_from;
    pos_to   = new_pos_to;

    // Draw circle segment POS_FROM -> POS_HINT or POS_HINT -> POS_TO

    // Determine the arc center
    double cx, cy;
    bool ok = center(pos_from, pos_hint, pos_to, cx, cy);
    if (!ok)
    {
	// Nodes form a line
 	if (w != 0)
	    LineGraphEdge::drawLine(w, exposed, gc);
	else
	    LineGraphEdge::_print(os, gc);
	return;
    }

    // Determine radius (easy when you have the center)
    double radius = hypot(cx - pos_to[X], cy - pos_to[Y]);

    // Determine start and path of arc
    double alpha_from = -atan2(pos_from[Y] - cy, pos_from[X] - cx);
    double alpha_hint = -atan2(pos_hint[Y] - cy, pos_hint[X] - cx);
    double alpha_to   = -atan2(pos_to[Y]   - cy, pos_to[X]   - cx);

    const int base = 360 * 64;

    int angle_from = (int(alpha_from * base / (PI * 2.0)) + base) % base;
    int angle_to   = (int(alpha_to   * base / (PI * 2.0)) + base) % base;
    int angle_hint = (int(alpha_hint * base / (PI * 2.0)) + base) % base;

    int path_from_hint = (base + angle_hint - angle_from) % base;
    int path_hint_to   = (base + angle_to - angle_hint) % base;

    if (abs(path_from_hint) > base / 2)
	path_from_hint = (path_from_hint - base) % base;
    if (abs(path_hint_to) > base / 2)
	path_hint_to = (path_hint_to - base) % base;

    if (sgn(path_from_hint) * sgn(path_hint_to) == -1)
    {
	// Hint is not between FROM and TO
 	if (w != 0)
	    LineGraphEdge::drawLine(w, exposed, gc);
	else
	    LineGraphEdge::_print(os, gc);
	return;
    }

    int angle, path;
    if (to()->isHint())
    {
	angle = angle_from;
	path  = path_from_hint;
    }
    else
    {
	angle = angle_hint;
	path  = path_hint_to;
    }

    if (w != 0)
    {
	XDrawArc(XtDisplay(w), XtWindow(w), gc.edgeGC,
		 int(cx - radius), int(cy - radius),
		 unsigned(radius) * 2, unsigned(radius) * 2, angle, path);
    }
    else if (gc.printGC->isPostScript())
    {
	BoxCoordinate line_width = 1;

	int arc_start  = angle / 64;
	int arc_extend = path / 64;

	int start, end;
	if (arc_extend > 0)
	{
	    start = (720 - arc_start - arc_extend) % 360;
	    end   = (720 - arc_start) % 360;
	}
	else
	{
	    start = (720 - arc_start) % 360;
	    end   = (720 - arc_start - arc_extend) % 360;
	}

	os << start << " " << end << " " 
	   << int(radius) << " " << int(radius) << " "
	   << int(cx) << " " << int(cy) << " " << line_width << " arc*\n";
    }
    else if (gc.printGC->isFig())
    {
	// We draw the entire arc in one stroke.
	if (from()->isHint())
	{
	    BoxCoordinate line_width = 1;

	    os << ARCARROWHEAD1 << line_width << ARCARROWHEAD2;
	    if (path > 0)
		os << ARCCOUNTERCLOCKWISE;
	    else
		os << ARCCLOCKWISE;
	    os << ARCARROWHEAD3
	       << cx << " " << cy << " "
	       << pos_from[X] << " " << pos_from[Y] << " "
	       << pos_hint[X] << " " << pos_hint[Y] << " "
	       << pos_to[X]   << " " << pos_to[Y]   << " "
	       << ARCARROWHEAD4;
	}
    }

    if (from()->isHint())
    {
	// Draw arrow head at POS_TO
	double alpha = atan2(pos_to[Y] - cy, pos_to[X] - cx);

	if (w != 0)
	{
	    if (path > 0)
		alpha += PI / 2.0;
	    else
		alpha -= PI / 2.0;

	    drawArrowHead(w, exposed, gc, pos_to, alpha);
	}
	else if (gc.printGC->isPostScript())
	{
	    if (path > 0)
		alpha -= PI / 2.0;
	    else
		alpha += PI / 2.0;

	    os << gc.arrowAngle << " " << gc.arrowLength << " " 
	       << (360 + int(alpha * 360.0 / (PI * 2.0))) % 360 << " "
	       << pos_to[X] << " " << pos_to[Y] << " arrowhead*\n";
	}
    }

    if (to()->isHint() && annotation() != 0)
    {
	if (w != 0)
	{
	    annotation()->draw(w, to()->pos(), exposed, gc);
	}
	else
	{
	    annotation()->_print(os, to()->pos(), gc);
	}
    }
}
