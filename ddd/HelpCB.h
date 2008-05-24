// $Id$  -*- C++ -*-
// Interactive Help Callbacks

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@gnu.org>.
// Cross-platform interface by Peter Wainwright <prw@ceiriog.eclipse.co.uk>
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

#ifndef _DDD_HelpCB_h
#define _DDD_HelpCB_h

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(IF_XM)
#include <X11/Intrinsic.h>
#include <Xm/Text.h>
#else
#include <GUI/Widget.h>
#include <GUI/ScrolledText.h>
#endif

#include "gtk_wrapper.h"

#include "MString.h"
#include "bool.h"

// Resources
// Text to be displayed in context-sensitive help (via HelpOnContextCB)
#define XtNhelpString "helpString"
#define XtCHelpString "HelpString"

// Text to be displayed in `Help On Version'
#define XtNhelpOnVersionString "helpOnVersionString"
#define XtCHelpOnVersionString "HelpOnVersionString"

// Text to be displayed in button tips (via InstallTips)
#define XtNtipString  "tipString"
#define XtCTipString  "TipString"

// Text to be displayed in the status line (via DisplayDocumentation)
#define XtNdocumentationString  "documentationString"
#define XtCDocumentationString  "DocumentationString"

// If true, give widget names in context-sensitive help
#define XtNhelpShowTitle "helpShowTitle"
#define XtCHelpShowTitle "HelpShowTitle"


#if defined(IF_XM)
// Select widget and call help on context.
// May be used in a menu entry "Help On Context".
extern void HelpOnContextCB(Widget widget, XtPointer client_data, 
			    XtPointer call_data);

// Call help on context on the widget that got the help key.
// May be used in a menu entry "Help On Item".
extern void HelpOnItemCB(Widget widget, XtPointer client_data, 
			 XtPointer call_data);

// Call help on current shell window.
// May be used in a menu entry "Help On Window".
extern void HelpOnWindowCB(Widget widget, XtPointer client_data, 
			   XtPointer call_data);

// Call help on the top-level window.
// May be used in a menu entry "Help On Version".
extern void HelpOnVersionCB(Widget widget, XtPointer client_data, 
			    XtPointer call_data);

// Call help on help.
// May be used in a menu entry "Help On Help".
extern void HelpOnHelpCB(Widget widget, XtPointer client_data, 
			 XtPointer call_data);

// Call help for associated widget.
// May be used as help callback for any primitive widget.
extern void ImmediateHelpCB(Widget, XtPointer, XtPointer);

// Call help for widget given in "Widget w = (Widget)client_data".
extern void HelpOnThisCB(Widget widget, XtPointer client_data, 
			 XtPointer call_data);

// Call help with "XmString s = (XmString)client_data" as text.
// May be used for unchanged text display.
extern void MStringHelpCB(Widget widget, XtPointer client_data, 
			  XtPointer call_data);

// Call help with "String s = (String)client_data" as text.
// May be used for unchanged text display.
extern void StringHelpCB(Widget widget, XtPointer client_data, 
			 XtPointer call_data);

// Call help with "String s = (String)client_data" as text.
// May be used for unchanged text display.
extern void TextHelpCB(Widget widget, XtPointer client_data, 
		       XtPointer call_data);
#else
// Select widget and call help on context.
// May be used in a menu entry "Help On Context".
extern void HelpOnContextCB(GUI::Widget *widget, GUI::Event *event);

// Call help on context on the widget that got the help key.
// May be used in a menu entry "Help On Item".
extern void HelpOnItemCB(GUI::Widget *widget, GUI::Event *event);

// Call help on current shell window.
// May be used in a menu entry "Help On Window".
extern void HelpOnWindowCB(GUI::Widget *widget, GUI::Event *event);

// Call help on the top-level window.
// May be used in a menu entry "Help On Version".
extern void HelpOnVersionCB(GUI::Widget *widget, GUI::Event *event);

// Call help on help.
// May be used in a menu entry "Help On Help".
extern void HelpOnHelpCB(GUI::Widget *widget);

// Call help for associated widget.
// May be used as help callback for any primitive widget.
extern void ImmediateHelpCB(GUI::Widget *);

