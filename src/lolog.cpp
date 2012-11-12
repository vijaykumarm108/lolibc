
#include <stdafx.h>
#include <lolog.h>
#include <windows.h>

namespace lo {
	void log::error( long errorcode, const char *format, ...)
	{
		SetLastError(errorcode);
	}
	void log::verbose( const char *format, ...)
	{

	}
	void log::warning( const char *format, ...)
	{

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
}
