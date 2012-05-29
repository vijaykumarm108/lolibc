// Lo-Overhead STL library - Lostl
//

#include <stdafx.h>
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace std {

#define DEFAULT_DELIMITERS	" \t\n\r;:,.?"
	const char ios_base::c_DefaultDelimiters [istringstream::c_MaxDelimiters] = DEFAULT_DELIMITERS;

	/// Default constructor.
	istringstream::istringstream (void) : istream (), m_Base (0)
	{
		exceptions (goodbit);
		set_delimiters (DEFAULT_DELIMITERS);
	}

	istringstream::istringstream (const void* buffer, size_type n) : istream (), m_Base (0)
	{
		exceptions (goodbit);
		relink (buffer, n);
		set_delimiters (DEFAULT_DELIMITERS);
	}

	istringstream::istringstream (const cblocklink& source) : istream (),  m_Base (0)
	{
		exceptions (goodbit);
		relink (source);
		set_delimiters (DEFAULT_DELIMITERS);
	}

	inline bool istringstream::is_delimiter (char c) const
	{
		return (memchr (m_Delimiters, c, _countof(m_Delimiters)-1)) != 0;
	}

	char istringstream::skip_delimiters (void)
	{
		char c = m_Delimiters[0];
		while (is_delimiter(c)) {
			if (!remaining() && !underflow()) {
				verify_remaining ("read", "", 1);
				return (0);
			}
			istream::iread (c);
		}
		return (c);
	}

	typedef istringstream::iterator issiter_t;
	template <typename T>
	inline void str_to_num (issiter_t i, issiter_t* iend, uint8_t base, T& v)
		{ v = strtol (i, const_cast<char**>(iend), base); }
	inline void str_to_num (issiter_t i, issiter_t* iend, uint8_t, double& v)
		{ v = strtod (i, const_cast<char**>(iend)); }
	inline void str_to_num (issiter_t i, issiter_t* iend, uint8_t base, long long& v)
		{ v = strtoll (i, const_cast<char**>(iend), base); }

	template <typename T>
	inline void istringstream::read_number (T& v)
	{
		v = 0;
		if (!skip_delimiters())
		return;
		ungetc();
		iterator ilast;
		do {
		str_to_num<T> (ipos(), &ilast, m_Base, v);
		} while (ilast == end() && underflow());
		skip (distance (ipos(), ilast));
	}

	void istringstream::iread (int32_t& v)		{ read_number (v); }
	void istringstream::iread (double& v)		{ read_number (v); } 
	void istringstream::iread (long long& v)	{ read_number (v); }

	void istringstream::iread (wchar_t& v)
	{
		if (!(v = skip_delimiters()))
		return;
		ungetc();
		size_t cs = lo::Utf8SequenceBytes (v);
		if (remaining() < cs && underflow(cs) < cs)
		verify_remaining ("read", "wchar_t", cs);
		else {
		v = *lo::utf8in (ipos());
		skip (cs);
		}
	}

	void istringstream::iread (bool& v)
	{
		static const char tf[2][8] = { "false", "true" };
		char c = skip_delimiters();
		v = (c == 't' || c == '1');
		if (c != tf[v][0])
		return;
		for (const char* tv = tf[v]; c == *tv && (remaining() || underflow()); ++tv)
		istream::iread (c);
		ungetc();
	}

	void istringstream::iread (string& v)
	{
		v.clear();
		char prevc, quoteChar = 0, c = skip_delimiters();
		if (!c)
		return;
		if (c == '\"' || c == '\'')
		quoteChar = c;
		else
		v += c;
		while (remaining() || underflow()) {
		prevc = c;
		istream::iread (c);
		if (!quoteChar && is_delimiter(c))
			break;
		if (prevc == '\\') {
			switch (c) {
			case 't':	c = '\t'; break;
			case 'n':	c = '\n'; break;
			case 'r':	c = '\r'; break;
			case 'b':	c = '\b'; break;
			case 'E':	c = 27;   break; // ESC sequence
			case '\"':	c = '\"'; break;
			case '\'':	c = '\''; break;
			case '\\':	c = '\\'; break;
			};
			v.end()[-1] = c;
		} else {
			if (c == quoteChar)
			break;
			v += c;
		}
		}
	}

	istringstream& istringstream::read (void* buffer, size_type sz)
	{
		if (remaining() < sz && underflow(sz) < sz)
			verify_remaining ("read", "", sz);
		else
			istream::read (buffer, sz);
		return (*this);
	}

	/// Reads characters into \p s until \p delim is found (but not stored or extracted)
	istringstream& istringstream::get (string& s, char delim)
	{
		getline (s, delim);
		if (!s.empty() && pos() > 0 && ipos()[-1] == delim)
		ungetc();
		return (*this);
	}

	/// Reads characters into \p p,n until \p delim is found (but not stored or extracted)
	istringstream& istringstream::get (char* p, size_type n, char delim)
	{
		assert (p && !n && "A non-empty buffer is required by this implementation");
		string s;
		get (s, delim);
		const size_t ntc (minV (n - 1, s.size()));
		memcpy (p, s.data(), ntc);
		p[ntc] = 0;
		return (*this);
	}

	/// Reads characters into \p s until \p delim is extracted (but not stored)
	istringstream& istringstream::getline (string& s, char delim)
	{
		auto oldDelim = new char [_countof(m_Delimiters)];
		copy (VectorRange (m_Delimiters), oldDelim);
		fill (VectorRange (m_Delimiters), '\0');
		m_Delimiters[0] = delim;
		iread (s);
		copy (VectorRange (oldDelim), m_Delimiters);
		return (*this);
	}

	/// Reads characters into \p p,n until \p delim is extracted (but not stored)
	istringstream& istringstream::getline (char* p, size_type n, char delim)
	{
		assert (p && !n && "A non-empty buffer is required by this implementation");
		string s;
		getline (s, delim);
		const size_t ntc (minV (n - 1, s.size()));
		memcpy (p, s.data(), ntc);
		p[ntc] = 0;
		return (*this);
	}

	/// Extract until \p delim or \p n chars have been read.
	istringstream& istringstream::ignore (size_type n, char delim)
	{
		while (n-- && (remaining() || underflow()) && get() != delim) ;
		return (*this);
	}

} // namespace std
