#pragma once

#ifndef _INC_TIME
#define _INC_TIME

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#ifndef _CLOCK_T_DEFINED
	typedef long clock_t;
#define _CLOCK_T_DEFINED
#endif  /* _CLOCK_T_DEFINED */

#ifndef _TM_DEFINED
	struct tm {
		int tm_sec;     /* seconds after the minute - [0,59] */
		int tm_min;     /* minutes after the hour - [0,59] */
		int tm_hour;    /* hours since midnight - [0,23] */
		int tm_mday;    /* day of the month - [1,31] */
		int tm_mon;     /* months since January - [0,11] */
		int tm_year;    /* years since 1900 */
		int tm_wday;    /* days since Sunday - [0,6] */
		int tm_yday;    /* days since January 1 - [0,365] */
		int tm_isdst;   /* daylight savings time flag */
	};
#define _TM_DEFINED
#endif

	struct utimbuf {
		__time32_t actime;	/* access time */
		__time32_t modtime;	/* modification time */
	};
	#define _INC_UTIME

	_CRTIMP clock_t __cdecl clock(void);
	_CRTIMP struct tm * localtime (const time_t *time);
	_CRTIMP __time32_t mktime( struct tm *timeptr );
	_CRTIMP __time32_t time ( __time32_t * timer );
	int utime (const char *filename, const struct utimbuf *times);	// in StdLibC.c


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_TIME */
