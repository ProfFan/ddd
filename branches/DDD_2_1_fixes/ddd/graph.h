// $Id$ -*- C++ -*-
//

// Copyright (C) 1996 Technische Universitaet Braunschweig, Germany.
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
// or send a mail to the DDD developers at `ddd@ips.cs.tu-bs.de'.

#ifndef _DDD_graph_h
#define _DDD_graph_h

#ifdef __GNUG__
#pragma interface
#endif

#include <X11/Intrinsic.h>

extern void graphAlignCB        (Widget, XtPointer, XtPointer);
extern void graphRotateCB       (Widget, XtPointer, XtPointer);
extern void graphLayoutCB       (Widget, XtPointer, XtPointer);

extern void graphToggleLocalsCB (Widget, XtPointer, XtPointer);
extern void graphToggleArgsCB   (Widget, XtPointer, XtPointer);

#endif // _DDD_graph_h
// DON'T ADD ANYTHING BEHIND THIS #endif
