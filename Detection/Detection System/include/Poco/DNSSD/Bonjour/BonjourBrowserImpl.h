//
// BonjourBrowserImpl.h
//
// $Id: //poco/1.4/DNSSD/Bonjour/include/Poco/DNSSD/Bonjour/BonjourBrowserImpl.h#3 $
//
// Library: DNSSD/Bonjour
// Package: Implementation
// Module:  BonjourBrowserImpl
//
// Definition of the BonjourBrowserImpl class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef DNSSD_Bonjour_BonjourBrowserImpl_INCLUDED
#define DNSSD_Bonjour_BonjourBrowserImpl_INCLUDED


#include "Poco/DNSSD/Bonjour/Bonjour.h"
#include "Poco/DNSSD/DNSSDBrowser.h"
#include "Poco/Timestamp.h"
#include "Poco/Event.h"
#include <map>
#include <dns_sd.h>


namespace Poco {
namespace DNSSD {
namespace Bonjour {


class EventLoop;


class POCO_DNSSD_Bonjour_API BonjourBrowserImpl: public DNSSDBrowser
	/// The DNSSDBrowser implementation for Bonjour.
{
public:
	BonjourBrowserImpl(EventLoop& eventLoop);
		/// Creates the BonjourBrowserImpl.
		
	~BonjourBrowserImpl();
		/// Destroys the BonjourBrowserImpl.
		
	// DNSSDBrowser
	BrowseHandle browse(const std::string& regType, const std::string& domain, int options, Poco::Int32 networkInterface);
	BrowseHandle resolve(const Service& service, int options);
	BrowseHandle enumerateBrowseDomains(Poco::Int32 networkInterface);
	BrowseHandle enumerateRegistrationDomains(Poco::Int32 networkInterface);
	BrowseHandle queryRecord(const std::string& name, Poco::UInt16 type, Poco::UInt16 clazz, int options, Poco::Int32 networkInterface);
	BrowseHandle resolveHost(const std::string& host, int options, Poco::Int32 networkInterface);
	void cancel(BrowseHandle& browseHandle);
	
	// Implementation
	void onBrowseReply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char* serviceName,  const char* regtype, const char* domain);
	void onResolveReply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char* fullName, const char* host, uint16_t port, uint16_t txtLen, const unsigned char* txtRecord);
	void onEnumerateBrowseDomainsReply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char* replyDomain);
	void onEnumerateRegistrationDomainsReply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char* replyDomain);
    void onQueryRecordReply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char* fullName, uint16_t rrtype, uint16_t rrclass, uint16_t rdlen, const void* rdata, uint32_t ttl);
	void onResolveHostReply(DNSServiceRef sdRef, DNSServiceFlags flags, uint32_t interfaceIndex, DNSServiceErrorType errorCode, const char* hostname, const struct sockaddr* address, uint32_t ttl);

protected:
	static void parseTXTRecord(Poco::UInt16 length, const void* data, Service::Properties& properties);

private:
	typedef std::map<DNSServiceRef, Service> ServiceMap;
	EventLoop& _eventLoop;
	ServiceMap _serviceMap;
};


} } } // namespace Poco::DNSSD::Bonjour


#endif // DNSSD_Bonjour_BonjourBrowserImpl_INCLUDED