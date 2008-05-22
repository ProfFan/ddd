// $Id$ -*- C++ -*-
// Data Display progress meter

// Copyright (C) 1998 Technische Universitaet Braunschweig, Germany.
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

#ifndef _DDD_ProgressMeter_h
#define _DDD_ProgressMeter_h

#include "bool.h"
#include "strclass.h"
#include "status.h"

#if defined(IF_XM)
#include <X11/Intrinsic.h>
#endif


//-----------------------------------------------------------------------------
// Show progress while creating or updating displays
//-----------------------------------------------------------------------------

class ProgressMeter {
public:
    int current;		// Current data to be processed
    int base;			// Data already processed
    int total;			// Total of data to be processed

    ProgressMeter(const char *msg);
    ~ProgressMeter();

private:
    string msg;			// The message shown
    StatusDelay delay;		// The delay shown
    int last_shown;		// Last shown amount
    bool (*old_background)(int); // DispValue bg proc
    bool aborted;		// True iff bg proc aborted

    // Update progess meter every UPDATE_THRESHOLD characters.
    static const int UPDATE_THRESHOLD;

    // Popup working dialog when updating from at least DIALOG_THRESHOLD chars.
    static const int DIALOG_THRESHOLD;

#if defined(IF_XM)
    static Widget dialog;
    static Widget scale;
#else
    static GUI::Widget *dialog;
    static GUI::Widget *scale;
#endif

    bool process(int remaining_length);

    static ProgressMeter *active; // Currently active object
    static bool _process(int remaining_length);

#if defined(IF_XM)
    static void CancelCB(Widget, XtPointer, XtPointer);
#else
    static void CancelCB(GUI::Widget *);
#endif

private:
    // No copy constructor
    ProgressMeter(const ProgressMeter &);

    // No assignment
    ProgressMeter& operator = (const ProgressMeter &);
};

#endif // _DDD_ProgressMeter_h
// DON'T ADD ANYTHING BEHIND THIS #endif