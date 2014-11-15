//
// Visitable.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/Visitable.h#2 $
//
// Library: XSD/Types
// Package: Visitor
// Module:  Visitable
//
// Definition of the Visitable class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_Visitable_INCLUDED
#define XSDTypes_Visitable_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/RefCountedObject.h"


namespace Poco {
namespace XSD {
namespace Types {


class Visitor;


class XSDTypes_API Visitable: public Poco::RefCountedObject
	/// Interface class Visitable, used to implement visitor pattern.
{
public:
	Visitable();
		/// Creates the Visitable.

	Visitable(const std::string& id);
		/// Creates the Visitable with the given ID.

	virtual ~Visitable();
		/// Destroys the Visitable.

	const std::string& id() const;
		/// Returns the id of the object

	virtual void accept(Visitor& v) const = 0;
		/// Implements the visitor pattern. Each subclass must implement it as
		/// v.visit(*this);

private:
	std::string _id;
};


//
// inlines
//
inline const std::string& Visitable::id() const
{
	return _id;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_Visitable_INCLUDED
