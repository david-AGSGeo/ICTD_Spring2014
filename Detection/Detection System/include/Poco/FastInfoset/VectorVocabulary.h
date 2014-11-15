//
// VectorVocabulary.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/VectorVocabulary.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  VectorVocabulary
//
// Definition of the VectorVocabulary class.
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


#ifndef FastInfoset_VectorVocabulary_INCLUDED
#define FastInfoset_VectorVocabulary_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include <vector>


namespace Poco {
namespace FastInfoset {


template<class T>
class VectorVocabulary: public Vocabulary<T>
{
public:
	VectorVocabulary()
	{
		T dummy;
		this->_index.push_back(dummy);
	}
	
	explicit VectorVocabulary(std::size_t sizeHint)
	{
		T dummy;
		this->_index.push_back(dummy);
	}
	
	~VectorVocabulary()
	{
	}

	Poco::UInt32 index(const T& value, bool& valueExisted)
	{
		this->_index.push_back(value);
		valueExisted = false;
		return static_cast<Poco::UInt32>(this->_index.size() - 1);
	}

	Poco::UInt32 exists(const T& value, bool& valueExisted) const
	{
		for (Poco::UInt32 i = 0; i < this->_index.size(); i++)
		{
			if (this->_index[i] == value)
			{
				valueExisted = true;
				return i;
			}
		}
		valueExisted = false;
		return Utility::INVALIDINDEX;
	}
	
	const T& value(Poco::UInt32 idx) const
	{
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
		VectorVocabulary* diff = new VectorVocabulary(DONT_INITIALIZE);
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
		return new VectorVocabulary(*this);
	}

protected:
	VectorVocabulary(const VectorVocabulary& voc):
		Vocabulary<T>(voc)
	{
	}
	
private:
	enum DontInitialize
	{
		DONT_INITIALIZE
	};
	
	explicit VectorVocabulary(DontInitialize)
	{
	}

	VectorVocabulary& operator = (const VectorVocabulary& voc);
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_VectorVocabulary_INCLUDED
