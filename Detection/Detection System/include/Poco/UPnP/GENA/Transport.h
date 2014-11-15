//
// Transport.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/Transport.h#3 $
//
// Library: UPnP/GENA
// Package: GENA
// Module:  Transport
//
// Definition of the Transport class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_GENA_Transport_INCLUDED
#define UPnP_GENA_Transport_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/UPnP/GENA/Serializer.h"
#include "Poco/UPnP/GENA/Deserializer.h"
#include "Poco/RemotingNG/Transport.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API Transport: public Poco::RemotingNG::Transport
	/// The Transport implementation for UPnP GENA.
{
public:
	static const std::string PROTOCOL;

	Transport(const Poco::Timespan& timeout, bool keepAlive, const Poco::Timespan& keepAliveTimeout);
		/// Creates a Transport.
		///
		/// If keepAlive is true, enables HTTP 1.1 persistent connections for this
		/// Transport connection.

	~Transport();
		/// Destroys the Transport.

	// Poco::RemotingNG::Transport
	const std::string& endPoint() const;
	void connect(const std::string& endPoint);
	void disconnect();
	bool connected() const;
	Poco::RemotingNG::Serializer& beginMessage(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType);
	void sendMessage(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType);
	Poco::RemotingNG::Serializer& beginRequest(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType);
	Poco::RemotingNG::Deserializer& sendRequest(const Poco::RemotingNG::Identifiable::ObjectId& oid, const Poco::RemotingNG::Identifiable::TypeId& tid, const std::string& messageName, Poco::RemotingNG::SerializerBase::MessageType messageType);
	void endRequest();

	static const std::string NOTIFY;
	static const std::string HDR_NT;
	static const std::string HDR_NTS;
	static const std::string HDR_SID;
	static const std::string HDR_SEQ;
	static const std::string CONTENT_TYPE;
	static const std::string UPNP_EVENT;
	static const std::string UPNP_PROPCHANGE;

private:
	Poco::UInt32 _eventSequenceNo;
	Poco::SharedPtr<Poco::Net::HTTPClientSession> _pSession;
	Serializer _serializer;
	Deserializer _deserializer;
	std::string _endPoint;
	Poco::URI _endPointURI;
	Poco::Timespan _timeout;
	bool _keepAlive;
	Poco::Timespan _keepAliveTimeout;
};


} } } // namespace Poco::RemotingNG::GENALite


#endif // UPnP_GENA_Transport_INCLUDED
