//
// BundleStreamFactory.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/BundleStreamFactory.h#1 $
//
// Library: OSP
// Package: Util
// Module:  BundleStreamFactory
//
// Definition of the BundleStreamFactory class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_BundleStreamFactory_INCLUDED
#define OSP_BundleStreamFactory_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/URIStreamFactory.h"


namespace Poco {
namespace OSP {


class BundleLoader;


class OSP_API BundleStreamFactory: public Poco::URIStreamFactory
	/// An implementation of the URIStreamFactory interface
	/// that handles Bundle (bndl) URIs for accessing
	/// resources stored in bundles.
	///
	/// The format of a bndl URI is:
	///     bndl://<symbolic-name>/<resource-path>
	///
	/// Example: bndl://com.appinf.osp.sample-bundle/sample.txt
{
public:
	BundleStreamFactory(BundleLoader& loader);
		/// Creates the BundleStreamFactory, using
		/// the given bundle loader.

	~BundleStreamFactory();
		/// Destroys the BundleStreamFactory.

	virtual std::istream* open(const Poco::URI& uri);
		/// Creates and opens a stream for the given bndl URI.
		
	static void registerFactory(BundleLoader& loader);
		/// Registers the BundleStreamFactory with the
		/// default URIStreamOpener instance.	

private:
	BundleStreamFactory();

	BundleLoader& _loader;
};


} } // namespace Poco::OSP


#endif // OSP_BundleStreamFactory_INCLUDED
