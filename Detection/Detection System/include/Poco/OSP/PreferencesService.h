//
// PreferencesService.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/PreferencesService.h#2 $
//
// Library: OSP
// Package: PreferencesService
// Module:  PreferencesService
//
// Definition of the PreferencesService class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_PreferencesService_INCLUDED
#define OSP_PreferencesService_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/Preferences.h"
#include "Poco/OSP/Configuration.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Path.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace OSP {


class OSP_API PreferencesService: public Service
	/// The PreferencesService provides an easy way for a bundle
	/// or service to retrieve and store configuration information.
	/// It also gives a bundle or service read-only access to
	/// the global application configuration.
	///
	/// The service name of the PreferencesService
	/// is "osp.core.preferences".
{
public:
	typedef Poco::AutoPtr<PreferencesService> Ptr;
	typedef const Ptr ConstPtr;

	PreferencesService(const Poco::Path& persistencyDir, Poco::Util::AbstractConfiguration* pGlobalConfig);
		/// Creates the PreferencesService, usign the given global 
		/// configuration.

	Preferences::Ptr preferences(const std::string& bundleOrServiceID);
		/// Returns the preferences object for the given bundle or
		/// service. A bundle should specify its symbolic name as
		/// ID. A service should specify its service name.

	Configuration::Ptr configuration();
		/// Returns the global application configuration.

	static const std::string SERVICE_NAME;

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;

protected:
	~PreferencesService();
		/// Destroys the PreferencesService.

private:
	typedef std::map<std::string, Preferences::Ptr> PrefsMap;
	
	Poco::Path         _path;
	Configuration::Ptr _pConfig;
	PrefsMap           _prefsMap;
	Poco::FastMutex    _mutex;
};


} } // namespace Poco::OSP


#endif // OSP_PreferencesService_INCLUDED
