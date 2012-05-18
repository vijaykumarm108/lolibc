/* matrix helper class */
#pragma once

#include "tuple"
#include "sys/types.h"

namespace lo {

	/// \brief A two-dimensional array of NX*NY elements of type T.
	template <size_t NX, size_t NY, typename T>
	class matrix : public tuple<NX*NY,T> {
	public:
		typedef tuple<NX,T>							row_type;
		typedef tuple<NY,T>							column_type;
		typedef tuple<NX*NY,T>						tuple_type;
		typedef typename tuple_type::value_type		value_type;
		typedef typename tuple_type::size_type		size_type;
		typedef typename tuple_type::pointer		pointer;
		typedef typename tuple_type::const_pointer	const_pointer;
		typedef typename tuple_type::reference		reference;
		typedef typename tuple_type::const_reference	const_reference;
		typedef typename tuple_type::iterator		iterator;
		typedef typename tuple_type::const_iterator	const_iterator;
		typedef typename tuple_type::range_t		range_t;
		typedef typename tuple_type::const_range_t	const_range_t;
		typedef typename tuple_type::reverse_iterator	reverse_iterator;
		typedef typename tuple_type::const_reverse_iterator	const_reverse_iterator;
	public:
		inline					matrix (void)			{ }
		inline const_iterator	at (size_type i) const		{ return (matrix::begin() + i * NX); }
		inline iterator			at (size_type i)		{ return (matrix::begin() + i * NX); }
		inline column_type		column (size_type c) const;
		inline size_type		columns (void) const		{ return (NX); }
		template <typename T2>
		inline const matrix&	operator= (const matrix<NX,NY,T2>& src)	{ tuple_type::operator= (src); return (*this); }
		inline const matrix&	operator= (const matrix<NX,NY,T>& src)	{ tuple_type::operator= (src); return (*this); }
		inline const matrix&	operator+= (const_reference v)			{ tuple_type::operator+= (v); return (*this); }
		inline const matrix&	operator-= (const_reference v)			{ tuple_type::operator-= (v); return (*this); }
		inline const matrix&	operator*= (const_reference v)			{ tuple_type::operator*= (v); return (*this); }
		inline const matrix&	operator/= (const_reference v)			{ tuple_type::operator/= (v); return (*this); }
		inline const matrix		operator+ (const_reference v) const		{ matrix result (*this); result += v; return (result); }
		inline const matrix		operator- (const_reference v) const		{ matrix result (*this); result -= v; return (result); }
		inline const matrix		operator* (const_reference v) const		{ matrix result (*this); result *= v; return (result); }
		inline const matrix		operator/ (const_reference v) const		{ matrix result (*this); result /= v; return (result); }
		inline const_iterator	operator[] (size_type i) const	{ return (at (i)); }
		inline iterator			operator[] (size_type i)	{ return (at (i)); }
		inline row_type			row (size_type r) const		{ return (row_type (at (r))); }
		inline size_type		rows (void) const		{ return (NY); }
	};

	template <size_t NX, size_t NY, typename T>
	inline typename matrix<NX,NY,T>::column_type matrix<NX,NY,T>::column (size_type c) const
	{
		column_type result;
		const_iterator src (matrix::begin() + c);
		iterator dest (result.begin());
		for (uoff_t i = 0; i < NY; ++ i, ++ dest, src += NX)
		*dest = *src;
		return (result);
	}

	/// \brief Creates an identity matrix in \p m
	/// \ingroup NumericAlgorithms
	template <size_t NX, size_t NY, typename T>
	void load_identity (matrix<NX,NY,T>& m)
	{
		fill_n (m.begin(), NX * NY, 0);
		for (typename matrix<NX,NY,T>::iterator i = m.begin(); i < m.end(); i += NX + 1)
		*i = 1;
	}

	/// \brief Multiplies two matrices
	/// \ingroup NumericAlgorithms
	template <size_t NX, size_t NY, typename T>
	matrix<NY,NY,T> operator* (const matrix<NX,NY,T>& m1, const matrix<NY,NX,T>& m2)
	{
		matrix<NY,NY,T> mr;
		for (uoff_t ry = 0; ry < NY; ++ ry)
		{
			for (uoff_t rx = 0; rx < NY; ++ rx)
			{
				T dpv (0);
				for (uoff_t x = 0; x < NX; ++ x)
				dpv += m1[ry][x] * m2[x][rx];
				mr[ry][rx] = dpv;
			}
		}
		return (mr);
	}

	/// \brief Transforms vector \p t with matrix \p m
	/// \ingroup NumericAlgorithms
	template <size_t NX, size_t NY, typename T>
	tuple<NX,T> operator* (const tuple<NY,T>& t, const matrix<NX,NY,T>& m)
	{
		tuple<NX,T> tr;
		for (uoff_t x = 0; x < NX; ++ x)
		{
			T dpv (0);
			for (uoff_t y = 0; y < NY; ++ y)
				dpv += t[y] * m[y][x];
			tr[x] = dpv;
		}
		return (tr);
	}

	/// 4-component vector transform
	std::tuple<4,float> operator* (const std::tuple<4,float>& t, const matrix<4,4,float>& m)
	{
		std::tuple<4,float> tr;
		for (uoff_t i = 0; i < 4; ++ i)
		tr[i] = t[0] * m[0][i] + t[1] * m[1][i] + t[2] * m[2][i] + t[3] * m[3][i];
		return (tr);
	}

	/// \brief Transposes (exchanges rows and columns) matrix \p m.
	/// \ingroup NumericAlgorithms
	template <size_t N, typename T>
	void transpose (matrix<N,N,T>& m)
	{
		for (uoff_t x = 0; x < N; ++x)
		{
			for (uoff_t y = x; y < N; ++y)
				swap (m[x][y], m[y][x]);
		}
	}

} // namespace lo
