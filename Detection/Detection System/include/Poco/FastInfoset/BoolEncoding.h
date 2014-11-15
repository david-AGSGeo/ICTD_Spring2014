//
// BoolEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/BoolEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  BoolEncoding
//
// Definition of the BoolEncoding class.
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


#ifndef FastInfoset_BoolEncoding_INCLUDED
#define FastInfoset_BoolEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"
#include <vector>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API BoolEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for boolean.
{
public:
	explicit BoolEncoding(bool value);
		/// Creates the BoolEncoding, using the given value.

	explicit BoolEncoding(const std::vector<bool>& values);
		/// Creates the BoolEncoding, using the given values.

	explicit BoolEncoding(const std::string& values);
		/// Creates the BoolEncoding, using the given
		/// string containing space-separated boolean values.

	~BoolEncoding();
		/// Destroys the BoolEncoding.

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
	static Poco::Int32 check(const std::string& str);
	static void decode(BitStreamReader& reader, std::string& result);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static void encode(BitStreamWriter& writer, const std::string& str);
	static void parse(const std::string& str, std::vector<bool>& data);
		/// Parses the string for the values "true and "false", single space chars are allowed between the values 
		/// but not at the end or at the beginning, every error will result in an empty data return vector.

	static const std::string VAL_TRUE;
	static const std::string VAL_FALSE;
	
private:
	std::vector<bool> _data;
};


//
// inlines
//
inline Poco::UInt32 BoolEncoding::type() const
{
	return EncodingAlgorithm::BOOL_ENCODING;
}


inline Encoding::CheckMethod BoolEncoding::checkMethod() const
{
	return &BoolEncoding::check;
}


inline Encoding::EncodeMethod BoolEncoding::encodeMethod() const
{
	return &BoolEncoding::encode;
}


inline Encoding::DecodeMethod BoolEncoding::decodeMethod() const
{
	return &BoolEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_BoolEncoding_INCLUDED
