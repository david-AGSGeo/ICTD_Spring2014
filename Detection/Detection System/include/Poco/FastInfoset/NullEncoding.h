//
// NullEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/NullEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  NullEncoding
//
// Definition of the NullEncoding class.
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


#ifndef FastInfoset_NullEncoding_INCLUDED
#define FastInfoset_NullEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API NullEncoding: public Encoding
	/// An encoding that simply passes data though as is.
{
public:
	NullEncoding();
		/// Creates the NullEncoding.

	explicit NullEncoding(const std::string& data);
		/// Creates the NullEncoding.

	explicit NullEncoding(const char* data, int length);
		/// Creates the NullEncoding.

	~NullEncoding();
		/// Destroys the NullEncoding.

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
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void encode(BitStreamWriter& writer, const std::string& str);
};


//
// inlines
//
inline Poco::UInt32 NullEncoding::type() const
{
	return EncodingAlgorithm::INVALID;
}


inline Encoding::CheckMethod NullEncoding::checkMethod() const
{
	return &NullEncoding::check;
}


inline Encoding::EncodeMethod NullEncoding::encodeMethod() const
{
	return &NullEncoding::encode;
}


inline void NullEncoding::createContent()
{
}


inline Encoding::DecodeMethod NullEncoding::decodeMethod() const
{
	return &NullEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_NullEncoding_INCLUDED
