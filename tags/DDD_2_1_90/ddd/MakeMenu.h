// $Id$
// Simple interface to motif menus

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@ips.cs.tu-bs.de>.
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
// or send a mail to the DDD developers <ddd@ips.cs.tu-bs.de>.

#ifndef _DDD_MakeMenu_h
#define _DDD_MakeMenu_h

#include <X11/Intrinsic.h>

// Main types
typedef int MMType;

const MMType MMPush        =  0; // create PushButton (default)
const MMType MMToggle      =  1; // create ToggleButton
const MMType MMMenu        =  2; // create CascadeButton with menu
const MMType MMSeparator   =  3; // create Separator
const MMType MMLabel       =  4; // create Label
const MMType MMRadioMenu   =  5; // create CascadeButton with RadioBox menu
const MMType MMOptionMenu  =  6; // create an option menu
const MMType MMPanel       =  7; // create a panel
const MMType MMRadioPanel  =  8; // create a panel with RadioBox menu
const MMType MMButtonPanel =  9; // like MMRadioPanel, but no radio behavior
const MMType MMScale       = 10; // create a scale

const MMType MMTypeMask    = 15; // mask to find type


// Special attributes, to be ORed with types

typedef int MMAttr;

const MMAttr MMHelp        = 16; // this is a help button
const MMAttr MMInsensitive = 32; // make item insensitive
const MMAttr MMUnmanaged   = 64; // make item unmanaged
const MMAttr MMAttrMask    = ~MMTypeMask;



// Description data structure

struct MMDesc {
    String name;		 // Widget name
    MMType type;		 // Widget type
    XtCallbackRec callback;	 // Associated callback
    MMDesc *items;		 // Submenus (NULL if none)
    Widget *widgetptr;           // Where to store the resulting widget
    Widget widget;		 // The resulting widget
};


// Fields

/*
    Type        Callback                 Items   Widget
    ----------- ------------------------ ------- -------------
    MMPush      XmNactivateCallback      -/-     PushButton
    MMToggle    XmNvalueChangedCallback  -/-     ToggleButton
    MMMenu      XmNmapCallback           items   CascadeButton
    MMSeparator -/-                      -/-     Separator
    MMLabel     -/-                      -/-     Label
*/


// Procs

typedef void (*MMItemProc)(MMDesc items[], XtPointer closure);


// Functions
Widget MMcreatePulldownMenu      (Widget parent, String name, MMDesc items[]);
Widget MMcreateRadioPulldownMenu (Widget parent, String name, MMDesc items[]);
Widget MMcreatePopupMenu         (Widget parent, String name, MMDesc items[]);
Widget MMcreateMenuBar           (Widget parent, String name, MMDesc items[]);
Widget MMcreateWorkArea          (Widget parent, String name, MMDesc items[]);
Widget MMcreatePanel             (Widget parent, String name, MMDesc items[]);
Widget MMcreateRadioPanel        (Widget parent, String name, MMDesc items[]);
Widget MMcreateButtonPanel       (Widget parent, String name, MMDesc items[]);

void   MMaddCallbacks   (MMDesc items[], XtPointer default_closure = 0);
void   MMaddHelpCallback(MMDesc items[], XtCallbackProc proc);
void   MMonItems        (MMDesc items[], MMItemProc proc, 
			 XtPointer closure = 0);

// Conveniences
#define MMNoCB { NULL }
#define MMEnd  { NULL }
#define MMSep  { "separator", MMSeparator }

// New resources
#define XtNpushMenuPopupTime  "pushMenuPopupTime"
#define XtCPushMenuPopupTime  "PushMenuPopupTime"

#endif // _DDD_MakeMenu_h
// DON'T ADD ANYTHING BEHIND THIS #endif