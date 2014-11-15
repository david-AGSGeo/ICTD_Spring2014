//
// HashVocabulary.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/HashVocabulary.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  HashVocabulary
//
// Definition of the HashVocabulary class.
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


#ifndef FastInfoset_HashVocabulary_INCLUDED
#define FastInfoset_HashVocabulary_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include "Poco/FastInfoset/Vocabulary.h"
#include "Poco/FastInfoset/Utility.h"
#include "Poco/HashFunction.h"
#include "Poco/Exception.h"
#include <map>


namespace Poco {
namespace FastInfoset {


template<class T>
class HashVocabulary: public Vocabulary<T>
	/// An implementation of Vocabulary using a hash table.
{
public:
	typedef HashFunction<T> ValueHashFunction;
	typedef std::vector<Poco::UInt32> HashTableVector;
	
	HashVocabulary(std::size_t hashTableSize = 32749):
		/// Creates the HashVocabulary.
		_hashTable(hashTableSize, Utility::INVALIDINDEX),
		_size(0),
		_capacity(hashTableSize)
	{
		bool dummy;
		// index starts with 1, thus insert some dummy data
		index(T(), dummy);
	}

	~HashVocabulary()
		/// Destroys the HashVocabulary.
	{
	}

	Poco::UInt32 index(const T& value, bool& valueExisted)
	{
		const Poco::UInt32 newIndex = (Poco::UInt32)(this->_index.size());
		Poco::UInt32 index = insert(value, newIndex, valueExisted);
		if (!valueExisted)
			this->_index.push_back(value);
		return index;
	}

	Poco::UInt32 exists(const T& value, bool& valueExisted) const
	{
		Poco::UInt32 index = find(value);
		valueExisted = (index != Utility::INVALIDINDEX);
		return index;
	}

	const T& value(Poco::UInt32 idx) const
	{
		poco_assert (this->_index.size() > idx);
		return this->_index[idx];
	}

	std::size_t size() const
	{
		return this->_index.size();
	}

	bool empty() const
	{
		return this->_index.empty();
	}

	Vocabulary<T>* subtract(const Vocabulary<T>& other) const
	{
		// NOTE: we have to keep the order!
		// ie. if a key1 had an idx1 smaller than idx2 of key2
		// then the diff must show that too!
		HashVocabulary* diff = new HashVocabulary(DONT_INITIALIZE);
		// thus iterate over the Index!
		Poco::UInt32 size = static_cast<Poco::UInt32>(this->_index.size());
		bool dummy;
		for (Poco::UInt32 i = 0; i < size; ++i)
		{
			const T& key = this->_index[i];
			bool existsInOther;
			other.exists(key, existsInOther);
			if (!existsInOther)
			{
				diff->index(key, dummy);
			}
		}
		return diff;
	}

	Vocabulary<T>* clone() const
	{
		return new HashVocabulary(*this);
	}

protected:
	Poco::UInt32 insert(const T& value, const Poco::UInt32 newIndex, bool &valueExisted)
	{
		Poco::UInt32 hsh = this->_hash(value, static_cast<Poco::UInt32>(this->_capacity));
		Poco::UInt32 origHash = hsh;
		while (true)
		{
			Poco::UInt32 pos = hsh % this->_capacity;
			if (this->_hashTable[pos] != Utility::INVALIDINDEX)
			{
				if (this->_index[this->_hashTable[pos]] == value)
				{
					valueExisted = true;
					return this->_hashTable[pos];
				}
			}
			else
			{
				// value not found
				valueExisted = false;
				this->_hashTable[pos] = newIndex;
				return newIndex;
			}				
			if (hsh - origHash > this->_capacity) throw PoolOverflowException("Vocabulary hash table full");
			hsh++;
		}
	}

	Poco::UInt32 find(const T& value) const
	{
		UInt32 hsh = this->_hash(value, static_cast<Poco::UInt32>(this->_capacity));
		UInt32 origHash = hsh;
		while (true)
		{
			Poco::UInt32 pos = hsh % this->_capacity;
			if (this->_hashTable[pos] != Utility::INVALIDINDEX)
			{
				if (this->_index[this->_hashTable[pos]] == value)
				{
					return this->_hashTable[pos];
				}
			}
			else return Utility::INVALIDINDEX;
			if (hsh - origHash > this->_capacity)
				return Utility::INVALIDINDEX;
			hsh++;
		}
	}

protected:
	HashVocabulary(const HashVocabulary& voc):
		Vocabulary<T>(voc),
		_hashTable(voc._hashTable),
		_size(voc._size),
		_capacity(voc._capacity),
		_hash(voc._hash)
	{
	}
	
private:
	enum DontInitialize
	{
		DONT_INITIALIZE
	};
	
	explicit HashVocabulary(DontInitialize)
	{
	}

	HashVocabulary& operator = (const HashVocabulary& voc);

	HashTableVector   _hashTable;
	std::size_t       _size;
	std::size_t       _capacity;
	ValueHashFunction _hash;
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_HashVocabulary_INCLUDED
