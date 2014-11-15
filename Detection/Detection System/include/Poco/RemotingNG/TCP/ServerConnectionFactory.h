//
// ServerConnectionFactory.h
//
// $Id: //poco/1.4/RemotingNG/TCP/include/Poco/RemotingNG/TCP/ServerConnectionFactory.h#3 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  ServerConnectionFactory
//
// Definition of the ServerConnectionFactory class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_TCP_ServerConnectionFactory_INCLUDED
#define RemotingNG_TCP_ServerConnectionFactory_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/Net/TCPServerConnectionFactory.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class RemotingNGTCP_API ServerConnectionFactory: public Poco::Net::TCPServerConnectionFactory
	/// The TCPServerConnectionFactory for RemotingNG TCP Transport connections.
{
public:
	explicit ServerConnectionFactory(Listener::Ptr pListener);
		/// Creates a ServerConnectionFactory using the given Listener instance.

	~ServerConnectionFactory();
		/// Destroys the ServerConnectionFactory.

	// TCPServerConnectionFactory
	Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket);

private:
	Listener::Ptr _pListener;
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_ServerConnectionFactory_INCLUDED
