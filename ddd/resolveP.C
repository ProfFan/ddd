// $Id$ -*- C++ -*-
// Search DDD resources

// Copyright (C) 2000 Universitaet Passau, Germany.
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

char resolvePath_rcsid[] = 
    "$Id$";

#ifdef __GNUG__
#pragma implementation
#endif

#include "resolveP.h"
#include "root.h"
#include "filetype.h"
#include "session.h"
#include "version.h"
#include "StringA.h"

#include <stdlib.h>

#ifndef LOG_RESOLVE_PATH
#define LOG_RESOLVE_PATH 1
#endif

// Return full path of FILE, searching in a number of predefined places.
// If not found, return "".
string resolvePath(const string& file)
{
    static StringArray prefixes;

    if (prefixes.size() == 0)
    {
	// Look in ~/.ddd.
	prefixes += session_state_dir();

	// Look in $DDD_HOME.
	if (getenv(DDD_NAME "_HOME") != 0)
	    prefixes += getenv(DDD_NAME "_HOME");

	// Look in DDD_ROOT (typically /usr/local/share/ddd-VERSION).
	prefixes += DDD_ROOT;

	// Look in DDD_ALT_ROOT (typically /usr/local/share/ddd)..
	prefixes += DDD_ALT_ROOT;

	// Look in standard prefix.
	prefixes += "/usr/local/share/" DDD_NAME "-" DDD_VERSION;
	prefixes += "/usr/local/share/" DDD_NAME;

	// Look in standard prefix.
	prefixes += "/usr/share/" DDD_NAME "-" DDD_VERSION;
	prefixes += "/usr/share/" DDD_NAME;

	// Look in standard prefix.
	prefixes += "/usr/local/lib/" DDD_NAME "-" DDD_VERSION;
	prefixes += "/usr/local/lib/" DDD_NAME;

	// Look in standard prefix.
	prefixes += "/usr/lib/" DDD_NAME "-" DDD_VERSION;
	prefixes += "/usr/lib/" DDD_NAME;
    }

    for (int i = 0; i < prefixes.size(); i++)
    {
	string path = prefixes[i] + "/" + file;
	if (is_regular_file(path))
	{
#if LOG_RESOLVE_PATH
	    clog << "Searching " << file << "..." << path << "\n";
#endif
	    return path;
	}
    }

#if LOG_RESOLVE_PATH
    clog << "Searching " << file << "...not found\n";
#endif

    return "";
}