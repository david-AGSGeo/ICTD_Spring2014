//
// BitStreamReader.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/BitStreamReader.h#3 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  BitStreamReader
//
// Definition of the BitStreamReader class.
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


#ifndef FastInfoset_BitStreamReader_INCLUDED
#define FastInfoset_BitStreamReader_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Utility.h"
#include <istream>
#include <cstdlib>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API BitStreamReader
	/// A BitStreamReader reads single bits from the input stream. 
	/// Single bits are read in highest bits first order, i.e. if 8 
	/// bits are read, the first bit is read from bit position 7 and 
	/// the last one from bit position 0. If data types larger than 
	/// a byte are read, they are deserialized as big endian numbers,
	/// i.e. byte n-1, then n-2,... 1, 0.
	/// String types are read starting with the first character.
{
public:
	BitStreamReader(std::istream& inStream);
		/// Creates the BitStreamReader. Bits are read from inStream.

	BitStreamReader(const char* pBuffer, std::size_t size);
		/// Creates the BitStreamReader. Bits are read from the given buffer.

	~BitStreamReader();
		/// Destroys the BitStreamReader.

	void skip(int n);
		/// Skips over n bits.

	void skipToByteStart();
		/// Skips until we are at the beginning of a byte, i.e. bitPos() == 0.

	bool peek(char& value, int numBits);
		/// Peek ahead the number of bits which the next read would return.

	bool peek(Poco::UInt8& value, int numBits);
		/// Peek ahead the number of bits which the next read would return.

	bool read(bool& value);
		/// Reads one single bit from the stream.

	bool read(char& value, int numBits);
		/// Reads numBits from the stream and puts them as the first bits of value.
		///
		/// Example: Reading the 4 bits 1111b(15d), will result in value = 15.

	bool read(std::string& str, std::size_t numCharacters);
		/// Clears str and reads the number of defined characters from the stream into str.

	bool read(Poco::UInt8& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool read(Poco::UInt16& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool read(Poco::UInt32& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool read(Poco::UInt64& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool read(Poco::Int8& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool read(Poco::Int16& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool read(Poco::Int32& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool read(Poco::Int64& value, int numBits);
		/// Reads numBits from the stream and sets them as the lowest numBits bits of value.

	bool eof() const;
		/// Returns true if End-Of-File was encountered.

	int bitPos() const;
		/// Returns the bit position in relation to the current byte.
		/// I.e., numBitsRead % 8

private:
	enum 
	{
		BUFFER_SIZE = 1024
	};

	const unsigned char& curByte();
		/// Returns the current byte.

	void refillBufferIfLessThan(int bits);
		/// Conditional refill.

	void refillBufferIfLessThanImpl(int unreadBits);
		/// Conditional refill implementation.

	void refillBuffer();
		/// Fills the buffer until eof or the buffer is full. 
		/// Erases old content, resets _bitOffset to 0 and _cachedBits to BitStreamReader::BUFFERSIZE*8.

	bool checkInputParams(int size, int& numOfBits) const;
		/// Helper method to check if the input for the read methods is valid, e.g. when reading a character numOfBits must be in the range 1..8.

	int cachedBits() const;
		/// Returns the number of unread bits in the cache.

	std::streamsize readFromStream(char* pBuffer, std::streamsize length);
		/// Reads data from the stream and checks the stream state.
		///
		/// Returns the number of bytes read.
		///
		/// Throws a Poco::IOException if reading fails.

private:
	std::istream*  _pStream;
	bool           _flipBytes;
	std::size_t    _cachedBits;
	int            _bitOffset;
	unsigned char* _buf;
};


//
// inlines
//
inline void BitStreamReader::skip(int bits)
{
	int bitsToRead = bits - cachedBits();

	if (bitsToRead >= 0)
	{
		// want to skip more than we have in Buffer, refill the buffer
		refillBuffer();
		_bitOffset = bitsToRead;
	}
	else
	{
		// we have less data to skip than we have cached, this will be the common case
		_bitOffset += bits;
	}
}


inline void BitStreamReader::skipToByteStart()
{
	int modVal = _bitOffset % Utility::SIZEOFCHARINBIT;
	if (modVal != 0)
		_bitOffset += (Utility::SIZEOFCHARINBIT-modVal);

	poco_assert_dbg (cachedBits() >= 0);
	poco_assert_dbg (_bitOffset % Utility::SIZEOFCHARINBIT == 0);
}


inline bool BitStreamReader::peek(char& value, int numBits)
{
	return peek((Poco::UInt8&)value, numBits);
}


inline bool BitStreamReader::read(Poco::UInt8& value, int numBits)
{
	bool ret = peek(value, numBits);
	_bitOffset += numBits;
	return ret;
}


inline bool BitStreamReader::read(char& value, int numBits)
{
	return read((Poco::UInt8&)value, numBits);
}


inline bool BitStreamReader::read(Poco::Int8& value, int numBits)
{
	return read((Poco::UInt8&)value, numBits);
}


inline bool BitStreamReader::read(Poco::Int16& value, int numBits)
{
	return read((Poco::UInt16&)value, numBits);
}


inline bool BitStreamReader::read(Poco::Int32& value, int numBits)
{
	return read((Poco::UInt32&)value, numBits);
}


inline bool BitStreamReader::read(Poco::Int64& value, int numBits)
{
	return read((Poco::UInt64&)value, numBits);
}


inline bool BitStreamReader::eof() const
{
	return _cachedBits == 0 && (!_pStream || _pStream->eof());
}


inline bool BitStreamReader::checkInputParams(int size, int& numOfBits) const
{
	return numOfBits > 0 && numOfBits <= size;
}


inline int BitStreamReader::bitPos() const
{
	return _bitOffset % Utility::SIZEOFCHARINBIT; 
}


inline int BitStreamReader::cachedBits() const
{
	return static_cast<int>(_cachedBits - _bitOffset);
}


inline const unsigned char& BitStreamReader::curByte()
{
	return _buf[_bitOffset/Utility::SIZEOFCHARINBIT];
}


inline void BitStreamReader::refillBufferIfLessThan(int bits)
{
	int unreadBits = cachedBits();
	if (unreadBits < bits)
		refillBufferIfLessThanImpl(unreadBits);
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_BitStreamReader_INCLUDED
