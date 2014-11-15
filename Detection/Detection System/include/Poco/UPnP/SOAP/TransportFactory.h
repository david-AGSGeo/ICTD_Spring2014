//
// TransportFactory.h
//
// $Id: //poco/1.4/UPnP/SOAP/include/Poco/UPnP/SOAP/TransportFactory.h#1 $
//
// Library: UPnP/SOAP
// Package: SOAP
// Module:  TransportFactory
//
// Definition of the TransportFactory class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SOAP_TransportFactory_INCLUDED
#define UPnP_SOAP_TransportFactory_INCLUDED


#include "Poco/UPnP/SOAP/SOAP.h"
#include "Poco/RemotingNG/TransportFactory.h"


namespace Poco {
namespace UPnP {
namespace SOAP {


class UPnPSOAP_API TransportFactory: public Poco::RemotingNG::TransportFactory
	/// The TransportFactory for UPnP SOAP Transport objects.
{
public:
	TransportFactory(bool keepAlive = false);
		/// Creates a TransportFactory.

	~TransportFactory();
		/// Destroys the TransportFactory.

	Poco::RemotingNG::Transport* createTransport();

	static void registerFactory(bool keepAlive = false);
		/// Helper function to register the factory with the manager.

	static void unregisterFactory();
		/// Helper function to unregister the factory with the manager.

private:
	bool _keepAlive;
};


} } } // namespace Poco::UPnP::SOAP


#endif // UPnP_SOAP_TransportFactory_INCLUDED
