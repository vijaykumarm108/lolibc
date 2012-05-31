/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
/*!
\file StdLib.c
\brief Helper functions to facilitate glibc calls into MSVCRT calls.
\author Jordan Stevens
\verbatim
$Author: jstevens $
$Rev: 413 $
$LastChangedDate: 2009-06-24 03:49:34 -0500 (Wed, 24 Jun 2009) $
$URL:  $
\endverbatim
\ingroup StdLib
@{
*/
#ifdef MRTDLL
#undef MRTDLL
#endif  /* MRTDLL */

#undef _CRTIMP
//#define  _DLL

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#define _TICORE
//#include <typeinfo.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


#define _CRT_SECURE_NO_WARNINGS
#include <errno.h>
#include <float.h>
#include <time.h>
#include <windows.h>
//#include <time.h>

#pragma comment(linker, "/defaultlib:kernel32.lib")
#pragma comment(linker, "/disallowlib:libc.lib")
#pragma comment(linker, "/disallowlib:libcd.lib")
#pragma comment(linker, "/disallowlib:libcmt.lib")
#pragma comment(linker, "/disallowlib:libcmtd.lib")
//#ifdef _DEBUG
#pragma comment(linker, "/disallowlib:msvcrt.lib")
//#else  /* _DEBUG */
#pragma comment(linker, "/disallowlib:msvcrtd.lib")
//#endif  /* _DEBUG */



#ifndef _TM_DEFINED
	struct tm {
		int tm_sec;     /* seconds after the minute - [0,59] */
		int tm_min;     /* minutes after the hour - [0,59] */
		int tm_hour;    /* hours since midnight - [0,23] */
		int tm_mday;    /* day of the month - [1,31] */
		int tm_mon;     /* months since January - [0,11] */
		int tm_year;    /* years since 1900 */
		int tm_wday;    /* days since Sunday - [0,6] */
		int tm_yday;    /* days since January 1 - [0,365] */
		int tm_isdst;   /* daylight savings time flag */
	};
#define _TM_DEFINED
#endif

HINSTANCE ghInstance;

extern UINT_PTR __security_cookie;

#pragma warning(disable:4273)
_CRTIMP struct tm * __cdecl _localtime64( const __time64_t * _Time);
errno_t __cdecl _localtime64_s( struct tm* _tm,	const __time64_t *time );

errno_t __cdecl _localtime64_s( struct tm * _tm, const __time64_t *time )
{
	errno_t retval = EINVAL;
	if( _tm && time && (time < 0) )
	{
		struct tm *tm2 = _localtime64( time );
		if( tm2 )
		{
			*_tm = *tm2;
			retval = 0;
		}
	}
	return retval;
}

extern __int64 _ftol( float f );
__int64 __cdecl _ftol2( float f )
{
	return (__int64)_ftol(f);
}

void *_recalloc( void *block, size_t num, size_t size )
{
	return realloc( block, num*size );
}

#ifdef _M_IX86
#define NAKED __declspec(naked)
#else
#define NAKED
#endif

void NAKED __fastcall __security_check_cookie(UINT_PTR cookie)
{
#ifdef _M_IX86
	/* x86 version written in asm to preserve all regs */
	__asm {
		cmp ecx, __security_cookie
		jne failure
		rep ret /* REP to avoid AMD branch prediction penalty */
failure:
		ret
		//jmp __report_gsfailure
	}
#endif
}


errno_t memcpy_s( void *dest, size_t numberOfElements, const void *src, size_t count )
{
	if( (dest == NULL) || (src == NULL) )
		return EINVAL;
	if( numberOfElements < count )
		return ERANGE;
	memcpy( dest, src, count );
	return 0;

}

_CRTIMP void *  __cdecl _memmove(_Out_opt_bytecapcount_(_Size) void * _Dst, _In_opt_bytecount_(_Size) const void * _Src,  size_t _Size);

errno_t memmove_s( void *dest, size_t numberOfElements, const void *src, size_t count )
{
	if( (dest == NULL) || (src == NULL) )
		return EINVAL;
	if( numberOfElements < count )
		return ERANGE;
	_memmove( dest, src, count );
	return 0;
}

void __cdecl _invalid_parameter( const wchar_t *pszExpression, const wchar_t *pszFunction, const wchar_t *pszFile,
								unsigned int nLine,	uintptr_t pReserved )
{
}
void __cdecl _invalid_parameter_noinfo()
{

}

_CRTIMP wchar_t * __cdecl wcsrchr(_In_z_ const wchar_t * str,  wchar_t ch)
{
	wchar_t *start = (wchar_t *)str;
	while (*str++)                       /* find end of string */
		;
	/* search towards front */
	while (--str != start && *str != (wchar_t)ch);
	if (*str == (wchar_t)ch)             /* wchar_t found ? */
		return (wchar_t * )str;
	return NULL;
}

