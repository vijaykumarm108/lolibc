#pragma once
#include <string>


namespace System {

	class DateTime
	{
	public:
		DateTime();
	};

	class Uri : public lo::object
	{
	public:
		Uri(const char *uri) : m_uri(uri) {}
		Uri(const Uri &uri,const char *additionalPath);
		Uri(const Uri &absoluteUri, Uri &relativeUri);
		static void EscapeAsciiChar(char ch, char to[], int & pos);
		static int FromHex( char digit );
		std::string	get_AbsolutePath() const;
		bool		get_IsFile();
		static bool IsHexDigit(char character);
		static const char *HexUpperChars;
		static const char *SchemeDelimiter;
		static const char *UriSchemeFile;
		static const char *UriSchemeFtp;
		static const char *UriSchemeGopher;
		static const char *UriSchemeHttp;
		static const char *UriSchemeHttps;
		static const char *UriSchemeMailto;
		static const char *UriSchemeNetPipe;
		static const char *UriSchemeNetTcp;
		static const char *UriSchemeNews;
		static const char *UriSchemeNntp;
	private:
		std::string m_uri;
	};

	class Environment
	{
	public:
		union SpecialFolder {
			SpecialFolder(int value) : m_value(value) {}
			enum { Desktop = 0, Programs = 2, Personal = 5, MyDocuments = 5, Favorites = 6, Startup = 7, Recent = 8, SendTo = 9, StartMenu = 11, MyMusic = 13, MyVideos = 14,
				DesktopDirectory = 16, MyComputer = 17, NetworkShortcuts = 19, Fonts = 20, Templates = 21, CommonStartMenu = 22, CommonPrograms = 23, CommonStartup = 24, CommonDesktopDirectory = 25,
				ApplicationData = 26, PrinterShortcuts = 27, LocalApplicationData = 28,	InternetCache = 32, Cookies = 33, History = 34,	CommonApplicationData = 35,	Windows = 36, System = 37,
				ProgramFiles = 38, MyPictures = 39,	UserProfile = 40, SystemX86 = 41, ProgramFilesX86 = 42,	CommonProgramFiles = 43, CommonProgramFilesX86 = 44, CommonTemplates = 45,
				CommonDocuments = 46, CommonAdminTools = 47, AdminTools = 48, CommonMusic = 53, CommonPictures = 54, CommonVideos = 55,	Resources = 56,	LocalizedResources = 57, CommonOemLinks = 58,
				CDBurning = 59 };
			operator int() { return m_value; }
		private:
			int m_value;
		};

		union SpecialFolderOption {
			SpecialFolderOption( int value ) : m_value(value) {}
			enum { None = 0, DoNotVerify = 16384, Create = 32768 };
			operator int() { return m_value; }
		private:
			int m_value;
		};
		static std::string GetFolderPath(SpecialFolder specialFolder);
	};

};

using namespace System;
