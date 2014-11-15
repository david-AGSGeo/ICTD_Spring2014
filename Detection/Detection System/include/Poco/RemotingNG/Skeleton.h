//
// Skeleton.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/Skeleton.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  Skeleton
//
// Definition of the Skeleton class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_Skeleton_INCLUDED
#define RemotingNG_Skeleton_INCLUDED


#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RemotingNG/AttributedObject.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/AutoPtr.h"
#include <map>


namespace Poco {
namespace RemotingNG {


class ServerTransport;
class RemoteObject;


class RemotingNG_API Skeleton: public AttributedObject
	/// A Skeleton is responsible for demultiplexing incoming requests
	/// to the correct service object method, using MethodHandler objects.
{
public:
	typedef Poco::AutoPtr<Skeleton> Ptr;
	typedef std::map<std::string, MethodHandler::Ptr> MethodHandlers;

	Skeleton();
		/// Creates a Skeleton.

	virtual ~Skeleton();
		/// Destroys the Skeleton.

	bool invoke(ServerTransport& transport, RemoteObject::Ptr pRemoteObject);
		/// Invoke a method on the RemoteObject.
		///
		/// First, obtains a Deserializer from the given ServerTransport
		/// by calling beginRequest().
		/// Then, determines the method name from the request (by calling
		/// Deserializer::findMessage()), obtains the MethodHandler for the 
		/// method and invokes the method using the MethodHandler.
		///
		/// If no MethodHandler is found, a MethodNotFoundException is sent back to the client.
		/// If the type of the received message is neither MESSAGE_REQUEST nor MESSAGE_EVENT,
		/// a UnexpectedMessageException will be thrown.
		///
		/// After processing the request, endRequest() is called on the ServerTransport.
		///
		/// Returns true if the method was found, false otherwise.
		
protected:
	void addMethodHandler(const std::string& name, MethodHandler::Ptr pMethodHandler);
		/// Adds a MethodHandler for the service object's method with the given name to the Skeleton. 
		/// Takes ownership of the MethodHandler.

private:
	Skeleton(const Skeleton&);
	Skeleton& operator = (const Skeleton&);

	MethodHandlers _handlers;
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_Skeleton_INCLUDED
