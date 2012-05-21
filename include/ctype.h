#pragma once

#ifndef _INC_CTYPE
#define _INC_CTYPE

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

extern int isalnum(int);
extern int isalpha(int);
extern int isblank(int);
extern int iscntrl(int);
extern int isdigit(int);
extern int islower(int);
extern int isgraph(int);
extern int isprint(int);
extern int ispunct(int);
extern int isspace(int);
extern int isupper(int);
extern int isxdigit(int);
extern int tolower(int);
extern int toupper(int);

extern int isascii(int);
extern int toascii(int);

#define _tolower(c) tolower(c)
#define _toupper(c) toupper(c)


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_CTYPE */
