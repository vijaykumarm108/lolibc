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

void* operator new (size_t size, void* ptr) throw()
{
	return ptr;
}

void operator delete (void* ptr, void* voidptr2) throw()
{
	// Don't free this block, because we never allocated it.
}
