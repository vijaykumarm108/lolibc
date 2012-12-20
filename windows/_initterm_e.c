/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
#define SPECIAL_CRTEXE
#include "lomsvcrt.h"

//#pragma comment(linker, "/include:__security_cookie")
#pragma comment(linker, "/merge:.CRT=.rdata")
UINT_PTR __security_cookie;

/*!
\brief 
Walk a table of function pointers in the same way as _initterm, but here the functions return an error code.  If an error is returned, it
will be a nonzero value equal to one of the _RT_* codes.

@param[in]	pfbegin	pointer to the beginning of the table (first valid entry).
@param[in]	*pfend	pointer to the end of the table (after last valid entry).

@return int No return value

\notes  This routine must be exported in the CRT DLL model so that the client EXE and client DLL(s) can call it.

\exceptions
	If either pfbegin or pfend is NULL, or invalid, all bets are off!
*/
int __cdecl _initterm_e ( _PIFV * pfbegin, _PIFV * pfend )
{
	int ret = 0;

	/*
	* walk the table of function pointers from the bottom up, until
	* the end is encountered.  Do not skip the first entry.  The initial
	* value of pfbegin points to the first valid entry.  Do not try to
	* execute what pfend points to.  Only entries before pfend are valid.
	*/
	while ( pfbegin < pfend  && ret == 0)
	{
		/*
		* if current table entry is non-NULL, call through it.
		*/
		if ( *pfbegin != NULL )
			ret = (**pfbegin)();
		++pfbegin;
	}

	return ret;
}


/* pointers to initialization sections */
_CRTALLOC(".CRT$XIA") _PIFV __xi_a[] = { NULL };
_CRTALLOC(".CRT$XIZ") _PIFV __xi_z[] = { NULL };    /* C initializers */
_CRTALLOC(".CRT$XCA") _PVFV __xc_a[] = { NULL };
_CRTALLOC(".CRT$XCZ") _PVFV __xc_z[] = { NULL };    /* C++ initializers */

