#pragma once
#include "lolibbase.h"
#include <stdint.h>
#include <dll.h>

namespace lo
{
	class ntoskrnl : public dll
	{
	public:

		///  Doubly linked list structure.  Can be used as either a list head, or as link words.
		typedef struct _LIST_ENTRY {
			struct _LIST_ENTRY *Flink;
			struct _LIST_ENTRY *Blink;
		} LIST_ENTRY, *PLIST_ENTRY;

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
			void *		OwningThread;        // from the thread's ClientId->UniqueThread
			long		RecursionCount;
			uintptr_t	SpinCount;        // force size on 64-bit systems when packed
		} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

#pragma pack(pop)

		// Functions
	private:
		const char *Name();
		int &counter();
	};

}
