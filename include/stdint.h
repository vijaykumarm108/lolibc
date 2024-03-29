/**
stdint.h for lolibc - portable version
*/
#pragma once
#ifndef _INC_STDINT
#define _INC_STDINT
#ifndef RC_INVOKED

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef signed char int_least8_t;
typedef short int_least16_t;
typedef int int_least32_t;

typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned int uint_least32_t;

typedef char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;

typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;

typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef long long int_least64_t;
typedef unsigned long long uint_least64_t;

typedef long long int_fast64_t;
typedef unsigned long long uint_fast64_t;

typedef long long intmax_t;
typedef unsigned long long uintmax_t;

		/* LIMIT MACROS */
#define INT8_MIN	(-0x7f - _C2)
#define INT16_MIN	(-0x7fff - _C2)
#define INT32_MIN	(-0x7fffffff - _C2)

#define INT8_MAX	0x7f
#define INT16_MAX	0x7fff
#define INT32_MAX	0x7fffffff
#define UINT8_MAX	0xff
#define UINT16_MAX	0xffff
#define UINT32_MAX	0xffffffff

#define INT_LEAST8_MIN		(-0x7f - _C2)
#define INT_LEAST16_MIN		(-0x7fff - _C2)
#define INT_LEAST32_MIN		(-0x7fffffff - _C2)

#define INT_LEAST8_MAX		0x7f
#define INT_LEAST16_MAX		0x7fff
#define INT_LEAST32_MAX		0x7fffffff
#define UINT_LEAST8_MAX		0xff
#define UINT_LEAST16_MAX	0xffff
#define UINT_LEAST32_MAX	0xffffffff

#define INT_FAST8_MIN		(-0x7f - _C2)
#define INT_FAST16_MIN		(-0x7fff - _C2)
#define INT_FAST32_MIN		(-0x7fffffff - _C2)

#define INT_FAST8_MAX		0x7f
#define INT_FAST16_MAX		0x7fff
#define INT_FAST32_MAX		0x7fffffff
#define UINT_FAST8_MAX		0xff
#define UINT_FAST16_MAX		0xffff
#define UINT_FAST32_MAX		0xffffffff

 #if _INTPTR == 0 || _INTPTR == 1
#define INTPTR_MAX			0x7fffffff
#define INTPTR_MIN			(-INTPTR_MAX - _C2)
#define UINTPTR_MAX			0xffffffff

 #else /* _INTPTR == 2 */
#define INTPTR_MIN			(-_LLONG_MAX - _C2)
#define INTPTR_MAX			_LLONG_MAX
#define UINTPTR_MAX			_ULLONG_MAX
#endif /* _INTPTR */

#define INT8_C(x)	(x)
#define INT16_C(x)	(x)
#define INT32_C(x)	((x) + (INT32_MAX - INT32_MAX))

#define UINT8_C(x)	(x)
#define UINT16_C(x)	(x)
#define UINT32_C(x)	((x) + (UINT32_MAX - UINT32_MAX))

#ifdef _WIN64
 #define PTRDIFF_MIN		INT64_MIN
 #define PTRDIFF_MAX		INT64_MAX
#else /* _WIN64 */
 #define PTRDIFF_MIN		INT32_MIN
 #define PTRDIFF_MAX		INT32_MAX
#endif /* _WIN64 */

#define SIG_ATOMIC_MIN	INT32_MIN
#define SIG_ATOMIC_MAX	INT32_MAX

#ifndef SIZE_MAX
 #ifdef _WIN64
  #define SIZE_MAX		UINT64_MAX
 #else /* _WIN64 */
  #define SIZE_MAX		UINT32_MAX
 #endif /* _WIN64 */
#endif /* SIZE_MAX */

#define WCHAR_MIN	0x0000
#define WCHAR_MAX	0xffff

#define WINT_MIN	0x0000
#define WINT_MAX	0xffff

 #define INT64_MIN	(-0x7fffffffffffffff - _C2)
 #define INT64_MAX	0x7fffffffffffffff
 #define UINT64_MAX	0xffffffffffffffffU

 #define INT_LEAST64_MIN	(-0x7fffffffffffffff - _C2)
 #define INT_LEAST64_MAX	0x7fffffffffffffff
 #define UINT_LEAST64_MAX	0xffffffffffffffffU

 #define INT_FAST64_MIN		(-0x7fffffffffffffff - _C2)
 #define INT_FAST64_MAX		0x7fffffffffffffff
 #define UINT_FAST64_MAX	0xffffffffffffffffU

 #define INTMAX_MIN		(-0x7fffffffffffffff - _C2)
 #define INTMAX_MAX		0x7fffffffffffffff
 #define UINTMAX_MAX	0xffffffffffffffffU

#define INT64_C(x)		((x) + (INT64_MAX - INT64_MAX))
#define UINT64_C(x)		((x) + (UINT64_MAX - UINT64_MAX))
#define INTMAX_C(x)		INT64_C(x)
#define UINTMAX_C(x)	UINT64_C(x)

// Checks if types are the right size
#ifdef __cplusplus
static union
{
	char 	int8_t_incorrect 	[sizeof( int8_t) == 1];
	char 	uint8_t_incorrect 	[sizeof( uint8_t) == 1];
	char 	int16_t_incorrect 	[sizeof( int16_t) == 2];
	char 	uint16_t_incorrect 	[sizeof(uint16_t) == 2];
	char 	int32_t_incorrect 	[sizeof( int32_t) == 4];
	char 	uint32_t_incorrect 	[sizeof(uint32_t) == 4];
}; 
#endif // __cplusplus

#endif /* RC_INVOKED */
#endif /* _INC_STDINT */
