#pragma once
#include <dll.h>
#include "ntoskrnl.h"

#ifdef __cplusplus

namespace lo
{
	class kernel32 : public dll
	{
	public:
		kernel32() : dll() {}
		enum {	CP_ACP = 0,			// default to ANSI code page
				CP_OEMCP = 1,		// default to OEM  code page
				CP_MACCP = 2,		// default to MAC  code page
				CP_THREAD_ACP = 3,	// current thread's ANSI code page
				CP_SYMBOL = 42,		// SYMBOL translations
				CP_UTF7 = 65000,	// UTF-7 translation
				CP_UTF8 = 65001		// UTF-8 translation
		};
		typedef int BOOL;
		typedef BOOL *LPBOOL;
		typedef ntoskrnl::RTL_CRITICAL_SECTION CRITICAL_SECTION;
		typedef ntoskrnl::PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;
		void		InitializeCriticalSection( LPCRITICAL_SECTION lpCriticalSection );
		int			MultiByteToWideChar( uint32_t Codepage, uint32_t dwFlags, const char *lpMultiByteStr, int cbMultiByte,
						wchar_t * lpWideCharStr, int cchWideChar );
		int			WideCharToMultiByte( uint32_t CodePage, uint32_t dwFlags, const wchar_t *lpWideCharStr, int cchWideChar,
						char * lpMultiByteStr, int cbMultiByte, const char * lpDefaultChar, LPBOOL lpUsedDefaultChar );
		const char *Name();
		int &counter();
	};
}

#else

typedef RTL_CRITICAL_SECTION CRITICAL_SECTION;
typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

#endif