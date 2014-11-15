//
// EventDispatcher.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/EventDispatcher.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  EventDispatcher
//
// Definition of the EventDispatcher class.
//
// Copyright (c) 2009-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_EventDispatcher_INCLUDED
#define RemotingNG_EventDispatcher_INCLUDED


#include "Poco/RefCountedObject.h"
#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RemotingNG/Transport.h"
#include "Poco/Timestamp.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace RemotingNG {


class RemotingNG_API EventDispatcher: public Poco::RefCountedObject
	/// The EventDispatcher is responsible for delivering
	/// events fired by service objects to remote subscribers.
	///
	/// Event dispatching and delivery in RemotingNG works as follows:
	/// If a service object has events, the corresponding RemoteObject class 
	/// will have a delegate member function for every service object
	/// event, as well as providing all the events itself (inherited from the
	/// interface class). During construction of the RemoteObject, its delegates
	/// will be bound to the service objects' events. The delegates will then
	/// simply fire the RemoteObject's event, when invoked.
	/// 
	/// The EventDispatcher subclass for a specific service will have
	/// delegate functions for all service object events, which will
	/// be bound to the RemoteObject's events. The EventDispatcher class
	/// maintains a list of event subscribers. When an event is fired,
	/// the EventDispatcher's delegate will dispatch the event to
	/// all registered event subscribers, using a Transport. This works
	/// in a very similar way to a Proxy.
{
public:
	typedef Poco::AutoPtr<EventDispatcher> Ptr;
	typedef Transport::NameValueMap NameValueMap;

	EventDispatcher(const std::string& protocol);
		/// Creates an EventDispatcher. 

	virtual ~EventDispatcher();
		/// Destroys the EventDispatcher.

	void subscribe(const std::string& subscriberURI, const std::string& endpointURI, Poco::Timestamp expireTime = 0);
		/// Registers a remote EventSubscriber identified by
		/// the given subscriberURI. Events will be sent to the
		/// specified endpoint, which must be a proper RemotingNG URI.
		/// Depending on the actual transport-specific events implementation,
		/// subscriberURI and enpoint may be the same or different.
		///
		/// If a non-null expireTime is given, the subscription will automatically
		/// expire at the time given in expireTime.
		///
		/// If a subscription with the given subscriberURI already exists,
		/// the expireTime of the existing subscription will be updated.

	void unsubscribe(const std::string& subscriberURI);
		/// Unregisters the remote EventSubscriber identified
		/// by the given URI.
		///
		/// Throws a Poco::NotFoundException if no subscription exists.

	const std::string& protocol() const;
		/// Returns the protocol to be used for delivering
		/// event messages to subscribers.

	AttributedObject& attributes(const std::string& subscriberURI);
		/// Returns the attributes for the subscriber identified
		/// by the given URI. The attributes are stored in the
		/// Transport object.
		
protected:	
	Transport& transportForSubscriber(const std::string& subscriberURI);
		/// Returns the Transport object for communicating
		/// with the remote EventSubscriber identified by the 
		/// given URI.
		///
		/// Throws a Poco::NotFoundException if the subscriber is not known.

	struct SubscriberInfo: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<SubscriberInfo> Ptr;
		
		std::string     endpoint;
		Transport::Ptr  pTransport;
		Poco::Timestamp expireTime;
	};
	typedef std::map<std::string, SubscriberInfo::Ptr> SubscriberMap;

	SubscriberMap   _subscribers;
	Poco::FastMutex _mutex;

private:
	EventDispatcher(const EventDispatcher&);
	EventDispatcher& operator = (const EventDispatcher&);

	std::string _protocol;
};


//
// inlines
//
inline const std::string& EventDispatcher::protocol() const
{
	return _protocol;
}


inline AttributedObject& EventDispatcher::attributes(const std::string& subscriberURI)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return transportForSubscriber(subscriberURI);
}


} } // namespace Poco::RemotingNG


#endif // RemotingNG_EventDispatcher_INCLUDED
