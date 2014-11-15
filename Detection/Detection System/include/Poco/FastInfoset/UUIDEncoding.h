//
// UUIDEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/UUIDEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  UUIDEncoding
//
// Definition of the UUIDEncoding class.
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


#ifndef FastInfoset_UUIDEncoding_INCLUDED
#define FastInfoset_UUIDEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"
#include "Poco/UUID.h"
#include <vector>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API UUIDEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for UUID values.
{
public:
	explicit UUIDEncoding(const std::string& data);
		/// Creates the UUIDEncoding by parsing the string for UUID entries.

	explicit UUIDEncoding(const Poco::UUID& data);
		/// Creates the UUIDEncoding using the given UUID.

	explicit UUIDEncoding(const std::vector<Poco::UUID>& data);
		/// Creates the UUIDEncoding using the given data.

	~UUIDEncoding();
		/// Destroys the UUIDEncoding.

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
	static void decode(BitStreamReader& reader, std::vector<Poco::UUID>& result);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void parse(const std::string& str, std::vector<Poco::UUID>& data);
	static void encode(BitStreamWriter& writer, const std::string& str);
		/// Parses the string for UUID values, single space chars are allowed between the values 
		/// but not at the end or at the beginning, every error will result in an empty data return vector.

private:
	std::vector<std::string> _data;
};


//
// inlines
//
inline Poco::UInt32 UUIDEncoding::type() const
{
	return EncodingAlgorithm::UUID_ENCODING;
}


inline Encoding::CheckMethod UUIDEncoding::checkMethod() const
{
	return &UUIDEncoding::check;
}


inline Encoding::EncodeMethod UUIDEncoding::encodeMethod() const
{
	return &UUIDEncoding::encode;
}


inline Encoding::DecodeMethod UUIDEncoding::decodeMethod() const
{
	return &UUIDEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_UUIDEncoding_INCLUDED
