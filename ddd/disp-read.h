// $Id$
// Helper functions to process GDB display output

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
// Written by Dorothea Luetkehaus (luetke@ips.cs.tu-bs.de).
// 
// This file is part of the DDD Library.
// 
// The DDD Library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// The DDD Library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Library General Public License for more details.
// 
// You should have received a copy of the GNU Library General Public
// License along with the DDD Library -- see the file COPYING.LIB.
// If not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// 
// DDD is the data display debugger.
// For details, see the DDD World-Wide-Web page, 
// `http://www.cs.tu-bs.de/softech/ddd/',
// or send a mail to the DDD developers at `ddd@ips.cs.tu-bs.de'.

//-----------------------------------------------------------------------------
// Verschiedene Routinen, die das Erkennen bzw. Lesen
// (und Erzeugen) von display-Ausgaben erleichtern.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#ifndef _DDD_disp_read_h
#define _DDD_disp_read_h

#ifdef __GNUG__
#pragma interface
#endif

// Misc includes
#include "strclass.h"
#include "bool.h"

// DDD includes
#include "GDBAgent.h"

//----------------------------------------------------------------------------
// Recognize most important commands
//----------------------------------------------------------------------------

// True if CMD creates a single display.
bool is_single_display_cmd(const string& cmd, GDBAgent *gdb);

// True if CMD has no side effects.
bool is_nop_cmd(const string& cmd);

// True if CMD creates a data display
bool is_display_cmd(const string& cmd);

// True if CMD changes a data display
bool is_data_cmd(const string& cmd);

// True if CMD deletes a data display
bool is_delete_display_cmd(const string& cmd);

// True if CMD disables a data display
bool is_disable_display_cmd(const string& cmd);

// True if CMD enables a data display
bool is_enable_display_cmd(const string& cmd);

// True if CMD executes debuggee and shows new displays
bool is_running_cmd(const string& cmd, GDBAgent *gdb);

// True if CMD starts debuggee
bool is_run_cmd(const string& cmd);

// True if CMD sets debuggee arguments.
bool is_set_args_cmd(const string& cmd);

// True if CMD changes the current program frame
bool is_frame_cmd(const string& cmd);
bool is_up_cmd(const string& cmd);   // ... towards caller
bool is_down_cmd(const string& cmd); // ... towards called

// True if CMD changes the current thread
bool is_thread_cmd(const string& cmd);

// True if CMD changes variable values.
bool is_set_cmd(const string& cmd);

// True if CMD changes debugger settings.
bool is_setting_cmd(const string& cmd);

// True if CMD changes the current file.
bool is_file_cmd(const string& cmd, GDBAgent *gdb);

// True if CMD changes breakpoints.
bool is_break_cmd(const string& cmd);

// True if CMD changes the current position.
bool is_lookup_cmd(const string& cmd);

// True if CMD changes the current directory
bool is_cd_cmd(const string& cmd);

// True if CMD is a make command
bool is_make_cmd(const string& cmd);

// True if CMD is an internal graph command.
bool is_graph_cmd(const string& cmd);

// True if CMD is an internal `graph refresh' command.
bool is_refresh_cmd(const string& cmd);

// Return the string after a `display' command.
string get_display_expression(const string& cmd);


//----------------------------------------------------------------------------
// Handle `display' output
//----------------------------------------------------------------------------

// True if GDB_ANSWER contains a display expression.
bool contains_display (const string& gdb_answer, GDBAgent *gdb);

// Return index of first display expr in GDB_ANSWER; -1, if none is found.
int display_index (const string& gdb_answer, GDBAgent *gdb);

// Return index of first possible beginning of display expr in GDB_ANSWER.
int possible_begin_of_display (string gdb_answer, GDBAgent *gdb);

// Return next display expr from DISPLAYS; remove it from DISPLAYS.
string read_next_display (string& displays, GDBAgent *gdb);

// Remove and return "NR: NAME = " from DISPLAY.
string get_disp_value_str (/*const*/ string& display, GDBAgent *gdb);


//----------------------------------------------------------------------------
// Recognize expressions in `info display'
//----------------------------------------------------------------------------

// Return first/next display info from GDB_ANSWER; "" if done.
string read_first_disp_info (string& gdb_answer, GDBAgent *gdb);
string read_next_disp_info (string& gdb_answer, GDBAgent *gdb);

// Remove and return "NR: " from DISPLAY.
string get_info_disp_str (string& display, GDBAgent *gdb);

// Check whether `disabled' entry in INFO_DISP_STR indicates an enabled display
bool disp_is_disabled (const string& info_disp_str, GDBAgent *gdb);



//----------------------------------------------------------------------------
// Handle `display' output
//----------------------------------------------------------------------------

// Remove and return display number from DISPLAY
string  read_disp_nr_str (string& display, GDBAgent *gdb);

// Remove and return display name from DISPLAY
string  read_disp_name   (string& display, GDBAgent *gdb);

// True if some display has been disabled
bool is_disabling (const string& value, GDBAgent *gdb);

// True if VALUE is an invalid value (i.e., an error message)
bool is_invalid(const string& value);

#endif // _DDD_disp_read_h
// DON'T ADD ANYTHING BEHIND THIS #endif
