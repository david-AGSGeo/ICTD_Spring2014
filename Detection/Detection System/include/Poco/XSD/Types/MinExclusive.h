//
// MinExclusive.h
//
// $Id: //poco/1.4/XSD/Types/include/Poco/XSD/Types/MinExclusive.h#1 $
//
// Library: XSD/Types
// Package: XSDFacets
// Module:  MinExclusive
//
// Definition of the MinExclusive class.
//
// Copyright (c) 2008-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef XSDTypes_MinExclusive_INCLUDED
#define XSDTypes_MinExclusive_INCLUDED


#include "Poco/XSD/Types/XSDTypes.h"


namespace Poco {
namespace XSD {
namespace Types {


class XSDTypes_API MinExclusive
	/// This class represents a minExclusive facet in an XML Schema.
{
public:
	MinExclusive();
		/// Creates the MinExclusive.

	virtual ~MinExclusive();
		/// Destroys the MinExclusive.

protected:

private:
};


} } } // namespace Poco::XSD::Types


#endif // XSDTypes_MinExclusive_INCLUDED
