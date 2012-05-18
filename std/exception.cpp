// Lo-Overhead STL library - Lostl
//
#include <stdafx.h>
#include <exception>
#include <string>
#include <istream>
#include <ostream>
#include "lo_uspecial.h"
#include <errno.h>
#include <new>

#if HAVE_CXXABI_H && WANT_NAME_DEMANGLING
extern "C" char* __cxa_demangle (const char* mangled_name, char* output_buffer, size_t* length, int* status);
#endif

namespace std {

	/// Initializes the empty object. \p nBytes is the size of the attempted allocation.
	bad_alloc::bad_alloc (size_t nBytes) throw() : exception(),  m_nBytesRequested (nBytes)
	{
	   // set_format (xfmt_BadAlloc);
	}

}
