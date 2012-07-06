#pragma once
#include "lolibbase.h"
#include "ntoskrnl.h"
//#include <wininet.h>

#ifdef __cplusplus
namespace lo { namespace wininet {
#endif

/* Set up Structure Packing to be 4 bytes for all wininet structures */
#if defined(_WIN64)
#include <pshpack8.h>
#else
#include <pshpack4.h>
#endif

#define INTERNET_OPEN_TYPE_PRECONFIG                    0   // use registry configuration
#define INTERNET_OPEN_TYPE_DIRECT                       1   // direct to net
#define INTERNET_OPEN_TYPE_PROXY                        3   // via named proxy
#define INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY  4   // prevent using java/script/INS

	typedef void * HINTERNET;

	typedef enum { INTERNET_SCHEME_PARTIAL = -2, INTERNET_SCHEME_UNKNOWN = -1, INTERNET_SCHEME_DEFAULT = 0, INTERNET_SCHEME_FTP, INTERNET_SCHEME_GOPHER,
		INTERNET_SCHEME_HTTP, INTERNET_SCHEME_HTTPS, INTERNET_SCHEME_FILE, INTERNET_SCHEME_NEWS, INTERNET_SCHEME_MAILTO, INTERNET_SCHEME_SOCKS, INTERNET_SCHEME_JAVASCRIPT,
		INTERNET_SCHEME_VBSCRIPT, INTERNET_SCHEME_RES, INTERNET_SCHEME_FIRST = INTERNET_SCHEME_FTP, INTERNET_SCHEME_LAST = INTERNET_SCHEME_RES
	} INTERNET_SCHEME, * LPINTERNET_SCHEME;

	typedef struct {
		uint32_t	dwStructSize;				// size of this structure. Used in version check
		char *	lpszScheme;					// pointer to scheme name
		uint32_t	dwSchemeLength;				// length of scheme name
		INTERNET_SCHEME nScheme;			// enumerated scheme type (if known)
		char *	lpszHostName;				// pointer to host name
		uint32_t   dwHostNameLength;			// length of host name
		uint16_t	nPort;						// converted port number
		char *	lpszUserName;				// pointer to user name
		uint32_t	dwUserNameLength;			// length of user name
		char *	lpszPassword;				// pointer to password
		uint32_t	dwPasswordLength;			// length of password
		char *	lpszUrlPath;				// pointer to URL-path
		uint32_t	dwUrlPathLength;			// length of URL-path
		char *	lpszExtraInfo;				// pointer to extra information (e.g. ?foo or #foo)
		uint32_t	dwExtraInfoLength;			// length of extra information
	} URL_COMPONENTSA, * LPURL_COMPONENTSA;

	typedef struct _INTERNET_BUFFERSA {
		uint32_t	dwStructSize;				// used for API versioning. Set to sizeof(INTERNET_BUFFERS)
		struct _INTERNET_BUFFERSA * Next;	// chain of buffers
		const char * lpcszHeader;			// pointer to headers (may be NULL)
		uint32_t	dwHeadersLength;			// length of headers if not NULL
		uint32_t	dwHeadersTotal;				// size of headers if not enough buffer
		void *	lpvBuffer;					// pointer to data buffer (may be NULL)
		uint32_t	dwBufferLength;				// length of data buffer if not NULL
		uint32_t	dwBufferTotal;				// total size of chunk, or content-length if not chunked
		uint32_t	dwOffsetLow;				// used for read-ranges (only used in HttpSendRequest2)
		uint32_t	dwOffsetHigh;
	} INTERNET_BUFFERSA, * LPINTERNET_BUFFERSA;

#ifdef __cplusplus
} } // end namespace lo::wininet

using namespace lo::wininet;

