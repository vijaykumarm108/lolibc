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

	void Tiff::OpenForReading(const char *file, const char *flags)
	{
		Close();
		m_tiff = reinterpret_cast<void *>(TIFFOpenW(wstring(file),"r"));
	}

	void Tiff::OpenForWriting(const char *file)
	{
		Close();
		m_tiff = reinterpret_cast<void *>(TIFFOpenW(wstring(file),"w"));
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