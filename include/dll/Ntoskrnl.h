#include <dll.h>

namespace lolibc
{
	class ntoskrnl : public dll
	{
	public:
		// Types
		typedef char CHAR;
		typedef short SHORT;
		typedef long LONG;
		typedef int INT;
		typedef void *HANDLE;
		typedef HANDLE *PHANDLE;

		typedef signed char         INT8, *PINT8;
		typedef signed short        INT16, *PINT16;
		typedef signed int          INT32, *PINT32;
		typedef signed __int64      INT64, *PINT64;
		typedef unsigned char       UINT8, *PUINT8;
		typedef unsigned short      UINT16, *PUINT16;
		typedef unsigned int        UINT32, *PUINT32;
		typedef unsigned __int64    UINT64, *PUINT64;
		// The following types are guaranteed to be signed and 32 bits wide.
		typedef signed int LONG32, *PLONG32;
		// The following types are guaranteed to be unsigned and 32 bits wide.
		typedef unsigned int ULONG32, *PULONG32;
		typedef unsigned int DWORD32, *PDWORD32;

#if !defined(_W64)
#if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
#define _W64 __w64
#else
#define _W64
#endif
#endif
#if defined(_WIN64)
		typedef __int64 INT_PTR, *PINT_PTR;
		typedef unsigned __int64 UINT_PTR, *PUINT_PTR;

		typedef __int64 LONG_PTR, *PLONG_PTR;
		typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;

		#define __int3264   __int64

#else
		typedef _W64 int INT_PTR, *PINT_PTR;
		typedef _W64 unsigned int UINT_PTR, *PUINT_PTR;
		typedef _W64 long LONG_PTR, *PLONG_PTR;
		typedef _W64 unsigned long ULONG_PTR, *PULONG_PTR;
		#define __int3264   __int32
#endif

		
		typedef struct _RTL_CRITICAL_SECTION_DEBUG {
			WORD   Type;
			WORD   CreatorBackTraceIndex;
			struct _RTL_CRITICAL_SECTION *CriticalSection;
			LIST_ENTRY ProcessLocksList;
			DWORD EntryCount;
			DWORD ContentionCount;
			DWORD Flags;
			WORD   CreatorBackTraceIndexHigh;
			WORD   SpareWORD  ;
		} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG, RTL_RESOURCE_DEBUG, *PRTL_RESOURCE_DEBUG;

#pragma pack(push, 8)

		typedef struct _RTL_CRITICAL_SECTION {
			PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
			//  The following three fields control entering and exiting the critical
			//  section for the resource
			LONG LockCount;
			LONG RecursionCount;
			HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
			HANDLE LockSemaphore;
			ULONG_PTR SpinCount;        // force size on 64-bit systems when packed
		} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

#pragma pack(pop)

		// Functions
	private:
		const char *Name();
		int &counter();
	};

}
