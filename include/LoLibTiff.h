// LoLibTiff - Tiff library - Link with lolibtiff
#include <lostlbase.h>
#include <stdarg.h>

namespace lo {

	/** TIFFTAG_SUBFILETYPE		254 */
	union TiffFileType
	{
	public:
		TiffFileType(uint32_t value) : m_value(value)	{}
		enum {REDUCEDIMAGE = 1,	/*!< reduced resolution version */
			PAGE = 2,			/*!< one page of many */
			MASK = 4			/*!< transparency mask */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_OSUBFILETYPE		255 */
	union TiffOFileType
	{
	public:
		TiffOFileType(uint32_t value) : m_value(value)	{}
		enum {IMAGE	 = 1,		/*!< full resolution image data */
			REDUCEDIMAGE = 2,	/*!< reduced size image data */
			PagPAGEe = 3		/*!< one page of many */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_COMPRESSION		259 */
	union TiffCompression
	{
	public:
		TiffCompression(uint32_t value) : m_value(value)	{}
		enum {
			NONE =		1,		/*!< dump mode */
			CCITTRLE =	2,		/*!< CCITT modified Huffman RLE */
			CCITTFAX3 =	3,		/*!< CCITT Group 3 fax encoding */
			CCITT_T4 =  3,		/*!< CCITT T.4 (TIFF 6 name) */
			CCITTFAX4 =	4,		/*!< CCITT Group 4 fax encoding */
			CCITT_T6 =  4,		/*!< CCITT T.6 (TIFF 6 name) */
			LZW      =  5,		/*!< Lempel-Ziv  & Welch */
			OJPEG =		6,		/*!< !6.0 JPEG */
			JPEG =		7,		/*!< %JPEG DCT compression */
			T85	=		9,		/*!< !TIFF/FX T.85 JBIG compression */
			T43	=		10,		/*!< !TIFF/FX T.43 colour by layered JBIG compression */
			NEXT =		32766,	/*!< NeXT 2-bit RLE */
			CCITTRLEW =	32771,	/*!< #1 w/ word alignment */
			PACKBITS =	32773,	/*!< Macintosh RLE */
			THUNDERSCAN = 32809,/*!< ThunderScan RLE */
			IT8CTPAD =	32895,	/*!< IT8 CT w/padding */
			IT8LW =		32896,	/*!< IT8 Linework RLE */
			IT8MP =		32897,	/*!< IT8 Monochrome picture */
			IT8BL =		32898,	/*!< IT8 Binary line art */
			PIXARFILM =	32908,	/*!< Pixar companded 10bit LZW */
			PIXARLOG =	32909,	/*!< Pixar companded 11bit ZIP */
			DEFLATE	=	32946,	/*!< Deflate compression */
			ADOBE_DEFLATE = 8,	/*!< Deflate compression, as recognized by Adobe */
			DCS =		32947,	/*!< Kodak DCS encoding */
			JBIG =		34661,	/*!< ISO JBIG */
			SGILOG	=	34676,	/*!< SGI Log Luminance RLE */
			SGILOG24 =	34677,	/*!< SGI Log 24-bit packed */
			JP2000 =    34712,	/*!< Leadtools JPEG2000 */
			LZMA =		34925	/*!< LZMA2 */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_PHOTOMETRIC		262 */
	union TiffPhotometric
	{
	public:
		TiffPhotometric( uint32_t value) : m_value(value) {}
		enum {
			MINISWHITE = 0,	/*!< min value is white */
			MINISBLACK = 1,	/*!< min value is black */
			RGB	= 2,		/*!< RGB color model */
			PALETTE = 3,	/*!< color map indexed */
			MASK = 4,		/*!< $holdout mask */
			SEPARATED = 5, 	/*!< !color separations */
			YCBCR = 6,		/*!< !CCIR 601 */
			CIELAB = 8,		/*!< !1976 CIE L*a*b* */
			ICCLAB = 9,		/*!< ICC L*a*b* [Adobe TIFF Technote 4] */
			ITULAB = 10,	/*!< ITU L*a*b* */
			LOGL = 32844,	/*!< CIE Log2(L) */
			LOGLUV = 32845	/*!< CIE Log2(L) (u',v') */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_THRESHHOLDING		263 */
	union TiffThreshholding
	{
	public:
		TiffThreshholding( uint32_t value) : m_value(value) {}
		enum {
			BILEVEL = 1,		/*!< b&w art scan */
			_HALFTONE	= 2,	/*!< or dithered scan */
			ERRORDIFFUSE = 3	/*!< usually floyd-steinberg */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_FILLORDER		266 */
	union TiffFillOrder
	{
	public:
		TiffFillOrder( uint32_t value) : m_value(value) {}
		enum {
			MSB2LSB = 1,		/*!< most significant -> least */
			LSB2MSB	= 2			/*!< least significant -> most */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_ORIENTATION		274:  +image orientation */
	union TiffOrientation
	{
	public:
		TiffOrientation( uint32_t value) : m_value(value) {}
		enum {
			TOPLEFT	 = 1,	/*!< row 0 top, col 0 lhs */
			TOPRIGHT = 2,	/*!< row 0 top, col 0 rhs */
			BOTRIGHT = 3,	/*!< row 0 bottom, col 0 rhs */
			BOTLEFT	 = 4,	/*!< row 0 bottom, col 0 lhs */
			LEFTTOP	 = 5,	/*!< row 0 lhs, col 0 top */
			RIGHTTOP = 6,	/*!< row 0 rhs, col 0 top */
			RIGHTBOT = 7,	/*!< row 0 rhs, col 0 bottom */
			LEFTBOT	 = 8	/*!< row 0 lhs, col 0 bottom */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_PLANARCONFIG		284: storage organization */ 
	union TiffPlanarConfig
	{
	public:
		TiffPlanarConfig( uint32_t value) : m_value(value) {}
		enum {
			CONTIG = 1,		/*!< single image plane */
			SEPARATE = 2	/*!< separate planes of data */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	/** TIFFTAG_RESOLUTIONUNIT		296: units of resolutions */
	union TiffResolutionUnit
	{
	public:
		TiffResolutionUnit( uint32_t value) : m_value(value) {}
		enum {
			NONE = 1,		/*!< no meaningful units */
			INCH = 2,		/*!< english */
			CENTIMETER = 3	/*!< metric */
		};
		operator uint32_t()	{return m_value;}
	private:
		uint32_t m_value;
	};

