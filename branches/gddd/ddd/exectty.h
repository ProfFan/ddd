// $Id$ -*- C++ -*-
// Execution TTY

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

#ifndef _DDD_exectty_h
#define _DDD_exectty_h

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "strclass.h"
#include <stdlib.h>

#if defined(IF_XM)

#include <X11/Intrinsic.h>

#endif

#if !defined(IF_XM)
#include <GUI/Widget.h>
#endif

#include "gtk_wrapper.h"

// Execution TTY

// Raise execution TTY
extern void startup_exec_tty();

#if defined(IF_XM)
// Raise execution TTY on COMMAND
extern void startup_exec_tty(string& command, Widget origin = 0);
#else
// Raise execution TTY on COMMAND
extern void startup_exec_tty(string& command, GUI::Widget *origin = 0);
#endif

// Kill execution TTY
extern void kill_exec_tty(bool killed = false);

// Reset execution TTY (also in GDB)
extern void reset_exec_tty();

// TTY pid (0: not initialized, -1: failed)
extern pid_t exec_tty_pid();

#if defined(IF_XM)
// TTY window
extern Window exec_tty_window();
#else
// TTY window
extern GUI::RefPtr<GUI::XWindow> exec_tty_window();
#endif

// Set TTY title
extern void set_tty_from_gdb(const string& text);

#if defined(IF_XM)
// Create TTY if required
extern void handle_running_commands(string& command, Widget origin);
#else
// Create TTY if required
extern void handle_running_commands(string& command, GUI::Widget *origin);
#endif

// Name of GDB tty
extern string gdb_tty;

// Verify if TTY window is still running
extern void exec_tty_running();

#endif // _DDD_exectty_h
// DON'T ADD ANYTHING BEHIND THIS #endif
