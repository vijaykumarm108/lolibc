// loexcept - lolib exception handling

#include <stdafx.h>
#include <exception>

namespace lo
{
	/// Initializes the empty object. \p operation is the function that returned the error code.
	libc_exception::libc_exception (const char* operation) throw()
	: exception(),
	  m_Errno (errno),
	  m_Operation (operation)
	{
		//set_format (xfmt_LibcException);
	}

	/// Copies object \p v.
	libc_exception::libc_exception (const libc_exception& v) throw()
	: exception (v),
	  m_Errno (v.m_Errno),
	  m_Operation (v.m_Operation)
	{
	}

	/// Copies object \p v.
	const libc_exception& libc_exception::operator= (const libc_exception& v)
	{
		m_Errno = v.m_Errno;
		m_Operation = v.m_Operation;
		return (*this);
	}

	//----------------------------------------------------------------------

	/// Initializes the empty object. \p operation is the function that returned the error code.
	file_exception::file_exception (const char* operation, const char* filename) throw()
	: libc_exception (operation)
	{
		memset (m_Filename, 0, _countof(m_Filename));
//		set_format (xfmt_FileException);
		if (filename)
		{
			strncpy (m_Filename, filename, _countof(m_Filename));
			m_Filename [_countof(m_Filename) - 1] = 0;
		}
	}

}
