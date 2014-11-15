//
// RequestHandler.h
//
// $Id: //poco/1.4/UPnP/SOAP/include/Poco/UPnP/SOAP/RequestHandler.h#1 $
//
// Library: UPnP/SOAP
// Package: SOAP
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


#ifndef UPnP_SOAP_RequestHandler_INCLUDED
#define UPnP_SOAP_RequestHandler_INCLUDED


#include "Poco/UPnP/SOAP/SOAP.h"
#include "Poco/UPnP/SOAP/Listener.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Logger.h"


namespace Poco {
namespace UPnP {
namespace SOAP {


class UPnPSOAP_API RequestHandler: public Poco::Net::HTTPRequestHandler
	/// The RemotingNG RequestHandler implementation for UPnP Control
	/// using SOAP.
{
public:
	RequestHandler(Listener& listener);
		/// Creates a RequestHandler, using the given Listener.

	~RequestHandler();
		/// Destroys the RequestHandler.

	// Poco::Net::HTTPRequestHandler
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

protected:
	static const std::string M_POST;
	static const std::string MAN;
	static const std::string EXT;
	static const std::string SOAPACTION;
	static const std::string EMPTY;
	
private:
	RequestHandler();

	Listener& _listener;
	Poco::Logger& _logger;
};


} } } // namespace Poco::UPnP::SOAP


#endif // UPnP_SOAP_RequestHandler_INCLUDED
