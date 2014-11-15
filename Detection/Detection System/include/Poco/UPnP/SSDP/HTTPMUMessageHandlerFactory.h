//
// HTTPMUMessageHandlerFactory.h
//
// $Id: //poco/1.4/UPnP/SSDP/include/Poco/UPnP/SSDP/HTTPMUMessageHandlerFactory.h#1 $
//
// Library: UPnP/SSDP
// Package: HTTPMU
// Module:  HTTPMUMessageHandlerFactory
//
// Definition of the HTTPMUMessageHandlerFactory class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SSDP_HTTPMUMessageHandlerFactory_INCLUDED
#define UPnP_SSDP_HTTPMUMessageHandlerFactory_INCLUDED


#include "Poco/UPnP/SSDP/SSDP.h"
#include "Poco/UPnP/SSDP/HTTPMUMessageHandler.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace UPnP {
namespace SSDP {


class UPnP_SSDP_API HTTPMUMessageHandlerFactory
	/// A factory for HTTPMUMessageHandler objects. 
	/// Subclasses must override the createMessageHandler() method.
{
public:
	typedef Poco::SharedPtr<HTTPMUMessageHandlerFactory> Ptr;

	HTTPMUMessageHandlerFactory();
		/// Creates a HTTPMUMessageHandler.

	virtual ~HTTPMUMessageHandlerFactory();
		/// Destroys the HTTPMUMessageHandler.

	virtual HTTPMUMessageHandler* createMessageHandler(const Poco::Net::HTTPMessage& message) = 0;
		/// Must be overridden by sublasses.
		///
		/// Creates a new message handler for the given HTTPMU request.
		///
		/// The given message object will be an instance of Poco::Net::HTTPRequest or
		/// Poco::Net::HTTPResponse. This can be used to create a message-specific
		/// message handler object, if required.

private:
	HTTPMUMessageHandlerFactory(const HTTPMUMessageHandlerFactory&);
	HTTPMUMessageHandlerFactory& operator = (const HTTPMUMessageHandlerFactory&);
};


} } } // namespace Poco::UPnP::SSDP


#endif // UPnP_SSDP_HTTPMUMessageHandlerFactory_INCLUDED
