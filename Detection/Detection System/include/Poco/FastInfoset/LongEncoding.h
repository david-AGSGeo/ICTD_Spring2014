//
// LongEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/LongEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  LongEncoding
//
// Definition of the LongEncoding class.
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


#ifndef FastInfoset_LongEncoding_INCLUDED
#define FastInfoset_LongEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API LongEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for 64-bit long integers.
{
public:
	explicit LongEncoding(Poco::Int64 value);
		/// Creates the LongEncoding.

	explicit LongEncoding(const std::vector<Poco::Int64>& values);
		/// Creates the LongEncoding.

	explicit LongEncoding(const std::string& values);
		/// Creates the LongEncoding, using the given
		/// string containing space-separated integer values.

	// Encoding
	~LongEncoding();
	Poco::UInt32 type() const;
	bool merge(const Encoding& enc);
	void write(BitStreamWriter& writer) const;
	Encoding::CheckMethod checkMethod() const;
	Encoding::EncodeMethod encodeMethod() const;
	Encoding::DecodeMethod decodeMethod() const;
	void handle(FISContentHandler* pHandler) const;
	void createContent();

	// Implementation
	static void decode(BitStreamReader& reader, std::string& result);
	static void decode(BitStreamReader& reader, std::vector<Poco::Int64>& result);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void encode(BitStreamWriter& writer, const std::string& str);
	static void parse(const std::string& str, std::vector<Poco::Int64>& data);
		/// Parses the string for Int64 values, single space chars are allowed between the values 
		/// but not at the end or at the beginning, every error will result in an empty data return vector.

private:
	std::vector<Poco::Int64> _data;
};


//
// inlines
//
inline Poco::UInt32 LongEncoding::type() const
{
	return EncodingAlgorithm::LONG_ENCODING;
}


inline Encoding::CheckMethod LongEncoding::checkMethod() const
{
	return &LongEncoding::check;
}


inline Encoding::EncodeMethod LongEncoding::encodeMethod() const
{
	return &LongEncoding::encode;
}


inline Encoding::DecodeMethod LongEncoding::decodeMethod() const
{
	return &LongEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_LongEncoding_INCLUDED
