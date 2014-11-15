//
// StringDecoder.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/StringDecoder.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  StringDecoder
//
// Definition of the StringDecoder class.
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


#ifndef FastInfoset_StringDecoder_INCLUDED
#define FastInfoset_StringDecoder_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/DocumentVocabulary.h"
#include "Poco/FastInfoset/Utility.h"


namespace Poco {
namespace FastInfoset {


class DocumentVocabulary;


class StringDecoder
	/// StringDecoder decodes strings.
{
public:
	static bool decodeUTF8(const std::string& str, std::string& res);
		/// Returns true when res was set, if it returns false, res would be equal to str

	static void decodeUTF16(const std::string& str, std::string& res);
		
	static void decodeAlphabet(const std::string& res, RestrictedAlphabet& al, std::string& out);

private:
	static bool decodeEntities(const std::string& str, std::string& res);
		/// Reverts XML entity encoding.
};


//
// inlines
//
inline bool StringDecoder::decodeUTF8(const std::string& str, std::string& res)
{
	return false;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_StringDecoder_INCLUDED
