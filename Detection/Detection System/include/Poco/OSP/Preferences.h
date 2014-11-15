//
// Preferences.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/Preferences.h#1 $
//
// Library: OSP
// Package: PreferencesService
// Module:  Preferences
//
// Definition of the Preferences class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_Preferences_INCLUDED
#define OSP_Preferences_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/PreferencesEvent.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/AutoPtr.h"
#include "Poco/BasicEvent.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace OSP {


class OSP_API Preferences: public Poco::Util::AbstractConfiguration
	/// Preferences objects are used by bundles to access their
	/// stored preferences.
{
public:
	typedef Poco::AutoPtr<Preferences> Ptr;
	typedef const Ptr ConstPtr;
	
	Poco::BasicEvent<PreferencesEvent> propertyChanged;
		/// Fired whenever a property is about to be changed.
	
	Preferences(const std::string& path);
		/// Creates the Preferences, using the given path.
		
	void save();
		/// Saves the preferences to the file system.

protected:
	bool getRaw(const std::string& key, std::string& value) const;
	void setRaw(const std::string& key, const std::string& value);		
	void enumerate(const std::string& key, Keys& range) const;
	void removeRaw(const std::string& key);
	~Preferences();

private:
	Preferences();
	
	std::string _path;
	Poco::Util::PropertyFileConfiguration* _pConfig;
	bool _dirty;
	mutable Poco::FastMutex _mutex;
};


} } // namespace Poco::OSP


#endif // OSP_Preferences_INCLUDED
