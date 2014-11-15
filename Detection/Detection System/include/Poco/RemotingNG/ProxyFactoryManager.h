//
// ProxyFactoryManager.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/ProxyFactoryManager.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  ProxyFactoryManager
//
// Definition of the ProxyFactoryManager class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_ProxyFactoryManager_INCLUDED
#define RemotingNG_ProxyFactoryManager_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/ProxyFactory.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace RemotingNG {


class ProxyFactory;


class RemotingNG_API ProxyFactoryManager
	/// A ProxyFactoryManager manages all existing ProxyFactory objects in the system.
{
public:
	ProxyFactoryManager();
		/// Creates a ProxyFactoryManager.

	~ProxyFactoryManager();
		/// Destroys the ProxyFactoryManager.

	void registerProxyFactory(const Identifiable::TypeId& tid, ProxyFactory::Ptr pProxyFactory);
		/// Registers a ProxyFactory under the given TypeId if no factory exists yet.

	void unregisterProxyFactory(const Identifiable::TypeId& tid);
		/// Unregisters the ProxyFactory for the given TypeId if one exists.

	Proxy* createProxy(const Identifiable::TypeId& tid, const RemotingNG::Identifiable::ObjectId& oid, const std::string& protocol, const std::string& uri) const;
		/// Creates a Proxy for the given TypeId and ObjectId, and connects it to the endpoint specified 
		/// by the given URI, using the Transport for the given protocol.

	Proxy* createProxy(const Identifiable::TypeId& tid, const RemotingNG::Identifiable::ObjectId& oid) const;
		/// Creates an unconnected Proxy for the given TypeId and ObjectId.

private:
	typedef std::map<Identifiable::TypeId, ProxyFactory::Ptr> Factories;

	Factories _factories;
	mutable Poco::FastMutex _mutex;
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_ProxyFactoryManager_INCLUDED
