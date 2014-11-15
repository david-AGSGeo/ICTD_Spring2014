//
// SSDPResponder.h
//
// $Id: //poco/1.4/UPnP/SSDP/include/Poco/UPnP/SSDP/SSDPResponder.h#6 $
//
// Library: UPnP/SSDP
// Package: SSDP
// Module:  SSDPResponder
//
// Definition of the SSDPResponder class.
//
// Copyright (c) 2008-2010, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_SSDP_SSDPResponder_INCLUDED
#define UPnP_SSDP_SSDPResponder_INCLUDED


#include "Poco/UPnP/SSDP/SSDP.h"
#include "Poco/UPnP/SSDP/Advertisement.h"
#include "Poco/UPnP/SSDP/HTTPMUServer.h"
#include "Poco/UPnP/SSDP/HTTPMUClient.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/BasicEvent.h"
#include "Poco/Random.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace UPnP {
namespace SSDP {


class UPnP_SSDP_API SSDPResponder
	/// SSDPResponder implements the Simple Service Discovery
	/// Protocol for UPnP. 
	///
	/// The SSDPResponder maintains a list of local Advertisements and 
	/// periodically sends out discovery messages, using a multicast
	/// socket. It also processes discovery and search messages received 
	/// from other UPnP devices on the network. Search messages are
	/// replied to, if possible, while discovery messages (ssdp:alive and 
	/// ssdp:byebye) from other UPnP devices are made available via events.
	///
	/// The steps for setting up a SSDPResponder are as follows:
	///     // 1. Set up a multicast socket (we use a wildcard address here)
	///     Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), Poco::UPnP::SSDPResponder::MULTICAST_PORT);
	///     Poco::Net::MulticastSocket socket(sa);
	///     socket.setLoopback(true); // optional
	///     socket.setTimeToLive(4);  // recommended by SSDP specification
	///     // 2. Set up SSDPResponder
	///     Poco::UPnP::SSDPResponder responder(socket);
	///     // 3. Join multicast group for advertisements
	///     socket.joinGroup(responder.groupAddress().host());
	///     // 4. Publish local devices and services.
	///     responder.publish(pRootDeviceAdvertisement);
	///     ...
	///     // 5. Start responder
	///     responder.start();
	///
	/// To shutdown a SSDPResponder, stop it and leave the multicast group:
	///     responder.stop();
	///     socket.leaveGroup(responder.groupAddress().host());
	///
	/// According to the UPnP SSDP specification, when a device is added to the network, 
	/// it multicasts discovery messages to advertise its root device, any embedded devices, 
	/// and any services. Each discovery message contains four major components:
	///   1. a potential search target (e.g., device type), sent in an NT (Notification Type) header,  
	///   2. a composite identifier for the advertisement, sent in a USN (Unique Service Name) header,
	///   3. a URL for more information about the device (or enclosing device in the case of a service), 
	///      sent in a LOCATION header, and
	///   4. a duration for which the advertisement is valid, sent in a CACHE-CONTROL header.  
	///
	/// To advertise its capabilities, a device multicasts a number of discovery messages. 
	/// Specifically, a root device must multicast:
	///   - Three discovery messages (root device, device UUID and device type) for the root device.
	///   - Two discovery messages (device UUID and device type) for each embedded device.
	///   - One discovery message (service type) for each service type in each device.
	///
	/// For more information, please refer to the UPnP Device Architecture specification.
	///
	/// Note: In order to comply with DLNA requirements, two sockets are used for sending and
	/// receiving messages. For "security reasons", DLNA requirement 7.2.3.4 disallows sending 
	/// out M-SEARCH and NOTIFY messages with source port 1900. Therefore, the same socket that 
	/// is used to receive notifications from other devices cannot be used to send messages, 
	/// and a separate socket is needed for that purpose. The second (outgoing) socket can be
	/// created automatically (in this case, bound address, TTL and loopback options are copied
	/// from the given socket), or it can be explicitly passed to the constructor, along with the
	/// incoming socket. Loopback option and TTL must be set for the outgoing socket in this case.
	/// However, the outgoing socket does not need to join the multicast group.
{
public:
	static const std::string MULTICAST_HOST;
	static const Poco::UInt16 MULTICAST_PORT;
	static const std::string UPNP_VERSION;
	static const std::string PRODUCT_VERSION;
	
	enum StopMode
	{
		SSDP_STOP_NO_BYEBYE,  /// Do not send ssdp:byebye messages when stopping.
		SSDP_STOP_SEND_BYEBYE /// Send ssdp:byebye messages when stopping.
	};
	
	Poco::BasicEvent<Advertisement::Ptr> advertisementSeen;
		/// A ssdp:alive message has been received for the
		/// given Advertisement.
		///
		/// The Advertisement will contain the following attributes:
		///   - Host: the host address and port number (<host>:<port>) of
		///     the device sending the message.
		///   - Server: the server name (the value of the Server header
		///     sent with the ssdp:alive message). Will not be included
		///     in advertisements from search responses.
		///   - ST: the search target. Only included in advertisements
		///     from search responses.
		///
		/// The event handler should return as soon as possible
		/// to avoid disruptions in SSDP message processing.
		
	Poco::BasicEvent<std::string> advertisementGone;
		/// A ssdp:byebye message has been received for
		/// the given Unique Service Name (USN).
		///
		/// The event handler should return as soon as possible
		/// to avoid disruptions in SSDP message processing.
		
	SSDPResponder(const Poco::Net::MulticastSocket& socket);
		/// Creates a SSDPResponder, using the given multicast socket,
		/// which must have been properly setup.
		///
		/// For sending M-SEARCH and NOTIFY messages, a separate 
		/// multicast socket is created and bound to the same
		/// IP address as the given socket. Loopback and TTL options
		/// are also copied from the given socket.

	SSDPResponder(const Poco::Net::MulticastSocket& incomingSocket, const Poco::Net::MulticastSocket& outgoingSocket);
		/// Creates a SSDPResponder, using the given multicast sockets,
		/// which must have been properly setup.

	SSDPResponder(const Poco::Net::MulticastSocket& socket, const Poco::Net::SocketAddress& groupAddress);
		/// Creates a SSDPResponder, using the given multicast socket,
		/// which must have been properly setup. Multicast messages are
		/// sent to the given address. Use of a non-standard multicast 
		/// address (239.255.255.250:1900) is not recommended.
		///
		/// For sending M-SEARCH and NOTIFY messages, a separate 
		/// multicast socket is created and bound to the same
		/// IP address as the given socket. Loopback and TTL options
		/// are also copied from the given socket.

	SSDPResponder(const Poco::Net::MulticastSocket& incomingSocket, const Poco::Net::MulticastSocket& outgoingSocket, const Poco::Net::SocketAddress& groupAddress);
		/// Creates a SSDPResponder, using the given multicast sockets,
		/// which must have been properly setup. Multicast messages are
		/// sent to the given address. Use of a non-standard multicast 
		/// address (239.255.255.250:1900) is not recommended.

	SSDPResponder(Poco::Util::Timer& timer, const Poco::Net::MulticastSocket& socket);
		/// Creates a SSDPResponder, using the given timer and multicast socket,
		/// which must have been properly setup.
		///
		/// For sending M-SEARCH and NOTIFY messages, a separate 
		/// multicast socket is created and bound to the same
		/// IP address as the given socket. Loopback and TTL options
		/// are also copied from the given socket.

	SSDPResponder(Poco::Util::Timer& timer, const Poco::Net::MulticastSocket& incomingSocket, const Poco::Net::MulticastSocket& outgoingSocket);
		/// Creates a SSDPResponder, using the given timer and multicast socket,
		/// which must have been properly setup.

	SSDPResponder(Poco::Util::Timer& timer, const Poco::Net::MulticastSocket& socket, const Poco::Net::SocketAddress& groupAddress);
		/// Creates a SSDPResponder, using the given timer and multicast socket,
		/// which must have been properly setup. Multicast messages are
		/// sent to the given address. Use of a non-standard multicast 
		/// address (239.255.255.250:1900) is not recommended.
		///
		/// For sending M-SEARCH and NOTIFY messages, a separate 
		/// multicast socket is created and bound to the same
		/// IP address as the given socket. Loopback and TTL options
		/// are also copied from the given socket.

	SSDPResponder(Poco::Util::Timer& timer, const Poco::Net::MulticastSocket& incomingSocket, const Poco::Net::MulticastSocket& outgoingSocket, const Poco::Net::SocketAddress& groupAddress);
		/// Creates a SSDPResponder, using the given timer and multicast socket,
		/// which must have been properly setup. Multicast messages are
		/// sent to the given address. Use of a non-standard multicast 
		/// address (239.255.255.250:1900) is not recommended.
				
	~SSDPResponder();
		/// Destroys the SSDPResponder.
		///
		/// Stops the responder if it is still running.
		
	void start();
		/// Starts the SSDPResponder.
		///
		/// The responder will start receiving advertisements.
		/// It will also send ssdp:alive messages for all registered
		/// advertisements.
		///
		/// While the SSDPResponder is running, it will send
		/// periodic discovery messages (ssdp:alive) for all registered
		/// advertisements. Messages will be send at a random interval.
		/// The interval will be larger than 1/3 of the Advertisement's
		/// life time and smaller than 2/3 of the Advertisement's life time.
		///
		/// The SSDPResponder will also reply to any matching search
		/// requests it receives.
		
	void stop();
		/// Stops the SSDPResponder.
		///
		/// The responder will send ssdp:byebye messages for all
		/// registered advertisements.
		///
		/// Please note that the byebye messages will be sent using
		/// the timer, after stop() returns. When using an external timer,
		/// make sure that the SSDPResponder remains alive until all byebye 
		/// messages have been sent and/or cancel all timer tasks before destroying 
		/// the SSDPResponder.
		
	void stop(StopMode mode);
		/// Stops the SSDPResponder.
		///
		/// If mode is SSDP_STOP_SEND_BYEBYE, the responder will send ssdp:byebye 
		/// messages for all registered advertisements.
		///
		/// Please note that the byebye messages will be sent using
		/// the timer, after stop() returns. When using an external timer,
		/// make sure that the SSDPResponder remains alive until all byebye 
		/// messages have been sent and/or cancel all timer tasks before destroying 
		/// the SSDPResponder.
		
	void publish(Advertisement::Ptr pAdvertisement);
		/// Adds a new Advertisement to the SSDPResponder's list of
		/// local advertisements.
		///
		/// An Advertisement can be for a root device, a device UUID,
		/// a device type or a service type.
		///
		/// If the SSDPResponder is already running, will also send
		/// an initial ssdp:alive message. While the SSDPResponder
		/// is running, it will send periodic discovery messages
		/// (ssdp:alive) for the Advertisement.
		///
		/// Throws a Poco::ExistsException if an Advertisement with
		/// the same USN has already been advertized.
		
	void revoke(const std::string& usn);
		/// Removes the Advertisement with the given Unique Service Name.
		/// 
		/// If the SSDPResponder is running, will send a
		/// ssdp:byebye message for the given USN.
		///
		/// Throws a Poco::NotFoundException if an Advertisement
		/// with the given USN is unknown.
		
	void search(const std::string& searchTarget);
		/// Multicasts a search request for the given search target.
		///
		/// According to the SSDP specification, the
		/// search target can be one of:
		///   - ssdp:all: Search for all devices and services.
		///   - upnp:rootdevice: Search for all root devices.
		///   - a Unique Service Name: Search for a specific device or service type.
		
	const Poco::Net::SocketAddress& groupAddress() const;
		/// Returns the socket address of the multicast group used
		/// by this SSDPResponder.
		///
		/// Unless an address has been given in the constructor,
		/// the default SSDP multicast address (239.255.255.250:1900)
		/// is returned.
		
	int getMaxResponseTime() const;
		/// Returns the maximum response time (in seconds) sent with search requests.
		/// The default is 2 seconds.
		
	void setMaxResponseTime(int seconds);
		/// Sets the maximum response time (in seconds) sent with search requests.
		///
		/// The maximum response time must be greater than 0.
		
	const std::string& getServer() const;
		/// Returns the Server identification string sent with alive messages.
		
	void setServer(const std::string& server);
		/// Sets the Server identification string sent with alive message.
		///
		/// The format must be <os>/<version> UPnP/1.0 <product>/<version>.
		
protected:
	struct AdvertisementInfo
	{
		Advertisement::Ptr pAdvertisement;
		Poco::Util::TimerTask::Ptr pTask;
	};
	typedef std::map<std::string, AdvertisementInfo> Advertisements;
	
	void sendAliveMessage(Advertisement::Ptr pAdvertisement);
	void sendByeByeMessage(Advertisement::Ptr pAdvertisement);
	void sendSearchRequest(const std::string& searchTarget);
	void sendSearchResponse(Advertisement::Ptr pAdvertisement, const std::string& searchTarget, const Poco::Net::SocketAddress& requesterAddress);
	void searchLocal(const std::string& searchTarget, int maxResponseTime, const Poco::Net::SocketAddress& requesterAddress);
	void handleRequest(const Poco::Net::HTTPRequest& request, const Poco::Net::SocketAddress& senderAddress);
	void handleResponse(const Poco::Net::HTTPResponse& response, const Poco::Net::SocketAddress& senderAddress);
	static std::string createServerString();
	
	static const std::string NOTIFY;
	static const std::string M_SEARCH;
	static const std::string WILDCARD_URI;
	static const std::string CACHE_CONTROL;
	static const std::string MAX_AGE_FORMAT;
	static const std::string LOCATION;
	static const std::string NT;
	static const std::string NTS;
	static const std::string SERVER;
	static const std::string USN;
	static const std::string MAN;
	static const std::string EXT;
	static const std::string MX;
	static const std::string ST;
	static const std::string SSDP_ALIVE;
	static const std::string SSDP_BYEBYE;
	static const std::string SSDP_DISCOVER;
	static const std::string SSDP_ALL;
	static const std::string UPNP_ROOTDEVICE;
	static const std::string HOST;
	static const std::string EMPTY;
	
	enum
	{
		INITIAL_AD_MIN_REPEAT_INTERVAL = 100,
		INITIAL_AD_MAX_REPEAT_INTERVAL = 300
	};
	
private:
	SSDPResponder();
	SSDPResponder(const SSDPResponder&);
	SSDPResponder& operator = (const SSDPResponder&);
	void initOutgoingSocket();
	
	Poco::Net::SocketAddress _groupAddress;
	Poco::Net::MulticastSocket _incomingSocket;
	Poco::Net::MulticastSocket _outgoingSocket;
	int _maxResponseTime;
	std::string _server;
	HTTPMUServer _httpmuServer;
	HTTPMUClient _httpmuClient;
	Poco::Util::Timer* _pTimer;
	bool _ownTimer;
	Advertisements _advertisements;
	bool _running;
	Poco::Random _rnd;
	mutable Poco::FastMutex _mutex;
	
	friend class SendAliveTask;
	friend class SendByeByeTask;
	friend class SendSearchRequestTask;
	friend class SendSearchResponseTask;
	friend class LocalSearchTask;
	friend class SSDPMessageHandler;
};


//
// inlines
//
inline const Poco::Net::SocketAddress& SSDPResponder::groupAddress() const
{
	return _groupAddress;
}


inline int SSDPResponder::getMaxResponseTime() const
{
	return _maxResponseTime;
}


inline const std::string& SSDPResponder::getServer() const
{
	return _server;
}


} } } // namespace Poco::UPnP::SSDP


#endif // UPnP_SSDP_SSDPResponder_INCLUDED
