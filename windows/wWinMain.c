/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
/*!
\file wWinMain.c
\brief Initialization for Windows EXE using MSVCRT.DLL, wchar_t version

The is is the startup/shutdown wrapper for Windows applications which
uses wWinMain().  It handles startup and shutdown for C/C++ applications
of the C/C++ language library.

*/

#define _WINMAIN_
#include "wmain.c"

