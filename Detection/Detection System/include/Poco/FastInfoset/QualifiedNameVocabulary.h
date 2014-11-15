//
// QualifiedNameVocabulary.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/QualifiedNameVocabulary.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  QualifiedNameVocabulary
//
// Definition of the QualifiedNameVocabulary class.
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


#ifndef FastInfoset_QualifiedNameVocabulary_INCLUDED
#define FastInfoset_QualifiedNameVocabulary_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Vocabulary.h"
#include "Poco/FastInfoset/HashVocabulary.h"
#include "Poco/FastInfoset/MapVocabulary.h"
#include "Poco/HashFunction.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API QualifiedNameEntry
	/// A QualifiedNameEntry represents a XML qualified name.
{
public:
	QualifiedNameEntry();
		/// Creates an empty QualifiedNameEntry

	QualifiedNameEntry(Poco::UInt32 prefixId, Poco::UInt32 namespaceId, Poco::UInt32 localNameId);
		/// Creates the QualifiedNameEntry

	~QualifiedNameEntry();
		/// Destroys the QualifiedNameEntry

	bool operator == (const QualifiedNameEntry& other) const;
		/// Compares two entries for equality.

	bool operator != (const QualifiedNameEntry& other) const;
		/// Compares two entries for unequality.

	bool operator < (const QualifiedNameEntry& other) const;
		/// Compares two entries by lower than.

	Poco::UInt32 prefixId() const;
		/// Returns the id of the prefix. The id presents an index into a vocabulary. 
		/// To convert the id back to the string representation, simply call vocabulary.value(index).
		/// Note that it depends on the location of the entry in the FISDocument which vocabulary will be used.

	Poco::UInt32 namespaceId() const;
		/// Returns the id of the namespace. The id presents an index into a vocabulary. 
		/// To convert the id back to the string representation, simply call vocabulary.value(index).
		/// Note that it depends on the location of the entry in the FISDocument which vocabulary will be used.

	Poco::UInt32 localNameId() const;
		/// Returns the id of the localName. The id presents an index into a vocabulary. 
		/// To convert the id back to the string representation, simply call vocabulary.value(index).
		/// Note that it depends on the location of the entry in the FISDocument which vocabulary will be used.

private:
	Poco::UInt32 _prefixId;
	Poco::UInt32 _namespaceId;
	Poco::UInt32 _localNameId;
};


//
// inlines
//
inline bool QualifiedNameEntry::operator == (const QualifiedNameEntry& other) const
{
	return _prefixId == other._prefixId && _namespaceId == other._namespaceId && _localNameId == other._localNameId;
}


inline bool QualifiedNameEntry::operator != (const QualifiedNameEntry& other) const
{
	return !(_prefixId == other._prefixId && _namespaceId == other._namespaceId && _localNameId == other._localNameId);
}


inline Poco::UInt32 QualifiedNameEntry::prefixId() const
{
	return _prefixId;
}


inline Poco::UInt32 QualifiedNameEntry::namespaceId() const
{
	return _namespaceId;
}


inline Poco::UInt32 QualifiedNameEntry::localNameId() const
{
	return _localNameId;
}


typedef Vocabulary<QualifiedNameEntry> QualifiedNameVocabulary;


} } // namespace Poco::FastInfoset


namespace Poco {


template <>
struct HashFunction<FastInfoset::QualifiedNameEntry>
{
	Poco::UInt32 operator()(const FastInfoset::QualifiedNameEntry& qne, Poco::UInt32 maxValue) const
	{
		return ((0xf4243 ^ qne.prefixId()) * (0xf4243 ^ qne.namespaceId()) * (0xf4243 ^ qne.localNameId())) % maxValue;
	}
};


} // namespace Poco


#endif // FastInfoset_QualifiedNameVocabulary_INCLUDED
