/*!
\file printer_driver.h - Lo-Overhead windows printer driver interface definitions.
*/
#pragma once
#include "gdi32.h"
#include <guiddef.h>
#include <winspool.h>

#ifndef EXTERN_C
    #ifdef __cplusplus
        #define EXTERN_C    extern "C"
    #else // !defined(__cplusplus)
        #define EXTERN_C    extern
    #endif // !defined(__cplusplus)
#endif // !defined(EXTERN_C)

#ifndef DEFINE_GUID
#ifndef INITGUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const GUID FAR name
#else // !defined(INITGUID)

#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
#endif // !defined(INITGUID)
#endif // !defined(DEFINE_GUID)

#ifndef DEFINE_GUIDEX
    #define DEFINE_GUIDEX(name) EXTERN_C const CDECL GUID name
#endif // !defined(DEFINE_GUIDEX)

#ifndef STATICGUIDOF
    #define STATICGUIDOF(guid) STATIC_##guid
#endif // !defined(STATICGUIDOF)

#ifndef GUID_DEFINED
    #define GUID_DEFINED
    typedef struct _GUID {
        ULONG   Data1;
        USHORT  Data2;
        USHORT  Data3;
        UCHAR   Data4[8];
    } GUID;
#endif // !defined(GUID_DEFINED)

#ifndef IsEqualGUID
    #define IsEqualGUID(guid1, guid2) \
        (!memcmp((guid1), (guid2), sizeof(GUID)))
#endif // !defined(IsEqualGUID)

#ifndef IsEqualIID
    #define IsEqualIID IsEqualGUID
#endif // !defined(IsEqualIID)

//
// Standard DirectX HAL includes
//

//#include <ddrawint.h>
//#include <d3dnthal.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef LONG_PTR (WINAPI *PFN)();
typedef void		*HBM;
typedef void		*HDEV;
typedef void		*HSURF;
typedef void		*DHSURF;
typedef void		*DHPDEV;
typedef void		*HDRVOBJ;


//
// drivers and other components that include this should NOT include
// windows.h  They should be system components that only use GDI internals
// and therefore only include wingdi.h
//

#if defined(_X86_) && !defined(USERMODE_DRIVER) && !defined(BUILD_WOW6432)
//
// x86 does not support floating-point instruction in the kernel mode,
// the floating-point data would like be handled 32bits value as double words.
//
typedef DWORD FLOATL;
#else
//
// Any platform that has support for floats in the kernel
//
typedef FLOAT FLOATL;
#endif // _X86_

typedef LONG	    PTRDIFF;
typedef PTRDIFF    *PPTRDIFF;
typedef LONG        FIX;
typedef FIX        *PFIX;
typedef ULONG       ROP4;
typedef ULONG       MIX;
typedef ULONG       HGLYPH;
typedef HGLYPH     *PHGLYPH;
#define HGLYPH_INVALID ((HGLYPH)-1)

typedef ULONG           IDENT;

//
// handles for font file and font context objects
//

typedef ULONG_PTR HFF;
typedef ULONG_PTR HFC;
#define HFF_INVALID ((HFF) 0)
#define HFC_INVALID ((HFC) 0)

#define FD_ERROR  0xFFFFFFFF
#define DDI_ERROR 0xFFFFFFFF

typedef struct _POINTE      /* pte  */
{
    FLOATL x;
    FLOATL y;
} POINTE, *PPOINTE;

typedef union _FLOAT_LONG
{
    FLOATL   e;
    LONG     l;
} FLOAT_LONG, *PFLOAT_LONG;

typedef struct  _POINTFIX
{
    FIX   x;
    FIX   y;
} POINTFIX, *PPOINTFIX;

typedef struct _RECTFX
{
    FIX   xLeft;
    FIX   yTop;
    FIX   xRight;
    FIX   yBottom;
} RECTFX, *PRECTFX;

#define LTOFX(x)            ((x)<<4)

#define FXTOL(x)            ((x)>>4)
#define FXTOLFLOOR(x)       ((x)>>4)
#define FXTOLCEILING(x)     ((x + 0x0F)>>4)
#define FXTOLROUND(x)       ((((x) >> 3) + 1) >> 1)

// context information

typedef struct _FD_XFORM {
    FLOATL eXX;
    FLOATL eXY;
    FLOATL eYX;
    FLOATL eYY;
} FD_XFORM, *PFD_XFORM;


typedef struct _FD_DEVICEMETRICS {       // devm
    FLONG  flRealizedType;
    POINTE pteBase;
    POINTE pteSide;
    LONG   lD;
    FIX    fxMaxAscender;
    FIX    fxMaxDescender;
    POINTL ptlUnderline1;
    POINTL ptlStrikeOut;
    POINTL ptlULThickness;
    POINTL ptlSOThickness;
    ULONG  cxMax;                      // max pel width of bitmaps

// the fields formerly in REALIZE_EXTRA as well as some new fields:

    ULONG cyMax;      // did not use to be here
    ULONG cjGlyphMax; // (cxMax + 7)/8 * cyMax, or at least it should be

    FD_XFORM  fdxQuantized;
    LONG      lNonLinearExtLeading;
    LONG      lNonLinearIntLeading;
    LONG      lNonLinearMaxCharWidth;
    LONG      lNonLinearAvgCharWidth;

// some new fields

    LONG      lMinA;
    LONG      lMinC;
    LONG      lMinD;

    LONG      alReserved[1]; // just in case we need it.

} FD_DEVICEMETRICS, *PFD_DEVICEMETRICS;

typedef struct _LIGATURE { /* lig */
        ULONG culSize;
        LPWSTR pwsz;
        ULONG chglyph;
        HGLYPH ahglyph[1];
} LIGATURE, *PLIGATURE;

typedef struct _FD_LIGATURE {
        ULONG culThis;
        ULONG ulType;
        ULONG cLigatures;
        LIGATURE alig[1];
} FD_LIGATURE;


// glyph handle must be 32 bit


// signed 16 bit integer type denoting number of FUnit's

typedef SHORT FWORD;

// point in the 32.32 bit precission

typedef struct _POINTQF    // ptq
{
    LARGE_INTEGER x;
    LARGE_INTEGER y;
} POINTQF, *PPOINTQF;

//. Structures


//     devm.flRealizedType flags

// FDM_TYPE_ZERO_BEARINGS           // all glyphs have zero a and c spaces

// the following two features refer to all glyphs in this font realization

// FDM_TYPE_CHAR_INC_EQUAL_BM_BASE  // base width == cx for horiz, == cy for vert.
// FDM_TYPE_MAXEXT_EQUAL_BM_SIDE    // side width == cy for horiz, == cx for vert.

#define FDM_TYPE_BM_SIDE_CONST          0x00000001
#define FDM_TYPE_MAXEXT_EQUAL_BM_SIDE   0x00000002
#define FDM_TYPE_CHAR_INC_EQUAL_BM_BASE 0x00000004
#define FDM_TYPE_ZERO_BEARINGS          0x00000008
#define FDM_TYPE_CONST_BEARINGS         0x00000010


// structures for describing a supported set of glyphs in a font

typedef struct _WCRUN {
    WCHAR   wcLow;        // lowest character in run  inclusive
    USHORT  cGlyphs;      // wcHighInclusive = wcLow + cGlyphs - 1;
    HGLYPH *phg;          // pointer to an array of cGlyphs HGLYPH's
} WCRUN, *PWCRUN;

// If phg is set to (HGLYPH *)NULL, for all wc's in this particular run
// the handle can be computed as simple zero extension:
//        HGLYPH hg = (HGLYPH) wc;
//
// If phg is not NULL, memory pointed to by phg, allocated by the driver,
// WILL NOT MOVE.


typedef struct _FD_GLYPHSET {
    ULONG    cjThis;           // size of this structure in butes
    FLONG    flAccel;          // accel flags, bits to be explained below
    ULONG    cGlyphsSupported; // sum over all wcrun's of wcrun.cGlyphs
    ULONG    cRuns;
    WCRUN    awcrun[1];        // an array of cRun WCRUN structures
} FD_GLYPHSET, *PFD_GLYPHSET;

typedef struct _FD_GLYPHATTR {
    ULONG    cjThis;           // size of this structure in butes
    ULONG    cGlyphs;
    ULONG    iMode;
    BYTE     aGlyphAttr[1];    // an array of byte
} FD_GLYPHATTR, *PFD_GLYPHATTR;

// If GS_UNICODE_HANDLES  bit is set,
// for ALL WCRUNS in this FD_GLYPHSET the handles are
// obtained by zero extending unicode code points of
// the corresponding supported glyphs, i.e. all gs.phg's are NULL

#define GS_UNICODE_HANDLES      0x00000001

// If GS_8BIT_HANDLES bit is set, all handles are in 0-255 range.
// This is just an ansi font then and we are really making up all
// the unicode stuff about this font.

#define GS_8BIT_HANDLES         0x00000002

// all handles fit in 16 bits.
// to 8 bit handles as it should.

#define GS_16BIT_HANDLES        0x00000004


// ligatures


typedef struct _FD_KERNINGPAIR {
    WCHAR  wcFirst;
    WCHAR  wcSecond;
    FWORD  fwdKern;
} FD_KERNINGPAIR;

// IFIMETRICS constants

#define FM_VERSION_NUMBER                   0x0

//
// IFIMETRICS::fsType flags
//
#define FM_TYPE_LICENSED                    0x2
#define FM_READONLY_EMBED                   0x4
#define FM_EDITABLE_EMBED                   0x8
#define FM_NO_EMBEDDING                     FM_TYPE_LICENSED

//
// IFIMETRICS::flInfo flags
//
#define FM_INFO_TECH_TRUETYPE               0x00000001
#define FM_INFO_TECH_BITMAP                 0x00000002
#define FM_INFO_TECH_STROKE                 0x00000004
#define FM_INFO_TECH_OUTLINE_NOT_TRUETYPE   0x00000008
#define FM_INFO_ARB_XFORMS                  0x00000010
#define FM_INFO_1BPP                        0x00000020
#define FM_INFO_4BPP                        0x00000040
#define FM_INFO_8BPP                        0x00000080
#define FM_INFO_16BPP                       0x00000100
#define FM_INFO_24BPP                       0x00000200
#define FM_INFO_32BPP                       0x00000400
#define FM_INFO_INTEGER_WIDTH               0x00000800
#define FM_INFO_CONSTANT_WIDTH              0x00001000
#define FM_INFO_NOT_CONTIGUOUS              0x00002000
#define FM_INFO_TECH_MM                     0x00004000
#define FM_INFO_RETURNS_OUTLINES            0x00008000
#define FM_INFO_RETURNS_STROKES             0x00010000
#define FM_INFO_RETURNS_BITMAPS             0x00020000
#define FM_INFO_DSIG                        0x00040000 // FM_INFO_UNICODE_COMPLIANT
#define FM_INFO_RIGHT_HANDED                0x00080000
#define FM_INFO_INTEGRAL_SCALING            0x00100000
#define FM_INFO_90DEGREE_ROTATIONS          0x00200000
#define FM_INFO_OPTICALLY_FIXED_PITCH       0x00400000
#define FM_INFO_DO_NOT_ENUMERATE            0x00800000
#define FM_INFO_ISOTROPIC_SCALING_ONLY      0x01000000
#define FM_INFO_ANISOTROPIC_SCALING_ONLY    0x02000000
#define FM_INFO_TECH_CFF                    0x04000000
#define FM_INFO_FAMILY_EQUIV                0x08000000
#define FM_INFO_DBCS_FIXED_PITCH            0x10000000
#define FM_INFO_NONNEGATIVE_AC              0x20000000
#define FM_INFO_IGNORE_TC_RA_ABLE           0x40000000
#define FM_INFO_TECH_TYPE1                  0x80000000

// max number of charsets supported in a tt font, 16 according to win95 guys

#define MAXCHARSETS 16

//
// IFIMETRICS::ulPanoseCulture
//
#define  FM_PANOSE_CULTURE_LATIN     0x0


//
// IFMETRICS::fsSelection flags
//
#define  FM_SEL_ITALIC          0x0001
#define  FM_SEL_UNDERSCORE      0x0002
#define  FM_SEL_NEGATIVE        0x0004
#define  FM_SEL_OUTLINED        0x0008
#define  FM_SEL_STRIKEOUT       0x0010
#define  FM_SEL_BOLD            0x0020
#define  FM_SEL_REGULAR         0x0040

//
// The FONTDIFF structure contains all of the fields that could
// possibly change under simulation
//
typedef struct _FONTDIFF {
    BYTE   jReserved1;      // 0x0
    BYTE   jReserved2;      // 0x1
    BYTE   jReserved3;      // 0x2
    BYTE   bWeight;         // 0x3  Panose Weight
    USHORT usWinWeight;     // 0x4
    FSHORT fsSelection;     // 0x6
    FWORD  fwdAveCharWidth; // 0x8
    FWORD  fwdMaxCharInc;   // 0xA
    POINTL ptlCaret;        // 0xC
} FONTDIFF;

typedef struct _FONTSIM {
    PTRDIFF  dpBold;       // offset from beginning of FONTSIM to FONTDIFF
    PTRDIFF  dpItalic;     // offset from beginning of FONTSIM to FONTDIFF
    PTRDIFF  dpBoldItalic; // offset from beginning of FONTSIM to FONTDIFF
} FONTSIM;


typedef struct _IFIMETRICS {
    ULONG    cjThis;           // includes attached information
    ULONG    cjIfiExtra;       // sizeof IFIEXTRA if any, formerly ulVersion
    PTRDIFF  dpwszFamilyName;
    PTRDIFF  dpwszStyleName;
    PTRDIFF  dpwszFaceName;
    PTRDIFF  dpwszUniqueName;
    PTRDIFF  dpFontSim;
    LONG     lEmbedId;
    LONG     lItalicAngle;
    LONG     lCharBias;

// dpCharSet field replaced alReserved[0].
// If the 3.51 pcl minidrivers are still to work on NT 4.0 this field must not
// move because they will have 0 at this position.

    PTRDIFF  dpCharSets;            // only used if > 1 charset supported
    BYTE     jWinCharSet;           // as in LOGFONT::lfCharSet
    BYTE     jWinPitchAndFamily;    // as in LOGFONT::lfPitchAndFamily
    USHORT   usWinWeight;           // as in LOGFONT::lfWeight
    ULONG    flInfo;                // see above
    USHORT   fsSelection;           // see above
    USHORT   fsType;                // see above
    FWORD    fwdUnitsPerEm;         // em height
    FWORD    fwdLowestPPEm;         // readable limit
    FWORD    fwdWinAscender;
    FWORD    fwdWinDescender;
    FWORD    fwdMacAscender;
    FWORD    fwdMacDescender;
    FWORD    fwdMacLineGap;
    FWORD    fwdTypoAscender;
    FWORD    fwdTypoDescender;
    FWORD    fwdTypoLineGap;
    FWORD    fwdAveCharWidth;
    FWORD    fwdMaxCharInc;
    FWORD    fwdCapHeight;
    FWORD    fwdXHeight;
    FWORD    fwdSubscriptXSize;
    FWORD    fwdSubscriptYSize;
    FWORD    fwdSubscriptXOffset;
    FWORD    fwdSubscriptYOffset;
    FWORD    fwdSuperscriptXSize;
    FWORD    fwdSuperscriptYSize;
    FWORD    fwdSuperscriptXOffset;
    FWORD    fwdSuperscriptYOffset;
    FWORD    fwdUnderscoreSize;
    FWORD    fwdUnderscorePosition;
    FWORD    fwdStrikeoutSize;
    FWORD    fwdStrikeoutPosition;
    BYTE     chFirstChar;           // for win 3.1 compatibility
    BYTE     chLastChar;            // for win 3.1 compatibility
    BYTE     chDefaultChar;         // for win 3.1 compatibility
    BYTE     chBreakChar;           // for win 3.1 compatibility
    WCHAR    wcFirstChar;           // lowest supported code in Unicode set
    WCHAR    wcLastChar;            // highest supported code in Unicode set
    WCHAR    wcDefaultChar;
    WCHAR    wcBreakChar;
    POINTL   ptlBaseline;           //
    POINTL   ptlAspect;             // designed aspect ratio (bitmaps)
    POINTL   ptlCaret;              // points along caret
    RECTL    rclFontBox;            // bounding box for all glyphs (font space)
    BYTE     achVendId[4];          // as per TrueType
    ULONG    cKerningPairs;
    ULONG    ulPanoseCulture;
    PANOSE   panose;

#if defined(_WIN64)

    //
    // IFIMETRICS must begin on a 64-bit boundary
    //

    PVOID    Align;

#endif

} IFIMETRICS, *PIFIMETRICS;


// rather than adding the fields of IFIEXTRA  to IFIMETRICS itself
// we add them as a separate structure. This structure, if present at all,
// lies below IFIMETRICS in memory.
// If IFIEXTRA is present at all, ifi.cjIfiExtra (formerly ulVersion)
// will contain size of IFIEXTRA including any reserved fields.
// That way ulVersion = 0 (NT 3.51 or less) printer minidrivers
// will work with NT 4.0.

