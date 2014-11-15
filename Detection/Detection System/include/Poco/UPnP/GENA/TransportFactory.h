//
// TransportFactory.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/TransportFactory.h#2 $
//
// Library: UPnP/GENA
// Package: GENA
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


#ifndef UPnP_GENA_TransportFactory_INCLUDED
#define UPnP_GENA_TransportFactory_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/Timespan.h"
#include "Poco/RemotingNG/TransportFactory.h"


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API TransportFactory: public Poco::RemotingNG::TransportFactory
	/// The TransportFactory for UPnP GENA Transport objects.
{
public:
	TransportFactory();
		/// Creates a TransportFactory using default settings (no persistent
		/// connections, HTTP timeout 10 seconds).
		
	TransportFactory(const Poco::Timespan& timeout, bool keepAlive, const Poco::Timespan& keepAliveTimeout);
		/// Creates a TransportFactory using the given settings.

	~TransportFactory();
		/// Destroys the TransportFactory.

	Poco::RemotingNG::Transport* createTransport();

	static void registerFactory();
		/// Helper function to register the factory with the manager,
		/// using default settings (no persistent
		/// connections, HTTP timeout 10 seconds).

	static void registerFactory(const Poco::Timespan& timeout, bool keepAlive, const Poco::Timespan& keepAliveTimeout);
		/// Helper function to register the factory with the manager,
		/// using the given settings.

	static void unregisterFactory();
		/// Helper function to unregister the factory with the manager.

	enum
	{
		HTTP_DEFAULT_TIMEOUT = 10000000,
		HTTP_DEFAULT_KEEPALIVE_TIMEOUT = 8000000
	};

private:
	Poco::Timespan _timeout;
	bool _keepAlive;
	Poco::Timespan _keepAliveTimeout;
};


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_TransportFactory_INCLUDED
