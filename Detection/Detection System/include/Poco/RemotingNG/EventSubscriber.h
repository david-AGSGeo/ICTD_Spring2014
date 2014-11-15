//
// EventSubscriber.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/EventSubscriber.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  EventSubscriber
//
// Definition of the EventSubscriber class.
//
// Copyright (c) 2009-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_EventSubscriber_INCLUDED
#define RemotingNG_EventSubscriber_INCLUDED


#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/RemotingNG/RemotingNG.h"
#include "Poco/RemotingNG/Transport.h"
#include "Poco/RemotingNG/Skeleton.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include <set>
#include <map>


namespace Poco {
namespace RemotingNG {


class RemotingNG_API EventSubscriber: public Skeleton
	/// The EventSubscriber is responsible for deserializing
	/// and dispatching event messages received from a
	/// server via an EventListener to a Proxy object.
{
public:
	typedef Poco::AutoPtr<EventSubscriber> Ptr;

	EventSubscriber(const std::string& uri);
		/// Creates an EventSubscriber, using the given URI.
		///
		/// The given URI is used for subscribing to the event.
		/// Usually, this will be the URI of the remote object
		/// providing the events for this EventSubscriber.

	virtual ~EventSubscriber();
		/// Destroys the EventSubscriber.

	const std::string& uri() const;
		/// Returns the URI of the remote object providing the
		/// events for this EventSubscriber.

private:
	EventSubscriber(const EventSubscriber&);
	EventSubscriber& operator = (const EventSubscriber&);

	std::string _uri;
};


//
// inlines
//
inline const std::string& EventSubscriber::uri() const
{
	return _uri;
}


} } // namespace Poco::RemotingNG


#endif // RemotingNG_EventSubscriber_INCLUDED
