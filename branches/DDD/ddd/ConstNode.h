// $Id$
// Deklaration Klasse ConstNode

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
// Revision 1.1  1995/05/01 15:47:36  zeller
// Initial revision
//
// Revision 10.14  1995/03/17  07:44:12  zeller
// New: renamed `boolean' to `bool'
//
// Revision 10.13  1994/09/05  06:34:06  zeller
// Fix: copy constructors made const correct
//
// Revision 10.12  1994/07/21  08:19:13  zeller
// Even more functions declared `const'
//
// Revision 10.11  1994/07/19  20:30:11  zeller
// Changes for gcc-2.6.0 (and ANSI C++)
//
// Revision 10.10  1993/08/27  15:37:52  zeller
// Neu: TypeInfo
//
// Revision 10.9  1993/05/22  20:16:52  zeller
// %Q% added by apply-q-flag.sh 1.5
//
// Revision 10.8  1993/04/22  11:07:40  zeller
// Lizenz verbessert
// 
// Revision 10.7  1993/04/21  00:27:54  zeller
// Umbenennung der Header-Dateien
// 
// Revision 10.6  1993/04/20  23:06:26  zeller
// Neuer Name gegen mehrfaches #include
// 
// Revision 10.5  1993/04/16  11:44:24  zeller
// Neu: GNU Library General Public License eingefuegt
// 
// Revision 10.4  1992/11/03  19:37:13  zeller
// Tabstops jetzt 8 statt 4
// 
// Revision 10.3  1992/06/02  03:00:01  zeller
// Neu: #pragma interface
// 
// Revision 10.2  1992/06/01  14:25:23  zeller
// #pragma once entfernt
// 
// Revision 10.1  1992/02/18  11:19:47  zeller
// Konfliktfreie Typbezeichner eingefuehrt
// 
// Revision 9.1  1991/07/08  05:57:02  zeller
// Installierte Version
// 
// Revision 8.1  1991/07/06  15:02:07  zeller
// Installierte Version
// 
// Revision 4.2  1991/07/02  14:37:57  zeller
// Neu: _dumpTree()
// 
// Revision 4.1  1991/05/25  12:53:07  zeller
// Neue Version mit folgenden Eigenschaften:
// Let- und Where-Konstrukten;
// Lokalen und globalen Funktionen, Overloading;
// Erweiterten Fehlermeldungen.
// 
// Revision 2.9  1991/05/23  18:54:12  zeller
// Neues Namenskonzept (schon wieder):
// Namen werden erst aufgeloest, wenn gesamter Ausdruck eingelesen.
// 
// Revision 2.8  1991/05/09  16:06:00  zeller
// Warnungen vermieden
// 
// Revision 2.7  1991/02/26  18:01:26  zeller
// isStraight() eingefuehrt
// 
// Revision 2.6  1991/02/25  16:24:10  zeller
// Neues Konzept leere Listen eingefuehrt
// 
// Revision 2.5  1991/02/24  19:04:36  zeller
// Neue Pruefungen 'NoBox' eingefuehrt
// 
// Revision 2.4  1991/02/20  19:51:22  zeller
// Neues Vergleichsverfahren mit Trace-Moeglichkeit
// 
// Revision 2.3  1991/02/20  18:54:41  zeller
// Neues Typenkonzept eingefuehrt
// 
// Revision 2.2  1991/02/20  12:10:33  zeller
// Beschreibung eingefuehrt
// 
// Revision 2.1  1991/02/20  12:00:00  zeller
// Initial revision
// 

#ifndef _Nora_ConstNode_h
#define _Nora_ConstNode_h

#ifdef __GNUG__
#pragma interface
#endif


// Ein ConstNode gibt zur Laufzeit eine Konstante zurueck.


#include "assert.h"
#include <iostream.h>

#include "VSLNode.h"
#include "Box.h"

// ConstNode

class ConstNode: public VSLNode {
public:
    DECLARE_TYPE_INFO

private:
    Box *_box;

protected:
    ConstNode(const ConstNode& node):
	VSLNode(node), _box(node._box->link())
    {}
    
    void dump(ostream& s) const;
    void _dumpTree(ostream& s) const;

    bool matches(const VSLNode& node) const
    {
	return VSLNode::matches(node) &&
		*_box == *(((ConstNode *)&node)->_box); // dirty trick
    }

public:
    // ConstNode erzeugen
    ConstNode(Box *box, char *type = "ConstNode"): 
	VSLNode(type), _box(box)
    {}

    ~ConstNode()
    // ConstNode zerstoeren
    {
	_box->unlink();
    }

    // ConstNode kopieren
    VSLNode *dup() const
    {
	return new ConstNode(*this);
    }

    const Box *_eval(ListBox *arglist) const;

    bool isConst() const { return true; }
    bool isConstNode() const { return true; }

    bool isStraight() const;

    // Repraesentations-Invariante
    bool OK() const;
};



#endif