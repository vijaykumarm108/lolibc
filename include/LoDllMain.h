
#include "lomsvcrt.h"
#include <stdlib.h>
#include <windows.h>

#ifdef _M_IX86
/* The local copy of the Pentium FDIV adjustment flag and the address of the flag in MSVCRT*.DLL. */
extern int _adjust_fdiv;
extern int * _imp___adjust_fdiv;
#endif  /* _M_IX86 */

// Located in _intterm_e.c
extern void __cdecl _initterm(_PVFV *, _PVFV *);

// Initializers
extern _CRTALLOC(".CRT$XIA") _PIFV __xi_a[];
extern _CRTALLOC(".CRT$XIZ") _PIFV __xi_z[];    /* C initializers */
extern _CRTALLOC(".CRT$XCA") _PVFV __xc_a[];
extern _CRTALLOC(".CRT$XCZ") _PVFV __xc_z[];    /* C++ initializers */

const PIMAGE_TLS_CALLBACK __dyn_tls_init_callback;

/** Flag set if and only if _CRTDLL_INIT was called with DLL_PROCESS_ATTACH */
static int __proc_attached = 0;


/**	Pointers to beginning and end of the table of function pointers manipulated	by _onexit()/atexit().  The atexit/_onexit code is shared for both EXE's and
DLL's but different behavior is required.  These values are initialized to 0 by default and will be set to point to a malloc-ed memory block to mark
this module as an DLL.	NOTE - the pointers are stored encoded. */
extern _PVFV *__onexitbegin;
extern _PVFV *__onexitend;

// User routine DllMain is called on all notifications
extern BOOL WINAPI DllMain( HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved );


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
