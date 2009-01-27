// High-level GUI wrapper for Xmmm.

// Copyright (C) 2007 Peter Wainwright <prw@ceiriog.eclipse.co.uk>
// 
// This file is part of Xmmm.
// 
// Xmmm is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// 
// Xmmm is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with Xmmm -- see the file COPYING.
// If not, see <http://www.gnu.org/licenses/>.

// High level object-oriented wrapper must support Gtk and Motif.
// Unfortunately Motif widgets require parent and name arguments to
// the constructor, unlike the Gtk ones.  Motif (Xt) widgets cannot be
// reparented.  Therefore we need a constructor with extra arguments.

#include <Xm/TextF.h>

#include <Xmmm/Entry.h>

using namespace Xmmm;

void
Entry::init_signals(void)
{
}

Entry::Entry(::Widget parent, const Xmmm::String &name)
{
    entry_ = XmCreateTextField(parent, (char *)name.c(), NULL, 0);
    init_signals();
    postinit();
}

Entry::Entry(Xmmm::Container &parent, const Xmmm::String &name)
{
    entry_ = XmCreateTextField(parent.xt_container(), (char *)name.c(), NULL, 0);
    init_signals();
    postinit();
}

Entry::~Entry(void)
{
    XtDestroyWidget(entry_);
}

::Widget Entry::internal(void)
{
    return entry_;
}

sigc::signal<void> &
Entry::signal_activate(void)
{
    return signal_activate_;
}

Xmmm::String
Entry::get_text(void)
{
    return XmTextFieldGetString(entry_);
}
