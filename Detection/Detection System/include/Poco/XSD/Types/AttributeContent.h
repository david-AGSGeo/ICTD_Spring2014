//
// AttributeContent.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/AttributeContent.h#2 $
//
// Library: XSD/Types
// Package: XSDAttributes
// Module:  AttributeContent
//
// Definition of the AttributeContent class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_AttributeGroupContent_INCLUDED
#define XSDTypes_AttributeGroupContent_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AnnotatedObject.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API AttributeContent: public AnnotatedObject
	/// The base class for Attribute and AttributeGroup classes.
{
public:
	typedef AutoPtr<AttributeContent> Ptr;

	AttributeContent(const std::string& id, const std::string& name);
		/// Creates the AttributeContent.

	virtual ~AttributeContent();
		/// Destroys the AttributeContent.

	virtual const std::string& name() const;
		/// The name of the attribute. Only set for root level attributes.

	virtual bool isAny() const = 0;
		/// Returns true for the any attribute.

	virtual void fixup() = 0;
		/// Resolves all references to types and AttributeRefs

private:
	std::string _name;
};


//
// inlines
//
inline const std::string& AttributeContent::name() const
{
	return _name;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_AttributeGroupContent_INCLUDED
