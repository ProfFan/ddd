// $Id$
// RegionGraphNode class

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
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

char RegionGraphNode_rcsid[] = 
    "$Id$";

#include <iostream>
#include <string.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

#include "RegionGN.h"
#include "box/printBox.h"

DEFINE_TYPE_INFO_1(RegionGraphNode, PosGraphNode)

// Center around position
void RegionGraphNode::center()
{
    _region.origin() = pos() - (_region.space() / 2);
}

// Compute position for ORIGIN
BoxPoint RegionGraphNode::originToPos(const BoxPoint& origin,
				      const GraphGC& gc) const
{
    return origin + region(gc).space() / 2;
}


// Draw a RegionGraphNode
void RegionGraphNode::draw(Widget w, 
			   const BoxRegion& exposed, 
			   const GraphGC& gc) const
{
    const BoxRegion& r = region(gc);

    // if not exposed or invisible, return
    if (!(r <= exposed) || r.space(X) == 0 || r.space(Y) == 0)
	return;

    Display *display = XtDisplay(w);
    Window window = XtWindow(w);

    // clear the area
    XFillRectangle(display, window, gc.clearGC,
		   r.origin(X), r.origin(Y),
		   r.space(X), r.space(Y));

    // draw contents
    forceDraw(w, exposed, gc);

    // if selected, invert area
    if (selected())
    {
	const BoxRegion& h = highlightRegion(gc);

	XFillRectangle(display, window, gc.invertGC,
		       h.origin(X), h.origin(Y),
		       h.space(X), h.space(Y));
    }
}



// cleanRegion
// clean a region with white ink
//
static void cleanRegion (std::ostream& os, const GraphGC& gc, BoxRegion region)
{
      BoxPoint origin = region.origin();
      BoxPoint width = region.space();

      if (gc.printGC->isPostScript())
      {
	  os << origin[X] << " " << origin[Y] << " ";
	  os << origin[X] + width[X] << " " << origin[Y];
	  os << " ";
	  os << origin[X] + width[X] << " ";
	  os << origin[Y] + width[Y] << " ";
	  os << origin[X] << " " << origin[Y] + width[Y];
	  os << " clean*\n";
      }
      else if (gc.printGC->isFig())
      {
	  os << CLEANHEAD;
	  os << origin[X] << " " << origin[Y] << " ";
	  os << origin[X] + width[X] << " " << origin[Y];
	  os << " ";
	  os << origin[X] + width[X] << " ";
	  os << origin[Y] + width[Y] << " ";
	  os << origin[X] << " " << origin[Y] + width[Y];
	  os << " ";
	  os << origin[X] << " "<< origin[Y] << " 9999 9999\n";
      }	  
}

// Print a RegionGraphNode
void RegionGraphNode::_print(std::ostream& os, const GraphGC& gc) const
{
    cleanRegion(os, gc, region(gc));
}

// Handlers
static bool Yes(RegionGraphNode *, const BoxSize&) { return true; }

bool (*RegionGraphNode::ResizeCB)(RegionGraphNode *, const BoxSize&) = Yes;
