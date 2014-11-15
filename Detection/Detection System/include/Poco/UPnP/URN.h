//
// URN.h
//
// $Id: //poco/1.4/UPnP/include/Poco/UPnP/URN.h#2 $
//
// Library: UPnP
// Package: Core
// Module:  URN
//
// Definition of the URN class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_URN_INCLUDED
#define UPnP_URN_INCLUDED


#include "Poco/UPnP/UPnP.h"
#include "Poco/UUID.h"


namespace Poco {
namespace UPnP {


class UPnP_API URN
	/// A Uniform Resource Name, or URN, is a variant
	/// of an URI that stores a structured name used
	/// to identify an entity. In UPnP, URNs are used
	/// to identify devices, device types and service
	/// types, as well as SSDP notification types.
	///
	/// This class is used to create and parse the different
	/// kinds of URNs used by UPnP:
	///    - UUID-based URNs (uuid:<device-UUID>[...]), as used
	///      for USNs.
	///    - Root Device (upnp:rootdevice), for announcing
	///      a root device with SSDP.
	///    - URNs containing device or service name, type
	///      and version (urn:<domain-name>:<name>:<type>:<version>)
	///    - Service IDs (urn:upnp-org:serviceId:serviceID), as used
	///      in XML device descriptions.
	///
	/// URN supports full value semantics, including comparison operators.
	/// Note, however, that copying URN values may be expensive.
	///
	/// Note: some device manufacturers use strings like
	/// "uuid:UPnP_Thomson TG585 v7-1_00-1F-9F-E9-24-14" for their
	/// UUIDs. Since these are not valid UUIDs we don't use the Poco::UUID
	/// class for storing them.

{
public:
	static const std::string URN_SCHEME;
	static const std::string UUID_SCHEME;
	static const std::string UPNP_SCHEME;
	static const std::string DEVICE;
	static const std::string SERVICE;
	static const std::string SERVICEID;
	static const std::string ROOTDEVICE;
	static const std::string UPNP_ORG;
	static const std::string SCHEMAS_UPNP_ORG;

	enum Type
	{
		URN_UUID = 0,    /// uuid:<device-UUID>
		URN_ROOT_DEVICE, /// upnp:rootdevice
		URN_DEVICE,      /// urn:<domain-name>:device:<type>:<version>
		URN_SERVICE,     /// urn:<domain-name>:service:<type>:<version>
		URN_SERVICEID    /// urn:upnp-org:serviceId:<serviceId>
	};
	
	URN();
		/// Creates an empty URN.

	URN(Type type);
		/// Creates a root device URN.
		///
		/// Note: type must always be URN_ROOT_DEVICE.

	URN(const URN& urn);
		/// Creates a URN by copying another one.

	explicit URN(const std::string& urn);
		/// Creates a URN by parsing the given string.

	explicit URN(const Poco::UUID& uuid);
		/// Creates a URN of type URN_UUID, using the given UUID.

	URN(Type type, const std::string& name, const std::string& version);
		/// Creates a URN of type URN_DEVICE or URN_SERVICE, using the
		/// given name and version. The domain is set to "schemas-upnp-org".
		///
		/// Type must be URN_DEVICE or URN_SERVICE.

	URN(Type type, const std::string& domain, const std::string& name, const std::string& version);
		/// Creates a URN of type URN_DEVICE or URN_SERVICE, using the
		/// given domain, name and version.
		///
		/// Type must be URN_DEVICE or URN_SERVICE.

	URN(Type type, const std::string& serviceId);
		/// Creates a URN of type URN_SERVICEID using the given serviceId.
		///
		/// Type must be URN_SERVICEID.

	~URN();
		/// Destroys the URN.

	void swap(URN& urn);
		/// Exchanges the URN with another one.

	URN& operator = (const URN& urn);
		/// Assignment operator.
		
	URN& operator = (const std::string& urn);
		/// Parses an URN from the given string and assigns it.

	URN::Type type() const;
		/// Returns the type of the URN.

	const std::string& scheme() const;
		/// Returns the URN scheme part, which will
		/// be one of "uuid", "upnp" or "urn".		

	const std::string& uuid() const;
		/// Returns the UUID value for a URN of type URN_UUID.
		/// Throws an exception if the URN has a wrong type.

	const std::string& domain() const;
		/// Returns the URN domain part (e.g. "schemas-upnp-org").

	const std::string& name() const;
		/// Returns the name of the service/device.

	const std::string& version() const;
		/// Returns the version string (<major>.<minor>).
		///
		/// A version is set for types URN_DEVICE and URN_SERVICE only.

	int minorVersion() const;
		/// Returns the minor version number. 
		///
		/// A version is set for types URN_DEVICE and URN_SERVICE only.

	int majorVersion() const;
		/// Returns the major version number.
		///
		/// A version is set for types URN_DEVICE and URN_SERVICE only.

	const std::string& toString() const;
		/// Converts a URN to a string.
		
	void clear();
		/// Clears the URN.

	bool empty() const;
		/// Returns true iff the URN is empty.

	bool operator == (const URN& urn) const;
	bool operator != (const URN& urn) const;
	bool operator >  (const URN& urn) const;
	bool operator >= (const URN& urn) const;
	bool operator <  (const URN& urn) const;
	bool operator <= (const URN& urn) const;

	bool operator == (const std::string& urn) const;
	bool operator != (const std::string& urn) const;
	bool operator >  (const std::string& urn) const;
	bool operator >= (const std::string& urn) const;
	bool operator <  (const std::string& urn) const;
	bool operator <= (const std::string& urn) const;

	bool matches(const URN& urn) const;
		/// Compares type, scheme, domain and name and checks whether
		/// this URN's version is greater or equal to urn's version.

	bool matches(const std::string& urn) const;
		/// Compares type, scheme, domain and name and checks whether
		/// this URN's version is greater or equal to urn's version.
	
private:
	void parse(const std::string& val);
	void parseVersion();
	void format();

private:
	Type        _type;
	std::string _scheme;
	std::string _uuid;
	std::string _domain;
	std::string _name;
	std::string _version;
	int         _majorVersion;
	int         _minorVersion;
	std::string _asString;
};


//
// inlines
//
inline URN::Type URN::type() const
{
	return _type;
}


inline const std::string& URN::scheme() const
{
	return _scheme;
}


inline const std::string& URN::uuid() const
{
	return _uuid;
}


inline const std::string& URN::domain() const
{
	return _domain;
}


inline const std::string& URN::name() const
{
	return _name;
}


inline const std::string& URN::version() const
{
	return _version;
}


inline int URN::minorVersion() const
{
	return _minorVersion;
}


inline int URN::majorVersion() const
{
	return _majorVersion;
}


inline const std::string& URN::toString() const
{
	return _asString;
}


inline bool URN::empty() const
{
	return _scheme.empty();
}


inline bool URN::operator == (const URN& urn) const
{
	return _asString == urn._asString;
}


inline bool URN::operator != (const URN& urn) const
{
	return _asString != urn._asString;
}


inline bool URN::operator > (const URN& urn) const
{
	return _asString > urn._asString;
}


inline bool URN::operator >= (const URN& urn) const
{
	return _asString >= urn._asString;
}


inline bool URN::operator < (const URN& urn) const
{
	return _asString < urn._asString;
}


inline bool URN::operator <= (const URN& urn) const
{
	return _asString <= urn._asString;
}

inline bool URN::operator == (const std::string& urn) const
{
	return _asString == urn;
}


inline bool URN::operator != (const std::string& urn) const
{
	return _asString != urn;
}


inline bool URN::operator > (const std::string& urn) const
{
	return _asString > urn;
}


inline bool URN::operator >= (const std::string& urn) const
{
	return _asString >= urn;
}


inline bool URN::operator < (const std::string& urn) const
{
	return _asString < urn;
}


inline bool URN::operator <= (const std::string& urn) const
{
	return _asString <= urn;
}


inline void swap(URN& urn1, URN& urn2)
{
	urn1.swap(urn2);
}


} } // namespace Poco::UPnP


#endif // UPnP_URN_INCLUDED
