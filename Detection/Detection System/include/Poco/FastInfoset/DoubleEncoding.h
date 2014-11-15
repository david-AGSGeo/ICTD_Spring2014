//
// DoubleEncoding.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/DoubleEncoding.h#1 $
//
// Library: FastInfoset
// Package: CodingAlgorithm
// Module:  DoubleEncoding
//
// Definition of the DoubleEncoding class.
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


#ifndef FastInfoset_DoubleEncoding_INCLUDED
#define FastInfoset_DoubleEncoding_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API DoubleEncoding: public Encoding
	/// This class implements the Fast Infoset encoding for double.
{
public:
	explicit DoubleEncoding(double value);
		/// Creates the DoubleEncoding using the given value.

	explicit DoubleEncoding(const std::vector<double>& values);
		/// Creates the DoubleEncoding using the given values.

	explicit DoubleEncoding(const std::string& values);
		/// Creates the DoubleEncoding, using the given
		/// string containing space-separated double values.

	~DoubleEncoding();
		/// Destroys the DoubleEncoding.

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
	static void decode(BitStreamReader& reader, std::vector<double>& val);
	static Encoding::Ptr decode(BitStreamReader& reader);
	static Poco::Int32 check(const std::string& str);
	static void encode(BitStreamWriter& writer, const std::string& str);
	static void parse(const std::string& str, std::vector<double>& data);
		/// Parses the string for double values, single space chars are allowed between the values 
		/// but not at the end or at the beginning, every error will result in an empty data return vector.

private:
	std::vector<double> _data;
};


//
// inlines
//
inline Poco::UInt32 DoubleEncoding::type() const
{
	return EncodingAlgorithm::DOUBLE_ENCODING;
}


inline Encoding::CheckMethod DoubleEncoding::checkMethod() const
{
	return &DoubleEncoding::check;
}


inline Encoding::EncodeMethod DoubleEncoding::encodeMethod() const
{
	return &DoubleEncoding::encode;
}


inline Encoding::DecodeMethod DoubleEncoding::decodeMethod() const
{
	return &DoubleEncoding::decode;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_DoubleEncoding_INCLUDED
