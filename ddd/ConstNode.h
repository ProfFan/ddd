// $Id$
// Constants

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
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

#ifndef _DDD_ConstNode_h
#define _DDD_ConstNode_h

#ifdef __GNUG__
#pragma interface
#endif


// A ConstNode returns a constant box upon run-time


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

private:
    ConstNode& operator = (const ConstNode&)
    {
	assert(0); return *this;
    }

public:
    // Constructor
    ConstNode(Box *box, char *type = "ConstNode"): 
	VSLNode(type), _box(box)
    {}

    // Destructor
    ~ConstNode()
    {
	_box->unlink();
    }

    // Copy
    VSLNode *dup() const
    {
	return new ConstNode(*this);
    }

    const Box *_eval(ListBox *arglist) const;

    bool isConst() const { return true; }
    bool isConstNode() const { return true; }

    bool isStraight() const;

    // Representation invariant
    bool OK() const;
};

#endif
