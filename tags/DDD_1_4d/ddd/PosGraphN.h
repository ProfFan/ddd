// $Id$
// PosGraphNode class: GraphNode with position

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller (zeller@ips.cs.tu-bs.de).
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
// 675 Mass Ave, Cambridge, MA 02139, USA.
// 
// DDD is the data display debugger.
// For details, see the DDD World-Wide-Web page, 
// `http://www.cs.tu-bs.de/softech/ddd/',
// or send a mail to the DDD developers at `ddd@ips.cs.tu-bs.de'.

#ifndef _Nora_PosGraphNode_h
#define _Nora_PosGraphNode_h

#ifdef __GNUG__
#pragma interface
#endif


#include "GraphNode.h"
#include "BoxPoint.h"

class PosGraphNode: public GraphNode {
public:
    DECLARE_TYPE_INFO

private:
    BoxPoint _pos;	// position

protected:
    // Copy Constructor
    PosGraphNode(const PosGraphNode& node):
	GraphNode(node),
	_pos(node._pos)
    {}

public:
    // Constructor
    PosGraphNode(const BoxPoint& initialPos = BoxPoint()):
	_pos(initialPos)
    {}

    // Move
    virtual void moveTo(const BoxPoint& newPos)
    {
	_pos = newPos;
    }

    // Attributes
    virtual const BoxPoint& pos() const
    {
	return _pos;
    }
};

#endif