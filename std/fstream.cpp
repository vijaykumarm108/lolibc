// Lo-Overhead STL library - Lostl
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "sys\types.h"
#include "errno.h"
#include "sys\stat.h"
#include "fstream"
#include "exception"
#include "xutility"
#include "winunix.h"

using namespace lo;

namespace std {

	/// Default fstream constructor
	fstream::fstream (void) : ios_base (), m_fd (-1), m_Filename ()
	{
		exceptions (goodbit);
	}

	/// Opens \p filename in \p mode.
	fstream::fstream (const char* filename, openmode mode) : ios_base (), m_fd (-1), m_Filename ()
	{
		exceptions (goodbit);
		fstream::open (filename, mode);
	}

	/// Attaches to \p nfd of \p filename.
	fstream::fstream (int nfd, const char* filename) : ios_base (), m_fd (-1), m_Filename ()
	{
		exceptions (goodbit);
		attach (nfd, filename);
	}

	/// Destructor. Closes if still open, without throwing.
	fstream::~fstream (void) throw()
	{
		clear (goodbit);
		exceptions (goodbit);
		close();
		assert (!(rdstate() & badbit) && "close failed in fstream destructor.");
	}

	/// Sets state \p s and throws depending on the exception setting.
	void fstream::set_and_throw (iostate s, const char* op)
	{
		if (ios_base::set_and_throw (s))
			throw file_exception (op, name());
	}

	/// Attaches to the given \p nfd.
	void fstream::attach (int nfd, const char* filename)
	{
		assert (filename && "filename set to nullptr");
		m_Filename = filename;
		clear (goodbit);
		if (nfd < 0)
			set_and_throw (badbit, "open");
		close();
		m_fd = nfd;
	}

	/// Detaches from the current fd.
	void fstream::detach (void)
	{
		m_fd = -1;
		m_Filename.clear();
	}

	/// Converts openmode bits into libc open flags.
	/*static*/ int fstream::om_to_flags (openmode m)
	{
		static const int s_OMFlags [nombits] = {
			0,			// in
			O_CREAT,	// out
			O_APPEND,	// app
			O_APPEND,	// ate
			0,			// binary
			O_TRUNC,	// trunc
			0 /*O_NONBLOCK*/,	// nonblock
			0,		// nocreate
			0 /*O_NOCTTY*/	// noctty
		};
		int flags = (m - 1) & O_ACCMODE;	// in and out
		for (uoff_t i = 0; i < _countof(s_OMFlags); ++ i)
			flags |= s_OMFlags[i] & (!(m & (1 << i)) - 1);
		if (m & nocreate)
			flags &= ~O_CREAT;
		return (flags);
	}

	/// \brief Opens \p filename in the given mode.
	/// \warning The string at \p filename must exist until the object is closed.
	void fstream::open (const char* filename, openmode mode, mode_t perms)
	{
		int nfd = ::open (filename, om_to_flags(mode), perms);
		attach (nfd, filename);
	}

	/// Closes the file and throws on error.
	void fstream::close (void)
	{
		if (m_fd < 0)
			return;	// already closed
		while (::close(m_fd))
		{
			if (errno != EINTR)
			{
				set_and_throw (badbit | failbit, "close");
				break;
			}
		}
		detach();
	}

	/// Moves the current file position to \p offset.
	off_t fstream::seek (off_t offset, seekdir whence)
	{
		off_t returns = lseek (m_fd, offset, whence);
		if (returns < 0)
			set_and_throw (failbit, "seek");
		return (returns);
	}

	/// Returns the current file position.
	off_t fstream::pos (void) const
	{
		return (lseek (m_fd, 0, SEEK_CUR));
	}

	/// Reads \p maximumBytes bytes into \p buffer.
	off_t fstream::read (void* buffer, off_t maximumBytes)
	{
		off_t returns (0);
		while ((returns < maximumBytes) & good())
			returns += readsome (advance (buffer, returns), maximumBytes - returns);
		return (returns);
	}

	/// Reads at most \p maximumBytes bytes into \p buffer, stopping when full or can read no further.
	off_t fstream::readsome (void* buffer, off_t maximumBytes)
	{
		ssize_t brn;
		do {
			brn = ::read (m_fd, buffer, maximumBytes);
		} while ((brn < 0) & (errno == EINTR));
		if (brn > 0)
			return (brn);
		else if ((brn < 0) & (errno != EAGAIN))
			set_and_throw (failbit, "read");
		else if (!brn && ios_base::set_and_throw (eofbit | failbit))
			throw stream_bounds_exception ("read", name(), pos(), maximumBytes, 0);
		return (0);
	}

	/// Writes \p n bytes from buffer \p p.
	off_t fstream::write (const void* p, off_t n)
	{
		off_t btw (n);
		while (btw) {
			const off_t bw (n - btw);
			ssize_t bwn = ::write (m_fd, advance(p,bw), btw);
			if (bwn > 0)
				btw -= bwn;
			else if (!bwn) {
				if (ios_base::set_and_throw (eofbit | failbit))
					throw stream_bounds_exception ("write", name(), pos() - bw, n, bw);
				break;
			} else if (errno != EINTR) {
				if (errno != EAGAIN)
					set_and_throw (failbit, "write");
				break;
			}
		}
		return (n - btw);
	}

	/// Returns the file size of the stream.
	off_t fstream::size (void) const
	{
		struct stat st;
		st.st_size = 0;
		stat (st);
		return (st.st_size);
	}

	/// Synchronizes the file's data and status with the disk.
	void fstream::sync (void)
	{
		if (::fsync (m_fd))
		{
			set_and_throw (badbit | failbit, "sync");
		}
	}

	/// Get the stat structure.
	void fstream::stat (struct stat& rs) const
	{
		if (fstat (m_fd, &rs))
			throw file_exception ("stat", name());
	}

	/// Calls the given ioctl. Use IOCTLID macro to pass in both \p name and \p request.
	int fstream::ioctl (const char* rname, int request, long argument)
	{
		int rv = ::ioctl (m_fd, request, argument);
		if (rv < 0)
			set_and_throw (failbit, rname);
		return (rv);
	}

	/// Calls the given fcntl. Use FCNTLID macro to pass in both \p name and \p request.
	int fstream::fcntl (const char* rname, int request, long argument)
	{
	#ifdef UNIX
		int rv = _fcntl (m_fd, request, argument);
		if (rv < 0)
			set_and_throw (failbit, rname);
		return (rv);
	#endif
		return 0;
	}

	/// Memory-maps the file and returns a link to it.
	blocklink fstream::mmap (off_t n, off_t offset)
	{
		void* result = ::mmap (NULL, n, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, offset);
		if (result == MAP_FAILED)
			set_and_throw (failbit, "mmap");
		return (blocklink (result, n));
	}

	/// Unmaps a memory-mapped area.
	void fstream::munmap (blocklink& block)
	{
		if (::munmap (block.data(), (long)block.size()))
			set_and_throw (failbit, "munmap");
		block.unlink();
	}

	/// Synchronizes a memory-mapped area.
	void fstream::msync (blocklink& block)
	{
		if (::msync (block.data(), (long)block.size(), MS_ASYNC | MS_INVALIDATE))
		{
			set_and_throw (failbit, "msync");
		}
	}

	/// Set the stream to non-blocking
	void fstream::set_nonblock (bool isNonBlocking)
	{
		int curf = maxV (0, fcntl (FCNTLID (F_GETFL)));
		if (isNonBlocking)
			curf |=  O_NONBLOCK;
		else
			curf &= ~O_NONBLOCK;
		fcntl (FCNTLID (F_SETFL), curf);
	}

} // namespace std
