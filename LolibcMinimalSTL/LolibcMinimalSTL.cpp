// LoMsvcrtTestExe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

int main(int argc, char* argv[])
{
	printf("Hello world.  Size of string=%d\n",sizeof(std::string));
	std::string str = "Press any key to continue";
	printf(str.c_str());
	getchar();
	return 0;
}

