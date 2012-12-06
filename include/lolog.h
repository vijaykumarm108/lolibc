/*
This is the main external header, which includes everything in this library.
*/
#pragma once
#include "lostlbase.h"
#include "stdarg.h"

namespace lo {
	/** All logs are stored in AppData/lologs directory with the modulename.linkertime-YY-MM-DD.log format
	(Error level)MIN:SEC@address=(Error number)[Optional Errorcode string]$optional string
	*/
	class log
	{
	public:
		/** This reports an error to the user. i.e. ERR_10:22@05F3A167=2[File not found]$c:\inputfile.fil  */
		static void		error( long errorcode, const char *format, ...);
		/** Useful function for translating error code to string. */
		static int		formatMessage( long errorcode, char *format, int length );
		/** Gets the AppData directory. */
		static const wchar_t *get_appdataDir();
		/** Gets the name of the current log file. */
		static const wchar_t *get_currentFile();
		/** Returns the full path of the module which contains this log library. */
		static const wchar_t *get_moduleFileName();
		/** Returns just the file name of the module which contains this log library. */
		static const wchar_t *get_moduleName();
		/** Report progress PROG10:22@0671A8D0=B$Copy files PROG10:22@0671A8D0=R$File1.fil PROG10:22@0671A8D0=E$Success. */
		static void		progress(const char *format);
		/** This error was unhandled and therefore is not placed in the log file, but rather generate a dump crash for pick up later. */
		static void		unhandled(long errorcode, const char *format, ...);
		/** This is some extra information, perhaps the user should know. i.e. i.e. INFO10:22@05F3A167=0$We are starting the application. */
		static void		verbose( const char *format, ...);
		/** This is a warning. Perhaps something the user should know. i.e. WARN10:22@05F3A167=0$Warning the user*/
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

	class progress
	{
	public:
		/** Indicate the name of the operation.  Use a static string. */
		progress(const char *operation);
		/** Call stop, otherwise the destructor indicates abnormal progress termination. */
		~progress();
		/** Updates progress in order to give a hint how long something might take. */
		void report(int current, int total);
		/** Call this to indicate the progress has started normally.*/
		void start();
		/** Call this to indicate the progress has stopped normally.*/
		void stop();
	private:
		const char *m_operation;
		__time64_t	m_startTime;
		bool		m_started;
		static int	m_level;
	};
}
