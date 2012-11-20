/**
\file IO.h
*/
#pragma once
#include <lostlbase.h>
#include <System.h>

namespace System { namespace IO {

	class DirectoryInfo
	{
	public:
		DirectoryInfo(const char *directory);
	protected:
		const char *OriginalPath;
		const char *FullPath;
	};

	union SearchOption
	{
		SearchOption( int value) : m_value(value) {}
		enum { TopDirectoryOnly = 0, AllDirectories = 1 };
	private:
		int m_value;
	};

	class Directory
	{
	public:
		static DirectoryInfo CreateDirectory(const char *directory);
		static void Delete(const char *directory);
		static void Delete(const char *directory,bool recursive);
		static bool Exists(const char *directory);
		static std::vector<std::string> GetFiles(const char *path, const char *searchPattern, SearchOption searchOption );
	};

	union FileMode
	{
		FileMode( int value) : m_value(value) {}
		enum { CreateNew = 1, Create = 2, Open = 3, OpenOrCreate = 4, Truncate = 5,	Append = 6 };
	private:
		int m_value;
	};

	union FileAccess
	{
		FileAccess( int value) : m_value(value) {}
		enum { Read = 1, Write = 2, ReadWrite = 3 };
	private:
		int m_value;
	};

	union FileShare
	{
		FileShare( int value ) : m_value(value)	{}
		enum { None = 0, Read = 1, Write = 2, ReadWrite = 3, Delete = 4, Inheritable = 16 };
	private:
		int m_value;
	};

	class File
	{
	public:
		static lo::object Open( const char *fileName, FileMode fileMode, FileAccess fileAccess, FileShare fileShare );
	private:
	};

	class IOException //: public System::SystemException
	{
	public:
		IOException(const char *operation);// : SystemException(operation) {}
		IOException(char *operation);// : SystemException(operation) {}
	};

	class FileNotFoundException : public IOException
	{
	public:
		FileNotFoundException(char *fileName) : IOException(fileName) {}
	};

	class Path
	{
	public:
		static const char AltDirectorySeparatorChar = '/';
		static const char DirectorySeparatorChar = '\\';
		static const char PathSeparator = ';';
		static const char VolumeSeparatorChar = ':';
		static std::string ChangeExtension( const char *path, const char *extension );
		static std::string Combine( const char *path0, const char *path1);
		static std::string Combine( const char *path0, const char *path1, const char *path2);
		static std::string Combine( const char *path0, const char *path1, const char *path2, const char *path3);
		static std::string GetDirectoryName( const char *fullPath );
		static std::string GetExtension(const char *fileName);
		static std::string GetFileName(const char *fullPath);
		static std::string GetFileNameWithoutExtension( const char * path );
		static std::vector<char> GetInvalidPathChars();
		static std::string GetPathRoot( const char *path );
		static std::string GetRandomFileName();
		static std::string GetTempFileName();
		static std::string GetTempPath();
		static bool HasExtension( const char *path );
		static bool IsPathRooted( const char *path );
	private:
		static std::string AppendDirectorySeparator(const char *path);
		static bool EndsWithDirectorySeparator(const char *path);
	};

	union SeekOrigin
	{
	public:
		SeekOrigin(int value) : m_value(value) {}
		enum { Begin=0,Current=1,End=2 };
		operator int() { return m_value; };
	private:
		int m_value;
	};

	class Stream : public lo::object
	{
	public:
		void	Close();
		void	CopyTo( Stream &destination );
		int		get_Length();
		int		Read(std::vector<unsigned char> &data, int offset, int length);
		virtual int ReadByte();
		long	Seek( long offset, SeekOrigin origin );
		void	SetLength( long value );
		int		Write(const std::vector<unsigned char> &data, int offset, int length);
	private:
		lo::object m_pimpl;
		inline lo::Pimpl *pimpl()	{ return (lo::Pimpl *)m_pimpl.Ptr();}
	};

	class FileStream : public Stream
	{
	public:
		FileStream(lo::object &obj);
	};

	class MemoryStream : public Stream
	{
	public:
		MemoryStream(const std::vector<unsigned char>& buffer);
	};

	class TextReader : public lo::object
	{
	public:
		std::string ReadToEnd();
	};

	class StreamReader : public TextReader
	{
	public:
		StreamReader(const Stream &stream);
	};

} }

using namespace System::IO;