typedef struct _IFIEXTRA
{
    ULONG    ulIdentifier;   // used for Type 1 fonts only
    PTRDIFF  dpFontSig;      // nontrivial for tt only, at least for now.
    ULONG    cig;            // maxp->numGlyphs, # of distinct glyph indicies
    PTRDIFF  dpDesignVector; // offset to design vector for mm instances
    PTRDIFF  dpAxesInfoW;    // offset to full axes info for base mm font
    ULONG    aulReserved[1]; // in case we need even more stuff in the future
} IFIEXTRA, *PIFIEXTRA;

#define SIZEOFDV(cAxes) (offsetof(DESIGNVECTOR,dvValues) + (cAxes)*sizeof(LONG))
#define SIZEOFAXIW(cAxes) (offsetof(AXESLISTW,axlAxisInfo) + (cAxes)*sizeof(AXISINFOW))
#define SIZEOFAXIA(cAxes) (offsetof(AXESLISTA,axlAxisInfo) + (cAxes)*sizeof(AXISINFOA))

/**************************************************************************\
 *
\**************************************************************************/

/* OpenGL DDI ExtEscape escape numbers (4352 - 4607) */

#define OPENGL_CMD      4352        /* for OpenGL ExtEscape */
#define OPENGL_GETINFO  4353        /* for OpenGL ExtEscape */
#define WNDOBJ_SETUP    4354        /* for live video ExtEscape */

#define DDI_DRIVER_VERSION     0x00020000
#define DDI_DRIVER_VERSION_NT4 0x00020000
#define DDI_DRIVER_VERSION_SP3 0x00020003
#define DDI_DRIVER_VERSION_NT5 0x00030000

#define GDI_DRIVER_VERSION 0x4000   /* for NT version 4.0.00 */

typedef LONG_PTR (WINAPI *PFN)();

typedef struct  _DRVFN  /* drvfn */
{
    ULONG   iFunc;
    PFN     pfn;
} DRVFN, *PDRVFN;

/* Required functions           */

#define INDEX_DrvEnablePDEV                      0L
#define INDEX_DrvCompletePDEV                    1L
#define INDEX_DrvDisablePDEV                     2L
#define INDEX_DrvEnableSurface                   3L
#define INDEX_DrvDisableSurface                  4L

/* Other functions              */

#define INDEX_DrvAssertMode                      5L
#define INDEX_DrvOffset                          6L     // Obsolete
#define INDEX_DrvResetPDEV                       7L
#define INDEX_DrvDisableDriver                   8L
#define INDEX_DrvCreateDeviceBitmap             10L
#define INDEX_DrvDeleteDeviceBitmap             11L
#define INDEX_DrvRealizeBrush                   12L
#define INDEX_DrvDitherColor                    13L
#define INDEX_DrvStrokePath                     14L
#define INDEX_DrvFillPath                       15L
#define INDEX_DrvStrokeAndFillPath              16L
#define INDEX_DrvPaint                          17L
#define INDEX_DrvBitBlt                         18L
#define INDEX_DrvCopyBits                       19L
#define INDEX_DrvStretchBlt                     20L
#define INDEX_DrvSetPalette                     22L
#define INDEX_DrvTextOut                        23L
#define INDEX_DrvEscape                         24L
#define INDEX_DrvDrawEscape                     25L
#define INDEX_DrvQueryFont                      26L
#define INDEX_DrvQueryFontTree                  27L
#define INDEX_DrvQueryFontData                  28L
#define INDEX_DrvSetPointerShape                29L
#define INDEX_DrvMovePointer                    30L
#define INDEX_DrvLineTo                         31L
#define INDEX_DrvSendPage                       32L
#define INDEX_DrvStartPage                      33L
#define INDEX_DrvEndDoc                         34L
#define INDEX_DrvStartDoc                       35L
#define INDEX_DrvGetGlyphMode                   37L
#define INDEX_DrvSynchronize                    38L
#define INDEX_DrvSaveScreenBits                 40L
#define INDEX_DrvGetModes                       41L
#define INDEX_DrvFree                           42L
#define INDEX_DrvDestroyFont                    43L
#define INDEX_DrvQueryFontCaps                  44L
#define INDEX_DrvLoadFontFile                   45L
#define INDEX_DrvUnloadFontFile                 46L
#define INDEX_DrvFontManagement                 47L
#define INDEX_DrvQueryTrueTypeTable             48L
#define INDEX_DrvQueryTrueTypeOutline           49L
#define INDEX_DrvGetTrueTypeFile                50L
#define INDEX_DrvQueryFontFile                  51L
#define INDEX_DrvMovePanning                    52L
#define INDEX_DrvQueryAdvanceWidths             53L
#define INDEX_DrvSetPixelFormat                 54L
#define INDEX_DrvDescribePixelFormat            55L
#define INDEX_DrvSwapBuffers                    56L
#define INDEX_DrvStartBanding                   57L
#define INDEX_DrvNextBand                       58L
#define INDEX_DrvGetDirectDrawInfo              59L
#define INDEX_DrvEnableDirectDraw               60L
#define INDEX_DrvDisableDirectDraw              61L
#define INDEX_DrvQuerySpoolType                 62L
#define INDEX_DrvIcmCreateColorTransform        64L
#define INDEX_DrvIcmDeleteColorTransform        65L
#define INDEX_DrvIcmCheckBitmapBits             66L
#define INDEX_DrvIcmSetDeviceGammaRamp          67L
#define INDEX_DrvGradientFill                   68L
#define INDEX_DrvStretchBltROP                  69L
#define INDEX_DrvPlgBlt                         70L
#define INDEX_DrvAlphaBlend                     71L
#define INDEX_DrvSynthesizeFont                 72L
#define INDEX_DrvGetSynthesizedFontFiles        73L
#define INDEX_DrvTransparentBlt                 74L
#define INDEX_DrvQueryPerBandInfo               75L
#define INDEX_DrvQueryDeviceSupport             76L

#define INDEX_DrvReserved1                      77L
#define INDEX_DrvReserved2                      78L
#define INDEX_DrvReserved3                      79L
#define INDEX_DrvReserved4                      80L
#define INDEX_DrvReserved5                      81L
#define INDEX_DrvReserved6                      82L
#define INDEX_DrvReserved7                      83L
#define INDEX_DrvReserved8                      84L

#define INDEX_DrvDeriveSurface                  85L
#define INDEX_DrvQueryGlyphAttrs                86L
#define INDEX_DrvNotify                         87L
#define INDEX_DrvSynchronizeSurface             88L

/* The total number of dispatched functions */

#define INDEX_LAST                              89L

typedef struct  tagDRVENABLEDATA
{
    ULONG   iDriverVersion;
    ULONG   c;
    DRVFN  *pdrvfn;
} DRVENABLEDATA, *PDRVENABLEDATA;

typedef struct  tagDEVINFO
{
    FLONG       flGraphicsCaps;
    LOGFONTW    lfDefaultFont;
    LOGFONTW    lfAnsiVarFont;
    LOGFONTW    lfAnsiFixFont;
    ULONG       cFonts;
    ULONG       iDitherFormat;
    USHORT      cxDither;
    USHORT      cyDither;
    HPALETTE    hpalDefault;
    FLONG       flGraphicsCaps2;
} DEVINFO, *PDEVINFO;

// flGraphicsCaps flags for DEVINFO:

#define GCAPS_BEZIERS           0x00000001
#define GCAPS_GEOMETRICWIDE     0x00000002
#define GCAPS_ALTERNATEFILL     0x00000004
#define GCAPS_WINDINGFILL       0x00000008
#define GCAPS_HALFTONE          0x00000010
#define GCAPS_COLOR_DITHER      0x00000020
#define GCAPS_HORIZSTRIKE       0x00000040      // Obsolete
#define GCAPS_VERTSTRIKE        0x00000080      // Obsolete
#define GCAPS_OPAQUERECT        0x00000100
#define GCAPS_VECTORFONT        0x00000200
#define GCAPS_MONO_DITHER       0x00000400
#define GCAPS_ASYNCCHANGE       0x00000800      // Obsolete
#define GCAPS_ASYNCMOVE         0x00001000
#define GCAPS_DONTJOURNAL       0x00002000
#define GCAPS_DIRECTDRAW        0x00004000      // Obsolete
#define GCAPS_ARBRUSHOPAQUE     0x00008000
#define GCAPS_PANNING           0x00010000
#define GCAPS_HIGHRESTEXT       0x00040000
#define GCAPS_PALMANAGED        0x00080000
#define GCAPS_DITHERONREALIZE   0x00200000
#define GCAPS_NO64BITMEMACCESS  0x00400000      // Obsolete
#define GCAPS_FORCEDITHER       0x00800000
#define GCAPS_GRAY16            0x01000000
#define GCAPS_ICM               0x02000000
#define GCAPS_CMYKCOLOR         0x04000000
#define GCAPS_LAYERED           0x08000000
#define GCAPS_ARBRUSHTEXT       0x10000000
#define GCAPS_SCREENPRECISION   0x20000000
#define GCAPS_FONT_RASTERIZER   0x40000000      // the device has built in tt rasterizer
#define GCAPS_NUP               0x80000000

// flGraphicsCaps2 flags for DEVINFO:

#define GCAPS2_JPEGSRC          0x00000001
#define GCAPS2_xxxx             0x00000002
#define GCAPS2_PNGSRC           0x00000008
#define GCAPS2_CHANGEGAMMARAMP  0x00000010
#define GCAPS2_ALPHACURSOR      0x00000020
#define GCAPS2_SYNCFLUSH        0x00000040
#define GCAPS2_SYNCTIMER        0x00000080
#define GCAPS2_ICD_MULTIMON     0x00000100

typedef struct  _LINEATTRS
{
    FLONG       fl;
    ULONG       iJoin;
    ULONG       iEndCap;
    FLOAT_LONG  elWidth;
    FLOATL      eMiterLimit;
    ULONG       cstyle;
    PFLOAT_LONG pstyle;
    FLOAT_LONG  elStyleState;
} LINEATTRS, *PLINEATTRS;

#define LA_GEOMETRIC        0x00000001
#define LA_ALTERNATE        0x00000002
#define LA_STARTGAP         0x00000004
#define LA_STYLED           0x00000008

#define JOIN_ROUND          0L
#define JOIN_BEVEL          1L
#define JOIN_MITER          2L

#define ENDCAP_ROUND        0L
#define ENDCAP_SQUARE       1L
#define ENDCAP_BUTT         2L

typedef LONG  LDECI4;

typedef struct _XFORML {
    FLOATL  eM11;
    FLOATL  eM12;
    FLOATL  eM21;
    FLOATL  eM22;
    FLOATL  eDx;
    FLOATL  eDy;
} XFORML, *PXFORML;

typedef struct _CIECHROMA
{
    LDECI4   x;
    LDECI4   y;
    LDECI4   Y;
}CIECHROMA;

typedef struct _COLORINFO
{
    CIECHROMA  Red;
    CIECHROMA  Green;
    CIECHROMA  Blue;
    CIECHROMA  Cyan;
    CIECHROMA  Magenta;
    CIECHROMA  Yellow;
    CIECHROMA  AlignmentWhite;

    LDECI4  RedGamma;
    LDECI4  GreenGamma;
    LDECI4  BlueGamma;

    LDECI4  MagentaInCyanDye;
    LDECI4  YellowInCyanDye;
    LDECI4  CyanInMagentaDye;
    LDECI4  YellowInMagentaDye;
    LDECI4  CyanInYellowDye;
    LDECI4  MagentaInYellowDye;
}COLORINFO, *PCOLORINFO;

// Allowed values for GDIINFO.ulPrimaryOrder.

#define PRIMARY_ORDER_ABC       0
#define PRIMARY_ORDER_ACB       1
#define PRIMARY_ORDER_BAC       2
#define PRIMARY_ORDER_BCA       3
#define PRIMARY_ORDER_CBA       4
#define PRIMARY_ORDER_CAB       5

// Allowed values for GDIINFO.ulHTPatternSize.

#define HT_PATSIZE_2x2          0
#define HT_PATSIZE_2x2_M        1
#define HT_PATSIZE_4x4          2
#define HT_PATSIZE_4x4_M        3
#define HT_PATSIZE_6x6          4
#define HT_PATSIZE_6x6_M        5
#define HT_PATSIZE_8x8          6
#define HT_PATSIZE_8x8_M        7
#define HT_PATSIZE_10x10        8
#define HT_PATSIZE_10x10_M      9
#define HT_PATSIZE_12x12        10
#define HT_PATSIZE_12x12_M      11
#define HT_PATSIZE_14x14        12
#define HT_PATSIZE_14x14_M      13
#define HT_PATSIZE_16x16        14
#define HT_PATSIZE_16x16_M      15
#define HT_PATSIZE_SUPERCELL    16
#define HT_PATSIZE_SUPERCELL_M  17
#define HT_PATSIZE_USER         18
#define HT_PATSIZE_MAX_INDEX    HT_PATSIZE_USER
#define HT_PATSIZE_DEFAULT      HT_PATSIZE_SUPERCELL_M

#define HT_USERPAT_CX_MIN       4
#define HT_USERPAT_CX_MAX       256
#define HT_USERPAT_CY_MIN       4
#define HT_USERPAT_CY_MAX       256


// Allowed values for GDIINFO.ulHTOutputFormat.

#define HT_FORMAT_1BPP          0
#define HT_FORMAT_4BPP          2
#define HT_FORMAT_4BPP_IRGB     3
#define HT_FORMAT_8BPP          4
#define HT_FORMAT_16BPP         5
#define HT_FORMAT_24BPP         6
#define HT_FORMAT_32BPP         7


// Allowed values for GDIINFO.flHTFlags.

#define HT_FLAG_SQUARE_DEVICE_PEL       0x00000001
#define HT_FLAG_HAS_BLACK_DYE           0x00000002
#define HT_FLAG_ADDITIVE_PRIMS          0x00000004
#define HT_FLAG_USE_8BPP_BITMASK        0x00000008
#define HT_FLAG_INK_HIGH_ABSORPTION     0x00000010
#define HT_FLAG_INK_ABSORPTION_INDICES  0x00000060
#define HT_FLAG_DO_DEVCLR_XFORM         0x00000080
#define HT_FLAG_OUTPUT_CMY              0x00000100
#define HT_FLAG_PRINT_DRAFT_MODE        0x00000200
#define HT_FLAG_8BPP_CMY332_MASK        0xFF000000

#define MAKE_CMYMASK_BYTE(c,m,y)    ((BYTE)(((BYTE)(c) & 0x07) << 5) |      \
                                     (BYTE)(((BYTE)(m) & 0x07) << 2) |      \
                                     (BYTE)((BYTE)(y) & 0x03))

#define MAKE_CMY332_MASK(c,m,y)     ((DWORD)(((DWORD)(c) & 0x07) << 29) |   \
                                     (DWORD)(((DWORD)(m) & 0x07) << 26) |   \
                                     (DWORD)(((DWORD)(y) & 0x03) << 24))


#define HT_FLAG_INK_ABSORPTION_IDX0     0x00000000
#define HT_FLAG_INK_ABSORPTION_IDX1     0x00000020
#define HT_FLAG_INK_ABSORPTION_IDX2     0x00000040
#define HT_FLAG_INK_ABSORPTION_IDX3     0x00000060

#define HT_FLAG_HIGHEST_INK_ABSORPTION  (HT_FLAG_INK_HIGH_ABSORPTION    |   \
                                         HT_FLAG_INK_ABSORPTION_IDX3)
#define HT_FLAG_HIGHER_INK_ABSORPTION   (HT_FLAG_INK_HIGH_ABSORPTION    |   \
                                         HT_FLAG_INK_ABSORPTION_IDX2)
#define HT_FLAG_HIGH_INK_ABSORPTION     (HT_FLAG_INK_HIGH_ABSORPTION    |   \
                                         HT_FLAG_INK_ABSORPTION_IDX1)
#define HT_FLAG_NORMAL_INK_ABSORPTION   HT_FLAG_INK_ABSORPTION_IDX0
#define HT_FLAG_LOW_INK_ABSORPTION      (HT_FLAG_INK_ABSORPTION_IDX1)
#define HT_FLAG_LOWER_INK_ABSORPTION    (HT_FLAG_INK_ABSORPTION_IDX2)
#define HT_FLAG_LOWEST_INK_ABSORPTION   (HT_FLAG_INK_ABSORPTION_IDX3)

// Allowed values for GDIINFO.ulPhysicalPixelCharacteristics

#define PPC_DEFAULT                        0x0
#define PPC_UNDEFINED                      0x1
#define PPC_RGB_ORDER_VERTICAL_STRIPES     0x2
#define PPC_BGR_ORDER_VERTICAL_STRIPES     0x3
#define PPC_RGB_ORDER_HORIZONTAL_STRIPES   0x4
#define PPC_BGR_ORDER_HORIZONTAL_STRIPES   0x5

// GDIINFO.ulPhysicalPixelGamma should be set either to the scaled
// gamma (x1000) of the physical pixel or one of the following
// values.  For example, a 2.2 gamma would be represented as 2200

#define PPG_DEFAULT                        0
#define PPG_SRGB                           1

