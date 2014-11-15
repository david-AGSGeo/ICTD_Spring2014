//
// BundleLoader.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/BundleLoader.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleLoader
//
// Definition of the BundleLoader class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_BundleLoader_INCLUDED
#define OSP_BundleLoader_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleFactory.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleContextFactory.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleManifest.h"
#include "Poco/OSP/LanguageTag.h"
#include "Poco/ClassLoader.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#if defined(POCO_OSP_STATIC)
#include "Poco/Instantiator.h"
#endif
#include <map>
#include <set>
#include <vector>


namespace Poco {
namespace OSP {


class CodeCache;


class OSP_API BundleLoader
	/// The BundleLoader is used internally by the framework
	/// to manage Bundle and BundleContext objects, and to
	/// load shared libraries containing BundleActivator classes.
	///
	/// The BundleLoader uses the logger osp.core.BundleLoader to
	/// write diagnostic messages.
{
public:
	typedef Poco::ClassLoader<BundleActivator> ActivatorClassLoader;
	typedef Poco::SharedPtr<ActivatorClassLoader> ActivatorClassLoaderPtr;

	struct BundleInfo
	{
		Bundle::Ptr             pBundle;
		BundleContext::Ptr      pContext;
		ActivatorClassLoaderPtr pClassLoader;
	};
	typedef std::map<std::string, BundleInfo> BundleMap;
	typedef std::set<Bundle*> BundleSet;
	
	BundleLoader(CodeCache& codeCache, BundleFactory::Ptr pBundleFactory, BundleContextFactory::Ptr pBundleContextFactory);
		/// Creates the BundleLoader.

	~BundleLoader();
		/// Destroys the BundleLoader.
		
	Bundle::ConstPtr findBundle(const std::string& symbolicName) const;
		/// Returns the Bundle object for the bundle with
		/// the given symbolic name, or NULL if the
		/// bundle does not exist.

	Bundle::ConstPtr findBundle(int id) const;
		/// Returns the Bundle object for the bundle with
		/// the given ID, or NULL if the
		/// bundle does not exist.
		
	Bundle::Ptr createBundle(const std::string& path);
		/// Loads a bundle from the given path.
		///
		/// A new Bundle object is created for the bundle,
		/// and the Bundle's state is BUNDLE_INSTALLED.
		/// The bundle is not added to the bundle map.
	
	Bundle::Ptr loadBundle(const std::string& path);
		/// Loads a bundle from the given path.
		/// A new Bundle object is created for the bundle,
		/// and the Bundle's state is BUNDLE_INSTALLED.
		///
		/// The bundle is then added to the bundle map.
		/// If another version of the same bundle is already
		/// loaded, a BundleVersionConflictException is thrown.
		///
		/// Returns the new Bundle object.

	void loadBundle(Bundle::Ptr pBundle);
		/// Loads the given Bundle, which must have
		/// been created with createBundle().
		///
		/// The bundle is then added to the bundle map.
		/// If another version of the same bundle is already
		/// loaded, a BundleVersionConflictException is thrown.

	void unloadBundle(Bundle::Ptr pBundle);
		/// Unloads the given bundle.
		///
		/// The bundle is removed from the bundle map and
		/// its activator library, if loaded, is unloaded.

	void listBundles(std::vector<Bundle::Ptr>& bundles) const;
		/// Fills the given vector with all bundles
		/// known to the loader.
		
	void resolveAllBundles();
		/// Resolves all bundles.
		///
		/// If a bundle cannot be resolved, an error is logged
		/// and the loader will continue to resolve other bundles.
	
	void startAllBundles();
		/// Starts all bundles, ordered by their run level.
		/// If a bundle has the lazyStart property set,
		/// that bundle won't be started unless another bundle
		/// requires it.
		///
		/// Bundles with lower run levels will be started
		/// before bundles with higher run levels.
		///
		/// If a bundle cannot be started, an error will be
		/// logged, and the loader will continue to load
		/// other bundles.
	
	void stopAllBundles();
		/// Stops all bundles.
		///
		/// Bundles are stopped in order of their depedencies.
		
	void unloadAllBundles();
		/// Stops and unloads all bundles.

	BundleEvents& events();
		/// Returns a reference to the BundleEvents
		/// object.
		
	const std::string& osName() const;
		/// Returns the name of the operating system.
	
	const std::string& osArchitecture() const;
		/// Returns the name of the hardware architecture.
		
	std::string pathForLibrary(const std::string& libraryName);
		/// Returns the full path for the library with the given
		/// libraryName. If libraryName is the empty string,
		/// return the path to the code cache directory.
		
	BundleContext::Ptr contextForBundle(Bundle::ConstPtr pBundle) const;
		/// Returns the BundleContext for the given bundle.

	int nextBundleId();
		/// Returns a new unique bundle ID.

#if defined(POCO_OSP_STATIC)
	typedef Poco::AbstractInstantiator<BundleActivator> BundleActivatorFactory;

	void registerBundleActivator(const std::string& className, BundleActivatorFactory* pFactory);
		/// Registers a factory object for the BundleActivator with the given class name.
		/// The BundleLoader takes ownership of the factory and deletes it in its destructor.
		///
		/// This is only available if OSP is compiled with the preprocessor symbol
		/// POCO_OSP_STATIC defined. In this case, dynamic loading of BundleActivator instances
		/// from shared libraries is disabled, and all BundleActivator instances will be
		/// created using statically registered factories.
		///
		/// This is only useful on platforms that do not support loading of shared libraries
		/// (such as the iPhone, where, although shared libraries are supported by the system,
		/// application distribution policies disallow loading of shared libraries).
		
	template <class BA>
	void registerBundleActivator(const std::string& className)
	{
		registerBundleActivator(className, new Poco::Instantiator<BA, Poco::OSP::BundleActivator>());
	}
#endif

protected:
	void resolveBundle(Bundle* pBundle);
		/// Resolves the given bundle.
		
	void startBundle(Bundle* pBundle);
		/// Starts the given bundle.
		
	void stopBundle(Bundle* pBundle);
		/// Stops the given bundle.
		
	void uninstallBundle(Bundle* pBundle);
		/// Uninstalls the given bundle.
	
	void resolveDependency(Bundle* pBundle, const BundleManifest::Dependency& dependency);
		/// Resolves a single dependency of a bundle.
	
	bool isResolving(Bundle* pBundle) const;
		/// Returns true iff the given bundle
		/// is currently being resolved.
		
	void startDependencies(Bundle* pBundle);
		/// Starts all bundles that the given
		/// bundle requires to run.
		
	BundleActivator* loadActivator(BundleInfo& bundleInfo);
		/// Loads the activator for the given bundle,
		/// unless it has already been loaded.

	void unloadActivator(BundleInfo& bundleInfo);
		/// Unloads the activator for the given bundle.
		
	void installLibraries(Bundle* pBundle);
		/// Copies all shared libraries in the bundle
		/// (for the current platform) to the code cache.
		
	void uninstallLibraries(Bundle* pBundle);
		/// Removes all shared libraries belonging
		/// to the given bundle from the code cache.

	const std::string& libraryNameFor(Bundle* pBundle);
		/// Returns the library name for the library
		/// containing the activator for the given bundle.
		
	void listLibraries(Bundle* pBundle, std::vector<std::string>& list);
		/// Lists all shared libraries contained in the bundle
		/// for the current platform.
		
	void sortBundles(std::vector<Bundle::Ptr>& bundles) const;
		/// Sorts all bundles topologically, based on
		/// their dependencies.
		///
		/// The bundles are sorted in such a way so that
		/// bundles can be safely stopped in the resulting
		/// order.

	std::string libraryPathFor(Bundle* pBundle);
		/// Returns the library path for the library
		/// containing the activator for the given bundle.

	static void makeValidFileName(std::string& name);
		/// Replaces all non alphanumeric characters in name
		/// with an underscore.

private:
	BundleLoader();
	BundleLoader(const BundleLoader&);
	BundleLoader& operator = (const BundleLoader&);

	typedef std::map<int, Bundle::Ptr> BundleIdMap;
	
	int                       _nextBundleId;
	CodeCache&                _codeCache;
	BundleFactory::Ptr        _pBundleFactory;
	BundleContextFactory::Ptr _pBundleContextFactory;
	BundleEvents              _events;
	std::string               _osName;
	std::string               _osArch;
	BundleMap                 _bundles;
	BundleIdMap               _bundleIds;
	BundleSet                 _resolvingBundles;
	Poco::Logger&             _logger;
	mutable Poco::Mutex       _mutex;

#if defined(POCO_OSP_STATIC)
	typedef std::map<std::string, BundleActivatorFactory*> BundleActivatorFactoryMap;

	BundleActivatorFactoryMap _bundleActivatorFactories;
#endif
	
	friend class Bundle;
};


//
// inline
//
inline BundleEvents& BundleLoader::events()
{
	return _events;
}


inline const std::string& BundleLoader::osName() const
{
	return _osName;
}


inline const std::string& BundleLoader::osArchitecture() const
{
	return _osArch;
}


} } // namespace Poco::OSP


#endif // OSP_BundleLoader_INCLUDED
