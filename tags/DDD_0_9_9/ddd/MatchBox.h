// $Id$ 
// Deklaration Klasse MatchBox

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

#ifndef _Nora_MatchBox_h
#define _Nora_MatchBox_h

#ifdef __GNUG__
#pragma interface
#endif


// Eine MatchBox wird -- fast ausschliesslich -- zum Pattern-Matching
// verwendet. Ist 'matchesAll' gesetzt, matcht die MatchBox jede
// andere Box (sonst nur eine gleiche). Ist 'matchCallback' gesetzt,
// wird eine Funktion nach jedem geglueckten Matchen aufgerufen.


#include "strclass.h"
#include "bool.h"
#include "Box.h"
#include "Widget.h"
#include "DummyBox.h"

// MatchBox

typedef void (*MatchBoxFunc)(int, const Box *);


class MatchBox: public DummyBox {
public:
    DECLARE_TYPE_INFO

private:
    int _data;  // Datum

protected:
    // Kopieren
    MatchBox(const MatchBox& box):
	DummyBox(box),
	_data(box._data)
    {}

    void dump(ostream& s) const;

    // Bei Vergleichen: Match-Funktion aufrufen
    bool matches (const Box &b, const Box *callbackArg = 0) const;

public:
    // Konstruktor
    MatchBox(int d, char *t = "MatchBox"):
	DummyBox(t),
	_data(d)
    {}

    Box *dup() const { return new MatchBox(*this); }

    static MatchBoxFunc matchCallback;  // Funktion bei Matching

    // MatchBoxen zaehlen
    void countMatchBoxes(int instances[]) const
    {
	instances[_data]++;
    }
};

#endif