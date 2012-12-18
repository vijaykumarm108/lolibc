//  - Build Verification Tests
//

#include "stdafx.h"
#include <vector>

using namespace std;

static bool isInitialized = false;
class Test
{
public:
	Test()
	{
		isInitialized = true;
	}
	int m_id;
};

void BvtMemory()
{
	// Check the malloc and free functions
	size_t lastCheck = heapCheck(0);
	{
		void *d = malloc(1920);
		free(d);
	}
	heapCheck(lastCheck);
	{
		Test m_id;
		construct(&m_id);
	}
	heapCheck(lastCheck);
}
