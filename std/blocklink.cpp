#include <stdafx.h>
#include <istream>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace lo {

	blocklink::iterator	blocklink::iat (size_type i)
	{
		assert (i <= size());
		return (begin() + i);
	}

	/// Shifts the data in the linked block from \p start to \p start + \p n.
	/// The contents of the uncovered bytes is undefined.
	void blocklink::insert (iterator start, size_type n)
	{
		assert (data() || !n);
		assert (cblocklink::begin() || !n);
		assert (start >= begin() && start + n <= end());
		rotate (start, end() - n, end());
	}

	/// Shifts the data in the linked block from \p start + \p n to \p start.
	/// The contents of the uncovered bytes is undefined.
	void blocklink::erase (iterator start, size_type n)
	{
		assert (data() || !n);
		assert (cblocklink::begin() || !n);
		assert (start >= begin() && start + n <= end());
		rotate (start, start + n, end());
	}

void	blocklink::link (const void* first, const void* last)
{
	link (first, std::distance (first, last));
}

void	blocklink::link (void* first, void* last)
{
	link (first, std::distance (first, last));
}

/// Reads the object from stream \p s
void blocklink::read (istream& is)
{
    written_size_type n = 0;
    is >> n;
    if (!is.verify_remaining ("read", "lo::std::blocklink", n))
	return;
    if (n > size())
	throw length_error ("blocklink can not increase the size of the linked storage for reading");
    resize (n);
    is.read (data(), n);
    is.align (alignof (n));
}

/// Fills the linked block with the given pattern.
/// \arg start   Offset at which to start filling the linked block
/// \arg p       Pointer to the pattern.
/// \arg elSize  Size of the pattern.
/// \arg elCount Number of times to write the pattern.
/// Total number of bytes written is \p elSize * \p elCount.
///
void blocklink::fill (iterator start, const void* p, size_type elSize, size_type elCount)
{
    assert (data() || !elCount || !elSize);
    assert (start >= begin() && start + elSize * elCount <= end());
    if (elSize == 1)
	fill_n<iterator,const uint8_t> (start, elCount, *reinterpret_cast<const uint8_t*>(p));
    else while (elCount--)
	start = copy_n (const_iterator(p), elSize, start);
}

}  // namespace lo
