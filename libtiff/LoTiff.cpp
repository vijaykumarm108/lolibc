/** 
Implementation of LoTiff
*/
#include <LoLibTiff.h>
#include "tiffio.h"
#include <string>

using namespace std;

namespace lo {

	Tiff::~Tiff()
	{
		Close();
	}

	void Tiff::Close()
	{
		if(m_tiff!=nullptr)
		{
			TIFFClose(reinterpret_cast<TIFF *>(m_tiff));
			m_tiff=nullptr;
		}
	}

	int		Tiff::GetField(uint32_t tag, ...)
	{
		va_list ap;
		int status;

		va_start(ap, tag);
		status = TIFFVGetField(reinterpret_cast<TIFF *>(m_tiff),tag,ap);
		va_end(ap);
		return (status);
	}

	int		Tiff::GetFieldInt(uint32_t tag, int _default)
	{
		GetField(tag,&_default);
		return _default;
	}

	void Tiff::OpenForReading(const char *file)
	{
		Close();
		m_tiff = reinterpret_cast<void *>(TIFFOpenW(wstring(file),"r"));
	}

	void Tiff::OpenForWriting(const char *file)
	{
		Close();
		m_tiff = reinterpret_cast<void *>(TIFFOpenW(wstring(file),"w"));
	}

	bool Tiff::ReadNextDirectory()
	{
		return TIFFReadDirectory(reinterpret_cast<TIFF *>(m_tiff)) == 1;
	}


	void	Tiff::ReadScanLine( void *data, size_t line)
	{
		TIFFReadScanline( reinterpret_cast<TIFF *>(m_tiff), data, line );
	}

	int	Tiff::SetField(uint32_t tagId, ...)
	{
		va_list ap;
		int status;

		va_start(ap, tagId);
		status = TIFFVSetField(reinterpret_cast<TIFF *>(m_tiff),tagId,ap);
		va_end(ap);
		return status;
	}

	void	Tiff::WriteDirectory()
	{
		TIFFWriteDirectory(reinterpret_cast<TIFF *>(m_tiff));
	}

	void	Tiff::WriteScanLine( void *line, size_t length )
	{
		TIFFWriteScanline(reinterpret_cast<TIFF *>(m_tiff),line,(uint32)length);
	}

}