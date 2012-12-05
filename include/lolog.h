/*
This is the main external header, which includes everything in this library.
*/
#pragma once
#include "lostlbase.h"
#include "stdarg.h"

namespace lo {
	/** All logs are stored in AppData/lologs directory with the modulename-YY-MM-DD.log format	*/
	class log
	{
	public:
		static void		error( long errorcode, const char *format, ...);
		static int		formatMessage( long errorcode, char *format, int length );
		/** Gets the AppData directory. */
		static const wchar_t *get_appdataDir();
		/** Gets the name of the current log file. */
		static const wchar_t *get_currentFile();
		/** Returns the full path of the module which contains this log library. */
		static const wchar_t *get_moduleFileName();
		/** Returns just the file name of the module which contains this log library. */
		static const wchar_t *get_moduleName();
		static void		verbose( const char *format, ...);
		static void		warning( const char *format, ...);
	private:
		/** Writes the given text to the log file without prefixing or appending anything. */
		static void		raw( const char *line );
		/** Writes the given line of text to the log file, prefixing the standard identifiers. A CR/LF is appended. */
		static void		write( const char *line );
		static wchar_t	m_logDirectory[];
		static wchar_t	m_logFile[];
		static time_t	m_lastTime;
		static wchar_t	m_moduleName[];
		static wchar_t	m_moduleFileName[];
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
