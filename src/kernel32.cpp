#include <stdafx.h>
#include <dll/kernel32.h>
#include <windows.h>

namespace lo
{
	static int _counter = 0;

	const char *kernel32::Name()
	{
		return "kernel32";
	}

	int &kernel32::counter()
	{
		return _counter;
	}
}


