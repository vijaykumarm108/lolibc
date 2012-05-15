// LoMsvcrtTestExe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <lo_string.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Hello world\n");
	lo::std::string str = "Press any key to continue";
	printf(str.c_str());
	getchar();
	return 0;
}

