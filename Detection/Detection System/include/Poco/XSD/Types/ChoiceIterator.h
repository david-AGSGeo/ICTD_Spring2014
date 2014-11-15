//
// ChoiceIterator.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/ChoiceIterator.h#2 $
//
// Library: XSD/Types
// Package: Iterator
// Module:  ChoiceIterator
//
// Definition of the ChoiceIterator class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_ChoiceIterator_INCLUDED
#define XSDTypes_ChoiceIterator_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/OrderIteratorImpl.h"


namespace Poco {
namespace XSD {
namespace Types {


class Choice;


class XSDTypes_API ChoiceIterator: public OrderIteratorImpl
	/// An iterator for iterating over a Choice's content.
{
public:
	ChoiceIterator(const Choice& choice);
		/// Creates the ChoiceIterator.

	virtual ~ChoiceIterator();
		/// Destroys the ChoiceIterator.

	// OrderIteratorImpl
	OrderContent::Ptr next(const std::string& name);
	const std::set<std::string>& validNexts() const;
	bool end() const;
	bool validNext(const std::string& name) const;
	void close();
	bool canClose() const;
	void reset();

private:
	typedef std::vector<OrderIterator> Iterators;

	UInt32    _min;
	UInt32    _max;
	mutable Iterators _vecIt;
	mutable Iterators::size_type _lastChosenPos;
	mutable std::set<std::string> _next;
	UInt32 _chosenElementCnt;
	mutable bool _dirtyFlag;
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_ChoiceIterator_INCLUDED