	class Tiff
	{
	public:
		Tiff() : m_tiff(nullptr) {}
		~Tiff();
		void	OpenForReading(const char *file);
		void	OpenForWriting(const char *file);
		void	Close();
		/** Gets multiple parameter fields. */
		int		GetField(uint32_t tag, ...);
		/** Gets a field with one parameter. */
		int		GetFieldInt(uint32_t tag1, int _default = 0);
		/** Gets BitsPerPixel: 258. */
		inline int					get_BitsPerPixel()				{return GetFieldInt(258);}
		/** TIFFTAG_ROWSPERSTRIP 278: rows per strip of data. */
		inline int					get_DefaultStripSize(int n = 0)	{return GetField(278,n);}
		/** get image width in pixels */
		inline int					get_ImageWidth()				{return GetFieldInt(256);}
		/** get image height in pixels */
		inline int					get_ImageLength()				{return GetFieldInt(257);}
		/** Gets the type of tiff file: RGB or monochrome. */
		inline TiffPhotometric		get_Photometric()				{return (TiffPhotometric)GetFieldInt(262);}
		/** TIFFTAG_PLANARCONFIG		284: storage organization */
		inline TiffPlanarConfig		get_PlanarConfig()				{return GetFieldInt(284);}
		/** Gets SamplesPerPixel. */
		inline int					get_SamplesPerPixel()			{return (TiffPhotometric)GetFieldInt(277);}



