/* lolibc */

#pragma once
#include "lostlbase.h"

namespace lo {

	/** Managed memory block.

	Adds memory management capabilities to blocklink. Uses malloc and realloc to
	maintain the internal pointer, but only if allocated using members of this class,
	or if linked to using the Manage() member function. Managed memory is automatically
	freed in the destructor.

	*/
	class block : public blocklink {
	public:
					block (void);
					block (const void* p, size_type n);
		explicit	block (size_type n);
		explicit	block (const cblocklink& b);
		explicit	block (const blocklink& b);
					block (const block& b);
		virtual		~block (void) throw();

		void					assign (const void* p, size_type n);
		inline void				assign (const cblocklink& l)		{ assign (l.cdata(), l.readable_size()); }
		inline size_type		capacity (void) const			{ return (m_Capacity); }
		inline void				clear (void)					{ resize (0); }
		void					copy_link (void);
		void					deallocate (void) throw();
		iterator				erase (iterator start, size_type size);
		iterator				insert (iterator start, size_type size);
		inline bool				is_linked (void) const			{ return (!capacity()); }
		inline const block&	operator= (const cblocklink& l)	{ assign (l); return (*this); }
		inline const block&	operator= (const blocklink& l)	{ assign (l); return (*this); }
		inline const block&	operator= (const block& l)	{ assign (l); return (*this); }
		inline void				manage (blocklink& l)				{ manage (const_cast<void *>(reinterpret_cast<const void *>(l.begin())), l.size()); }
		void					manage (void* p, size_type n);
		inline size_type		max_size (void) const			{ return (is_linked() ? blocklink::max_size() : SIZE_MAX); }
		void					read (std::istream& is);
		void					read_file (const char* filename);
		void					reserve (size_type newSize, bool bExact = true);
		void					resize (size_type newSize, bool bExact = true);
		inline void				swap (block& l)				{ blocklink::swap (l); ::std::swap (m_Capacity, l.m_Capacity); }
		virtual void			unlink (void) throw();
	protected:
		virtual size_type		minimumFreeCapacity (void) const throw() __attribute__((const));
	private:
		size_type				m_Capacity;	///< Number of bytes allocated by Resize.
	};


} // namespace lo

namespace std
{
	template <> inline void swap (lo::block& a, lo::block& b)
	{
		a.swap (b);
	}
}