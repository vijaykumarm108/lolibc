#pragma once

#ifndef _INC_LOCALE
#define _INC_LOCALE

#include "lolibbase.h"

/* All MS C compilers for Win32 platforms default to 8 byte alignment. */
#pragma pack(push,8)

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/* define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else  /* __cplusplus */
#define NULL    ((void *)0)
#endif  /* __cplusplus */
#endif  /* NULL */

	
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct * pthreadlocinfo;
typedef struct threadmbcinfostruct * pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct
{
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
} _locale_tstruct, *_locale_t;

#ifndef _TAGLC_ID_DEFINED
typedef struct tagLC_ID {
        unsigned short wLanguage;
        unsigned short wCountry;
        unsigned short wCodePage;
} LC_ID, *LPLC_ID;
#define _TAGLC_ID_DEFINED
#endif  /* _TAGLC_ID_DEFINED */

#ifndef _THREADLOCALEINFO
typedef struct threadlocaleinfostruct {
        int refcount;
        unsigned int lc_codepage;
        unsigned int lc_collate_cp;
        unsigned long lc_handle[6]; /* LCID */
        LC_ID lc_id[6];
        struct {
            char *locale;
            wchar_t *wlocale;
            int *refcount;
            int *wrefcount;
        } lc_category[6];
        int lc_clike;
        int mb_cur_max;
        int * lconv_intl_refcount;
        int * lconv_num_refcount;
        int * lconv_mon_refcount;
        struct lconv * lconv;
        int * ctype1_refcount;
        unsigned short * ctype1;
        const unsigned short * pctype;
        const unsigned char * pclmap;
        const unsigned char * pcumap;
        struct __lc_time_data * lc_time_curr;
} threadlocinfo;
#define _THREADLOCALEINFO
#endif

/* Locale categories */
#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MONETARY     3
#define LC_NUMERIC      4
#define LC_TIME         5

#define LC_MIN          LC_ALL
#define LC_MAX          LC_TIME

/* Locale convention structure */
#ifndef _LCONV_DEFINED
struct lconv {
	char *decimal_point;
	char *thousands_sep;
	char *grouping;
	char *int_curr_symbol;
	char *currency_symbol;
	char *mon_decimal_point;
	char *mon_thousands_sep;
	char *mon_grouping;
	char *positive_sign;
	char *negative_sign;
	char int_frac_digits;
	char frac_digits;
	char p_cs_precedes;
	char p_sep_by_space;
	char n_cs_precedes;
	char n_sep_by_space;
	char p_sign_posn;
	char n_sign_posn;
	wchar_t *_W_decimal_point;
	wchar_t *_W_thousands_sep;
	wchar_t *_W_int_curr_symbol;
	wchar_t *_W_currency_symbol;
	wchar_t *_W_mon_decimal_point;
	wchar_t *_W_mon_thousands_sep;
	wchar_t *_W_positive_sign;
	wchar_t *_W_negative_sign;
};
#define _LCONV_DEFINED
#endif  /* _LCONV_DEFINED */

/* ANSI: char lconv members default is CHAR_MAX which is compile time
   dependent. Defining and using _charmax here causes CRT startup code
   to initialize lconv members properly */

#ifdef _CHAR_UNSIGNED
extern int _charmax;
extern __inline int __dummy(void) { return _charmax; }
#endif  /* _CHAR_UNSIGNED */

/* function prototypes */

#ifndef _CONFIG_LOCALE_SWT
#define _ENABLE_PER_THREAD_LOCALE			0x1
#define _DISABLE_PER_THREAD_LOCALE			0x2
#define _ENABLE_PER_THREAD_LOCALE_GLOBAL	0x10
#define _DISABLE_PER_THREAD_LOCALE_GLOBAL	0x20
#define _ENABLE_PER_THREAD_LOCALE_NEW		0x100
#define _DISABLE_PER_THREAD_LOCALE_NEW		0x200
#define _CONFIG_LOCALE_SWT
#endif  /* _CONFIG_LOCALE_SWT */

_Check_return_opt_ _CRTIMP int __cdecl		_configthreadlocale( int _Flag);
_Check_return_opt_ _CRTIMP char * __cdecl	setlocale( int _Category, _In_opt_z_ const char * _Locale);
_Check_return_opt_ _CRTIMP struct lconv * __cdecl localeconv(void);
_Check_return_opt_ _CRTIMP _locale_t __cdecl _get_current_locale(void);
_Check_return_opt_ _CRTIMP _locale_t __cdecl _create_locale( int _Category, _In_z_ const char * _Locale);
_CRTIMP void __cdecl _free_locale(_In_opt_ _locale_t _Locale);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#pragma pack(pop)

#endif  /* _INC_LOCALE */
