//
// Listener.h
//
// $Id: //poco/1.4/UPnP/SOAP/include/Poco/UPnP/SOAP/Listener.h#1 $
//
// Library: UPnP/SOAP
// Package: SOAP
// Module:  Listener
//
// Definition of the Listener class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SOAP_Listener_INCLUDED
#define UPnP_SOAP_Listener_INCLUDED


#include "Poco/UPnP/SOAP/SOAP.h"
#include "Poco/RemotingNG/Listener.h"


namespace Poco {
namespace UPnP {
namespace SOAP {


class UPnPSOAP_API Listener: public Poco::RemotingNG::Listener
	/// The RemotingNG Listener implementation for UPnP Control
	/// using SOAP.
{
public:
	typedef Poco::AutoPtr<Listener> Ptr;

	Listener(const std::string& endPoint);
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// Note that this Listener implementation does not actually
		/// accept requests itself. It merely registers an endpoint
		/// in the ORB. The actual work of accepting and dispatching
		/// requests is done by the RequestHandler class.

	~Listener();
		/// Destroys the Listener.

	// Poco::RemotingNG::Listener
	void start();
	void stop();
	const std::string& protocol() const;
	std::string createURI(const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId);
	bool handlesURI(const std::string& uri);
	void registerObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject, Poco::RemotingNG::Skeleton::Ptr pSkeleton);
	void unregisterObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject);
};


} } } // namespace Poco::UPnP::SOAP


#endif // UPnP_SOAP_Listener_INCLUDED
