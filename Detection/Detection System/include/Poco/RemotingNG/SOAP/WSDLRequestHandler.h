//
// WSDLRequestHandler.h
//
// $Id: //poco/1.4/RemotingNG/SOAP/include/Poco/RemotingNG/SOAP/WSDLRequestHandler.h#1 $
//
// Library: RemotingNG/SOAP
// Package: SOAP
// Module:  WSDLRequestHandler
//
// Definition of the WSDLRequestHandler class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_SOAP_SDLRequestHandler_INCLUDED
#define RemotingNG_SOAP_SDLRequestHandler_INCLUDED


#include "Poco/RemotingNG/SOAP/SOAP.h"
#include "Poco/Net/HTTPRequestHandler.h"


namespace Poco {
namespace RemotingNG {
namespace SOAP {


class RemotingNGSOAP_API WSDLRequestHandler: public Poco::Net::HTTPRequestHandler
	/// The WSDLRequestHandler serves WSDL files to clients.
{
public:
	WSDLRequestHandler(const std::string& wsdlPath);
		/// Creates the WSDLRequestHandler.
		///
		/// The path to the directory containing WSDL files 
		/// must be given as argument.

	~WSDLRequestHandler();
		/// Destroys the WSDLRequestHandler.

	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		/// Sends the WSDL file back to the client, or
		/// sends a 404 response if the requested WSDL file
		/// does not exist.

private:
	std::string _wsdlPath;
};


} } } // namespace Poco::RemotingNG::SOAP


#endif // RemotingNG_SOAP_SDLRequestHandler_INCLUDED
