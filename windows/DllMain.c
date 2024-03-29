/*
 * Copyright � 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
/*!
\file DllMain.c
\brief CRT initialization for a DLL using the MSVCRT* model of C run-time

This module contains the initialization entry point for the C run-time
stub in this DLL.  All C run-time code is located in the C Run-Time
Library DLL "MSVCRT.DLL", except for a little bit of start-up code in
the EXE, and this code in each DLL.  This code is necessary to invoke
the C++ constructors for the C++ code in this DLL.

This entry point should either be specified as the DLL initialization
entry point, or else it must be called by the DLL initialization entry
point of the DLL with the same arguments that the entry point receives.
*/

#include "lomsvcrt.h"
#include <stdlib.h>
#include <windows.h>
//#define _DECL_DLLMAIN   /* enable prototypes for DllMain and _CRT_INIT */
//#include <process.h>
//#include <dbgint.h>
//#include <rtcapi.h>
//#include <locale.h>

#ifdef _M_IX86
/* The local copy of the Pentium FDIV adjustment flag and the address of the flag in MSVCRT*.DLL. */
extern int _adjust_fdiv;
extern int * _imp___adjust_fdiv;
#endif  /* _M_IX86 */

/// routine in DLL to do initialization (in this case, C++ constructors)

extern void __cdecl _initterm(_PVFV *, _PVFV *);
#ifndef _SYSCRT
extern int __cdecl _initterm_e(_PIFV *, _PIFV *);
#endif  /* _SYSCRT */

/*
 * pointers to initialization sections
 */

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
 * flag set if and only if _CRTDLL_INIT was called with DLL_PROCESS_ATTACH
 */
static int __proc_attached = 0;


/*
 * Pointers to beginning and end of the table of function pointers manipulated
 * by _onexit()/atexit().  The atexit/_onexit code is shared for both EXE's and
 * DLL's but different behavior is required.  These values are initialized to
 * 0 by default and will be set to point to a malloc-ed memory block to mark
 * this module as an DLL.
 * NOTE - the pointers are stored encoded.
 */

extern _PVFV *__onexitbegin;
extern _PVFV *__onexitend;


// User routine DllMain is called on all notifications
extern BOOL WINAPI DllMain( HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved );

/*
 * _pRawDllMain MUST be an extern const variable, which will be aliased to
 * _pDefaultRawDllMain if no real user definition is present, thanks to the
 * alternate name directive.
 */

extern BOOL (WINAPI * const _pRawDllMain)(HANDLE, DWORD, LPVOID);
extern BOOL (WINAPI * const _pDefaultRawDllMain)(HANDLE, DWORD, LPVOID) = NULL;
#if defined (_M_IX86)
#pragma comment(linker, "/alternatename:__pRawDllMain=__pDefaultRawDllMain")
#elif defined (_M_IA64) || defined (_M_AMD64)
#pragma comment(linker, "/alternatename:_pRawDllMain=_pDefaultRawDllMain")
#else  /* defined (_M_IA64) || defined (_M_AMD64) */
#error Unsupported platform
#endif  /* defined (_M_IA64) || defined (_M_AMD64) */

/*!
\brief The code in mainCRTStartup that was executed before executing C
initializers was shifted in this function. Also this function is the
first thing that is executed in c init section.
*/
static int __cdecl pre_c_init(void)
{
	_PVFV * onexitbegin;

	// Create the onexit table.
	onexitbegin = (_PVFV *)malloc(32 * sizeof(_PVFV));
	__onexitend = __onexitbegin = (_PVFV *)onexitbegin;

	if ( onexitbegin == NULL )
	{
		// Cannot allocate minimal required size. generate failure to load DLL.
		return 1;
	}

	*onexitbegin = (_PVFV) NULL;

	// Run the RTC initialization code for this DLL.
#ifdef _RTC
	_RTC_Initialize();
	atexit(_RTC_Terminate);
#endif  /* _RTC */
#ifndef _SYSCRT
		/* Register __clean_type_info_names so that we clean up all the type_info.names that are allocated */
//    atexit(__clean_type_info_names);
#endif  /* _SYSCRT */

	return 0;
}

