//
// TransportFactory.h
//
// $Id: //poco/1.4/RemotingNG/TCP/include/Poco/RemotingNG/TCP/TransportFactory.h#2 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  TransportFactory
//
// Definition of the TransportFactory class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_TCP_TransportFactory_INCLUDED
#define RemotingNG_TCP_TransportFactory_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/RemotingNG/TransportFactory.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class ConnectionManager;


class RemotingNGTCP_API TransportFactory: public Poco::RemotingNG::TransportFactory
	/// The TransportFactory for RemotingNG TCP Transport objects.
{
public:
	TransportFactory();
		/// Creates a TransportFactory using the default ConnectionManager instance.
		
	explicit TransportFactory(ConnectionManager& connectionManager);
		/// Creates a TransportFactory using the given ConnectionManager instance.

	~TransportFactory();
		/// Destroys the TransportFactory.

	// TransportFactory
	Poco::RemotingNG::Transport* createTransport();

	// Helpers
	static void registerFactory();
		/// Helper function to register the factory with the TransportFactoryManager.

	static void registerFactory(ConnectionManager& connectionManager);
		/// Helper function to register the factory with the TransportFactoryManager,
		/// using a specific ConnectionManager instance.

	static void unregisterFactory();
		/// Helper function to unregister the factory with the manager.
		
private:
	ConnectionManager& _connectionManager;
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_TransportFactory_INCLUDED
