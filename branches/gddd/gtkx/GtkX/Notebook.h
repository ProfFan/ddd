// -*- C++ -*-

// High-level GUI wrapper for Gtkmm.

// Copyright (C) 2007 Peter Wainwright <prw@ceiriog.eclipse.co.uk>
// 
// This file is part of GtkX.
// 
// GtkX is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// 
// GtkX is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with GtkX -- see the file COPYING.
// If not, see <http://www.gnu.org/licenses/>.

// High level object-oriented wrapper must support Gtk and Motif.
// Unfortunately Motif widgets require parent and name arguments to
// the constructor, unlike the Gtk ones.  Motif (Xt) widgets cannot be
// reparented.  Therefore we need a constructor with extra arguments.
// A brief look at QT indicates that this will be required there as
// well.

#ifndef GTKX_NOTEBOOK_H
#define GTKX_NOTEBOOK_H

#include <gtkmm/notebook.h>

#include <GtkX/Container.h>

namespace GtkX {

    class Notebook: public Container {
	Gtk::Notebook *nb_;
    public:
	Notebook(GtkX::Container &parent, PackOptions po=PACK_SHRINK,
		 const String &name="");
	~Notebook(void);
	Gtk::Widget *internal(void);
	const Gtk::Widget *internal(void) const;
	// Note: we must ensure all children are GtkX widgets.
	GtkX::Widget *get_current_child(void);
	int append_page(GtkX::Widget &child, const String &tab_label, bool use_mnemonic=false);
	GtkX::Container *append_page(const String &tab_label="", bool use_mnemonic=false);
	int get_n_pages();
	void set_current_page(int page_num);
    };

}

#endif // GTKX_NOTEBOOK_H
