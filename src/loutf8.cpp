// loexcept - lolib exception handling

#include <stdafx.h>
#include <lo_utf8.h>

namespace lo
{


	/// Returns the number of bytes required to UTF-8 encode \p v.
	size_t Utf8Bytes (wchar_t v)
	{
		if ((uint32_t) v < 128)
			return (1);
		size_t n;
#if __i386__ || __x86_64__
		uint32_t r = 0;
		asm ("bsr\t%2, %%eax\n\t"
			"add\t$4, %0\n\t"
			"div\t%3":"=a"(n),"+d"(r):"r"(v),"c"(5));
#else
		static const uint32_t c_Bounds[7] = { 0x0000007F, 0x000007FF, 0x0000FFFF, 0x001FFFFF, 0x03FFFFFF, 0x7FFFFFFF, 0xFFFFFFFF };
		for (n = 0; c_Bounds[n++] < uint32_t(v););
#endif
		return (n);
	}

	/// Measures the size of a wchar_t array in UTF-8 encoding.
	size_t Utf8Bytes (const wchar_t* first, const wchar_t* last)
	{
		size_t bc = 0;
		for (; first < last; ++first)
			bc += Utf8Bytes(*first);
		return (bc);
	}

	/// Returns the number of bytes in a UTF-8 sequence that starts with \p c.
	size_t Utf8SequenceBytes (wchar_t c)	// a wchar_t to keep c in a full register
	{
		// Count the leading bits. Header bits are 1 * nBytes followed by a 0.
		//	0 - single byte character. Take 7 bits (0xFF >> 1)
		//	1 - error, in the middle of the character. Take 6 bits (0xFF >> 2)
		//	    so you will keep reading invalid entries until you hit the next character.
		//	>2 - multibyte character. Take remaining bits, and get the next bytes.
		// All errors are ignored, since the user can not correct them.
		//
		wchar_t mask = 0x80;
		size_t nBytes = 0;
		for (; c & mask; ++nBytes)
			mask >>= 1;
		return (nBytes ? nBytes : 1); // A sequence is always at least 1 byte.
	}

}
