

#include <stdafx.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdarg.h>
#include <Windows.h>

using namespace lo;

namespace std {
//const uoff_t string::npos;

	/// Assigns itself the value of string \p s
	string::string (const string& s)
	: block ((s.size()+1) & (s.is_linked()-1))	// Allocate with terminator if not linked (can't call virtuals from base ctor)
	{
		if (s.is_linked())
			relink (s.c_str(), s.size());
		else
		{
			copy_n (s.begin(), size(), begin());
			relink (begin(), size()-1);	// --m_Size
		}
	}

	/// Links to \p s
	string::string (const_pointer s) : block ()
	{
		if (!s) s = "";
		relink (s, strlen(s));
	}

	string::string(pointer s) : block(strlen(s)+1)
	{
		strcpy(begin(),s);
		relink(begin(),strlen(s));
	}

	/// Creates a string of length \p n filled with character \p c.
	string::string (size_type n, value_type c)
	: block (n+1)	// because base ctor can't call virtuals of this class
	{
		relink (begin(), size()-1);	// --m_Size
		fill_n (begin(), n, c);
		at(n) = 0;
	}

	string::string (const_wpointer s ) : block (WideCharToMultiByte(CP_UTF8,0,s,-1,NULL,0,NULL,NULL))
	{
		WideCharToMultiByte(CP_UTF8,0,s,-1,begin(),(int)size(),NULL,NULL);
		relink(begin(),size()-1);
	}

	size_type		string::capacity (void) const
	{
		size_type c (block::capacity()); return (c - !!c);
	}

	/// Resize the string to \p n characters. New space contents is undefined.
	void string::resize (size_type n)
	{
		if (!(n | block::capacity()))
		return (relink ("",0));
		block::resize (n);
		at(n) = 0;
	}

	/// Assigns itself the value of string \p s
	void string::assign (const_pointer s)
	{
		if (!s) s = "";
		assign (s, strlen (s));
	}

	/// Assigns itself the value of string \p s of length \p len.
	void string::assign (const_pointer s, size_type len)
	{
		while (len && s[len - 1] == 0)
		-- len;
		resize (len);
		copy_n (s, len, begin());
	}

	/// Appends to itself the value of string \p s of length \p len.
	void string::append (const_pointer s)
	{
		if (!s) s = "";
		append (s, strlen (s));
	}

	/// Appends to itself the value of string \p s of length \p len.
	void string::append (const_pointer s, size_type len)
	{
		while (len && s[len - 1] == 0)
		-- len;
		resize (size() + len);
		copy_n (s, len, end() - len);
	}

	/// Appends to itself \p n characters of value \p c.
	void string::append (size_type n, value_type c)
	{
		resize (size() + n);
		fill_n (end() - n, n, c);
	}

	/// Copies into itself at offset \p start, the value of string \p p of length \p n.
	string::size_type string::copyto (pointer p, size_type n, const_iterator start) const
	{
		assert (p && n);
		if (!start)
		start = begin();
		const size_type btc = minV(n-1, size());
		copy_n (start, btc, p);
		p[btc] = 0;
		return (btc+1);
	}

	/// Returns comparison value regarding string \p s.
	/// The return value is:
	/// \li 1 if this string is greater (by value, not length) than string \p s
	/// \li 0 if this string is equal to string \p s
	/// \li -1 if this string is less than string \p s
	///
	/*static*/ int string::compare (const_iterator first1, const_iterator last1, const_iterator first2, const_iterator last2)
	{
		assert (first1 <= last1 && (first2 <= last2 || !last2) && "Negative ranges result in memory allocation errors.");
		const size_type len1 = distance (first1, last1), len2 = distance (first2, last2);
		const int rvbylen = sign (int(len1 - len2));
		int rv = memcmp (first1, first2, minV (len1, len2));
		return (rv ? rv : rvbylen);
	}

	/// Returns true if this string is equal to string \p s.
	bool string::operator== (const_pointer s) const
	{
		if (!s) s = "";
		return (size() == strlen(s) && 0 == memcmp (c_str(), s, size()));
	}

	/// Returns the beginning of character \p i.
	string::const_iterator string::wiat (uoff_t i) const
	{
		utf8in_iterator<string::const_iterator> cfinder (begin());
		cfinder += i;
		return (cfinder.base());
	}

