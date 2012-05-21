/*
	All the base classes required for the stl part of lolibc.
	All classes derive either from reference_type or value_type.
	value_types always contain a sub-type which is always cloned on copy.
	You can:
	object
		value_type - always copied type
		buffer - memory link type
*/
#pragma once
#include "lolibbase.h"

#ifndef __cplusplus
#error This header requires a C++ compiler ...
#endif


namespace lo
{
	class object;
	class reference_type;

	class ref_base
	{
	public:
		ref_base();
		ref_base(object *obj);
		virtual ~ref_base();
	protected:
		reference_type	*m_obj;
	};

	template <typename T>
	class ref : public ref_base
	{
	public:
		ref() : ref_base() {}
		ref(const T& obj) : ref_base(&obj)	{  }
		ref(const T* obj) : ref_base(obj)	{  }
		inline ref( ref<T> & external ) : BaseRef(external.ptr) {}
		inline T* operator->()				{ return (reinterpret_cast<T *>(ptr)); }
		inline T *Ptr() const				{ return reinterpret_cast<T*>(ptr); }
	private:
	};

	typedef uint8_t utf8subchar_t;	///< Type for the encoding subcharacters.

	/// Creates an malloc sprintf string, which you *must* later free.
	const char *dsprintf(const char *format,...);
}

namespace std
{
	class istream;
	class string;
	class ostream;
	class ostringstream;
	template<typename T>	class vector;
	typedef unsigned size_type;
	
	/// Returns the difference \p p1 - \p p2
	template <typename T1, typename T2>
	inline ptrdiff_t distance (T1 i1, T2 i2)
	{
		return (i2 - i1);
	}
	
	/// Assigns the contents of a to b and the contents of b to a.
	/// This is used as a primitive operation by many other algorithms. 
	/// \ingroup SwapAlgorithms
	template <typename Assignable> 
	inline void swap (Assignable& a, Assignable& b)
	{
		Assignable tmp = a;
		a = b;
		b = tmp;
	}
}

namespace lo
{
	int GetHashCode(const unsigned char *buffer,size_t len);

	class object
	{
		friend class ref_base;
	public:
		virtual ~object();
		inline virtual int			GetHashCode() const	{ return 0; }
		virtual ref<::std::string>	ToString();
	private:
		ref<::std::vector<ref_base *>>	m_references;
	};

	/*!
	\brief value_type always copies its value.
	T = class name, TValue = value type name, i.e. "bool"
	Derive your value_type from this class.
	 */
	template <class T,typename TValue>
	class value_type : public object
	{
	public:
		virtual int CompareTo(const object &obj) const
		{
			if( const ValueType<T,TValue> * t = dynamic_cast<const ValueType<T,TValue> *>(&obj) )
				return CompareTo(*t);
			return 1;
		}
		virtual bool Equals(const object &obj) const
		{
			if( const ValueType<T,TValue> * t = dynamic_cast<const ValueType<T,TValue> *>(&obj) )
				return Equals(*t);
			return false;
		}
		virtual bool Equals(const T &obj) const
		{
			return (m_value==obj.m_value) != 0;
		}
		inline bool	operator== (const T &obj) const
		{
			return m_value==obj.m_value;
		}
		inline bool	operator!= (const T &obj) const
		{
			return m_value!=obj.m_value;
		}
		inline operator TValue()	{ return m_value; }
		inline const TValue *		GetPointer() const	{ return &m_value; }
		inline size_t				ValueSize()	const	{ return sizeof(TValue); }
		ref<object>					Clone()				{ return ref<object>(static_cast<object *>(new T(m_value))); }
		virtual int					GetHashCode() const	{ return ::lo::GetHashCode(reinterpret_cast<const unsigned char *>(GetPointer()), ValueSize()); }
	protected:
		inline value_type()	{}
		inline value_type(const TValue value) : m_value(value)	{}
		TValue				m_value;
	};


	class buffer_type : public object
	{
	};

	/// The alignment performed by default.
	const size_t c_DefaultAlignment = __alignof__(void*);

	/// \brief Rounds \p n up to be divisible by \p grain
	template <typename T>
	inline T Align (T n, size_t grain = c_DefaultAlignment)
	{
		n += (T)(grain - 1);
		return (n - n % grain);
	}

