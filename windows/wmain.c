/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
/*!
\file wmain.c
brief Initialization for console EXE using MSVCRT.DLL, wchar_t version

The is is the startup/shutdown wrapper for console applications which
uses wmain().  It handles startup and shutdown for C/C++ applications
of the C/C++ language library.

*/

#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef UNICODE
#define UNICODE
#endif

#undef _MBCS /* UNICODE not _MBCS */

#include "main.c"

