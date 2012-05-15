// Lo-Overhead STL library - Lostl
//

#include "milan.h"
#include "lo_unew.h"

void* tmalloc (size_t n) /*throw (lo::std::bad_alloc)*/
{
    void* p = malloc (n);
    if (!p)
	throw lo::std::bad_alloc (n);
    return (p);
}
