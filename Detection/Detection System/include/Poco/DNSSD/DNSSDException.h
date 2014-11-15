//
// DNSSDException.h
//
// $Id: //poco/1.4/DNSSD/include/Poco/DNSSD/DNSSDException.h#1 $
//
// Library: DNSSD
// Package: Core
// Module:  DNSSDException
//
// Definition of the DNSSDException class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef DNSSD_DNSSDException_INCLUDED
#define DNSSD_DNSSDException_INCLUDED


#include "Poco/DNSSD/DNSSD.h"
#include "Poco/Exception.h"


namespace Poco {
namespace DNSSD {


POCO_DECLARE_EXCEPTION(POCO_DNSSD_API, DNSSDException, Poco::RuntimeException)


} } // namespace Poco::DNSSD


#endif // DNSSD_DNSSDException_INCLUDED
