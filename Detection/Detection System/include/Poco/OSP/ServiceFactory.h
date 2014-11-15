//
// ServiceFactory.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/ServiceFactory.h#1 $
//
// Library: OSP
// Package: Service
// Module:  ServiceFactory
//
// Definition of the ServiceFactory class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_ServiceFactory_INCLUDED
#define OSP_ServiceFactory_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Service.h"


namespace Poco {
namespace OSP {


class OSP_API ServiceFactory: public Service
	/// A ServiceFactory is a special Service that, as its name
	/// implies, acts as a factory for Service objects.
	///
	/// If a subclass of ServiceFactory is registered as a
	/// service, the factory will be used to create a new
	/// instance of the service whenever the service is
	/// requested from the ServiceRegistry.
{
public:
	virtual Service::Ptr createService() = 0;
		/// Creates and returns a new instance of a Service.
		
	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;
		
protected:
	ServiceFactory();
		/// Creates the ServiceFactory.

	~ServiceFactory();
		/// Destroys the ServiceFactory.
};


} } // namespace Poco::OSP


#endif // OSP_ServiceFactory_INCLUDED
