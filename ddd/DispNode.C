// $Id$
// Store information about a single display espression

// Copyright (C) 1995-1998 Technische Universitaet Braunschweig, Germany.
// Written by Dorothea Luetkehaus <luetke@ips.cs.tu-bs.de>
// and Andreas Zeller <zeller@gnu.org>
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

char DispNode_rcsid[] =
    "$Id$";

//-----------------------------------------------------------------------------
// A DispNode keeps all information about a single data display
//-----------------------------------------------------------------------------

#include "DispNode.h"

#include "base/cook.h"
#include "AppData.h"
#include "box/CompositeB.h"
#include "DispValue.h"
#include "DispBox.h"
#include "AliasGE.h"

#ifndef KEEP_CLUSTERED_DISPLAYS
#define KEEP_CLUSTERED_DISPLAYS 0
#endif

DEFINE_TYPE_INFO_1(DispNode, BoxGraphNode)

// Data
HandlerList DispNode::handlers(DispNode_NTypes);

int DispNode::tics = 0;

// Constructor
DispNode::DispNode (int disp_nr,
		    const string& name,
		    const string& scope,
		    const string& val,
		    bool pl)
    : BoxGraphNode(),
      mydisp_nr(disp_nr),
      myname(name),
      myaddr(""),
      myscope(scope),
      mydepends_on(""),
      myactive(true),
      saved_node_hidden(false),
      mydeferred(false),
      myclustered(false),
      myplotted(pl),
      myconstant(false),
      disp_value(0),
      myselected_value(0),
      disp_box(0),
      mylast_change(++tics),
      mylast_refresh(++tics),
      alias_of(0)
{
    if (!val.empty())
    {
	string v = val;
	disp_value = DispValue::parse(v, myname);
	set_addr(disp_value->addr());
    }

    if (plotted() && value() != 0)
    {
	// No need to show all detail; it is plotted, anyway
	value()->collapse();
    }

    // Create new box from DISP_VALUE
    disp_box = new DispBox (mydisp_nr, myname, disp_value);

    // Set the box
    setBox(disp_box->box());
}

// Destructor
DispNode::~DispNode()
{
    if (disp_value != 0)
    {
	disp_value->unlink();
	disp_value = 0;
    }

    delete disp_box;
}

// User-defined displays (status displays)

// Return user command from S
string user_command(const string& s)
{
    if (is_user_command(s))
	return _unquote(s);
    else
	return "";
}

// Add event handler
void DispNode::addHandler (unsigned    type,
			   HandlerProc proc,
			   void*       client_data)
{
    DispNode::handlers.add(type, proc, client_data);
}

// Remove event handler
void DispNode::removeHandler (unsigned    type,
			      HandlerProc proc,
			      void        *client_data)
{
    DispNode::handlers.remove(type, proc, client_data);
}


// Update with VALUE;  return false if value is unchanged
bool DispNode::update(string& value)
{
    bool changed = false;
    bool inited  = false;

    if (disabled()) 
    { 
	// Display has been enabled (automatically)
	enable();
	changed = true;
    }

    if (disp_value == 0)
    { 
	// We have not read a value yet
	disp_value = DispValue::parse(value, myname);
	set_addr(disp_value->addr());
	changed = true;
    }
    else
    {
	// Update existing value
	disp_value = disp_value->update(value, changed, inited);
	if (!disp_value->addr().empty() && addr() != disp_value->addr())
	{
	    set_addr(disp_value->addr());
	    changed = true;
	}
    }

    if (inited)
    {
	// We were reinitialized: disable old selection
	select(0);
    }
	
    if (changed)
    {
	disp_box->set_value(disp_value);

	// Set new box
	setBox(disp_box->box());
    }

    if (changed || inited)
    {
	// mylast_change = ++tics;
	mylast_refresh = ++tics;
#if 0
	std::clog << "Display " << disp_nr() << " changed"
		  << " (" << mylast_change << ")\n";
#endif
    }

    return changed;
}


// Re-create box value from current disp_value
void DispNode::refresh()
{
    disp_box->set_value(disp_value);
    setBox(disp_box->box());
    select(selected_value());
    refresh_plot_state();

    mylast_refresh = ++tics;
}

// Re-create entire box from current disp_value
void DispNode::reset()
{
    bool have_title = disp_box->have_title();

    if (disp_value)
	disp_value->clear_box_cache();
    delete disp_box;

    // Create new box from DISP_VALUE
    disp_box = new DispBox (mydisp_nr, myname, disp_value);

    // Set the title
    set_title(have_title);

    // Set the box
    setBox(disp_box->box());

    // Reset selection
    select(0);

    mylast_refresh = ++tics;
}

// In BOX, find outermost TagBox for given DispValue DV
TagBox *DispNode::findTagBox(const Box *box, DispValue *dv)
{
    TagBox *tb = ptr_cast(TagBox, (Box *)box);
    if (tb && tb->__data() == (void *)dv)
	return tb;

    HatBox *hb = ptr_cast(HatBox, (Box *)box);
    if (hb)
	return findTagBox(hb->box(), dv);

    CompositeBox *cb = ptr_cast(CompositeBox, (Box *)box);
    if (cb)
    {
	for (int i = 0; i < cb->nchildren(); i++)
	{
	    Box *child = (*cb)[i];
	    TagBox *tb = findTagBox(child, dv);
	    if (tb)
		return tb;
	}
    }

    return 0;
}

