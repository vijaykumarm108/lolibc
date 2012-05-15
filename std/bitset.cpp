/* bitset.cpp for lolibc */

#include "../include/bitset"

namespace std {

	/// Copies bits from \p v of size \p n into \p buf as MSB "1011001..." LSB
	/// If \p buf is too small, MSB bits will be truncated.
	void convert_to_bitstring (const bitset_value_type* v, size_t n, string& buf)
	{
		string::iterator stri = buf.end();
		for (size_t i = 0; i < n && stri > buf.begin(); ++ i)
		for (bitset_value_type b = 1; b && stri > buf.begin(); b <<= 1)
			*--stri = (v[i] & b) ? '1' : '0';
	}

	/// Copies bits from \p buf as MSB "1011001..." LSB into \p v of size \p n.
	void convert_from_bitstring (const string& buf, bitset_value_type* v, size_t n)
	{
		string::const_iterator stri = buf.end();
		for (size_t i = 0; i < n; ++ i)
		{
			for (bitset_value_type b = 1; b; b <<= 1)
			{
				if (stri == buf.begin() || *--stri == '0')
				v[i] &= ~b;
				else
				v[i] |= b;
			}
		}
	}

	bitset::bitset (value_type v = 0)
	{
		fill_n (m_Bits, s_nWords, 0);
		m_Bits[0] = v;
	}

	bitset::bitset (const string& buf)
	{
		convert_from_bitstring (buf, m_Bits, s_nWords);
	}

	bool		bitset::any (void) const
	{
		value_type sum = 0; foreach (const_iterator, i, *this) sum |= *i; return (sum != 0);
	}

	value_type	bitset::at (uoff_t first, uoff_t last) const
	{
		assert (size_t (distance (first, last)) <= s_WordBits && "Bit ranges must be 32 bits or smaller");
		assert (first / s_WordBits == last / s_WordBits && "Bit ranges can not cross dword (4 byte) boundary");
		return ((BitRef(first) >> (first % s_WordBits)) & BitMask(value_type,distance(first, last)));
	}

	value_type&		bitset:BitRef (uoff_t n)
	{
		assert (n < Size); return (m_Bits [n / s_WordBits]);
	}

	value_type		bitset:BitRef (uoff_t n) const
	{
		assert (n < Size); return (m_Bits [n / s_WordBits]);
	}

	size_t		bitset::count (void) const
	{
		size_t sum = 0;
		foreach (const_iterator, i, *this)
			sum += popcount(*i); return (sum);
	}

	void		bitset::flip (void)
	{
		transform (begin(), end(), begin(), bitwise_not<value_type>());
	}

	value_type	bitset::Mask (uoff_t n) const
	{
		assert (n < Size);
		return (1 << (n % s_WordBits));
	}

	bool		bitset::operator== (rcself_t v) const
	{
		return (s_nWords == 1 ? (m_Bits[0] == v.m_Bits[0]) : equal (begin(), end(), v.begin()));
	}

	bitset		bitset::operator& (rcself_t v) const
	{
		bitset<Size> result;
		transform (begin(), end(), v.begin(), result.begin(), bitwise_and<value_type>());
		return (result);
	}
	bitset		bitset::operator| (rcself_t v) const
	{
		bitset<Size> result;
		transform (begin(), end(), v.begin(), result.begin(), bitwise_or<value_type>());
		return (result);
	}
	bitset		bitset::operator^ (rcself_t v) const
	{
		bitset<Size> result;
		transform (begin(), end(), v.begin(), result.begin(), bitwise_xor<value_type>());
		return (result);
	}
	rcself_t	bitset::operator&= (rcself_t v)
	{
		transform (begin(), end(), v.begin(), begin(), bitwise_and<value_type>());
		return (*this);
	}
	rcself_t	bitset::operator|= (rcself_t v)
	{
		transform (begin(), end(), v.begin(), begin(), bitwise_or<value_type>());
		return (*this);
	}

	rcself_t	bitset::operator^= (rcself_t v)
	{
		transform (begin(), end(), v.begin(), begin(), bitwise_xor<value_type>());
		return (*this);
	}

	bitset		bitset::operator~ (void) const
	{
		bitset rv (*this);
		rv.flip();
		return (rv);
	}

	void		bitset::set (uoff_t n, bool val = true)
	{
		value_type& br (BitRef (n));
		const value_type mask (Mask (n));
		const value_type bOn (br | mask), bOff (br & ~mask);
		br = val ? bOn : bOff;
	}

	void		bitset::set (uoff_t first, uoff_t DebugArg(last), value_type v)
	{
		assert (size_t (distance (first, last)) <= s_WordBits && "Bit ranges must be 32 bits or smaller");
		assert (first / s_WordBits == last / s_WordBits && "Bit ranges can not cross dword (4 byte) boundary");
		assert ((v & BitMask(value_type,distance(first,last))) == v && "The value is too large to fit in the given bit range");
		BitRef(first) |= v << (first % s_WordBits);
	}

	string	bitset::to_string (void) const
	{
		string rv (Size, '0');
		convert_to_bitstring (m_Bits, s_nWords, rv);
		return (rv);
	}


}
