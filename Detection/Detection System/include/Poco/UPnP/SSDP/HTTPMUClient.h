//
// HTTPMUClient.h
//
// $Id: //poco/1.4/UPnP/SSDP/include/Poco/UPnP/SSDP/HTTPMUClient.h#1 $
//
// Library: UPnP/SSDP
// Package: HTTPMU
// Module:  HTTPMUClient
//
// Definition of the HTTPMUClient class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SSDP_HTTPMUClient_INCLUDED
#define UPnP_SSDP_HTTPMUClient_INCLUDED


#include "Poco/UPnP/SSDP/SSDP.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Buffer.h"


namespace Poco {
namespace UPnP {
namespace SSDP {


class UPnP_SSDP_API HTTPMUClient
	/// HTTPMUClient is used to send HTTPMU messages
	/// (requests and responses) to other hosts or
	/// multicast groups.
	///
	/// The specification for HTTPMU can be found in the
	/// (expired) Internet Draft "Multicast and Unicast
	/// UDP HTTP Messages" 
	/// <http://tools.ietf.org/id/draft-goland-http-udp-00.txt>.
	///
	/// Note that HTTPMU does not support request-reply messages in the same way
	/// as HTTP. All HTTPMU messages are one-way. The correlation between requests
	/// and replies must be implemented by an application specific mechanism.
	/// If a client wants to receive a response message from a server,
	/// it has to set up its own HTTPMUServer instance.
	///
	/// Note that the client supports a maximum message size (defined by
	/// MAX_MESSAGE_SIZE). Actual message size should be smaller to avoid
	/// packet fragmentation, which decreases performance and increases
	/// the probability of packet loss.
{
public:
	enum
	{
		MAX_MESSAGE_SIZE = 4096
	};
	
	HTTPMUClient(const Poco::Net::DatagramSocket& socket);
		/// Creates the HTTPMUClient, using the given socket.
		///
		/// For sending multicast messages, a Poco::Net::MulticastSocket
		/// must be given.
		
	~HTTPMUClient();
		/// Destroys the HTTPMUClient.

	void sendRequest(const Poco::Net::SocketAddress& destinationAddress, Poco::Net::HTTPRequest& request);
		/// Sends the given request to the host (or multicast group) given by destinationAddress.
		///
		/// A Host header will be added to the request if none has been set.

	void sendRequest(const Poco::Net::SocketAddress& destinationAddress, Poco::Net::HTTPRequest& request, const std::string& requestBody);
		/// Sends the given request to the host (or multicast group) given by destinationAddress.
		///
		/// A Host header will be added to the request if none has been set.
		///
		/// The given requestBody can be empty. If a non-empty requestBody is given, the request's
		/// content length field should be set accordingly.

	void sendResponse(const Poco::Net::SocketAddress& destinationAddress, Poco::Net::HTTPResponse& response);
		/// Sends the given response to the host (or multicast group) given by destinationAddress.
		///
		/// A Date header will be added to the response if none has been set.

	void sendResponse(const Poco::Net::SocketAddress& destinationAddress, Poco::Net::HTTPResponse& response, const std::string& responseBody);
		/// Sends the given response to the host (or multicast group) given by destinationAddress.
		///
		/// A Date header will be added to the response if none has been set.
		///
		/// The given responseBody can be empty. If a non-empty responseBody is given, the response's
		/// content length field should be set accordingly.

protected:
	void sendMessage(const Poco::Net::SocketAddress& destinationAddress, const Poco::Net::HTTPMessage& message, const std::string& messageBody);

private:
	HTTPMUClient();
	HTTPMUClient(const HTTPMUClient&);
	HTTPMUClient& operator = (const HTTPMUClient&);
	
	Poco::Net::DatagramSocket _socket;
	Poco::Buffer<char> _buffer;
};


} } } // namespace Poco::UPnP::SSDP


#endif // UPnP_SSDP_HTTPMUClient_INCLUDED