// Highlights the box related to the display value DV
void DispNode::select(DispValue *dv)
{
    TagBox *tb = 0;
    if (dv != 0)
	tb = findTagBox(box(), dv);

    setHighlight(tb);
    myselected_value = dv;
}

// Copy selection state from SRC
void DispNode::copy_selection_state(const DispNode& src)
{
    if (value() != 0 && src.value() != 0 && src.selected_value() != 0)
    {
	const DispValue *descendant = 0;
	bool eq = value()->structurally_equal(src.value(), 
					      src.selected_value(),
					      descendant);
	if (eq)
	    select((DispValue *)descendant);
	return;
    }

    // Don't care - just select it all
    select(0);
}

// Set up plot state
void DispNode::refresh_plot_state() const
{
    if (value() == 0)
	return;

    if (disabled())
	value()->set_plot_state("Disabled");
    else if (!active())
	value()->set_plot_state("Not active");
    else
	value()->set_plot_state();
}

// Disable display
void DispNode::disable()
{
    if (value() == 0 || disabled())
	return;

    value()->enabled() = false;
    handlers.call(DispNode_Disabled, this, (void *)true);
    refresh();
}

// Enable display
void DispNode::enable()
{
    if (value() == 0 || enabled())
	return;

    value()->enabled() = true;
    handlers.call(DispNode_Disabled, this, (void *)false);
    refresh();
}

// Hide display
void DispNode::make_inactive()
{
    if (active())
    {
	if (!clustered())
	{
	    saved_node_hidden = hidden();
	    hidden() = true;
	}
	myactive = false;

	mylast_refresh = ++tics;

	refresh_plot_state();
    }

    // Unselect it
    selected() = false;
}

// Show display
void DispNode::make_active()
{
    if (!active())
    {
	myactive = true;
	if (!clustered())
	    hidden() = saved_node_hidden;

	mylast_refresh = ++tics;

	refresh_plot_state();
    }
}

// Cluster display into TARGET
void DispNode::cluster(int target)
{
    if (target != 0)
    {
	if (clustered() == 0)
	    saved_node_hidden = hidden();

#if KEEP_CLUSTERED_DISPLAYS
	// Don't hide clustered displays
#else
	hidden() = true;
#endif
    }
    else // target == 0
    {
	if (clustered() != 0)
	    hidden() = saved_node_hidden;
    }

    // Set new target
    myclustered = target;

    // Unselect it
    selected() = false;

    // Mark as changed
    mylast_refresh = ++tics;
}

// Update address with NEW_ADDR
void DispNode::set_addr(const string& new_addr)
{
    if (myaddr != new_addr)
    {
	myaddr = new_addr;
	// mylast_change = ++tics;
#if 0
	std::clog << "Display " << disp_nr() << " changed"
		  << " (" << mylast_change << ")\n";
#endif
    }
}

// Return `true' if this expression can be aliased.
bool DispNode::alias_ok() const
{
    // We avoid merging displays that are derived from other displays,
    // such as `/FMT EXPR' or `(TYPE) EXPR'.
    return !is_user_command()
	&& !name().contains('/', 0) 
	&& !name().contains('(', 0);
}

// Toggle titles.  Return true if changed.
bool DispNode::set_title(bool set)
{
    bool changed = false;
    if (set && !disp_box->have_title())
    {
	// Add title
	disp_box->set_title(value(), mydisp_nr, myname);
	changed = true;
    }
    else if (!set && disp_box->have_title())
    {
	// Remove title
	disp_box->set_title(value(), mydisp_nr, "");
	changed = true;
    }

    if (changed)
    {
	// Set value again
	disp_box->set_value(disp_value);

	// Show new box
	setBox(disp_box->box());
    }

    return changed;
}

// Duplication
DispNode::DispNode(const DispNode& node)
    : BoxGraphNode(node),
      mydisp_nr(node.disp_nr()),
      myname(node.name()),
      myaddr(node.addr()),
      myscope(node.scope()),
      mydepends_on(node.mydepends_on),
      myactive(node.active()),
      saved_node_hidden(node.saved_node_hidden),
      mydeferred(node.deferred()),
      myclustered(node.clustered()),
      myplotted(node.plotted()),
      myconstant(node.constant()),
      disp_value(node.value() ? node.value()->dup() : 0),
      myselected_value(0),
      disp_box(node.disp_box ? node.disp_box->dup() : 0),
      mylast_change(node.last_change()),
      mylast_refresh(node.last_refresh()),
      alias_of(node.alias_of)
{
    setBox(disp_box->box());
    copy_selection_state(node);
}

// Plotting

// Print plots to FILENAME
void DispNode::print_plots(const string& filename, const GraphGC& gc) const
{
    if (gc.printSelectedNodesOnly && selected_value() != 0)
	selected_value()->print_plots(filename, *gc.printGC);
    else if (value() != 0)
	value()->print_plots(filename, *gc.printGC);
}
