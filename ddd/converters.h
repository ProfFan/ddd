// $Id$
// Own converters

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
// Revision 1.1  1995/05/01 15:47:57  zeller
// Initial revision
//
// Revision 1.11  1993/07/06  09:24:44  zeller
// Neu: CvtStringToAlignment, CvtStringToOrientation, CvtStringToPacking
//
// Revision 1.10  1993/05/22  20:10:00  zeller
// %Q% added by apply-q-flag.sh 1.5
//
// Revision 1.9  1993/04/22  11:04:12  zeller
// Lizenz verbessert
// 
// Revision 1.8  1993/04/20  23:02:18  zeller
// Neuer Name gegen mehrfaches #include
// 
// Revision 1.7  1993/04/16  11:41:55  zeller
// Neu: GNU Library General Public License eingefuegt
// 
// Revision 1.6  1993/03/26  11:19:54  zeller
// Neu: CvtStringToBitmap -- laesst Einsen und Nullen unveraendert
// 
// Revision 1.5  1992/11/23  17:32:16  zeller
// Neu: Eigener Konverter String -> XmString,\
// 
// Revision 1.4  1992/11/05  19:43:12  zeller
// Neuer String -> Pixmap/Bitmap-Konverter
// 
// Revision 1.3  1992/06/01  17:04:47  zeller
// #pragma once entfernt
// 
// Revision 1.2  1992/03/17  08:21:42  zeller
// CvtStringToWindow durch CvtStringToWidget ersetzt
// 
// Revision 1.1  1992/03/17  08:16:47  zeller
// Initial revision
// 

#ifndef _Nora_converters_h
#define _Nora_converters_h

// Convert String to Widget
extern Boolean CvtStringToWidget(Display *display, 
				 XrmValue *args, Cardinal *num_args, 
				 XrmValue *fromVal, XrmValue *toVal,
				 XtPointer *converter_data);

// Convert String to Pixmap, converting 1s and 0s to fg/bg color
extern Boolean CvtStringToPixmap(Display *display, 
				 XrmValue *args, Cardinal *num_args, 
				 XrmValue *fromVal, XrmValue *toVal,
				 XtPointer *converter_data);

// Convert String to Bitmap, leaving 1s and 0s untouched
extern Boolean CvtStringToBitmap(Display *display, 
				 XrmValue *args, Cardinal *num_args, 
				 XrmValue *fromVal, XrmValue *toVal,
				 XtPointer *converter_data);

// Convert String to XmString, using @ for font specs
extern Boolean CvtStringToXmString(Display *display, 
				   XrmValue *args, Cardinal *num_args, 
				   XrmValue *fromVal, XrmValue *toVal,
				   XtPointer *converter_data);

// Convert String to Alignment
extern Boolean CvtStringToAlignment(Display *display, 
				    XrmValue *args, Cardinal *num_args, 
				    XrmValue *fromVal, XrmValue *toVal,
				    XtPointer *converter_data);

// Convert String to Orientation
extern Boolean CvtStringToOrientation(Display *display, 
				      XrmValue *args, Cardinal *num_args, 
				      XrmValue *fromVal, XrmValue *toVal,
				      XtPointer *converter_data);

// Convert String to Packing
extern Boolean CvtStringToPacking(Display *display, 
				  XrmValue *args, Cardinal *num_args, 
				  XrmValue *fromVal, XrmValue *toVal,
				  XtPointer *converter_data);

// Register all converters
extern void registerOwnConverters();

#endif