extern "C" {
#endif // __cplusplus

	BOOL		WINAPI	FtpCreateDirectoryW( HINTERNET hConnect, const wchar_t * lpszDirectory );
	BOOL		WINAPI	FtpDeleteFileW( HINTERNET hConnect, const wchar_t * lpszFileName );
	HINTERNET	WINAPI	FtpFindFirstFile( HINTERNET hConnect, const char * lpszSearchFile, LPWIN32_FIND_DATAW lpFindFileData, uint32_t dwFlags, uintptr_t dwContext );
	BOOL		WINAPI	FtpGetCurrentDirectoryW( HINTERNET hConnect, wchar_t * lpszCurrentDirectory, uint32_t * lpdwCurrentDirectory );
	uint32_t	WINAPI	FtpGetFileSize( HINTERNET hFile, uint32_t * lpdwFileSizeHigh );
	BOOL		WINAPI	FtpGetFileW( HINTERNET hConnect, const wchar_t * lpszRemoteFile, const wchar_t * lpszNewFile, BOOL fFailIfExists, uint32_t dwFlagsAndAttributes, uint32_t dwFlags, uintptr_t dwContext );
	HINTERNET	WINAPI	FtpOpenFileW( HINTERNET hConnect, const wchar_t * lpszFileName, uint32_t dwAccess, uint32_t dwFlags, uintptr_t dwContext );
	BOOL		WINAPI	FtpPutFileW(HINTERNET hConnect, const wchar_t * lpszLocalFile, const wchar_t * lpszNewRemoteFile, uint32_t dwFlags, uintptr_t dwContext );
	BOOL		WINAPI	FtpRemoveDirectoryW(HINTERNET hConnect, const wchar_t * lpszDirectory );
	BOOL		WINAPI	FtpRenameFileW( HINTERNET hConnect, const wchar_t * lpszExisting, const wchar_t * lpszNew );
	BOOL		WINAPI	FtpSetCurrentDirectoryW( HINTERNET hConnect, const wchar_t * lpszDirectory );
	BOOL		WINAPI	HttpAddRequestHeadersA( HINTERNET hRequest, const char * lpszHeaders, uint32_t dwHeadersLength, uint32_t dwModifiers );
	BOOL		WINAPI	HttpEndRequest( HINTERNET hRequest, LPINTERNET_BUFFERSA lpBuffersOut, uint32_t dwFlags, uintptr_t dwContext	);
	HINTERNET	WINAPI	HttpOpenRequestA( HINTERNET hConnect, const char * lpszVerb, const char * lpszObjectName, const char * lpszVersion, const char * lpszReferer,
											const char * lplpszAcceptTypes, uint32_t dwFlags, uintptr_t dwContext );
	BOOL		WINAPI	HttpSendRequestA( HINTERNET hRequest, const char * lpszHeaders, uint32_t dwHeadersLength, void * lpOptional, uint32_t dwOptionalLength );
	BOOL		WINAPI	InternetCloseHandle( HINTERNET hInternet );
	BOOL		WINAPI	InternetCrackUrlA( const char * lpszUrl, uint32_t dwUrlLength, uint32_t dwFlags, LPURL_COMPONENTSA lpUrlComponents );
	BOOL		WINAPI	InternetFindNextFile( HINTERNET hFind, void * lpvFindData );
	HINTERNET	WINAPI	InternetOpenA( const char * lpszAgent, uint32_t dwAccessType, const char * lpszProxy, const char * lpszProxyBypass, uint32_t dwFlags );
	HINTERNET	WINAPI	InternetOpenUrlA( HINTERNET hInternet, const char * lpszUrl, const char * lpszHeaders, uint32_t dwHeadersLength, uint32_t dwFlags, uintptr_t dwContext );
	BOOL		WINAPI	InternetReadFile( HINTERNET hFile, void * lpBuffer, uint32_t dwNumberOfBytesToRead, uint32_t * lpdwNumberOfBytesRead );
	BOOL		WINAPI	InternetWriteFile( HINTERNET hFile, const void * lpBuffer, uint32_t dwNumberOfBytesToWrite, uint32_t * lpdwNumberOfBytesWritten );

/* Return packing to whatever it was before we entered this file */
#include <poppack.h>

#ifdef __cplusplus
};
#endif / __cplusplus
