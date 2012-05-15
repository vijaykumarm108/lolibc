

#define MUNMAP_FAILURE -1
#define MAP_FAILED nullptr
#define MMAP_FAILURE nullptr
#define PROT_READ	0
#define PROT_WRITE	PAGE_READWRITE
#define MAP_SHARED	0
void *mmap (void *ptr, long size, long prot, long type, long handle, long arg);
long munmap (void *ptr, long size);

#define MS_INVALIDATE	0
#define MS_ASYNC		0
int msync ( void *data, long size, long flags );

#define O_ACCMODE	(O_RDONLY|O_WRONLY)
#define O_NONBLOCK	(0)

int fsync( int fd );

int ioctl(int fildes, int request, ... /* arg */);

#define F_GETFL	0x08
#define F_SETFL 0x10
typedef size_t size_type;
