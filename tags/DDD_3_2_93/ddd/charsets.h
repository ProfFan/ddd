// $Id$ -*- C++ -*-
// Character sets used in DDD

// Copyright (C) 1997 Technische Universitaet Braunschweig, Germany.
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

#ifndef _DDD_charsets_h
#define _DDD_charsets_h

#ifdef __GNUG__
#pragma interface
#endif

#include "MString.h"

// Character sets

// The default charset (for button labels, etc.)
#define CHARSET_DEFAULT  MSTRING_DEFAULT_CHARSET

// The fixed-width font used in texts.
#define CHARSET_TT XmStringCharSet("tt")

// The bold variant of TT.
#define CHARSET_TB XmStringCharSet("tb")

// The slanted variant of TT.
#define CHARSET_TS XmStringCharSet("ts")

// The bold slanted variant of TT.
#define CHARSET_TBS XmStringCharSet("tbs")

// Roman text.
#define CHARSET_RM XmStringCharSet("rm")

// Slanted text
#define CHARSET_SL XmStringCharSet("sl")

// Bold face text
#define CHARSET_BF XmStringCharSet("bf")

// Bold slanted text
#define CHARSET_BS XmStringCharSet("bs")

// Key caps
#define CHARSET_KEY XmStringCharSet("key")

// The fixed-width font used in text fields
#define CHARSET_TEXT XmStringCharSet("text")

// Logo
#define CHARSET_LOGO XmStringCharSet("logo")

// Large logo
#define CHARSET_LLOGO XmStringCharSet("llogo")

// Symbol
#define CHARSET_SYMBOL XmStringCharSet("symbol")

// Small font (for `<<' and `>>')
#define CHARSET_SMALL XmStringCharSet("small")

// Light font (for the command tool buttons)
#define CHARSET_LIGHT XmStringCharSet("light")


// Convenience functions
inline MString tt(const string& text) 
{
    return MString(text, CHARSET_TT);
}

inline MString tb(const string& text) 
{
    return MString(text, CHARSET_TB);
}

inline MString rm(const string& text) 
{
    return MString(text, CHARSET_RM);
}

inline MString sl(const string& text) 
{
    return MString(text, CHARSET_SL);
}

inline MString bf(const string& text) 
{
    return MString(text, CHARSET_BF);
}

inline MString bs(const string& text) 
{
    return MString(text, CHARSET_BS);
}


// Newline function
#if XmVERSION == 1 && XmREVISION <= 1
inline MString cr() { return rm("\n"); }
#else
inline MString cr() 
{
    static XmString sep = XmStringSeparatorCreate();
    return MString(sep, true);
}
#endif

#endif // _DDD_charsets_h
// DON'T ADD ANYTHING BEHIND THIS #endif