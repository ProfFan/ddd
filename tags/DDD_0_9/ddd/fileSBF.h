// $Id$  -*- C++ -*-
// get filename from file selection box

// Copyright (C) 1993 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller (zeller@ips.cs.tu-bs.de).
// 
// This file is part of the NORA Library.
// 
// The NORA Library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// The NORA Library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Library General Public License for more details.
// 
// You should have received a copy of the GNU Library General Public
// License along with the NORA Library -- see the file COPYING.LIB.
// If not, write to the Free Software Foundation, Inc.,
// 675 Mass Ave, Cambridge, MA 02139, USA.
// 
// NORA is an experimental inference-based software development
// environment. Contact nora@ips.cs.tu-bs.de for details.

// $Log$
// Revision 1.1  1995/05/01 15:48:04  zeller
// Initial revision
//
// Revision 1.6  1995/03/27  16:03:59  zeller
// Fix: don't include <Nora/...>
//

#ifndef _Nora_fileSelectionBoxFilename_h
#define _Nora_fileSelectionBoxFilename_h

#ifdef __GNUG__
#pragma interface
#endif

#include <Xm/Xm.h>
#include "strclass.h"

extern string fileSelectionBoxFilename(XtPointer call_data);

#endif // _Nora_fileSelectionBoxFilename_h
// DON'T ADD ANYTHING BEHIND THIS #endif