errno_t _controlfp_s( unsigned int *currentControl, unsigned int newControl, unsigned int mask )
{
	if( currentControl )
		*currentControl = _statusfp();
	_controlfp( newControl, mask );
	return 0;
}

errno_t _wfopen_s( FILE** pFile, const wchar_t *filename, const wchar_t *mode )
{
	_CRTIMP	FILE *_wfopen( const wchar_t *filename, const wchar_t *mode );
	if( !pFile || !filename || !mode )
		return EINVAL;
	*pFile = _wfopen( filename, mode );
	return 0;
}

errno_t fopen_s( FILE** pFile, const char *filename, const char *mode )
{
	if( !pFile || !filename || !mode )
		return EINVAL;
	*pFile = fopen( filename, mode );
	return 0;
}

errno_t _gmtime64_s( struct tm* _tm, const __time64_t* time )
{
	_CRTIMP struct tm *_gmtime64( const __time64_t *timer );
	if( !_tm || !time || (*time < 0) )
		return EINVAL;
	*_tm = *_gmtime64( time );
	return 0;
}

int _stat64i32( const char *path, struct _stat64i32 *buffer )
{
	_CRTIMP int _stat64( const char *path, struct __stat64 *buffer );
	int	iRetVal;
	struct _stat64 s64;
	if( (iRetVal = _stat64( path, &s64 )) == 0 )
	{
		buffer->st_dev = s64.st_dev;
		buffer->st_ino = s64.st_ino;
		buffer->st_mode = s64.st_mode;
		buffer->st_nlink = s64.st_nlink;
		buffer->st_uid = s64.st_uid;
		buffer->st_gid = s64.st_gid;
		buffer->st_rdev = s64.st_rdev;
		buffer->st_size = (_off_t)s64.st_size;
		buffer->st_atime = s64.st_atime;
		buffer->st_mtime = s64.st_mtime;
		buffer->st_ctime = s64.st_ctime;
	}
	return iRetVal;
}

int _wstat64i32( const wchar_t *path, struct _stat64i32 *buffer )
{
	_CRTIMP int _wstat64( const wchar_t *path, struct __stat64 *buffer );
	int	iRetVal;
	struct _stat64 s64;
	if( (iRetVal = _wstat64( path, &s64 )) == 0 )
	{
		buffer->st_dev = s64.st_dev;
		buffer->st_ino = s64.st_ino;
		buffer->st_mode = s64.st_mode;
		buffer->st_nlink = s64.st_nlink;
		buffer->st_uid = s64.st_uid;
		buffer->st_gid = s64.st_gid;
		buffer->st_rdev = s64.st_rdev;
		buffer->st_size = (_off_t)s64.st_size;
		buffer->st_atime = s64.st_atime;
		buffer->st_mtime = s64.st_mtime;
		buffer->st_ctime = s64.st_ctime;
	}
	return iRetVal;
}

errno_t _wdupenv_s( wchar_t **buffer, size_t *numberOfElements, const wchar_t *varname )
{
	_CRTIMP wchar_t *_wgetenv( const wchar_t *varname );
	wchar_t	*temp;
	if( !buffer || !numberOfElements || !varname )
		return EINVAL;
	if( temp = _wgetenv(varname) )
	{
		if( (*buffer = _wcsdup(temp)) == NULL )
			return ENOMEM;
		*numberOfElements = wcslen(*buffer); 
	}
	else
		*numberOfElements = 0;
	return 0;
}

int vswprintf_s( wchar_t *buffer, size_t numberOfElements, const wchar_t *format, va_list argptr )
{
	_CRTIMP int _vsnwprintf( wchar_t *buffer, size_t count, const wchar_t *format, va_list argptr );
	if( !buffer || (numberOfElements <= 0) || !format )
	{
		errno = EINVAL;
		return -1;
	}
	return _vsnwprintf( buffer, numberOfElements, format, argptr );
}

int vsprintf_s( char *buffer, size_t numberOfElements, const char *format, va_list argptr )
{
	_CRTIMP int _vsnprintf(	char *buffer, size_t count,	const char *format,	va_list argptr );
	if( !buffer || (numberOfElements <= 0) || !format )
	{
		errno = EINVAL;
		return -1;
	}
	return _vsnprintf( buffer, numberOfElements, format, argptr );
}

int swprintf_s( wchar_t *buffer, size_t sizeOfBuffer, const wchar_t *format, ... )
{
	va_list	start;
	va_start(start,format);
	return vswprintf_s( buffer, sizeOfBuffer, format, start );
}

int sprintf_s(  char *buffer, size_t sizeOfBuffer, const char *format, ... )
{
	va_list	start;
	va_start(start,format);
	return vsprintf_s( buffer, sizeOfBuffer, format, start );
}

