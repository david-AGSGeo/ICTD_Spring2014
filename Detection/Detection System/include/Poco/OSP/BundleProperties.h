//
// BundleProperties.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/BundleProperties.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleProperties
//
// Definition of the BundleProperties class.
//
// Copyright (c) 2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_BundleProperties_INCLUDED
#define OSP_BundleProperties_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Util/LayeredConfiguration.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace OSP {


class OSP_API BundleProperties: public Poco::Util::AbstractConfiguration
	/// A simple wrapper class around Poco::Util::LayeredConfiguration
	/// that adds thread safety.
{
public:
	typedef Poco::AutoPtr<BundleProperties> Ptr;

	BundleProperties();
		/// Creates the BundleProperties.

	void addProperties(Poco::Util::AbstractConfiguration* pConfig, bool shared);
		/// Adds a configuration.
		///
		/// If shared is true, increments the configuration's reference count.
		
	void addProperties(Poco::Util::AbstractConfiguration* pConfig, int priority, bool shared);
		/// Adds a configuration with the given priority.
		///
		/// If shared is true, increments the configuration's reference count.
		
	void removeProperties(Poco::Util::AbstractConfiguration* pConfig);
		/// Removes the given configuration.

protected:
	~BundleProperties();

	bool getRaw(const std::string& key, std::string& value) const;
	void setRaw(const std::string& key, const std::string& value);
	void enumerate(const std::string& key, Keys& range) const;
	void removeRaw(const std::string& key);

	Poco::Util::LayeredConfiguration* _pLayeredConfig;
	mutable Poco::FastMutex _mutex;
};


} } // namespace Poco::OSP


#endif // OSP_BundleProperties_INCLUDED
