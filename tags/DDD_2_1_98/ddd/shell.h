// $Id$ -*- C++ -*-
// Shell commands

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
// or send a mail to the DDD developers <ddd@ips.cs.tu-bs.de>.

#ifndef _DDD_shell_h
#define _DDD_shell_h

#ifdef __GNUG__
#pragma interface
#endif

#include "strclass.h"
#include "bool.h"

// Command management
extern bool remote_gdb();
extern string _sh_command(string command = "", 
			  bool force_local = false,
			  bool force_display_settings = false);
extern string sh_command(string command = "", bool force_local = false);
extern string sh_quote(string s);

// Host management
extern string gdb_host;		  // non-empty if separate host

#endif // _DDD_shell_h
// DON'T ADD ANYTHING BEHIND THIS #endif