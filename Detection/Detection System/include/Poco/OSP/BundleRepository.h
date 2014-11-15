//
// BundleRepository.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/BundleRepository.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleRepository
//
// Definition of the BundleRepository class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_BundleRepository_INCLUDED
#define OSP_BundleRepository_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Logger.h"
#include <vector>
#include <map>
#include <istream>


namespace Poco {
namespace OSP {


class BundleLoader;


class OSP_API BundleRepository
	/// The bundle repository manages one or more directories
	/// in the file system containing bundles.
	///
	/// The BundleRepository uses the Logger "osp.core.BundleRepository"
	/// to log non-fatal errors.
{
public:
	BundleRepository(const std::string& path, BundleLoader& loader);
		/// Creates the BundleRepository, using the given
		/// path and BundleLoader.
		///
		/// The path argument may contain a single path, or a list
		/// of paths, separated by the platform's path separator
		/// (':' on Unix platforms, ';' on Windows).
		///
		/// The first path given in a list is said to be the
		/// primary path. Other paths are secondary paths.
		///
		/// Paths may either reference a directory containing
		/// bundles, or a bundle file (or bundle directory with
		/// the extension ".bndl") directly. 
		///
		/// Paths may contain Glob expressions (see Poco::Glob).

	~BundleRepository();
		/// Destroys the BundleRepository.

	void loadBundles();
		/// Loads all available bundles, using the BundleLoader.
		///
		/// If two or more versions of a bundle are found,
		/// the latest version of the bundle is loaded
		/// and a warning message is logged.
		
	Bundle::Ptr installBundle(std::istream& istr);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the primary path.
		///
		/// The bundle's file name in the bundle repository
		/// will be "<symbolicName>_<version>.bndl".
		///
		/// Returns the newly installed bundle, which will
		/// be in INSTALLED state.

	Bundle::Ptr installBundle(std::istream& istr, const std::string& replaceBundle);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the primary path.
		///
		/// If a bundle with the symbolic name given in replaceBundle
		/// exists, the bundle is stopped and uninstalled before
		/// the new bundle is installed.
		///
		/// The bundle's file name in the bundle repository
		/// will be "<symbolicName>_<version>.bndl".
		///
		/// Returns the newly installed bundle, which will
		/// be in INSTALLED state.

protected:
	typedef std::map<std::string, Bundle::Ptr> BundleMap;
	
	void loadBundles(const std::string& path, BundleMap& bundles);
		/// Loads all availble bundles from the given path.

	void loadBundle(const std::string& path, BundleMap& bundles);
		/// Loads a bundle from the given path.

	Bundle::Ptr installBundle(std::istream& istr, const std::string& replaceBundle, const std::string& path);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the given path.

	std::string tempBundleName() const;
		/// Returns a temporary bundle name in the
		/// form "tmp.bundle-nnnn".
		
	void removeBundle(const std::string& symbolicName);
		/// Removes the bundle, by first stopping (if necessary),
		/// and then uninstalling it.
		
private:
	BundleRepository();
	BundleRepository(const BundleRepository&);
	BundleRepository& operator = (const BundleRepository&);
	
	std::vector<std::string> _paths;
	BundleLoader&            _loader;
	Poco::Logger&            _logger;
};


} } // namespace Poco::OSP


#endif // OSP_BundleRepository_INCLUDED
