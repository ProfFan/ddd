// $Id$
// Data/Length struct

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

#ifndef _Nora_DataLength_h
#define _Nora_DataLength_h

#ifdef __GNUG__
#pragma interface
#endif


#include <string.h>
#include "TypeInfo.h"

struct DataLength {
    DECLARE_TYPE_INFO

    const char *data;
    int length;

    DataLength(const char *d):
	data(d), length(strlen(d))
    {}

    DataLength(const char *d, int l):
        data(d), length(l)
    {}
};

#endif
