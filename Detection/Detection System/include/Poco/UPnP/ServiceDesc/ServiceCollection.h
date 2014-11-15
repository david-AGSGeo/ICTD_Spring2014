//
// ServiceCollection.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/ServiceCollection.h#4 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  ServiceCollection
//
// Definition of the ServiceCollection class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_ServiceCollection_INCLUDED
#define UPnP_ServiceDesc_ServiceCollection_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/Service.h"
#include "Poco/URI.h"
#include "Poco/Mutex.h"
#include <istream>
#include <map>


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API ServiceCollection
	/// A ServiceCollection contains all services a UPnP device provides.
{
public:
	struct ServiceInfo: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<ServiceInfo> Ptr;
		
		ServiceInfo(const std::string& st, Service::Ptr pS):
			serviceType(st),
			pService(pS)
		{
		}

		std::string  serviceType;
		Service::Ptr pService;
	};
	typedef std::map<std::string, ServiceInfo::Ptr> ServiceInfos;

	ServiceCollection();
		/// Creates the ServiceManager.

	~ServiceCollection();
		/// Destroys the ServiceManager.

	void addService(const std::string& serviceId, const std::string& serviceType, Service::Ptr pService);
		/// Adds a Service with the given serviceId and serviceType 
		/// to the collection of managed services.

	Service::Ptr loadService(const std::string& serviceId, const std::string& serviceType, std::istream& istr);
		/// Loads an XML service description for the service with
		/// the given serviceId and serviceType from the given input 
		/// stream and adds it to the collection.
		///
		/// Returns the Service if successful.

	Service::Ptr loadService(const std::string& serviceId, const std::string& serviceType, const Poco::URI& uri);
		/// Loads an XML service description for the service with
		/// the given serviceId and serviceType from the resource 
		/// identified by URI and adds it to the collection.
		///
		/// Uses the default Poco::URIStreamOpener class to read the service description
		/// from the given URI. In order to load service descriptions from a HTTP server,
		/// the Poco::Net::HTTPStreamFactory class must have been registered.
		///
		/// Returns the Service if successful.

	ServiceInfo::Ptr findService(const std::string& serviceId) const;
		/// Returns the Service object for the service with the given
		/// serviceId, or a null pointer if the service does not exist.
	
	ServiceInfos services() const;
		/// Returns a std::map mapping serviceIds to ServiceInfo objects.
	
	void clear();
		/// Removes all services.
	
private:
	ServiceCollection(const ServiceCollection&);
	ServiceCollection& operator = (const ServiceCollection&);

private:
	ServiceInfos _services;
	mutable Poco::FastMutex _mutex;
};


//
// inlines
//
inline ServiceCollection::ServiceInfos ServiceCollection::services() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	return _services;
}

} } } // namespace Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_ServiceCollection_INCLUDED
