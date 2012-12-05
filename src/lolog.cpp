
#include <stdafx.h>
#include <lolog.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>

extern HINSTANCE ghInstance;

namespace lo {

	static CRITICAL_SECTION	s_cs;	/// Local critical section.
	static bool s_isCsInitialized = false;

	wchar_t log::m_logDirectory[MAX_PATH*2];
	wchar_t log::m_logFile[MAX_PATH*2];
	wchar_t log::m_moduleName[MAX_PATH] = {0};
	wchar_t	log::m_moduleFileName[MAX_PATH] = {0};
	
	time_t log::m_lastTime;

	const wchar_t *log::get_appdataDir()
	{
		GetEnvironmentVariableW(L"AppData", m_logDirectory, sizeof(m_logDirectory)/sizeof(wchar_t) );
		return m_logDirectory;
	}

	extern "C" _CRTIMP int _wmkdir(const wchar_t *dirname  );
	const wchar_t *log::get_currentFile()
	{
		__time64_t	_time;
		_time = time(&_time);
		struct tm *_tm;
		_tm = _localtime64(&_time);
		size_t i = wcslen(wcscpy(m_logFile,get_appdataDir()));
		if( *(m_logFile + i - 1) != '\\' )
		{	// Append a backslash if it is missing.
			m_logFile[i++] = '\\';
			m_logFile[i] = 0;
		}
		wcscat(m_logFile,L"lologs");
		_wmkdir(m_logFile);
		_snwprintf( m_logFile + wcslen(m_logFile), MAX_PATH - i, L"\\%s-%04d%02d%02d.log", get_moduleName(), _tm->tm_year+1970, _tm->tm_mon + 1, _tm->tm_mday );

		return m_logFile;
	}

	const wchar_t *log::get_moduleFileName()
	{
		if( *m_moduleFileName == 0)
			GetModuleFileNameW(ghInstance,m_moduleFileName,sizeof(m_moduleFileName)/sizeof(wchar_t) );
		return m_moduleFileName;
	}

	const wchar_t *log::get_moduleName()
	{
		if( *m_moduleName == 0)
		{
			const wchar_t *source = get_moduleFileName();
			for( source += wcslen(m_moduleFileName) - 1; source > m_moduleFileName && *source != '\\'; --source );
			if( *source == '\\')
				++source;
			wcscpy(m_moduleName,source);
		}
		return m_moduleName;
	}

	void log::error( long errorcode, const char *format, ...)
	{
		static const char errorHeader[] = {"ERROR:"};
		char message[1024];
		va_list	VAList;
		SetLastError(errorcode);
		va_start(VAList, format);
		strcpy(message,errorHeader);
		int len = vsnprintf(message + sizeof(errorHeader) - 1, sizeof(message) - sizeof(errorHeader), format, VAList) + sizeof(errorHeader) - 1;
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
		static const char warningHeader[] = {"WARNING:"};
		char message[1024];
		va_list	VAList;
		va_start(VAList, format);
		strcpy(message,warningHeader);
		int len = vsnprintf(message + sizeof(warningHeader) - 1, sizeof(message) - sizeof(warningHeader), format, VAList);
		write(message);
	}
	void log::raw( const char *output )
	{
#ifdef _DEBUG
		OutputDebugStringA(output);
		OutputDebugStringA("\r\n");
#endif
		if(!s_isCsInitialized)
		{
			s_isCsInitialized = true;
			InitializeCriticalSection(&s_cs);
		}
		EnterCriticalSection(&s_cs);
		FILE * file = _wfopen(get_currentFile(),L"at");
		if(file)
		{
			fputs(output,file);
			fclose(file);
		}
		LeaveCriticalSection(&s_cs);
	}
	void log::write(const char *line)
	{
		char	temp[1024];	// Limit lines to 1024 characters
		__time64_t	_time;
		_time = time(&_time);
		struct tm *_tm;
		_tm = _localtime64(&_time);
		_snprintf(temp, 1024, "%02d:%02d=%s\n",  _tm->tm_hour, _tm->tm_min, line );
		raw(temp);
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

	int log::formatMessage( long errorcode, char *message, int length )
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
