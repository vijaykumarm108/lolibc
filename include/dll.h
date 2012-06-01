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
		intptr_t	m_handle;
	};
}


#endif
#define FALSE (0)
#define TRUE (1)
typedef int BOOL;
typedef BOOL *LPBOOL;
typedef void *HINSTANCE;
#define WINBASEAPI __declspec(dllimport)
#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

// Writes flags
#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)
#define STANDARD_RIGHTS_ALL              (0x001F0000L)
#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)
#define ACCESS_SYSTEM_SECURITY           (0x01000000L)	// AccessSystemAcl access type
#define MAXIMUM_ALLOWED                  (0x02000000L)	// MaximumAllowed access type
#define GENERIC_READ                     (0x80000000L)	//  These are the generic rights.
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)
