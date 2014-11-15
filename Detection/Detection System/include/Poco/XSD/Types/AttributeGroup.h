//
// AttributeGroup.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/AttributeGroup.h#3 $
//
// Library: XSD/Types
// Package: XSDAttributes
// Module:  AttributeGroup
//
// Definition of the AttributeGroup class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_AttributeGroup_INCLUDED
#define XSDTypes_AttributeGroup_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/AbstractAttributeGroup.h"
#include "Poco/XSD/Types/AttributeContent.h"
#include "Poco/XSD/Types/AnyAttribute.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API AttributeGroup: public AbstractAttributeGroup
	/// This class represents a group of attributes.
{
public:
	typedef AutoPtr<AttributeGroup> Ptr;

	AttributeGroup(const std::string& id, const std::string& name);
		/// Creates the AttributeGroup.

	virtual ~AttributeGroup();
		/// Destroys the AttributeGroup.

	void add(AttributeContent::Ptr ptr);
		/// Adds an attribute content child to the group.
		///
		/// Throws an exception if a child with that name already exists.

	const AbstractAttributeGroup::Attributes& getAttributes() const;
		/// Returns all the children.

	bool hasAnyAttribute() const;
		/// Returns true if the any attribute is set.

	AnyAttribute::Ptr getAny() const;
		/// Returns the any attribute.

	// AbstractAttributeGroup
	void fixup();
	void accept(Visitor& v) const;

private:
	AbstractAttributeGroup::Attributes _children;
	AnyAttribute::Ptr _pAny;
	std::vector<AttributeContent::Ptr> _tmp;
};


//
// inlines
//
inline const AbstractAttributeGroup::Attributes& AttributeGroup::getAttributes() const
{
	return _children;
}


inline bool AttributeGroup::hasAnyAttribute() const
{
	return _pAny.get() != 0;
}


inline AnyAttribute::Ptr AttributeGroup::getAny() const
{
	return _pAny;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_AttributeGroup_INCLUDED
