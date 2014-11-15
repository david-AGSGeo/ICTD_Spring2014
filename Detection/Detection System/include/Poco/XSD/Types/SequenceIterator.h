//
// SequenceIterator.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/SequenceIterator.h#3 $
//
// Library: XSD/Types
// Package: Iterator
// Module:  SequenceIterator
//
// Definition of the SequenceIterator class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_SequenceIterator_INCLUDED
#define XSDTypes_SequenceIterator_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/OrderIteratorImpl.h"
#include "Poco/XSD/Types/OrderIterator.h"
#include <vector>


namespace Poco {
namespace XSD {
namespace Types {


class Sequence;


class XSDTypes_API SequenceIterator: public OrderIteratorImpl
	/// An iterator for iterating over Sequence content groups.
{
public:
	SequenceIterator(const Sequence& data);
		/// Creates the SequenceIterator.

	SequenceIterator(const std::vector<OrderIterator>& its, UInt32 min);
		/// Creates the SequenceIterator.

	virtual ~SequenceIterator();
		/// Destroys the SequenceIterator.

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

	UInt32 _min;
	UInt32 _max;
	Iterators _vecIt;
	Iterators::size_type _curPos;
	mutable std::set<std::string> _next;
	mutable bool _dirtyFlag;
	static const Iterators::size_type NO_POS;
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_SequenceIterator_INCLUDED
