//
// DecodingAlgorithm.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/DecodingAlgorithm.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  DecodingAlgorithm
//
// Definition of the DecodingAlgorithm class.
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


#ifndef FastInfoset_DecodingAlgorithm_INCLUDED
#define FastInfoset_DecodingAlgorithm_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Encoding.h"
#include <vector>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API DecodingAlgorithm
	/// DecodingAlgorithm bundles all decoding algorithms supported by 
	/// FastInfoset standard (like hex encoding, int encoding, uuid encoding....)
{
public:
	DecodingAlgorithm();
		/// Creates the DecodingAlgorithm.

	~DecodingAlgorithm();
		/// Destroys the DecodingAlgorithm.

	Encoding::Ptr read(Poco::Int32 algo, BitStreamReader& reader);
		/// Reads the encoded data, converts it to a string and forwards it as characterchunk to pHandler

	void add(Encoding::DecodeMethod dec);

private:
	void initializeDecodings();

private:
	std::vector<Encoding::DecodeMethod> _decodings;
};


//
// inlines
//
inline Encoding::Ptr DecodingAlgorithm::read(Poco::Int32 algo, BitStreamReader& reader)
{
	return (*_decodings[algo])(reader);
}


inline void DecodingAlgorithm::add(Encoding::DecodeMethod dec)
{
	_decodings.push_back(dec);
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_DecodingAlgorithm_INCLUDED