//
// HT_FLAG_DO_DEVCLR_XFORM flag specified devices and/or drivers are required
// gdi halftone to do a device transform when ICM is off, the device transform
// take a input RGB value and map it to the device color space to produced
// perceived density same as input RGB color values.  This flag only valid if
// it is a printer device surface and its format is 16bpp or 24bpp.
//
// ** If devices are additive and/or device surface is 1bpp, 4bpp or 8bpp, then
//    gdi halftone will always performed device transform regardless the
//    setting of HT_FLAG_DO_DEVCLR_XFORM flag.
//
// HT_FLAG_8BPP_CMY332_MASK - define the bit mask for 8-bpp format halftone
// palette, this palette only used if a HT_FORMAT_8BPP is specified in
// flHTOutputFormat and HT_FLAG_USE_8BPP_BITMASK bit is set in the flHTFlags.
// if HT_FLAG_USE_8BPP_BITMAP is not set then a standard NT4.0 8-bpp format is
// assumed.  The format of 8BPP is set per PDEV, it cannot be changed after
// the pDEV is created.
//
// To set HT_FLAG_8BPP_CMY332_MASK, macro MAKE_CMY332_MASK() can be used.  When
// specified, the bit mask cover total of 8 bits area which describe the
// highest of level of CYAN, MAGENTA and YELLOW primary color, the maximum of
// Cyan is 3 bits (7 levels), Magenta is 3 bits (7 levels) and Yellow is 2 bit
// (3 levels).
//
//  0xE0000000  -- Cyan Bits (3 bits, 0 to 7 levels)
//  0x1C000000  -- Magenta Bits (3 bits, 0 to 7 levels)
//  0x03000000  -- Yellow Bits (2 bits, 0 to 3 levels)
//
//  a 0x6F000000 specified Cyan=3 levels, Magenta=3 levels, Yellow=3 levels
//  a 0xFF000000 specified Cyan=7 levels, Magenta=7 levels, Yellow=3 levels
//  a 0x25000000 specified Cyan=1 level,  Magenta=1 level,  Yellow=1 level,
//  is same as using CMY 4bpp
//
//  if any of Cyan, Magenta, Yellow level bits is 0 (zero) then it specified
//  8bpp output format is 256 level gray scale with index 0 equal to WHITE and
//  index 255 equal to BLACK,
//
//  The Palette indics are arranged as CMY entries with CYAN at highest bit
//  numbers and YELLOW at lowest bit number as shown below for palette indics
//  bit's (8 bit) definition.
//
//  Pallete Index BIT#:     7   6   5   4   3   2   1   0
//                          |       |   |       |   |   |
//                          +---C---+   +---M---+   +-Y-+
//                            0xe0         0x1c      0x03
//
//  If a primray color level in an index is greater than the prmary color
//  levels then it is eqaul to the maximum primary color level, for example
//  if C=7 (0xe0), and Cyan level only 5 then level 6 and 7 are same as 5
//
//  To retrieve the palette definition for 8bpp format, use
//
//  LONG WINAPI
//  HT_Get8BPPMaskPalette(PPALETTEENTRY pPaletteEntry,
//                        BOOL          Use8BPPMaskPal,
//                        BYTE          CMYMask,
//                        USHORT        RedGamma,
//                        USHORT        GreenGamma,
//                        USHORT        BlueGamma);
//
//  pPaletteEntry   - Pointer to the PALETTEENTRY, if NULL it return palette
//                    count needed
//
//  Use8BPPmaskPal  - FALSE if a NT4.0 standard 8bpp palette requested, FALSE
//                    if a CMYMask 8bpp mask palette is needed.
//
//  CMYMask         - CMY bit mask for CMY as defined above.  This must be the
//                    same primary level as defined in GDIInfo.flHTFlags.
//                    It should be same as ((GDIInfo.flHTFlags >> 24) & 0xFF).
//                    The CMYMask also can be specified using predefined macro
//                    MAKS_CMYMASK_BYTE(cLevel, mLevel, yLevel)
//
//  RedGamma        - Red gamma if Use8BPPMaskPal is FALSE, Cyan gamma
//                    if Use8BPPMaskPal is TRUE
//
//  GreenGamma      - Green gamma if Use8BPPMaskPal is FALSE, Magenta gamma
//                    if Use8BPPMaskPal is TRUE
//
//  BlueGamma       - Blue gamma if Use8BPPMaskPal is FALSE, Yellow gamma
//                    if Use8BPPMaskPal is TRUE
//


typedef struct _GDIINFO
{
    ULONG ulVersion;
    ULONG ulTechnology;
    ULONG ulHorzSize;
    ULONG ulVertSize;
    ULONG ulHorzRes;
    ULONG ulVertRes;
    ULONG cBitsPixel;
    ULONG cPlanes;
    ULONG ulNumColors;
    ULONG flRaster;
    ULONG ulLogPixelsX;
    ULONG ulLogPixelsY;
    ULONG flTextCaps;

    ULONG ulDACRed;
    ULONG ulDACGreen;
    ULONG ulDACBlue;

    ULONG ulAspectX;
    ULONG ulAspectY;
    ULONG ulAspectXY;

    LONG  xStyleStep;
    LONG  yStyleStep;
    LONG  denStyleStep;

    POINTL ptlPhysOffset;
    SIZEL  szlPhysSize;

    ULONG ulNumPalReg;

// These fields are for halftone initialization.

    COLORINFO ciDevice;
    ULONG     ulDevicePelsDPI;
    ULONG     ulPrimaryOrder;
    ULONG     ulHTPatternSize;
    ULONG     ulHTOutputFormat;
    ULONG     flHTFlags;

    ULONG ulVRefresh;
    ULONG ulBltAlignment;

    ULONG ulPanningHorzRes;
    ULONG ulPanningVertRes;
    ULONG xPanningAlignment;
    ULONG yPanningAlignment;

// The following fields are for user defined halftone dither patterns.  These
// fields are only checked if ulHTPatternSize is eqaul to HT_PATSIZE_USER.
//
// The user defined pHTPatA, pHTPatB, pHTPatC pointers correspond to the primary
// color order defined in ulPrimaryOrder as PRIMARY_ORDER_xxx.
//
// The size of halftone dither pattern must range from 4 to 256.  For each
// dither pattern, pHTPatA, pHTPatB, pHTPatC must point to a
// valid byte array of (cxHTPat x cyHTPat) size.  pHTPatA, pHTPatB and
// pHTPatC may point to the same dither pattern array.
//
// Each byte threshold within the dither pattern defines the additive
// intensity threshold of pixels.  A zero threshold value indicates the pixel
// location is ignored (always black), while 1 to 255 threshold values give the
// dither pattern 255 level of grays.

    ULONG   cxHTPat;    // cxHTPat must range from 4-256
    ULONG   cyHTPat;    // cyHTPat must range from 4-256
    LPBYTE  pHTPatA;    // for Primary Color Order A
    LPBYTE  pHTPatB;    // for Primary Color Order B
    LPBYTE  pHTPatC;    // for Primary Color Order C

// Shade and blend caps

    ULONG   flShadeBlend;

    ULONG   ulPhysicalPixelCharacteristics;
    ULONG   ulPhysicalPixelGamma;

} GDIINFO, *PGDIINFO;

/*
 * User objects
 */

typedef struct _BRUSHOBJ
{
    ULONG  iSolidColor;
    PVOID  pvRbrush;
    FLONG  flColorType;
} BRUSHOBJ;

//
// BRUSHOBJ::flColorType
//
#define BR_DEVICE_ICM    0x01
#define BR_HOST_ICM      0x02
#define BR_CMYKCOLOR     0x04

typedef struct _CLIPOBJ
{
    ULONG   iUniq;
    RECTL   rclBounds;
    BYTE    iDComplexity;
    BYTE    iFComplexity;
    BYTE    iMode;
    BYTE    fjOptions;
} CLIPOBJ;

typedef struct _DRIVEROBJ DRIVEROBJ;

typedef BOOL (CALLBACK * FREEOBJPROC)(DRIVEROBJ *pDriverObj);

typedef struct _DRIVEROBJ
{
    PVOID       pvObj;
    FREEOBJPROC pFreeProc;
    HDEV        hdev;
    DHPDEV      dhpdev;
} DRIVEROBJ;

typedef struct _FONTOBJ
{
    ULONG      iUniq;
    ULONG      iFace;
    ULONG      cxMax;
    FLONG      flFontType;
    ULONG_PTR   iTTUniq;
    ULONG_PTR   iFile;
    SIZE       sizLogResPpi;
    ULONG      ulStyleSize;
    PVOID      pvConsumer;
    PVOID      pvProducer;
} FONTOBJ;

typedef struct _BLENDOBJ
{
    BLENDFUNCTION BlendFunction;
}BLENDOBJ,*PBLENDOBJ;

typedef BYTE GAMMA_TABLES[2][256];

//
// FONTOBJ::flFontType
//
#define FO_TYPE_RASTER   RASTER_FONTTYPE     /* 0x1 */
#define FO_TYPE_DEVICE   DEVICE_FONTTYPE     /* 0x2 */
#define FO_TYPE_TRUETYPE TRUETYPE_FONTTYPE   /* 0x4 */
#define FO_TYPE_OPENTYPE OPENTYPE_FONTTYPE   /* 0X8 */

#define FO_SIM_BOLD      0x00002000
#define FO_SIM_ITALIC    0x00004000
#define FO_EM_HEIGHT     0x00008000
#define FO_GRAY16        0x00010000          /* [1] */
#define FO_NOGRAY16      0x00020000          /* [1] */
#define FO_NOHINTS       0x00040000          /* [3] */
#define FO_NO_CHOICE     0x00080000          /* [3] */

// new accelerators so that printer drivers  do not need to look to ifimetrics

#define FO_CFF            0x00100000
#define FO_POSTSCRIPT     0x00200000
#define FO_MULTIPLEMASTER 0x00400000
#define FO_VERT_FACE      0x00800000
#define FO_DBCS_FONT      0X01000000

/**************************************************************************\
*
*   [1]
*
*   If the FO_GRAY16 flag is set then the bitmaps of the font
*   are 4-bit per pixel blending (alpha) values. A value of zero
*   means that the the resulting pixel should be equal to the
*   background color. If the value of the alpha value is k != 0
*   then the resulting pixel must be:
*
*       c0 = background color
*       c1 = foreground color
*       b  = blending value = (k+1)/16  // {k = 1,2,..,15}
*       b  = 0 (k = 0)
*       d0 = gamma[c0], d1 = gamma[c1]  // luminance components
*       d = (1 - b)*d0 + b*d1           // blended luminance
*       c = lambda[d]                   // blended device voltage
*
*   where gamma[] takes a color component from application space
*   to CIE space and labmda[] takes a color from CIE space to
*   device color space
*
*   GDI will set this bit if it request a font be gray scaled
*   to 16 values then GDI will set FO_GRAY16 upon entry to
*   DrvQueryFontData().  If the font driver cannot (or will
*   not) grayscale a particular realization of a font then the
*   font provider will zero out FO_GRAY16  and set FO_NOGRAY16
*   to inform GDI that
*   the gray scaling request cannot (or should not) be
*   satisfied.
*
*   [2]
*
*   The FO_NOHINTS indicates that hints were not used in the formation
*   of the glyph images. GDI will set this bit to request that hinting
*   be supressed. The font provider will set this bit accroding to the
*   rendering scheme that it used in generating the glyph image.
*
*   [3]
*
*   The FO_NO_CHOICE flag indicates that the flags FO_GRAY16 and
*   FO_NOHINTS must be obeyed if at all possible.
*
\**************************************************************************/

typedef struct _PALOBJ
{
    ULONG   ulReserved;
} PALOBJ;

typedef struct _PATHOBJ
{
    FLONG   fl;
    ULONG   cCurves;
} PATHOBJ;

typedef struct _SURFOBJ
{
    DHSURF  dhsurf;
    HSURF   hsurf;
    DHPDEV  dhpdev;
    HDEV    hdev;
    SIZEL   sizlBitmap;
    ULONG   cjBits;
    PVOID   pvBits;
    PVOID   pvScan0;
    LONG    lDelta;
    ULONG   iUniq;
    ULONG   iBitmapFormat;
    USHORT  iType;
    USHORT  fjBitmap;
} SURFOBJ;

typedef struct _WNDOBJ
{
    CLIPOBJ  coClient;
    PVOID    pvConsumer;
    RECTL    rclClient;
    SURFOBJ *psoOwner;
} WNDOBJ, *PWNDOBJ;

typedef struct _XFORMOBJ
{
    ULONG ulReserved;
} XFORMOBJ;

typedef struct _XLATEOBJ
{
    ULONG   iUniq;
    FLONG   flXlate;
    USHORT  iSrcType;               // Obsolete
    USHORT  iDstType;               // Obsolete
    ULONG   cEntries;
    ULONG  *pulXlate;
} XLATEOBJ;

/* BRUSHOBJ callbacks */
PVOID WINAPI BRUSHOBJ_pvAllocRbrush( BRUSHOBJ *pbo, ULONG cj );
PVOID WINAPI BRUSHOBJ_pvGetRbrush( BRUSHOBJ *pbo );
ULONG WINAPI BRUSHOBJ_ulGetBrushColor( BRUSHOBJ *pbo );
HANDLE WINAPI BRUSHOBJ_hGetColorTransform( BRUSHOBJ *pbo );

/* CLIPOBJ callbacks */
#define DC_TRIVIAL      0
#define DC_RECT         1
#define DC_COMPLEX      3

#define FC_RECT         1
#define FC_RECT4        2
#define FC_COMPLEX      3

#define TC_RECTANGLES   0
#define TC_PATHOBJ      2

#define OC_BANK_CLIP    1       // Obsolete

#define CT_RECTANGLES   0L

#define CD_RIGHTDOWN    0L
#define CD_LEFTDOWN     1L
#define CD_RIGHTUP      2L
#define CD_LEFTUP       3L
#define CD_ANY          4L

#define CD_LEFTWARDS    1L
#define CD_UPWARDS      2L

typedef struct _ENUMRECTS
{
    ULONG       c;
    RECTL       arcl[1];
} ENUMRECTS;

ULONG WINAPI CLIPOBJ_cEnumStart( CLIPOBJ *pco, BOOL bAll, ULONG iType, ULONG iDirection, ULONG cLimit );
BOOL WINAPI CLIPOBJ_bEnum( CLIPOBJ *pco, ULONG cj, ULONG *pul );
PATHOBJ* WINAPI CLIPOBJ_ppoGetPath( CLIPOBJ* pco );

/*
 *   FONTOBJ callbacks
 */

typedef struct _GLYPHBITS
{
    POINTL      ptlOrigin;
    SIZEL       sizlBitmap;
    BYTE        aj[1];
} GLYPHBITS;

#define FO_HGLYPHS          0L
#define FO_GLYPHBITS        1L
#define FO_PATHOBJ          2L

#define FD_NEGATIVE_FONT    1L

#define FO_DEVICE_FONT      1L
#define FO_OUTLINE_CAPABLE  2L

typedef union _GLYPHDEF
{
    GLYPHBITS  *pgb;
    PATHOBJ    *ppo;
} GLYPHDEF;

typedef struct _GLYPHPOS    /* gp */
{
    HGLYPH      hg;
    GLYPHDEF   *pgdf;
    POINTL      ptl;
} GLYPHPOS,*PGLYPHPOS;


// individual glyph data

// r is a unit vector along the baseline in device coordinates.
// s is a unit vector in the ascent direction in device coordinates.
// A, B, and C, are simple transforms of the notional space versions into
// (28.4) device coordinates.  The dot products of those vectors with r
// are recorded here.  Note that the high words of ptqD are also 28.4
// device coordinates.  The low words provide extra accuracy.

// THE STRUCTURE DIFFERS IN ORDERING FROM NT 3.51 VERSION OF THE STRUCTURE.
// ptqD has been moved to the bottom.
// This requires only recompile of all the drivers.

typedef struct _GLYPHDATA {
        GLYPHDEF gdf;               // pointer to GLYPHBITS or to PATHOBJ
        HGLYPH   hg;                // glyph handle
        FIX      fxD;               // Character increment amount: D*r.
        FIX      fxA;               // Prebearing amount: A*r.
        FIX      fxAB;              // Advancing edge of character: (A+B)*r.
        FIX      fxInkTop;          // Baseline to inkbox top along s.
        FIX      fxInkBottom;       // Baseline to inkbox bottom along s.
        RECTL    rclInk;            // Ink box with sides parallel to x,y axes
        POINTQF  ptqD;              // Character increment vector: D=A+B+C.
} GLYPHDATA;


// flAccel flags for STROBJ

// SO_FLAG_DEFAULT_PLACEMENT // default inc vectors used to position chars
// SO_HORIZONTAL             // "left to right" or "right to left"
// SO_VERTICAL               // "top to bottom" or "bottom to top"
// SO_REVERSED               // set if horiz & "right to left" or if vert &  "bottom to top"
// SO_ZERO_BEARINGS          // all glyphs have zero a and c spaces
// SO_CHAR_INC_EQUAL_BM_BASE // base == cx for horiz, == cy for vert.
// SO_MAXEXT_EQUAL_BM_SIDE   // side == cy for horiz, == cx for vert.

