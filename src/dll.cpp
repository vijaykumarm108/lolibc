/*
The Lolibc project.
Copyright (C) 2012  Jordan C. Stevens

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library;
If not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <stdafx.h>
#include <dll.h>
#include <dll/kernel32.h>

namespace lo
{
	void dll::_addref()
	{
		if(counter()++ == 0)
			m_handle = LoadLibraryA(Name());
	}

	void dll::_release()
	{
		if(--counter() == 0)
		{
			::FreeLibrary(m_handle);
			m_handle = 0;
		}
	}
}

/** (c) Copyright 2012 - Jordan C. Stevens, All Rights reserved. */
