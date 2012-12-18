//  - Build Verification Tests
//

#include "stdafx.h"

void BvtMsvcrt()
{
	// Check the malloc and free functions
	void *d = malloc(1920);
	free(d);
}
