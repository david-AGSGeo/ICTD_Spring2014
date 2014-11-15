//
// NoRestriction.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/NoRestriction.h#1 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  NoRestriction
//
// Definition of the NoRestriction class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_NoRestriction_INCLUDED
#define UPnP_ServiceDesc_NoRestriction_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/Restriction.h"


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API NoRestriction: public Restriction
	/// The NoRestriction doesn't restrict at all
{
public:
	typedef Poco::AutoPtr<NoRestriction> Ptr;

	NoRestriction();
		/// Creates the NoRestriction.

	~NoRestriction();
		/// Destroys the NoRestriction.

	// Restriction
	bool valid(const std::string& val) const;
	std::string toString() const;
};


} } } // Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_NoRestriction_INCLUDED
