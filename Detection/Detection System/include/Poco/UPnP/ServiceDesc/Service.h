//
// Service.h
//
// $Id: //poco/1.4/UPnP/ServiceDesc/include/Poco/UPnP/ServiceDesc/Service.h#2 $
//
// Library: UPnP/ServiceDesc
// Package: ServiceDesc
// Module:  Argument
//
// Definition of the Service class.
//
// Copyright (c) 2011-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_ServiceDesc_Service_INCLUDED
#define UPnP_ServiceDesc_Service_INCLUDED


#include "Poco/UPnP/ServiceDesc/ServiceDesc.h"
#include "Poco/UPnP/ServiceDesc/Action.h"
#include "Poco/UPnP/ServiceDesc/StateVariable.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include <vector>


namespace Poco {
namespace UPnP {
namespace ServiceDesc {


class UPnP_ServiceDesc_API Service: public Poco::RefCountedObject
	/// This class represents a UPnP service description consisting
	/// of Action and StateVariable objects.
{
public:
	typedef std::vector<StateVariable::Ptr> StateVariables;
	typedef std::vector<Action::Ptr> Actions;
	typedef Poco::AutoPtr<Service> Ptr;

	Service();
		/// Creates the Service.

	~Service();
		/// Destroys the Service.

	const Actions& actions() const;
		/// Returns a std::vector containing all Action objects 
		/// defined by the service.

	Actions& actions();
		/// Returns a std::vector containing all Action objects 
		/// defined by the service.

	const StateVariables& stateVariables() const;
		/// Returns a std::vector containing all StateVariable
		/// objects defined by the service.

	StateVariables& stateVariables();
		/// Returns a std::vector containing all StateVariable
		/// objects defined by the service.

	int majorVersion() const;
		/// Returns the major version of the UPnP Device Architecture
		/// supported by the device.

	int minorVersion() const;
		/// Returns the minor version of the UPnP Device Architecture
		/// supported by the device.
		
	std::string specVersion() const;
		/// Returns the version of the UPnP Device Architecture 
		/// supported by the device, formatted as string "<major>.<minor>".

protected:
	void setMajorVersion(int major);
		/// Sets the major version of the UPnP Device Architecture
		/// supported.

	void setMinorVersion(int minor);
		/// Sets the minor version of the UPnP Device Architecture
		/// supported.

private:
	Actions _actions;
	StateVariables _stateVariables;
	int _majorVersion;
	int _minorVersion;
	
	friend class ServiceContentHandler;
};


//
// inlines
//
inline const Service::Actions& Service::actions() const
{
	return _actions;
}


inline const Service::StateVariables& Service::stateVariables() const
{
	return _stateVariables;
}


inline Service::Actions& Service::actions()
{
	return _actions;
}


inline Service::StateVariables& Service::stateVariables()
{
	return _stateVariables;
}


inline int Service::majorVersion() const
{
	return _majorVersion;
}


inline void Service::setMajorVersion(int major)
{
	poco_assert (major > 0);
	_majorVersion = major;
}


inline int Service::minorVersion() const
{
	return _minorVersion;
}


inline void Service::setMinorVersion(int minor)
{
	poco_assert (minor >= 0);
	_minorVersion = minor;
}


} } } // namespace Poco::UPnP::ServiceDesc


#endif // UPnP_ServiceDesc_Service_INCLUDED
