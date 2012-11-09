/*
Standard Windows DLL definitions. These are the very basic definitions for all windows system DLLs.
*/
#pragma once

#include "lolibbase.h"

#ifdef __cplusplus

#define WINAPI __stdcall
#define WINAPIV __stdcall
#define APIENTRY __stdcall

namespace lo
{
	class dll
	{
	public:
		inline dll()	{_addref();}
		~dll()			{_release(); }
		virtual const char *Name() = 0;
		static void		_free_unused_dlls();
	protected:
		virtual int &counter() = 0;
		void _addref();
		void _release();
		intptr_t	m_handle;
	};
}

#endif

#define FAR
#define NEAR
#define IN
#define OUT
#define CONST				const
#define FALSE (0)
#define TRUE (1)
typedef int					BOOL;
typedef BOOL				*LPBOOL;
typedef void				*HINSTANCE;
typedef char				CHAR;
typedef wchar_t				WCHAR;
typedef unsigned char       BYTE;
typedef BYTE				*LPBYTE;
typedef BYTE				*PBYTE;
typedef unsigned short		WORD;
typedef unsigned long       DWORD;
typedef DWORD				*LPDWORD;
typedef long				LONG;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef void				*LPVOID;
typedef const void			*LPCVOID;
typedef unsigned short		SHORT;
typedef unsigned int		UINT, *PUINT;
typedef unsigned long		ULONG;
typedef CHAR				*NPSTR, *LPSTR, *PSTR;
typedef const CHAR			*LPCSTR, *PCSTR;
typedef const WCHAR			*LPCWSTR, *PCWSTR;
typedef WCHAR				*NWPSTR, *LPWSTR, *PWSTR;
typedef UINT_PTR            WPARAM;
typedef LONG_PTR            LPARAM;
typedef LONG_PTR            LRESULT;
typedef void				*HANDLE;
typedef HANDLE FAR          *LPHANDLE;
typedef int					INT;
typedef int					*LPINT;
typedef void				*HWND;
typedef void				*HINSTANCE;
typedef intptr_t			(WINAPI *PROC)();
typedef intptr_t			(WINAPI *FARPROC)();
typedef void				*HMODULE;
typedef void				*LPVOID;
typedef void				*PVOID;
typedef unsigned short		USHORT;
typedef WORD				*LPWORD;
typedef __int64				LONGLONG;
typedef unsigned __int64	ULONGLONG;
typedef ULONGLONG			DWORDLONG;
typedef DWORDLONG			*PDWORDLONG;
typedef DWORD				*PDWORD;
typedef ULONG_PTR			DWORD_PTR, *PDWORD_PTR;
typedef WORD				*PWORD;
typedef ULONG				*PULONG;
typedef WORD				FSHORT;

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef signed __int64      INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned __int64    UINT64, *PUINT64;

#define WINBASEAPI __declspec(dllimport)
#define CALLBACK    __stdcall
typedef LONG				HRESULT;
#define VOID void
#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)


// Writes flags
#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)
#define STANDARD_RIGHTS_ALL              (0x001F0000L)
#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)
#define ACCESS_SYSTEM_SECURITY           (0x01000000L)	// AccessSystemAcl access type
#define MAXIMUM_ALLOWED                  (0x02000000L)	// MaximumAllowed access type
#define GENERIC_READ                     (0x80000000L)	//  These are the generic rights.
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

#if !defined(DECLSPEC_IMPORT)
#if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_IA64) || defined(_M_AMD64)) && !defined(MIDL_PASS)
#define DECLSPEC_IMPORT __declspec(dllimport)
#else
#define DECLSPEC_IMPORT
#endif
#endif

#define MAX_PATH						260

typedef struct tagPOINT
{
	long  x;
	long  y;
} POINT, *PPOINT, *NPPOINT, *LPPOINT;

typedef struct tagSIZE
{
	LONG        cx;
	LONG        cy;
} SIZE, *PSIZE, *LPSIZE;

typedef SIZE               SIZEL;
typedef SIZE               *PSIZEL, *LPSIZEL;

typedef union _LARGE_INTEGER {
	struct {
		DWORD LowPart;
		LONG HighPart;
	} u;
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD_PTR)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))

// More static analysis definitions
#define __field_ecount_opt(Count)

#ifndef DECLSPEC_UUID
#if (_MSC_VER >= 1100) && defined(__cplusplus)
#define DECLSPEC_UUID(x) __declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif
#endif

#ifndef DECLSPEC_NOVTABLE
#if (_MSC_VER >= 1100) && defined(__cplusplus)
#define DECLSPEC_NOVTABLE __declspec(novtable)
#else
#define DECLSPEC_NOVTABLE
#endif
#endif

#define MIDL_INTERFACE(x)   struct DECLSPEC_UUID(x) DECLSPEC_NOVTABLE
