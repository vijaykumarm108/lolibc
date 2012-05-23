#pragma once

#ifdef __cplusplus

#define WINAPI __stdcall

namespace lo
{
	class dll
	{
	public:
		inline dll()	{_addref();}
		~dll()			{_release(); }
		virtual const char *Name() = 0;
		static void		_free_unused_dlls();
	protected:
		virtual int &counter() = 0;
		void _addref();
		void _release();
		void *m_handle;
	};
}

#endif
