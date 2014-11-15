//
// MinInclusive.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/MinInclusive.h#1 $
//
// Library: XSD/Types
// Package: XSDFacets
// Module:  MinInclusive
//
// Definition of the MinInclusive class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_MinInclusive_INCLUDED
#define XSDTypes_MinInclusive_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API MinInclusive
	/// This class represents a minInclusive facet in an XML Schema.
{
public:
	MinInclusive();
		/// Creates the MinInclusive.

	virtual ~MinInclusive();
		/// Destroys the MinInclusive.

protected:

private:
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_MinInclusive_INCLUDED
