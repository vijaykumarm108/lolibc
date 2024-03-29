#include <stdafx.h>
#include <istream>
#include <sstream>
#include <string>
#include <limits>
#include <stdio.h>
#include <stdarg.h>

namespace std {

	/// Creates an output string stream linked to the given memory area.
	ostringstream::ostringstream (void* p, size_t n) : ostream (), m_Buffer (), m_Flags (0), m_Width (0), m_Base (10), m_Precision (2)
	{
		exceptions (goodbit);
		link (p, n);
	}

	/// Creates an output string stream, initializing the buffer with v.
	ostringstream::ostringstream (const string& v) : ostream (), m_Buffer (v), m_Flags (0), m_Width (0), m_Base (10), m_Precision (2)
	{
		exceptions (goodbit);
		ostream::link (m_Buffer);
	}

	/// Copies \p s to the internal buffer.
	void ostringstream::str (const string& s)
	{
		m_Buffer = s;
		ostream::link (m_Buffer);
		SetPos (m_Buffer.size());
	}

	/// Writes a single character into the stream.
	void ostringstream::iwrite (uint8_t v)
	{
		if (remaining() >= 1 || overflow() >= 1)
		ostream::iwrite (v);
	}

	/// Writes the contents of \p buffer of \p size into the stream.
	ostringstream& ostringstream::write (const void* buffer, size_type sz)
	{
		const char* buf = (const char*) buffer;
		for (size_type bw = 0; (bw = minV(sz, remaining() ? remaining() : overflow(sz))); buf += bw, sz -= bw)
		ostream::write (buf, bw);
		return (*this);
	}

	/// Simple decimal encoding of \p n into \p fmt.
	char* ostringstream::encode_dec (char* fmt, uint32_t n) const
	{
		do {
			*fmt++ = '0' + n % 10;
		} while (n /= 10);
		return (fmt);
	}

	/// Generates a sprintf format string for the given type.
	void ostringstream::fmtstring (char* format, const char* typestr, bool bInteger) const
	{
		*format++ = '%';
		if (m_Width)
			format = encode_dec (format, m_Width);
		if (m_Flags & left)
			*format++ = '-';
		if (!bInteger) {
			*format++ = '.';
			format = encode_dec (format, m_Precision);
		}
		while (*typestr)
			*format++ = *typestr++;
		if (bInteger)
		{
			if (m_Base == 16)
				format[-1] = 'X';
			else if (m_Base == 8)
				format[-1] = 'o';
		} else {
			if (m_Flags & scientific)
				format[-1] = 'E';
		}
		*format = 0;
	}

	/// Writes \p v into the stream as utf8
	void ostringstream::iwrite (wchar_t v)
	{
		char buffer [8];
		*lo::utf8out(buffer) = v;
		write (buffer, lo::Utf8Bytes(v));
	}

	/// Writes value \p v into the stream as text.
	void ostringstream::iwrite (bool v)
	{
		static const char tf[2][8] = { "false", "true" };
		write (tf[v], 5 - v);
	}

	/// Equivalent to a vsprintf on the string.
	int ostringstream::vformat (const char* fmt, va_list args)
	{
		size_t rv, space;
		do {
			space = remaining();
			rv = vsnprintf (const_cast<char *>(ipos()), space, fmt, args);
			if (ssize_t(rv) < 0)
				rv = space;
		} while (rv >= space && rv < overflow(rv + 1));
		SetPos (pos() + minV (rv, space));
		return (int)(rv);
	}

	/// Equivalent to a sprintf on the string.
	int ostringstream::format (const char* fmt, ...)
	{
		va_list args;
		va_start (args, fmt);
		const int rv = vformat (fmt, args);
		va_end (args);
		return (rv);
	}

	/// Links to string \p l as re-sizable.
	void ostringstream::link (void* p, size_type n)
	{
		assert ((p || !n) && "The output string buffer must not be read-only");
		ostream::link (p, n);
		m_Buffer.link (p, n);
	}

	/// Attempts to create more output space. Returns remaining().
	ostringstream::size_type ostringstream::overflow (size_type n)
	{
		if (n > remaining())
		{
			const uoff_t oldPos (pos());
			m_Buffer.reserve (oldPos + n, false);
			m_Buffer.resize (oldPos + n);
			ostream::link (m_Buffer);
			SetPos (oldPos);
		}
		verify_remaining ("write", "text", n);
		return (remaining());
	}

}  // namespace std