// do not substitute device font for tt font even if device font sub table
// tells the driver this should be done

// SO_DO_NOT_SUBSTITUTE_DEVICE_FONT

#define SO_FLAG_DEFAULT_PLACEMENT        0x00000001
#define SO_HORIZONTAL                    0x00000002
#define SO_VERTICAL                      0x00000004
#define SO_REVERSED                      0x00000008
#define SO_ZERO_BEARINGS                 0x00000010
#define SO_CHAR_INC_EQUAL_BM_BASE        0x00000020
#define SO_MAXEXT_EQUAL_BM_SIDE          0x00000040
#define SO_DO_NOT_SUBSTITUTE_DEVICE_FONT 0x00000080
#define SO_GLYPHINDEX_TEXTOUT            0x00000100
#define SO_ESC_NOT_ORIENT                0x00000200
#define SO_DXDY                          0x00000400
#define SO_CHARACTER_EXTRA               0x00000800
#define SO_BREAK_EXTRA                   0x00001000

typedef struct _STROBJ
{
    ULONG     cGlyphs;     // # of glyphs to render
    FLONG     flAccel;     // accel flags
    ULONG     ulCharInc;   // non-zero only if fixed pitch font, equal to advanced width.
    RECTL     rclBkGround; // bk ground  rect of the string in device coords
    GLYPHPOS *pgp;         // If non-NULL then has all glyphs.
    LPWSTR    pwszOrg;     // pointer to original unicode string.
} STROBJ;

typedef struct _FONTINFO /* fi */
{
    ULONG   cjThis;
    FLONG   flCaps;
    ULONG   cGlyphsSupported;
    ULONG   cjMaxGlyph1;
    ULONG   cjMaxGlyph4;
    ULONG   cjMaxGlyph8;
    ULONG   cjMaxGlyph32;
} FONTINFO, *PFONTINFO;

ULONG WINAPI FONTOBJ_cGetAllGlyphHandles( FONTOBJ *pfo, HGLYPH *phg );
VOID WINAPI FONTOBJ_vGetInfo( FONTOBJ  *pfo, ULONG cjSize, FONTINFO *pfi );
ULONG WINAPI FONTOBJ_cGetGlyphs( FONTOBJ *pfo, ULONG iMode, ULONG cGlyph, HGLYPH *phg, PVOID *ppvGlyph );
GAMMA_TABLES* WINAPI FONTOBJ_pGetGammaTables( FONTOBJ *pfo );
XFORMOBJ * WINAPI FONTOBJ_pxoGetXform( FONTOBJ *pfo );
IFIMETRICS * WINAPI FONTOBJ_pifi( FONTOBJ *pfo );
FD_GLYPHSET * WINAPI FONTOBJ_pfdg( FONTOBJ *pfo );
PVOID WINAPI FONTOBJ_pvTrueTypeFontFile( FONTOBJ *pfo, ULONG *pcjFile );
PBYTE WINAPI FONTOBJ_pjOpenTypeTablePointer( FONTOBJ *pfo, ULONG ulTag, ULONG *pcjTable );
LPWSTR WINAPI FONTOBJ_pwszFontFilePaths( FONTOBJ *pfo, ULONG *pcwc );

// for now only one mode is defined for glyph attributes

#define FO_ATTR_MODE_ROTATE         1

PFD_GLYPHATTR WINAPI FONTOBJ_pQueryGlyphAttrs( FONTOBJ *pfo, ULONG iMode );

/*
 * PALOBJ callbacks
 */

#define PAL_INDEXED       0x00000001
#define PAL_BITFIELDS     0x00000002
#define PAL_RGB           0x00000004
#define PAL_BGR           0x00000008
#define PAL_CMYK          0x00000010

ULONG WINAPI PALOBJ_cGetColors(
    PALOBJ *ppalo,
    ULONG   iStart,
    ULONG   cColors,
    ULONG  *pulColors
    );

/*
 * PATHOBJ callbacks
 */

#define PO_BEZIERS          0x00000001
#define PO_ELLIPSE          0x00000002
#define PO_ALL_INTEGERS     0x00000004
#define PO_ENUM_AS_INTEGERS 0x00000008

#define PD_BEGINSUBPATH   0x00000001
#define PD_ENDSUBPATH     0x00000002
#define PD_RESETSTYLE     0x00000004
#define PD_CLOSEFIGURE    0x00000008
#define PD_BEZIERS        0x00000010
#define PD_ALL           (PD_BEGINSUBPATH | \
                          PD_ENDSUBPATH   | \
                          PD_RESETSTYLE   | \
                          PD_CLOSEFIGURE  | \
                          PD_BEZIERS)

typedef struct  _PATHDATA
{
    FLONG    flags;
    ULONG    count;
    POINTFIX *pptfx;
} PATHDATA, *PPATHDATA;

typedef struct  _RUN
{
    LONG    iStart;
    LONG    iStop;
} RUN, *PRUN;

typedef struct  _CLIPLINE
{
    POINTFIX ptfxA;
    POINTFIX ptfxB;
    LONG    lStyleState;
    ULONG   c;
    RUN     arun[1];
} CLIPLINE, *PCLIPLINE;

VOID WINAPI PATHOBJ_vEnumStart( PATHOBJ *ppo );
BOOL WINAPI PATHOBJ_bEnum( PATHOBJ *ppo, PATHDATA *ppd );
VOID WINAPI PATHOBJ_vEnumStartClipLines( PATHOBJ *ppo, CLIPOBJ   *pco, SURFOBJ   *pso, LINEATTRS *pla );
BOOL WINAPI PATHOBJ_bEnumClipLines( PATHOBJ *ppo, ULONG cb, CLIPLINE *pcl );
BOOL WINAPI PATHOBJ_bMoveTo( PATHOBJ *ppo, POINTFIX ptfx );
BOOL WINAPI PATHOBJ_bPolyLineTo( PATHOBJ *ppo, POINTFIX  *pptfx, ULONG cptfx );
BOOL WINAPI PATHOBJ_bPolyBezierTo( PATHOBJ *ppo, POINTFIX *pptfx, ULONG cptfx );

BOOL WINAPI PATHOBJ_bCloseFigure( PATHOBJ *ppo );

VOID WINAPI PATHOBJ_vGetBounds( PATHOBJ *ppo, PRECTFX prectfx );

/*
 * STROBJ callbacks
 */

VOID WINAPI STROBJ_vEnumStart( STROBJ *pstro );
BOOL WINAPI STROBJ_bEnum( STROBJ *pstro, ULONG *pc, PGLYPHPOS *ppgpos );
BOOL WINAPI STROBJ_bEnumPositionsOnly( STROBJ *pstro, ULONG *pc, PGLYPHPOS *ppgpos );

DWORD WINAPI STROBJ_dwGetCodePage(
    STROBJ  *pstro
    );

FIX WINAPI STROBJ_fxCharacterExtra(
    STROBJ  *pstro
    );

FIX WINAPI STROBJ_fxBreakExtra(
    STROBJ  *pstro
    );

BOOL WINAPI STROBJ_bGetAdvanceWidths(
    STROBJ   *pso,
    ULONG     iFirst,
    ULONG     c,
    POINTQF  *pptqD
    );


#define SGI_EXTRASPACE 0

/*
 * SURFOBJ callbacks
 */

#define STYPE_BITMAP    0L
#define STYPE_DEVICE    1L
#define STYPE_DEVBITMAP 3L

#define BMF_1BPP       1L
#define BMF_4BPP       2L
#define BMF_8BPP       3L
#define BMF_16BPP      4L
#define BMF_24BPP      5L
#define BMF_32BPP      6L
#define BMF_4RLE       7L
#define BMF_8RLE       8L
#define BMF_JPEG       9L
#define BMF_PNG       10L

#define BMF_TOPDOWN    0x0001
#define BMF_NOZEROINIT 0x0002
#define BMF_DONTCACHE  0x0004
#define BMF_USERMEM    0x0008
#define BMF_KMSECTION  0x0010
#define BMF_NOTSYSMEM  0x0020
#define BMF_WINDOW_BLT 0x0040

/*
 * XFORMOBJ callbacks
 */

#define GX_IDENTITY     0L
#define GX_OFFSET       1L
#define GX_SCALE        2L
#define GX_GENERAL      3L

#define XF_LTOL         0L
#define XF_INV_LTOL     1L
#define XF_LTOFX        2L
#define XF_INV_FXTOL    3L

ULONG WINAPI XFORMOBJ_iGetXform(
    XFORMOBJ *pxo,
    XFORML   *pxform
    );

BOOL WINAPI XFORMOBJ_bApplyXform(
    XFORMOBJ *pxo,
    ULONG     iMode,
    ULONG     cPoints,
    PVOID     pvIn,
    PVOID     pvOut
    );

HANDLE WINAPI XFORMOBJ_cmGetTransform(
    XFORMOBJ *pxo
    );

/*
 * XLATEOBJ callbacks
 */

#define XO_TRIVIAL      0x00000001
#define XO_TABLE        0x00000002
#define XO_TO_MONO      0x00000004
#define XO_FROM_CMYK    0x00000008
#define XO_DEVICE_ICM   0x00000010 // ICM on Device
#define XO_HOST_ICM     0x00000020 // ICM on Engine/Apps

#define XO_SRCPALETTE    1
#define XO_DESTPALETTE   2
#define XO_DESTDCPALETTE 3
#define XO_SRCBITFIELDS  4
#define XO_DESTBITFIELDS 5

ULONG WINAPI XLATEOBJ_iXlate(
    XLATEOBJ *pxlo,
    ULONG iColor
    );

ULONG * WINAPI XLATEOBJ_piVector(
    XLATEOBJ *pxlo
    );

ULONG WINAPI XLATEOBJ_cGetPalette(
    XLATEOBJ *pxlo,
    ULONG     iPal,
    ULONG     cPal,
    ULONG    *pPal
    );

HANDLE WINAPI XLATEOBJ_hGetColorTransform(
    XLATEOBJ *pxlo
    );

/*
 * Engine callbacks - error logging
 */
#define EngGetLastError     GetLastError
#define EngSetLastError     SetLastError
/*
 * Engine callbacks - Surfaces
 */
#define HOOK_BITBLT                     0x00000001
#define HOOK_STRETCHBLT                 0x00000002
#define HOOK_PLGBLT                     0x00000004
#define HOOK_TEXTOUT                    0x00000008
#define HOOK_PAINT                      0x00000010      // Obsolete
#define HOOK_STROKEPATH                 0x00000020
#define HOOK_FILLPATH                   0x00000040
#define HOOK_STROKEANDFILLPATH          0x00000080
#define HOOK_LINETO                     0x00000100
#define HOOK_COPYBITS                   0x00000400
#define HOOK_MOVEPANNING                0x00000800      // Obsolete
#define HOOK_SYNCHRONIZE                0x00001000
#define HOOK_STRETCHBLTROP              0x00002000
#define HOOK_SYNCHRONIZEACCESS          0x00004000      // Obsolete
#define HOOK_TRANSPARENTBLT             0x00008000
#define HOOK_ALPHABLEND                 0x00010000
#define HOOK_GRADIENTFILL               0x00020000
#define HOOK_FLAGS                      0x0003b5ff

HBITMAP WINAPI EngCreateBitmap(
    SIZEL sizl,
    LONG  lWidth,
    ULONG iFormat,
    FLONG fl,
    PVOID pvBits
    );

HSURF WINAPI EngCreateDeviceSurface(
    DHSURF dhsurf,
    SIZEL sizl,
    ULONG iFormatCompat
    );

HBITMAP WINAPI EngCreateDeviceBitmap(
    DHSURF dhsurf,
    SIZEL sizl,
    ULONG iFormatCompat
    );

BOOL WINAPI EngDeleteSurface(
    HSURF hsurf
    );

SURFOBJ * WINAPI EngLockSurface(
    HSURF hsurf
    );

VOID WINAPI EngUnlockSurface(
    SURFOBJ *pso
    );

BOOL WINAPI EngEraseSurface(
    SURFOBJ *pso,
    RECTL   *prcl,
    ULONG    iColor
    );

BOOL WINAPI EngAssociateSurface(
    HSURF hsurf,
    HDEV  hdev,
    FLONG flHooks
    );

#define MS_NOTSYSTEMMEMORY  0x0001
#define MS_SHAREDACCESS     0x0002


BOOL WINAPI EngModifySurface(
    HSURF   hsurf,
    HDEV    hdev,
    FLONG   flHooks,
    FLONG   flSurface,
    DHSURF  dhsurf,
    VOID*   pvScan0,
    LONG    lDelta,
    VOID*   pvReserved
    );

BOOL WINAPI EngMarkBandingSurface(
    HSURF hsurf
    );

BOOL WINAPI EngCheckAbort(
    SURFOBJ *pso
    );

/*
 * Engine callbacks - Paths
 */

PATHOBJ * WINAPI EngCreatePath();

VOID WINAPI EngDeletePath(
    PATHOBJ *ppo
    );

/*
 * Engine callbacks - Palettes
 */

HPALETTE WINAPI EngCreatePalette(
    ULONG  iMode,
    ULONG  cColors,
    ULONG *pulColors,
    FLONG  flRed,
    FLONG  flGreen,
    FLONG  flBlue
    );

ULONG WINAPI EngQueryPalette(
    HPALETTE    hpal,
    ULONG      *piMode,
    ULONG       cColors,
    ULONG      *pulColors);

BOOL WINAPI EngDeletePalette(
    HPALETTE hpal
    );

/*
 * Engine callbacks - Clipping
 */

CLIPOBJ * WINAPI EngCreateClip();

VOID WINAPI EngDeleteClip( CLIPOBJ *pco );

/*
 * Function prototypes
 */

//
// User-mode printer driver information-query entrypoint
//

BOOL WINAPI
WINAPI
DrvQueryDriverInfo(
    DWORD   dwMode,
    PVOID   pBuffer,
    DWORD   cbBuf,
    PDWORD  pcbNeeded
    );

#define DRVQUERY_USERMODE   1


// These are the only EXPORTED functions for ANY driver

BOOL WINAPI DrvEnableDriver(
    ULONG          iEngineVersion,
    ULONG          cj,
    DRVENABLEDATA *pded
    );

/*
 * Driver functions
 */

VOID WINAPI  DrvDisableDriver();

DHPDEV WINAPI DrvEnablePDEV(
    DEVMODEW *pdm,
    LPWSTR    pwszLogAddress,
    ULONG     cPat,
    HSURF    *phsurfPatterns,
    ULONG     cjCaps,
    ULONG    *pdevcaps,
    ULONG     cjDevInfo,
    DEVINFO  *pdi,
    HDEV      hdev,
    LPWSTR    pwszDeviceName,
    HANDLE    hDriver
    );

#define HS_DDI_MAX 6

BOOL WINAPI DrvResetPDEV(
    DHPDEV dhpdevOld,
    DHPDEV dhpdevNew
    );

VOID WINAPI DrvCompletePDEV(
    DHPDEV dhpdev,
    HDEV hdev
    );

BOOL WINAPI DrvOffset(        // Obsolete
    SURFOBJ* pso,
    LONG x,
    LONG y,
    FLONG flReserved
    );

HSURF WINAPI DrvEnableSurface(
    DHPDEV dhpdev
    );

VOID WINAPI DrvSynchronize(
    DHPDEV dhpdev,
    RECTL *prcl
    );

VOID WINAPI DrvDisableSurface(
    DHPDEV dhpdev
    );

VOID WINAPI DrvDisablePDEV(
    DHPDEV dhpdev
    );

/* DrvSaveScreenBits - iMode definitions */

#define SS_SAVE    0
#define SS_RESTORE 1
#define SS_FREE    2

ULONG_PTR WINAPI DrvSaveScreenBits(
    SURFOBJ  *pso,
    ULONG    iMode,
    ULONG_PTR ident,
    RECTL    *prcl
    );

/*
 * Desktops
 */

BOOL WINAPI DrvAssertMode(
    DHPDEV dhpdev,
    BOOL   bEnable
    );

ULONG WINAPI DrvGetModes(
    HANDLE    hDriver,
    ULONG     cjSize,
    DEVMODEW *pdm
    );

VOID WINAPI DrvMovePanning(
    LONG    x,
    LONG    y,
    FLONG   fl
    );

BOOL WINAPI DrvPlgBlt(
    SURFOBJ         *psoTrg,
    SURFOBJ         *psoSrc,
    SURFOBJ         *psoMsk,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    COLORADJUSTMENT *pca,
    POINTL          *pptlBrushOrg,
    POINTFIX        *pptfx,
    RECTL           *prcl,
    POINTL          *pptl,
    ULONG            iMode
    );


/*
 * Bitmaps
 */

HBITMAP WINAPI DrvCreateDeviceBitmap(
    DHPDEV dhpdev,
    SIZEL  sizl,
    ULONG  iFormat
    );

VOID WINAPI DrvDeleteDeviceBitmap(
    DHSURF dhsurf
    );

/*
 * Palettes
 */

BOOL WINAPI DrvSetPalette(
    DHPDEV  dhpdev,
    PALOBJ *ppalo,
    FLONG   fl,
    ULONG   iStart,
    ULONG   cColors
    );

/*
 * Brushes
 */

