// a bunch of non-standard Windows calls that we used to support and might have to again...

#include "stdio.h"
#if 0



struct _wfinddata64_t {
	unsigned    attrib;
	__time64_t  time_create;    /* -1 for FAT file systems */
	__time64_t  time_access;    /* -1 for FAT file systems */
	__time64_t  time_write;
	__int64     size;
	wchar_t     name[260];
};

_CRTIMP int _wfindnexti64( intptr_t handle, struct _wfinddata64_t *fileinfo );

int _wfindnext64i32( intptr_t handle, struct _wfinddata64i32_t *fileinfo )
{
	struct _wfinddata64_t	f;
	int retval = _wfindnexti64( handle, &f );
	fileinfo->attrib = f.attrib;
	fileinfo->size = (_fsize_t)f.size;
	fileinfo->time_access = f.time_access;
	fileinfo->time_create = f.time_create;
	fileinfo->time_write = f.time_write;
	wcsncpy( fileinfo->name, f.name, MAX_PATH );
	return retval;
}

intptr_t _wfindfirst64i32( const wchar_t *filespec, struct _wfinddata64i32_t *fileinfo )
{
	struct _wfinddata64_t	f;
	intptr_t retval = _wfindfirsti64( filespec, &f );
	if(retval != -1)
	{
		fileinfo->attrib = f.attrib;
		fileinfo->size = (_fsize_t)f.size;
		fileinfo->time_access = f.time_access;
		fileinfo->time_create = f.time_create;
		fileinfo->time_write = f.time_write;
		wcsncpy( fileinfo->name, f.name, MAX_PATH );
	}
	return retval;
}

int _fstat64i32( int fd, struct _stat64i32 *buffer )
{
	struct _stat64 s;
	int retval = _fstati64( fd, &s );
	if(!retval )
	{
		buffer->st_atime = s.st_atime;
		buffer->st_ctime = s.st_ctime;
		buffer->st_dev = s.st_dev;
		buffer->st_gid = s.st_gid;
		buffer->st_ino = s.st_ino;
		buffer->st_mode = s.st_mode;
		buffer->st_mtime = s.st_mtime;
		buffer->st_nlink = s.st_nlink;
		buffer->st_rdev = s.st_rdev;
		buffer->st_size = (_off_t)s.st_size;
		buffer->st_uid = s.st_uid;
	}
	return retval;
}


#endif