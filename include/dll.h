
namespace lolibc
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
