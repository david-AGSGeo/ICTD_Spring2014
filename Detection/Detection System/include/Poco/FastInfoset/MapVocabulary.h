//
// MapVocabulary.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/MapVocabulary.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  MapVocabulary
//
// Definition of the MapVocabulary class.
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


#ifndef FastInfoset_MapVocabulary_INCLUDED
#define FastInfoset_MapVocabulary_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Vocabulary.h"
#include "Poco/FastInfoset/Utility.h"
#include <map>


namespace Poco {
namespace FastInfoset {


template <class T>
class MapVocabulary: public Vocabulary<T>
	/// An implementation of Vocabulary using a map.
{
public:
	typedef std::map<T, Poco::UInt32>     Data;
	typedef typename Data::iterator       Iterator;
	typedef typename Data::const_iterator ConstIterator;

	explicit MapVocabulary(std::size_t sizeHint = 0)
		/// Creates the MapVocabulary.
	{
		bool dummy;
		// index starts with 1, thus insert some dummy data
		index(T(), dummy);
	}

	~MapVocabulary()
		/// Destroys the MapVocabulary.
	{
	}

	Poco::UInt32 index(const T& value, bool& valueExisted)
	{
		Poco::UInt32 newIdx = (Poco::UInt32)(this->_index.size());

		std::pair<Iterator, bool> res = this->_entries.insert(std::make_pair(value, newIdx));
		valueExisted = !res.second;
		if (!valueExisted)
			this->_index.push_back(res.first->first);
		
		return res.first->second;
	}

	Poco::UInt32 exists(const T& value, bool& valueExisted) const
	{
		ConstIterator it = this->_entries.find(value);
		valueExisted = (it != this->_entries.end());
		if (valueExisted)
			return it->second;

		return (Poco::UInt32) Utility::INVALIDINDEX;
	}

	const T& value(Poco::UInt32 idx) const
		/// Returns the value for the given index. Throws an exception if the idx is out of range.
	{
		poco_assert_dbg (this->_index.size() > idx);
		return this->_index[idx];
	}

	std::size_t size() const
	{
		return this->_entries.size();
	}

	bool empty() const
	{
		return this->_entries.empty();
	}

	Vocabulary<T>* subtract(const Vocabulary<T>& voc) const
	{
		// NOTE: we have to keep the order!
		// ie. if a key1 had an idx1 smaller than idx2 of key2
		// then the diff must show that too!
		MapVocabulary* diff = new MapVocabulary(DONT_INITIALIZE);
		// thus iterate over the Index!
		Poco::UInt32 size = static_cast<Poco::UInt32>(this->_index.size());
		bool dummy;
		for (Poco::UInt32 i = 0; i < size; ++i)
		{
			const T& key = this->_index[i];
			bool existsInOther;
			voc.exists(key, existsInOther);
			if (!existsInOther)
			{
				diff->index(key, dummy);
			}
		}
		return diff;
	}

	Vocabulary<T>* clone() const
	{
		MapVocabulary* pVoc = new MapVocabulary(DONT_INITIALIZE);

		// to retain the same order we have to iterate over the vector
		std::size_t size = this->_index.size();
		bool dummy;
		for (std::size_t i = 0; i < size; i++)
		{
			pVoc->index(this->_index[i], dummy);
		}
		return pVoc;
	}

private:
	enum DontInitialize
	{
		DONT_INITIALIZE
	};
	
	explicit MapVocabulary(DontInitialize)
	{
	}

	MapVocabulary(const MapVocabulary& voc);
	MapVocabulary& operator = (const MapVocabulary& voc);

private:
	Data _entries;
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_Vocabulary_INCLUDED
