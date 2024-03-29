/*!
\file string.h lolibc
*/
#if     _MSC_VER > 1000
#pragma once
#endif
#ifndef _INC_STRING
#define _INC_STRING
#include "lolibbase.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* Define __cdecl for non-Microsoft compilers */
#if ( !defined(_MSC_VER) && !defined(__cdecl) )
#define __cdecl
#endif

/* Define _CRTAPI1 (for compatibility with the NT SDK) */
#ifndef _CRTAPI1
#if	_MSC_VER >= 800 && _M_IX86 >= 300
#define _CRTAPI1 __cdecl
#else
#define _CRTAPI1
#endif
#endif

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

#ifndef _MAC
#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif
#endif  /* ndef _MAC */

#ifndef _NLSCMP_DEFINED
#define _NLSCMPERROR    2147483647  /* currently == INT_MAX */
#define _NLSCMP_DEFINED
#endif

/* Define NULL pointer value */

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/* Function prototypes  - Those without _CRTIMP can be intrinsic. */

	char * __cdecl				basename (const char *filename);
	_CRTIMP void *  __cdecl		_memccpy(void *, const void *, int, unsigned int);
	_CRTIMP int     __cdecl		_memicmp(const void *, const void *, unsigned int);
	char *  __cdecl				_strset(char *, int);
	_CRTIMP void * __cdecl		memccpy(void *, const void *, int, unsigned int);
	int     __cdecl				memcmp(const void *, const void *, size_t);
	void *  __cdecl				memcpy(void *, const void *, size_t);
	__inline wchar_t *			wmemcpy (wchar_t *wto, const wchar_t *wfrom, size_t size)
	{
		return (wchar_t *) memcpy (wto, wfrom, size * sizeof (wchar_t));
	}
	_CRTIMP int __cdecl			memicmp(const void *, const void *, unsigned int);
	void *	__cdecl				memfrob (void *mem, size_t length);
	void *  __cdecl				memset(void *, int, size_t);
	char *  __cdecl				strcpy(char *, const char *);
	char *  __cdecl				strcat(char *, const char *);
	int     __cdecl				strcmp(const char *, const char *);
	size_t  __cdecl				strlen(const char *);             
	_CRTIMP const void *  __cdecl	memchr(const void *, int, size_t);
	_CRTIMP void *  __cdecl		memmove(void *, const void *, size_t);
	_CRTIMP char *  __cdecl		strchr(const char *, int);
	_CRTIMP int     __cdecl		_strcmpi(const char *, const char *);
	_CRTIMP char				*strerror( int errnum );
	_CRTIMP int     __cdecl		_stricmp(const char *, const char *);
	_CRTIMP int     __cdecl		strcoll(const char *, const char *);
	_CRTIMP int     __cdecl		_stricoll(const char *, const char *);
	_CRTIMP int     __cdecl		_strncoll(const char *, const char *, size_t);
	_CRTIMP int     __cdecl		_strnicoll(const char *, const char *, size_t);
	_CRTIMP size_t  __cdecl		strcspn(const char *, const char *);
	_CRTIMP char *  __cdecl		_strdup(const char *);
	__inline char * __cdecl		strdup(const char *str)
	{
		return _strdup(str);
	}
	_CRTIMP char *  __cdecl		_strerror(const char *);
	_CRTIMP char *  __cdecl		strerror(int);
	_CRTIMP char *  __cdecl		_strlwr(char *);
	_CRTIMP char *  __cdecl		strncat(char *, const char *, size_t);
	_CRTIMP int     __cdecl		strncmp(const char *, const char *, size_t);
	_CRTIMP int     __cdecl		_strnicmp(const char *, const char *, size_t);
	_CRTIMP char *  __cdecl		strncpy(char *, const char *, size_t);
	_CRTIMP char *  __cdecl		_strnset(char *, int, size_t);
	_CRTIMP char *  __cdecl		strpbrk(const char *, const char *);
	_CRTIMP char *  __cdecl		strrchr(const char *, int);
	_CRTIMP char *  __cdecl		_strrev(char *);
	_CRTIMP size_t  __cdecl		strspn(const char *, const char *);
	_CRTIMP char *  __cdecl		strstr(const char *, const char *);
	_CRTIMP char *  __cdecl		strtok(char *, const char *);
	_CRTIMP char *  __cdecl		_strupr(char *);
	_CRTIMP size_t  __cdecl		strxfrm (char *, const char *, size_t);
	_CRTIMP int		__cdecl		strcmpi(const char *, const char *);
	__inline int	__cdecl		stricmp(const char *str1, const char *str2)
	{
		return _stricmp(str1,str2);
	}
	_CRTIMP char * __cdecl		strlwr(char *);
	_CRTIMP int __cdecl			strnicmp(const char *, const char *, size_t);
	_CRTIMP char * __cdecl		strnset(char *, int, size_t);
	_CRTIMP char * __cdecl		strrev(char *);
	char * __cdecl		strset(char *, int);
	_CRTIMP char * __cdecl		strupr(char *);

