// $Id$ -*- C++ -*-
// Show tip of the day

// Copyright (C) 1998 Technische Universitaet Braunschweig, Germany.
// Copyright (C) 2001 Free Software Foundation, Inc.
// Copyright (C) 2001 Universitaet des Saarlandes, Germany.
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

char tips_rcsid[] = 
    "$Id$";

#include "tips.h"

#include "AppData.h"
#include "Command.h"
#include "x11/DestroyCB.h"
#include "HelpCB.h"
#include "motif/MakeMenu.h"
#include "base/cook.h"
#include "ddd.h"
#include "post.h"
#include "session.h"
#include "string-fun.h"
#include "x11/verify.h"
#include "wm.h"

#include <iostream>
#include <fstream>

#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/PushB.h>
#include <Xm/ToggleB.h>

Widget set_startup_tips_w;

static MString get_tip_of_the_day(Widget w, int n)
{
    struct tip_of_the_day_resource_values {
	XmString tip;
    };

    const string tip_name = "tip" + itostring(n);

    XtResource r;
    r.resource_name   = XTRESSTR(tip_name.chars());
    r.resource_class  = XTRESSTR("Tip");
    r.resource_type   = XmRXmString;
    r.resource_size   = sizeof(XmString);
    r.resource_offset = XtOffsetOf(tip_of_the_day_resource_values, tip);
    r.default_type    = XtRImmediate;
    r.default_addr    = XtPointer(0);

    tip_of_the_day_resource_values values;
    XtGetApplicationResources(w, &values, &r, 1, ArgList(0), 0);

    return MString(values.tip, true);
}

static string app_value(const string& resource, const string& value)
{
    String app_name;
    String app_class;
    XtGetApplicationNameAndClass(XtDisplay(find_shell()), 
				 &app_name, &app_class);

    if (resource.contains(string(app_name) + ".", 0))
	return string(app_class) + resource.from(".") + ": " + value;
    else
	return string(app_class) + "*" + resource + ": " + value;
}

static void SaveTipCountCB(Widget, XtPointer = 0, XtPointer = 0)
{
    create_session_dir(DEFAULT_SESSION);
    const string file = session_tips_file();

    std::ofstream os(file.chars());
    os << 
	"! " DDD_NAME " tips file\n"
	"\n"
       << app_value(XtNstartupTipCount,
		    itostring(++app_data.startup_tip_count)) << "\n";

    os.close();
    if (os.bad())
    {
	post_error("Cannot save tip count in " + quote(file),
		   "options_save_error");
    }
}

inline bool is_tip(const MString& m)
{
    return !m.isNull() && !m.isEmpty();
}

static bool refresh_tip_dialog(Widget w)
{
    MString tip = get_tip_of_the_day(w, app_data.startup_tip_count);
    if (!is_tip(tip))
    {
	// Restart from first tip
	app_data.startup_tip_count = 0;
	tip = get_tip_of_the_day(w, app_data.startup_tip_count);
    }
    if (!is_tip(tip))
	return false;

    XtVaSetValues(w, XmNmessageString, tip.xmstring(), XtPointer(0));

    MString next_tip = get_tip_of_the_day(w, app_data.startup_tip_count + 1);
    MString prev_tip = get_tip_of_the_day(w, app_data.startup_tip_count - 1);

    set_sensitive(XmMessageBoxGetChild(w, XmDIALOG_CANCEL_BUTTON),
		  is_tip(prev_tip));
    set_sensitive(XmMessageBoxGetChild(w, XmDIALOG_HELP_BUTTON),
		  is_tip(next_tip));

    string title = DDD_NAME " Tip of the Day #" + 
	itostring(app_data.startup_tip_count);
    XtVaSetValues(XtParent(w), XmNtitle, title.chars(), XtPointer(0));

    return true;
}

static void PrevTipCB(Widget w, XtPointer, XtPointer)
{
    app_data.startup_tip_count--;
    refresh_tip_dialog(w);
}

static void NextTipCB(Widget w, XtPointer, XtPointer)
{
    app_data.startup_tip_count++;
    refresh_tip_dialog(w);
}

void SetStartupTipsCB(Widget, XtPointer, XtPointer call_data)
{
    XmToggleButtonCallbackStruct *info = 
	(XmToggleButtonCallbackStruct *)call_data;

    app_data.startup_tips = info->set;

    update_options();
}

void TipOfTheDayCB(Widget w, XtPointer, XtPointer)
{
    static Widget tip_dialog = 0;

    if (tip_dialog == 0)
    {
	Arg args[10];
	Cardinal arg = 0;
	XtSetArg(args[arg], XmNautoUnmanage, False); arg++;
	tip_dialog = 
	    verify(XmCreateInformationDialog(find_shell(w), 
					     XMST("tip_dialog"), 
					     args, arg));

#if XmVersion >= 1002
	arg = 0;
	XtSetArg(args[arg], XmNset, app_data.startup_tips); arg++;
	set_startup_tips_w = 
	    verify(XmCreateToggleButton(tip_dialog, 
					XMST("set_startup_tips"),
					args, arg));
	XtAddCallback(set_startup_tips_w, XmNvalueChangedCallback, 
		      SetStartupTipsCB, 0);

	XtManageChild(set_startup_tips_w);
#endif

	XtAddCallback(tip_dialog, XmNokCallback, UnmanageThisCB, 
		      XtPointer(tip_dialog));
	XtAddCallback(tip_dialog, XmNcancelCallback, PrevTipCB, 0);
	XtAddCallback(tip_dialog, XmNhelpCallback,   NextTipCB, 0);
	XtAddCallback(tip_dialog, XmNunmapCallback,  SaveTipCountCB, 0);
    }

    bool ok = refresh_tip_dialog(tip_dialog);
    if (!ok)
	return;

    manage_and_raise(tip_dialog);
}
