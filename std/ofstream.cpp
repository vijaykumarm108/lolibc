#include <stdafx.h>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
//#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>

namespace std {

	//----------------------------------------------------------------------

	ifstream cin  (STDIN_FILENO);
	ofstream cout (STDOUT_FILENO);
	ofstream cerr (STDERR_FILENO);

	//----------------------------------------------------------------------

	/// Default constructor.
	ofstream::ofstream (void) : ostringstream (), m_File ()
	{
		reserve (255);
	}

	/// Constructs a stream for writing to \p Fd.
	ofstream::ofstream (int Fd) : ostringstream (),  m_File (Fd)
	{
		clear (m_File.rdstate());
		reserve (255);
	}

	/// Constructs a stream for writing to \p filename.
	ofstream::ofstream (const char* filename, openmode mode) : ostringstream (), m_File (filename, mode)
	{
		clear (m_File.rdstate());
	}

	/// Default destructor.
	ofstream::~ofstream (void) throw()
	{
		try { flush(); } catch (...) {}
	}

	/// Flushes the buffer and closes the file.
	void ofstream::close (void)
	{
		clear (m_File.rdstate());
		flush();
		m_File.close();
	}

	/// Flushes the buffer to the file.
	ofstream& ofstream::flush (void)
	{
		clear();
		while (good() && pos() && overflow (remaining())) ;
		m_File.sync();
		clear (m_File.rdstate());
		return (*this);
	}

	/// Seeks to \p p based on \p d.
	ofstream& ofstream::seekp (off_t p, seekdir d)
	{
		flush();
		m_File.seekp (p, d);
		clear (m_File.rdstate());
		return (*this);
	}

	/// Called when more buffer space (\p n bytes) is needed.
	ofstream::size_type ofstream::overflow (size_type n)
	{
		if (eof() || (n > remaining() && n < capacity() - pos()))
			return (ostringstream::overflow (n));
		size_type bw = (size_type)m_File.write (cdata(), (off_t)pos());
		clear (m_File.rdstate());
		erase (begin(), bw);
		if (remaining() < n)
			ostringstream::overflow (n);
		return (remaining());
	}

//----------------------------------------------------------------------

	/// Constructs a stream to read from \p Fd.
	ifstream::ifstream (int Fd) : istringstream (), m_Buffer (255), m_File (Fd)
	{
		link (m_Buffer.data(), streamsize(0));
	}

	/// Constructs a stream to read from \p filename.
	ifstream::ifstream (const char* filename, openmode mode) : istringstream (), m_Buffer (255), m_File (filename, mode)
	{
		clear (m_File.rdstate());
		link (m_Buffer.data(), streamsize(0));
	}

	/// Reads at least \p n more bytes and returns available bytes.
	ifstream::size_type ifstream::underflow (size_type n)
	{
		if (eof())
			return (istringstream::underflow (n));

		const ssize_t freeSpace = (ssize_t)(m_Buffer.size() - pos());
		const ssize_t neededFreeSpace = (ssize_t)maxV (n, m_Buffer.size() / 2);
		const size_t oughtToErase = lo::Align (maxV (0, neededFreeSpace - freeSpace));
		const size_type nToErase = minV (pos(), oughtToErase);
		m_Buffer.blocklink::erase (m_Buffer.begin(), nToErase);
		const uoff_t oldPos (pos() - nToErase);

		size_type br = oldPos;
		if (m_Buffer.size() - br < n) {
			m_Buffer.resize (br + neededFreeSpace);
			link (m_Buffer.data(), streamsize(0));
		}
		cout.flush();

		size_type brn = 1;
		for (; br < oldPos + n && brn && m_File.good(); br += brn)
			brn = m_File.readsome (m_Buffer.begin() + br, (off_t)(m_Buffer.size() - br));
		clear (m_File.rdstate());

		((char*)m_Buffer)[br] = 0;
		link (m_Buffer.data(), br);
		seek (oldPos);
		return (remaining());
	}

	/// Flushes the input.
	int ifstream::sync (void)
	{
		istringstream::sync();
		underflow (0U);
		m_File.sync();
		clear (m_File.rdstate());
		return ((good()?-1:0));
	}

	/// Seeks to \p p based on \p d.
	ifstream& ifstream::seekg (off_t p, seekdir d)
	{
		m_Buffer.clear();
		link (m_Buffer);
		m_File.seekg (p, d);
		clear (m_File.rdstate());
		return (*this);
	}

//----------------------------------------------------------------------

}  // namespace std
