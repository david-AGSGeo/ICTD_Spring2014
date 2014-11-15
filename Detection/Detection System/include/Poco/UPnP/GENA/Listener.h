//
// Listener.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/Listener.h#4 $
//
// Library: UPnP/GENA
// Package: GENA
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


#ifndef UPnP_GENA_Listener_INCLUDED
#define UPnP_GENA_Listener_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/UPnP/GENA/StateProvider.h"
#include "Poco/RemotingNG/EventListener.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/BasicEvent.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#include <map>


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API Listener: public Poco::RemotingNG::EventListener
	/// The RemotingNG Listener implementation for UPnP Eventing
	/// using GENA.
	///
	/// This class also manages event subscriptions. A subscription
	/// timeout can be set for events
{
public:
	typedef Poco::AutoPtr<Listener> Ptr;

	Poco::BasicEvent<const std::string> eventSubscriptionRenewed;
		/// Fired whenever an event subscription has been
		/// successfully renewed.
		///
		/// The event subscription URI is given as argument.

	Poco::BasicEvent<const std::string> eventSubscriptionRenewalFailed;
		/// Fired whenever an attempt to renew an event subscription
		/// failed with a network error or HTTP error other than 412.
		///
		/// The framework will still attempt to renew the subscription
		/// in the future, until it gets a 412 Precondition Failed error.
		/// In this case, one last attempt to create a new subscription
		/// will be made. If this also fails, the event subscription
		/// is lost and the eventSubscriptionLost event is fired.
		///
		/// The event subscription URI is given as argument.
		
	Poco::BasicEvent<const std::string> eventSubscriptionLost;
		/// Fired whenever an event subscription has been lost.
		/// This happens when an normal renewal attempt fails with
		/// a 412 Precondition Failed HTTP error, and the following
		/// attempt to create a new subscription also fails.
		///
		/// The event subscription URI is given as argument.

	Listener(const std::string& endPoint, Poco::Util::Timer& timer);
		/// Creates a Listener for the given endpoint,
		/// which must be in <host>:<port> format.
		///
		/// The timer is required for periodically renewing event
		/// subscriptions.
		///
		/// Note that this Listener implementation does not actually
		/// accept requests itself. It merely registers an endpoint
		/// in the ORB. The actual work of accepting and dispatching
		/// requests is done by the RequestHandler class.

	~Listener();
		/// Destroys the Listener.

	void setEventSubscriptionTimeout(int seconds);
		/// Sets the timeout (in seconds) for event subscriptions.
		///
		/// A zero timeout means infinite.
		
	int getEventSubscriptionTimeout() const;
		/// Returns the timeout (in seconds) for event subscriptions.
		
	Poco::RemotingNG::EventSubscriber::Ptr findSubscriber(const std::string& sid);
		/// Returns a pointer to the EventSubscriber with the given SID,
		/// or a null pointer if no such subscriber exists.
	
	void registerStateProvider(const std::string& uri, StateProvider* pStateProvider);
		/// Registers a StateProvider interface for the remote object with the
		/// given URI.

	void unregisterStateProvider(const std::string& uri);
		/// Unregisters the StateProvider interface for the remote object with the
		/// given URI.
		
	StateProvider* findStateProvider(const std::string& uri);
		/// Returns the StateProvider for the remote object with the given URI,
		/// or a null pointer if no StateProvider has been registered for that object.
	
	// Poco::RemotingNG::EventListener
	void subscribeToEvents(Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber);
	void unsubscribeFromEvents(Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber);

	// Poco::RemotingNG::Listener
	void start();
	void stop();
	const std::string& protocol() const;
	std::string createURI(const Poco::RemotingNG::Identifiable::TypeId& typeId, const Poco::RemotingNG::Identifiable::ObjectId& objectId);
	bool handlesURI(const std::string& uri);
	void registerObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject, Poco::RemotingNG::Skeleton::Ptr pSkeleton);
	void unregisterObject(Poco::RemotingNG::RemoteObject::Ptr pRemoteObject);

	static const std::string SUBSCRIBE;
	static const std::string UNSUBSCRIBE;
	static const std::string HDR_CALLBACK;
	static const std::string HDR_TIMEOUT;
	static const std::string TIMEOUT_SECOND;
	static const std::string TIMEOUT_INFINITE;
	static const std::string EMPTY;

	enum
	{
		EVENT_REQUEST_TIMEOUT = 30,       /// timeout for event subscription HTTP requests (seconds)
		EVENT_SUBSCRIPTION_TIMEOUT = 1800 /// default timeout for event subscriptions (seconds)
	};
	
private:
	struct Subscription
	{
		Poco::RemotingNG::EventSubscriber::Ptr pEventSubscriber;
		Poco::Util::TimerTask::Ptr pTimerTask;
	};
	typedef std::map<std::string, Subscription> SubscriptionMap;
	typedef std::map<std::string, StateProvider*> StateProviderMap;
	
	SubscriptionMap _subscriptions;
	StateProviderMap _stateProviders;
	Poco::Util::Timer& _timer;
	int _subscriptionTimeout;
	Poco::FastMutex _mutex;
	Poco::Logger& _logger;
	
	friend class RequestHandler;
};


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_Listener_INCLUDED