/* wide function prototypes, also declared in wchar.h  */
#ifndef _WSTRING_DEFINED

wchar_t * __cdecl			wcscat(wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl	wcschr(const wchar_t *, wchar_t);
int __cdecl					wcscmp(const wchar_t *, const wchar_t *);
wchar_t * __cdecl			wcscpy(wchar_t *, const wchar_t *);
errno_t						wcscpy_s( wchar_t *strDestination, size_t numberOfElements,	const wchar_t *strSource  ); // C++ only
_CRTIMP size_t __cdecl		wcscspn(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl	wcsdup(const wchar_t *);
size_t __cdecl				wcslen(const wchar_t *);
size_t __cdecl				wcsnlen(const wchar_t *,size_t);
wchar_t * __cdecl			wcsncat(wchar_t *, const wchar_t *, size_t);
_CRTIMP int __cdecl			wcsncmp(const wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl	wcsncpy(wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl	wcspbrk(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl	wcsrchr(const wchar_t *, wchar_t);
_CRTIMP size_t __cdecl		wcsspn(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl	wcsstr(const wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl	wcstok(wchar_t *, const wchar_t *);
_CRTIMP wchar_t * __cdecl	_wcsdup(const wchar_t *);
_CRTIMP int __cdecl			_wcsicmp(const wchar_t *, const wchar_t *);
_CRTIMP int __cdecl			_wcsnicmp(const wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl	_wcsnset(wchar_t *, wchar_t, size_t);
_CRTIMP wchar_t * __cdecl	_wcsrev(wchar_t *);
wchar_t * __cdecl			_wcsset(wchar_t *, wchar_t);
_CRTIMP wchar_t * __cdecl	_wcslwr(wchar_t *);
_CRTIMP wchar_t * __cdecl	_wcsupr(wchar_t *);
_CRTIMP size_t __cdecl		wcsxfrm(wchar_t *, const wchar_t *, size_t);
_CRTIMP int __cdecl			wcscoll(const wchar_t *, const wchar_t *);
_CRTIMP int __cdecl			_wcsicoll(const wchar_t *, const wchar_t *);
_CRTIMP int __cdecl			_wcsncoll(const wchar_t *, const wchar_t *, size_t);
_CRTIMP int __cdecl			_wcsnicoll(const wchar_t *, const wchar_t *, size_t);
static	wchar_t * __cdecl	wcswcs(const wchar_t *s1, const wchar_t *s2)	{ return wcsstr(s1,s2); }
_CRTIMP int __cdecl			wcsicmp(const wchar_t *, const wchar_t *);
_CRTIMP int __cdecl			wcsnicmp(const wchar_t *, const wchar_t *, size_t);
_CRTIMP wchar_t * __cdecl	wcsnset(wchar_t *, wchar_t, size_t);
_CRTIMP wchar_t * __cdecl	wcsrev(wchar_t *);
_CRTIMP wchar_t * __cdecl	wcsset(wchar_t *, wchar_t);
_CRTIMP wchar_t * __cdecl	wcslwr(wchar_t *);
_CRTIMP wchar_t * __cdecl	wcsupr(wchar_t *);
_CRTIMP int __cdecl			wcsicoll(const wchar_t *, const wchar_t *);

#define _WSTRING_DEFINED
#endif

#ifdef  __cplusplus
}
#endif

#endif  /* _INC_STRING */
