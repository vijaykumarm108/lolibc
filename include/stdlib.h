
#pragma once
#include "lolibbase.h"

_CRTIMP void *malloc(size_t size);
_CRTIMP void free(void *ptr);
_CRTIMP void *realloc(void *ptr, size_t size);
_CRTIMP void *calloc(size_t nmemb, size_t size);
_CRTIMP double strtod ( const char * str, char ** endptr );
_CRTIMP long int strtol ( const char * str, char ** endptr, int base );

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
