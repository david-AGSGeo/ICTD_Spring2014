//
// OSPSubsystem.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/OSPSubsystem.h#2 $
//
// Library: OSP
// Package: Util
// Module:  OSPSubsystem
//
// Definition of the OSPSubsystem class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_OSPSubsystem_INCLUDED
#define OSP_OSPSubsystem_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/SystemEvents.h"
#include "Poco/Util/Subsystem.h"


namespace Poco {
namespace OSP {


class CodeCache;
class ServiceRegistry;
class BundleLoader;
class BundleRepository;


class OSP_API OSPSubsystem: public Poco::Util::Subsystem
	/// This subsystem implementation sets up the
	/// OSP runtime environment, including
	/// BundleLoader, CodeCache and ServiceRegistry.
	///
	/// It also defines the "clean" command line option,
	/// which forces the code cache to be cleared, and
	/// the "bundles" command line option which allows
	/// for specification of additional bundle repositories.
	///
	/// The following configuration properties are used:
	///   - osp.bundleRepository: list of directories containing bundles
	///                           (defaults to ${application.dir}bundles)
	///   - osp.codeCache:        location of code cache directory
	///                           (defaults to ${application.dir}codeCache)
	///   - osp.language:         language used for localization (overrides
	///                           the system default)
	///   - osp.data              the directory where temporary and persistent
	///                           data for bundles is stored (defaults to
	///                           ${application.dir}data)
	///
	/// The following configuration properties are set:
	///   - osp.version: OSP Version from osp.core bundle (only if osp.core bundle is present)
	///   - osp.osname:  name of operating system
	///   - osp.osarch:  hardware architecture identifier
{
public:
	OSPSubsystem();
		/// Creates the OSPSubsystem.

	~OSPSubsystem();
		/// Destroys the OSPSubsystem.
		
	BundleLoader& bundleLoader();
		/// Returns a reference to the bundle loader.
		
	void cancelInit();
		/// Cancels initialization.	
		
	ServiceRegistry& serviceRegistry();
		/// Returns a reference to the service registry.
	
	// Subsystem
	void initialize(Poco::Util::Application& app);		
	void uninitialize();
	void defineOptions(Poco::Util::OptionSet& options);
	const char* name() const;

protected:
	void handleClear(const std::string& name, const std::string& value);
	void handleBundles(const std::string& name, const std::string& value);

	virtual void loadBundles(Poco::Util::Application& app);
		/// Loads all bundles from all known bundle repositories.

	virtual void startBundles(Poco::Util::Application& app);
		/// Resolves and starts all loaded bundles.
	
private:
	CodeCache*        _pCodeCache;
	ServiceRegistry*  _pServiceRegistry;
	BundleLoader*     _pBundleLoader;
	BundleRepository* _pBundleRepository;
	SystemEvents      _systemEvents;
	bool              _clearCache;
	bool              _cancelInit;
	std::string       _bundles;
};


//
// inlines
//
inline BundleLoader& OSPSubsystem::bundleLoader()
{
	poco_check_ptr(_pBundleLoader);
	
	return *_pBundleLoader;
}

	
inline ServiceRegistry& OSPSubsystem::serviceRegistry()
{
	poco_check_ptr (_pServiceRegistry);
	
	return *_pServiceRegistry;
}


} } // namespace Poco::OSP


#endif // OSP_OSPSubsystem_INCLUDED
