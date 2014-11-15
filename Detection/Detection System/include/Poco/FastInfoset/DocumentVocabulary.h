//
// DocumentVocabulary.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/DocumentVocabulary.h#2 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  DocumentVocabulary
//
// Definition of the DocumentVocabulary class.
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


#ifndef FastInfoset_DocumentVocabulary_INCLUDED
#define FastInfoset_DocumentVocabulary_INCLUDED


#include "Poco/FastInfoset/Vocabulary.h"
#include "Poco/FastInfoset/EncodingAlgorithm.h"
#include "Poco/FastInfoset/DecodingAlgorithm.h"
#include "Poco/FastInfoset/DocumentRestrictedAlphabet.h"
#include "Poco/FastInfoset/QualifiedNameVocabulary.h"
#include "Poco/FastInfoset/HashVocabulary.h"
#include "Poco/FastInfoset/MapVocabulary.h"


namespace Poco {
namespace FastInfoset {


class FastInfoset_API DocumentVocabulary
	/// DocumentVocabulary groups together all 
	/// vocabularies used when de-/encoding a FISDocument.
	///
	/// DocumentVocabulary can use different internal
	/// table implementations, e.g. a hash table, a map
	/// or a simple vector.
	/// If the vocabulary is used for parsing only,
	/// the simple vector-based implementation is the best
	/// choice, as it will deliver the fastest
	/// parsing speed. However, a vector-based vocabulary
	/// cannot be used for generating FastInfoset data with
	/// the FastInfosetWriter.
	///
	/// A hash table based vocabulary is the best choice for use with
	/// the FastInfosetWriter. Its only limitations are
	/// the sizes of the internal hash tables. which might be
	/// too small for some very huge documents.
	///
	/// A map based vocabulary does not has the size limitations
	/// of a hash table based vocabulary, but is slightly slower.
{
public:
	typedef Vocabulary<std::string> XMLStringVocabulary;
	typedef std::vector<XMLStringVocabulary*> VocabularyVector;

	enum VocabularyImpl
		/// Implementation of vocabulary.
	{
		VOC_HASH,   /// using hash table -- fast, but limited size
		VOC_MAP,    /// using map -- a bit slower than hash, but no size limit
		VOC_VECTOR  /// using vector -- fastest, but can only be used for parsing
	};

	enum ID
	{
		RESTRICTED_ALPHABET     = 0,
		ENCODING_ALGORITHM      = 1,
		PREFIX                  = 2,
		NAMESPACE_NAME          = 3,
		LOCAL_NAME              = 4,
		OTHER_NCNAME            = 5,
		OTHER_URI               = 6,
		ATTRIBUTE_VALUE         = 7,
		OTHER_STRING            = 8,
		CHARACTER_CONTENT_CHUNK = 9,
		ELEMENT_NAME            = 10,
		ATTRIBUTE_NAME          = 11,
		INVALID                 = 0xffffffff
	};

	enum CharacterStringEncoding
	{
		UTF8               = 0,
		UTF16              = 1,
		RESTRICTEDALPHABET = 2,
		ENCODINGALGORITHM  = 3
	};

	explicit DocumentVocabulary(VocabularyImpl impl = VOC_HASH);
		/// Creates the DocumentVocabulary, using the given implementation.

	DocumentVocabulary(const std::string& uri, VocabularyImpl impl = VOC_HASH);
		/// Creates the DocumentVocabulary, using the given URI and vocabulary implementation.

	DocumentVocabulary(const DocumentVocabulary& other);
		/// Creates a DocumentVocabulary by copying another one.

	~DocumentVocabulary();
		/// Destroys the DocumentVocabulary.

	DocumentVocabulary& operator = (const DocumentVocabulary& voc);
		/// Assignement operator.

	void init();
		/// Sets the minimum required entries.
		
	void reset();
		/// Resets the vocabulary for a new parsing run.

	DocumentRestrictedAlphabet& restrictedAlphabets();
		/// Returns the restricted alphabets, per default only the builtin ones are enabled.

	const DocumentRestrictedAlphabet& restrictedAlphabets() const;
		/// Returns the restricted alphabets, per default only the builtin ones are enabled.

	EncodingAlgorithm& encodings();
		/// Returns the encodings which are available per default.

	DecodingAlgorithm& decodings();
		/// Returns the decodings which are available per default.

	void initialize(ID vocabulary, XMLStringVocabulary* pVoc);
		/// Initializes a vocabulary with the given one. Existing cached data will be cleared! Class takes ownership of the pointer.

	Poco::UInt32 index(ID vocabulary, const std::string& value, bool& valueExisted);
		/// Returns the index for the given vocabulary and value. Automatically appends the value and assigns it a new
		/// index if the value does not exist yet.

	Poco::UInt32 exists(ID vocabulary, const std::string& value, bool& valueExists) const;
		/// Returns the index for the given vocabulary and value if it exists. otherwise an invalid value is returned and
		/// valueExists is set to false.

	const std::string& value(ID vocabulary, Poco::UInt32 idx) const;
		/// Returns the value for the given vocabulary and index. Throws an exception if vocabulary or idx are out of range.

	QualifiedNameVocabulary& elementVocabulary();
		/// Returns the vocabulary used for QualifiedNames of elements.

	QualifiedNameVocabulary& attributeVocabulary();
		/// Returns the vocabulary used for QualifiedNames of attributes.

	const QualifiedNameVocabulary& elementVocabulary() const;
		/// Returns the vocabulary used for QualifiedNames of elements.

	const QualifiedNameVocabulary& attributeVocabulary() const;
		/// Returns the vocabulary used for QualifiedNames of attributes.

	XMLStringVocabulary& vocabulary(ID voc);

	const XMLStringVocabulary& vocabulary(ID voc) const;

	void setURI(const std::string& uri);
		/// Sets the vocabulary's URI (for external vocabularies).

	const std::string& getURI() const;
		/// Returns the vocabulary's URI.

	DocumentVocabulary operator - (const DocumentVocabulary& doc);
		/// Subtracts from this object doc. the doc vocabulary must contain for each vocabulary
		/// less elements than this vocabulary. The returned Vocabulary will only
		/// contain the difference, url will be always empty
		/// note that the - operator ignores encodingalgos currently!

	const VocabularyVector& vocabularies() const;
	
	VocabularyImpl impl() const;

private:
	enum DontInitialize
	{
		DONT_INITIALIZE
	};

	DocumentVocabulary(DontInitialize);
	void clear();		
	void copy(const DocumentVocabulary& voc);

	template <class StringVoc, class QNEVoc>
	void create()
	{
		_pElementVocabulary   = new QNEVoc(10009);
		_pAttributeVocabulary = new QNEVoc(10009);

		// PREFIX: 19
		_vocabularies.push_back(new StringVoc(251));
		// NAMESPACE_NAME: 19
		_vocabularies.push_back(new StringVoc(251));
		// LOCAL_NAME: for large docs this can easily be 10000
		_vocabularies.push_back(new StringVoc(40009));
		// OTHER_NCNAME
		_vocabularies.push_back(new StringVoc(40009));
		// OTHER_URI 
		_vocabularies.push_back(new StringVoc(19));
		// ATTRIBUTE_VALUE
		_vocabularies.push_back(new StringVoc(40009));
		// OTHER_STRING
		_vocabularies.push_back(new StringVoc(19));
		// CHARACTER_CONTENT_CHUNK: for large docs this can easily be 30000
		_vocabularies.push_back(new StringVoc(65521));
	}

private:
	VocabularyImpl             _impl;
	VocabularyVector           _vocabularies;
	DocumentRestrictedAlphabet _restrAlphabets;
	EncodingAlgorithm          _encodings;
	DecodingAlgorithm          _decodings;
	QualifiedNameVocabulary*   _pElementVocabulary;
	QualifiedNameVocabulary*   _pAttributeVocabulary;
	std::string                _uri;
};


//
// inlines
//
inline DocumentRestrictedAlphabet& DocumentVocabulary::restrictedAlphabets()
{
	return _restrAlphabets;
}


inline const DocumentRestrictedAlphabet& DocumentVocabulary::restrictedAlphabets() const
{
	return _restrAlphabets;
}


inline EncodingAlgorithm& DocumentVocabulary::encodings()
{
	return _encodings;
}


inline DecodingAlgorithm& DocumentVocabulary::decodings()
{
	return _decodings;
}


inline Poco::UInt32 DocumentVocabulary::index(DocumentVocabulary::ID vocabulary, const std::string& value, bool& valueExisted)
{
	poco_assert_dbg (vocabulary > DocumentVocabulary::ENCODING_ALGORITHM && vocabulary < DocumentVocabulary::ELEMENT_NAME);
	return _vocabularies[(int)vocabulary]->index(value, valueExisted);
}


inline Poco::UInt32 DocumentVocabulary::exists(DocumentVocabulary::ID vocabulary, const std::string& value, bool& valueExisted) const
{
	poco_assert_dbg (vocabulary > DocumentVocabulary::ENCODING_ALGORITHM && vocabulary < DocumentVocabulary::ELEMENT_NAME);
	return _vocabularies[(int)vocabulary]->exists(value, valueExisted);
}


inline const std::string& DocumentVocabulary::value(DocumentVocabulary::ID vocabulary, Poco::UInt32 idx) const
{
	poco_assert_dbg (vocabulary > DocumentVocabulary::ENCODING_ALGORITHM && vocabulary < DocumentVocabulary::ELEMENT_NAME);
	return _vocabularies[(int)vocabulary]->value(idx);
}


inline QualifiedNameVocabulary& DocumentVocabulary::elementVocabulary()
{
	poco_assert_dbg (_pElementVocabulary);
	return *_pElementVocabulary;
}


inline QualifiedNameVocabulary& DocumentVocabulary::attributeVocabulary()
{
	poco_assert_dbg (_pAttributeVocabulary);
	return *_pAttributeVocabulary;
}


inline const QualifiedNameVocabulary& DocumentVocabulary::elementVocabulary() const
{
	poco_assert_dbg (_pElementVocabulary);
	return *_pElementVocabulary;
}


inline const QualifiedNameVocabulary& DocumentVocabulary::attributeVocabulary() const
{
	poco_assert_dbg (_pAttributeVocabulary);
	return *_pAttributeVocabulary;
}


inline DocumentVocabulary::XMLStringVocabulary& DocumentVocabulary::vocabulary(DocumentVocabulary::ID voc)
{
	poco_assert_dbg (voc > DocumentVocabulary::ENCODING_ALGORITHM && voc < DocumentVocabulary::ELEMENT_NAME);
	return *(_vocabularies[(int)voc]);
}


inline const DocumentVocabulary::XMLStringVocabulary& DocumentVocabulary::vocabulary(DocumentVocabulary::ID voc) const
{
	poco_assert_dbg (voc > DocumentVocabulary::ENCODING_ALGORITHM && voc < DocumentVocabulary::ELEMENT_NAME);
	return *(_vocabularies[(int)voc]);
}


inline void DocumentVocabulary::setURI(const std::string& uri)
{
	_uri = uri;
}


inline const std::string& DocumentVocabulary::getURI() const
{
	return _uri;
}


inline const DocumentVocabulary::VocabularyVector& DocumentVocabulary::vocabularies() const
{
	return _vocabularies;
}


inline DocumentVocabulary::VocabularyImpl DocumentVocabulary::impl() const
{
	return _impl;
}


} } // namespace Poco::FastInfoset


#endif // FastInfoset_DocumentVocabulary_INCLUDED
