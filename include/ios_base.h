/*
 * Copyright © 2012, MuThink Inc, All rights reserved.
 * http://www.muthink.com
 * Copying and distribution of this product is forbidden without direct permission from MuThink Inc.
 */
#pragma once

#include "lostlbase.h"

namespace std {

/// Defines types and constants used by all stream classes.
class ios_base {
public:
    /// Used to set parameters for stringstreams
    enum fmtflags {
		boolalpha	= (1 << 0),	///< Boolean values printed as text.
		dec			= (1 << 1),	///< Decimal number output.
		fixed		= (1 << 2),	///< Fixed-point float output.
		hex			= (1 << 3),	///< Hexadecimal number output.
		internal	= (1 << 4),
		left		= (1 << 5),	///< Left alignment.
		oct			= (1 << 6),	///< Octal number output.
		right		= (1 << 7),	///< Right alignment.
		scientific	= (1 << 8),	///< Scientific float format.
		showbase	= (1 << 9),	///< Add 0x or 0 prefixes on hex and octal numbers.
		showpoint	= (1 << 10),///< Print decimal point.
		showpos		= (1 << 11),
		skipws		= (1 << 12),///< Skip whitespace when reading.
		unitbuf		= (1 << 13),
		uppercase	= (1 << 14),
		adjustfield	= (1 << 15),
		basefield	= (1 << 16),
		floatfield	= (1 << 17)
    };
    /// For file-based streams, specifies fd mode.
    enum openmode_bits {
		in	= (1 << 0),
		out	= (1 << 1),
		app	= (1 << 2),
		ate	= (1 << 3),
		binary	= (1 << 4),
		trunc	= (1 << 5),
		nonblock= (1 << 6),
		nocreate= (1 << 7),
		noctty	= (1 << 8),
		nombits	= 9
    };
    /// Seek directions, equivalent to SEEK_SET, SEEK_CUR, and SEEK_END.
    enum seekdir { beg,	cur, end };
    /// I/O state bitmasks.
    enum iostate_bits {
		goodbit	= 0,
		badbit	= (1 << 0),
		eofbit	= (1 << 1),
		failbit	= (1 << 2),
		nbadbits = 3,
		allbadbits = 0x7
    };

    typedef uint32_t		openmode;	///< Holds openmode_bits.
    typedef uint32_t		iostate;	///< Holds iostate_bits for a file stream.
    //typedef file_exception	failure;	///< Thrown by fstream on errors.

    static const char c_DefaultDelimiters [16];	///< Default word delimiters for stringstreams.
public:
    inline ios_base (void) : m_State (goodbit), m_Exceptions (allbadbits) {}
    inline iostate	rdstate (void) const		{ return (m_State); }
    inline bool		bad (void) const			{ return (rdstate() & badbit); }
    inline void		clear (iostate v = goodbit)	{ m_State = v; }
    inline bool		eof (void) const			{ return (rdstate() & eofbit) != 0; }
    inline iostate	exceptions (void) const		{ return (m_Exceptions); }
    inline iostate	exceptions (iostate v)		{ return (m_Exceptions = v); }
    inline bool		fail (void) const			{ return (rdstate() & (badbit | failbit)) != 0; }
    inline bool		good (void) const			{ return (rdstate() == goodbit); }
    inline bool		operator! (void) const		{ return (fail()); }
    inline			operator void* (void) const	{ return ((void*)(!fail())); }
    inline void		setstate (iostate v)		{ m_State |= v; }
protected:
    inline bool		set_and_throw (iostate v)	{ setstate(v); return (exceptions() & v) != 0; }
    void			overrun (const char* op, const char* type, uint32_t n, uint32_t p, uint32_t rem);
private:
    uint16_t		m_State;	///< Open state, using ios::iostate_bits.
    uint16_t		m_Exceptions;	///< Exception flags, using ios::iostate_bits.
};

} // namespace std
