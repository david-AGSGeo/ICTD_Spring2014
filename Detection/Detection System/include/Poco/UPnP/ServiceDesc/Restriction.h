//
// Restriction.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/Restriction.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  Restriction
//
// Definition of the Restriction class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_Restriction_INCLUDED
#define UPnP_ServiceDesc_Restriction_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API Restriction: public Poco::RefCountedObject
	/// This class represents a restriction for a StateVariable's value.
{
public:
	typedef Poco::AutoPtr<Restriction> Ptr;

	Restriction();
		/// Creates the Restriction.

	~Restriction();
		/// Destroys the Restriction.

	virtual bool valid(const std::string& val) const = 0;
		/// Returns true if the given value is valid with regards,
		/// to the Restriction.

	virtual std::string toString() const = 0;
		/// Returns a string representation of the Restriction.
};


} } } // Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_Restriction_INCLUDED
