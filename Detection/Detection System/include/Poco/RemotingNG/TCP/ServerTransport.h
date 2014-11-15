//
// ServerTransport.h
//
// $Id: //poco/1.4/RemotingNG/TCP/include/Poco/RemotingNG/TCP/ServerTransport.h#3 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  ServerTransport
//
// Definition of the ServerTransport class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_TCP_ServerTransport_INCLUDED
#define RemotingNG_TCP_ServerTransport_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/RemotingNG/TCP/ChannelStream.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/BinarySerializer.h"
#include "Poco/RemotingNG/BinaryDeserializer.h"
#include "Poco/InflatingStream.h"
#include "Poco/DeflatingStream.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/Event.h"
#include "Poco/Logger.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class Listener;


class RemotingNGTCP_API ServerTransport: public Poco::RemotingNG::ServerTransport, public Poco::Runnable, public Poco::RefCountedObject
	/// The ServerTransport implementation for the RemotingNG TCP transport.
{
public:
	typedef Poco::AutoPtr<ServerTransport> Ptr;

	ServerTransport(Listener& _listener, const Poco::SharedPtr<ChannelInputStream>& pRequestStream, const Poco::SharedPtr<ChannelOutputStream>& pReplyStream, bool compressed);
		/// Creates a ServerTransport.
		
	~ServerTransport();
		/// Destroys the ServerTransport().
		
	void waitReady();
		/// Waits until the server thread is ready.

	// ServerTransport
	Deserializer& beginRequest();
	Serializer& sendReply(SerializerBase::MessageType messageType);
	void endRequest();

	// Runnable
	void run();
	
private:
	Listener& _listener;
	Poco::SharedPtr<ChannelInputStream> _pRequestStream;
	Poco::SharedPtr<ChannelOutputStream> _pReplyStream;
	Poco::InflatingInputStream* _pInflater;
	Poco::DeflatingOutputStream* _pDeflater;
	Poco::RemotingNG::BinarySerializer _serializer;
	Poco::RemotingNG::BinaryDeserializer _deserializer;
	Poco::Event _ready;
	Poco::Logger& _logger;
};


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_ServerTransport_INCLUDED
