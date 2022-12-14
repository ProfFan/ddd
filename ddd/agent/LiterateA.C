// $Id$
// Agent interface on a callback basis

// Copyright (C) 1995-1998 Technische Universitaet Braunschweig, Germany.
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

char LiterateAgent_rcsid[] = 
    "$Id$";

#include "config.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>		// On Linux, includes _G_config.h
#include <ctype.h>

#if HAVE_FCNTL_H
#include <fcntl.h>
#endif

#if HAVE_FCNTL && !HAVE_FCNTL_DECL && !defined(fcntl)
extern "C" int fcntl(int fd, int command, ...);
#endif

#include "base/bool.h"
#include "LiterateA.h"
#include "base/SignalB.h"
#include "ChunkQueue.h"

#include <limits.h>

#ifndef ARG_MAX
#define ARG_MAX 4096
#endif


DEFINE_TYPE_INFO_1(LiterateAgent, AsyncAgent)

// ---------------------------------------------------------------------------
// TTY blocking
// ---------------------------------------------------------------------------

// This package reads data in non-blocking mode, reading only data
// that is currently present.  Unfortunately, this is not a good idea
// for ttys, since if the process is run in the background, it will
// set non-blocking mode for its controlling tty.  Since this mode
// change affects all processes reading from this tty, they will
// detect an EOF on input and (most likely) exit.

// Consequently, we provide a special flag, BLOCK_TTY_INPUT.  If
// BLOCK_TTY_INPUT is TRUE, we use blocking mode for TTYs and read
// only one line at a time.  This works fine unless the process
// runs in raw or cbreak mode.  If BLOCK_TTY_INPUT is FALSE, we
// have no special treatment for TTYs.

// Determine an appropriate default setting
bool LiterateAgent::default_block_tty_input()
{
#if defined(BLOCK_TTY_INPUT)
    return BLOCK_TTY_INPUT;

#elif defined(linux)
    // All Linux variants want BLOCK_TTY_INPUT to be unset:

    // * Andi <ak@muc.de> states that Linux with GNU libc 5.3.12 wants
    //   BLOCK_TTY_INPUT to be unset.
    // * Ronald Wahl <rwahl@gmx.net>, Phil Romig <romig@bierstadt.unl.edu> 
    //   and Michael Marxmeier <mike@msede.com> report the same for GNU 
    //   libc 5.4.33.
    // * Terence Spielman <terence@globeset.com> says that Linux
    //   with GNU libc 5.4.35 also doesn't want BLOCK_TTY_INPUT.  
    // * Anders Wegge Jakobsen <wegge@wegge.dk> reports the same for
    //   GNU libc 5.4.38.
    // * Ray Dassen <jdassen@wi.LeidenUniv.nl> reports that Linux with
    //   GNU libc 6 (that is, glibc 2.x or later) wants BLOCK_TTY_INPUT
    //   to be unset.

    // There are no reports for earlier Linux variants, so let's keep
    // it this way.
    return false;

#else  // !LINUX && !BLOCK_TTY_INPUT
    // For all other systems, the default is BLOCK_TTY_INPUT set.  (I
    // don't know whether this is the `best' setting, but I have no
    // reason to change a default that has been around successfully
    // for so long...)

    return true;
#endif // !LINUX && !BLOCK_TTY_INPUT
}


// ---------------------------------------------------------------------------
// I/O functions
// ---------------------------------------------------------------------------

// Input data handling
int LiterateAgent::readInput(const char*& data)
{
    data = "";
    if (inputfp() == 0 || !activeIO)
	return -1;

    return _readInput(data);
}

// Error data handling
int LiterateAgent::readError(const char*& data)
{
    data = "";
    if (errorfp() == 0 || !activeIO)
	return -1;

    return _readError(data);
}

