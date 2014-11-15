//
// BundleFile.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/BundleFile.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleFile
//
// Definition of the BundleFile class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_BundleFile_INCLUDED
#define OSP_BundleFile_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/BundleStorage.h"


namespace Poco {
namespace Zip {
class ZipArchive;
} } // namespace Poco::Zip


namespace Poco {
namespace OSP {


class OSP_API BundleFile: public BundleStorage
	/// BundleFile implements the BundleStorage interface
	/// for bundles stored in Zip files.
{
public:
	BundleFile(const std::string& path);
		/// Creates the BundleFile, using the
		/// given path which must specify a Zip file.

	// BundleStorage
	std::istream* getResource(const std::string& path) const;
	void list(const std::string& path, std::vector<std::string>& files) const;		
	std::string path() const;

protected:
	bool isSubdirectoryOf(const std::string& dir, const std::string& parent) const;
		/// Returns true iff dir is a subdirectory of parent.

	~BundleFile();
		/// Destroys the BundleDirectory.

private:
	BundleFile();
	BundleFile(const BundleFile&);
	BundleFile& operator = (const BundleFile&);
	
	std::string _path;
	Poco::Zip::ZipArchive* _pArchive;
};


} } // namespace Poco::OSP


#endif // OSP_BundleFile_INCLUDED
