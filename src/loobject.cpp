// loexcept - lolib exception handling

#include <stdafx.h>

namespace lo
{
	object_base::~object_base()
	{

	}

	rstring	object_base::ToString()
	{
		return typeid(this).name();
	}

	rstring::rstring(const char *str)
	{
		m_isConst = true;
		m_str = const_cast<char *>(str);
	}

	ref_base::ref_base(object_base *obj )
	{
		m_obj = obj;
	}

	ref_base::~ref_base()
	{
		if(m_obj != nullptr)
		{
			delete m_obj;
		}
	}
}
