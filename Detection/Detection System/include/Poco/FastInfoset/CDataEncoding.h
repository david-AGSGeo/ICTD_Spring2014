//
// CDataEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/CDataEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  CDataEncoding
//
// Definition of the CDataEncoding class.
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


#ifndef FastInfoset_CDataEncoding_INCLUDED
#define FastInfoset_CDataEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API CDataEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for CDATA.
{
public:
	explicit CDataEncoding(const std::string& data);
		/// Creates the CDataEncoding using the given data.

	CDataEncoding(const char* data, int length);
		/// Creates the CDataEncoding using the given data.

	~CDataEncoding();
		/// Destroys the CDataEncoding.

	// Encoding
	Poco::UInt32 type() const;
	bool merge(const Encoding& enc);
	Encoding::CheckMethod checkMethod() const;
	Encoding::EncodeMethod encodeMethod() const;
	Encoding::DecodeMethod decodeMethod() const;
	void write(BitStreamWriter& writer) const;
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
inline Poco::UInt32 CDataEncoding::type() const
{
	return EncodingAlgorithm::CDATA_ENCODING;
}


inline Encoding::CheckMethod CDataEncoding::checkMethod() const
{
	return &CDataEncoding::check;
}


inline Encoding::EncodeMethod CDataEncoding::encodeMethod() const
{
	return &CDataEncoding::encode;
}


inline void CDataEncoding::createContent()
{
}


inline Encoding::DecodeMethod CDataEncoding::decodeMethod() const
{
	return &CDataEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_CDataEncoding_INCLUDED
