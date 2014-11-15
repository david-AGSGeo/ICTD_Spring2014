//
// ServerConnection.h
//
// $Id: //poco/1.4/RemotingNG/TCP/include/Poco/RemotingNG/TCP/ServerConnection.h#3 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  ServerConnection
//
// Definition of the ServerConnection class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_TCP_ServerConnection_INCLUDED
#define RemotingNG_TCP_ServerConnection_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Logger.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class RemotingNGTCP_API ServerConnection: public Poco::Net::TCPServerConnection
	/// The TCPServerConnection for handling incoming RemotingNG TCP Transport connections.
{
public:
	explicit ServerConnection(Listener::Ptr pListener, const Poco::Net::StreamSocket& socket);
		/// Creates a ServerConnectionFactory using the given Listener instance.

	~ServerConnection();
		/// Destroys the ServerConnectionFactory.

	// TCPServerConnection
	void run();

private:
	Listener::Ptr _pListener;
	Poco::Logger& _logger;
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_ServerConnection_INCLUDED
