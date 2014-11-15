//
// Listener.h
//
// $Id: //poco/1.4/RemotingNG/JSONRPC/include/Poco/RemotingNG/JSONRPC/Listener.h#3 $
//
// Library: RemotingNG/JSONRPC
// Package: JSONRPC
// Module:  Listener
//
// Definition of the Listener class.
//
// Copyright (c) 2006-2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_JSONRPC_Listener_INCLUDED
#define RemotingNG_JSONRPC_Listener_INCLUDED


#include "Poco/RemotingNG/JSONRPC/JSONRPC.h"
#include "Poco/RemotingNG/Listener.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace RemotingNG {
namespace JSONRPC {


class RemotingNGJSONRPC_API Listener: public Poco::RemotingNG::Listener
	/// The RemotingNG Listener implementation for the JSONRPC transport.
	///
	/// For more information, please see the Transport class.
{
public:
	typedef Poco::AutoPtr<Listener> Ptr;

	enum Protocol
	{
		PROTO_HTTP,
		PROTO_HTTPS
	};

	Listener(const std::string& endPoint, Protocol proto);
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// The value specified for proto determines the URI
		/// scheme used by createURI().
		///
		/// Note that the Listener instance created by this constructor 
		/// does not actually accept requests itself. It merely registers an 
		/// endpoint in the ORB. A Poco::Net::HTTPServer must be created
		/// for accepting SOAP requests using a JSONRPCRequestHandler.

	Listener(const std::string& endPoint, Poco::Net::HTTPServerParams::Ptr pParams = new Poco::Net::HTTPServerParams);
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// This constructor will create a Poco::Net::HTTPServer 
		/// instance for handling incoming JSONRPC requests, using
		/// a Poco::Net::ServerSocket bound to endPoint.

	Listener(const std::string& endPoint, const Poco::Net::ServerSocket& socket, Poco::Net::HTTPServerParams::Ptr pParams = new Poco::Net::HTTPServerParams);
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// This constructor will create a Poco::Net::HTTPServer 
		/// instance using the given server socket for handling 
		/// incoming JSONRPC requests. The given server socket can
		/// be a Poco::Net::ServerSocket or a Poco::Net::SecureServerSocket
		/// which must be bound to a socket address corresponding to
		/// the given endPoint.

	~Listener();
		/// Destroys the Listener.

	void enableChunkedTransferEncoding(bool enable = true);
		/// Enables or disables chunked transfer encoding for responses.
		/// Default is enabled.
		
	bool isChunkedTransferEncodingEnabled() const;
		/// Returns true iff chunked transfer encoding is enabled for responses.
		
	void enableCompression(bool enable = true);
		/// Enables or disables GZIP compression for responses.
		/// Default is enabled.
		///
		/// Note that chunked transfer encoding must also be enabled
		/// in order to allow compression.
		
	bool isCompressionEnabled() const;
		/// Returns true iff GZIP compression is enabled for responses.
		
	void enableCORS(bool enable = true);
		/// Enables or disables CORS (Cross Origin Resource Sharing).
		/// Default is disabled.
		
	bool isCORSEnabled() const;
		/// Returns true iff CORS is enabled.
		
	void setCORSAllowedOrigin(const std::string& origin);
		/// Sets the CORS allowed origin.
		///
		/// Can be empty (default), an asterisk ("*"), or a specific origin
		/// in the form of a complete http(s) URL ("http://domain.com").
		///
		/// In case of an empty origin specified here, all origins will
		/// be accepted and the origin specified by the client will simply
		/// be echoed back. If an asterisk is specified, again, all origins
		/// will be accepted, but the asterisk will be sent back to the client
		/// in the "Access-Control-Allow-Origin" header. 
		/// If any other origin is given, the origin presented by the client
		/// must exactly match the specified origin for the request to be accepted.
		
	const std::string& getCORSAllowedOrigin() const;
		/// Retuns the CORS allowed origin.
		///
		/// See setCORSAllowedOrigin() for more information.

	// Poco::RemotingNG::Listener
	void start();
	void stop();
	const std::string& protocol() const;
	std::string createURI(const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId);
	bool handlesURI(const std::string& uri);
	void registerObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject, Poco::RemotingNG::Skeleton::Ptr pSkeleton);
	void unregisterObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject);

private:
	bool _secure;
	Poco::SharedPtr<Poco::Net::HTTPServer> _pHTTPServer;
	bool _enableChunkedTransferEncoding;
	bool _enableCompression;
	bool _enableCORS;
	std::string _corsAllowedOrigin;
};


//
// inlines
//
inline bool Listener::isChunkedTransferEncodingEnabled() const
{
	return _enableChunkedTransferEncoding;
}


inline bool Listener::isCompressionEnabled() const
{
	return _enableCompression;
}


inline bool Listener::isCORSEnabled() const
{
	return _enableCORS;
}


inline const std::string& Listener::getCORSAllowedOrigin() const
{
	return _corsAllowedOrigin;
}


} } } // namespace Poco::RemotingNG::JSONRPC


#endif // RemotingNG_JSONRPC_Listener_INCLUDED
