//
// ShortEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/ShortEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  ShortEncoding
//
// Definition of the ShortEncoding class.
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


#ifndef FastInfoset_ShortEncoding_INCLUDED
#define FastInfoset_ShortEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API ShortEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for 16-bit integers.
{
public:
	explicit ShortEncoding(Poco::Int16 value);
		/// Creates the ShortEncoding using the given value.

	explicit ShortEncoding(const std::vector<Poco::Int16>& values);
		/// Creates the ShortEncoding using the given values.

	explicit ShortEncoding(const std::string& values);
		/// Creates the ShortEncoding, using the given
		/// string containing space-separated integer values.

	~ShortEncoding();
		/// Destroys the ShortEncoding.

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
	static void decode(BitStreamReader& reader, std::vector<Poco::Int16>& result);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void encode(BitStreamWriter& writer, const std::string& str);
	static void parse(const std::string& str, std::vector<Poco::Int16>& data);
		/// Parses the string for short values, single space chars are allowed between the values 
		/// but not at the end or at the beginning, every error will result in an empty data return vector.

private:
	std::vector<Poco::Int16> _data;
};


//
// inlines
//
inline Poco::UInt32 ShortEncoding::type() const
{
	return EncodingAlgorithm::SHORT_ENCODING;
}


inline Encoding::CheckMethod ShortEncoding::checkMethod() const
{
	return &ShortEncoding::check;
}


inline Encoding::EncodeMethod ShortEncoding::encodeMethod() const
{
	return &ShortEncoding::encode;
}


inline Encoding::DecodeMethod ShortEncoding::decodeMethod() const
{
	return &ShortEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_ShortEncoding_INCLUDED
