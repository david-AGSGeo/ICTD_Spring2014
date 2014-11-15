//
// FloatEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/FloatEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  FloatEncoding
//
// Definition of the FloatEncoding class.
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


#ifndef FastInfoset_FloatEncoding_INCLUDED
#define FastInfoset_FloatEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API FloatEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for float.
{
public:
	explicit FloatEncoding(float value);
		/// Creates the FloatEncoding using the given value.

	explicit FloatEncoding(const std::vector<float>& values);
		/// Creates the FloatEncoding using the given values.

	explicit FloatEncoding(const std::string& values);
		/// Creates the FloatEncoding, using the given
		/// string containing space-separated float values.

	~FloatEncoding();
		/// Destroys the FloatEncoding.

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
	static void decode(BitStreamReader& reader, std::vector<float>& result);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void encode(BitStreamWriter& writer, const std::string& str);
	static void parse(const std::string& str, std::vector<float>& data);
		/// Parses the string for float values, single space chars are allowed between the values 
		/// but not at the end or at the beginning, every error will result in an empty data return vector.

private:
	std::vector<float> _data;
};


//
// inlines
//
inline Poco::UInt32 FloatEncoding::type() const
{
	return EncodingAlgorithm::FLOAT_ENCODING;
}


inline Encoding::CheckMethod FloatEncoding::checkMethod() const
{
	return &FloatEncoding::check;
}


inline Encoding::EncodeMethod FloatEncoding::encodeMethod() const
{
	return &FloatEncoding::encode;
}


inline Encoding::DecodeMethod FloatEncoding::decodeMethod() const
{
	return &FloatEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_FloatEncoding_INCLUDED