		/** Sets the file type: 254 */
		inline void	set_FileType(TiffFileType fileType)				{SetField(254,fileType);}
		/** bits per channel (sample) */
		inline void	set_BitsPerSample(uint32_t bps)					{SetField(258,bps);}
		/** +dithering matrix width */
		inline void set_CellWidth(uint32_t width)					{SetField(264,width);}
		/** +dithering matrix height */
		inline void set_CellHeight(uint32_t height)					{SetField(265,height);}
		/**  data compression technique */
		inline void set_Compression( TiffCompression compression)	{SetField(259,(uint32_t)compression); }
		/** name of doc. image is from */
		inline void set_DocumentName(const char *name)				{SetField(269,name);}
		/** info about image */
		inline void set_ImageDescription(const char *name)			{SetField(270,name);}
		/** set image width in pixels */
		inline void	set_ImageWidth( uint32_t width)					{SetField(256,width);}
		/** image height in pixels */
		inline void	set_ImageLength( uint32_t length)				{SetField(257,length);}
		/** scanner manufacturer name */
		inline void set_ManufacturerName(const char *name)			{SetField(271,name);}
		/** scanner model name/number */
		inline void set_ModelName(const char *name)					{SetField(272,name);}
		/** TIFFTAG_ORIENTATION		274:  +image orientation */
		inline void set_Orientation(TiffOrientation orientation)	{SetField(274,orientation);}
		/** TIFFTAG_PLANARCONFIG		284: storage organization */
		inline void set_PlanarConfig(TiffPlanarConfig config)		{SetField(284,config);}
		/** photometric interpretation */
		inline void set_Photometric( TiffPhotometric photometric )	{SetField(262,photometric); }
		/** TIFFTAG_PAGENUMBER: 297	- page numbers of multi-page */
		inline void set_PageNumber( uint32_t currentPage, uint32_t totalPages )	{ SetField(297,currentPage,totalPages); }
		/** TIFFTAG_STRIPOFFSETS: offsets to data strips */
		inline void set_StripOffsets(uint32_t offset)				{SetField(273,offset);}
		/** +thresholding used on data */
		inline void set_Threshholding( TiffThreshholding threshholding)	{SetField(263,threshholding);}
		/** data order within a byte */
		inline void set_TiffFillOrder( TiffFillOrder order)			{SetField(266,order);}
		/** TIFFTAG_SAMPLESPERPIXEL		277: samples per pixel */
		inline void set_SamplesPerPixel( uint32_t samplesPerPixel )	{SetField(277,samplesPerPixel);}
		/** TIFFTAG_ROWSPERSTRIP		278: rows per strip of data */
		inline void set_RowsPerStrip( uint32_t rowsPerStrip )		{SetField(278,rowsPerStrip);}
		/** TIFFTAG_STRIPBYTECOUNTS		279: bytes counts for strips */
		inline void set_StripByteCounts( uint32_t stripByteCounts )	{SetField(279,stripByteCounts);}
		/** TIFFTAG_MINSAMPLEVALUE		280: +minimum sample value */
		inline void set_MinSampleValue( uint32_t minSampleValue )	{SetField(280,minSampleValue);}
		/** TIFFTAG_MAXSAMPLEVALUE		281: +maximum sample value */
		inline void set_MaxSampleValue( uint32_t maxSampleValue )	{SetField(281,maxSampleValue);}
		/** TIFFTAG_XRESOLUTION			282: pixels/resolution in x */
		inline void set_XResolution( uint32_t xResolution )			{SetField(282,xResolution);}
		/** TIFFTAG_YRESOLUTION			283: pixels/resolution in y */
		inline void set_YResolution( uint32_t yResolution )			{SetField(283,yResolution);}
		/** TIFFTAG_RESOLUTIONUNIT		296: units of resolutions */
		inline void set_ResolutionUnit( TiffResolutionUnit unit)	{SetField(296,unit);}
		bool	ReadNextDirectory();
		void	ReadScanLine( void *line, size_t length);
		void	SetFieldV(uint32_t tag, int value, va_list ap);
		int		SetField(uint32_t tag, ...);
		void	WriteDirectory();
		void	WriteScanLine( void *data, size_t line );
	private:
		void	*m_tiff;
	};

}