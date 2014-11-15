//
// ElementIterator.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/ElementIterator.h#2 $
//
// Library: XSD/Types
// Package: Iterator
// Module:  ElementIterator
//
// Definition of the ElementIterator class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_ElementIterator_INCLUDED
#define XSDTypes_ElementIterator_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/OrderIteratorImpl.h"


namespace Poco {
namespace XSD {
namespace Types {


class Element;


class XSDTypes_API ElementIterator: public OrderIteratorImpl
	/// An iterator for iterating over an Element's content.
{
public:
	ElementIterator(Element& elem);
		/// Creates the ElementIterator.

	virtual ~ElementIterator();
		/// Destroys the ElementIterator.

	// OrderIteratorImpl
	OrderContent::Ptr next(const std::string& name);
	const std::set<std::string>& validNexts() const;
	bool validNext(const std::string& name) const;
	bool end() const;
	void close();
	bool canClose() const;
	void reset();

private:
	Element* _pElem;
	UInt32 _cnt;
	mutable std::set<std::string> _next;
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_ElementIterator_INCLUDED
