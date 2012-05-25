/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
/*!
\file main.c
\brief Initialization for console EXE using CRT DLL.

This is the startup routine for apps or dlls's linking with LoMsvcrt.lib.
It will initialized all the static initializers, including constructors and also
call all the cleanup code, including static destructors.

It looks for [w]main() or [w]WinMain() depending on the ifdefs set.

This file is included by the following files in order to support different bindings:

   wcrtexe.c   the startup routine for console apps with wide chars
   WinMain.c   the startup routine for Windows apps
   wWinMain.c  the startup routine for Windows apps with wide chars

If this file is not wrapped, then its default is MBCS(not UNICODE) for console app.

*/
//#if defined(_M_IX86)
#define CRTDLL
//#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef CRTDLL
#undef  CRTDLL
#ifndef _DLL
#define _DLL
#endif  /* _DLL */


#define SPECIAL_CRTEXE
#include "lomsvcrt.h"
#include <process.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <rtcapi.h>
#include <locale.h>

#if defined (_WIN64) && defined (_M_IA64)
#pragma section(".base", long, read)
__declspec(allocate(".base"))
extern
IMAGE_DOS_HEADER __ImageBase;
#else  /* defined (_WIN64) && defined (_M_IA64) */
extern IMAGE_DOS_HEADER __ImageBase;
#endif  /* defined (_WIN64) && defined (_M_IA64) */


/* We only want to set the UnhandledExceptionFilter when this crt is loaded by an EXE (ie. not loaded by a DLL) */
//int  __cdecl __CxxSetUnhandledExceptionFilter(void);
//_CRTALLOC(".CRT$XIY") static _PIFV pinit = &__CxxSetUnhandledExceptionFilter;

#define SPACECHAR   _T(' ')
#define DQUOTECHAR  _T('\"')

#ifdef _M_IX86
/* The local copy of the Pentium FDIV adjustment flag and the address of the flag in MSVCRT*.DLL. */
//extern int _adjust_fdiv;
//extern int * _imp___adjust_fdiv;
#endif  /* _M_IX86 */

// Declare function used to install a user-supplied _matherr routine.
_CRTIMP void __setusermatherr( int (__cdecl *)(struct _exception *) );

/*
* routine in DLL to do initialization (in this case, C++ constructors)
*/
extern void __cdecl _initterm(_PVFV *, _PVFV *);


/*
 * Declare the names of the exports corresponding to _fmode and _commode
 */
//#ifdef _M_IX86

#define _IMP___FMODE    (__p__fmode())
#define _IMP___COMMODE  (__p__commode())

//#else  /* _M_IX86 */

/* assumed to be MIPS or Alpha */

//#define _IMP___FMODE    __imp__fmode
//#define _IMP___COMMODE  __imp__commode

//#endif  /* _M_IX86 */

//#if !defined (_M_IX86)
//extern int * _IMP___FMODE;      /* exported from the CRT DLL */
//extern int * _IMP___COMMODE;    /* these names are implementation-specific */
//#endif  /* !defined (_M_IX86) */

/*
 * Declare/define communal that serves as indicator the default matherr
 * routine is being used.
 */
int __defaultmatherr;

/* _initterm_c and the C and C++ initialization variables */
extern int __cdecl _initterm_e ( _PIFV * pfbegin, _PIFV * pfend );
extern _CRTALLOC(".CRT$XIA") _PIFV __xi_a[];
extern _CRTALLOC(".CRT$XIZ") _PIFV __xi_z[];    /* C initializers */
extern _CRTALLOC(".CRT$XCA") _PVFV __xc_a[];
extern _CRTALLOC(".CRT$XCZ") _PVFV __xc_z[];    /* C++ initializers */

/*
 * Pointer to callback function to initialize any dynamically initialized
 * __declspec(thread) variables.  This relies on a subtle aspect of C.
 * The pointer is defined here uninitialized.  It is defined initialized in
 * tlsdyn.c.  If user code uses dynamically initialized __declspec(thread)
 * variables, then compiler-injected dependencies cause tlsdyn.obj to be
 * linked.  In that case, the non-zero definition of __dyn_tls_init_callback
 * in tlsdyn.obj will take precedence, and the startup code will execute the
 * callback.  This use of multiple definitions is only legal in C, not C++.
 */

const PIMAGE_TLS_CALLBACK __dyn_tls_init_callback;

/*
 * Pointers to beginning and end of the table of function pointers manipulated
 * by _onexit()/atexit().  The atexit/_onexit code is shared for both EXE's and
 * DLL's but different behavior is required.  These values are set to -1 to
 * mark this module as an EXE.
 * NOTE - the pointers are stored encoded.
 */

_PVFV *__onexitbegin;
_PVFV *__onexitend;

/*
 * All the below variables are made static global for this file. This facilitates
 * in communicating mainCRTStartup and initialization code. Along with making these
 * variables global, two new functions are created pre_c_init, pre_cpp_init. The functions
 * are executed before anything in c_init and cpp_init sections respectively.
 */


//extern int _argc;
//extern char **_argv;
//extern wchar_t **_wargv;

