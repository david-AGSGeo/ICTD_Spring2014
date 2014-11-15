//
// AttributeGroupRef.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/AttributeGroupRef.h#2 $
//
// Library: XSD/Types
// Package: XSDAttributes
// Module:  AttributeGroupRef
//
// Definition of the AttributeGroupRef class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_AttributeGroupRef_INCLUDED
#define XSDTypes_AttributeGroupRef_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/QName.h"
#include "Poco/XSD/Types/AbstractAttributeGroup.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API AttributeGroupRef: public AbstractAttributeGroup
	/// This class represents a reference to a group of attributes.
{
public:
	typedef AutoPtr<AttributeGroupRef> Ptr;

	AttributeGroupRef(const std::string& id, const QName& ref);
		/// Creates the AttributeGroupRef.

	virtual ~AttributeGroupRef();
		/// Destroys the AttributeGroupRef.

	// AbstractAttributeGroup
	const AbstractAttributeGroup::Attributes& getAttributes() const;
	bool hasAnyAttribute() const;
	AnyAttribute::Ptr getAny() const;
	void add(AttributeContent::Ptr ptr);
	void fixup();
	void accept(Visitor& v) const;

private:
	QName _ref;
	const AbstractAttributeGroup* _pGroup;
};


//
// inlines
//
inline void AttributeGroupRef::add(AttributeContent::Ptr ptr)
{
	throw Poco::NoPermissionException("Adding attributes to refs not allowed!");
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_AttributeGroupRef_INCLUDED
