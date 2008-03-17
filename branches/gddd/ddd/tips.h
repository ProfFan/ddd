// $Id$ -*- C++ -*-
// Show startup tips

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

#ifndef _DDD_tips_h
#define _DDD_tips_h

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(IF_XM)
#include <X11/Intrinsic.h>
#else
#include <GUI/Button.h>
#include <GUI/CheckButton.h>
#endif

#include "gtk_wrapper.h"

#if defined(IF_XM)
extern void TipOfTheDayCB(Widget w, XtPointer = 0, XtPointer = 0);
extern void SetStartupTipsCB(Widget, XtPointer, XtPointer);
#else
extern void TipOfTheDayCB(GUI::Button *w);
extern void SetStartupTipsCB(GUI::CheckButton *);
#endif

#if defined(IF_XM)
extern Widget set_startup_tips_w;
#else
extern GUI::CheckButton *set_startup_tips_w;
#endif

#endif // _DDD_tips_h
// DON'T ADD ANYTHING BEHIND THIS #endif