#define DM_DEFAULT    0x00000001
#define DM_MONOCHROME 0x00000002

#define DCR_SOLID       0
#define DCR_DRIVER      1
#define DCR_HALFTONE    2

ULONG WINAPI DrvDitherColor(
    DHPDEV dhpdev,
    ULONG  iMode,
    ULONG  rgb,
    ULONG *pul
    );

BOOL WINAPI DrvRealizeBrush(
    BRUSHOBJ *pbo,
    SURFOBJ  *psoTarget,
    SURFOBJ  *psoPattern,
    SURFOBJ  *psoMask,
    XLATEOBJ *pxlo,
    ULONG    iHatch
    );

#define RB_DITHERCOLOR 0x80000000L


/*
 * Fonts
 */

PIFIMETRICS WINAPI DrvQueryFont(
    DHPDEV    dhpdev,
    ULONG_PTR  iFile,
    ULONG     iFace,
    ULONG     *pid
    );

// #define QFT_UNICODE     0L
#define QFT_LIGATURES       1L
#define QFT_KERNPAIRS       2L
#define QFT_GLYPHSET        3L

PVOID WINAPI DrvQueryFontTree(
    DHPDEV    dhpdev,
    ULONG_PTR  iFile,
    ULONG     iFace,
    ULONG     iMode,
    ULONG     *pid
    );

#define QFD_GLYPHANDBITMAP    1L
#define QFD_GLYPHANDOUTLINE   2L
#define QFD_MAXEXTENTS        3L
#define QFD_TT_GLYPHANDBITMAP 4L
#define QFD_TT_GRAY1_BITMAP   5L
#define QFD_TT_GRAY2_BITMAP   6L
#define QFD_TT_GRAY4_BITMAP   8L
#define QFD_TT_GRAY8_BITMAP   9L

#define QFD_TT_MONO_BITMAP QFD_TT_GRAY1_BITMAP

LONG WINAPI DrvQueryFontData(
    DHPDEV      dhpdev,
    FONTOBJ    *pfo,
    ULONG       iMode,
    HGLYPH      hg,
    GLYPHDATA  *pgd,
    PVOID       pv,
    ULONG       cjSize
    );

VOID WINAPI DrvFree(
PVOID   pv,
ULONG   id);

VOID WINAPI DrvDestroyFont(
FONTOBJ *pfo);

// Capability flags for DrvQueryCaps.

#define QC_OUTLINES             0x00000001
#define QC_1BIT                 0x00000002
#define QC_4BIT                 0x00000004

//
// This is a mask of the capabilites of a font provider that can return more
// than just glyph metrics (i.e., bitmaps and/or outlines).  If a driver has
// one or more of these capabilities, then it is FONT DRIVER.
//
// Drivers should only set individual bits. GDI will check if any are turned on
// using this define.
//

#define QC_FONTDRIVERCAPS   ( QC_OUTLINES | QC_1BIT | QC_4BIT )


LONG WINAPI DrvQueryFontCaps( ULONG culCaps, ULONG  *pulCaps );

// fStatus is a new flag NT 5.0

#define FF_SIGNATURE_VERIFIED 0x1
#define FF_IGNORED_SIGNATURE  0x2

ULONG_PTR WINAPI DrvLoadFontFile(
    ULONG     cFiles,  // number of font files associated with this font
    ULONG_PTR  *piFile,  // handles for individual files, cFiles of them
    PVOID     *ppvView, // array of cFiles views
    ULONG     *pcjView, // array of their sizes
    DESIGNVECTOR *pdv, // only non null for mm instances
    ULONG     ulLangID,
    ULONG     ulFastCheckSum
    );

BOOL WINAPI DrvUnloadFontFile(
    ULONG_PTR   iFile
    );

LONG WINAPI DrvQueryTrueTypeTable(
    ULONG_PTR   iFile,
    ULONG      ulFont,
    ULONG      ulTag,
    PTRDIFF    dpStart,
    ULONG      cjBuf,
    BYTE       *pjBuf,
    PBYTE      *ppjTable,
    ULONG      *pcjTable
    );

BOOL WINAPI DrvQueryAdvanceWidths( DHPDEV   dhpdev, FONTOBJ *pfo, ULONG    iMode, HGLYPH  *phg, PVOID    pvWidths, ULONG    cGlyphs );

// Values for iMode

#define QAW_GETWIDTHS       0
#define QAW_GETEASYWIDTHS   1

// values for bMetricsOnly. even though declared as BOOL
// by adding TTO_QUBICS, this is becoming a flag field.
// For versions of NT 4.0 and earlier, this value is always
// set to zero by GDI.

#define TTO_METRICS_ONLY 1
#define TTO_QUBICS       2
#define TTO_UNHINTED     4

LONG WINAPI DrvQueryTrueTypeOutline(
    DHPDEV      dhpdev,
    FONTOBJ    *pfo,
    HGLYPH      hglyph,
    BOOL        bMetricsOnly,
    GLYPHDATA  *pgldt,
    ULONG       cjBuf,
    TTPOLYGONHEADER *ppoly
    );

PVOID WINAPI DrvGetTrueTypeFile (
    ULONG_PTR   iFile,
    ULONG      *pcj
    );

// values for ulMode:

#define QFF_DESCRIPTION     1L
#define QFF_NUMFACES        2L

LONG WINAPI DrvQueryFontFile(
    ULONG_PTR   iFile,
    ULONG      ulMode,
    ULONG      cjBuf,
    ULONG      *pulBuf
    );

/*
 * BitBlt
 */
BOOL WINAPI DrvBitBlt( SURFOBJ *psoTrg, SURFOBJ *psoSrc, SURFOBJ *psoMask, CLIPOBJ *pco, XLATEOBJ *pxlo, RECTL *prclTrg, POINTL *pptlSrc, POINTL *pptlMask, BRUSHOBJ *pbo, POINTL *pptlBrush, ROP4 rop4 );
BOOL WINAPI DrvStretchBlt(
    SURFOBJ         *psoDest,
    SURFOBJ         *psoSrc,
    SURFOBJ         *psoMask,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    COLORADJUSTMENT *pca,
    POINTL          *pptlHTOrg,
    RECTL           *prclDest,
    RECTL           *prclSrc,
    POINTL          *pptlMask,
    ULONG            iMode
    );

BOOL WINAPI DrvStretchBltROP(
    SURFOBJ         *psoDest,
    SURFOBJ         *psoSrc,
    SURFOBJ         *psoMask,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    COLORADJUSTMENT *pca,
    POINTL          *pptlHTOrg,
    RECTL           *prclDest,
    RECTL           *prclSrc,
    POINTL          *pptlMask,
    ULONG            iMode,
    BRUSHOBJ        *pbo,
    DWORD            rop4
    );

BOOL WINAPI DrvAlphaBlend(
    SURFOBJ       *psoDest,
    SURFOBJ       *psoSrc,
    CLIPOBJ       *pco,
    XLATEOBJ      *pxlo,
    RECTL         *prclDest,
    RECTL         *prclSrc,
    BLENDOBJ      *pBlendObj
    );

BOOL WINAPI DrvGradientFill(
    SURFOBJ         *psoDest,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    TRIVERTEX       *pVertex,
    ULONG            nVertex,
    PVOID            pMesh,
    ULONG            nMesh,
    RECTL           *prclExtents,
    POINTL          *pptlDitherOrg,
    ULONG            ulMode
    );

BOOL WINAPI DrvTransparentBlt(
    SURFOBJ    *psoDst,
    SURFOBJ    *psoSrc,
    CLIPOBJ    *pco,
    XLATEOBJ   *pxlo,
    RECTL      *prclDst,
    RECTL      *prclSrc,
    ULONG      iTransColor,
    ULONG      ulReserved
);

BOOL WINAPI DrvCopyBits(
    SURFOBJ  *psoDest,
    SURFOBJ  *psoSrc,
    CLIPOBJ  *pco,
    XLATEOBJ *pxlo,
    RECTL    *prclDest,
    POINTL   *pptlSrc
    );

/*
 * Text Output
 */

BOOL WINAPI DrvTextOut(
    SURFOBJ  *pso,
    STROBJ   *pstro,
    FONTOBJ  *pfo,
    CLIPOBJ  *pco,
    RECTL    *prclExtra,        // Obsolete, always NULL
    RECTL    *prclOpaque,
    BRUSHOBJ *pboFore,
    BRUSHOBJ *pboOpaque,
    POINTL   *pptlOrg,
    MIX       mix
    );

/*
 * Graphics Output
 */

BOOL WINAPI DrvLineTo(
    SURFOBJ   *pso,
    CLIPOBJ   *pco,
    BRUSHOBJ  *pbo,
    LONG       x1,
    LONG       y1,
    LONG       x2,
    LONG       y2,
    RECTL     *prclBounds,
    MIX        mix
    );

BOOL WINAPI DrvStrokePath(
    SURFOBJ   *pso,
    PATHOBJ   *ppo,
    CLIPOBJ   *pco,
    XFORMOBJ  *pxo,
    BRUSHOBJ  *pbo,
    POINTL    *pptlBrushOrg,
    LINEATTRS *plineattrs,
    MIX        mix
    );

#define FP_ALTERNATEMODE    1L
#define FP_WINDINGMODE      2L

BOOL WINAPI DrvFillPath(
    SURFOBJ  *pso,
    PATHOBJ  *ppo,
    CLIPOBJ  *pco,
    BRUSHOBJ *pbo,
    POINTL   *pptlBrushOrg,
    MIX       mix,
    FLONG     flOptions
    );

BOOL WINAPI DrvStrokeAndFillPath(
    SURFOBJ   *pso,
    PATHOBJ   *ppo,
    CLIPOBJ   *pco,
    XFORMOBJ  *pxo,
    BRUSHOBJ  *pboStroke,
    LINEATTRS *plineattrs,
    BRUSHOBJ  *pboFill,
    POINTL    *pptlBrushOrg,
    MIX        mixFill,
    FLONG      flOptions
    );

BOOL WINAPI DrvPaint( SURFOBJ  *pso, CLIPOBJ  *pco, BRUSHOBJ *pbo, POINTL   *pptlBrushOrg, MIX       mix );

/*
 * Printing
 */

BOOL WINAPI DrvSendPage( SURFOBJ *pso );
BOOL WINAPI DrvStartPage( SURFOBJ *pso );
ULONG WINAPI DrvEscape( SURFOBJ *pso, ULONG iEsc, ULONG cjIn, PVOID pvIn, ULONG cjOut, PVOID pvOut );
BOOL  WINAPI DrvStartDoc( SURFOBJ *pso, LPWSTR   pwszDocName, DWORD    dwJobId );

#define ED_ABORTDOC    1

BOOL WINAPI DrvEndDoc( SURFOBJ *pso, FLONG fl );
BOOL WINAPI DrvQuerySpoolType( DHPDEV, LPWSTR );
ULONG WINAPI DrvDrawEscape( SURFOBJ *pso, ULONG iEsc, CLIPOBJ *pco, RECTL *prcl, ULONG cjIn, PVOID pvIn );
ULONG WINAPI DrvGetGlyphMode( DHPDEV, FONTOBJ *);
ULONG WINAPI DrvFontManagement( SURFOBJ *pso, FONTOBJ *pfo, ULONG iMode, ULONG cjIn, PVOID pvIn, ULONG cjOut, PVOID pvOut );
BOOL WINAPI DrvStartBanding( SURFOBJ *pso, POINTL *pptl );
BOOL WINAPI DrvNextBand( SURFOBJ *pso, POINTL *pptl );

typedef struct _PERBANDINFO
{
    BOOL  bRepeatThisBand;
    SIZEL szlBand;
    ULONG ulHorzRes;
    ULONG ulVertRes;
} PERBANDINFO, *PPERBANDINFO;

ULONG WINAPI DrvQueryPerBandInfo(SURFOBJ *pso, PERBANDINFO *pbi );

/*
 * ICM (Image Color Matching)
 */

HANDLE WINAPI DrvIcmCreateColorTransform(
    DHPDEV           dhpdev,
    LPLOGCOLORSPACEW pLogColorSpace,
    PVOID            pvSourceProfile,
    ULONG            cjSourceProfile,
    PVOID            pvDestProfile,
    ULONG            cjDestProfile,
    PVOID            pvTargetProfile,
    ULONG            cjTargetProfile,
    DWORD            dwReserved
    );

BOOL WINAPI DrvIcmDeleteColorTransform(
    DHPDEV dhpdev,
    HANDLE hcmXform
    );

BOOL WINAPI DrvIcmCheckBitmapBits(
    DHPDEV   dhpdev,
    HANDLE   hColorTransform,
    SURFOBJ *pso,
    PBYTE    paResults
    );

typedef struct _GAMMARAMP {
    WORD Red[256];
    WORD Green[256];
    WORD Blue[256];
} GAMMARAMP, *PGAMMARAMP;

BOOL WINAPI DrvIcmSetDeviceGammaRamp(
    DHPDEV  dhpdev,
    ULONG   iFormat,
    LPVOID  lpRamp
    );

#define IGRF_RGB_256BYTES  0 /* Obsolate */
#define IGRF_RGB_256WORDS  1 /* Same GammaRampArray format as Win95/98 DDI */

/*
 * Query miscellaneous driver support
 */

BOOL WINAPI DrvQueryDeviceSupport(
    SURFOBJ *pso,
    XLATEOBJ *pxlo,
    XFORMOBJ *pxo,
    ULONG iType,
    ULONG cjIn,
    PVOID pvIn,
    ULONG cjOut,
    PVOID pvOut);

#define QDS_CHECKJPEGFORMAT     0
#define QDS_CHECKPNGFORMAT      1

VOID WINAPI DrvSynchronizeSurface(
    SURFOBJ *pso,
    RECTL   *prcl,
    FLONG    fl
);

#define DSS_TIMER_EVENT        0x0001
#define DSS_FLUSH_EVENT        0x0002

VOID WINAPI DrvNotify(
    SURFOBJ *pso,
    ULONG    iType,
    PVOID    pvData);

#define DN_ACCELERATION_LEVEL     1
#define DN_DEVICE_ORIGIN          2
#define DN_SLEEP_MODE             3
#define DN_DRAWING_BEGIN          4

/*
 * Engine callbacks - tracking clip region changes
 */

#define WOC_RGN_CLIENT_DELTA    0x0001
#define WOC_RGN_CLIENT          0x0002
#define WOC_RGN_SURFACE_DELTA   0x0004
#define WOC_RGN_SURFACE         0x0008
#define WOC_CHANGED             0x0010
#define WOC_DELETE              0x0020
#define WOC_DRAWN               0x0040
#define WOC_SPRITE_OVERLAP      0x0080
#define WOC_SPRITE_NO_OVERLAP   0x0100

typedef VOID (CALLBACK * WNDOBJCHANGEPROC)(WNDOBJ *pwo, FLONG fl);

#define WO_RGN_CLIENT_DELTA     0x0001
#define WO_RGN_CLIENT           0x0002
#define WO_RGN_SURFACE_DELTA    0x0004
#define WO_RGN_SURFACE          0x0008
#define WO_RGN_UPDATE_ALL       0x0010
#define WO_RGN_WINDOW           0x0020
#define WO_DRAW_NOTIFY          0x0040
#define WO_SPRITE_NOTIFY        0x0080
#define WO_RGN_DESKTOP_COORD    0x0100

WNDOBJ * WINAPI EngCreateWnd(
    SURFOBJ         *pso,
    HWND             hwnd,
    WNDOBJCHANGEPROC pfn,
    FLONG            fl,
    int              iPixelFormat
    );

VOID WINAPI EngDeleteWnd(
    WNDOBJ  *pwo
    );

ULONG WINAPI WNDOBJ_cEnumStart(
    WNDOBJ  *pwo,
    ULONG    iType,
    ULONG    iDirection,
    ULONG    cLimit
    );

BOOL WINAPI WNDOBJ_bEnum(
    WNDOBJ  *pwo,
    ULONG    cj,
    ULONG   *pul
    );

VOID WINAPI WNDOBJ_vSetConsumer(
    WNDOBJ  *pwo,
    PVOID    pvConsumer
    );

/*
 * Engine callbacks - tracking driver managed resources
 */

HDRVOBJ WINAPI EngCreateDriverObj(
    PVOID pvObj,
    FREEOBJPROC pFreeObjProc,
    HDEV hdev
    );

BOOL WINAPI EngDeleteDriverObj(
    HDRVOBJ hdo,
    BOOL bCallBack,
    BOOL bLocked
    );

DRIVEROBJ* WINAPI EngLockDriverObj(
    HDRVOBJ hdo
    );

BOOL WINAPI EngUnlockDriverObj(
    HDRVOBJ hdo
    );

/*
 * Engine callback - return current process handle.
 */

HANDLE WINAPI EngGetProcessHandle();

/*
 * Engine callback - return current thread id
 */

HANDLE WINAPI EngGetCurrentThreadId();

/*
 * Engine callback - return current process id
 */

HANDLE WINAPI EngGetCurrentProcessId();

/*
 * Pixel formats
 */

BOOL WINAPI DrvSetPixelFormat(
    SURFOBJ *pso,
    LONG     iPixelFormat,
    HWND     hwnd
    );

