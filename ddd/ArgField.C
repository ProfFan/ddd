// $Id$
// Argument field Implementation

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
// Written by Dorothea Luetkehaus <luetke@ips.cs.tu-bs.de>.
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

char ArgField_rcsid[] =
    "$Id$";

//-----------------------------------------------------------------------------
#include "ArgField.h"
#include <ctype.h>

#include <Xm/TextF.h>
#include <Xm/PushB.h>

#include "x11/verify.h"
#include "x11/charsets.h"
#include "AppData.h"
#include "buttons.h"
#include "string-fun.h"		// strip_space()
#include "base/tabs.h"		// tabify()
#include "motif/ComboBox.h"


// Constructor
ArgField::ArgField (Widget parent, const char* name)
    : arg_text_field(0), handlers(ArgField_NTypes), is_empty(true), 
      locked(false)
{
    Arg args[10];
    Cardinal arg = 0;

    if (!app_data.button_captions)
    {
	// Make argument field a little less high
	XtSetArg(args[arg], XmNmarginHeight, 2); arg++;
    }

    arg_text_field = CreateComboBox(parent, name, args, arg);

    XtAddCallback(arg_text_field, XmNvalueChangedCallback,
		  valueChangedCB, this);
    XtAddCallback(arg_text_field, XmNlosePrimaryCallback,
		  losePrimaryCB, this);
}

string ArgField::get_string () const
{
    String arg = XmTextFieldGetString (arg_text_field);
    string str(arg);
    XtFree (arg);
    strip_space(str);
    return str;
}

void ArgField::set_string(string s)
{
    if (locked)
	return;

    // Strip blanks
    strip_space(s);

    // XmTextField cannot display tabs
    untabify(s);

    // Don't use newlines
    s.gsub('\n', ' ');

    // Set it
    String old_s = XmTextFieldGetString(arg_text_field);
    if (s != old_s)
    {
	XmTextFieldSetString(arg_text_field, XMST(s.chars()));

	if (XtIsRealized(arg_text_field)) // LessTif 0.1 crashes otherwise
	{
	    XmTextPosition last_pos = 
		XmTextFieldGetLastPosition(arg_text_field);
	    XmTextFieldSetInsertionPosition(arg_text_field, last_pos);
	    XmTextFieldShowPosition(arg_text_field, 0);
	    XmTextFieldShowPosition(arg_text_field, last_pos);
	}
    }

    XtFree(old_s);
}

void ArgField::valueChangedCB(Widget,
			      XtPointer client_data,
			      XtPointer)
{
    ArgField *arg_field = (ArgField *)client_data;
    arg_field->handlers.call(Changed, arg_field);

    const string s = arg_field->get_string();

    if (s.empty())
    {
	if (!arg_field->is_empty)
	{
	    arg_field->is_empty = true;
	    arg_field->handlers.call(Empty, arg_field, (void *)true);
	}
    }
    else if (arg_field->is_empty)
    {
	arg_field->is_empty = false;
	arg_field->handlers.call(Empty, arg_field, (void *)false);
    }
}

void ArgField::lock(bool arg)
{
    locked = arg;
    XtSetSensitive(top(), !locked);
    XtSetSensitive(text(), !locked);
}

void ArgField::losePrimaryCB(Widget,
			     XtPointer client_data,
			     XtPointer)
{
    ArgField *arg_field = (ArgField *)client_data;
    arg_field->handlers.call(LosePrimary, arg_field, 0);
}

void ArgField::addHandler (unsigned    type,
			   HandlerProc proc,
			   void*       client_data)
{
    handlers.add(type, proc, client_data);
}

void ArgField::removeHandler (unsigned    type,
			      HandlerProc proc,
			      void        *client_data)
{
    handlers.remove(type, proc, client_data);
}

void ArgField::callHandlers ()
{
    handlers.call(Empty, this, (void*)is_empty);
}

Widget ArgField::top() const { return ComboBoxTop(text()); }


// Clear the text field given in Widget(CLIENT_DATA)
void ClearTextFieldCB(Widget, XtPointer client_data, XtPointer)
{
    Widget arg_field = Widget(client_data);
    XmTextFieldSetString(arg_field, XMST(""));
}

// Create a `():' label named "arg_label" for ARG_FIELD
Widget create_arg_label(Widget parent)
{
    return create_flat_button(parent, "arg_label");
}