errno_t strcpy_s( char *strDestination, size_t numberOfElements, const char *strSource )
{
	if( ((NULL == strDestination) || (NULL == strSource) || (0 == numberOfElements)) )
	{
		return EINVAL;
	}
	strncpy(strDestination,strSource,numberOfElements);
	return 0;
}

errno_t wcsncpy_s( wchar_t *strDest, size_t numberOfElements, const wchar_t *strSource, size_t count )
{
	if( ((NULL == strDest) || (NULL == strSource) || (0 == numberOfElements)) )
	{
		return EINVAL;
	}
	wcsncpy(strDest, strSource, min(numberOfElements,count) );
	return 0;
}

errno_t wcscpy_s( wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource )
{
	return wcsncpy_s( strDestination, numberOfElements, strSource, numberOfElements );
}

errno_t wcscat_s( wchar_t *strDestination, size_t numberOfElements, const wchar_t *strSource )
{
	size_t i;
	if( !strDestination || !strSource )
	{
		return EINVAL;
	}
	for( i = 0; (i < numberOfElements) && ('\0' != *strDestination); ++i, ++strDestination )
	{
		;
	}
	return wcscpy_s( strDestination, numberOfElements - i, strSource );
}

void * _memmove( void* dest, const void* src, size_t count )
{
	return memmove( dest, src, count );
}

size_t wcsnlen( const wchar_t *str, size_t numberOfElements )
{
	size_t	returnValue = 0;
	if( NULL != str )
	{
		for( ; *str && (numberOfElements > returnValue); ++str )
		{
			++returnValue;
		}
	}
	return returnValue;
}

int __cdecl _snwprintf_s ( wchar_t *string, size_t sizeInWords, size_t count, const wchar_t *format, ...  )
{
    va_list arglist;

    va_start(arglist, format);
 
	return _vsnwprintf( string, min(sizeInWords,count), format, arglist );
}

int __cdecl _snprintf_s ( char *string, size_t sizeInWords, size_t count, const char *format, ...  )
{
    va_list arglist;

    va_start(arglist, format);
 
	return _vsnprintf( string, min(sizeInWords,count), format, arglist );
}

errno_t strcat_s( char *strDestination, size_t numberOfElements, const char *strSource )
{
	if ((NULL == strDestination ) || (NULL == strSource))
		return EINVAL;
	if ((strlen(strDestination) + strlen(strSource) + 1) > numberOfElements)
		return ERANGE;
	strcpy( strDestination, strSource );
	return 0;
}

size_t wcstombs( char *mbstr, const wchar_t *wcstr, size_t count )
{
	return WideCharToMultiByte( CP_THREAD_ACP, 0, wcstr, -1, mbstr, (int)count, NULL, NULL );
}

errno_t __cdecl wcstombs_s ( size_t *pConvertedChars, char * dst, size_t sizeInBytes, const wchar_t * src, size_t n )
{
	int vI;

	if ( (NULL==src) || ((NULL==dst) && (sizeInBytes>0)) )
		return EINVAL;
	vI = WideCharToMultiByte( CP_THREAD_ACP, 0, src, (int)n, dst, (int)sizeInBytes, NULL, NULL );
	if ( (vI < 0) || (vI > (int)sizeInBytes) )
		return ERANGE;
	WideCharToMultiByte( CP_THREAD_ACP, 0, src, (int)n, dst, (int)sizeInBytes, NULL, NULL );
	return 0;
}

errno_t _itoa_s( int value, char *buffer, size_t sizeInCharacters, int radix )
{
	_CRTIMP char *_itoa( int value,	char *str, int radix );
	char temp[34];
	if ( (NULL==buffer) || (sizeInCharacters<=1) || (radix<2) || (radix>36) )
		return EINVAL;
	_itoa( value, temp, radix );
	if( sizeInCharacters <= strlen(temp) )
		return EINVAL;
	strcpy( buffer, temp);
	return 0;
}


errno_t _itow_s( int value, wchar_t *buffer, size_t sizeInCharacters, int radix )
{
	_CRTIMP wchar_t * _itow( int value, wchar_t *str, int radix );
	wchar_t temp[34];
	if ( (NULL==buffer) || (sizeInCharacters<=1) || (radix<2) || (radix>36) )
		return EINVAL;
	_itow( value, temp, radix );
	if( sizeInCharacters <= wcslen(temp) )
		return EINVAL;
	wcscpy( buffer, temp);
	return 0;
}

