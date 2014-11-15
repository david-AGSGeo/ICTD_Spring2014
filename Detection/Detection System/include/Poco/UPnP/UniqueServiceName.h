//
// UniqueServiceName.h
//
// $Id: //poco/1.4/UPnP/include/Poco/UPnP/UniqueServiceName.h#2 $
//
// Library: UPnP
// Package: Core
// Module:  UniqueServiceName
//
// Definition of the UniqueServiceName class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_UniqueServiceName_INCLUDED
#define UPnP_UniqueServiceName_INCLUDED


#include "Poco/UPnP/UPnP.h"
#include "Poco/UPnP/URN.h"


namespace Poco {
namespace UPnP {


class UPnP_API UniqueServiceName
	/// This class represents a UPnP Unique Service Name
	/// (USN), which is used to uniquely identify
	/// UPnP devices and services.
	///
	/// A USN consists of one or two URNs, the first one
	/// being a UUID URN, the second one a device or
	/// service name. The two URNs are separated by two
	/// colons.
	///
	/// Examples for valid USNs are:
	///   - uuid:C809DE34-C1F8-48A6-81B9-3450E560137D
	///   - uuid:C809DE34-C1F8-48A6-81B9-3450E560137D::upnp:rootdevice
	///   - uuid:C809DE34-C1F8-48A6-81B9-3450E560137D::urn:schemas-upnp-org:service:RenderingControl:2
	///
	/// This class is mostly intended for splitting USNs into
	/// their two parts, or creating USNs from their parts.
{
public:
	UniqueServiceName();
		/// Creates an empty UniqueServiceName.

	explicit UniqueServiceName(const std::string& usn);
		/// Creates the UniqueServiceName from a string.

	explicit UniqueServiceName(const Poco::UUID& uuid);
		/// Creates an UniqueServiceName for the given UUID.

	UniqueServiceName(const Poco::UUID& uuid, const URN& urn);
		/// Creates the UniqueServiceName for the given UUID and URN.

	UniqueServiceName(const std::string& uuid, const URN& urn);
		/// Creates the UniqueServiceName for the given UUID and URN.

	UniqueServiceName(const URN& uuid, const URN& urn);
		/// Creates the UniqueServiceName for the given UUID and URN.
		/// The uuid URN must be of type URN_UUID.

	~UniqueServiceName();
		/// Destroys the UniqueServiceName.

	std::string toString() const;
		/// Returns the UniqueServiceName as string.

	const std::string& uuid() const;
		/// Returns the UUID part of the UniqueServiceName.	

	const URN& urn() const;
		/// Returns the urn part of the UniqueServiceName

private:
	URN _uuid;
	URN _urn;
};


//
// inlines
//
inline const std::string& UniqueServiceName::uuid() const
{
	return _uuid.uuid();
}


inline const URN& UniqueServiceName::urn() const
{
	return _urn;
}


inline bool operator < (const UniqueServiceName& usn1, const UniqueServiceName& usn2)
{
	return usn1.toString() < usn2.toString();
}


} } // namespace Poco::UPnP


#endif // UPnP_UniqueServiceName_INCLUDED
