// Lo-Overhead STL library - Lostl
//
#include "stdafx.h"
#include "lostlbase.h"
#include "new"

void* tmalloc (size_t n) /*throw (lo::std::bad_alloc)*/
{
    void* p = malloc (n);
    if (!p)
		throw std::bad_alloc (n);
    return (p);
}
