// $Id$ -*- C++ -*-
// DDD completion actions

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

#ifndef _DDD_complete_h
#define _DDD_complete_h

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(IF_XM)
#include <X11/Intrinsic.h>
#else
#include <GUI/Widget.h>
#include "gtk_wrapper.h"
#endif

#if defined(IF_XM)
// Actions
extern void complete_commandAct  (Widget, XEvent*, String*, Cardinal*);
extern void complete_argAct      (Widget, XEvent*, String*, Cardinal*);
extern void complete_tabAct      (Widget, XEvent*, String*, Cardinal*);
#else
// Actions
extern void complete_commandAct  (GUI::Widget *, GUI::Event *, GUI::String *, unsigned int *);
extern void complete_argAct      (GUI::Widget *, GUI::Event *, GUI::String *, unsigned int *);
extern void complete_tabAct      (GUI::Widget *, GUI::Event *, GUI::String *, unsigned int *);
#endif

// Completion is done
extern void clear_completion_delay();

#endif // _DDD_complete_h
// DON'T ADD ANYTHING BEHIND THIS #endif