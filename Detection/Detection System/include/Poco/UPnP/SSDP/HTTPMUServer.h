//
// HTTPMUServer.h
//
// $Id: //poco/1.4/UPnP/SSDP/include/Poco/UPnP/SSDP/HTTPMUServer.h#2 $
//
// Library: UPnP/SSDP
// Package: HTTPMU
// Module:  HTTPMUServer
//
// Definition of the HTTPMUServer class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SSDP_HTTPMUServer_INCLUDED
#define UPnP_SSDP_HTTPMUServer_INCLUDED


#include "Poco/UPnP/SSDP/SSDP.h"
#include "Poco/UPnP/SSDP/HTTPMUMessageHandlerFactory.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Activity.h"
#include <vector>


namespace Poco {
namespace UPnP {
namespace SSDP {


class UPnP_SSDP_API HTTPMUServer
	/// This class implements a simple server for the
	/// HTTPMU (HTTP over Multicast/UDP) protocol, as 
	/// used by the UPnP Simple Service Discovery Protocol
	/// (SSDP).
	///
	/// The specification for HTTPMU can be found in the
	/// (expired) Internet Draft "Multicast and Unicast
	/// UDP HTTP Messages" 
	/// <http://tools.ietf.org/id/draft-goland-http-udp-00.txt>.
	///
	/// Note that a HTTPMUServer may receive both request
	/// and response messages.
	///
	/// The server has an internal limit for the maximum 
	/// accepted message size, defined by MAX_MESSAGE_SIZE.
	/// In practice, messages should be much smaller than
	/// this limit to avoid packet fragmentation in the network.
	///
	/// The server can listen on multiple Poco::Net::DatagramSocket
	/// (or Poco::Net::MulticastSocket) instances simultaneously.
{
public:
	enum
	{
		MIN_MESSAGE_SIZE = 16,
		MAX_MESSAGE_SIZE = 4096,
		SELECT_TIMEOUT   = 100000
	};
	
	HTTPMUServer(HTTPMUMessageHandlerFactory::Ptr pFactory, const Poco::Net::DatagramSocket& socket);
		/// Creates a HTTPMUServer, using the given message handler factory
		/// and socket. The socket can also be a Poco::Net::MulticastSocket.

	HTTPMUServer(HTTPMUMessageHandlerFactory::Ptr pFactory, const Poco::Net::DatagramSocket& socket1, const Poco::Net::DatagramSocket& socket2);
		/// Creates a HTTPMUServer, using the given message handler factory
		/// and sockets. The sockets can also be Poco::Net::MulticastSocket instances.

	HTTPMUServer(HTTPMUMessageHandlerFactory::Ptr pFactory, const std::vector<Poco::Net::DatagramSocket>& sockets);
		/// Creates a HTTPMUServer, using the given message handler factory
		/// and sockets. The socket can also be a Poco::Net::MulticastSocket.

	~HTTPMUServer();
		/// Destroys the HTTPMUServer.

	void start();
		/// Starts the server. A new thread will be created that waits for 
		/// and processes incoming messages.
		
	void stop();
		/// Stops the server.
		///
		/// No new messages will be accepted. Already received messages 
		/// will be processed to completion.
		///
		/// Once the server is stopped, it cannot be restarted.

protected:
	void handleMessages();

private:
	HTTPMUServer();
	HTTPMUServer(const HTTPMUServer&);
	HTTPMUServer& operator = (const HTTPMUServer&);
	
	HTTPMUMessageHandlerFactory::Ptr _pFactory;
	std::vector<Poco::Net::DatagramSocket> _sockets;
	Poco::Activity<HTTPMUServer> _handleMessages;
};


} } } // namespace Poco::UPnP::SSDP


#endif // UPnP_SSDP_HTTPMUServer_INCLUDED
