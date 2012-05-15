/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
/*
\file LoMsvcrt.h
\brief Common header file for entire LoMsvcrt.lib project
*/

#pragma once
#define _CRT_VCCLRIT_NO_DEPRECATE	// This is needed to include _vcclrit.h, because this library is not for managed code!
#include <_vcclrit.h>
#include <windows.h>
#include <WinNT.h>					// This is found in the Microsoft SDK which must be installed in addition to Visual Studio
#include <tchar.h>
#include <crtdbg.h>

// Startup function pointers
typedef void (__cdecl *_PVFV)(void);
typedef int  (__cdecl *_PIFV)(void);
typedef void (__cdecl *_PVFI)(int);

// Declare our standard startup and shutdown sections
#pragma section(".CRTMP$XCA",long,read)
#pragma section(".CRTMP$XCZ",long,read)
#pragma section(".CRTMP$XIA",long,read)
#pragma section(".CRTMP$XIZ",long,read)

#pragma section(".CRTMA$XCA",long,read)
#pragma section(".CRTMA$XCZ",long,read)
#pragma section(".CRTMA$XIA",long,read)
#pragma section(".CRTMA$XIZ",long,read)

#pragma section(".CRTVT$XCA",long,read)
#pragma section(".CRTVT$XCZ",long,read)

#pragma section(".CRT$XCA",long,read)
#pragma section(".CRT$XCAA",long,read)
#pragma section(".CRT$XCC",long,read)
#pragma section(".CRT$XCZ",long,read)
#pragma section(".CRT$XDA",long,read)
#pragma section(".CRT$XDC",long,read)
#pragma section(".CRT$XDZ",long,read)
#pragma section(".CRT$XIA",long,read)
#pragma section(".CRT$XIAA",long,read)
#pragma section(".CRT$XIC",long,read)
#pragma section(".CRT$XID",long,read)
#pragma section(".CRT$XIY",long,read)
#pragma section(".CRT$XIZ",long,read)
#pragma section(".CRT$XLA",long,read)
#pragma section(".CRT$XLC",long,read)
#pragma section(".CRT$XLD",long,read)
#pragma section(".CRT$XLZ",long,read)
#pragma section(".CRT$XPA",long,read)
#pragma section(".CRT$XPX",long,read)
#pragma section(".CRT$XPXA",long,read)
#pragma section(".CRT$XPZ",long,read)
#pragma section(".CRT$XTA",long,read)
#pragma section(".CRT$XTB",long,read)
#pragma section(".CRT$XTX",long,read)
#pragma section(".CRT$XTZ",long,read)

#pragma section(".rdata$T",long,read)
#pragma section(".rtc$IAA",long,read)
#pragma section(".rtc$IZZ",long,read)
#pragma section(".rtc$TAA",long,read)
#pragma section(".rtc$TZZ",long,read)

#define _CRTALLOC(x) __declspec(allocate(x))

#ifndef _STARTUP_INFO_DEFINED
typedef struct
{
	int newmode;
} _startupinfo;
#define _STARTUP_INFO_DEFINED
#endif // _STARTUP_INFO_DEFINED

// Set app type...
#define _UNKNOWN_APP    0
#define _CONSOLE_APP    1
#define _GUI_APP        2
_CRTIMP void __cdecl __set_app_type(int);

_CRTIMP int * __cdecl __p__commode(void);
_CRTIMP extern int _commode;


_CRTIMP int __cdecl __getmainargs(_Out_ int * _Argc, _Out_ _Deref_post_cap_(*_Argc) char *** _Argv,
								  _Deref_out_opt_ char *** _Env, _In_ int _DoWildCard,
								  _In_ _startupinfo * _StartInfo);

_CRTIMP int __cdecl __wgetmainargs(_Out_ int * _Argc, _Out_ _Deref_post_cap_(*_Argc)wchar_t *** _Argv,
								   _Deref_out_opt_ wchar_t *** _Env, _In_ int _DoWildCard,
								   _In_ _startupinfo * _StartInfo);

#define _RT_SPACEARG                    8               /* not enough space for arguments */
_CRTIMP void __cdecl _amsg_exit(int);


extern _CRTIMP wchar_t **__winitenv;
extern _CRTIMP char **__initenv;

extern _CRTIMP wchar_t *_wcmdln;
extern _CRTIMP char *_acmdln;
/*
extern int __argc;
extern char ** __argv;
extern wchar_t ** __wargv;
*/
int __CRTDECL main(_In_ int _Argc, _In_count_(_Argc) _Pre_z_ char ** _Argv, _In_z_ char ** _Env);
int __CRTDECL wmain(_In_ int _Argc, _In_count_(_Argc) _Pre_z_ wchar_t ** _Argv, _In_z_ wchar_t ** _Env);
