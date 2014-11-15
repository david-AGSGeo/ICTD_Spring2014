//
// Encoder.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/Encoder.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  Encoder
//
// Definition of the Encoder class.
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


#ifndef FastInfoset_Encoder_INCLUDED
#define FastInfoset_Encoder_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include <cstdlib>


namespace Poco {
namespace FastInfoset {


class BitStreamWriter;
class DocumentVocabulary;


class FastInfoset_API Encoder
	/// Encoder class contains utility functions for encoding simple FIS data types.
{
public:
	enum
	{
		MAXINT1          = 2,
		MAXINT1PLUS      = 3,
		MAXINT3          = 8,
		MAXINT3PLUS      = 9,
		MAXINT4          = 16,
		MAXINT4PLUS      = 17,
		MAXINT5          = 32,
		MAXINT5PLUS      = 33,
		MAXINT6          = 64,
		MAXINT6PLUS      = 65,
		ZEROENCODEDVALUE = 0x7f,
		MAXINT8XS        = 258,
		MAXINT8XSPLUS    = 259,
		MAXINT8S         = 264,
		MAXINT8SPLUS     = 265,
		MAXINT8          = 320,
		MAXINT8PLUS      = 321,
		MAXINT10         = 1040,
		MAXINT10PLUS     = 1041,
		MAXINT11         = 2080,
		MAXINT11PLUS     = 2081,
		MAXINT13         = 8256,
		MAXINT13PLUS     = 8257,
		MAXINT18         = 263184,
		MAXINT18PLUS     = 263185,
		MAXINT19         = 526368,
		MAXINT19PLUS     = 526369,
		MAXINT20         = 0x00100000
	};

	static const Poco::UInt16 DOCUMENTSTART;
	static const Poco::UInt16 XMLDECLARATION;

	static void documentPreHeader(BitStreamWriter& aWriter, bool writeXMLDeclaration = false);
		/// Writes the default pre header for a FIS document (33bits).

	static void integer(BitStreamWriter& aWriter, Poco::UInt32 val);
		/// Encodes an integer value.

	static void pad0ThenInteger(BitStreamWriter& aWriter, Poco::UInt32 val);
		/// Writes first a padding bit 0 then the integer. Faster in some cases.

	static void nonEmptyOctetString(BitStreamWriter& aWriter, const std::string& str);
		/// Encodes a non empty string.
	
	static void lengthOfSequence(BitStreamWriter& aWriter, Poco::UInt32 len);
		/// Encodes the length of a sequence type.

	static void nonEmptyStringLength(BitStreamWriter& aWriter, const std::size_t strLen);
		/// Encodes the length of a string.
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Encoder_INCLUDED
