#pragma once

#ifndef _INC_UNISTD
#define _INC_UNISTD

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

	int chdir(const char *path);					// In stdlibc.c
	char * getcwd( char * path, int lengthOfPath );	// In stdlibc.c
	int mkdir (const char *filename, mode_t mode);	// In stdlibc.c

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_UNISTD */