__int64 _strtoi64( const char *nptr, char **endptr, int base )
{
	__int64	retval = 0;
	char start = *nptr;
	int digit;

	if ((base < 2) || (base >36) || (nptr == NULL ) )
	{
		errno = EINVAL;
		return 0;
	}

	if ( start == '-' )	++nptr;
	for ( digit = 0; *nptr != 0 ; ++nptr )
	{
		if (*nptr >= '0' && *nptr <= '9')	digit = *nptr - '0';
		else if (*nptr >= 'A' && *nptr <= 'Z')	digit = *nptr - 'A' + 10;
		else if (*nptr >= 'a' && *nptr <= 'z')	digit = *nptr - 'a' + 10;
		else break;
		if (digit < 0 || digit >= base )	break;
		retval *= base;
		retval += digit;
	}

	if (endptr != NULL )	*endptr = (char *)nptr;
	return retval*((start == '-' ? -1 : 1));
}

#include <wchar.h>

wchar_t *wcsncpy( wchar_t *strDest, const wchar_t *strSource, size_t count )
{
	return lstrcpynW( strDest, strSource, (int)count );
}

void Utf8ToUtf16( const char *input, wchar_t *output, int maxLength )
{
	MultiByteToWideChar( CP_UTF8, 0, input, -1, output, maxLength );
}

void Utf16ToUtf8( const wchar_t *input, char *output, int maxLength )
{
	WideCharToMultiByte( CP_UTF8, 0, input, -1, output, maxLength, NULL, NULL );
}

// Utf-8 version of fopen
FILE * fopen ( const char * fileName, const char * mode )
{
	wchar_t	path[512];
	wchar_t wmode[20];
	Utf8ToUtf16( fileName, path, _countof(path));
	Utf8ToUtf16( mode, wmode, _countof(wmode));
	return _wfopen( path, wmode ); 
}

// Utf-8 version of fopen
FILE * __cdecl freopen ( const char * fileName, const char * mode, FILE *stream )
{
	_CRTIMP FILE *_wfreopen( const wchar_t *path, const wchar_t *mode, FILE *stream );
	wchar_t	path[512];
	wchar_t wmode[20];
	Utf8ToUtf16( fileName, path, _countof(path));
	Utf8ToUtf16(mode,wmode, _countof(wmode));
	return _wfreopen( path, wmode, stream ); 
}

/// Deletes the UTF-8 file designated by the path \p fileName
int remove( const char *fileName )
{
	_CRTIMP int _wremove( const wchar_t *path );
	wchar_t	path[512];
	Utf8ToUtf16( fileName, path, _countof(path));
	return _wremove(path);
}

/// Makes the UTF-8 \p path the current directory
int chdir(const char *path)
{
	_CRTIMP int _wchdir(const wchar_t *path);
	wchar_t	wpath[512];
	Utf8ToUtf16( path, wpath, _countof(wpath));
	return _wchdir(wpath);
}

/// Gets the current working directory as a utf8 \p path
char * getcwd( char * path, int lengthOfPath )
{
	wchar_t * __cdecl _wgetcwd( wchar_t * wpath, int sizeInWords );
	wchar_t	wpath[512];
	_wgetcwd(wpath,_countof(wpath));
	Utf16ToUtf8( wpath, path, lengthOfPath );
	return path;
}

/// makes the directory from the utf-8 \p filename with the \b security mode
int mkdir (const char *path, unsigned mode)
{
	_CRTIMP int _wmkdir(const wchar_t *dirname  );
	wchar_t	wpath[512];
	Utf8ToUtf16( path, wpath, _countof(wpath));
	return _wmkdir(wpath);
}

/// Sets the file modification time for the UTF-8 \p filename
int utime (const char *filename, const struct utimbuf *times)
{
	_CRTIMP int _wutime( const wchar_t *filename, const struct utimbuf *times );
	wchar_t wpath[512];
	Utf8ToUtf16( filename, wpath, _countof(wpath));
	return _wutime(wpath,times);
}

__int64 ftello64(FILE *stream)
{
	_CRTIMP __int64 _telli64( int handle );
	return _telli64( stream->_file);
}

__int64 fseeko64 (FILE *stream, __int64 offset, int whence)
{
	_CRTIMP __int64 _lseeki64( int fd, __int64 offset, int origin );
	return _lseeki64(stream->_file, offset, whence );
}

/// UTF-8 version of access
int access (const char *filename, int how)
{
	_CRTIMP int _waccess( const wchar_t *path, int mode );
	wchar_t wpath[512];
	Utf8ToUtf16( filename, wpath, _countof(wpath));
	return _waccess( wpath, how );
}

/// Utf-8 version of stat
int stat (const char *filename, struct stat *buf)
{
	_CRTIMP int _wstat(	const wchar_t *path, struct stat *buffer );
	wchar_t wpath[512];
	Utf8ToUtf16( filename, wpath, _countof(wpath));
	return _wstat(wpath,buf);
}

// Debug requirement
void _CRT_RTC_INITW()
{

}


/*! @} */
