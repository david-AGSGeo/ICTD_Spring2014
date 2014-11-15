//
// Transport.h
//
// $Id: //poco/1.4/UPnP/SOAP/include/Poco/UPnP/SOAP/Transport.h#5 $
//
// Library: UPnP/SOAP
// Package: SOAP
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


#ifndef UPnP_SOAP_Transport_INCLUDED
#define UPnP_SOAP_Transport_INCLUDED


#include "Poco/UPnP/SOAP/SOAP.h"
#include "Poco/UPnP/SOAP/Serializer.h"
#include "Poco/UPnP/SOAP/Deserializer.h"
#include "Poco/RemotingNG/Transport.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include <sstream>


namespace Poco {
namespace UPnP {
namespace SOAP {


class UPnPSOAP_API Transport: public Poco::RemotingNG::Transport
	/// The Transport implementation for UPnP SOAP.
	///
	/// This Transport implementation provides SOAP support
	/// for UPnP device control.
{
public:
	static const std::string PROTOCOL;

	Transport(bool keepAlive = false);
		/// Creates a Transport.
		///
		/// If keepAlive is true, enables HTTP 1.1 persistent connections for this
		/// Transport connection.

	~Transport();
		/// Destroys the Transport.

	Poco::Timespan getTimeout() const;
		/// Returns the HTTP timeout.
		///
		/// The Transport must be connected, otherwise a Poco::IllegalStateException
		/// will be thrown.
		
	void setTimeout(const Poco::Timespan& timeout);
		/// Sets the HTTP timeout.
		///
		/// The Transport must be connected, otherwise a Poco::IllegalStateException
		/// will be thrown.

	bool getKeepAlive() const;
		/// Returns true iff HTTP/1.1 persistent connections are enabled.
		///
		/// The Transport must be connected, otherwise a Poco::IllegalStateException
		/// will be thrown.

	void setKeepAlive(bool enable);
		/// Enables or disables HTTP/1.1 persistent connections.
		///
		/// The Transport must be connected, otherwise a Poco::IllegalStateException
		/// will be thrown.		

	Poco::Timespan getKeepAliveTimeout() const;
		/// Returns the timeout for HTTP/1.1 persistent connections.
		///
		/// The Transport must be connected, otherwise a Poco::IllegalStateException
		/// will be thrown.
		
	void setKeepAliveTimeout(const Poco::Timespan& timeout);
		/// Sets the timeout for HTTP/1.1 persistent connections.
		///
		/// The Transport must be connected, otherwise a Poco::IllegalStateException
		/// will be thrown.
		
	bool getChunkedTransferEncoding() const;
		/// Returns true iff chunked transfer encoding is enabled,
		/// which is the default unless enableChunkedTransferEncoding() has
		/// been called.

	void setChunkedTransferEncoding(bool enable = true);
		/// Enables or disables chunked transfer encoding for HTTP requests.
		/// This is normally enabled. However, some poorly implemented UPnP stacks cannot 
		/// handle chunked HTTP messages.
	
	const std::string& getUserAgent() const;
		/// Returns the value of the User-Agent header sent with UPnP SOAP
		/// requests, or an empty string if no User-Agent value has been set.
	
	void setUserAgent(const std::string& userAgent);
		/// Sets the value of the User-Agent header sent with UPnP SOAP
		/// requests. If an empty string is given (default), no User-Agent
		/// header is included in the request. 
		
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

protected:
	const Poco::Net::HTTPClientSession& requireSession() const;
	Poco::Net::HTTPClientSession& requireSession();
	void prepareRequest(Poco::Net::HTTPRequest& request, const std::string& messageName);
	static const std::string SOAPACTION;
	static const std::string USER_AGENT;
	static const std::string CONTENT_TYPE;

private:
	Poco::SharedPtr<Poco::Net::HTTPClientSession> _pSession;
	Serializer _serializer;
	Deserializer _deserializer;
	std::string _endPoint;
	Poco::URI _endPointURI;
	bool _keepAlive;
	bool _chunkedTransferEncoding;
	std::string _userAgent;
	Poco::SharedPtr<std::stringstream> _pStream;
	
	friend class RequestHandler;
};


} } } // namespace Poco::RemotingNG::SoapLite


#endif // UPnP_SOAP_Transport_INCLUDED
