/* stdarg.h -- C standard says this is deprecated and instead should use cstdarg, which just includes this. */

#pragma once

#ifndef _INC_STDARG
#define _INC_STDARG

#include "lolibbase.h"

/* Currently, all MS C compilers for Win32 platforms default to 8 byte alignment. */
#ifdef _WIN32
#undef _CRT_PACKING
#define _CRT_PACKING 8
#pragma pack(push,_CRT_PACKING)
#endif

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef _UINTPTR_T_DEFINED
#ifdef _WIN64
typedef unsigned __int64    uintptr_t;
#else  /* _WIN64 */
typedef _W64 unsigned int   uintptr_t;
#endif  /* _WIN64 */
#define _UINTPTR_T_DEFINED
#endif  /* _UINTPTR_T_DEFINED */

#ifndef _VA_LIST_DEFINED
#ifdef _M_CEE_PURE
typedef System::ArgIterator va_list;
#else  /* _M_CEE_PURE */
typedef char *  va_list;
#endif  /* _M_CEE_PURE */
#define _VA_LIST_DEFINED
#endif  /* _VA_LIST_DEFINED */

#ifdef __cplusplus
#define _ADDRESSOF(v)   ( &reinterpret_cast<const char &>(v) )
#else  /* __cplusplus */
#define _ADDRESSOF(v)   ( &(v) )
#endif  /* __cplusplus */

#if defined (_M_IA64) && !defined (_M_CEE_PURE)
#define _VA_ALIGN       8
#define _SLOTSIZEOF(t)   ( (sizeof(t) + _VA_ALIGN - 1) & ~(_VA_ALIGN - 1) )

#define _VA_STRUCT_ALIGN  16

#define _ALIGNOF(ap) ((((ap)+_VA_STRUCT_ALIGN - 1) & ~(_VA_STRUCT_ALIGN -1)) \
        - (ap))
#define _APALIGN(t,ap)  (__alignof(t) > 8 ? _ALIGNOF((uintptr_t) ap) : 0)

#else  /* defined (_M_IA64) && !defined (_M_CEE_PURE) */
#define _SLOTSIZEOF(t)   (sizeof(t))
#define _APALIGN(t,ap)  (__alignof(t))
#endif  /* defined (_M_IA64) && !defined (_M_CEE_PURE) */

#if defined (_M_CEE)

extern void __cdecl __va_start(va_list*, ...);
extern void * __cdecl __va_arg(va_list*, ...);
extern void __cdecl __va_end(va_list*);

#define _crt_va_start(ap,v)  ( __va_start(&ap, _ADDRESSOF(v), _SLOTSIZEOF(v), __alignof(v), _ADDRESSOF(v)) )
#define _crt_va_arg(ap,t)    ( *(t *)__va_arg(&ap, _SLOTSIZEOF(t), _APALIGN(t,ap), (t *)0) )
#define _crt_va_end(ap)      ( __va_end(&ap) )

#elif defined (_M_IX86)

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define _crt_va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define _crt_va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _crt_va_end(ap)      ( ap = (va_list)0 )

#elif defined (_M_IA64)

#ifdef __cplusplus
extern void __cdecl __va_start(va_list*, ...);
#define _crt_va_start(ap,v)  ( __va_start(&ap, _ADDRESSOF(v), _SLOTSIZEOF(v), _ADDRESSOF(v)) )
#else  /* __cplusplus */
#define _crt_va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _SLOTSIZEOF(v) )
#endif  /* __cplusplus */

#define _crt_va_arg(ap,t)    (*(t *)((ap += _SLOTSIZEOF(t)+ _APALIGN(t,ap)) - _SLOTSIZEOF(t)))
#define _crt_va_end(ap)      ( ap = (va_list)0 )

#elif defined (_M_AMD64)

extern void __cdecl __va_start(va_list *, ...);

#define _crt_va_start(ap, x) ( __va_start(&ap, x) )
#define _crt_va_arg(ap, t)   \
    ( ( sizeof(t) > sizeof(__int64) || ( sizeof(t) & (sizeof(t) - 1) ) != 0 ) \
        ? **(t **)( ( ap += sizeof(__int64) ) - sizeof(__int64) ) \
        :  *(t  *)( ( ap += sizeof(__int64) ) - sizeof(__int64) ) )
#define _crt_va_end(ap)      ( ap = (va_list)0 )

#else  /* defined (_M_AMD64) */

/* A guess at the proper definitions for other platforms */

#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define _crt_va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define _crt_va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _crt_va_end(ap)      ( ap = (va_list)0 )

#endif  /* defined (_M_AMD64) */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#pragma pack(pop)

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
};
#endif

#endif  /* _INC_VADEFS */
