//
// SimpleTypeInheritance.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/SimpleTypeInheritance.h#3 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  SimpleTypeInheritance
//
// Definition of the SimpleTypeInheritance class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_SimpleTypeInheritance_INCLUDED
#define XSDTypes_SimpleTypeInheritance_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AnnotatedObject.h"
#include <vector>


namespace Poco {
namespace XSD {
namespace Types {


class Type;


class XSDTypes_API SimpleTypeInheritance: public AnnotatedObject
	/// Describes how a simple type extends from another one.
{
public:
	typedef AutoPtr<SimpleTypeInheritance> Ptr;

	SimpleTypeInheritance();
		/// Creates the SimpleTypeInheritance.

	SimpleTypeInheritance(const std::string& id);
		/// Creates the SimpleTypeInheritance.

	virtual ~SimpleTypeInheritance();
		/// Destroys the SimpleTypeInheritance.

	virtual const std::vector<const Type*>& types() const = 0;
		/// Returns the types that we inherit from. Will only contain more than one element for the union case.

	virtual void fixup() = 0;
		/// Replaces type references with the referenced type object.

	virtual bool isRestriction() const = 0;
		/// True if we inherit by restriction.

	virtual bool isList() const = 0;
		/// Inherit by list.

	virtual bool isUnion() const = 0;
		/// Inherit by union.
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_SimpleTypeInheritance_INCLUDED
