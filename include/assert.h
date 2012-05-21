#pragma once
#include "lolibbase.h"

#undef  assert

#ifdef NDEBUG

#define assert(_Expression)     ((void)0)

#else  /* NDEBUG */

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

_CRTIMP void __cdecl _assert(const char *, const char *, unsigned int);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#define assert(_expr) (void)((!!(_expr)) || (_assert(#_expr, __FILE__, __LINE__), 0))

#endif  /* NDEBUG */
