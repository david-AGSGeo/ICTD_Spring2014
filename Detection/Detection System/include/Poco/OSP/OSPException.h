//
// OSPException.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/OSPException.h#1 $
//
// Library: OSP
// Package: Core
// Module:  OSPException
//
// Definition of the OSPException class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_OSPException_INCLUDED
#define OSP_OSPException_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Exception.h"


namespace Poco {
namespace OSP {


POCO_DECLARE_EXCEPTION(OSP_API, OSPException, Poco::RuntimeException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleException, OSPException)
POCO_DECLARE_EXCEPTION(OSP_API, ManifestException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleStateException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleVersionConflictException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleLoadException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleResolveException, BundleException)


} } // namespace Poco::OSP


#endif // OSP_OSPException_INCLUDED
