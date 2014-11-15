//
// VerbTable.h
//
// $Id: //poco/1.4/FastInfoset/include/Poco/FastInfoset/VerbTable.h#1 $
//
// Library: FastInfoset
// Package: FastInfoset
// Module:  VerbTable
//
// Definition of the VerbTable class template.
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


#ifndef FastInfoset_VerbTable_INCLUDED
#define FastInfoset_VerbTable_INCLUDED


#include "Poco/FastInfoset/FastInfoset.h"
#include <vector>
#include <stdexcept>


namespace Poco {
namespace FastInfoset {


template<typename T>
class VerbTable
	/// This is a vector class template providing minimal features required
	/// for use with a FastInfoset Vocabulary. A special property of this class is 
	/// that it can grow without the need to reallocate memory for existing
	/// elements. Therefore, it is save to keep pointers to objects
	/// stored in the vector.
{
public:
	typedef std::vector<std::vector<T>*> StorageVec;
	enum
	{
		INITIAL_CHUNK_SIZE = 256
	};
	
	VerbTable()
		/// Creates the VerbTable.
	{
	}
	
	VerbTable(const VerbTable& vec)
		/// Creates the VerbTable by copying another one.
	{
		if (!vec.empty())
		{
			for (typename StorageVec::const_iterator it = vec._data.begin(); it != vec._data.end(); ++it)
			{
				this->_data.push_back(new std::vector<T>(**it));
			}
			this->_data.back()->reserve(vec._data.back()->capacity());
		}
	}
	
	~VerbTable()
		/// Destroys the VerbTable.
	{
		for (typename StorageVec::iterator it = this->_data.begin(); it != this->_data.end(); ++it)
		{
			delete *it;
		}
	}
	
	void push_back(const T& value)
		/// Appends a value to the end of the vector.
		///
		/// Grows the vector if necessary.
	{
		if (this->_data.empty())
		{
			this->_data.push_back(new std::vector<T>);
			this->_data.back()->reserve(INITIAL_CHUNK_SIZE);
		}
		else if (this->_data.back()->size() == this->_data.back()->capacity())
		{
			std::size_t cap = this->_data.back()->capacity()*2;
			this->_data.push_back(new std::vector<T>);
			this->_data.back()->reserve(cap);
		}
		this->_data.back()->push_back(value);
	}
	
	std::size_t size() const
		/// Returns the size of the vector.
	{
		std::size_t n = 0;
		for (typename StorageVec::const_iterator it = this->_data.begin(); it != this->_data.end(); ++it)
		{
			n += (*it)->size();
		}
		return n;
	}

	bool empty() const
		/// Returns true iff the VerbTable does not contain any elements.
	{
		return this->_data.empty();
	}
	
	const T& operator [] (std::size_t index) const
		/// Returns the element at the given index.
	{
		return at(index);
	}
	
	T& operator [] (std::size_t index)
		/// Returns the element at the given index.
	{
		return at(index);
	}

protected:
	T& at(std::size_t index) const
	{
		for (typename StorageVec::const_iterator it = this->_data.begin(); it != this->_data.end(); ++it)
		{
			if (index < (*it)->size())
				return (**it)[index];
			index -= (*it)->size();
		}
		throw std::out_of_range("index out of range");
	}
	
private:
	VerbTable& operator = (const VerbTable& vec);
	
	StorageVec _data;
};


} } // namespace Poco::FastInfoset


#endif // FastInfoset_VerbTable_INCLUDED
