/*!
\file stat.h lolibc
*/

#pragma once

#ifndef _INC_STAT
#define _INC_STAT

#pragma pack(push,8)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include <sys/types.h>

#if !defined (_W64)
#if !defined (__midl) && (defined (_X86_) || defined (_M_IX86))
#define _W64 __w64
#else  /* !defined (__midl) && (defined (_X86_) || defined (_M_IX86)) */
#define _W64
#endif  /* !defined (__midl) && (defined (_X86_) || defined (_M_IX86)) */
#endif  /* !defined (_W64) */

#ifndef _TIME32_T_DEFINED
typedef _W64 long __time32_t;   /* 32-bit time value */
#define _TIME32_T_DEFINED
#endif  /* _TIME32_T_DEFINED */

#ifndef _TIME64_T_DEFINED
typedef __int64 __time64_t;     /* 64-bit time value */
#define _TIME64_T_DEFINED
#endif  /* _TIME64_T_DEFINED */

#ifndef _TIME_T_DEFINED
#ifdef _USE_32BIT_TIME_T
typedef __time32_t time_t;      /* time value */
#else  /* _USE_32BIT_TIME_T */
typedef __time64_t time_t;      /* time value */
#endif  /* _USE_32BIT_TIME_T */
#define _TIME_T_DEFINED         /* avoid multiple def's of time_t */
#endif  /* _TIME_T_DEFINED */

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif  /* _WCHAR_T_DEFINED */


/* define structure for returning status information */
struct _stat32 {
	_dev_t     st_dev;
	_ino_t     st_ino;
	unsigned short st_mode;
	short      st_nlink;
	short      st_uid;
	short      st_gid;
	_dev_t     st_rdev;
	_off_t     st_size;
	__time32_t st_atime;
	__time32_t st_mtime;
	__time32_t st_ctime;
};

struct stat {
	_dev_t     st_dev;
	_ino_t     st_ino;
	unsigned short st_mode;
	short      st_nlink;
	short      st_uid;
	short      st_gid;
	_dev_t     st_rdev;
	_off_t     st_size;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
};

struct _stat32i64 {
	_dev_t     st_dev;
	_ino_t     st_ino;
	unsigned short st_mode;
	short      st_nlink;
	short      st_uid;
	short      st_gid;
	_dev_t     st_rdev;
	__int64    st_size;
	__time32_t st_atime;
	__time32_t st_mtime;
	__time32_t st_ctime;
};

struct _stat64i32 {
	_dev_t     st_dev;
	_ino_t     st_ino;
	unsigned short st_mode;
	short      st_nlink;
	short      st_uid;
	short      st_gid;
	_dev_t     st_rdev;
	_off_t     st_size;
	__time64_t st_atime;
	__time64_t st_mtime;
	__time64_t st_ctime;
};

struct _stat64 {
	_dev_t     st_dev;
	_ino_t     st_ino;
	unsigned short st_mode;
	short      st_nlink;
	short      st_uid;
	short      st_gid;
	_dev_t     st_rdev;
	__int64    st_size;
	__time64_t st_atime;
	__time64_t st_mtime;
	__time64_t st_ctime;
};

/*
 * We have to have same name for structure and the function so as to do the
 * macro magic.we need the structure name and function name the same.
 */
#define __stat64    _stat64

#define _S_IFMT         0xF000          /* file type mask */
#define _S_IFDIR        0x4000          /* directory */
#define _S_IFCHR        0x2000          /* character special */
#define _S_IFIFO        0x1000          /* pipe */
#define _S_IFREG        0x8000          /* regular */
#define _S_IREAD        0x0100          /* read permission, owner */
#define _S_IWRITE       0x0080          /* write permission, owner */
#define _S_IEXEC        0x0040          /* execute/search permission, owner */


/* Function prototypes */
#ifdef _WIN32
__inline int __cdecl fstat(_In_ int _FileDes, _Out_ struct stat * _Stat)
{
	_CRTIMP int __cdecl _fstat(_In_ int _FileDes, _Out_ struct stat * _Stat);
	return _fstat(_FileDes,_Stat);
}
__inline int __cdecl fstat64(_In_ int _FileDes, _Out_ struct _stat64 * _Stat)
{
	_CRTIMP int __cdecl _fstat64(_In_ int _FileDes, _Out_ struct _stat64 * _Stat);
	return _fstat64(_FileDes,_Stat);
}
int stat (const char *filename, struct stat *buf); // In StdLibC.c
#else
_CRTIMP int __cdecl fstat(_In_ int _FileDes, _Out_ struct stat * _Stat);
_CRTIMP int __cdecl fstat64(_In_ int _FileDes, _Out_ struct _stat64 * _Stat);
_CRTIMP int stat (const char *filename, struct stat *buf);
_CRTIMP int __cdecl stat64(_In_z_ const char * _Name, _Out_ struct _stat64 * _Stat);
#endif


#if !__STDC__

/* Non-ANSI names for compatibility */

#define S_IFMT   _S_IFMT
#define S_IFDIR  _S_IFDIR
#define S_IFCHR  _S_IFCHR
#define S_IFREG  _S_IFREG
#define S_IREAD  _S_IREAD
#define S_IWRITE _S_IWRITE
#define S_IEXEC  _S_IEXEC

#endif  /* !__STDC__ */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#pragma pack(pop)

#endif  /* _INC_STAT */
