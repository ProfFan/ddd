// $Id$ -*- C++ -*-
// DDD buttons

// Copyright (C) 1996 Technische Universitaet Braunschweig, Germany.
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

#ifndef _DDD_buttons_h
#define _DDD_buttons_h

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "strclass.h"

#if defined(IF_XM)
#include <X11/Intrinsic.h>
#else
#include <GUI/Widget.h>
#endif

#if !defined(IF_XM)
#include <GUI/Box.h>
#include <GUI/Container.h>
#include <GUI/Button.h>
#endif

#include "gtk_wrapper.h"

#if defined(IF_XM)
// Create a button row named NAME with buttons as specified in LIST
Widget make_buttons(Widget parent, const char *name, const _XtString list);

// Assign BUTTONS the buttons specified in LIST.  If MANAGE is set,
// (un)manage BUTTONS depending on the number of buttons.
void set_buttons(Widget buttons, const _XtString list, bool manage = true);
#else
// Create a button row named NAME with buttons as specified in LIST
GUI::Container *make_buttons(GUI::Container *parent, const char *name, const char *list);

// Assign BUTTONS the buttons specified in LIST.  If MANAGE is set,
// (un)manage BUTTONS depending on the number of buttons.
void set_buttons(GUI::Box *buttons, const char *list, bool manage = true);
#endif

#if defined(IF_XM)
// Make BUTTON insensitive if it is not supported
void verify_button(Widget button);
#else
// Make BUTTON insensitive if it is not supported
void verify_button(GUI::Widget *button);
#endif

// Refresh button sensitivity
void refresh_buttons();

// Maximum length of value in value tip and in status line
extern int max_value_tip_length;
extern int max_value_doc_length;

// Clear value cache after some change in the program state
extern void clear_value_cache();

#if defined(IF_XM)
// Invoke button and shortcut editors
void dddEditButtonsCB  (Widget, XtPointer, XtPointer);
void dddEditShortcutsCB(Widget, XtPointer, XtPointer);
#else
// Invoke button and shortcut editors
void dddEditButtonsCB  (GUI::Widget *parent);
void dddEditShortcutsCB(GUI::Widget *parent);
#endif

// Refresh button editor after external change
void refresh_button_editor();

// Get a value from GDB, using PRINT_COMMAND (default if none)
string gdbValue(const string& expr, string print_command = "");

// Return changed EXPR that can be used as assignment value
string assignment_value(const string& expr);

#if defined(IF_XM)
// Create a flat PushButton named NAME
Widget create_flat_button(Widget parent, const string& name);
#else
// Create a flat PushButton named NAME
GUI::Button *create_flat_button(GUI::Container *parent, const string& name,
				const string& label);
#endif

// Remove command from help cache.
void clear_help_cache(const string& command);

#endif // _DDD_buttons_h
// DON'T ADD ANYTHING BEHIND THIS #endif