	/// Inserts wide character \p c at \p ipo \p n times as a UTF-8 string.
	///
	/// \p ipo is a byte position, not a character position, and is intended
	/// to be obtained from one of the find functions. Generally you are not
	/// able to know the character position in a localized string; different
	/// languages will have different character counts, so use find instead.
	///
	void string::insert (const uoff_t ipo, wchar_t c, size_type n)
	{
		iterator ip (iat(ipo));
		ip = iterator (block::insert (block::iterator(ip), n * Utf8Bytes(c)));
		fill_n (lo::utf8out (ip), n, c);
		*end() = 0;
	}

	/// Inserts sequence of wide characters at \p ipo (byte position from a find call)
	void string::insert (const uoff_t ipo, const wchar_t* first, const wchar_t* last, const size_type n)
	{
		iterator ip (iat(ipo));
		size_type nti = distance (first, last), bti = 0;
		for (uoff_t i = 0; i < nti; ++ i)
		bti += Utf8Bytes(first[i]);
		ip = iterator (block::insert (block::iterator(ip), n * bti));
		utf8out_iterator<string::iterator> uout (lo::utf8out (ip));
		for (uoff_t j = 0; j < n; ++ j)
		for (uoff_t k = 0; k < nti; ++ k, ++ uout)
			*uout = first[k];
		*end() = 0;
	}

	/// Inserts character \p c into this string at \p start.
	string::iterator string::insert (iterator start, const_reference c, size_type n)
	{
		start = iterator (block::insert (block::iterator(start), n));
		fill_n (start, n, c);
		*end() = 0;
		return (start);
	}

	/// Inserts \p count instances of string \p s at offset \p start.
	string::iterator string::insert (iterator start, const_pointer s, size_type n)
	{
		if (!s) s = "";
		return (insert (start, s, s + strlen(s), n));
	}

	/// Inserts [first,last] \p n times.
	string::iterator string::insert (iterator start, const_pointer first, const_pointer last, size_type n)
	{
		assert (first <= last);
		assert (begin() <= start && end() >= start);
		assert ((first < begin() || first >= end() || size() + abs_distance(first,last) < capacity()) && "Insertion of self with autoresize is not supported");
		start = iterator (block::insert (block::iterator(start), distance(first, last) * n));
		fill (block::iterator(start), first, distance(first, last), n);
		*end() = 0;
		return (start);
	}

	/// Erases \p size bytes at \p ep.
	string::iterator string::erase (iterator ep, size_type n)
	{
		string::iterator rv = (string::iterator)block::erase (block::iterator(ep), n);
		*end() = 0;
		return (rv);
	}

	/// Erases \p n bytes at byte offset \p epo.
	void string::erase (uoff_t epo, size_type n)
	{
		erase (iat(epo), n);
	}

	/// Replaces range [\p start, \p start + \p len] with string \p s.
	void string::replace (iterator first, iterator last, const_pointer s)
	{
		if (!s) s = "";
		replace (first, last, s, s + strlen(s));
	}

	/// Replaces range [\p start, \p start + \p len] with \p count instances of string \p s.
	void string::replace (iterator first, iterator last, const_pointer i1, const_pointer i2, size_type n)
	{
		assert (first <= last);
		assert (n || distance(first, last));
		assert (first >= begin() && first <= end() && last >= first && last <= end());
		assert ((i1 < begin() || i1 >= end() || abs_distance(i1,i2) * n + size() < capacity()) && "Replacement by self can not autoresize");
		const size_type bte = distance(first, last), bti = distance(i1, i2) * n;
		if (bti < bte)
		first = iterator (block::erase (block::iterator(first), bte - bti));
		else if (bte < bti)
		first = iterator (block::insert (block::iterator(first), bti - bte));
		fill (block::iterator(first), i1, distance(i1, i2), n);
		*end() = 0;
	}

	/// Returns the offset of the first occurence of \p c after \p pos.
	uoff_t string::find (const_reference c, uoff_t pos) const
	{
		const_iterator found = ::std::find (iat(pos), end(), c);
		return (found < end() ? (uoff_t) distance(begin(),found) : npos);
	}