LONG WINAPI DrvDescribePixelFormat(
    DHPDEV   dhpdev,
    LONG     iPixelFormat,
    ULONG    cjpfd,
    PIXELFORMATDESCRIPTOR *ppfd
    );

BOOL WINAPI DrvSwapBuffers( SURFOBJ *pso, WNDOBJ  *pwo );

/*
 * Function prototypes - Engine Simulations
 */

BOOL WINAPI EngBitBlt( SURFOBJ *psoTrg, SURFOBJ *psoSrc, SURFOBJ *psoMask, CLIPOBJ *pco, XLATEOBJ *pxlo, RECTL *prclTrg, POINTL *pptlSrc, POINTL *pptlMask, BRUSHOBJ *pbo, POINTL *pptlBrush, ROP4 rop4 );
BOOL WINAPI EngLineTo(
    SURFOBJ   *pso,
    CLIPOBJ   *pco,
    BRUSHOBJ  *pbo,
    LONG       x1,
    LONG       y1,
    LONG       x2,
    LONG       y2,
    RECTL     *prclBounds,
    MIX        mix
    );

BOOL WINAPI EngStretchBlt(
    SURFOBJ         *psoDest,
    SURFOBJ         *psoSrc,
    SURFOBJ         *psoMask,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    COLORADJUSTMENT *pca,
    POINTL          *pptlHTOrg,
    RECTL           *prclDest,
    RECTL           *prclSrc,
    POINTL          *pptlMask,
    ULONG            iMode
    );

BOOL WINAPI EngStretchBltROP(
    SURFOBJ         *psoDest,
    SURFOBJ         *psoSrc,
    SURFOBJ         *psoMask,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    COLORADJUSTMENT *pca,
    POINTL          *pptlHTOrg,
    RECTL           *prclDest,
    RECTL           *prclSrc,
    POINTL          *pptlMask,
    ULONG            iMode,
    BRUSHOBJ        *pbo,
    DWORD            rop4
    );

BOOL WINAPI EngAlphaBlend(
    SURFOBJ       *psoDest,
    SURFOBJ       *psoSrc,
    CLIPOBJ       *pco,
    XLATEOBJ      *pxlo,
    RECTL         *prclDest,
    RECTL         *prclSrc,
    BLENDOBJ      *pBlendObj
    );

BOOL WINAPI EngGradientFill(
    SURFOBJ         *psoDest,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    TRIVERTEX       *pVertex,
    ULONG            nVertex,
    PVOID            pMesh,
    ULONG            nMesh,
    RECTL           *prclExtents,
    POINTL          *pptlDitherOrg,
    ULONG            ulMode
    );

BOOL WINAPI EngTransparentBlt(
    SURFOBJ    *psoDst,
    SURFOBJ    *psoSrc,
    CLIPOBJ    *pco,
    XLATEOBJ   *pxlo,
    RECTL      *prclDst,
    RECTL      *prclSrc,
    ULONG      iTransColor,
    ULONG      ulReserved
    );

BOOL WINAPI EngTextOut(
    SURFOBJ  *pso,
    STROBJ   *pstro,
    FONTOBJ  *pfo,
    CLIPOBJ  *pco,
    RECTL    *prclExtra,
    RECTL    *prclOpaque,
    BRUSHOBJ *pboFore,
    BRUSHOBJ *pboOpaque,
    POINTL   *pptlOrg,
    MIX       mix
    );

BOOL WINAPI EngStrokePath( SURFOBJ   *pso, PATHOBJ   *ppo, CLIPOBJ   *pco, XFORMOBJ  *pxo, BRUSHOBJ  *pbo, POINTL    *pptlBrushOrg, LINEATTRS *plineattrs, MIX        mix );
BOOL WINAPI EngFillPath( SURFOBJ  *pso, PATHOBJ  *ppo, CLIPOBJ  *pco, BRUSHOBJ *pbo, POINTL   *pptlBrushOrg, MIX       mix, FLONG     flOptions );
BOOL WINAPI EngStrokeAndFillPath(SURFOBJ   *pso, PATHOBJ   *ppo, CLIPOBJ   *pco, XFORMOBJ  *pxo, BRUSHOBJ  *pboStroke, LINEATTRS *plineattrs, BRUSHOBJ  *pboFill,
    POINTL    *pptlBrushOrg, MIX        mixFill, FLONG      flOptions );
BOOL WINAPI EngPaint( SURFOBJ  *pso, CLIPOBJ  *pco, BRUSHOBJ *pbo, POINTL   *pptlBrushOrg, MIX       mix );

BOOL WINAPI EngCopyBits(
    SURFOBJ  *psoDest,
    SURFOBJ  *psoSrc,
    CLIPOBJ  *pco,
    XLATEOBJ *pxlo,
    RECTL    *prclDest,
    POINTL   *pptlSrc
    );

ULONG WINAPI EngSetPointerShape(
    SURFOBJ  *pso,
    SURFOBJ  *psoMask,
    SURFOBJ  *psoColor,
    XLATEOBJ *pxlo,
    LONG      xHot,
    LONG      yHot,
    LONG      x,
    LONG      y,
    RECTL    *prcl,
    FLONG     fl
    );

VOID WINAPI EngMovePointer(
    SURFOBJ  *pso,
    LONG      x,
    LONG      y,
    RECTL    *prcl
    );

BOOL WINAPI EngPlgBlt(
    SURFOBJ         *psoTrg,
    SURFOBJ         *psoSrc,
    SURFOBJ         *psoMsk,
    CLIPOBJ         *pco,
    XLATEOBJ        *pxlo,
    COLORADJUSTMENT *pca,
    POINTL          *pptlBrushOrg,
    POINTFIX        *pptfx,
    RECTL           *prcl,
    POINTL          *pptl,
    ULONG            iMode
    );

ULONG WINAPI EngDitherColor( HDEV hdev, ULONG iMode, ULONG  rgb, ULONG *pul );

//
// Sprite control
//

#define ECS_TEARDOWN    0x0001
#define ECS_REDRAW      0x0002

BOOL WINAPI EngControlSprites( WNDOBJ *pwo, FLONG fl );


//
// Halftone releated APIs
//

LONG WINAPI HT_ComputeRGBGammaTable(
    USHORT  GammaTableEntries,
    USHORT  GammaTableType,
    USHORT  RedGamma,
    USHORT  GreenGamma,
    USHORT  BlueGamma,
    LPBYTE  pGammaTable
    );

LONG WINAPI HT_Get8BPPFormatPalette(
    LPPALETTEENTRY  pPaletteEntry,
    USHORT          RedGamma,
    USHORT          GreenGamma,
    USHORT          BlueGamma
    );

LONG WINAPI HT_Get8BPPMaskPalette(
    LPPALETTEENTRY  pPaletteEntry,
    BOOL            Use8BPPMaskPal,
    BYTE            CMYMask,
    USHORT          RedGamma,
    USHORT          GreenGamma,
    USHORT          BlueGamma
    );

typedef struct _DEVHTINFO {
    DWORD       HTFlags;
    DWORD       HTPatternSize;
    DWORD       DevPelsDPI;
    COLORINFO   ColorInfo;
    } DEVHTINFO, *PDEVHTINFO;

#define DEVHTADJF_COLOR_DEVICE      0x00000001
#define DEVHTADJF_ADDITIVE_DEVICE   0x00000002

typedef struct _DEVHTADJDATA {
    DWORD       DeviceFlags;
    DWORD       DeviceXDPI;
    DWORD       DeviceYDPI;
    PDEVHTINFO  pDefHTInfo;
    PDEVHTINFO  pAdjHTInfo;
    } DEVHTADJDATA, *PDEVHTADJDATA;

LONG WINAPI HTUI_DeviceColorAdjustment( LPSTR pDeviceName, PDEVHTADJDATA pDevHTAdjData );



//
// General support APIS
//

VOID WINAPI EngDebugBreak( VOID );
//VOID WINAPI EngDebugPrint( LPCSTR StandardPrefix,LPCSTR DebugMessage, va_list ap );
VOID WINAPI EngQueryPerformanceCounter( LONGLONG  *pPerformanceCount );
VOID WINAPI EngQueryPerformanceFrequency( LONGLONG  *pFrequency );
BOOL WINAPI EngSetPointerTag( HDEV hdev, SURFOBJ *psoMask, SURFOBJ *psoColor, XLATEOBJ *pxlo, FLONG fl );

//
// Kernel mode memory operations
//

#define FL_ZERO_MEMORY      0x00000001

#define EngAllocMem(flags, cj, tag) ((PVOID) GlobalAlloc(((flags) & FL_ZERO_MEMORY) ? GPTR : GMEM_FIXED, cj))
#define EngFreeMem(p)               GlobalFree((HGLOBAL) (p))
#define EngAllocUserMem(cj, tag)    ((PVOID) GlobalAlloc(GMEM_FIXED,cj))
#define EngFreeUserMem(p)           GlobalFree((HGLOBAL) (p))
#define EngAllocPrivateUserMem( psl, cj, tag) ((PVOID) GlobalAlloc(GMEM_FIXED,cj))
#define EngFreePrivateUserMem( psl, p)        GlobalFree((HGLOBAL) (p))
#define EngMulDiv                   MulDiv

//
// User mode memory Operations
//
VOID WINAPI EngProbeForRead( PVOID Address, ULONG Length, ULONG Alignment  );
VOID WINAPI EngProbeForReadAndWrite( PVOID Address, ULONG Length, ULONG Alignment );
HANDLE WINAPI EngSecureMem( PVOID Address, ULONG Length );
VOID WINAPI EngUnsecureMem( HANDLE hSecure );
DWORD WINAPI EngDeviceIoControl( HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer,
    DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned );

//
// Loading drivers and getting entry points from them
//

#define EngLoadImage(filename)               ((HANDLE) LoadLibraryW(filename))
#define EngFindImageProcAddress(h, procname) ((PVOID) GetProcAddress(h, procname))
#define EngUnloadImage(h)                    FreeLibrary((HMODULE) (h))

//
// callback for extra PDEV information
//
LPWSTR WINAPI EngGetPrinterDataFileName( HDEV hdev );
LPWSTR WINAPI EngGetDriverName( HDEV hdev );

typedef struct _TYPE1_FONT
{
    HANDLE  hPFM;
    HANDLE  hPFB;
    ULONG   ulIdentifier;
} TYPE1_FONT;


BOOL WINAPI EngGetType1FontList(
    HDEV            hdev,
    TYPE1_FONT      *pType1Buffer,
    ULONG           cjType1Buffer,
    PULONG          pulLocalFonts,
    PULONG          pulRemoteFonts,
    LARGE_INTEGER   *pLastModified
    );

//
// Manipulating resource sections
//

HANDLE WINAPI EngLoadModule( LPWSTR pwsz );
PVOID WINAPI EngFindResource( HANDLE h, int    iName, int    iType, PULONG pulSize );
VOID WINAPI EngFreeModule( HANDLE h );
BOOL WINAPI EngDeleteFile( LPWSTR pwszFileName );

PVOID WINAPI EngMapFile( LPWSTR pwsz, ULONG cjSize, ULONG_PTR  *piFile );
BOOL WINAPI EngUnmapFile ( ULONG_PTR iFile );
//
// FontFile Callbacks
//

VOID WINAPI EngUnmapFontFile( ULONG_PTR iFile );
BOOL WINAPI EngMapFontFile( ULONG_PTR iFile, PULONG *ppjBuf, ULONG *pcjBuf );
VOID WINAPI EngUnmapFontFileFD( ULONG_PTR iFile );
BOOL WINAPI EngMapFontFileFD( ULONG_PTR iFile, PULONG *ppjBuf, ULONG *pcjBuf );
BOOL WINAPI EngLpkInstalled();



//
// Semaphores
//

typedef void *HSEMAPHORE;

HSEMAPHORE WINAPI EngCreateSemaphore( VOID );
VOID WINAPI EngAcquireSemaphore( HSEMAPHORE hsem );
VOID WINAPI EngReleaseSemaphore( HSEMAPHORE hsem );
VOID WINAPI EngDeleteSemaphore( HSEMAPHORE hsem );

//
// Semaphore wrapper with a reference count for thread-safe creation and
// destruction.  Data must be created zero-filled.
//
// Use EngAcquire/ReleaseSemaphore on hsem for access protection.
//

typedef struct _ENGSAFESEMAPHORE
{
    HSEMAPHORE hsem;
    LONG lCount;
} ENGSAFESEMAPHORE;

BOOL WINAPI EngInitializeSafeSemaphore( ENGSAFESEMAPHORE *pssem );
VOID WINAPI EngDeleteSafeSemaphore( ENGSAFESEMAPHORE *pssem );

VOID WINAPI EngMultiByteToUnicodeN( LPWSTR UnicodeString, ULONG MaxBytesInUnicodeString, PULONG BytesInUnicodeString, LPCSTR MultiByteString, ULONG BytesInMultiByteString );
VOID WINAPI EngUnicodeToMultiByteN( LPSTR MultiByteString, ULONG MaxBytesInMultiByteString, PULONG BytesInMultiByteString, PWSTR UnicodeString, ULONG BytesInUnicodeString );

// for the spooler

#define EngWritePrinter     WritePrinter
#define EngGetPrinter       GetPrinter
#define EngGetPrinterDriver GetPrinterDriver
#define EngGetPrinterData   GetPrinterData
#define EngSetPrinterData   SetPrinterData
#define EngEnumForms        EnumForms
#define EngGetForm          GetForm

ULONG WINAPI EngEscape( HANDLE hPrinter, ULONG iEsc, ULONG cjIn, PVOID pvIn, ULONG cjOut, PVOID pvOut );

    // any platform that has support for floats in the kernel

    typedef FLOAT FLOATOBJ;
    typedef FLOAT *PFLOATOBJ;

    #define   FLOATOBJ_SetFloat(pf,f)       {*(pf) = (f);           }
    #define   FLOATOBJ_SetLong(pf,l)        {*(pf) = (FLOAT)(l);    }

    #define   FLOATOBJ_GetFloat(pf)         *((PULONG)pf)
    #define   FLOATOBJ_GetLong(pf)          (LONG)*(pf)

    #define   FLOATOBJ_AddFloat(pf,f)       {*(pf) += f;            }
    #define   FLOATOBJ_AddLong(pf,l)        {*(pf) += (LONG)(l);    }
    #define   FLOATOBJ_Add(pf,pf1)          {*(pf) += *(pf1);       }

    #define   FLOATOBJ_SubFloat(pf,f)       {*(pf) -= f;            }
    #define   FLOATOBJ_SubLong(pf,l)        {*(pf) -= (LONG)(l);    }
    #define   FLOATOBJ_Sub(pf,pf1)          {*(pf) -= *(pf1);       }

    #define   FLOATOBJ_MulFloat(pf,f)       {*(pf) *= f;            }
    #define   FLOATOBJ_MulLong(pf,l)        {*(pf) *= (LONG)(l);    }
    #define   FLOATOBJ_Mul(pf,pf1)          {*(pf) *= *(pf1);       }

    #define   FLOATOBJ_DivFloat(pf,f)       {*(pf) /= f;            }
    #define   FLOATOBJ_DivLong(pf,l)        {*(pf) /= (LONG)(l);    }
    #define   FLOATOBJ_Div(pf,pf1)          {*(pf) /= *(pf1);       }

    #define   FLOATOBJ_Neg(pf)              {*(pf) = -*(pf);        }

    #define   FLOATOBJ_EqualLong(pf,l)          (*(pf) == (FLOAT)(l))
    #define   FLOATOBJ_GreaterThanLong(pf,l)    (*(pf) >  (FLOAT)(l))
    #define   FLOATOBJ_LessThanLong(pf,l)       (*(pf) <  (FLOAT)(l))

    #define   FLOATOBJ_Equal(pf,pf1)            (*(pf) == *(pf1))
    #define   FLOATOBJ_GreaterThan(pf,pf1)      (*(pf) >  *(pf1))
    #define   FLOATOBJ_LessThan(pf,pf1)         (*(pf) <  *(pf1))

#if defined(USERMODE_DRIVER)

typedef XFORML FLOATOBJ_XFORM ;
typedef XFORML *PFLOATOBJ_XFORM;
typedef XFORML FAR *LPFLOATOBJ_XFORM;

#define XFORMOBJ_iGetFloatObjXform XFORMOBJ_iGetXform

#else

typedef struct  tagFLOATOBJ_XFORM
{
    FLOATOBJ eM11;
    FLOATOBJ eM12;
    FLOATOBJ eM21;
    FLOATOBJ eM22;
    FLOATOBJ eDx;
    FLOATOBJ eDy;
} FLOATOBJ_XFORM, *PFLOATOBJ_XFORM, FAR *LPFLOATOBJ_XFORM;

ULONG WINAPI XFORMOBJ_iGetFloatObjXform(
    XFORMOBJ *pxo,
    FLOATOBJ_XFORM * pfxo
    );

#endif


// SORT specific defines

typedef int (__cdecl *SORTCOMP)(const void *pv1, const void *pv2);

VOID WINAPI EngSort(
    PBYTE pjBuf,
    ULONG c,
    ULONG cjElem,
    SORTCOMP pfnComp
    );

