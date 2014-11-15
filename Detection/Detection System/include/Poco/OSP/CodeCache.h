//
// CodeCache.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/CodeCache.h#1 $
//
// Library: OSP
// Package: Util
// Module:  CodeCache
//
// Definition of the CodeCache class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_CodeCache_INCLUDED
#define OSP_CodeCache_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Path.h"


namespace Poco {
namespace OSP {


class OSP_API CodeCache
	/// CodeCache is a utility class that manages the
	/// code cache directory where the shared libraries
	/// of resolved bundles are kept.
{
public:
	CodeCache(const std::string& path);
		/// Creates the CodeCache, using the
		/// given path.
		///
		/// If the cache directory does not exist,
		/// it is created.

	~CodeCache();
		/// Destroys the CodeCache.

	bool hasLibrary(const std::string& name);
		/// Returns true if a library with the given name
		/// is stored in the code cache.
		///
		/// The name must not contain an filename extension.
		
	void installLibrary(const std::string& name, std::istream& istr);
		/// Installs the library with the given name, which
		/// must not contain an extension, into the code cache.
		
	void uninstallLibrary(const std::string& name);
		/// Removes the library with the given name from
		/// the cache directory.
		
	std::string pathFor(const std::string& name);
		/// Returns the full path for the library with the given name.	
		
	void clear();
		/// Clears the cache by removing the entire
		/// cache directory.	
		
private:
	CodeCache();
	CodeCache(const CodeCache&);
	CodeCache& operator = (const CodeCache&);
	
	Poco::Path _path;
};


} } // namespace Poco::OSP


#endif // OSP_CodeCache_INCLUDED
