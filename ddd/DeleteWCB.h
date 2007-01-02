// $Id: DeleteWCB.h,v 1.1.1.1 2003/03/03 00:44:05 rockyb Exp $ -*- C++ -*-
// Add deletion callback to window

// Copyright (C) 2000 Universitaet Passau, Germany.
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

#ifndef _DDD_DeleteWindowCallBack_h
#define _DDD_DeleteWindowCallBack_h

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef IF_MOTIF

#include <X11/Intrinsic.h>

#endif // IF_MOTIF

#include "gtk_wrapper.h"

#ifdef IF_MOTIF
extern void AddDeleteWindowCallback(Widget shell,
				    XtCallbackProc callback, 
				    XtPointer closure = 0);
#else // NOT IF_MOTIF
extern void AddDeleteWindowCallback(Widget shell,
				    GTK_SLOT_);
#endif // IF_MOTIF

#endif // _DDD_DeleteWindowCallBack_h
// DON'T ADD ANYTHING BEHIND THIS #endif
