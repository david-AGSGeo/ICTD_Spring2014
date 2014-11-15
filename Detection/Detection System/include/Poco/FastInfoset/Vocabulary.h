//
// Vocabulary.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/Vocabulary.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  Vocabulary
//
// Definition of the Vocabulary class.
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


#ifndef FastInfoset_Vocabulary_INCLUDED
#define FastInfoset_Vocabulary_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/VerbTable.h"


namespace Poco {
namespace FastInfoset {


template<class T>
class Vocabulary
	/// A Vocabulary allows to map values to indices and vice versa. 
	/// New values are automatically enqueued and assigned an index.
{
public:
	typedef VerbTable<T> Index;

	Vocabulary()
		/// Creates the Vocabulary.
	{
	}
	
	virtual ~Vocabulary()
		/// Destroys the Vocabulary.
	{
	}

	virtual Poco::UInt32 index(const T& value, bool& valueExisted) = 0;
		/// Returns the index for the given value. Automatically appends the value and assigns it a new
		/// index if the value does not exist yet. Query valueExisted to find out if the value already existed.

	virtual Poco::UInt32 exists(const T& value, bool& valueExisted) const = 0;
		/// Returns the index for the given value. Sets valueExisted to false if the value did not exist and returns Utility::INVALIDINDEX
	
	virtual const T& value(Poco::UInt32 idx) const = 0;
		/// Returns the value for the given index. Throws an exception if the idx is out of range.
	
	virtual std::size_t size() const = 0;
		/// Returns the vocabulary's size.
	
	virtual bool empty() const = 0;
		/// Returns true iff the vocabulary is empty.

	const Index& index() const
	{
		return _index;
	}
		
	virtual Vocabulary* subtract(const Vocabulary& other) const = 0;
		/// Returns a new Vocabulary containing all entries that
		/// are contained in this Vocabulary, but not in the given other.

	virtual Vocabulary* clone() const = 0;
		/// Deep-copies the vocabulary

protected:
	Vocabulary(const Vocabulary& voc):
		_index(voc._index)
	{
	}

	Index _index;

private:
	Vocabulary& operator = (const Vocabulary& voc);
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Vocabulary_INCLUDED
