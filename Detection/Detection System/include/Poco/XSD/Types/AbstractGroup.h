//
// AbstractGroup.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/AbstractGroup.h#2 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  AbstractGroup
//
// Definition of the AbstractGroup class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_AbstractGroup_INCLUDED
#define XSDTypes_AbstractGroup_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/CollectionContent.h"
#include "Poco/XSD/Types/Order.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API AbstractGroup: public CollectionContent
{
public:
	typedef AutoPtr<AbstractGroup> Ptr;

	AbstractGroup(const std::string& id, Poco::UInt32 minOcc, Poco::UInt32 maxOcc);
		/// Creates the AbstractGroup.

	virtual ~AbstractGroup();
		/// Destroys the AbstractGroup.

	virtual void fixup() = 0;
		/// Resolves references to point to the actual types

	virtual Order::Ptr getChild() const = 0;
		/// Returns the child of the group

	virtual const std::string& name() const = 0;
		/// Returns the non-empty name

	OrderIterator iterator() const;
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_AbstractGroup_INCLUDED