	/// Returns the offset of the first occurence of substring \p s of length \p n after \p pos.
	uoff_t string::find (const string& s, uoff_t pos) const
	{
		if (s.empty() || s.size() > size() - pos)
		return (npos);
		const uoff_t endi = s.size() - 1;
		const_reference endchar = s[endi];
		uoff_t lastPos = endi;
		while (lastPos-- && s[lastPos] != endchar) ;
		const size_type skip = endi - lastPos;
		const_iterator i = iat(pos) + endi;
		for (; i < end() && (i = ::std::find (i, end(), endchar)) < end(); i += skip)
		if (memcmp (i - endi, s.c_str(), s.size()) == 0)
			return (distance (begin(), i) - endi);
		return (npos);
	}

	/// Returns the offset of the last occurence of character \p c before \p pos.
	uoff_t string::rfind (const_reference c, uoff_t pos) const
	{
		for (int i = (int)minV(pos,size()-1); i >= 0; --i)
		if (at((uoff_t)i) == c)
			return ((uoff_t)i);
		return (npos);
	}

	/// Returns the offset of the last occurence of substring \p s of size \p n before \p pos.
	uoff_t string::rfind (const string& s, uoff_t pos) const
	{
		const_iterator d = iat(pos) - 1;
		const_iterator sp = begin() + s.size() - 1;
		const_iterator m = s.end() - 1;
		for (long int i = 0; d > sp && size_type(i) < s.size(); -- d)
		for (i = 0; size_type(i) < s.size(); ++ i)
			if (m[-i] != d[-i])
			break;
		return (d > sp ? (uoff_t) distance (begin(), d + 2 - s.size()) : npos);
	}

	/// Returns the offset of the first occurence of one of characters in \p s of size \p n after \p pos.
	uoff_t string::find_first_of (const string& s, uoff_t pos) const
	{
		for (uoff_t i = minV(pos,size()); i < size(); ++ i)
		if (s.find (at(i)) != npos)
			return (i);
		return (npos);
	}

	/// Returns the offset of the first occurrence of one of characters not in \p s of size \p n after \p pos.
	uoff_t string::find_first_not_of (const string& s, uoff_t pos) const
	{
		for (uoff_t i = minV(pos,size()); i < size(); ++ i)
		if (s.find (at(i)) == npos)
			return (i);
		return (npos);
	}

	/// Returns the offset of the last occurrence of one of characters in \p s of size \p n before \p pos.
	uoff_t string::find_last_of (const string& s, uoff_t pos) const
	{
		for (int i = (int)minV(pos,size()-1); i >= 0; -- i)
		if (s.find (at(i)) != npos)
			return (i);
		return (npos);
	}

	size_t	string::find_last_of ( char c, size_t pos ) const
	{
		const char *result =  strrchr ( c_str(), (int)c );
		return (result == nullptr) ? npos : (size_t)(result - c_str());
	}

	size_t	string::find_last_of ( const char *s, size_t pos ) const
	{
		return find_last_of(string(s),pos);
	}

	/// Returns the offset of the last occurrence of one of characters not in \p s of size \p n before \p pos.
	uoff_t string::find_last_not_of (const string& s, uoff_t pos) const
	{
		for (int i = (int)minV(pos,size()-1); i >= 0; -- i)
		if (s.find (at(i)) == npos)
			return (i);
		return (npos);
	}

	/// Equivalent to a vsprintf on the string.
	int string::vformat (const char* fmt, va_list args)
	{
		size_t rv = size();
		do {
			reserve (rv);
			rv = vsnprintf (data(), block::capacity(), fmt, args);
			rv = minV (rv, block::capacity());
		} while (rv > capacity());
		resize (minV (rv, capacity()));
		return (int)(rv);
	}

	/// Equivalent to a sprintf on the string.
	int string::format (const char* fmt, ...)
	{
		va_list args;
		va_start (args, fmt);
		const int rv = vformat (fmt, args);
		va_end (args);
		return (rv);
	}

	/// Returns the number of bytes required to write this object to a stream.
	size_t string::stream_size (void) const
	{
		return (size_t)(Utf8Bytes((wchar_t)size()) + size());
	}

