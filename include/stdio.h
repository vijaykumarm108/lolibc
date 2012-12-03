/*!
\file stdio.h lolibc
*/
#pragma once

#ifndef _INC_STDIO
#define _INC_STDIO
#include "stdarg.h"

/* Currently, all MS C compilers for Win32 platforms default to 8 byte alignment. */
#pragma pack(push,8)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/* Buffered I/O macros */
#define BUFSIZ  512

#ifndef _INTERNAL_IFSTRIP_
/*
 * Real default size for stdio buffers
 */
#define _INTERNAL_BUFSIZ    4096
#define _SMALL_BUFSIZ       512
#endif  /* _INTERNAL_IFSTRIP_ */

/*
 * Default number of supported streams. _NFILE is confusing and obsolete, but
 * supported anyway for backwards compatibility.
 */
#define _NFILE      _NSTREAM_
#define _NSTREAM_   512

/*
 * Number of entries in _iob[] (declared below). Note that _NSTREAM_ must be
 * greater than or equal to _IOB_ENTRIES.
 */
#define _IOB_ENTRIES 20
#define EOF     (-1)

#ifndef _FILE_DEFINED
struct _iobuf {
	char *_ptr;
	int   _cnt;
	char *_base;
	int   _flag;
	int   _file;
	int   _charbuf;
	int   _bufsiz;
	char *_tmpfname;
};
typedef struct _iobuf FILE;
#define _FILE_DEFINED
#endif  /* _FILE_DEFINED */

/* Directory where temporary files may be created. */

#define _P_tmpdir   "\\"
#define _wP_tmpdir  L"\\"

/* L_tmpnam = length of string _P_tmpdir
 *            + 1 if _P_tmpdir does not end in "/" or "\", else 0
 *            + 12 (for the filename string)
 *            + 1 (for the null terminator)
 * L_tmpnam_s = length of string _P_tmpdir
 *            + 1 if _P_tmpdir does not end in "/" or "\", else 0
 *            + 16 (for the filename string)
 *            + 1 (for the null terminator)
 */
#define L_tmpnam   (sizeof(_P_tmpdir) + 12)
#if __STDC_WANT_SECURE_LIB__
#define L_tmpnam_s (sizeof(_P_tmpdir) + 16)
#endif  /* __STDC_WANT_SECURE_LIB__ */

/* Seek method constants */

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

#define FILENAME_MAX    260
#define FOPEN_MAX       20
#define _SYS_OPEN       20
#define TMP_MAX         32767  /* SHRT_MAX */

/*!
\brief stdio.h
MuThink
*/
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else  /* __cplusplus */
#define NULL    ((void *)0)
#endif  /* __cplusplus */
#endif  /* NULL */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

	_CRTIMP int		fclose ( FILE * stream );
	_CRTIMP FILE *	_fdopen( int fd, const char *mode );
	_CRTIMP int		feof (FILE *stream);
	_CRTIMP int		ferror (FILE *stream);
	_CRTIMP int		fflush(_Inout_opt_ FILE * _File);
	_CRTIMP FILE *	fopen ( const char * filename, const char * mode );
	_CRTIMP size_t	fread ( void * ptr, size_t size, size_t count, FILE * stream );
	_CRTIMP FILE *	freopen ( const char * fileName, const char * mode, FILE *stream );
	_CRTIMP int		fseek ( FILE * stream, long int offset, int origin );
	__int64			fseeko64 (FILE *stream, __int64 offset, int whence);	// in StdLibC.c
	_CRTIMP long	ftell ( FILE * stream );
	__int64			ftello64(FILE *stream);	// in StdLibC.c
	_CRTIMP size_t	fwrite ( const void * ptr, size_t size, size_t count, FILE * stream );
	_CRTIMP int		getc ( FILE * stream );
	_CRTIMP int		getchar ( void );
	_CRTIMP int		printf( const char * format, ... );
	_CRTIMP int		putc ( int character, FILE * stream );
	_CRTIMP int		puts ( const char * str );
	_CRTIMP int		remove (const char *filename);	// In stdlib.h
	_CRTIMP int		scanf (const char *format, ...);
	_CRTIMP int		_snprintf( char *buffer, size_t count, const char *format, ...  );
	_CRTIMP int		_snwprintf( wchar_t *buffer, size_t count, const wchar_t *format, ... );
	_CRTIMP int		sprintf( char *str, const char *format, ... );
	_CRTIMP int		sscanf( const char *buffer, const char *format, ... );
	_CRTIMP int		swscanf( const wchar_t *buffer,	const wchar_t *format, ... );
	_CRTIMP int		vprintf( const char *format, va_list ap );
	_CRTIMP int		vsprintf( char *str, const char *format, va_list ap );
	_CRTIMP int		_vsnprintf( char *str, size_t size, const char *format, va_list ap );
	__inline int	vsnprintf(char *str, size_t size, const char *format, va_list ap )
	{
		return _vsnprintf(str,size,format,ap);
	}
	_CRTIMP int		vswprintf( wchar_t *buffer, size_t count, const wchar_t *format, va_list argptr );
	_CRTIMP int		vfprintf( FILE *stream, const char *format, va_list ap );
	_CRTIMP int		_vsnwprintf( wchar_t *buffer, size_t count, const wchar_t *format, va_list argptr );
#ifdef __cplusplus
};
#endif

#pragma pack(pop)

#endif // _INC_STDIO
