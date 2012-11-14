/*
This is the main external header, which includes everything in this library.
*/
#pragma once
#include "lostlbase.h"
#include "stdarg.h"

namespace lo {
	class log
	{
	public:
		static void error( long errorcode, const char *format, ...);
		static void verbose( const char *format, ...);
		static void warning( const char *format, ...);
	private:
		static void write( const char *output );
	};

	class function_trace
	{
	public:
		function_trace();
		function_trace( const char *format );
		~function_trace();
		void set_return_value(intptr_t returnValue, bool isError=false);
	private:
		intptr_t m_returnValue;
		const char *m_id;
	};
}