	/// \brief A read-only pointer to a sized block of memory.
	///
	/// Use this class the way you would a const pointer to an allocated unstructured block.
	/// The pointer and block size are available through member functions and cast operator.
	///
	/// Example usage:
	///
	/// \code
	///     void* p = malloc (46721);
	///     cblocklink a, b;
	///     a.link (p, 46721);
	///     assert (a.size() == 46721));
	///     b = a;
	///     assert (b.size() == 46721));
	///     assert (b.DataAt(34) == a.DataAt(34));
	///     assert (0 == memcmp (a, b, 12));
	/// \endcode
	///
	class cblocklink {
	public:
		typedef char				value_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef value_type			reference;
		typedef value_type			const_reference;
		typedef size_t				size_type;
		typedef uint32_t			written_size_type;
		typedef ptrdiff_t			difference_type;
		typedef const_pointer		const_iterator;
		typedef const_iterator		iterator;
		typedef const cblocklink&		rcself_t;
	public:
		inline				cblocklink (void)				: m_Data (NULL), m_Size (0) { }
							cblocklink (const void* p, size_type n);
		inline				cblocklink (const cblocklink& l)		: m_Data (l.m_Data), m_Size (l.m_Size) {}
		inline virtual     ~cblocklink (void) throw()			{}
		inline iterator		begin (void) const			{ return (iterator (cdata())); }
		inline const_pointer	cdata (void) const			{ return (m_Data); }
		inline bool			empty (void) const			{ return (!size()); }
		inline iterator		end (void) const			{ return (iat (size())); }
		iterator			iat (size_type i) const;
		void				link (const void* p, size_type n);
		inline void			link (const cblocklink& l)	{ link (l.begin(), l.size()); }
		void				link (const void* first, const void* last);
		inline size_type	max_size (void) const		{ return (size()); }
		inline rcself_t		operator= (const cblocklink& l)	{ link (l); return (*this); }
		bool				operator== (const cblocklink& l) const;
		void				read (std::istream&);
		inline void			relink (const void* p, size_type n);
		inline size_type	readable_size (void) const	{ return (size()); }
		inline void			resize (size_type n)		{ m_Size = n; }
		inline size_type	size (void) const			{ return (m_Size); }
		size_type			stream_size (void) const;
		void				swap (cblocklink& l);
		void				text_write (std::ostringstream& os) const;
		virtual void		unlink (void) throw();
		void				write (std::ostream& os) const;
		void				write_file (const char* filename, int mode = 0644) const;
	private:
		const_pointer	m_Data;		///< Pointer to the data block (const)
		size_type		m_Size;		///< size of the data block
	};

	//----------------------------------------------------------------------

	/// A fast alternative to link which can be used when relinking to the same block (i.e. when it is resized)
	inline void cblocklink::relink (const void* p, size_type n)
	{
		m_Data = reinterpret_cast<const_pointer>(p);
		m_Size = n;
	}

	//template <> inline void swap (cblocklink& a, cblocklink& b)
	//{
	//	a.swap (b);
	//}

	/**	Wrapper for pointer to block with size.

	Use this class the way you would a pointer to an allocated unstructured block.
	The pointer and block size are available through member functions and cast operator.

	Example usage:
	\code
		void* p = malloc (46721);
		blocklink a, b;
		a.link (p, 46721);
		assert (a.size() == 46721));
		b = a;
		assert (b.size() == 46721));
		assert (b.begin() + 34 == a.begin + 34);
		assert (0 == memcmp (a, b, 12));
		a.fill (673, b, 42, 67);
		b.erase (87, 12);
	\endcode
	*/
	class blocklink : public cblocklink {
	public:
		typedef cblocklink::const_iterator	const_iterator;
		typedef cblocklink::pointer			const_pointer;
		typedef pointer						iterator;
		typedef value_type*					pointer;
		typedef const blocklink&				rcself_t;
	public:
		inline					blocklink (void)				: cblocklink() {}
		inline					blocklink (void* p, size_type n)		: cblocklink (p, n) {}
		inline					blocklink (const void* p, size_type n)	: cblocklink (p, n) {}
		inline					blocklink (rcself_t l)			: cblocklink (l) {}
		inline explicit			blocklink (const cblocklink& l)		: cblocklink (l) {}
		inline const_iterator	begin (void) const			{ return (cblocklink::begin()); }
		inline iterator			begin (void)				{ return (iterator (data())); }
		inline pointer			data (void)					{ return (const_cast<pointer>(cdata())); }
		inline iterator			end (void)					{ return (iat (size())); }
		inline const_iterator	end (void) const			{ return (cblocklink::end()); }
		void					erase (iterator start, size_type size);
		void					fill (iterator start, const void* p, size_type elsize, size_type elCount = 1);
		iterator				iat (size_type i);
		inline const_iterator	iat (size_type i) const		{ return (cblocklink::iat (i)); }
		void					insert (iterator start, size_type size);
		inline void				link (const void* p, size_type n)	{ cblocklink::link (p, n); }
		inline void				link (void* p, size_type n)			{ cblocklink::link (p, n); }
		inline void				link (const cblocklink& l)			{ cblocklink::link (l); }
		inline void				link (blocklink& l)					{ cblocklink::link (l); }
		void					link (const void* first, const void* last);
		void					link (void* first, void* last);
		inline rcself_t			operator= (const cblocklink& l)		{ cblocklink::operator= (l); return (*this); }
		inline rcself_t			operator= (rcself_t l)				{ cblocklink::operator= (l); return (*this); }
		inline void				relink (const void* p, size_type n)	{ cblocklink::relink (p, n); }
		inline void				relink (void* p, size_type n)		{ cblocklink::relink (p, n); }
		void					read (std::istream& is);
		inline void				swap (blocklink& l)					{ cblocklink::swap (l); }
		size_type				writable_size (void) const			{ return (size()); }
	};

	

/// Use with blocklink-derived classes to allocate and link to stack space.
#define alloca_link(m,n)	(m).link (alloca (n), (n))

/// Use with cblocklink-derived classes to link to a static array
#define static_link(v)	link (VectorBlock(v))

}

namespace std
{
	template <> inline void swap (lo::blocklink& a, lo::blocklink& b)			{ a.swap (b); }
}
