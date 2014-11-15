//
// DocumentRestrictedAlphabet.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/DocumentRestrictedAlphabet.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  DocumentRestrictedAlphabet
//
// Definition of the DocumentRestrictedAlphabet class.
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


#ifndef FastInfoset_DocumentRestrictedAlphabet_INCLUDED
#define FastInfoset_DocumentRestrictedAlphabet_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/RestrictedAlphabet.h"
#include <vector>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API DocumentRestrictedAlphabet
	/// DocumentRestrictedAlphabet stores the prefined simple 
	/// vocabularies for numeric or date time de-/encoding.
{
public:
	typedef std::vector<RestrictedAlphabet> Alphabets;

	static const std::string NUMERIC_CHARACTERS;
	static const std::string DATE_TIME_CHARACTERS;

	DocumentRestrictedAlphabet();
		/// Creates the DocumentRestrictedAlphabet.

	~DocumentRestrictedAlphabet();
		/// Destroys the DocumentRestrictedAlphabet.

	Poco::UInt32 add(const std::string& str);
		/// Adds the string as a new vocabulary, returns the ids of the vocabulary,
		/// the maximum is limited to 256 vocabularies.

	int charToIndex(Poco::UInt32 vocabulary, int value) const;
		/// Returns the index for the given vocabulary and Unicode character.

	int indexToChar(Poco::UInt32 vocabulary, int index) const;
		/// Returns the Unicode character for the given vocabulary and character index.

	RestrictedAlphabet& alphabet(Poco::UInt32 vocabulary);
		/// Returns the alphabet for the given id.

	const Alphabets& alphabets() const;
		/// Returns all defined alphabets.

	DocumentRestrictedAlphabet operator - (const DocumentRestrictedAlphabet& other);
		/// Subtracts another restricted alphabet from this one. 
		///
		/// The other vocabulary must be smaller than this alphabet
		/// The content of the alphabets is not checked but assumed to be equal.

private:
	void addDummy();
		/// adds an illegal vocabulary: finf only defines voc 1+2, then 3 to 15 as reserved ones, user defined start at 16!

	DocumentRestrictedAlphabet(bool empty);
		/// creates a totally empty alphabet

private:
	Alphabets _alphabets;
};


//
// inlines
//
inline int DocumentRestrictedAlphabet::charToIndex(Poco::UInt32 vocabulary, int ch) const
{
	poco_assert (vocabulary > 0 && vocabulary <= _alphabets.size());
	return _alphabets[vocabulary - 1].charToIndex(ch); // restr voc start at pos 1, not 0
}


inline int DocumentRestrictedAlphabet::indexToChar(Poco::UInt32 vocabulary, int index) const
{
	poco_assert (vocabulary > 0 && vocabulary <= _alphabets.size());
	return _alphabets[vocabulary - 1].indexToChar(index); // restr voc start at pos 1, not 0
}


inline RestrictedAlphabet& DocumentRestrictedAlphabet::alphabet(Poco::UInt32 vocabulary)
{
	poco_assert (vocabulary > 0 && vocabulary <= _alphabets.size());
	return _alphabets[vocabulary - 1]; // restr voc start at pos 1, not 0
}


inline const DocumentRestrictedAlphabet::Alphabets& DocumentRestrictedAlphabet::alphabets() const
{
	return _alphabets;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_DocumentRestrictedAlphabet_INCLUDED
