//
// Transport.h
//
// $Id: //poco/1.4/RemotingNG/SOAP/include/Poco/RemotingNG/SOAP/Transport.h#7 $
//
// Library: RemotingNG/SOAP
// Package: SOAP
// Module:  Transport
//
// Definition of the Transport class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_SOAP_Transport_INCLUDED
#define RemotingNG_SOAP_Transport_INCLUDED


#include "Poco/RemotingNG/SOAP/SOAP.h"
#include "Poco/RemotingNG/SOAP/Serializer.h"
#include "Poco/RemotingNG/SOAP/Deserializer.h"
#include "Poco/RemotingNG/Transport.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPCredentials.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include <sstream>


namespace Poco
{
	class DeflatingOutputStream;
}


namespace Poco {
namespace RemotingNG {
namespace SOAP {


class RemotingNGSOAP_API Transport: public Poco::RemotingNG::Transport
	/// The Transport implementation for RemotingNG SOAP.
	///
	/// The transport supports HTTP Basic and HTTP Digest authentication.
	/// Please note that for HTTP Digest authentication to work, chunked transfer
	/// encoding must be disabled. Also, HTTP Digest authentication is not supported
	/// for one-way requests.
{
public:
	static const std::string PROTOCOL;
	static const std::string PROTOCOL_SOAP11;
	static const std::string PROTOCOL_SOAP12;
	static const std::string CONTENT_TYPE_SOAP11;
	static const std::string CONTENT_TYPE_SOAP12;
	
	enum AuthMode
		/// Authentication mode.
	{
		AUTH_NONE    = 0, /// No authentication.
		AUTH_BASIC   = 1, /// HTTP Basic Authentication only (credentials are always sent).
		AUTH_DIGEST  = 2, /// HTTP Digest Authentication only.
		AUTH_ANY     = 3  /// HTTP Basic or Digest authentication (whichever the server requests).
	};

	Transport();
		/// Creates a Transport for SOAP 1.1.

	Transport(Serializer::SOAPVersion soapVersion);
		/// Creates a Transport for the given SOAP version.

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

	bool isKeepAliveEnabled() const;
		/// Returns true iff HTTP/1.1 persistent connections are enabled.
		///
		/// The Transport must be connected, otherwise a Poco::IllegalStateException
		/// will be thrown.

	void enableKeepAlive(bool enable);
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
		
	bool isChunkedTransferEncodingEnabled() const;
		/// Returns true iff chunked transfer encoding is enabled,
		/// which is the default unless enableChunkedTransferEncoding(false) has
		/// been called.

	void enableChunkedTransferEncoding(bool enable = true);
		/// Enables or disables chunked transfer encoding for HTTP requests.
		/// This is normally enabled. However, some poorly implemented HTTP stacks cannot 
		/// handle chunked HTTP messages. Also, chunked transfer encoding must be
		/// disabled if AUTH_DIGEST or AUTH_ANY authentication is used.
		///
		/// Regardless of this setting, chunked transfer encoding is always supported
		/// for responses sent by the server.
		
	bool isCompressionEnabled() const;
		/// Returns true iff HTTP compression (GZIP) is enabled for requests.
		/// Default is disabled.
		
	void enableCompression(bool enable);
		/// Enables or disables HTTP compression via GZIP Content-Encoding for
		/// requests.
		/// This is normally disabled, due to a lack of support by most servers.
		///
		/// Note that chunked transfer encoding must also be enabled in
		/// order to allow compression.
		///
		/// Regardless of this setting, server responses can always be compressed 
		/// using GZIP Content-Encoding.
		
	bool isMTOMEnabled() const;
		/// Returns true if MTOM (Message Transport Optimization Mechanism)
		/// is enabled for requests.
		
	void enableMTOM(bool enable);
		/// Enables or disables MTOM (Message Transport Optimization Mechanism)
		/// for client requests. If enabled, every request will be sent in a 
		/// MIME multipart message and binary data (std::vector<char>) will
		/// be sent raw in a separate MIME part instead of Base64-encoded within
		/// the SOAP body.
		///
		/// See http://www.w3.org/TR/soap12-mtom/ for more information about MTOM.
		///
		/// Regardless of this setting, server responses can always use MTOM. 
	
	void setAuthentication(AuthMode authMode);
		/// Sets the authentication mode.
		///
		/// Please note that for AUTH_DIGEST or AUTH_ANY, chunked
		/// transfer encoding must be disabled.
		
	AuthMode getAuthentication() const;
		/// Returns the authentication mode.

	void setUsername(const std::string& username);
		/// Sets the username for HTTP authentication.
		
	const std::string& getUsername() const;
		/// Returns the username for HTTP authentication.
		
	void setPassword(const std::string& password);
		/// Sets the password for HTTP authentication.
		
	const std::string& getPassword() const;
		/// Returns the password for HTTP authentication.

	const std::string& getUserAgent() const;
		/// Returns the value of the User-Agent header sent with SOAP HTTP
		/// requests, or an empty string if no User-Agent value has been set.
	
	void setUserAgent(const std::string& userAgent);
		/// Sets the value of the User-Agent header sent with SOAP HTTP
		/// requests. If an empty string is given (default), no User-Agent
		/// header is included in the request.
		
	static Poco::Net::HTTPSessionFactory& httpSessionFactory();
		/// Returns the Poco::Net::HTTPSessionFactory instance used by
		/// the transport.
		
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
	static const std::string PROP_ACTION;

private:
	Poco::Net::HTTPCredentials _creds;
	Poco::SharedPtr<Poco::Net::HTTPClientSession> _pSession;
	Serializer _serializer;
	Deserializer _deserializer;
	std::string _endPoint;
	Poco::URI _endPointURI;
	bool _keepAlive;
	bool _chunkedTransferEncoding;
	bool _compression;
	bool _mtom;
	AuthMode _authMode;
	std::string _userAgent;
	Poco::SharedPtr<std::stringstream> _pStream;
	Poco::SharedPtr<Poco::DeflatingOutputStream> _pDeflater;
	std::string _mtomContentType;
	
	static Poco::Net::HTTPSessionFactory _httpSessionFactory;
	
	friend class SOAPRequestHandler;
};


//
// inlines
//
inline Poco::Net::HTTPSessionFactory& Transport::httpSessionFactory()
{
	return _httpSessionFactory;
}


} } } // namespace Poco::RemotingNG::SOAP


#endif // RemotingNG_SOAP_Transport_INCLUDED
