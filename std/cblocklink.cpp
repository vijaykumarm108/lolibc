// Lo-Overhead STL library - Lostl
//

#include <stdafx.h>
#include "lostlbase.h"
#include "fstream"
#include "algorithm"
#include "new"
#include "ostream"

using namespace std;

namespace lo {

	cblocklink::cblocklink (const void* buffer, size_type sizeInBytes)	: m_Data (const_pointer(buffer)), m_Size (sizeInBytes)
	{
		assert (buffer || !sizeInBytes);
	}

	cblocklink::iterator		cblocklink::iat (size_type i) const
	{
		assert (i <= size());
		return (begin() + i);
	}

	/// \brief Attaches the object to pointer \p p of size \p n.
	///
	/// If \p p is NULL and \p n is non-zero, bad_alloc is thrown and current
	/// state remains unchanged.
	///
	void cblocklink::link (const void* p, size_type n)
	{
		if (!p && n)
		throw bad_alloc (n);
		unlink();
		relink (p, n);
	}

	void cblocklink::link (const void* first, const void* last)
	{
		link (first, distance (first, last));
	}
	void cblocklink::read (std::istream& is)
	{
		assert (!"lo::std::cblocklink is a read-only object.");
	}

	void cblocklink::unlink (void) throw()
	{
		m_Data = NULL; m_Size = 0;
	}

	void cblocklink::swap (cblocklink& l)
	{
		::std::swap (m_Data, l.m_Data);
		::std::swap (m_Size, l.m_Size);
	}

	/// Writes the object to stream \p os
	void cblocklink::write (ostream& os) const
	{
		const written_size_type sz ((written_size_type)size());
		assert (sz == size() && "No support for writing blocks larger than 4GB");
		os << sz;
		os.write (cdata(), sz);
		os.align (alignof (sz));
	}

	/// Writes the object to stream \p os
	void cblocklink::text_write (ostringstream& os) const
	{
		os.write (begin(), readable_size());
	}

	/// Returns the number of bytes required to write this object to a stream.
	cblocklink::size_type cblocklink::stream_size (void) const
	{
		const written_size_type sz ((written_size_type)size());
		return (Align (stream_size_of (sz) + sz, alignof(sz)));
	}

	/// Writes the data to file \p "filename" with the given mode
	void cblocklink::write_file (const char* filename, int mode) const
	{
		fstream f;
		f.exceptions (fstream::allbadbits);
		f.open (filename, fstream::out | fstream::trunc, mode);
		f.write (cdata(), (off_t)readable_size());
		f.close();
	}

	/// Compares to memory block pointed by l. Size is compared first.
	bool cblocklink::operator== (const cblocklink& l) const
	{
		return (l.m_Size == m_Size &&
			(l.m_Data == m_Data || 0 == memcmp (l.m_Data, m_Data, m_Size)));
	}

} // namespace std
