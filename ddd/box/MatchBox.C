// $Id$ 
// Matching boxes (for pattern matching)

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
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

char MatchBox_rcsid[] = 
    "$Id$";

#include "assert.h"
#include "MatchBox.h"

DEFINE_TYPE_INFO_1(MatchBox, DummyBox)

// MatchBox

MatchBoxFunc MatchBox::matchCallback = 0;

// Call callback during matching

bool MatchBox::matches (const Box &box, const Box *callbackArg) const
{
    bool ret = matchesAll ||
	(DummyBox::matches(box) &&
	    _data == ((const MatchBox *)&box)->_data); // dirty trick

    if (ret && matchCallback)
    {
	if (callbackArg == 0)
	    callbackArg = &box;
	matchCallback(_data, callbackArg);
    }

    return ret;
}

// Dump
void MatchBox::dump(std::ostream& s) const
{
    s << "<" << _data << ">";
}
