#pragma once

#ifndef _INC_UNISTD
#define _INC_UNISTD

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define F_OK	0
#define R_OK	4
#define W_OK	2
#define RW_OK	6

	int access (const char *filename, int how);		// In stdlibc.c
	int chdir(const char *path);					// In stdlibc.c
	char * getcwd( char * path, int lengthOfPath );	// In stdlibc.c
	int mkdir (const char *filename, mode_t mode);	// In stdlibc.c
	int rmdir(const char * path);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _INC_UNISTD */