typedef struct _ENG_TIME_FIELDS {
    USHORT usYear;        // range [1601...]
    USHORT usMonth;       // range [1..12]
    USHORT usDay;         // range [1..31]
    USHORT usHour;        // range [0..23]
    USHORT usMinute;      // range [0..59]
    USHORT usSecond;      // range [0..59]
    USHORT usMilliseconds;// range [0..999]
    USHORT usWeekday;     // range [0..6] == [Sunday..Saturday]
} ENG_TIME_FIELDS, *PENG_TIME_FIELDS;

VOID WINAPI EngQueryLocalTime(PENG_TIME_FIELDS );

FD_GLYPHSET* WINAPI EngComputeGlyphSet(INT nCodePage, INT nFirstChar, INT cChars  );
INT WINAPI EngMultiByteToWideChar( UINT CodePage, LPWSTR WideCharString, INT BytesInWideCharString, LPSTR MultiByteString, INT BytesInMultiByteString );
INT WINAPI EngWideCharToMultiByte( UINT CodePage, LPWSTR WideCharString, INT BytesInWideCharString, LPSTR MultiByteString, INT BytesInMultiByteString );
VOID WINAPI EngGetCurrentCodePage( USHORT *OemCodePage, USHORT *AnsiCodePage );
HANDLE WINAPI EngLoadModuleForWrite( LPWSTR pwsz, ULONG cjSizeOfModule );

LARGE_INTEGER WINAPI EngQueryFileTimeStamp ( LPWSTR pwsz );
BOOL WINAPI EngGetFileChangeTime( HANDLE h, LARGE_INTEGER   *pChangeTime );
BOOL WINAPI EngGetFilePath( __in HANDLE h, __out WCHAR (*pDest)[MAX_PATH+1] );
ULONG WINAPI EngSaveFloatingPointState( VOID *pBuffer, ULONG cjBufferSize );
BOOL WINAPI EngRestoreFloatingPointState( VOID *pBuffer );

//
//  Engine Event support.
//

//
//  Opaque type for event objects.
//

typedef struct _PENG_EVENT * PEVENT;

//
//  This routine can only be called on PEVENTS returned from EngCreateEvent()
//  and must not be called on PEVENTs returned from EngMapEvent().
//

BOOL WINAPI EngDeleteEvent(__in  PEVENT  pEngEvent );
BOOL WINAPI EngCreateEvent(__out PEVENT *ppEngEvent );

//
//  This routine must be called by Display driver process terminate. This routine can only
//  be called on pEvent PEVENTs returned by EngMapEvent(). It must not be called on
//  pEvents returned via EngCreateEvent(). It must not be called in the PDRVCLEANPROC typed
//  below
//
BOOL WINAPI EngUnmapEvent( __in  HDRVOBJ pDrvObj );

//
//  May be called by Display driver. Can only be called on events created by
//  the Display driver, not on mapped events. Returns TRUE if successful,
//  FALSE otherwise. FALSE indicates an invalid parameter, which must not
//  be used again.
//

BOOL WINAPI EngWaitForSingleObject( __in  PEVENT pEngEvent, __in PLARGE_INTEGER  pTimeOut );

//
// Querying of system attributes.
//

typedef enum _ENG_SYSTEM_ATTRIBUTE {
    EngProcessorFeature = 1,
    EngNumberOfProcessors,
    EngOptimumAvailableUserMemory,
    EngOptimumAvailableSystemMemory,
} ENG_SYSTEM_ATTRIBUTE;

#define QSA_MMX 0x00000100

BOOL WINAPI
EngQuerySystemAttribute(
    ENG_SYSTEM_ATTRIBUTE CapNum,
    PDWORD pCapability);

#define ENG_FNT_CACHE_READ_FAULT    0x1
#define ENG_FNT_CACHE_WRITE_FAULT   0x2

PVOID WINAPI  EngFntCacheLookUp(ULONG FastCheckSum, ULONG * pulSize);
PVOID WINAPI  EngFntCacheAlloc(ULONG FastCheckSum, ULONG ulSize);

VOID  WINAPI  EngFntCacheFault(ULONG ulFastCheckSum, ULONG iFaultMode);

typedef enum _ENG_DEVICE_ATTRIBUTE {
    QDA_RESERVED = 0,
    QDA_ACCELERATION_LEVEL = 1
} ENG_DEVICE_ATTRIBUTE;

BOOL WINAPI
EngQueryDeviceAttribute(
    HDEV                    hdev,
    ENG_DEVICE_ATTRIBUTE    devAttr,
    VOID *                  pvIn,
    ULONG                   ulInSize,
    VOID *                  pvOUt,
    ULONG                   ulOutSize);

typedef struct
{
   DWORD nSize;
   HDC   hdc;
   PBYTE pvEMF;
   PBYTE pvCurrentRecord;
} EMFINFO, *PEMFINFO;

BOOL WINAPI
EngQueryEMFInfo(
    HDEV              hdev,
    EMFINFO           *pEMFInfo);

//
// EngProcessorFeature
//

//
// EngNumberOfProcessors
//
// Number of active processors in the machine.
//

//
// EngOptimumAvailableUserMemory
//
// Optimum amount of user-mode memory available to avoid paging.
// Returns the number of bytes for the optimum allocation size
// Memory is allocated via EngAllocUserMem.
//

//
// EngOptimumAvailableSystemMemory
//
// Optimum amount of system memory available to avoid paging.
// Returns the number of bytes for the optimum allocation size.
// Memory is allocated via EngAllocMem.
//

//
// DDI entrypoint function prototypes
//
typedef BOOL   (WINAPI *PFN_DrvEnableDriver)(ULONG,ULONG,PDRVENABLEDATA);
typedef DHPDEV (WINAPI *PFN_DrvEnablePDEV) (PDEVMODEW,LPWSTR,ULONG,HSURF*,ULONG,GDIINFO*,ULONG,PDEVINFO,HDEV,LPWSTR,HANDLE);
typedef VOID   (WINAPI *PFN_DrvCompletePDEV)(DHPDEV,HDEV);
typedef VOID   (WINAPI *PFN_DrvDisablePDEV)(DHPDEV);
typedef VOID   (WINAPI *PFN_DrvSynchronize)(DHPDEV,RECTL *);
typedef HSURF  (WINAPI *PFN_DrvEnableSurface)(DHPDEV);
typedef VOID   (WINAPI *PFN_DrvDisableDriver)(VOID);
typedef VOID   (WINAPI *PFN_DrvDisableSurface)(DHPDEV);
typedef BOOL   (WINAPI *PFN_DrvAssertMode)(DHPDEV, BOOL);
typedef BOOL   (WINAPI *PFN_DrvTextOut)(SURFOBJ *,STROBJ *,FONTOBJ *,CLIPOBJ *,RECTL *,RECTL *,BRUSHOBJ *,BRUSHOBJ *,POINTL *,MIX);
typedef BOOL   (WINAPI *PFN_DrvStretchBlt)(SURFOBJ *,SURFOBJ *,SURFOBJ *,CLIPOBJ *,XLATEOBJ *,COLORADJUSTMENT *,POINTL *,RECTL *,RECTL *,POINTL *,ULONG);
typedef BOOL   (WINAPI *PFN_DrvStretchBltROP)(SURFOBJ *,SURFOBJ *,SURFOBJ *,CLIPOBJ *,XLATEOBJ *,COLORADJUSTMENT *,POINTL *,RECTL *,RECTL *,POINTL *,ULONG, BRUSHOBJ *,ROP4);
typedef BOOL   (WINAPI *PFN_DrvTransparentBlt)(SURFOBJ *, SURFOBJ *, CLIPOBJ *, XLATEOBJ *, RECTL *, RECTL *, ULONG, ULONG);
typedef BOOL   (WINAPI *PFN_DrvPlgBlt)(SURFOBJ *,SURFOBJ *,SURFOBJ *,CLIPOBJ *,XLATEOBJ *,COLORADJUSTMENT *,POINTL *,POINTFIX *,RECTL *,POINTL *,ULONG);
typedef BOOL   (WINAPI *PFN_DrvBitBlt)(SURFOBJ *,SURFOBJ *,SURFOBJ *,CLIPOBJ *,XLATEOBJ *,RECTL *,POINTL *,POINTL *,BRUSHOBJ *,POINTL *,ROP4);
typedef BOOL   (WINAPI *PFN_DrvRealizeBrush)(BRUSHOBJ *,SURFOBJ *,SURFOBJ *,SURFOBJ *,XLATEOBJ *,ULONG);
typedef BOOL   (WINAPI *PFN_DrvCopyBits)(SURFOBJ *,SURFOBJ *,CLIPOBJ *,XLATEOBJ *,RECTL *,POINTL *);
typedef ULONG  (WINAPI *PFN_DrvDitherColor)(DHPDEV, ULONG, ULONG, ULONG *);
typedef HBITMAP (WINAPI *PFN_DrvCreateDeviceBitmap)(DHPDEV, SIZEL, ULONG);
typedef VOID   (WINAPI *PFN_DrvDeleteDeviceBitmap)(DHSURF);
typedef BOOL   (WINAPI *PFN_DrvSetPalette)(DHPDEV, PALOBJ *, FLONG, ULONG, ULONG);
typedef ULONG  (WINAPI *PFN_DrvEscape)(SURFOBJ *, ULONG, ULONG, PVOID, ULONG, PVOID);
typedef ULONG  (WINAPI *PFN_DrvDrawEscape)(SURFOBJ *, ULONG, CLIPOBJ *, RECTL *, ULONG, PVOID);
typedef PIFIMETRICS (WINAPI *PFN_DrvQueryFont)(DHPDEV, ULONG_PTR, ULONG, ULONG *);
typedef PVOID  (WINAPI *PFN_DrvQueryFontTree)(DHPDEV, ULONG_PTR, ULONG, ULONG, ULONG *);
typedef LONG   (WINAPI *PFN_DrvQueryFontData)(DHPDEV, FONTOBJ *, ULONG, HGLYPH, GLYPHDATA *, PVOID, ULONG);
typedef VOID   (WINAPI *PFN_DrvFree)(PVOID, ULONG);
typedef VOID   (WINAPI *PFN_DrvDestroyFont)(FONTOBJ *);
typedef LONG   (WINAPI *PFN_DrvQueryFontCaps)(ULONG, ULONG *);
typedef HFF    (WINAPI *PFN_DrvLoadFontFile)(ULONG, ULONG_PTR *, PVOID *, ULONG *, DESIGNVECTOR *, ULONG, ULONG);
typedef BOOL   (WINAPI *PFN_DrvUnloadFontFile)(ULONG_PTR);
typedef ULONG  (WINAPI *PFN_DrvSetPointerShape)(SURFOBJ *, SURFOBJ *, SURFOBJ *,XLATEOBJ *,LONG,LONG,LONG,LONG,RECTL *,FLONG);
typedef BOOL   (WINAPI *PFN_DrvSendPage)(SURFOBJ *);
typedef BOOL   (WINAPI *PFN_DrvStartPage)(SURFOBJ *pso);
typedef BOOL   (WINAPI *PFN_DrvStartDoc)(SURFOBJ *pso, LPWSTR pwszDocName, DWORD dwJobId);
typedef BOOL   (WINAPI *PFN_DrvEndDoc)(SURFOBJ *pso, FLONG fl);
typedef BOOL   (WINAPI *PFN_DrvQuerySpoolType)(DHPDEV dhpdev, LPWSTR pwchType);
typedef BOOL   (WINAPI *PFN_DrvLineTo)(SURFOBJ *,CLIPOBJ *,BRUSHOBJ *,LONG,LONG,LONG,LONG,RECTL *,MIX);
typedef BOOL   (WINAPI *PFN_DrvStrokePath)(SURFOBJ *,PATHOBJ *,CLIPOBJ *,XFORMOBJ *,BRUSHOBJ *,POINTL *,LINEATTRS *,MIX);
typedef BOOL   (WINAPI *PFN_DrvFillPath)(SURFOBJ *,PATHOBJ *,CLIPOBJ *,BRUSHOBJ *,POINTL *,MIX,FLONG);
typedef BOOL   (WINAPI *PFN_DrvStrokeAndFillPath)(SURFOBJ *,PATHOBJ *,CLIPOBJ *,XFORMOBJ *,BRUSHOBJ *,LINEATTRS *,BRUSHOBJ *,POINTL *,MIX,FLONG);
typedef BOOL   (WINAPI *PFN_DrvPaint)(SURFOBJ *,CLIPOBJ *,BRUSHOBJ *,POINTL *,MIX);
typedef ULONG  (WINAPI *PFN_DrvGetGlyphMode)(DHPDEV dhpdev,FONTOBJ *pfo);
typedef BOOL   (WINAPI *PFN_DrvResetPDEV)(DHPDEV dhpdevOld, DHPDEV dhpdevNew);
typedef ULONG_PTR  (WINAPI *PFN_DrvSaveScreenBits)(SURFOBJ *, ULONG, ULONG_PTR, RECTL *);
typedef ULONG  (WINAPI *PFN_DrvGetModes)(HANDLE, ULONG, DEVMODEW *);
typedef LONG   (WINAPI *PFN_DrvQueryTrueTypeTable)(ULONG_PTR, ULONG, ULONG, PTRDIFF, ULONG, BYTE *, PBYTE *, ULONG *);
typedef LONG   (WINAPI *PFN_DrvQueryTrueTypeSection)(ULONG, ULONG, ULONG, HANDLE *, PTRDIFF *);
typedef LONG   (WINAPI *PFN_DrvQueryTrueTypeOutline)(DHPDEV, FONTOBJ *, HGLYPH, BOOL, GLYPHDATA *, ULONG, TTPOLYGONHEADER *);
typedef PVOID  (WINAPI *PFN_DrvGetTrueTypeFile)(ULONG_PTR, ULONG *);
typedef LONG   (WINAPI *PFN_DrvQueryFontFile)(ULONG_PTR, ULONG, ULONG, ULONG *);
typedef PFD_GLYPHATTR   (WINAPI *PFN_DrvQueryGlyphAttrs)(FONTOBJ *, ULONG );
typedef BOOL   (WINAPI *PFN_DrvQueryAdvanceWidths)(DHPDEV,FONTOBJ *,ULONG,HGLYPH *,PVOID,ULONG);
typedef ULONG  (WINAPI *PFN_DrvFontManagement)(SURFOBJ *,FONTOBJ *,ULONG,ULONG,PVOID,ULONG,PVOID);
typedef BOOL   (WINAPI *PFN_DrvSetPixelFormat)(SURFOBJ *,LONG,HWND);
typedef LONG   (WINAPI *PFN_DrvDescribePixelFormat)(DHPDEV,LONG,ULONG,PIXELFORMATDESCRIPTOR *);
typedef BOOL   (WINAPI *PFN_DrvSwapBuffers)(SURFOBJ *, WNDOBJ *);
typedef BOOL   (WINAPI *PFN_DrvStartBanding)(SURFOBJ *, POINTL *ppointl);
typedef BOOL   (WINAPI *PFN_DrvNextBand)(SURFOBJ *, POINTL *ppointl);
typedef BOOL   (WINAPI *PFN_DrvQueryPerBandInfo)(SURFOBJ *,PERBANDINFO *);
typedef HANDLE (WINAPI *PFN_DrvIcmCreateColorTransform)(DHPDEV,LPLOGCOLORSPACEW,LPVOID,ULONG,LPVOID,ULONG,LPVOID,ULONG,DWORD);
typedef BOOL   (WINAPI *PFN_DrvIcmDeleteColorTransform)(DHPDEV,HANDLE);
typedef BOOL   (WINAPI *PFN_DrvIcmCheckBitmapBits)(DHPDEV,HANDLE,SURFOBJ *,PBYTE);
typedef BOOL   (WINAPI *PFN_DrvIcmSetDeviceGammaRamp)(DHPDEV,ULONG,LPVOID);
typedef BOOL   (WINAPI *PFN_DrvAlphaBlend)(SURFOBJ*,SURFOBJ*,CLIPOBJ*,XLATEOBJ*,PRECTL,PRECTL,BLENDOBJ *);
typedef BOOL   (WINAPI *PFN_DrvGradientFill)(SURFOBJ*,CLIPOBJ*,XLATEOBJ*,TRIVERTEX*,ULONG,PVOID,ULONG,RECTL *,POINTL *,ULONG);
typedef BOOL   (WINAPI *PFN_DrvQueryDeviceSupport)(SURFOBJ*,XLATEOBJ*,XFORMOBJ*,ULONG,ULONG,PVOID,ULONG,PVOID);
typedef VOID   (WINAPI *PFN_DrvSynchronizeSurface)(SURFOBJ*, RECTL*, FLONG);
typedef VOID   (WINAPI *PFN_DrvNotify)(SURFOBJ*, ULONG, PVOID);



#define PROPSHEETUI_REASON_INIT             0
#define PROPSHEETUI_REASON_GET_INFO_HEADER  1
#define PROPSHEETUI_REASON_DESTROY          2
#define PROPSHEETUI_REASON_SET_RESULT       3
#define PROPSHEETUI_REASON_GET_ICON         4
#define MAX_PROPSHEETUI_REASON_INDEX        4

