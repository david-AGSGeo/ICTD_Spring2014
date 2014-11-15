//
// Sequence.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/Sequence.h#3 $
//
// Library: XSD/Types
// Package: XSDTypes
// Module:  Sequence
//
// Definition of the Sequence class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_Sequence_INCLUDED
#define XSDTypes_Sequence_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"
#include "Poco/XSD/Types/Order.h"
#include <vector>


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API Sequence: public Order
	/// This class represents the XML Schema sequence element group.
{
public:
	typedef std::vector<OrderContent::Ptr> Content;
	typedef AutoPtr<Sequence> Ptr;

	Sequence(const std::string& id, Poco::UInt32 minOcc, Poco::UInt32 maxOcc);
		/// Creates the Sequence.

	virtual ~Sequence();
		/// Destroys the Sequence.

	void add(OrderContent::Ptr pChild);
		/// Adds a child to the end of the sequence

	void accept(Visitor& v) const;

	const Sequence::Content& getContent() const;
		/// Returns all the children in the sequence

	void fixup();

	OrderIterator iterator() const;

private:
	Sequence::Content _content;
};


//
// inlines
//
inline const Sequence::Content& Sequence::getContent() const
{
	return _content;
}


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_Sequence_INCLUDED
