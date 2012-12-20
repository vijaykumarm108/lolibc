//  - Build Verification Tests
//

#include "stdafx.h"
#include <string>

using namespace std;

void BvtString()
{
	string		str("Static string test");

	string str2 = "Assignment check";

	string str3 = string("hello") + " world " + "here";
	if(str3 != "hello world here")
		throw std::exception("lol");
}
