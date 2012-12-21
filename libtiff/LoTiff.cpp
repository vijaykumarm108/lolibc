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

	void Tiff::Open(const char *file)
	{
		Close();
		m_tiff = reinterpret_cast<void *>(TIFFOpenW(wstring(file),"w"));
	}

	void	Tiff::SetField(uint32_t tagId, uint32_t value)
	{
		TIFFSetField(reinterpret_cast<TIFF *>(m_tiff),tagId,value);
	}

	void	Tiff::SetField(uint32_t tagId, const char * value)
	{
		TIFFSetField(reinterpret_cast<TIFF *>(m_tiff),tagId,value);
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