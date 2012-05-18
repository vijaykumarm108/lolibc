#include <stdafx.h>
#include <dll.h>
#include <windows.h>

namespace lo
{
	void dll::_addref()
	{
		if(counter()++ == 0)
			m_handle = (void *)LoadLibraryA(Name());
	}

	void dll::_release()
	{
		if(--counter() == 0)
		{
			::FreeLibrary((HMODULE)m_handle);
			m_handle = nullptr;
		}
	}
}
