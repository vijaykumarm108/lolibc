// Lo-Overhead STL library - Lostl
//
#include <stdafx.h>
#include <exception>
#include <stdexcept>
#include <string>
#include <istream>
#include <ostream>
#include <typeinfo>
#include <errno.h>
#include <new>
#include <stdarg.h>

namespace lo {
	/// Returns a dynamically allocated formatted string
	const char *dsprintf(const char *format, ... )
	{
		va_list argptr;
		va_start(argptr, format);
		char *str = nullptr;
		for( size_t	i = 128; ; i += 128 )
		{
			char *str = (char *)malloc(i);
			if(vsnprintf( str, i, format, argptr ) > 0)
				break;
			free(str);
		}
		return const_cast<const char *>(str);
	}
}

namespace std {
	/// Initializes the empty object. \p nBytes is the size of the attempted allocation.
	bad_alloc::bad_alloc (size_t nBytes) throw() : exception()
	{		
		_m_what = lo::dsprintf("%s %d bytes",typeid(this).name(),nBytes);
		_m_doFree = true;
	}

	logic_error::logic_error (const char* arg) throw() : exception (lo::dsprintf("%s:%s",typeid(logic_error).name(),arg))
	{
		_m_doFree = true;
	}

	logic_error::logic_error (const type_info &type, const char* arg) throw()
	{
		_m_what = lo::dsprintf("%s:%s",type.name(),arg);
		_m_doFree = true;
	}

	runtime_error::runtime_error (const char* arg) throw() : exception (lo::dsprintf("%s:%s",typeid(runtime_error).name(),arg))
	{
		_m_doFree = true;
	}

	runtime_error::runtime_error (const type_info &type, const char* arg) throw()
	{
		_m_what = lo::dsprintf("%s:%s",type.name(),arg);
		_m_doFree = true;
	}

}