//extern int _argc;
//extern _TSCHAR **_argv;
#pragma warning(disable:4273)
//extern int __argc;   /* three standard arguments to main */
#ifndef _UNICODE
//extern char **__argv;
char **envp;
#else
//wchar_t **__wargv;
wchar_t **envp;
#endif

_CRTIMP int* __cdecl __p___argc(void);
_CRTIMP char*** __cdecl __p___argv(void);
_CRTIMP wchar_t*** __cdecl __p___wargv(void);
#define __argv (*__p___argv())
#define __argc (*__p___argc())
#define __wargv (*__p___wargv())

static int argret;
static int mainret=0;
static _startupinfo    startinfo;

_CRTIMP int* __cdecl __p__fmode();
int __cdecl _XcptFilter(_In_ unsigned long _ExceptionNum, _In_ struct _EXCEPTION_POINTERS * _ExceptionPtr);

/*!
\brief The code in mainCRTStartup that was executed before executing C
	   initializers was shifted in this function. Also this function is the
	   first thing that is executed in c init section.
*/
static int __cdecl pre_c_init(void)
{
	/*
	 * Set __app_type properly
	 */
#ifdef _WINMAIN_
	__set_app_type(_GUI_APP);
#else  /* _WINMAIN_ */
	__set_app_type(_CONSOLE_APP);
#endif  /* _WINMAIN_ */

	/*
	 * Mark this module as an EXE file so that atexit/_onexit
	 * will do the right thing when called, including for C++
	 * d-tors.
	 */
	__onexitbegin = __onexitend = (_PVFV *)(-1);

	/*
	 * Propagate the _fmode and _commode variables to the DLL
	 */
	*_IMP___FMODE = _fmode;
	*_IMP___COMMODE = _commode;

#ifdef _M_IX86
	/*
	 * Set the local copy of the Pentium FDIV adjustment flag
	 */

	// _adjust_fdiv = * _imp___adjust_fdiv;
#endif  /* _M_IX86 */

	/*
	 * Run the RTC initialization code for this DLL
	 */
#ifdef _RTC
	_RTC_Initialize();
#endif  /* _RTC */

	/*
	 * Call _setargv(), which will trigger a call to __setargv() if
	 * SETARGV.OBJ is linked with the EXE.  If SETARGV.OBJ is not
	 * linked with the EXE, a dummy _setargv() will be called.
	 */
//#ifdef WPRFLAG
//    _wsetargv();
//#else  /* WPRFLAG */
//   _setargv();
//#endif  /* WPRFLAG */

#if 0
	/* If the user has supplied a _matherr routine then set * __pusermatherr to point to it. */
	if ( !__defaultmatherr )
		__setusermatherr(_matherr);
#endif

#ifdef _M_IX86
	_controlfp(_PC_53, _MCW_PC);
#endif  /* _M_IX86 */

	return 0;
}

/*!
\brief The code in mainCRTStartup that was executed after C initializers and
before C++ initializers is shifted in this function. Also this funciton
is the first thing that is executed in C++ init section.
*/
static void __cdecl pre_cpp_init(void)
{
#ifdef _RTC
	atexit(_RTC_Terminate);
#endif  /* _RTC */

	/*
	 * Get the arguments for the call to main. Note this must be
	 * done explicitly, rather than as part of the dll's
	 * initialization, to implement optional expansion of wild
	 * card chars in filename args
	 */

	startinfo.newmode = 0; // _newmode;

#ifdef _UNICODE
	argret = __wgetmainargs(&__argc, &__wargv, &envp, 0 /* _dowildcard */, &startinfo);
#else  /* !_UNICODE */
//    argret = __getmainargs(__p___argc(), __p___argv(), &envp, 0 /* _dowildcard */, &startinfo);
	argret = __getmainargs(&__argc, &__argv, &envp, 0 /* _dowildcard */, &startinfo);
#endif  /* _UNICODE */

#ifndef _SYSCRT
	if (argret < 0)
		_amsg_exit(_RT_SPACEARG);
#endif  /* _SYSCRT */
}

extern HINSTANCE ghInstance;

//_CRTALLOC(".CRT$XIAA") static _PIFV pcinit = pre_c_init;
//_CRTALLOC(".CRT$XCAA") static _PVFV pcppinit = pre_cpp_init;

/*!
\brief This is the external wrapper to our startup code.

This routine can be one of several different names:
	Function:					User entry:
	mainCRTStartup(void)		main
	wmainCRTStartup(void)		wmain
	WinMainCRTStartup(void)		WinMain
	wWinMainCRTStartup(void)	wWinMain

  These routines do the C runtime initialization, call the appropriate
  user entry function, and handle termination cleanup.
  This function never returns even thought it has a return type.

\retval int Never returns, but does have an exit code.
*/

#ifdef _WINMAIN_

