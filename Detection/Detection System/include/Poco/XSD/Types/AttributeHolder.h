//
// AttributeHolder.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/AttributeHolder.h#2 $
//
// Library: XSD/Types
// Package: XSDAttributes
// Module:  AttributeHolder
//
// Definition of the AttributeHolder class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_AttributeHolder_INCLUDED
#define XSDTypes_AttributeHolder_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AttributeContent.h"
#include <vector>


namespace Poco {
namespace XSD {
namespace Types {


class SimpleType;


class XSDTypes_API AttributeHolder
	/// Interface for classes storing attributes.
{
public:
	AttributeHolder();
		/// Creates the AttributeHolder.

	virtual ~AttributeHolder();
		/// Destroys the AttributeHolder.

	virtual const std::vector<AttributeContent::Ptr>& attributeContent() const = 0;
		/// Returns the attributes defined for the complex type.

	virtual void addAttribute(AttributeContent::Ptr pAttr) = 0;
		/// Adds the attribute to the set.

	virtual bool hasAnyAttribute() const = 0;
		/// Returns true if the any attribute is allowed.
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_AttributeHolder_INCLUDED
