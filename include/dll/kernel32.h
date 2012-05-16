#include <dll.h>
#include "ntoskrnl.h"

namespace lolibc
{
	class kernel32 : public dll
	{
	public:
		typedef ntoskrnl::RTL_CRITICAL_SECTION CRITICAL_SECTION;
		typedef ntoskrnl::PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;
		void		InitializeCriticalSection( LPCRITICAL_SECTION lpCriticalSection );
		const char *Name();
		int &counter();
	};
}
