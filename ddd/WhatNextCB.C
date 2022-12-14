// $Id$ -*- C++ -*-
// DDD `What Now?' help

// Copyright (C) 1997-1998 Technische Universitaet Braunschweig, Germany.
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

char WhatNextCB_rcsid[] = 
    "$Id$";

#include "WhatNextCB.h"

#include "Command.h"
#include "x11/converters.h"
#include "comm-manag.h"
#include "ddd.h"
#include "editing.h"
#include "exit.h"
#include "file.h"
#include "question.h"
#include "regexps.h"
#include "status.h"
#include "x11/verify.h"
#include "version.h"
#include "wm.h"
#include "AppData.h"
#include "DataDisp.h"
#include "x11/Delay.h"
#include "x11/DestroyCB.h"
#include "HelpCB.h"
#include "SourceView.h"
#include "UndoBuffer.h"

#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/MessageB.h>

// Show a suggestion named NAME
static void hint_on(const _XtString name)
{
    // Create some `dummy' widget and create a help text for it
    Widget suggestion = 
	verify(XmCreateInformationDialog(find_shell(), XMST(name), 0, 0));

    ImmediateHelpCB(suggestion, XtPointer(0), XtPointer(0));

    DestroyWhenIdle(suggestion);
}

static bool no_source_and_no_code()
{
    return !source_view->have_source()
	&& (gdb->type() != GDB || !app_data.disassemble);
}

static bool no_gdb()
{
    return !gdb_initialized;
}

static bool gdb_has_crashed()
{
    return !no_gdb() && (gdb == 0 || gdb->pid() <= 0 || !gdb->running());
}

static bool code_but_no_source()
{
    return source_view->have_pc() && !source_view->have_exec_pos()
	&& (gdb->type() != GDB || !app_data.disassemble);
}

// Return 1 if the signal specified in PROGRAM_STATE is passed to the
// program; 0 if not, -1 if undecided.
static int passed_to_program(const string& program_state)
{
    string signal = program_state.from("SIG");
    signal = signal.through(rxalpha);

    if (!signal.empty())
    {
	string signal_description = program_state.after(signal);
	signal_description = signal_description.after(rxwhite);

	if (signal_description.empty())
	    signal_description = signal;
	
	defineConversionMacro("SIGNAL", signal.chars());
	defineConversionMacro("SIGNAL_DESCRIPTION", signal_description.chars());

	string ans = gdb_question("info handle " + signal);

	// `info handle SIGINT' output has the form
	// "Signal        Stop\tPrint\tPass to program\tDescription\n"
	// "SIGINT        Yes\tYes\tNo\t\tInterrupt\n"

	ans.downcase();
	string header = ans.before("pass ");
	int tabs_before_pass = header.freq('\t');
	string info = ans.after('\n');
	while (tabs_before_pass--)
	    info = info.after('\t');
	if (info.contains('y', 0))
	    return 1;
	if (info.contains('n', 0))
	    return 0;
    }
    return -1;
}

// Give a help dependent on current DDD state
void WhatNextCB(Widget, XtPointer, XtPointer)
{
    // Special DDD states
    if (ddd_has_crashed)
    {
	hint_on("fatal_dialog");
	return;
    }

    // Special GDB states
    if (no_gdb())
    {
	hint_on("no_debugger_dialog");
	return;
    }

    if (gdb_has_crashed())
    {
	hint_on("terminated_dialog");
	return;
    }

    if (gdb_asks_yn)
    {
	hint_on("yn_dialog");
	return;
    }

    if (gdb->recording())
    {
	hint_on("recording");
	return;
    }

    if (debuggee_running)
    {
	hint_on("running");
	return;
    }

    if (!can_do_gdb_command())
    {
	hint_on("busy");
	return;
    }

    if (undo_buffer.showing_earlier_state())
    {
	hint_on("showing_earlier_state");
	return;
    }

    // Typical start-up situations
    ProgramInfo info;
    if (info.file.empty())
    {
	hint_on("no_program");
	return;
    }

    if (no_source_and_no_code())
    {
	hint_on("no_source_and_no_code");
	return;
    }

    // Examine state
    if (source_view->have_selection())
    {
	hint_on("item_selected");
	return;
    }

    if (data_disp->have_selection())
    {
	hint_on("display_selected");
	return;
    }

    if (!current_line().empty())
    {
	hint_on("command_entered");
	return;
    }

    if (!info.running)
    {
	hint_on("program_not_running");
	return;
    }

    // Program has stopped and nothing is selected.
    defineConversionMacro("PROGRAM_STATE", info.state.chars());

    if (code_but_no_source())
    {
	hint_on("code_but_no_source");
	return;
    }

    if (gdb->type() == GDB && info.state.contains("signal"))
    {
	int p = passed_to_program(info.state);
	if (p > 0)
	{
	    hint_on("stopped_at_passed_signal");
	    return;
	}
	else if (p == 0)
	{
	    hint_on("stopped_at_ignored_signal");
	    return;
	}
    }

    hint_on("stopped");
}
