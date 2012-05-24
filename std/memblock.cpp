#include <stdafx.h>
#include <istream>
#include "lo_block.h"
#include <algorithm>
#include <memory>
#include <fstream>
#include <errno.h>
#include <new>

using namespace std;

namespace lo {

block::block (void)			: blocklink (), m_Capacity (0) { }
block::block (const void* p, size_type n) : blocklink (), m_Capacity (0) { assign (p, n); }
block::block (size_type n)		: blocklink (), m_Capacity (0) { resize (n); }
block::block (const cblocklink& b)		: blocklink (), m_Capacity (0) { assign (b); }
block::block (const blocklink& b)		: blocklink (), m_Capacity (0) { assign (b); }
block::block (const block& b)		: blocklink (), m_Capacity (0) { assign (b); }
block::~block (void) throw()		{ deallocate(); }

void block::unlink (void) throw()
{
    m_Capacity = 0;
    blocklink::unlink();
}

/// resizes the block to \p newSize bytes, reallocating if necessary.
void block::resize (size_type newSize, bool bExact)
{
    if (m_Capacity < newSize + minimumFreeCapacity())
	reserve (newSize, bExact);
    blocklink::resize (newSize);
}

/// Frees internal data.
void block::deallocate (void) throw()
{
    if (m_Capacity) {
	assert (cdata() && "Internal error: space allocated, but the pointer is NULL");
	assert (data() && "Internal error: read-only block is marked as allocated space");
	free (data());
    }
    unlink();
}

/// Assumes control of the memory block \p p of size \p n.
/// The block assigned using this function will be freed in the destructor.
void block::manage (void* p, size_type n)
{
    assert (p || !n);
    assert (!m_Capacity && "Already managing something. deallocate or unlink first.");
    link (p, n);
    m_Capacity = n;
}

/// "Instantiate" a linked block by allocating and copying the linked data.
void block::copy_link (void)
{
    const pointer p ((pointer)begin());
    const size_t sz (size());
    if (is_linked())
	unlink();
    assign (p, sz);
}
 
/// Copies data from \p p, \p n.
void block::assign (const void* p, size_type n)
{
    assert ((p != (const void*) cdata() || size() == n) && "Self-assignment can not resize");
    resize (n);
    copy_n (pointer(p), n, begin());
}

/// \brief Reallocates internal block to hold at least \p newSize bytes.
///
/// Additional memory may be allocated, but for efficiency it is a very
/// good idea to call reserve before doing byte-by-byte edit operations.
/// The block size as returned by size() is not altered. reserve will not
/// reduce allocated memory. If you think you are wasting space, call
/// deallocate and start over. To avoid wasting space, use the block for
/// only one purpose, and try to get that purpose to use similar amounts
/// of memory on each iteration.
///
void block::reserve (size_type newSize, bool bExact)
{
    if ((newSize += minimumFreeCapacity()) <= m_Capacity)
	return;
    pointer oldBlock (is_linked() ? NULL : data());
    const size_t alignedSize (Align (newSize, 64));
    if (!bExact)
	newSize = alignedSize;
    pointer newBlock = (pointer) realloc (oldBlock, newSize);
    if (!newBlock)
		throw std::bad_alloc (newSize);
    if (!oldBlock & (cdata() != NULL))
	copy_n (cdata(), minV (size() + 1, newSize), newBlock);
    link (newBlock, size());
    m_Capacity = newSize;
}

/// Shifts the data in the linked block from \p start to \p start + \p n.
block::iterator block::insert (iterator start, size_type n)
{
    const uoff_t ip = start - begin();
    assert (ip <= size());
    resize (size() + n, false);
    blocklink::insert (iat(ip), n);
    return (iat (ip));
}

/// Shifts the data in the linked block from \p start + \p n to \p start.
block::iterator block::erase (iterator start, size_type n)
{
    const uoff_t ep = start - begin();
    assert (ep + n <= size());
    blocklink::erase (start, n);
    blocklink::resize (size() - n);
    return (iat (ep));
}

/// Reads the object from stream \p s
void block::read (istream& is)
{
    written_size_type n = 0;
    is >> n;
    if (!is.verify_remaining ("read", "lo::std::block", n))
	return;
    resize (n);
    is.read (data(), writable_size());
    is.align (alignof (n));
}

/// Reads the entire file \p "filename".
void block::read_file (const char* filename)
{
    fstream f;
    f.exceptions (fstream::allbadbits);
    f.open (filename, fstream::in);
    const off_t fsize (f.size());
    reserve (fsize);
    f.read (data(), fsize);
    f.close();
    resize (fsize);
}

block::size_type block::minimumFreeCapacity (void) const throw() { return (0); }

} // namespace std