// Write a whole string
int LiterateAgent::write(const char *data, int length)
{
    if (outputfp() == 0 || !activeIO)
	return -1;

    int failures = 0;

    while (length > 0)
    {
	errno = 0;
	int nitems = ::write(fileno(outputfp()), data, length);

	if (nitems <= 0)
	{
	    if (false
#ifdef EAGAIN
		|| errno == EAGAIN 
#endif
#ifdef EWOULDBLOCK
		|| errno == EWOULDBLOCK
#endif
#ifdef EINTR
		|| errno == EINTR
#endif
		)
	    {
		continue;	// Try again, possibly blocking
	    }

	    if (nitems == 0 && ++failures <= 3)
	    {
		std::ostringstream os;
		os << "write failed (attempt #" 
		   << failures << ", still trying)";
		string s(os);
		raiseIOMsg(s);
		sleep(1);
		continue;
	    }
	    else
	    {
		raiseIOMsg("write failed");
		return -1;
	    }
	}

	assert(nitems > 0);
	dispatch(Output, data, nitems);

	length -= nitems;
	data += nitems;
    }

    if (failures)
	raiseMsg("write ok");

    return 0;
}

// Flush output buffers
int LiterateAgent::flush()
{
    // Not needed, since we use immediate write()
    return 0;
}


// Read from fp without delay
int LiterateAgent::_readNonBlocking(char *buffer, int nelems, FILE *fp)
{
    // Avoid being stopped when file is non-blocking
    SignalBlocker sb;

#if HAVE_FCNTL && defined(O_NONBLOCK)
    // Make file non-blocking
    int flags = fcntl(fileno(fp), F_GETFL, 0);
    if (flags == -1)
	_raiseIOWarning("cannot get file descriptor status flags");
    if (fcntl(fileno(fp), F_SETFL, flags | O_NONBLOCK) == -1)
	_raiseIOWarning("cannot set file to non-blocking mode");
#endif

    /*
     * On Linux, this call is returning zero with errno set to EIO
     * when we are exiting.  That causes an infinite loop unless
     * the caller checks with ferror().
     */
    // Read stuff
    int nitems = fread(buffer, sizeof(char), nelems, fp);

    if (nitems <= 0)
    {
	if (false
#ifdef EAGAIN
	|| errno == EAGAIN
#endif
#ifdef EWOULDBLOCK
	|| errno == EWOULDBLOCK
#endif
	)
	{
	    // Resource temporarily unavailable: an operation that
	    // would block was attempted on an object that has
	    // non-blocking mode selected.  Trying the same operation
	    // again will block until some external condition makes it
	    // possible to read, write, or connect (whatever the
	    // operation).  So, just try again next time.
	    nitems = 0;

	    // Linux libc 5.4.39 and later treats EAGAIN and
	    // EWOULDBLOCK as EOF condition.  This is a bad idea.
	    clearerr(fp);
	}
    }


#if HAVE_FCNTL && defined(F_SETFL)
    // Reset file state
    if (fcntl(fileno(fp), F_SETFL, flags) == -1)
	_raiseIOWarning("cannot restore file mode");
#endif

    return nitems;
}


// Read from fp
int LiterateAgent::_read(const char*& data, FILE *fp)
{
    static ChunkQueue queue(ARG_MAX);

    queue.discard();
    char buffer[ARG_MAX + 1];
    
    if (blocking_tty(fp))
    {
	// Non-blocking ttys are nasty, so we read only the 
	// single line available here and now.
	char *s = fgets(buffer, ARG_MAX, fp);

	if (s != 0)
	    queue.append(buffer, strlen(buffer));
	else if (false
#ifdef EAGAIN
		 || errno == EAGAIN
#endif
#ifdef EINTR
		 || errno == EINTR
#endif
#ifdef EWOULDBLOCK
		 || errno == EWOULDBLOCK
#endif
	    )
	{
	    // Linux libc 5.4.39 and later treats EAGAIN and
	    // EWOULDBLOCK as EOF condition.  This is a bad idea.
	    clearerr(fp);
	}
    }
    else
    {
	// Otherwise, read and accumulate whatever's there - up to
	// ARG_MAX characters
	int length = -1;
	while (queue.length() < ARG_MAX
	       && (length = _readNonBlocking(buffer, ARG_MAX, fp)) > 0)
	    queue.append(buffer, length);

	if (length < 0)
	    raiseIOMsg("read from agent failed");
    }

    data = queue.data();
    return queue.length();
}

