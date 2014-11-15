//
// RestrictedAlphabet.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/RestrictedAlphabet.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  RestrictedAlphabet
//
// Definition of the RestrictedAlphabet class.
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


#ifndef FastInfoset_RestrictedAlphabet_INCLUDED
#define FastInfoset_RestrictedAlphabet_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include <vector>
#include <algorithm>


namespace Poco {
namespace FastInfoset {


class FastInfoset_API RestrictedAlphabet
	/// A RestrictedAlphabet consists of a sequence of single characters, 
	/// the position of each character is equal to the integer value used to encode it.
	/// Example:
	///    RestrictedAlphabet alph("0123456789");
	///    poco_assert (alph.index('1') == 1);
	///    poco_assert (alph.value(1) == '1');
{
public:
	RestrictedAlphabet();
		/// Creates an illegal RestrictedAlphabet. Used for reserved alphabets 3-15.

	RestrictedAlphabet(const std::string& utf8Characters);
		/// Creates the RestrictedAlphabet using the given table, which is a
		/// sequence of UTF-8 encoded characters.

	~RestrictedAlphabet();
		/// Destroys the RestrictedAlphabet.

	int charToIndex(int ch) const;
		/// Converts a Unicode character to its index, returns -1 if not found.

	int indexToChar(int index) const;
		/// Converts a character index to the character it represents.
		
	bool isEndOfString(int index) const;
		/// Returns true iff the given character index marks the end of the encoded string.

	int bitSize() const;
		/// Returns the number of bits required to encode a single character.
		
	const std::string& characters() const;
		/// Returns a UTF-8 string containing all characters of the alphabet.
		
private:
	std::string _utf8Characters;
	std::vector<int> _characters;
	int _numBits;
};


//
// inlines
//
inline int RestrictedAlphabet::charToIndex(int ch) const
{
	std::vector<int>::size_type size = _characters.size();
	for (std::vector<int>::size_type i = 0; i < size; i++)
	{
		if (_characters[i] == ch) return static_cast<int>(i);
	}
	return -1;
}


inline int RestrictedAlphabet::indexToChar(int index) const
{
	return _characters[index];
}


inline bool RestrictedAlphabet::isEndOfString(int index) const
{
	return index == static_cast<int>(_characters.size() - 1);
}


inline int RestrictedAlphabet::bitSize() const
{
	return _numBits;
}


inline const std::string& RestrictedAlphabet::characters() const
{
	return _utf8Characters;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_RestrictedAlphabet_INCLUDED
