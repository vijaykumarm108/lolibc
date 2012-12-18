//  - Build Verification Tests
//

#include "stdafx.h"
#include <vector>
#include <string>

using namespace std;

class Test
{
public:
	Test() : m_id(0) {}
	Test(int id) : m_id(id) {}
	int m_id;
};

void BvtVector()
{
	// Create an empty string vector
	size_t lastCheck = heapCheck(0);
	{
		vector<string>		str;
	}
	heapCheck(lastCheck);
	// Simple int vector
	{
		vector<int>		ivector;
		ivector.push_back(1);
		ivector.push_back(2);
		ivector.push_back(3);
	}
	heapCheck(lastCheck);
	// Simple push of a string.
	{
		vector<string>		str;
		str.push_back(string("Hello"));
		string &str2 = str.back();
		if(str2!="Hello")
			throw std::exception("Hello failed");
	}
	heapCheck(lastCheck);
	// Push of a Test class
	{
		vector<Test>	test;
		test.push_back(Test(1));
		test.push_back(Test(2));
		test.push_back(Test(3));
	}
	heapCheck(lastCheck);
}
