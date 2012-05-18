// Lo-Overhead STL library - Lostl
//

#include <stdafx.h>
#include <istream>
#include <ostream>
#include <sstream>

namespace std {
	istream&	ios::align::apply (istream& is) const
	{
		is.align (m_Grain); return (is);
	}

	ostream&	ios::align::apply (ostream& os) const
	{
		os.align (m_Grain); return (os);
	}

	void		ios::align::read (istream& is) const
	{
		apply (is);
	}

	void		ios::align::write (ostream& os) const
	{
		apply (os);
	}

	istream&	ios::skip::apply (istream& is) const
	{
		is.skip (m_nBytes);
		return (is);
	}

	ostream&	ios::skip::apply (ostream& os) const
	{
		os.skip (m_nBytes);
		return (os);
	}

	void		ios::skip::read (istream& is) const
	{
		apply (is);
	}

	void		ios::skip::write (ostream& os) const
	{
		apply (os);
	}

	ostringstream&	ios::width::apply (ostringstream& os) const
	{
		os.set_width ((uint16_t)m_nBytes);
		return (os);
	}

	void			ios::width::text_write (ostringstream& os) const
	{
		apply (os);
	}

	ostringstream&	ios::base::apply (ostringstream& os) const
	{
		os.set_base ((uint16_t)m_Base);
		return (os);
	}

	void			ios::base::text_write (ostringstream& os) const
	{
		apply (os);
	}

} // namespace std