_CRTALLOC(".CRT$XIAA") static _PIFV pcinit = pre_c_init;

extern HINSTANCE ghInstance;

const PIMAGE_TLS_CALLBACK __dyn_tls_init_callback;	// Thread local storage variable.

void _CRT_INIT()
{
#ifdef _M_IX86
	// Set the local copy of the Pentium FDIV adjustment flag
	_adjust_fdiv = * _imp___adjust_fdiv;
#endif  /* _M_IX86 */

	_initterm_e( __xi_a, __xi_z );	// Invoke C constructors
	_initterm( __xc_a, __xc_z );	// Invoke C++ constructors
}

/** Do _onexit or atexit() terminators (if there are any).
These terminators MUST be executed in reverse order (LIFO)!
\note  This code assumes that __onexitbegin points to the first valid onexit()
entry and that __onexitend points past the last valid entry. If __onexitbegin == __onexitend, the
table is empty and there are no
routines to call.
*/
void _CRT_TERM()
{
	_PVFV * onexitbegin = (_PVFV *)__onexitbegin;
	if (onexitbegin)
	{
		_PVFV * onexitend = (_PVFV *)__onexitend;
		_PVFV function_to_call = NULL;

		// Save the start and end for later comparison
		_PVFV * onexitbegin_saved = onexitbegin;
		_PVFV * onexitend_saved = onexitend;

		while (1)
		{
			_PVFV * onexitbegin_new = NULL;
			_PVFV * onexitend_new = NULL;

			/* find the last valid function pointer to call. */
			while (--onexitend >= onexitbegin && (*onexitend == NULL || *onexitend == NULL))
			{
				/* keep going backwards. */
			}

			if (onexitend < onexitbegin)
			{
				// There are no more valid entries in the list, we are done.
				break;
			}

			// Cache the function to call.
			function_to_call = (_PVFV)*onexitend;

			// Mark the function pointer as visited.
			*onexitend = (_PVFV)NULL;

			// Call the function, which can eventually change __onexitbegin and __onexitend.
			(*function_to_call)();

			onexitbegin_new = (_PVFV *)__onexitbegin;
			onexitend_new = (_PVFV *)__onexitend;

			if ( ( onexitbegin_saved != onexitbegin_new ) || ( onexitend_saved != onexitend_new ) )
			{
				// Reset only if either start or end has changed
				onexitbegin = onexitbegin_saved = onexitbegin_new;
				onexitend = onexitend_saved = onexitend_new;
			}
		}
		// Free the block holding onexit table to avoid memory leaks.  Also zero the ptr variables so that they are clearly cleaned up.
		free( onexitbegin );
		__onexitbegin = __onexitend = (_PVFV *)0;
	}
}

BOOL WINAPI _DllMainCRTStartup( HANDLE  hDllHandle, DWORD dwReason, LPVOID lpreserved )
{
	BOOL retcode = TRUE;

	if(__proc_attached==0)
	{
		__proc_attached = 1;
		ghInstance = (HINSTANCE)hDllHandle;
		_CRT_INIT();
	}
	// Call the user's DllMain
	if(dwReason==DLL_THREAD_ATTACH)
	{
		if(__dyn_tls_init_callback!=0)
			__dyn_tls_init_callback( hDllHandle, DLL_THREAD_ATTACH, lpreserved );
		// Enable buffer count checking if linking against static lib
		_CrtSetCheckCount(TRUE);
	}
	retcode = DllMain( hDllHandle, dwReason, lpreserved );
	if(dwReason==DLL_THREAD_DETACH)
	{

	}
	if(dwReason==DLL_PROCESS_DETACH)
	{
		_CRT_TERM();
		__proc_attached = 0;
	}

	return retcode;
}
