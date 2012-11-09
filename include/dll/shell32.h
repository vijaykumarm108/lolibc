#pragma once
#include <dll.h>
#include "kernel32.h"

// All the kernel32 definitions go here
#ifdef __cplusplus
namespace lo { namespace kernel32 {	// This namespace contains all the definitions for the kernel32 functions
#endif

#ifdef __cplusplus
} }

using namespace lo::kernel32;

extern "C" {
#endif

//----------------------------------------- Function declarations -------------------------------------------
HINSTANCE WINAPI ShellExecuteW(__in_opt HWND hwnd, __in_opt LPCWSTR lpOperation, __in LPCWSTR lpFile, __in_opt LPCWSTR lpParameters, __in_opt LPCWSTR lpDirectory, __in INT nShowCmd);

#ifdef __cplusplus
}; // end extern "C"

namespace lo { namespace kernel32 {

} }

#endif
