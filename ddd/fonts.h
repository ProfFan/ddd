// $Id$ -*- C++ -*-
// Setup DDD fonts

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

#ifndef _DDD_fonts_h
#define _DDD_fonts_h

#include "strclass.h"
#include "AppData.h"

#ifdef IF_MOTIF

#include <X11/Intrinsic.h>

#endif // IF_MOTIF

#include "gtk_wrapper.h"

// Font types
enum DDDFont { DefaultDDDFont       = 0,
	       VariableWidthDDDFont = 1,
	       FixedWidthDDDFont    = 2,
	       SymbolDDDFont        = 3,
               DataDDDFont          = 4 };

// Setup font specs.  DB is the resource database in use.
extern void setup_fonts(AppData& app_data, XrmDatabase db = 0);

// Return font name from BASE, overriding with parts from OVERRIDE.
// Override contains "-SPEC-SPEC-..."; each non-empty SPEC overrides
// the default in BASE.
extern string make_font(const AppData& ad, DDDFont base, 
			const string& override = "");

// Set a new font resource
extern void set_font(DDDFont n, const string& name);

// Browse fonts
extern void BrowseFontCB(CB_ALIST_12(BUTTON_P w, XtP(DDDFont)));

// Set font name and size
extern void SetFontNameCB(CB_ALIST_12(ENTRY_P, XtP(DDDFont)));
extern void SetFontSizeCB(CB_ALIST_12(ENTRY_P, XtP(DDDFont)));

#endif // _DDD_fonts_h
// DON'T ADD ANYTHING BEHIND THIS #endif
