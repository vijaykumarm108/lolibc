// winunix.cpp - Unix functions on windows
#include <stdafx.h>
#include <intrin.h>
#include <io.h>
#include <winunix.h>
#include <windows.h>

/* Initialize critical section */
void csinitialize (CRITICAL_SECTION *cs) {
    InitializeCriticalSection (cs);
}
/* Delete critical section */
void csdelete (CRITICAL_SECTION *cs) {
    DeleteCriticalSection (cs);
}
/* Enter critical section */
int csenter (CRITICAL_SECTION *cs) {
    EnterCriticalSection (cs);
    return 0;
}
/* Leave critical section */
int csleave (CRITICAL_SECTION *cs) {
    LeaveCriticalSection (cs);
    return 0;
}

static int g_cs_initialized;
static CRITICAL_SECTION g_cs;

/* Wait for spin lock */
int slwait (int *sl) {
    while (InterlockedCompareExchange ((__drv_interlocked unsigned *) sl, 1, 0) != 0) 
	Sleep (0);
    return 0;
}
/* Release spin lock */
int slrelease (int *sl) {
	::InterlockedExchange((volatile unsigned int *)sl,0);
    return 0;
}

static int g_sl;

/* getpagesize for windows */
long getpagesize (void) {
    static long g_pagesize = 0;
    if (! g_pagesize) {
        SYSTEM_INFO system_info;
        GetSystemInfo (&system_info);
        g_pagesize = system_info.dwPageSize;
    }
    return g_pagesize;
}
long getregionsize (void) {
    static long g_regionsize = 0;
    if (! g_regionsize) {
        SYSTEM_INFO system_info;
        GetSystemInfo (&system_info);
        g_regionsize = system_info.dwAllocationGranularity;
    }
    return g_regionsize;
}

/* A region list entry */
typedef struct _region_list_entry {
    void *top_allocated;
    void *top_committed;
    void *top_reserved;
    long reserve_size;
    struct _region_list_entry *previous;
} region_list_entry;

/* Allocate and link a region entry in the region list */
static int region_list_append (region_list_entry **last, void *base_reserved, long reserve_size) {
    region_list_entry *next = (region_list_entry *)HeapAlloc (GetProcessHeap (), 0, sizeof (region_list_entry));
    if (! next)
        return FALSE;
    next->top_allocated = (char *) base_reserved;
    next->top_committed = (char *) base_reserved;
    next->top_reserved = (char *) base_reserved + reserve_size;
    next->reserve_size = reserve_size;
    next->previous = *last;
    *last = next;
    return TRUE;
}
/* Free and unlink the last region entry from the region list */
static int region_list_remove (region_list_entry **last) {
    region_list_entry *previous = (*last)->previous;
    if (! HeapFree (GetProcessHeap (), sizeof (region_list_entry), *last))
        return FALSE;
    *last = previous;
    return TRUE;
}

/* mmap for windows */
void *mmap (void *ptr, long size, long prot, long type, long handle, long arg) {
    static long g_pagesize;
    static long g_regionsize;
    /* Wait for spin lock */
    slwait (&g_sl);
    /* First time initialization */
    if (! g_pagesize) 
        g_pagesize = getpagesize ();
    if (! g_regionsize) 
        g_regionsize = getregionsize ();
    /* Allocate this */
    ptr = VirtualAlloc (ptr, size, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, prot);
    if (! ptr)
	{
        ptr = MMAP_FAILURE;
        goto mmap_exit;
    }
mmap_exit:
    /* Release spin lock */
    slrelease (&g_sl);
    return ptr;
}
/* munmap for windows */
long munmap (void *ptr, long size)
{
    static long g_pagesize;
    static long g_regionsize;
    long rc = MUNMAP_FAILURE;
    /* Wait for spin lock */
    slwait (&g_sl);
    /* First time initialization */
    if (! g_pagesize) 
        g_pagesize = getpagesize ();
    if (! g_regionsize) 
        g_regionsize = getregionsize ();
    /* Free this */
    if (! VirtualFree (ptr, 0, 
                       MEM_RELEASE))
        goto munmap_exit;
    rc = 0;
munmap_exit:
    /* Release spin lock */
    slrelease (&g_sl);
    return rc;
}

int msync ( void *data, long size, long flags )
{
	return FlushViewOfFile( data, size ) != FALSE ? 0 : -1;
}

int fsync( int fd )
{
	if (fd > 2 )
	{
		return _commit(fd);
	}
	return 0;
}

int ioctl(int fildes, int request, ... /* arg */)
{
	return 0;
}
