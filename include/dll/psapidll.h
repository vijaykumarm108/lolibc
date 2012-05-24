#pragma once
#include "lolibbase.h"
#include <dll.h>

#ifdef __cplusplus
namespace lo { namespace psapidll {
#endif

	// PSAPIDLL structures
	static const uint32_t PROCESS_TERMINATE					=(0x0001);  
	static const uint32_t PROCESS_CREATE_THREAD				=(0x0002);  
	static const uint32_t PROCESS_SET_SESSIONID				=(0x0004);  
	static const uint32_t PROCESS_VM_OPERATION				=(0x0008);  
	static const uint32_t PROCESS_VM_READ					=(0x0010);  
	static const uint32_t PROCESS_VM_WRITE					=(0x0020);  
	static const uint32_t PROCESS_DUP_HANDLE				=(0x0040);  
	static const uint32_t PROCESS_CREATE_PROCESS			=(0x0080);  
	static const uint32_t PROCESS_SET_QUOTA					=(0x0100);  
	static const uint32_t PROCESS_SET_INFORMATION			=(0x0200);  
	static const uint32_t PROCESS_QUERY_INFORMATION			=(0x0400);  
	static const uint32_t PROCESS_SUSPEND_RESUME			=(0x0800);  
	static const uint32_t PROCESS_QUERY_LIMITED_INFORMATION =(0x1000);  
	static const uint32_t PROCESS_ALL_ACCESS				=(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFF);


#ifdef __cplusplus
} } // end namespace lo::psapidll

using namespace lo::psapidll;

extern "C" {
#endif // __cplusplus

	//----------------------------------------- Function declarations -------------------------------------------
	uint32_t WINAPI GetProcessImageFileNameW( __in intptr_t hProcess, __out wchar_t * lpImageFileName, __in uintptr_t nSize	);

#ifdef __cplusplus
};
#endif / __cplusplus
