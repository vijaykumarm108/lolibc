#include <dll.h>

namespace lolibc
{
	class kernel32 : public dll
	{
	public:
		const char *Name();
		int &counter();
	};
}
