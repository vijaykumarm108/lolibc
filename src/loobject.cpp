// loexcept - lolib exception handling

#include <stdafx.h>

namespace lo
{

	object_base::object_base()
	{

	}
	object_base::~object_base()
	{

	}

	std::string	object_base::ToString()
	{
		return typeid(this).name();
	}

	std::string object_base::ToString(const char *format)
	{
		return typeid(this).name();
	}

	ref_base::ref_base()
	{
		m_obj = nullptr;
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
