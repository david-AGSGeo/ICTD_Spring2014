//
// Decoder.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/Decoder.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  Decoder
//
// Definition of the Decoder class.
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


#ifndef FastInfoset_Decoder_INCLUDED
#define FastInfoset_Decoder_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/DocumentVocabulary.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/SAX/DTDHandler.h"
#include <cstdlib>


namespace Poco {
namespace FastInfoset {


class BitStreamReader;
class QualifiedNameEntry;
class FISDocumentHandler;


class FastInfoset_API Decoder
	/// A Utility class to decode trivial FastInfoset data types.
{
public:
	struct OpenHeaderParts
	{
		bool hasNotations;
		bool hasUnparsedEntities;
		bool hasCharacterEncodingScheme;
		bool isStandalone;
		bool hasVersion;
	};

	static void documentPreHeader(BitStreamReader& aReader, std::string& xmlDeclaration);
		/// Parses over the preHeader, returns the xmldeclaration if there is one, checks if the start bytes before the document are ok.

	static OpenHeaderParts documentHeader(BitStreamReader& aReader, DocumentVocabulary& voc, FISDocumentHandler* pHandler);
		/// Parses over the document header, returning the initialized DocumentVocabulary.
		/// OpenHeaderParts contains information about header elements that were not parsed but should be parsed outside by the caller

	static void integer(BitStreamReader& aReader, Poco::UInt32& val);
		/// Returns the integer value or an FISException.

	static void nonEmptyOctetString(BitStreamReader& aReader, std::string& str);
		/// Returns a non empty string or an FISException.

	static void lengthOfSequence(BitStreamReader& aReader, Poco::UInt32& len);
		/// Returns the number of elements present in a sequence.

	static void nonEmptyStringLength(BitStreamReader& aReader, std::size_t& strLen);
		/// Decodes the length of the string.

private:
	static void skipAdditionalData(BitStreamReader& aReader);

	static void parseInitialVocabulary(BitStreamReader& aReader, DocumentVocabulary& voc, FISDocumentHandler* pHandler);

	static void handleExternalVocabulary(BitStreamReader& aReader, DocumentVocabulary& voc, FISDocumentHandler* pHandler);

	static void handleRestrictedAlphabet(BitStreamReader& aReader, DocumentVocabulary& voc);

	static void handleVocabulary(BitStreamReader& aReader, DocumentVocabulary::XMLStringVocabulary& voc);

	static void handleEncodedCharacterStringVoc(BitStreamReader& aReader, DocumentVocabulary::XMLStringVocabulary& voc, DocumentVocabulary& vocDocu);
		/// handles an encoded character string voc 

	static void encodedCharacterString(BitStreamReader& aReader, std::string& utf8String, DocumentVocabulary& voc);
		/// Decodes an encodedcharacterstring to utf8 format

	static void handleNameSurrogatesVoc(BitStreamReader& aReader, QualifiedNameVocabulary& voc);

	static void skipEncodingAlgos(BitStreamReader& aReader, DocumentVocabulary& voc);

	static QualifiedNameEntry nameSurrogate(BitStreamReader& aReader);
		// Returns a namesurrogate.
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Decoder_INCLUDED
