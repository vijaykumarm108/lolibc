/*
	All the base classes required for the stl part of lolibc.
*/
#pragma once
#include "lolibbase.h"

#ifdef __cplusplus

namespace lo
{
	class object_base;
	template <typename T> class ref;
	typedef ref<object_base>	object;
	class reference_type;

	/// Base class of the ref<T> and iref<T> smart pointers
	class ref_base
	{
	public:
		bool		is_null()	{ return m_obj == nullptr; }
	protected:
		ref_base();
		ref_base(object_base *obj);
		virtual ~ref_base();
		object_base	*m_obj;		// Object we are referring to
	private:
		uintptr_t	m_id;		// The unique id bit/number of this reference
	};

	/// The main smart pointer used in lolibc
	template <typename T>
	class ref : public ref_base
	{
	public:
		ref() : ref_base() {}
		ref(T& obj) : ref_base(&obj)	{  }
		ref(T* obj) : ref_base(obj)	{  }
		//ref(object_base *obj) : ref_base(obj) {}
//		inline ref( ref<T> & external ) : ref_base(external.ptr) {}
		inline T *operator->()				{ return ((reinterpret_cast<T *>(m_obj))); }
		inline const T *operator->() const 	{ return (((const T *)(m_obj))); }
		inline T *Ptr() const				{ return reinterpret_cast<T*>(m_obj); }
		inline operator const T &()			{ return *Ptr(); }
		static ref<T>	null()				{ return lo::ref<T>((T*)nullptr); }
	private:
	};

	/// This class stores an indirect reference to an object, for accessing base classes and interfaces
	template <typename T>
	class iref : public ref_base
	{
	public:
		iref(object *obj) : ref_base(obj) {}
		inline T* operator->()				{ return (reinterpret_cast<T *>(m_ptr)); }
		inline T *Ptr() const				{ return reinterpret_cast<T*>(m_ptr); }
	private:
		T *m_ptr;
	};

	typedef uint8_t utf8subchar_t;	///< Type for the encoding subcharacters.

	/// Creates an malloc sprintf string, which you *must* later free.
	const char *dsprintf(const char *format,...);
}

namespace std
{
	class istream;
	class string;
	class wstring;
	class ostream;
	class ostringstream;
	template<typename T>	class vector;
	typedef size_t size_type;
	
