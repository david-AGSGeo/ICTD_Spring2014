//
// IntEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/IntEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  IntEncoding
//
// Definition of the IntEncoding class.
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


#ifndef FastInfoset_IntEncoding_INCLUDED
#define FastInfoset_IntEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API IntEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for 32-bit integers.
{
public:
	explicit IntEncoding(Poco::Int32 value);
		/// Creates the IntEncoding using the given value.

	explicit IntEncoding(const std::vector<Poco::Int32>& values);
		/// Creates the IntEncoding using the given values.

	explicit IntEncoding(const std::string& values);
		/// Creates the IntEncoding, using the given
		/// string containing space-separated integer values.

	~IntEncoding();
		/// Destroys the IntEncoding.

	// Encoding
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
	static void decode(BitStreamReader& reader, std::vector<Poco::Int32>& result);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void encode(BitStreamWriter& writer, const std::string& str);
	static void parse(const std::string& str, std::vector<Poco::Int32>& data);
		/// Parses the string for int values, single space chars are allowed between the values 
		/// but not at the end or at the beginning, every error will result in an empty data return vector.

private:
	std::vector<Poco::Int32> _data;
};


//
// inlines
//
inline Poco::UInt32 IntEncoding::type() const
{
	return EncodingAlgorithm::INT_ENCODING;
}


inline Encoding::CheckMethod IntEncoding::checkMethod() const
{
	return &IntEncoding::check;
}


inline Encoding::EncodeMethod IntEncoding::encodeMethod() const
{
	return &IntEncoding::encode;
}


inline Encoding::DecodeMethod IntEncoding::decodeMethod() const
{
	return &IntEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_IntEncoding_INCLUDED
