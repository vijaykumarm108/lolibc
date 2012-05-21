// loexcept - lolib exception handling

#include <stdafx.h>
#include <exception>

namespace lo
{
	/// Initializes the empty object. \p operation is the function that returned the error code.
	libc_exception::libc_exception (const char* operation, bool doFree ) throw() : exception(operation)
	{
		_m_doFree = doFree;
		//set_format (xfmt_LibcException);
	}

	/// Copies object \p v.
	libc_exception::libc_exception (const libc_exception& v) throw() : exception (v)
	{
		_m_what = strdup(v.what());
		_m_doFree = true;
	}

	/// Copies object \p v.
	const libc_exception& libc_exception::operator= (const libc_exception& v)
	{
		_m_what = strdup(v.what());
		_m_doFree = true;
		return (*this);
	}

	//----------------------------------------------------------------------

	/// Initializes the empty object. \p operation is the function that returned the error code.
	file_exception::file_exception (const char* operation, const char* filename) throw()
		: libc_exception((const char *)malloc( strlen(operation) + strlen(filename) + 2 ),true)
	{
		sprintf(const_cast<char *>(what()),"%s:%s",operation,filename);
	}

	stream_bounds_exception::stream_bounds_exception (const char* operation, const char* type, uoff_t offset, size_t expected, size_t remaining) throw()
		: libc_exception((const char *)malloc( strlen(operation) + strlen(type) + 60),true)
	{
		sprintf(const_cast<char *>(what()),"op=%s,type=%s,off=%u,expected=%u,remaining=%u",operation,type,offset,expected,remaining);
	}
}
