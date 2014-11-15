//
// RequestHandler.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/RequestHandler.h#1 $
//
// Library: UPnP/GENA
// Package: GENA
// Module:  RequestHandler
//
// Definition of the RequestHandler class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_GENA_RequestHandler_INCLUDED
#define UPnP_GENA_RequestHandler_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/UPnP/GENA/Listener.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Logger.h"


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API RequestHandler: public Poco::Net::HTTPRequestHandler
	/// The RemotingNG RequestHandler implementation for UPnP Eventing
	/// using GENA.
	///
	/// The request handler handles both event notifications and
	/// subscriptions.
{
public:
	RequestHandler(Listener& listener);
		/// Creates a RequestHandler, using the given Listener.

	~RequestHandler();
		/// Destroys the RequestHandler.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	void handleNotify(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void handleSubscribe(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void handleUnsubscribe(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void sendResponse(Poco::Net::HTTPServerResponse& response, Poco::Net::HTTPResponse::HTTPStatus status);
	
private:
	RequestHandler();

	Listener& _listener;
	Poco::Logger& _logger;
};


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_RequestHandler_INCLUDED
