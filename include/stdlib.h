
#pragma once
#include "lolibbase.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definition of the argument values for the exit() function */
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1


_CRTIMP size_t __cdecl		_msize( void *memblock );
_CRTIMP long int __cdecl	a64l (const char *string);
int	__cdecl					abs (int number);	// intrinsic
_CRTIMP void __cdecl		abort (void);
_CRTIMP long int atol ( const char * str );
int __cdecl					atexit(void (__cdecl *)(void));
_CRTIMP void * __cdecl		calloc(size_t nmemb, size_t size);
_CRTIMP void				exit (int status);
_CRTIMP void __cdecl		free(void *ptr);
_CRTIMP void * __cdecl		malloc(size_t size);
_CRTIMP int					rand (void);
_CRTIMP void * __cdecl		realloc(void *ptr, size_t size);
_CRTIMP void				srand (unsigned int seed);
_CRTIMP double __cdecl		strtod ( const char * str, char ** endptr );
_CRTIMP long int __cdecl	strtol ( const char * str, char ** endptr, int base );
int64_t	__cdecl				strtoll ( const char * str, char **tailptr, int base);

#ifdef __cplusplus
};
#endif

/* _countof helper */
#if !defined(_countof)
#if !defined(__cplusplus)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
template <typename _CountofType, size_t _SizeOfArray>
char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)
}
#endif
#endif
