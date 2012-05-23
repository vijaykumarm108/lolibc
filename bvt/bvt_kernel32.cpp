#include <stdafx.h>
namespace test {
#include <dll/kernel32.h>
#undef WINBASEAPI
}
#include <windows.h>

void bvt_kernel32()
{
	// Tests our sizes of types vs. what windows has...
	BVT(sizeof(CRITICAL_SECTION)!=sizeof(test::CRITICAL_SECTION));
}
