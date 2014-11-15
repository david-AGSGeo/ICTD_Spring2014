//
// HexEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/HexEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  HexEncoding
//
// Definition of the HexEncoding class.
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


#ifndef FastInfoset_HexEncoding_INCLUDED
#define FastInfoset_HexEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API HexEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for hex-based binary data.
{
public:
	explicit HexEncoding(const std::string& data);
		/// Creates the HexEncoding using the given string containing hex-encoded data.

	HexEncoding(const char* data, std::size_t length);
		/// Creates the HexEncoding, usign the given raw binary data.

	~HexEncoding();
		/// Destroys the HexEncoding.

	// Encoding
	Poco::UInt32 type() const;
	bool merge(const Encoding& enc);
	void write(BitStreamWriter& writer) const;
	Encoding::CheckMethod checkMethod() const;
	Encoding::EncodeMethod encodeMethod() const;
	Encoding::DecodeMethod decodeMethod() const;
	void handle(FISContentHandler* pHandler) const;
	void handle(Poco::XML::ContentHandler* pHandler) const;
	void createContent();

	// Implementation
	static void decode(BitStreamReader& reader, std::string& result);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void encode(BitStreamWriter& writer, const std::string& str);

private:
	HexEncoding();
	static void decode(const std::string& binaryData, std::string& hexData);
};


//
// inlines
//
inline Poco::UInt32 HexEncoding::type() const
{
	return EncodingAlgorithm::HEX_ENCODING;
}


inline Encoding::CheckMethod HexEncoding::checkMethod() const
{
	return &HexEncoding::check;
}


inline Encoding::EncodeMethod HexEncoding::encodeMethod() const
{
	return &HexEncoding::encode;
}


inline Encoding::DecodeMethod HexEncoding::decodeMethod() const
{
	return &HexEncoding::decode;
}


inline void HexEncoding::createContent()
{
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_HexEncoding_INCLUDED
