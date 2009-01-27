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

#ifndef GTKX_DIALOG_H
#define GTKX_DIALOG_H

#include <gtkmm/dialog.h>
#include <gtkmm/window.h>

#include <GtkX/Container.h>
#include <GtkX/Box.h>
#include <GtkX/Button.h>
#include <GtkX/Label.h>

namespace GtkX {

    class Dialog: public Shell {
	Gtk::Dialog *dlg_;
	GtkX::VBox *vbox_;
	// Note that we do NOT use the Gtk::Dialog's button area.
	// This is because we want to create the buttons ourself as
	// GtkX widgets.
	GtkX::HBox *buttons_;
    public:
	Dialog(GtkX::Widget &parent, const String &name="");
	void init(const String &name);
	Dialog(const String &name="");
	Gtk::Widget *internal(void);
	const Gtk::Widget *internal(void) const;
	Gtk::Container *gtk_container(void);
	~Dialog(void);
	Button *add_button(const String &name="", const String &label="");
	// FIXME: Disambiguate inheritance from GtkX::Widget and Gtk class.
	// #include <GtkX/redirect.h>
	void set_title(const String &);
	int run(void);
	void set_default_size(int width, int height); // FIXME inherited from Window
    };

    enum MessageType {
	MESSAGE_INFO,
	MESSAGE_WARNING,
	MESSAGE_ERROR
    };

    class MessageDialog: public Dialog {
	GtkX::Label *message_;
    public:
	MessageDialog(GtkX::Widget &parent, const String &name="",
		      const String &label="", MessageType type=MESSAGE_INFO);
	MessageDialog(const String &name="", const String &label="",
		      MessageType type=MESSAGE_INFO);
	~MessageDialog(void);
    };

}

#endif // GTKX_DIALOG_H