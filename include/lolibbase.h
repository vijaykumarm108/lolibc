/*
 lolibbase.h - Base set of definitions for lolib's C functions.  This file is included before any of the STDC headers.
*/
#pragma once
#ifndef _INC_LOLIBBASE_
#define _INC_LOLIBBASE_

#define _INC_CRTDEFS
#define _INC_IO
#define _INC_MBSTRING

// Static analysis tool helpers
//#define _In_
//#define _Out_opt_
//#define _Out_
//#define _In_opt_
//#define _Inout_
//#define _In_z_
//#define _In_opt_z_
#include <sal.h>

#if defined(_PREFAST_) && defined(_CA_SHOULD_CHECK_RETURN)
#define _Check_return_opt_ _Check_return_
#else
#define _Check_return_opt_
#endif

/* WIN32 - Lets you mark variables, such that when you compile with /Wp64 the compiler will report any warnings
that would be reported if you were compiling with a 64-bit compiler. */
#if !defined (_W64)
#if !defined (__midl) && (defined (_X86_) || defined (_M_IX86))
#define _W64 __w64
#else  /* !defined (__midl) && (defined (_X86_) || defined (_M_IX86)) */
#define _W64
#endif  /* !defined (__midl) && (defined (_X86_) || defined (_M_IX86)) */
#endif  /* !defined (_W64) */

#ifdef __linux // __clang__
#ifdef __APPLE__
#error APPLE & LINUX not yet supported
#endif // __APPLE__
#ifndef __clang__
#error Only Clang supported under linux
#endif // __clang__
#elif defined(_WIN32)
#define STDC_HEADERS
#define HAVE_STDINT_H 1
#define __attribute__(x)
#define __alignof__(x) __alignof(x)
typedef unsigned mode_t;
typedef long ssize_t;
#define DLL_LOCAL
#define PATH_MAX			260
#define STDIN_FILENO		0
#define STDOUT_FILENO		1
#define STDERR_FILENO		2
#define WITHOUT_LIBSTDCPP	0
#define __builtin_constant_p(dvs) (false)
#define HAVE_INT64_T		1
#else
#error unsupported platform
#endif // platform

#ifndef _CRTIMP
#ifdef _DLL
#define _CRTIMP __declspec(dllimport)
#else  /* _DLL */
#define _CRTIMP
#endif  /* _DLL */
#endif  /* _CRTIMP */

/* preprocessor string helpers */
#ifndef _CRT_STRINGIZE
#define __CRT_STRINGIZE(_Value) #_Value
#define _CRT_STRINGIZE(_Value) __CRT_STRINGIZE(_Value)
#endif  /* _CRT_STRINGIZE */

#ifndef _ERRNO_T_DEFINED
#define _ERRNO_T_DEFINED
typedef int errno_t;
#endif  /* _ERRNO_T_DEFINED */

#if !defined(UNALIGNED)
#if defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED __unaligned
#else  // defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED
#endif // defined(_M_IA64) || defined(_M_AMD64)
#endif // !defined(UNALIGNED)

//
// The INT_PTR is guaranteed to be the same size as a pointer.  Its
// size with change with pointer size (32/64).  It should be used
// anywhere that a pointer is cast to an integer type. UINT_PTR is
// the unsigned variation.
//
// __int3264 is intrinsic to 64b MIDL but not to old MIDL or to C compiler.
//
#if ( 501 < __midl )
	typedef [public] __int3264 intptr_t, *PINT_PTR;
	typedef [public] unsigned __int3264 UINT_PTR, *PUINT_PTR;
	typedef [public] __int3264 LONG_PTR, *PLONG_PTR;
	typedef [public] unsigned __int3264 ULONG_PTR, *PULONG_PTR;
#else  // midl64
// old MIDL and C++ compiler
#if defined(_WIN64)
	typedef __int64				INT_PTR, *PINT_PTR;
	typedef unsigned __int64	UINT_PTR, *PUINT_PTR;
	typedef __int64				LONG_PTR, *PLONG_PTR;
	typedef unsigned __int64	ULONG_PTR, *PULONG_PTR;
	#define __int3264   __int64
#else
	typedef _W64 intptr_t		INT_PTR, *PINT_PTR;
	typedef _W64 unsigned int	UINT_PTR, *PUINT_PTR;
	typedef _W64 long			LONG_PTR, *PLONG_PTR;
	typedef _W64 unsigned long	ULONG_PTR, *PULONG_PTR;
	#define __int3264   __int32
#endif
#endif // midl64

#ifndef _PTRDIFF_T_DEFINED
#ifdef _WIN64
typedef __int64             ptrdiff_t;
#else  /* _WIN64 */
typedef _W64 int            ptrdiff_t;
#endif  /* _WIN64 */
#define _PTRDIFF_T_DEFINED
#endif  /* _PTRDIFF_T_DEFINED */

#ifndef _INTPTR_T_DEFINED
#define _INTPTR_T_DEFINED
#ifdef _WIN64
typedef __int64 intptr_t;
#else /* _WIN64 */
typedef _W64 int intptr_t;
#endif /* _WIN64 */
#endif /* _INTPTR_T_DEFINED */

#ifndef _UINTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED
#ifdef _WIN64
typedef unsigned __int64 uintptr_t;
#else /* _WIN64 */
typedef _W64 unsigned int uintptr_t;
#endif /* _WIN64 */
#endif /* _UINTPTR_T_DEFINED */

#define _CRT_ALIGN(x) __declspec(align(x))

#include "stdint.h"
#include "sys/types.h"
#include "tchar.h"
#include "stddef.h"
#include "limits.h"
#include "float.h"
#include "string.h"
#include "stdlib.h"

#ifndef SIZE_MAX
	#define SIZE_MAX		UINT_MAX
#endif
#if sun || __sun		// Solaris defines UINTPTR_MAX as empty.
	#undef UINTPTR_MAX
	#define UINTPTR_MAX		ULONG_MAX
#endif
#ifndef WCHAR_MAX
	#ifdef __WCHAR_MAX__
	#define WCHAR_MAX	__WCHAR_MAX__
	#else
	#define WCHAR_MAX	CHAR_MAX
	#endif
#endif
#if HAVE_LONG_LONG
	#ifndef LLONG_MAX
	#define ULLONG_MAX	UINT64_C(0xFFFFFFFFFFFFFFFF)
	#define LLONG_MAX	INT64_C(0x7FFFFFFFFFFFFFFF)
	#define LLONG_MIN	ULLONG_MAX
	#endif
#endif
#ifndef BYTE_ORDER
	#define LITTLE_ENDIAN	STD_LITTLE_ENDIAN
	#define BIG_ENDIAN		STD_BIG_ENDIAN
	#define BYTE_ORDER		STD_BYTE_ORDER
#endif

typedef size_t		uoff_t;			///< A type for storing offsets into blocks measured by size_t.
typedef uint32_t	hashvalue_t;	///< Value type returned by the hash functions.
typedef size_t		streamsize;		///< Size of stream data
typedef uoff_t		streamoff;		///< Offset into a stream

// Test function
#define BVT(x)	if(x)	throw #x
#define BVTGROUP(x)	__try { (x); } __except(1) { puts("Error in group: " #x ); }


#endif // _INC_LOLIBBASE_