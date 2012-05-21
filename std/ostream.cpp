
#include <stdafx.h>
#include <istream>
#include <ostream>
#include <string>
#include <algorithm>
#include <sstream>

namespace std {

	/// Checks that \p n bytes are available in the stream, or else throws.
	bool ostream::verify_remaining (const char* op, const char* type, size_t n)
	{
		const size_t rem = remaining();
		bool enough = n <= rem;
		if (!enough) overrun (op, type, (uint32_t)n, (uint32_t)pos(), (uint32_t)rem);
		return (enough);
	}

	/// Move the write pointer to \p newPos
	void ostream::seek (uoff_t newPos)
	{
		assert (newPos <= size());
		SetPos (newPos);
	}

	/// Sets the current write position to \p newPos
	void ostream::iseek (const_iterator newPos)
	{
		seek (distance (begin(), const_cast<iterator>(newPos)));
	}

	/// Sets the current write position to \p p based on \p d.
	void ostream::seekp (off_t p, seekdir d)
	{
		switch (d) {
		case beg:	seek (p); break;
		case cur:	seek (pos() + p); break;
		case ios_base::end:	seek (size() - p); break;
		}
	}

	/// Skips \p nBytes without writing anything.
	void ostream::skip (streamsize nBytes)
	{
		seek (pos() + nBytes);
	}

	/// Returns number of bytes remaining in the write buffer.
	streamsize ostream::remaining (void) const
	{
		return (size() - pos());
	}

	/// Returns \c true if the write pointer is aligned on \p grain
	bool ostream::aligned (streamsize grain) const
	{
		assert (uintptr_t(begin()) % grain == 0 && "Streams should be attached aligned at the maximum element grain to avoid bus errors.");
		return (pos() % grain == 0);
	}

	/// Returns the number of bytes to skip to be aligned on \p grain.
	streamsize ostream::align_size (streamsize grain) const
	{
		return (lo::Align (pos(), grain) - pos());
	}

	/// Writes \p n bytes from \p buffer.
	void ostream::write (const void* buffer, size_type n)
	{
		assert (remaining() >= n && "Buffer overrun. Check your stream size calculations.");
		memcpy (const_cast<void *>(reinterpret_cast<const void *>(ipos())), const_iterator(buffer), n);
		m_Pos += n;
	}

	/// Writes the contents of \p buf into the stream as a raw dump.
	void ostream::write (const cblocklink& buf)
	{
		write (buf.begin(), buf.size());
	}

	/// Swaps with \p os
	void ostream::swap (ostream& os)
	{
		blocklink::swap (os);
		::std::swap (m_Pos, os.m_Pos);
	}

}
