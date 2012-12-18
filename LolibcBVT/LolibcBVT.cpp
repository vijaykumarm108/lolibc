// LolibcBVT - Build Verification Tests
//

#include "stdafx.h"
#include <string>


extern "C" _CRTIMP intptr_t _get_heap_handle( void );

size_t heapCheck(size_t lastCheck)
{
	PROCESS_HEAP_ENTRY		entry = {0};
	HANDLE heap = (HANDLE)_get_heap_handle();
	size_t size = 0;
	size_t count = 0;
	while( HeapWalk(heap,&entry) )
	{
		size += entry.cbData;
		++count;
	}
	if(lastCheck && size!=lastCheck)
		throw std::exception("Heap corrupted.");
	return size;
}

void BvtMsvcrt();
void BvtMemory();
void BvtString();
void BvtVector();
int main(int argc, char* argv[])
{
	printf("Build Verification Tests\n");
	size_t heapUsed = 0;
	heapUsed = heapCheck(0);
	BvtMsvcrt();			// MSVCRT basic library checks
	heapCheck(heapUsed);
	BvtMemory();
	BvtString();			// String checks.
	heapCheck(heapUsed);
	BvtVector();			// Vector checks.
	heapCheck(heapUsed);
	std::string str = "Tests pass successfully, press any key to continue";
	printf(str.c_str());
	getchar();
	return 0;
}

