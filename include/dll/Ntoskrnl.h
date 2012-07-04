#pragma once
#include "lolibbase.h"
#include <dll.h>

#ifdef __cplusplus
namespace lo { namespace ntoskrnl {
#endif

	typedef struct _LIST_ENTRY {
		struct _LIST_ENTRY *Flink;
		struct _LIST_ENTRY *Blink;
	} LIST_ENTRY, *PLIST_ENTRY;

	struct _RTL_CRITICAL_SECTION;

	typedef struct _RTL_CRITICAL_SECTION_DEBUG {
		uint16_t		Type;
		uint16_t		CreatorBackTraceIndex;
		struct _RTL_CRITICAL_SECTION *CriticalSection;
		LIST_ENTRY		ProcessLocksList;
		uint32_t		EntryCount;
		uint32_t		ContentionCount;
		uint32_t		Flags;
		uint16_t		CreatorBackTraceIndexHigh;
		uint16_t		SpareWORD;
	} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG, RTL_RESOURCE_DEBUG, *PRTL_RESOURCE_DEBUG;

#pragma pack(push, 8)

	typedef struct _RTL_CRITICAL_SECTION {
		PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
		//  The following three fields control entering and exiting the critical
		//  section for the resource
		long		LockCount;
		void *		LockSemaphore;
		void *		OwningThread;		// from the thread's ClientId->UniqueThread
		long		RecursionCount;
		uintptr_t	SpinCount;			// force size on 64-bit systems when packed
	} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

#pragma pack(pop)

	typedef struct _FILETIME {
		uint32_t dwLowDateTime;
		uint32_t dwHighDateTime;
	} FILETIME, *PFILETIME, *LPFILETIME;

#ifndef WIN32_FIND_DATAW
	typedef struct _WIN32_FIND_DATAW {
		uint32_t	dwFileAttributes;
		FILETIME	ftCreationTime;
		FILETIME	ftLastAccessTime;
		FILETIME	ftLastWriteTime;
		uint32_t	nFileSizeHigh;
		uint32_t	nFileSizeLow;
		uint32_t	dwReserved0;
		uint32_t	dwReserved1;
		wchar_t		cFileName[ 260 ];
		wchar_t		cAlternateFileName[ 14 ];
	} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;
#endif

/// Service Types (Bit Mask)
	static const uint32_t SERVICE_KERNEL_DRIVER = 0x00000001;
	static const uint32_t SERVICE_FILE_SYSTEM_DRIVER = 0x00000002;
	static const uint32_t SERVICE_ADAPTER = 0x00000004;
	static const uint32_t SERVICE_RECOGNIZER_DRIVER = 0x00000008;
	static const uint32_t SERVICE_DRIVER = (SERVICE_KERNEL_DRIVER | SERVICE_FILE_SYSTEM_DRIVER | SERVICE_RECOGNIZER_DRIVER);

	static const uint32_t SERVICE_WIN32_OWN_PROCESS = 0x00000010;
	static const uint32_t SERVICE_WIN32_SHARE_PROCESS = 0x00000020;
	static const uint32_t SERVICE_WIN32 = (SERVICE_WIN32_OWN_PROCESS | SERVICE_WIN32_SHARE_PROCESS);
	static const uint32_t SERVICE_INTERACTIVE_PROCESS = 0x00000100;
	static const uint32_t SERVICE_TYPE_ALL = (SERVICE_WIN32 | SERVICE_ADAPTER | SERVICE_DRIVER | SERVICE_INTERACTIVE_PROCESS);

/// Service Start Type
	static const uint32_t SERVICE_BOOT_START     = 0x00000000;
	static const uint32_t SERVICE_SYSTEM_START   = 0x00000001;
	static const uint32_t SERVICE_AUTO_START     = 0x00000002;
	static const uint32_t SERVICE_DEMAND_START   = 0x00000003;
	static const uint32_t SERVICE_DISABLED       = 0x00000004;

/// Error control type
	static const uint32_t SERVICE_ERROR_IGNORE   = 0x00000000;
	static const uint32_t SERVICE_ERROR_NORMAL   = 0x00000001;
	static const uint32_t SERVICE_ERROR_SEVERE   = 0x00000002;
	static const uint32_t SERVICE_ERROR_CRITICAL = 0x00000003;

#ifdef __cplusplus
} } // end namespace lo::ntoskrnl

using namespace lo::ntoskrnl;

extern "C" {
#endif // __cplusplus

	//----------------------------------------- Function declarations -------------------------------------------

#ifdef __cplusplus
};
#endif / __cplusplus
