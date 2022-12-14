// $Id$ -*- C++ -*-
// DispValue Types

// Copyright (C) 1998 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@gnu.org>.
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

char DispValueType_rcsid[] = 
    "$Id$";

#include "DispValueT.h"

//-----------------------------------------------------------------------------
// Debugging stuff
//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, DispValueType type)
{
    switch (type)
    {
    case UnknownType: os << "Unknown";     break;
    case Simple:      os << "Simple";      break;
    case Pointer:     os << "Pointer";     break;
    case Array:       os << "Array";       break;
    case Struct:      os << "Struct";      break;
    case Reference:   os << "Reference";   break;
    case Sequence:    os << "Sequence";    break;
    case List:        os << "List";	   break;
    case Text:        os << "Text";	   break;
    case UserCommand: os << "UserCommand"; break;
    case STLVector:   os << "STLVector";   break;
    case STLList:     os << "STLList";     break;
    }
    
    return os;
}
