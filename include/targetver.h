#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.
#define _WIN32_WINNT	_WIN32_WINNT_WINXP
#define NTDDI_VERSION	NTDDI_WINXP
#include <SDKDDKVer.h>
#undef _WIN32_IE
#define _WIN32_IE		_WIN32_IE_IE60