#ifdef _UNICODE
int __declspec(noinline) wWinMainCRTStartup(
#else  /* _UNICODE */
int __declspec(noinline) WinMainCRTStartup(
#endif  /* _UNICODE */

#else  /* _WINMAIN_ */

#ifdef _UNICODE
int __declspec(noinline) wmainCRTStartup(
#else  /* _UNICODE */
int __declspec(noinline) mainCRTStartup(
#endif  /* _UNICODE */

#endif  /* _WINMAIN_ */
		void
		)
{
	/*
	* The /GS security cookie must be initialized before any exception
	* handling targeting the current image is registered.  No function
	* using exception handling can be called in the current image until
	* after __security_init_cookie has been called.
	*/
	// __security_init_cookie() - You must compile with checking buffer overruns to off.

	//ghInstance = (HINSTANCE)&__ImageBase;

#ifdef _WINMAIN_
		TCHAR *lpszCommandLine;
		STARTUPINFO StartupInfo;
		BOOL inDoubleQuote=FALSE;

		__try {
		   /* Note: MSDN specifically notes that GetStartupInfo returns no error, and throws unspecified SEH if it fails, so
			  the very general exception handler below is appropriate. */
			GetStartupInfo( &StartupInfo );
		} __except(EXCEPTION_EXECUTE_HANDLER) {
			return 255;
		}
#endif  /* _WINMAIN_ */


		/*
		 * Guard the initialization code and the call to user's main, or
		 * WinMain, function in a __try/__except statement.
		 */

		__try
		{
		   /*
			 * Do runtime startup initializers.
			 *
			 * Note: the only possible entry we'll be executing here is for
			 * __lconv_init, pulled in from charmax.obj only if the EXE was
			 * compiled with -J.  All other .CRT$XI* initializers are only
			 * run as part of the CRT itself, and so for the CRT DLL model
			 * are not found in the EXE.  For that reason, we call _initterm,
			 * not _initterm_e, because __lconv_init will never return failure,
			 * and _initterm_e is not exported from the CRT DLL.
			 *
			 * Note further that, when using the CRT DLL, executing the
			 * .CRT$XI* initializers is only done for an EXE, not for a DLL
			 * using the CRT DLL.  That is to make sure the -J setting for
			 * the EXE is not overridden by that of any DLL.
			*/
			pre_c_init();
			_initterm( (_PVFV*)__xi_a, (_PVFV *)__xi_z );

			pre_cpp_init();
			// Do C++ constructors (initializers) specific to this EXE
			_initterm( __xc_a, __xc_z );

			/*
			 * If we have any dynamically initialized __declspec(thread)
			 * variables, then invoke their initialization for the primary
			 * thread used to start the process, by calling __dyn_tls_init
			 * through a callback defined in tlsdyn.obj.
			 */
			if (__dyn_tls_init_callback != NULL
				/* && LoPeIsNonwritableInCurrentImage((PBYTE)&__ImageBase,(PBYTE)&__dyn_tls_init_callback) */)
			{
				__dyn_tls_init_callback(NULL, DLL_THREAD_ATTACH, NULL);
			}

			/* Enable buffer count checking if linking against static lib */
#ifndef _DEBUG
			_CrtSetCheckCount(TRUE);
#endif

#ifdef _WINMAIN_
			/*
			 * Skip past program name (first token in command line).
			 * Check for and handle quoted program name.
			 */
#ifdef _UNICODE
			/* OS may not support "W" flavors */
			if (_wcmdln == NULL)
				return 255;
			lpszCommandLine = _wcmdln;
#else  /* _UNICODE */
			lpszCommandLine = _acmdln;
#endif  /* _UNICODE */

			while ( (*lpszCommandLine > SPACECHAR) || (*lpszCommandLine && inDoubleQuote) )
			{
				// Flip the count from 1 to 0 or 0 to 1 if current character is DOUBLEQUOTE.
				if (*lpszCommandLine==DQUOTECHAR) inDoubleQuote=!inDoubleQuote;
#ifdef _MBCS
				if (_ismbblead(*lpszCommandLine))
				{
					if (lpszCommandLine)
					{
						lpszCommandLine++;
					}
				}
#endif  /* _MBCS */
				++lpszCommandLine;
			}

			/*
			 * Skip past any white space preceding the second token.
			 */
			while ( *lpszCommandLine && (*lpszCommandLine <= SPACECHAR) )
			{
				lpszCommandLine++;
			}

#ifdef _UNICODE
			mainret = wWinMain(
#else   /* !_UNICODE */
			mainret = WinMain(
#endif  /* _UNICODE */
					   (HINSTANCE)&__ImageBase, NULL, lpszCommandLine,
					   StartupInfo.dwFlags & STARTF_USESHOWWINDOW ? StartupInfo.wShowWindow : SW_SHOWDEFAULT );
#else   /* _WINMAIN_ */

#ifdef _UNICODE
			__winitenv = envp;
			mainret = wmain(__argc, __wargv, envp);
#else   /* !_UNICODE */
			__initenv = envp;
			mainret = main(*__p___argc(), *__p___argv(), envp);
#endif  /* _UNICODE */

#endif  /* _WINMAIN_ */

			exit(mainret);
		}
		__except ( _XcptFilter(GetExceptionCode(), GetExceptionInformation()) )
		{
			// Should never reach here
			mainret = GetExceptionCode();
			// Just exit with exception code
			 _exit(mainret);
		} /* end of try - except */

		return mainret;
}

#endif  /* CRTDLL */
