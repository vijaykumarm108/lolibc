/* lolibc library
*/
#pragma once
#include "lolibbase.h"

#ifndef _INC_FCNTL
#define _INC_FCNTL


#define _O_RDONLY       0x0000  /* open for reading only */
#define _O_WRONLY       0x0001  /* open for writing only */
#define _O_RDWR         0x0002  /* open for reading and writing */
#define _O_APPEND       0x0008  /* writes done at eof */

#define _O_CREAT        0x0100  /* create and open file */
#define _O_TRUNC        0x0200  /* open and truncate */
#define _O_EXCL         0x0400  /* open only if file doesn't already exist */

/* O_TEXT files have <cr><lf> sequences translated to <lf> on read()'s,
** and <lf> sequences translated to <cr><lf> on write()'s
*/

#define _O_TEXT         0x4000  /* file mode is text (translated) */
#define _O_BINARY       0x8000  /* file mode is binary (untranslated) */
#define _O_WTEXT        0x10000 /* file mode is UTF16 (translated) */
#define _O_U16TEXT      0x20000 /* file mode is UTF16 no BOM (translated) */
#define _O_U8TEXT       0x40000 /* file mode is UTF8  no BOM (translated) */

/* macro to translate the C 2.0 name used to force binary mode for files */

#define _O_RAW  _O_BINARY

/* Open handle inherit bit */

#define _O_NOINHERIT    0x0080  /* child process doesn't inherit file */

/* Temporary file bit - file is deleted when last handle is closed */

#define _O_TEMPORARY    0x0040  /* temporary file bit */

/* temporary access hint */

#define _O_SHORT_LIVED  0x1000  /* temporary storage file, try not to flush */

/* sequential/random access hints */

#define _O_SEQUENTIAL   0x0020  /* file access is primarily sequential */
#define _O_RANDOM       0x0010  /* file access is primarily random */

#if !__STDC__
/* Non-ANSI names for compatibility */
#define O_RDONLY        _O_RDONLY
#define O_WRONLY        _O_WRONLY
#define O_RDWR          _O_RDWR
#define O_APPEND        _O_APPEND
#define O_CREAT         _O_CREAT
#define O_TRUNC         _O_TRUNC
#define O_EXCL          _O_EXCL
#define O_TEXT          _O_TEXT
#define O_BINARY        _O_BINARY
#define O_RAW           _O_BINARY
#define O_TEMPORARY     _O_TEMPORARY
#define O_NOINHERIT     _O_NOINHERIT
#define O_SEQUENTIAL    _O_SEQUENTIAL
#define O_RANDOM        _O_RANDOM
#endif  /* !__STDC__ */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
	__inline int __cdecl close(int _FileHandle)
	{
		_CRTIMP int __cdecl _close(int _FileHandle);
		return _close(_FileHandle);
	}
	__inline off_t lseek(int fd, off_t offset, int whence)
	{
		_CRTIMP off_t _lseek(int fd, off_t offset, int whence);
		return _lseek(fd,offset,whence);
	}
	__inline __int64 lseek64 (int filedes, __int64 offset, int whence)
	{
		_CRTIMP __int64 _lseeki64 (int filedes, __int64 offset, int whence);
		return _lseeki64(filedes,offset,whence);
	}
	__inline int __cdecl open( const char * _Filename, int _OpenFlag, ...)
	{
		_CRTIMP int __cdecl _open( const char * _Filename, int _OpenFlag, ...);	// UTF8 version punts to _wopen
		return _open(_Filename,_OpenFlag);
	}
	__inline int __cdecl read( int _FileHandle, void * _DstBuf, unsigned int _MaxCharCount)
	{
		_CRTIMP int __cdecl _read( int _FileHandle, void * _DstBuf, unsigned int _MaxCharCount);
		return _read(_FileHandle,_DstBuf,_MaxCharCount);
	}
	__inline int __cdecl write( int file, const void * buffer, unsigned int bufferLength)
	{
		_CRTIMP int __cdecl _write( int file, const void * buffer, unsigned int bufferLength);
		return _write(file,buffer,bufferLength);
	}
#else
#error not implemented
	_CRTIMP off_t lseek(int fd, off_t offset, int whence);
	_CRTIMP __int64 lseek64 (int filedes, __int64 offset, int whence);
#endif

#ifdef __cplusplus
};
#endif

#endif

