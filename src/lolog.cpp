
#include <stdafx.h>
#include <lolog.h>
#include <windows.h>
#include <stdio.h>

namespace lo {

	void log::error( long errorcode, const char *format, ...)
	{
		char message[1024];
		va_list	VAList;
		SetLastError(errorcode);
		va_start(VAList, format);
		int len = vsnprintf(message, sizeof(message), format, VAList);
		if( errorcode != 0 )
		{
			strcat(message," : ");
			len += 3;
			FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), message + len, sizeof(message) - len, NULL );
		}
		write(message);
	}
	void log::verbose( const char *format, ...)
	{
		char message[1024];
		va_list	VAList;
		va_start(VAList, format);
		int len = vsnprintf(message, sizeof(message), format, VAList);
		write(message);
	}
	void log::warning( const char *format, ...)
	{
		char message[1024];
		va_list	VAList;
		va_start(VAList, format);
		int len = vsnprintf(message, sizeof(message), format, VAList);
		write(message);
	}
	void log::write( const char *output )
	{
#ifdef _DEBUG
		OutputDebugStringA(output);
		OutputDebugStringA("\r\n");
#endif
	}
	function_trace::function_trace() : m_id("")
	{

	}
	function_trace::function_trace( const char *format ) : m_id(format)
	{

	}
	function_trace::~function_trace()
	{

	}
	void function_trace::set_return_value(intptr_t returnValue, bool isError)
	{
		m_returnValue = returnValue;
		if(isError)
			log::error(GetLastError(),"%s,%d",m_id,returnValue);
	}

	int log::format_message( long errorcode, char *message, int length )
	{
		WCHAR	wmessage[512];

		int messageLength = (int)FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), wmessage, sizeof(message)/sizeof(WCHAR), NULL );
		if(messageLength <= 0 )
		{
			messageLength = (int)FormatMessageW( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, HRESULT_FROM_WIN32(errorcode), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), wmessage, sizeof(message)/sizeof(WCHAR), NULL );
		}
		if(messageLength <= 0 )
			messageLength = _snprintf(message, length, "Unknown WIN32ERROR code:(%d=%08X)", errorcode, errorcode);
		else
		{
			messageLength = WideCharToMultiByte(CP_UTF8,0,wmessage,-1,message,length,NULL,NULL);
		}
		return messageLength;
	}

}
