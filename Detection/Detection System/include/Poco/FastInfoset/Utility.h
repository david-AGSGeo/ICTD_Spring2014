//
// Utility.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/Utility.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  Utility
//
// Definition of the Utility class.
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


#ifndef FastInfoset_Utility_INCLUDED
#define FastInfoset_Utility_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API Utility
	/// The Utility class contains commonly used constants and helper methods.
{
public:
	enum 
	{
		SIZEOFCHARINBIT = 8,
		SIZEOFINT16INBIT = 16,
		SIZEOFINT32INBIT = 32,
		SIZEOFINT64INBIT = 64,
		INVALIDINDEX = 0xffffffffu
	};

	static unsigned char pow2[];
		/// A vector storing for pos x the value 2^x, x in range [0,7].

	static unsigned char revertedPow2[];
		/// A vector storing for pos x the value 2^(7-x), x in range [0,7].

	static unsigned char highBitMask[];
		/// A bitmask where the numBits highest bits are set to 1.

	static unsigned char lowBitMask[];
		/// A bitmask where the numBits lowest bits are set to 1.

	//@ deprecated
	static void convertToFIS(std::istream& xmlInput, std::ostream& fisOutput, int maxIndexedStringLength = 16);
		/// This method is provided for backwards compatibility only and
		/// simply calls Converter::convertToFIS().

	//@ deprecated
	static void convertToXML(std::istream& fisInput, std::ostream& xmlOutput);
		/// This method is provided for backwards compatibility only and
		/// simply calls Converter::convertToXML().
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Utility_INCLUDED