	/// Returns the difference \p p1 - \p p2
	template <typename T1, typename T2>
	inline ptrdiff_t distance (T1 i1, T2 i2)
	{
		return ((intptr_t)i2 - (intptr_t)i1);
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

	class object_base
	{
		friend class ref_base;
	public:
		object_base();
		object_base(object_base &obj);
		virtual ~object_base();
		inline virtual int		GetHashCode() const	{ return 0; }
		virtual std::string		ToString();
		virtual std::string		ToString(const char *format);
		bool operator!=(const object_base &ref) const;
	private:
		uintptr_t		m_references;	// ID mask for references which have a lock on this object
	};

	extern object_base nullref;

	/*!
	\brief If you are passing around a reference, then derive from ref_object, not object_base
	 */
	template<class T>
	class ref_object : object_base
	{
	protected:
		inline T* operator->()				{ return (reinterpret_cast<T *>(m_pimpl->Ptr())); }
		ref<T>	m_pimpl;
	};

	/// This class is used to forward reference pimpl classes which are defined in the .cpp file only.
	class Pimpl;

	/*!
	\brief This class contains a pointer and information about the buffer.
	 */
	class _link_buffer : public object_base
	{
	public:
		char			*m_buffer;
		size_t			m_sizeOfElement;	// Byte size of each element.
		size_t			m_numberElements;	// Number of elements
		size_t			m_allocatedLength;	// How many bytes are actually allocated
		bool			m_isConst;			// If true, then this is not deallocated when changed.
	};
	/*!
	\brief This class defines a continuous buffer, which can be either linked
	or directly allocated.
	*/
	class link_buffer : public object_base
	{
	protected:
		ref<_link_buffer>			m_linkBuffer;
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
		typedef const link_buffer&	rcself_t;
		inline iterator				begin (void)			{ return (iterator)(m_linkBuffer->m_buffer); }
		inline const_pointer		cdata (void) const		{ return (const_pointer)(m_linkBuffer->m_buffer); }
		bool						empty (void) const;
		iterator					end (void) const;
		inline size_type			size (void) const		{ return (size_type)(m_linkBuffer->m_numberElements); }
	};

#if 0
	class nstring : public link_buffer
	{
	public:
		typedef char				value_type;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef wchar_t				wvalue_type;
		typedef wvalue_type*		wpointer;
		typedef const wvalue_type*	const_wpointer;
		typedef pointer				iterator;
		typedef const_pointer		const_iterator;
		typedef value_type&			reference;
		typedef value_type			const_reference;
		typedef ::std::reverse_iterator<iterator>			reverse_iterator;
		typedef ::std::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef lo::utf8in_iterator<const_iterator>				utf8_iterator;
		const int npos = -1;
		nstring& append ( const nstring& str );
		nstring& append ( const nstring& str, size_t pos, size_t n );
		nstring& append ( const char* s, size_t n );
		nstring& append ( const char* s );
		nstring& append ( size_t n, char c );
		template <class InputIterator> nstring& append ( InputIterator first, InputIterator last );
		nstring& assign ( const nstring& str );
		nstring& assign ( const nstring& str, size_t pos, size_t n );
		nstring& assign ( const char* s, size_t n );
		nstring& assign ( const char* s );
		nstring& assign ( size_t n, char c );
		template <class InputIterator>
		nstring& assign ( InputIterator first, InputIterator last );
		const char& at ( size_t pos ) const;
		char& at ( size_t pos );
		iterator begin();
		const_iterator begin() const;
		size_t capacity ( ) const;
		void clear();
		int compare ( const nstring& str ) const;
		int compare ( const char* s ) const;
		int compare ( size_t pos1, size_t n1, const nstring& str ) const;
		int compare ( size_t pos1, size_t n1, const char* s) const;
		int compare ( size_t pos1, size_t n1, const nstring& str, size_t pos2, size_t n2 ) const;
		int compare ( size_t pos1, size_t n1, const char* s, size_t n2) const;
		size_t copy ( char* s, size_t n, size_t pos = 0) const;
		const char* c_str ( ) const;
		const char* data() const;
		bool empty ( ) const;
		iterator end();
		const_iterator end() const;
		nstring& erase ( size_t pos = 0, size_t n = npos );
		iterator erase ( iterator position );
		iterator erase ( iterator first, iterator last );
		size_t find ( const nstring& str, size_t pos = 0 ) const;
		size_t find ( const char* s, size_t pos, size_t n ) const;
		size_t find ( const char* s, size_t pos = 0 ) const;
		size_t find ( char c, size_t pos = 0 ) const;
		size_t find_first_not_of ( const nstring& str, size_t pos = 0 ) const;
		size_t find_first_not_of ( const char* s, size_t pos, size_t n ) const;
		size_t find_first_not_of ( const char* s, size_t pos = 0 ) const;
		size_t find_first_not_of ( char c, size_t pos = 0 ) const;
		size_t find_first_of ( const nstring& str, size_t pos = 0 ) const;
		size_t find_first_of ( const char* s, size_t pos, size_t n ) const;
		size_t find_first_of ( const char* s, size_t pos = 0 ) const;
		size_t find_first_of ( char c, size_t pos = 0 ) const;
		size_t find_last_of ( const nstring& str, size_t pos = npos ) const;
		size_t find_last_of ( const char* s, size_t pos, size_t n ) const;
		size_t find_last_of ( const char* s, size_t pos = npos ) const;
		size_t find_last_of ( char c, size_t pos = npos ) const;
		nstring& insert ( size_t pos1, const nstring& str );
		nstring& insert ( size_t pos1, const nstring& str, size_t pos2, size_t n );
		nstring& insert ( size_t pos1, const char* s, size_t n);
		nstring& insert ( size_t pos1, const char* s );
		nstring& insert ( size_t pos1, size_t n, char c );
		iterator insert ( iterator p, char c );
		void insert ( iterator p, size_t n, char c );
		template<class InputIterator>
		void insert ( iterator p, InputIterator first, InputIterator last );
		size_t length() const;
		size_t max_size ( ) const;
		nstring& operator+= ( const nstring& str );
		nstring& operator+= ( const char* s );
		nstring& operator+= ( char c );
		nstring& operator= ( const nstring& str );
		nstring& operator= ( const char* s );
		nstring& operator= ( char c );
		const char& operator[] ( size_t pos ) const;
		char& operator[] ( size_t pos );
		void push_back ( char c );
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		nstring& replace ( size_t pos1, size_t n1,   const nstring& str );
		nstring& replace ( iterator i1, iterator i2, const nstring& str );
		nstring& replace ( size_t pos1, size_t n1, const nstring& str, size_t pos2, size_t n2 );
		nstring& replace ( size_t pos1, size_t n1,   const char* s, size_t n2 );
		nstring& replace ( iterator i1, iterator i2, const char* s, size_t n2 );
		nstring& replace ( size_t pos1, size_t n1,   const char* s );
		nstring& replace ( iterator i1, iterator i2, const char* s );
		nstring& replace ( size_t pos1, size_t n1,   size_t n2, char c );
		nstring& replace ( iterator i1, iterator i2, size_t n2, char c );
		template<class InputIterator>
		nstring& replace ( iterator i1, iterator i2, InputIterator j1, InputIterator j2 );
		void resize ( size_t n, char c );
		void resize ( size_t n );
		size_t rfind ( const nstring& str, size_t pos = npos ) const;
		size_t rfind ( const char* s, size_t pos, size_t n ) const;
		size_t rfind ( const char* s, size_t pos = npos ) const;
		size_t rfind ( char c, size_t pos = npos ) const;
		size_t size() const;
		nstring substr ( size_t pos = 0, size_t n = npos ) const;
		void swap ( nstring& str );
	};
#endif
	template<typename T>
	class nvector : public link_buffer
	{
	public:

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
		inline					cblocklink (void) : m_Data (NULL), m_Size (0) { }
		cblocklink (const void* p, size_type n);
		inline					cblocklink (const cblocklink& l) : m_Data (l.m_Data), m_Size (l.m_Size) {}
		inline virtual			~cblocklink (void) throw()	{}
		inline iterator			begin (void) const			{ return (iterator (cdata())); }
		inline const_pointer	cdata (void) const			{ return (m_Data); }
		inline bool				empty (void) const			{ return (!size()); }
		inline iterator			end (void) const			{ return (iat (size())); }
		iterator				iat (size_type i) const;
		void					link (const void* p, size_type n);
		inline void				link (const cblocklink& l)	{ link (l.begin(), l.size()); }
		void					link (const void* first, const void* last);
		inline size_type		max_size (void) const		{ return (size()); }
		inline rcself_t			operator= (const cblocklink& l)	{ link (l); return (*this); }
		bool					operator== (const cblocklink& l) const;
		void					read (std::istream&);
		inline void				relink (const void* p, size_type n);
		inline size_type		readable_size (void) const	{ return (size()); }
		inline void				resize (size_type n)
		{
			m_Size = n;
		}
		inline size_type		size (void) const
		{
			return (m_Size);
		}
		size_type				stream_size (void) const;
		void					swap (cblocklink& l);
		void					text_write (std::ostringstream& os) const;
		/** Simply clears the pointer to the data. Dangerous function. */
		virtual void			unlink (void) throw();
		void					write (std::ostream& os) const;
		void					write_file (const char* filename, int mode = 0644) const;
	protected:
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
		inline const_iterator	begin (void) const
		{
			return (cblocklink::begin());
		}
		inline iterator			begin (void)
		{
			return (iterator (data()));
		}
		inline pointer			data (void)
		{
			return (const_cast<pointer>(cdata()));
		}
		inline iterator			end (void)
		{
			return (iat (size()));
		}
		inline const_iterator	end (void) const
		{
			return (cblocklink::end());
		}
		void					erase (iterator start, size_type size);
		void					fill (iterator start, const void* p, size_type elsize, size_type elCount = 1);
		iterator				iat (size_type i);
		inline const_iterator	iat (size_type i) const
		{
			return (cblocklink::iat (i));
		}
		void					insert (iterator start, size_type size);
		inline void				link (const void* p, size_type n)
		{
			cblocklink::link (p, n);
		}
		inline void				link (void* p, size_type n)
		{
			cblocklink::link (p, n);
		}
		inline void				link (const cblocklink& l)
		{
			cblocklink::link (l);
		}
		inline void				link (blocklink& l)
		{
			cblocklink::link (l);
		}
		void					link (const void* first, const void* last);
		void					link (void* first, void* last);
		inline rcself_t			operator= (const cblocklink& l)
		{
			cblocklink::operator= (l); return (*this);
		}
		inline rcself_t			operator= (rcself_t l)
		{
			cblocklink::operator= (l); return (*this);
		}
		inline void				relink (const void* p, size_type n)
		{
			cblocklink::relink (p, n);
		}
		inline void				relink (void* p, size_type n)
		{
			cblocklink::relink (p, n);
		}
		void					read (std::istream& is);
		inline void				swap (blocklink& l)
		{
			cblocklink::swap (l);
		}
		size_type				writable_size (void) const
		{
			return (size());
		}
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

#endif // __cplusplus

