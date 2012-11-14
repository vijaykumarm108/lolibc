/*!
\file types.h lolibc
*/
#pragma once
#ifndef _INC_TYPES
#define _INC_TYPES

#if !defined(_W64)
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86))
#define _W64 __w64
#else
#define _W64
#endif
#endif

//#ifdef  _USE_32BIT_TIME_T
//#ifdef  _WIN64
//#include <crtwrn.h>
//#endif
//#endif

#ifndef _TIME32_T_DEFINED
typedef _W64 long __time32_t;   /* 32-bit time value */
#define _TIME32_T_DEFINED
#endif

#ifndef _TIME64_T_DEFINED
typedef __int64 __time64_t;			/* 64-bit time value */
#define _TIME64_T_DEFINED
#endif

#ifndef _TIME_T_DEFINED
#ifdef _USE_32BIT_TIME_T
typedef __time32_t time_t;			/* time value */
#else
typedef __time64_t time_t;			/* time value */
#endif
#define _TIME_T_DEFINED				/* avoid multiple def's of time_t */
#endif

#ifndef _INO_T_DEFINED
typedef unsigned short _ino_t;		/* i-node number (not used on DOS) */
typedef unsigned short ino_t;
#define _INO_T_DEFINED
#endif

#ifndef _DEV_T_DEFINED
typedef unsigned int _dev_t;		/* device code */
typedef unsigned int dev_t;			/* Non-ANSI */
#define _DEV_T_DEFINED
#endif

#ifndef _OFF_T_DEFINED
typedef long _off_t;				/* file offset value */
typedef long off_t;					/* Non-ANSI name for compatibility */
#define _OFF_T_DEFINED
#endif

#endif  /* _INC_TYPES */
