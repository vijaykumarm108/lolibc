/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
/*!
\file StdLib.cpp
\brief StdLib* code

This source code is protected by GNU GPL for non-commerical use.  For commercial use it is
restricted by license.

\author Jordan Stevens
\verbatim
$Author: jstevens $
$Copyright: $
$Rev: 472 $
$LastChangedDate: 2009-12-17 11:31:54 +0100 (Thu, 17 Dec 2009) $
$URL:  $
$License: $
\endverbatim
\ingroup Buffer
@{
*/
#include <stdafx.h>
#include <stdio.h>
#include <string.h>
#include <typeinfo>
//#pragma comment(lib,"msvcrt6.lib")


#if 0
void __cdecl operator delete( void * p )
{
	free( p );
}

void __cdecl operator delete[]( void * object )
{
	free( object );
}

void * __cdecl operator new(unsigned int count )
{
	return (void *)malloc( count );
}

void * __cdecl operator new[](unsigned int count )
{
	return (void *)malloc( count );
}
type_info::~type_info()
{
}
#endif

/*
* The purpose of defining these two dummy functions is to generate the
* type_info::'vftable' ["const type_info::`vftable'" (??_7type_info@@6B@)].
* This symbol is needed in our import lib, any class with virtual member
* functions compiled with /GR (which is on by default) will depends on this
* type_info::'vftable' symbol.
*
*/
type_info::type_info(const type_info& rhs)
{
}

type_info& type_info::operator=(const type_info& rhs)
{
	return *this;
}

#include <exception>

namespace std {

__declspec(noreturn) void __cdecl _Xinvalid_argument(_In_z_ const char *)
{
}

__declspec(noreturn) void __cdecl _Xlength_error(_In_z_ const char *)
{
}

__declspec(noreturn) void __cdecl _Xout_of_range(_In_z_ const char *)
{
}

__declspec(noreturn) void __cdecl _Xoverflow_error(_In_z_ const char *)
{
}

__declspec(noreturn) void __cdecl _Xruntime_error(_In_z_ const char *)
{
}

} // namespace std

/*! @} */
