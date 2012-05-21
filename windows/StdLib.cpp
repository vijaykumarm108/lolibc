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
#define _CRT_SECURE_NO_WARNINGS
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

exception::exception()
: _m_what(NULL), _m_doFree(0)
{ }
exception::exception(const char *const& _What)
{
	if (_What != NULL)
	{
		size_t _Buf_size = strlen( _What ) + 1;
#pragma warning(push)
#pragma warning(disable:4996)
		_m_what = static_cast< char * >( (char *)malloc( _Buf_size ) );
#pragma warning(pop)
		if ( _m_what != NULL )
		{
			strncpy( const_cast<char *>(_m_what), _What, _Buf_size );
		}
	}
	else
	{
		_m_what = NULL;
	}
	_m_doFree = 1;
}
exception::exception(const char *const& _What, int)
{
	_m_what = _What;
	_m_doFree = 0;
}
exception::exception(const exception& _That)
{
	_m_doFree = _That._m_doFree;
	if (_m_doFree)
	{
		if (_That._m_what != NULL)
		{
			size_t _Buf_size = strlen( _That._m_what ) + 1;
#pragma warning(push)
#pragma warning(disable:4996)
			_m_what = static_cast< char * >( (char *)malloc( _Buf_size ) );
#pragma warning(pop)
			if (_m_what != NULL)                {
				strncpy( const_cast<char *>(_m_what), _That._m_what, _Buf_size );
			}
		}
		else
		{
			_m_what = NULL;
		}
	}
	else
		_m_what = _That._m_what;
}
exception& exception::operator=(const exception& _That)
{
	if (this != &_That)
	{
		_m_doFree = _That._m_doFree;
		if (_m_doFree)
		{
			if (_That._m_what != NULL)
			{
				size_t _Buf_size = strlen( _That._m_what ) + 1;
#pragma warning(push)
#pragma warning(disable:4996)
				_m_what = static_cast< char * >( (char *)malloc( _Buf_size ) );
#pragma warning(pop)
				if( _m_what != NULL )
				{
					strncpy( const_cast<char *>(_m_what), _That._m_what, _Buf_size );
				}
			}
			else
			{
				_m_what = NULL;
			}
		}
		else
			_m_what = _That._m_what;
	}
	return *this;
}
exception::~exception()
{
	if (_m_doFree)
#pragma warning(push)
#pragma warning(disable:4996)
		free( const_cast< char * >( _m_what ) );
#pragma warning(pop)
}
const char* exception::what() const
{
	if ( _m_what != NULL )
		return _m_what;
	else
		return "Unknown exception";
}

_STD_END


/*! @} */
