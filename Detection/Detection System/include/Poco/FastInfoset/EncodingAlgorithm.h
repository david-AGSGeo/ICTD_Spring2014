//
// EncodingAlgorithm.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/EncodingAlgorithm.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  EncodingAlgorithm
//
// Definition of the EncodingAlgorithm class.
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


#ifndef FastInfoset_EncodingAlgorithm_INCLUDED
#define FastInfoset_EncodingAlgorithm_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/BitStreamWriter.h"
#include "Poco/FastInfoset/FISException.h"
#include "Poco/FastInfoset/Encoding.h"
#include <vector>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API EncodingAlgorithm
	/// Groups together different encoding algorithms as defined by the FastInfoset standard.
{
public:
	enum Algorithm
	{
		INVALID        = 0,
		HEX_ENCODING   = 1,
		DWORD_ENCODING = 2,
		SHORT_ENCODING = 3,
		INT_ENCODING   = 4,
		LONG_ENCODING  = 5,
		BOOL_ENCODING  = 6,
		FLOAT_ENCODING = 7,
		DOUBLE_ENCODING= 8,
		UUID_ENCODING  = 9,
		CDATA_ENCODING = 10,
		RESERVED       = 11,
		LAST_RESERVED  = 31,
		USER_DEFINED   = 32,
		LAST_USER_DEFINED = 256
	};

	EncodingAlgorithm();
	~EncodingAlgorithm();

	void encode(Poco::UInt32 idx, BitStreamWriter& aWriter, const std::string& data);
		/// Encodes data directly to the bitstream. idx specifies the algorithm used.

	Poco::UInt32 findEncoding(const std::string& data) const;
		/// Finds an encoding that can encode the data, returns INVALID if none is found.

	Poco::Int32 canEncode(Poco::UInt32 idx, const std::string& data) const;
		/// Returns the size of the compressed content (excl header) if it can encode sth, otherwise a value <= 0 is returned.

	void add(Encoding::EncodeMethod em, Encoding::CheckMethod ec);
		/// Adds the given encoding.

private:
	void initializeEncodings();

private:
	std::vector<Encoding::EncodeMethod> _encodings;
	std::vector<Encoding::CheckMethod>  _checks;
};


//
// inlines
//
inline void EncodingAlgorithm::encode(Poco::UInt32 idx, BitStreamWriter& aWriter, const std::string& data)
{
	(*_encodings[idx])(aWriter, data);
}


inline Poco::Int32 EncodingAlgorithm::canEncode(Poco::UInt32 idx, const std::string& data) const
{
	return (*_checks[idx])(data);
}


inline void EncodingAlgorithm::add(Encoding::EncodeMethod em, Encoding::CheckMethod ec)
{
	_encodings.push_back(em);
	_checks.push_back(ec);
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_EncodingAlgorithm_INCLUDED
