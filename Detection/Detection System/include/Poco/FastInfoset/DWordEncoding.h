//
// DWordEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/DWordEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  DWordEncoding
//
// Definition of the DWordEncoding class.
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


#ifndef FastInfoset_DWordEncoding_INCLUDED
#define FastInfoset_DWordEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API DWordEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for base64-based binary data.
{
public:
	explicit DWordEncoding(const std::string& data);
		/// Creates the DWordEncoding, using the given base64-encoded data.
		
	DWordEncoding(const char* data, std::size_t length);
		/// Creates the DWordEncoding, usign the given raw binary data.

	~DWordEncoding();
		/// Destroys the DWordEncoding.

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
	DWordEncoding();
	static void decode(const std::string& binaryData, std::string& base64Data);
};


//
// inlines
//
inline Poco::UInt32 DWordEncoding::type() const
{
	return EncodingAlgorithm::DWORD_ENCODING;
}


inline Encoding::CheckMethod DWordEncoding::checkMethod() const
{
	return &DWordEncoding::check;
}


inline Encoding::EncodeMethod DWordEncoding::encodeMethod() const
{
	return &DWordEncoding::encode;
}


inline Encoding::DecodeMethod DWordEncoding::decodeMethod() const
{
	return &DWordEncoding::decode;
}


inline void DWordEncoding::createContent()
{
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_DWordEncoding_INCLUDED
