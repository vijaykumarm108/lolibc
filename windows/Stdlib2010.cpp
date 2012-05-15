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
#include <typeinfo.h>
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

type_info& __CLR_OR_THIS_CALL type_info::operator=(const type_info& rhs)
{
	return *this;
}

#include <exception>

_STD_BEGIN

	
_EXCEPTION_INLINE __CLR_OR_THIS_CALL exception::exception()
    : _Mywhat(NULL), _Mydofree(false) { }

_EXCEPTION_INLINE __CLR_OR_THIS_CALL exception::exception(const char * const & _What)
    : _Mywhat(NULL), _Mydofree(false)
    {
    _Copy_str(_What);
    }

_EXCEPTION_INLINE __CLR_OR_THIS_CALL exception::exception(const char * const & _What, int)
    : _Mywhat(_What), _Mydofree(false) { }

_EXCEPTION_INLINE __CLR_OR_THIS_CALL exception::exception(const exception& _That)
    : _Mywhat(NULL), _Mydofree(false)
    {
    *this = _That;
    }

_EXCEPTION_INLINE exception& __CLR_OR_THIS_CALL exception::operator=(const exception& _That)
    {
    if (this != &_That)
        {
        _Tidy();

        if (_That._Mydofree)
            {
            _Copy_str(_That._Mywhat);
            }
        else
            {
            _Mywhat = _That._Mywhat;
            }
        }

    return *this;
    }

_EXCEPTION_INLINE __CLR_OR_THIS_CALL exception::~exception()
    {
    _Tidy();
    }

_EXCEPTION_INLINE const char * __CLR_OR_THIS_CALL exception::what() const
    {
    return _Mywhat ? _Mywhat : "Unknown exception";
    }

// _Copy_str() assumes that *this is already tidy.
_EXCEPTION_INLINE void __CLR_OR_THIS_CALL exception::_Copy_str(const char * _What)
    {
    if (_What != NULL)
        {
        const size_t _Buf_size = strlen(_What) + 1;
        
        _Mywhat = static_cast<char *>(malloc(_Buf_size));
        
        if (_Mywhat != NULL)
            {
            _CRT_SECURE_STRCPY(const_cast<char *>(_Mywhat), _Buf_size, _What);
            _Mydofree = true;
            }
        }
    }

_EXCEPTION_INLINE void __CLR_OR_THIS_CALL exception::_Tidy()
    {
    if (_Mydofree)
        {
        free(const_cast<char *>(_Mywhat));
        }

    _Mywhat = NULL;
    _Mydofree = false;
    }

_CRTIMP2_PURE __declspec(noreturn) void __CLRCALL_PURE_OR_CDECL _Xinvalid_argument(_In_z_ const char *)
{
}

_CRTIMP2_PURE __declspec(noreturn) void __CLRCALL_PURE_OR_CDECL _Xlength_error(_In_z_ const char *)
{
}

_CRTIMP2_PURE __declspec(noreturn) void __CLRCALL_PURE_OR_CDECL _Xout_of_range(_In_z_ const char *)
{
}

_CRTIMP2_PURE __declspec(noreturn) void __CLRCALL_PURE_OR_CDECL _Xoverflow_error(_In_z_ const char *)
{
}

_CRTIMP2_PURE __declspec(noreturn) void __CLRCALL_PURE_OR_CDECL _Xruntime_error(_In_z_ const char *)
{
}

_STD_END


/*! @} */
