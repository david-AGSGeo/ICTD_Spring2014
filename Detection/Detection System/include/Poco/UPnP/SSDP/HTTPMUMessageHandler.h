//
// HTTPMUMessageHandler.h
//
// $Id: //poco/1.4/UPnP/SSDP/include/Poco/UPnP/SSDP/HTTPMUMessageHandler.h#1 $
//
// Library: UPnP/SSDP
// Package: HTTPMU
// Module:  HTTPMUMessageHandler
//
// Definition of the HTTPMUMessageHandler class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SSDP_HTTPMUMessageHandler_INCLUDED
#define UPnP_SSDP_HTTPMUMessageHandler_INCLUDED


#include "Poco/UPnP/SSDP/SSDP.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/SharedPtr.h"
#include <istream>


namespace Poco {
namespace UPnP {
namespace SSDP {


class UPnP_SSDP_API HTTPMUMessageHandler
	/// The abstract base class for message handlers created by HTTPMUServer.
	///
	/// Derived classes must override the handleRequest() and handleResponse() methods. 
	/// Furthermore, a HTTPMUMessageHandlerFactory must be provided.
	///
	/// Note that HTTPMU does not support request-reply messages in the same way
	/// as HTTP. All HTTPMU messages are one-way. The correlation between requests
	/// and replies must be implemented by an application specific mechanism.
	/// If a message handler wants to send a response message to a request, it
	/// has to do this by using a HTTPMUClient object.
	///
	/// In order to avoid delays when processing HTTPMU messages in the HTTPMUServer,
	/// the handleRequest() and handleResponse() methods should complete as soon
	/// as possible. Processing of incoming messages blocks while the message
	/// handler is handling a message.
{
public:
	typedef Poco::SharedPtr<HTTPMUMessageHandler> Ptr;

	HTTPMUMessageHandler();
		/// Creates a HTTPMUMessageHandler.

	virtual ~HTTPMUMessageHandler();
		/// Destroys the HTTPMUMessageHandler.

	virtual void handleRequest(const Poco::Net::HTTPRequest& request, const Poco::Net::SocketAddress& senderAddress, std::istream& requestStream) = 0;
		/// Handles the given request message.
		///
		/// The IP address and port number of the sender is 
		/// given in senderAddress.
		///
		/// The request body of the message (if present) can be read from requestStream.
		
	virtual void handleResponse(const Poco::Net::HTTPResponse& response, const Poco::Net::SocketAddress& senderAddress, std::istream& responseStream) = 0;
		/// Handles the given response message.
		///
		/// The IP address and port number of the sender is 
		/// given in senderAddress.
		///
		/// The response body of the message (if present) can be read from responseStream.

private:
	HTTPMUMessageHandler(const HTTPMUMessageHandler&);
	HTTPMUMessageHandler& operator = (const HTTPMUMessageHandler&);
};


} } } // namespace Poco::UPnP::SSDP


#endif // UPnP_SSDP_HTTPMUMessageHandler_INCLUDED