int LiterateAgent::_readInput(const char*& data)
{
    return _read(data, inputfp());
}

int LiterateAgent::_readError(const char*& data)
{
    return _read(data, errorfp());
}



// ---------------------------------------------------------------------------
// Dispatchers
// ---------------------------------------------------------------------------

// dispatch data to <type> handler 
void LiterateAgent::dispatch(int type, const char *data, int length)
{
  // TODO is this correction all right ?
    if (data[length] != '\0'){
      const string s1(data,length);
      const char *data_l = s1.chars();
      DataLength dl(data_l, length);
      
      // call global handlers
      callHandlers(type, &dl);
    } else {
      DataLength dl(data, length);
      
      // call global handlers
      callHandlers(type, &dl);
    }
}
    

// ---------------------------------------------------------------------------
// Handlers
// ---------------------------------------------------------------------------

// Data handlers

void LiterateAgent::outputReady(AsyncAgent *c)
{
    ptr_cast(LiterateAgent, c)->callHandlers(Ready);
}

void LiterateAgent::inputReady(AsyncAgent *c)
{
    char data[ARG_MAX];
    const char *datap = data;
    LiterateAgent *lc = ptr_cast(LiterateAgent, c);
    if (lc != 0)
    {
	int length = lc->readInput(datap);
	if (length > 0)
	    lc->dispatch(Input, datap, length);
	else if (length == 0 && lc->inputfp() != 0
		&& (feof(lc->inputfp()) || ferror(lc->inputfp())))
	    lc->inputEOF();
    }
}

void LiterateAgent::errorReady(AsyncAgent *c)
{
    char data[ARG_MAX];
    const char *datap = data;
    LiterateAgent *lc = ptr_cast(LiterateAgent, c);
    if (lc != 0)
    {
	int length = lc->readError(datap);
	if (length > 0)
	    lc->dispatch(Error, datap, length);
	else if (length == 0 && lc->errorfp() != 0 && feof(lc->errorfp()))
	    lc->errorEOF();
    }
}

// Input Data is available: read all and call Input handlers of current job
void LiterateAgent::readAndDispatchInput(bool expectEOF)
{
    const char *data;

    int length = readInput(data);
    if (length > 0)
    {
	dispatch(Input, data, length);
    }
    else if (length == 0 && inputfp() != 0 && feof(inputfp()))
    {
	if (expectEOF)
	    clearerr(inputfp());
	else
	    inputEOF();
    }
}

// Error Data is available: read all and call Error handlers of current job
void LiterateAgent::readAndDispatchError(bool expectEOF)
{
    const char *data;

    int length = readError(data);
    if (length > 0)
    {
	dispatch(Error, data, length);
    }
    else if (length == 0 && errorfp() != 0 && feof(errorfp()))
    {
	if (expectEOF)
	    clearerr(errorfp());
	else
	    errorEOF();
    }
}


// (Re)set I/O handlers
void LiterateAgent::handlerChange()
{
    if (activeIO)
	_activateIO();
}

// Activate Handlers
void LiterateAgent::_activateIO()
{
    // We do select this event only if a handler is present
    // Otherwise, outputReady() may be called all the time
    setHandler(OutputReady, hasHandler(Ready) ? outputReady : 0);
    setHandler(InputReady,  inputReady);
    setHandler(ErrorReady,  errorReady);
}

// Deactivate Handlers
void LiterateAgent::_deactivateIO()
{
    setHandler(OutputReady, 0);
    setHandler(InputReady,  0);
    setHandler(ErrorReady,  0);
}


// Starter
void LiterateAgent::start()
{
    AsyncAgent::start();
    
    // Dispatch input data that may already be there  (if there is some)
    if (inputfp() != 0 && !blocking_tty(inputfp()))
	readAndDispatchInput(true);

    if (errorfp() != 0 && !blocking_tty(errorfp()))
	readAndDispatchError(true);
}

// Terminator
void LiterateAgent::abort()
{
    // Dispatch remaining input data (if there is some remaining)
    activateIO();
    readAndDispatchInput(true);
    readAndDispatchError(true);

    // Clean up now
    deactivateIO();
    AsyncAgent::abort();
}
