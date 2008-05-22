// -*- C++ -*-

// High-level GUI wrapper for Gtkmm.

// Copyright (C) 2007 Peter Wainwright <prw@ceiriog.eclipse.co.uk>
// 
// This file is part of GtkX.
// 
// GtkX is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// GtkX is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with GtkX -- see the file COPYING.
// If not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#ifndef GTKX_FILESELECTIONDIALOG_H
#define GTKX_FILESELECTIONDIALOG_H

#include <vector>

#include <gtkmm/window.h>
#include <gtkmm/dialog.h>

#include <GtkX/Dialog.h>
#include <GtkX/FileSelection.h>

namespace GtkX {

    class FileSelectionDialog: public Dialog {
	FileSelection *fs_;
    public:
	void init(Gtk::Window &parent, const String &name,
		  FileAction action);
	FileSelectionDialog(GtkX::Shell &parent, const String &name,
			    FileAction action);
	Gtk::Widget *internal(void);
	const Gtk::Widget *internal(void) const;
	std::string get_selected(void);
	~FileSelectionDialog(void);
#include <GtkX/redirect.h>
    private:
	FileSelectionDialog(Gtk::Window &parent, const String &name,
			    FileAction action);
    };

}

#endif // GTKX_FILESELECTIONDIALOG_H