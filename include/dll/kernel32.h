#pragma once
#include <dll.h>
#include "ntoskrnl.h"

// All the kernel32 definitions go here
#ifdef __cplusplus
namespace lo { namespace kernel32 {	// This namespace contains all the definitions for the kernel32 functions
#endif

	enum {	CP_ACP = 0,			// default to ANSI code page
		CP_OEMCP = 1,		// default to OEM  code page
		CP_MACCP = 2,		// default to MAC  code page
		CP_THREAD_ACP = 3,	// current thread's ANSI code page
		CP_SYMBOL = 42,		// SYMBOL translations
		CP_UTF7 = 65000,	// UTF-7 translation
		CP_UTF8 = 65001		// UTF-8 translation
	};

	typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
	typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

	static uint32_t STD_INPUT_HANDLE  = ((uint32_t)-10);
	static uint32_t STD_OUTPUT_HANDLE = ((uint32_t)-11);
	static uint32_t STD_ERROR_HANDLE  = ((uint32_t)-12);

#ifdef __cplusplus
} }

using namespace lo::kernel32;

extern "C" {
#endif

typedef HANDLE              HGLOBAL;

//----------------------------------------- Function declarations -------------------------------------------
WINBASEAPI int WINAPI		Beep( __in  uint32_t dwFreq, __in  uint32_t dwDuration	);
WINBASEAPI void WINAPI		FreeLibrary( __in intptr_t libraryHandle );
WINBASEAPI intptr_t WINAPI	GetStdHandle( __in uint32_t nStdHandle );
WINBASEAPI void WINAPI		InitializeCriticalSection( LPCRITICAL_SECTION lpCriticalSection );
WINBASEAPI intptr_t WINAPI	LoadLibraryA( __in const char *moduleName );
WINBASEAPI intptr_t WINAPI  OpenProcess( __in uint32_t desiredAccess, __in BOOL bInheritHandle, __in uint32_t processId );
WINBASEAPI int	WINAPI		MultiByteToWideChar( uint32_t Codepage, uint32_t dwFlags, const char *lpMultiByteStr, int cbMultiByte, wchar_t * lpWideCharStr, int cchWideChar );
WINBASEAPI BOOL WINAPI		SetConsoleTextAttribute( __in intptr_t hConsoleOutput, __in uint16_t wAttributes );
WINBASEAPI VOID	WINAPI		SetLastError( __in DWORD dwErrCode );
WINBASEAPI int WINAPI		WideCharToMultiByte( uint32_t CodePage, uint32_t dwFlags, const wchar_t *lpWideCharStr, int cchWideChar, char * lpMultiByteStr, int cbMultiByte, const char * lpDefaultChar, LPBOOL lpUsedDefaultChar );
#ifdef __cplusplus
}; // end extern "C"

namespace lo { namespace kernel32 {

} }

#endif
