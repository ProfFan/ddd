// $Id$ -*- C++ -*-
// Return `official' name of host

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

char hostname_rcsid[] = 
    "$Id$";

#include "hostname.h"
#include "config.h"
#include "base/bool.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if !HAVE_POPEN_DECL
extern "C" FILE *popen(const char *command, const char *mode);
#endif
#if !HAVE_PCLOSE_DECL
extern "C" int pclose(FILE *stream);
#endif

extern "C" {
// Get hostname.
// We prefer gethostname() on uname() since <sys/utsname.h> makes
// trouble on some systems.
#if HAVE_GETHOSTNAME
#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#if !HAVE_GETHOSTNAME_DECL
    int gethostname(char *name, size_t size);
#endif // !HAVE_GETHOSTNAME_DECL
#elif HAVE_UNAME
#if HAVE_SYS_UTSNAME_H
#include <sys/utsname.h>
#endif
#if !HAVE_UNAME_DECL
    int uname(struct utsname *name);
#endif
#endif // HAVE_UNAME


// Get host aliases.
#if HAVE_GETHOSTBYNAME && HAVE_NETDB_H

#if HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif

#include <netdb.h>

#ifndef AF_INET
#define AF_INET 2		// internetwork: UDP, TCP, etc.
#endif

#endif // HAVE_GETHOSTBYNAME && HAVE_NETDB_H
}

#include <sys/param.h>
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 1024
#endif

// Return local host name
const char *hostname()
{
    static const char *name = 0;
    if (name != 0)
	return name;

    char buffer[MAXHOSTNAMELEN];

    bool okay = false;

#if HAVE_GETHOSTNAME
    if (!okay && gethostname(buffer, sizeof(buffer)) == 0)
    {
	okay = true;
    }
#elif HAVE_UNAME
    struct utsname un;
    if (!okay && uname(&un) >= 0)
    {
	strcpy(buffer, un.nodename);
	okay = true;
    }
#endif

    if (!okay)
    {
	FILE *fp = popen("uname -n", "r");
	if (fp != 0)
	{
	    buffer[0] = '\0';
	    (void)! fscanf(fp, "%s", buffer);
	}
	pclose(fp);
    }

    if (okay)
	name = strcpy(new char[strlen(buffer) + 1], buffer);
    else
	name = "unknown";

    return name;
}

// Return the number of '.' in STR
inline int dots(const char *str)
{
    int dots = 0;
    while (*str != '\0')
	if (*str++ == '.')
	    dots++;

    return dots;
}

// Return most qualified name for the current host
static const char *_fullhostname(const char *most_qualified_host)
{
    // Try local name
    if (most_qualified_host == 0)
	most_qualified_host = hostname();

#if HAVE_GETHOSTBYNAME
    struct hostent *h = gethostbyname(most_qualified_host);
    if (h)
    {
	// Try official name
	if (dots(h->h_name) > dots(most_qualified_host))
	    most_qualified_host = (char *)h->h_name;

	// Try aliases
	for (int i = 0; h->h_aliases[i] != 0; i++)
	    if (dots(h->h_aliases[i]) > dots(most_qualified_host))
		most_qualified_host = h->h_aliases[i];

	if (dots(most_qualified_host) == 0)
	{
	    // Unqualified host - try network addresses
	    if (h->h_addrtype == AF_INET)
	    {
		for (int j = 0; h->h_addr_list[j] != 0; j++)
		{
		    static char num_host[128];
		    num_host[0] = '\0';
		    for (int i = 0; i < (int)h->h_length; i++)
			sprintf(num_host + strlen(num_host), i ? ".%d" : "%d",
				int((unsigned char)(h->h_addr_list[j][i])));

		    if (dots(num_host) > dots(most_qualified_host))
			most_qualified_host = num_host;
		}
	    }
	}
    }
#endif

    // Return most qualified host name
    return most_qualified_host;
}


// Return and cache a fully qualified name for the current host
const char *fullhostname(const char *host)
{
    // Buffer for local host name
    static char *name = 0;

    if (name && host == 0)
	return name;

    const char *n = _fullhostname(host);
    if (host == 0)
	return name = strcpy(new char[strlen(n) + 1], n);
    else
	return n;
}
