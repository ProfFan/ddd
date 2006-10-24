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
// version 2 of the License, or (at your option) any later version.
// 
// DDD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with DDD -- see the file COPYING.
// If not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// 
// DDD is the data display debugger.
// For details, see the DDD World-Wide-Web page, 
// `http://www.gnu.org/software/ddd/',
// or send a mail to the DDD developers <ddd@gnu.org>.

#ifndef _DDD_buttons_h
#define _DDD_buttons_h

#include "strclass.h"

#ifdef IF_MOTIF

#include <X11/Intrinsic.h>

#endif // IF_MOTIF

#include "gtk_wrapper.h"

// Create a button row named NAME with buttons as specified in LIST
Widget make_buttons(Widget parent, const char *name, const _XtString list);

// Assign BUTTONS the buttons specified in LIST.  If MANAGE is set,
// (un)manage BUTTONS depending on the number of buttons.
void set_buttons(BOX_P buttons, const _XtString list, bool manage = true);

// Make BUTTON insensitive if it is not supported
void verify_button(Widget button);

// Refresh button sensitivity
void refresh_buttons();

// Maximum length of value in value tip and in status line
extern int max_value_tip_length;
extern int max_value_doc_length;

// Clear value cache after some change in the program state
extern void clear_value_cache();

// Invoke button and shortcut editors
void dddEditButtonsCB  (CB_ALIST_1(Widget));
void dddEditShortcutsCB(CB_ALIST_1(Widget));

// Refresh button editor after external change
void refresh_button_editor();

// Get a value from GDB, using PRINT_COMMAND (default if none)
string gdbValue(const string& expr, string print_command = "");

// Return changed EXPR that can be used as assignment value
string assignment_value(const string& expr);

// Create a flat PushButton named NAME
BUTTON_P create_flat_button(CONTAINER_P parent, const string& name);

// Remove command from help cache.
void clear_help_cache(const string& command);

#endif // _DDD_buttons_h
// DON'T ADD ANYTHING BEHIND THIS #endif