// Call help for widget given in "Widget w = (Widget)client_data".
extern void HelpOnThisCB(GUI::Widget *widget, GUI::Event *event);

// Call help with text.
// May be used for unchanged text display.
extern void MStringHelpCB(GUI::Widget *widget, const GUI::String &text);

// Call help with GUI::String(s) as text.
// May be used for unchanged text display.
extern void StringHelpCB(GUI::Widget *widget, const char *s);

// Call help with "String s" as text.
// May be used for unchanged text display.
extern void TextHelpCB(GUI::Widget *widget, const char *s);
#endif

#if defined(IF_XM)
// Call help with a built-in formatted manual page "String s =
// (String)client_data".
extern void ManualStringHelpCB(Widget widget, XtPointer client_data, 
			       XtPointer call_data);
extern void ManualStringHelpCB(Widget widget, const MString& title,
			       const string& text);
#else
// Call help with a built-in formatted manual page "String s =
// (String)client_data".
extern void ManualStringHelpCB(GUI::Widget *widget, char *s);
extern void ManualStringHelpCB(GUI::Widget *widget, const MString& title,
			       const string& text);
#endif

#if defined(IF_XM)
// (Un)install button tips on W.
extern void InstallButtonTips(Widget w, bool install = true);

// (Un)install text tips on W.
extern void InstallTextTips(Widget w, bool install = true);
#else
// (Un)install button tips on W.
extern void InstallButtonTips(GUI::Widget *w, bool install = true);

// (Un)install text tips on W.
extern void InstallTextTips(GUI::Widget *w, bool install = true);
#endif

// Enable or disable all installed button tips.
extern void EnableButtonTips(bool enable = true);

// Enable or disable all installed text tips.
extern void EnableTextTips(bool enable = true);

// Enable or disable all installed button docs.
extern void EnableButtonDocs(bool enable = true);

// Enable or disable all installed text docs.
extern void EnableTextDocs(bool enable = true);


// Data

#if defined(IF_XM)
// Create a help text if the `help' resource is empty
extern MString (*DefaultHelpText)(Widget widget);

// Create a help text if the `tipString' resource is empty
extern MString (*DefaultTipText)(Widget widget, XEvent *event);

// Create a help text for the documentation if the `documentationString'
// resource is empty
extern MString (*DefaultDocumentationText)(Widget widget, XEvent *event);

// Return a text position associated with this event
extern XmTextPosition (*TextPosOfEvent)(Widget widget, XEvent *event);
#else
// Create a help text if the `help' resource is empty
extern GUI::String (*DefaultHelpText)(GUI::Widget *widget);

// Create a help text if the `tipString' resource is empty
extern GUI::String (*DefaultTipText)(GUI::Widget *widget, GUI::Event *event);

// Create a help text for the documentation if the `documentationString'
// resource is empty
extern GUI::String (*DefaultDocumentationText)(GUI::Widget *widget, GUI::Event *event);

// Return a text position associated with this event
extern long (*TextPosOfEvent)(GUI::ScrolledText *widget, GUI::Event *event);
#endif

// Hook for displaying documentation
extern void (*DisplayDocumentation)(const MString& doc);

#if defined(IF_XM)
// Hook before help on context
extern void (*PreHelpOnContextHook)(Widget w, XtPointer client_data, 
				    XtPointer call_data);

// Hook after help on item
extern void (*PostHelpOnItemHook)(Widget item);

// Additional text to display at ``help on version''
extern MString helpOnVersionExtraText;
#else
// Hook before help on context
extern void (*PreHelpOnContextHook)(GUI::Widget *, GUI::Event *);

// Hook after help on item
extern void (*PostHelpOnItemHook)(GUI::Widget *item);

// Additional text to display at ``help on version''
extern GUI::String helpOnVersionExtraText;
#endif

// Delay times (in ms)
extern int help_button_tip_delay; // delay before raising button tip
extern int help_value_tip_delay;  // delay before raising value tip
extern int help_button_doc_delay; // delay before showing button doc
extern int help_value_doc_delay;  // delay before showing value doc
extern int help_clear_doc_delay;  // delay before clearing doc
extern int help_clear_tip_delay;  // delay before clearing tip

#endif // _DDD_HelpCB_h
// DON'T ADD ANYTHING BEHIND THIS #endif