#define PROPSHEETUI_INFO_VERSION            0x0100

#define PSUIINFO_UNICODE                    0x0001

typedef LONG_PTR (CALLBACK *PFNCOMPROPSHEET)(HANDLE hComPropSheet, UINT   Function, LPARAM lParam1, LPARAM lParam2);

typedef struct _PROPSHEETUI_INFO {
	WORD            cbSize;
	WORD            Version;
	WORD            Flags;
	WORD            Reason;
	HANDLE          hComPropSheet;
	PFNCOMPROPSHEET pfnComPropSheet;
	LPARAM          lParamInit;
	ULONG_PTR       UserData;
	ULONG_PTR       Result;
} PROPSHEETUI_INFO, *PPROPSHEETUI_INFO;

LONG WINAPI DrvDevicePropertySheets( PPROPSHEETUI_INFO pPSUIInfo, LPARAM lParam	);

typedef struct _DEVICEPROPERTYHEADER {
	WORD    cbSize;
	WORD    Flags;
	HANDLE  hPrinter;
	LPWSTR  pszPrinterName;
} DEVICEPROPERTYHEADER, *PDEVICEPROPERTYHEADER;

#define DPS_NOPERMISSION    0x0001


//
// For document properties replace DocumentProperties.
//
// Note: if pPSUIInfo is NULL then the call need not to display any dialog
//       boxes (Ignored the DC_PROMPT bit in the fMode, the lParam in this case
//       is a pointer to DOCUMENTPROPERTYHEADER
//

LONG WINAPI DrvDocumentPropertySheets( PPROPSHEETUI_INFO pPSUIInfo, LPARAM lParam );

typedef struct _DOCUMENTPROPERTYHEADER {
	WORD        cbSize;
	WORD        Reserved;
	HANDLE      hPrinter;
	LPWSTR      pszPrinterName;
	PDEVMODE    pdmIn;
	PDEVMODE    pdmOut;
	DWORD       cbOut;
	DWORD       fMode;
} DOCUMENTPROPERTYHEADER, *PDOCUMENTPROPERTYHEADER;

#define DM_ADVANCED         0x10
#define DM_NOPERMISSION     0x20
#define DM_USER_DEFAULT     0x40

// Devmode conversion function used by GetPrinter and SetPrinter
BOOL WINAPI DrvConvertDevMode( LPWSTR pPrinterName, PDEVMODE pdmIn, PDEVMODE pdmOut, LONG * pcbNeeded, DWORD fMode );
#define CDM_CONVERT         0x01
#define CDM_CONVERT351      0x02
#define CDM_DRIVER_DEFAULT  0x04


//
// This is for DevQueryPrintEx()
//

typedef struct _DEVQUERYPRINT_INFO {
	WORD    cbSize;         // size of this structure in bytes
	WORD    Level;          // Level of this info, 1 for this version
	HANDLE  hPrinter;       // handle to the printer for the query
	DEVMODE *pDevMode;      // pointer to the DEVMODE for this job.
	LPWSTR  pszErrorStr;    // pointer to the error string buffer.
	DWORD   cchErrorStr;    // count characters of pwErrorStr passed.
	DWORD   cchNeeded;      // count characters of pwErrorStr needed.
} DEVQUERYPRINT_INFO, *PDEVQUERYPRINT_INFO;

BOOL WINAPI DevQueryPrintEx( PDEVQUERYPRINT_INFO pDQPInfo );

//
// This for the DrvUpgradePrinter
//

typedef struct _DRIVER_UPGRADE_INFO_1 {
	LPWSTR  pPrinterName;
	LPWSTR  pOldDriverDirectory;
} DRIVER_UPGRADE_INFO_1, *PDRIVER_UPGRADE_INFO_1;

typedef struct _DRIVER_UPGRADE_INFO_2 {
	LPWSTR   pPrinterName;
	LPWSTR   pOldDriverDirectory;
	DWORD    cVersion;
	LPWSTR   pName;
	LPWSTR   pEnvironment;
	LPWSTR   pDriverPath;
	LPWSTR   pDataFile;
	LPWSTR   pConfigFile;
	LPWSTR   pHelpFile;
	LPWSTR   pDependentFiles;
	LPWSTR   pMonitorName;
	LPWSTR   pDefaultDataType;
	LPWSTR   pszzPreviousNames;
} DRIVER_UPGRADE_INFO_2, *PDRIVER_UPGRADE_INFO_2;

BOOL WINAPI DrvUpgradePrinter( DWORD Level, LPBYTE pDriverUpgradeInfo );

//
// DrvDocumentEvent
//
//
//  Defines and proto-types for hooking GDI printer management functions
//
//  return values: -1 means error, 0 means not supported function
//
//  CreateDCPre must return > 0 or none of the others will be called.
//
//
//  CREATEDCPRE
//      return failure from CreateDC if this fails, CREATEDCPOST not called
//      bIC - TRUE if came from CreateIC
//      output devmode - this is the devmode that actualy gets passed to the
//      server side driver.  Any data needed in EnablePDEV should be passed
//      as part of the DriverExtra.
//
//  CREATEDCPOST
//      return value is ignored
//      the hdc will be 0 if something failed since CREATEDCPRE
//      The input buffer contains a pointer to the devmode returned in the
//      CREATEDCPRE output buffer
//
//  RESETDCPRE
//      return failure from ResetDC if this fails, CREATEDCPOST not called
//
//  RESETDCPOST
//      return value is ignored
//
//  STARTDOCPRE
//      return failure form StartDoc if this fails, driver not called
//
//  STARTDOCPOST
//      return failure form StartDoc if this fails, driver already called.
//      AbortDoc() called.
//
//  STARTPAGE
//      return failure form EndPage if this fails, driver not called
//
//  ENDPAGE
//      return value is ignored, DrvEndPage always called
//
//  ENDDOCPRE
//      return value is ignored, DrvEndDoc always called
//
//  ENDDOCPOST
//      return value is ignored, DrvEndDoc has alreadybeen called
//
//  ABORTDOC
//      return value is ignored
//
//  DELETEDC
//      return value is ignored
//
//  EXTESCAPE
//      return value is ignored
//      The input buffer includes the ExtEscape escape value, size of input
//      buffer to ExtEscape and the input buffer passed in.
//      The output buffer is just the buffer that was passed to ExtEscape
//
//  DOCUMENTEVENT_SPOOLED
//      This flag is added to the iEsc value if the document is being spooled
//      to a metafile rather than going direct.  Note that if this bit is set
//
//

#define DOCUMENTEVENT_EVENT(iEsc) (LOWORD(iEsc))
#define DOCUMENTEVENT_FLAGS(iEsc) (HIWORD(iEsc))

//
// Escape codes for DrvDocumentEvent
//

#define DOCUMENTEVENT_FIRST         1   // Inclusive lower bound
#define DOCUMENTEVENT_CREATEDCPRE   1   // in-pszDriver, pszDevice, pdm, bIC, out-ppdm
#define DOCUMENTEVENT_CREATEDCPOST  2   // in-ppdm
#define DOCUMENTEVENT_RESETDCPRE    3   // in-pszDriver, pszDevice, pdm, out-ppdm
#define DOCUMENTEVENT_RESETDCPOST   4   // in-ppdm
#define DOCUMENTEVENT_STARTDOC      5   // none
#define DOCUMENTEVENT_STARTDOCPRE   5   // none
#define DOCUMENTEVENT_STARTPAGE     6   // none
#define DOCUMENTEVENT_ENDPAGE       7   // none
#define DOCUMENTEVENT_ENDDOC        8   // none
#define DOCUMENTEVENT_ENDDOCPRE     8   // none
#define DOCUMENTEVENT_ABORTDOC      9   // none
#define DOCUMENTEVENT_DELETEDC     10   // none
#define DOCUMENTEVENT_ESCAPE       11   // in-iEsc, cjInBuf, inBuf, out-outBuf
#define DOCUMENTEVENT_ENDDOCPOST   12   // none
#define DOCUMENTEVENT_STARTDOCPOST 13   // none
#define DOCUMENTEVENT_LAST         14   // Non-inclusive upper bound

#define DOCUMENTEVENT_SPOOLED   0x10000

//
// Return values for DrvDocumentEvent
//

#define DOCUMENTEVENT_SUCCESS     1
#define DOCUMENTEVENT_UNSUPPORTED 0
#define DOCUMENTEVENT_FAILURE     -1

int WINAPI DrvDocumentEvent( HANDLE hPrinter, HDC hdc, int iEsc, ULONG cbIn, PULONG pbIn, ULONG cbOut, PULONG  pbOut );


//
// DrvPrinterEvent
//
//
//    DrvPrinterEvent are called by the print subsystem when events
//    happen that might be of interest to a printer driver
//    The only event which should be implemented in the driver
//    is PRITNER_EVENT_INITIALIZE so that default settings are created
//    for the printer.
//
// PRINTER_EVENT_ADD_CONNECTION
//        return value ignored
//        Called after a successful AddPrinterConnection API
//        in the context of the calling app
//        lParam NULL
//
// PRINTER_EVENT_DELETE_CONNECTION
//        return value ignored
//        Called Before DeletePrinterConnect API
//        in the context of the calling app
//        lParam NULL
//
// PRINTER_EVENT_INITIALIZE
//        Called when a printer is created for the driver to
//        initialize its registry settings
//        Called in the spooler process
//        lParam NULL
//
// PRINTER_EVENT_DELETE
//        Called when a printer is about to be deleted
//        Called in the spooler process
//        lParam NULL
//
// PRINTER_EVENT_CACHE_REFRESH
//        return value ignored
//        called in spooler process
//        No UI
//        called when spooler detects that something has
//        changed in the workstaion cache or when establishing
//        the cache.
//        allows driver to update any private cache data
//        ( such as font files etc. )
//
// PRINTER_EVENT_CACHE_DELETE
//        return value ignored
//        called in spooler process
//        No UI
//        called when spooler is deleting a cached printer
//        allows printer driver to delete anything it has
//        cached
//
// PRINTER_EVENT_FLAG_NO_UI
//        Do not bring up UI when this flag it ON
//

//
// DrvPrinterEvent DriverEvent code
//

#define PRINTER_EVENT_ADD_CONNECTION            1
#define PRINTER_EVENT_DELETE_CONNECTION         2
#define PRINTER_EVENT_INITIALIZE                3
#define PRINTER_EVENT_DELETE                    4
#define PRINTER_EVENT_CACHE_REFRESH             5
#define PRINTER_EVENT_CACHE_DELETE              6

//
// DrvPrinterEvent Flags
//

#define PRINTER_EVENT_FLAG_NO_UI        0x00000001


BOOL WINAPI DrvPrinterEvent( LPWSTR  pPrinterName, int DriverEvent, DWORD Flags, LPARAM lParam );

//
// DrvDriverEvent is called when any version of the printer driver is deleted.
//
#define DRIVER_EVENT_INITIALIZE        0x00000001
#define DRIVER_EVENT_DELETE            0x00000002

BOOL WINAPI DrvDriverEvent( DWORD dwDriverEvent, DWORD dwLevel, LPBYTE pDriverInfo, LPARAM  lParam );

// Print processor capabilities for the driver.
#define BORDER_PRINT                   0x00000000        // default
#define NO_BORDER_PRINT                0x00000001

//#define NORMAL_PRINT                   0x00000000        // default
//#define REVERSE_PRINT                  0x00000001
#define BOOKLET_PRINT                  0x00000002

#define NO_COLOR_OPTIMIZATION          0x00000000        // default
#define COLOR_OPTIMIZATION             0x00000001

typedef struct _ATTRIBUTE_INFO_1 {
	DWORD    dwJobNumberOfPagesPerSide;
	DWORD    dwDrvNumberOfPagesPerSide;
	DWORD    dwNupBorderFlags;
	DWORD    dwJobPageOrderFlags;
	DWORD    dwDrvPageOrderFlags;
	DWORD    dwJobNumberOfCopies;
	DWORD    dwDrvNumberOfCopies;
} ATTRIBUTE_INFO_1, *PATTRIBUTE_INFO_1;

typedef struct _ATTRIBUTE_INFO_2 {
	DWORD    dwJobNumberOfPagesPerSide;
	DWORD    dwDrvNumberOfPagesPerSide;
	DWORD    dwNupBorderFlags;
	DWORD    dwJobPageOrderFlags;
	DWORD    dwDrvPageOrderFlags;
	DWORD    dwJobNumberOfCopies;
	DWORD    dwDrvNumberOfCopies;
	DWORD    dwColorOptimization;           // Added for monochrome optimization
} ATTRIBUTE_INFO_2, *PATTRIBUTE_INFO_2;

typedef struct _ATTRIBUTE_INFO_3 {
	DWORD    dwJobNumberOfPagesPerSide;
	DWORD    dwDrvNumberOfPagesPerSide;
	DWORD    dwNupBorderFlags;
	DWORD    dwJobPageOrderFlags;
	DWORD    dwDrvPageOrderFlags;
	DWORD    dwJobNumberOfCopies;
	DWORD    dwDrvNumberOfCopies;
	DWORD    dwColorOptimization;           // Added for monochrome optimization
	short    dmPrintQuality;                // Added for monochrome optimization
	short    dmYResolution;                 // Added for monochrome optimization
} ATTRIBUTE_INFO_3, *PATTRIBUTE_INFO_3;


//
// DrvQueryJobAttributes is called by the spooler(print processor) to get information
// about the printing options used with the job. These options include N-up and reverse
// order printing.
//
BOOL
	DrvQueryJobAttributes(
	HANDLE      hPrinter,
	PDEVMODE    pDevMode,
	DWORD       dwLevel,
	LPBYTE      lpAttributeInfo
	);

//
// DrvQueryColorProfile is called by the GDI (graphics device interface) to get information
// about the default color profile for the given DEVMODE, used with ICM (image color
// management).
//
BOOL WINAPI DrvQueryColorProfile( HANDLE hPrinter, PDEVMODEW pdevmode, ULONG ulQueryMode, VOID *pvProfileData, ULONG *pcbProfileData, FLONG *pflProfileData );

// The value for ulQueryMode
#define QCP_DEVICEPROFILE   0x0000
#define QCP_SOURCEPROFILE   0x0001

// The flags for pflProfileData.
#define QCP_PROFILEMEMORY  0x0001 // The pvProfileData points the color profile data itself.
#define QCP_PROFILEDISK    0x0002 // The pvProfileData points the color profile file name in Unicode.

//
//  User Mode Printer Driver DLL,
//
//  Note on hPrinter passed into DrvSplStartDoc() and subsequent
//  DrvSplxxx calls
//
//
//  A. If you have DrvSplxxxx calls in separate DLL and link it with
//     spoolss.lib.
//
//      * The hPrinter will be valid for any call to the spooler, such as
//        WritePrinter(), GetPrinterData()
//
//      * To do this you must
//
//          1. Have separate DLL for all DrvSplxxx functions.
//          2. Put this DLL name into your dependency files (inf).
//          3. link to spoolss.lib rather than winspool.lib
//          4. Use SetPrinterData() with SPLPRINTER_USER_MODE_PRINTER_DRIVER
//             as key name, and this DLL name as data.
//          5. Call any spooler functions linked from spoolss.lib
//
//
//
//  B. If you have DrvSplxxx calls located in your printer driver UI DLL and
//     linked with winspool.lib
//
//      * The hPrinter is NOT valid for any spooler calls, such as
//        WritePrinter(), GetPrinterData() from within the DrvSplxxx driver
//        functions.
//
//      * To do any spooler call from inside of DrvSplxxxx function you must
//        do the following
//
//          1. hSpoolSS = LoadLibrary("spoolss.dll");
//          2. pfn = GetProcAddress("WritePrinter") or whatever the spooler
//             functions you wish to call
//          3. Call the pfn function pointer returned from GetProcAddress()
//          4. FreeLibrary(hSpoolSS);
//
//
//  The A method is recommended.
//
//
//  If a UserModePrinterDriver DLL is created the following routines are
//  required or optional
//
//  Required Routines
//      DrvSplStartDoc
//      DrvSplWritePrinter
//      DrvSplEndDoc
//      DrvSplClose
//
//
//  Optional Routines
//      DrvSplStart
//      DrvSplEndPage
//      DrvSplAbort
//
//

HANDLE	WINAPI DrvSplStartDoc( HANDLE hPrinter, DWORD JobId	);
BOOL	WINAPI DrvSplWritePrinter( HANDLE hDriver, LPVOID pBuf, DWORD cbBuf, LPDWORD pcWritten );
VOID	WINAPI DrvSplEndDoc( HANDLE hDriver );
VOID	WINAPI DrvSplClose( HANDLE hDriver );
BOOL	WINAPI DrvSplStartPage( HANDLE hDriver );
BOOL	WINAPI DrvSplEndPage( HANDLE  hDriver	);
VOID	WINAPI DrvSplAbort( HANDLE hDriver );

//
//  Printer Attribute
//  Use with SetPrinterData to define UMPD.DLL
//

#define SPLPRINTER_USER_MODE_PRINTER_DRIVER     TEXT("SPLUserModePrinterDriver")


#ifdef __cplusplus
}  // extern "C"
#endif
