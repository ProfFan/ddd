// $Id$
// Deklaration builtin()

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@ips.cs.tu-bs.de>.
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
// `http://www.cs.tu-bs.de/softech/ddd/',
// or send a mail to the DDD developers <ddd@ips.cs.tu-bs.de>.

#ifndef _DDD_VSLBuiltin_h
#define _DDD_VSLBuiltin_h

#ifdef __GNUG__
#pragma interface
#endif


#include "strclass.h"
#include "Range.h"
#include "bool.h"
#include "ListBox.h"

typedef Box * (*BuiltinFunc)(ListBox *);

struct VSLBuiltin {
    static int resolve(const string& func_name);
    // Index zu gegebener Funktion zurueckgeben

    static BuiltinFunc func(int index);
    // Funktionsaufruf zu gegebenem Index zurueckgeben

    static bool isAssoc(int functionIndex);
    // Flag: ist Funktion assoziativ?

    static bool hasSideEffects(int functionIndex);
    // Flag: hat Funktion Seiteneffekte?

    static char *func_name(int functionIndex);
    // Name fuer interne Repraesentation ("__op_halign")

    static char *ext_name(int functionIndex);
    // Name fuer externe Repraesentation ("(&)")

    static bool isInfix(int functionIndex);
    // Flag: ext_name infix ausgeben?
};

#endif
