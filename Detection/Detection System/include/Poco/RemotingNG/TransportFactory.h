//
// TransportFactory.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/TransportFactory.h#1 $
//
// Library: RemotingNG
// Package: Transport
// Module:  TransportFactory
//
// Definition of the TransportFactory class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_TransportFactory_INCLUDED
#define RemotingNG_TransportFactory_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace RemotingNG {


class Transport;


class RemotingNG_API TransportFactory: public Poco::RefCountedObject
	/// A TransportFactory creates Transport objects.
{
public:
	typedef Poco::AutoPtr<TransportFactory> Ptr;

	TransportFactory();
		/// Creates a TransportFactory.

	virtual ~TransportFactory();
		/// Destroys the TransportFactory.

	virtual Transport* createTransport() = 0;
		/// Returns an unconnected Transport.
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_TransportFactory_INCLUDED