	/// Reads the object from stream \p os
	void string::read (istream& is)
	{
		char szbuf [8];
		is >> szbuf[0];
		size_t szsz (Utf8SequenceBytes (szbuf[0]) - 1), n = 0;
		if (!is.verify_remaining ("read", "lo::std::string", szsz)) return;
		is.read (szbuf + 1, szsz);
		n = *lo::utf8in(szbuf);
		if (!is.verify_remaining ("read", "lo::std::string", n)) return;
		resize (n);
		is.read (data(), size());
	}

	/// Writes the object to stream \p os
	void string::write (ostream& os) const
	{
		const written_size_type sz ((written_size_type)size());
		assert (sz == size() && "No support for writing strings larger than 4G");

		char szbuf [8];
		utf8out_iterator<char*> szout (szbuf);
		*szout = sz;
		size_t szsz = distance (szbuf, szout.base());

		if (!os.verify_remaining ("write", "lo::std::string", szsz + sz)) return;
		os.write (szbuf, szsz);
		os.write (cdata(), sz);
	}

	/// Returns a hash value for [first, last)
	/*static*/ hashvalue_t string::hash (const char* first, const char* last)
	{
		hashvalue_t h = 0;
		// This has the bits flowing into each other from both sides of the number
		for (; first < last; ++ first)
		h = *first + ((h << 7) | (h >> (BitsInType(hashvalue_t) - 7)));
		return (h);
	}

	/// Assigns itself the value of string \p s
	string::string (const cblocklink& s) : block ()
	{
		assign (const_iterator (s.begin()), s.size());
	}

	/// Assigns itself a [o,o+n] substring of \p s.
	string::string (const string& s, uoff_t o, size_type n) : block()
	{
		assign (s, o, n);
	}

	/// Copies the value of \p s of length \p len into itself.
	string::string (const_pointer s, size_type len) : block ()
	{
		assign (s, len);
	}

	/// Copies into itself the string data between \p s1 and \p s2
	string::string (const_pointer s1, const_pointer s2) : block ()
	{
		assert (s1 <= s2 && "Negative ranges result in memory allocation errors.");
		assign (s1, s2);
	}

	/// Returns the pointer to the first character.
	string::operator const string::value_type* (void) const
	{
		assert ((!end() || !*end()) && "This string is linked to data that is not 0-terminated. This may cause serious security problems. Please assign the data instead of linking.");
		return (begin());
	}

	/// Returns the pointer to the first character.
	string::operator string::value_type* (void)
	{
		assert ((end() && !*end()) && "This string is linked to data that is not 0-terminated. This may cause serious security problems. Please assign the data instead of linking.");
		return (begin());
	}

	/// Concatenates itself with \p s
	string string::operator+ (const string& s) const
	{
		string result (*this);
		result += s;
		return (result);
	}

	/// Resize to \p n and fill new entries with \p c
	void string::resize (size_type n, value_type c)
	{
		const size_type oldn = size();
		resize (n);
		fill_n (iat(oldn), maxV(ssize_t(n-oldn),0), c);
	}

	string::size_type string::minimumFreeCapacity (void) const throw() { return (1); }

	//------------------------------ wstring helper functions ---------------------

	/// Converts the UTF-8 string in \p bufferIn to a widechar string
	void wstring::init(const char *bufferIn)
	{
		if(bufferIn == nullptr)
			buffer = nullptr;
		else
		{
			int length = MultiByteToWideChar(CP_UTF8, 0, bufferIn, -1, NULL, 0 );
			if( length > 0 )
			{
				buffer = reinterpret_cast<wchar_t *>(malloc(length*sizeof(wchar_t)));
				MultiByteToWideChar(CP_UTF8, 0, bufferIn, -1, buffer, length );
			}
			else
				buffer = nullptr;
		}
	}

	wstring::~wstring()
	{
		if( buffer != nullptr )
			free(buffer);
	}

	/// Converts the wstring to a \p text UTF-8 string
	void wstring::toString( string& text)
	{
		int length = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, NULL, 0, NULL, NULL );
		if( length > 0 )
		{
			char *temp=reinterpret_cast<char *>(malloc(length));
			WideCharToMultiByte(CP_UTF8, 0, buffer, -1, temp, length, NULL, NULL );
			text.assign(temp);
			free( temp );
		}
		else
			text.clear();
	}

} // namespace std
