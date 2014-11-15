//
// BitStreamWriter.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/BitStreamWriter.h#3 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  BitStreamWriter
//
// Definition of the BitStreamWriter class.
//
// Copyright (c) 2006-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics
// Software Engineering GmbH.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part, without
// prior written permission from Applied Informatics.
//


#ifndef FastInfoset_BitStreamWriter_INCLUDED
#define FastInfoset_BitStreamWriter_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Utility.h"
#include <ostream>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API BitStreamWriter
	/// A BitStreamWriter writes single bits to the encapsulated 
	/// output stream. Single bits are written in highest bits first order, 
	/// i.e. if 8 bits are written, the first bit is written to bit position 
	/// 7 and the last one to bit position 0. If data types larger than a 
	/// byte are written, they are serialized as big endian numbers,
	/// i.e. byte n-1, then n-2,... 1, 0.
	/// String types are written starting with the first character.
{
public:
	BitStreamWriter(std::ostream& outStream, bool paddingBit);
		/// Creates the BitStreamWriter. Writes bits to the given outStream, serializes data always 
		/// in Big endian byte order, and, when closing the stream, fills up incomplete bytes 
		/// with the defined padding bit value.

	virtual ~BitStreamWriter();
		/// Destroys the BitStreamWriter.

	void write(bool value);
		/// Writes a single bit to the outputstream (1 if value is true, false otherwise).

	void writeBits(int cnt, bool value = false);
		/// Write cnt padding bits (value false corresponds to 0, true to 1).

	void write(const std::string& str);
		/// Writes the full string without '\0'.

	void write(const char* pStr);
		/// Writes the full string without '\0'. 

	void write(const char* pStr, std::size_t numBytes);
		/// Writes numBytes from pStr.

	void write(char value, int numOfBits = Utility::SIZEOFCHARINBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::Int8 value, int numOfBits = Utility::SIZEOFCHARINBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::Int16 value, int numOfBits = Utility::SIZEOFINT16INBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::Int32 value, int numOfBits = Utility::SIZEOFINT32INBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::Int64 value, int numOfBits = Utility::SIZEOFINT64INBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::UInt8 value, int numOfBits = Utility::SIZEOFCHARINBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::UInt16 value, int numOfBits = Utility::SIZEOFINT16INBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::UInt32 value, int numOfBits = Utility::SIZEOFINT32INBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void write(Poco::UInt64 value, int numOfBits = Utility::SIZEOFINT64INBIT);
		/// Writes from the value the first numOfBits.
		/// Invalid parameters for numOfBits will result in an exception.

	void flush();
		/// Writes all full bytes to the underlying output stream which is then flushed.

	void complete();
		/// Fills up any incomplete byte with the default padding bits.

	void complete(bool padBit);
		/// Fills up any incomplete byte with the specified padBit.

	int bitPos() const;
		/// Returns the bit position in relation to the current byte.
		/// I.e., numBitsWritten % 8

private:
	bool checkInputParams(int size, int& numOfBits);
		/// Helper method to check if the input for the write methods is valid, e.g. when writing a character numOfBits must be in the range 1..8

	char& curByte();
		/// Returns the current byte we write to from the internal buffer.

	int curBitOffsetInByte();
		/// Returns the bit offset from the current byte.

	void writeFullBytes();
		/// Writes all full bytes to the underlying output stream.

	void writeFullBytesImpl();
		/// Conditional write: writes only full bytes. Does not add padding bits.
		
	void writeToStream(const char* buffer, std::streamsize length);
		/// Writes to the output stream.
		///
		/// Throws a Poco::IOException if writing fails.

private:
	std::ostream&  _outStream;
	bool           _flipBytes;
	bool           _paddingBit;
	std::size_t    _cachedBits; /// The number of cached bits in _buf. Guaranteed to be lower than 8 at the begin of a write.
	char           _buf[10];    /// Temporary buffer (10 = sizeof(UInt64)+ max 7 cached bits+1 endofstring terminator when working with stringstreams).
};


//
// inlines
//
inline void BitStreamWriter::write(char value, int numOfBits)
{
	write((Poco::Int8)value, numOfBits);
}


inline void BitStreamWriter::write(Poco::UInt8 value, int numOfBits)
{
	write((Poco::Int8)value, numOfBits);
}


inline void BitStreamWriter::write(Poco::UInt16 value, int numOfBits)
{
	write((Poco::Int16)value, numOfBits);
}


inline void BitStreamWriter::write(Poco::UInt32 value, int numOfBits)
{
	write((Poco::Int32)value, numOfBits);
}


inline void BitStreamWriter::write(Poco::UInt64 value, int numOfBits)
{
	write((Poco::Int64)value, numOfBits);
}


inline void BitStreamWriter::writeFullBytes()
{
	if (_cachedBits >= Utility::SIZEOFCHARINBIT)
		writeFullBytesImpl();
}


inline void BitStreamWriter::flush()
{
	writeFullBytes();
	_outStream.flush();
}


inline bool BitStreamWriter::checkInputParams(int size, int& numOfBits)
{
	return numOfBits > 0 && numOfBits <= size;
}


inline char& BitStreamWriter::curByte()
{
	return _buf[_cachedBits/Utility::SIZEOFCHARINBIT];
}


inline int BitStreamWriter::curBitOffsetInByte()
{
	return (Utility::SIZEOFCHARINBIT - 1) - (_cachedBits % Utility::SIZEOFCHARINBIT);
}


inline int BitStreamWriter::bitPos() const
{
	return _cachedBits % Utility::SIZEOFCHARINBIT;
}


inline void BitStreamWriter::complete()
{
	complete(_paddingBit);
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_BitStreamWriter_INCLUDED
