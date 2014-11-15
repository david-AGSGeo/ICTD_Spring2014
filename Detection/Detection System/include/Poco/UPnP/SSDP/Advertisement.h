//
// Advertisement.h
//
// $Id: //poco/1.4/UPnP/SSDP/include/Poco/UPnP/SSDP/Advertisement.h#1 $
//
// Library: UPnP/SSDP
// Package: SSDP
// Module:  Advertisement
//
// Definition of the Advertisement class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SSDP_Advertisement_INCLUDED
#define UPnP_SSDP_Advertisement_INCLUDED


#include "Poco/UPnP/SSDP/SSDP.h"
#include "Poco/UUID.h"
#include "Poco/UPnP/URN.h"
#include "Poco/UPnP/UniqueServiceName.h"
#include "Poco/Net/NameValueCollection.h"
#include "Poco/Timestamp.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace UPnP {
namespace SSDP {


class UPnP_SSDP_API Advertisement: public Poco::RefCountedObject
	/// An Advertisement contains all data transferred
	/// via a SSDP Discovery message.
	///
	/// Advertisement objects are used with the SSDPResponder
	/// and the SSDPBrowser classes.
	///
	/// In addition to UUID, URN, location and lifetime an Advertisement
	/// can hold an arbitrary number of attributes. These can provide
	/// additional information about an Advertisement, such as
	/// the server ID of the device sending the advertisement, as
	/// well as the sender's IP address. Attributes can also be used
	/// by an application to add application-specific data to an
	/// Advertisement.
{
public:
	typedef Poco::AutoPtr<Advertisement> Ptr;

	enum Type
	{
		AD_ROOT_DEVICE,
		AD_DEVICE,
		AD_DEVICE_TYPE,
		AD_SERVICE_TYPE
	};
	
	enum
	{
		DEFAULT_LIFETIME = 120 /// Default lifetime of advertisements in seconds.
	};
	
	Advertisement(Type type, const Poco::UUID& deviceUUID, const std::string& location, int lifetime = DEFAULT_LIFETIME);
		/// Creates an Advertisement for the given root device or embedded device with the given 
		/// XML device description location (URI) and lifetime in seconds.
		///
		/// Type must be ANNOUNCE_ROOT_DEVICE or ANNOUNCE_DEVICE.
		
	Advertisement(const Poco::UUID& deviceUUID, const URN& deviceOrServiceURN, const std::string& location, int lifetime = DEFAULT_LIFETIME);
		/// Creates an Advertisement for a device type or service type.
		
	Advertisement(const std::string& notificationType, const std::string& uniqueServiceName, const std::string& location, int lifetime = DEFAULT_LIFETIME);
		/// Creates an Advertisement for the given notificationType, uniqueServiceName and with the given timestamp and lifetime (in seconds).

	Advertisement(const URN& notificationType, const UniqueServiceName& uniqueServiceName, const std::string& location, int lifetime = DEFAULT_LIFETIME);
		/// Creates an Advertisement for the given notificationType, uniqueServiceName and with the given timestamp and lifetime (in seconds).

	~Advertisement();
		/// Destroys the Advertisement.
		
	Type type() const;
		/// Returns the type of the Advertisement.

	const URN& notificationType() const;
		/// Returns the notification type.
		
	const UniqueServiceName& uniqueServiceName() const;
		/// Returns the unique service name.

	const std::string& location() const;
		/// Returns the URI for obtaining the device or service description.
		
	Poco::Timestamp lastSeen() const;
		/// Returns the time the Advertisement was last seen.
		
	int lifetime() const;
		/// Returns the lifetime, in seconds, of the Advertisement.
		
	void renew();
		/// Renews the Advertisement by updating the lastSeen variable.
		
	bool expired() const;
		/// Returns true iff the Advertisement has expired.
		
	Poco::Net::NameValueCollection& attributes();
		/// Returns the Advertisement's attributes.

	const Poco::Net::NameValueCollection& attributes() const;
		/// Returns the Advertisement's attributes.
		
protected:
	void determineType();
	
private:
	Advertisement();
	
	Type _type;
	URN _notificationType;
	UniqueServiceName _uniqueServiceName;
	std::string _location;
	Poco::Timestamp _lastSeen;
	int _lifetime;
	Poco::Net::NameValueCollection _attributes;
};


//
// inlines
//
inline Advertisement::Type Advertisement::type() const
{
	return _type;
}


inline const URN& Advertisement::notificationType() const
{
	return _notificationType;
}


inline const UniqueServiceName& Advertisement::uniqueServiceName() const
{
	return _uniqueServiceName;
}


inline const std::string& Advertisement::location() const
{
	return _location;
}


inline Poco::Timestamp Advertisement::lastSeen() const
{
	return _lastSeen;
}


inline int Advertisement::lifetime() const
{
	return _lifetime;
}


inline void Advertisement::renew()
{
	_lastSeen.update();
}


inline bool Advertisement::expired() const
{
	return _lastSeen.isElapsed(Poco::Timestamp::TimeDiff(_lifetime)*1000000);
}


inline Poco::Net::NameValueCollection& Advertisement::attributes()
{
	return _attributes;
}


inline const Poco::Net::NameValueCollection& Advertisement::attributes() const
{
	return _attributes;
}


} } } // namespace Poco::UPnP::SSDP


#endif // UPnP_SSDP_Advertisement_INCLUDED
