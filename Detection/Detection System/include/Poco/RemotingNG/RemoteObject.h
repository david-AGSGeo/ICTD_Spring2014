//
// RemoteObject.h
//
// $Id: //poco/1.4/RemotingNG/include/Poco/RemotingNG/RemoteObject.h#1 $
//
// Library: RemotingNG
// Package: ORB
// Module:  RemoteObject
//
// Definition of the RemoteObject class.
//
// Copyright (c) 2006-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_RemoteObject_INCLUDED
#define RemotingNG_RemoteObject_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace RemotingNG {
	
	
class EventListener;


class RemotingNG_API RemoteObject: public Identifiable
	/// A RemoteObject forwards method calls to the
	/// local service object.
	///
	/// For every service object, the RemotingNG code generator
	/// generates a RemoteObject that is a subclass of the
	/// service object's interface class.
{
public:
	typedef Poco::AutoPtr<RemoteObject> Ptr;

	RemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid);
		/// Creates a RemoteObject.

	virtual ~RemoteObject();
		/// Destroys the RemoteObject.

	virtual bool remoting__hasEvents() const;
		/// Returns true if the service object has events, false otherwise.
		/// Must be overridden by subclasses. The default implementation
		/// always returns false.

	virtual void remoting__registerEvents(EventListener& listener);
		/// Register events at the given EventListener and store a
		/// pointer to the EventListener object (_pEventListener).

	virtual void remoting__unregisterEvents(EventListener& listener);
		/// Unregister events.

protected:
	Poco::FastMutex& mutex() const;
	
	EventListener* _pEventListener;

private:
	mutable Poco::FastMutex _mutex;
};


//
// inlines
//
inline Poco::FastMutex& RemoteObject::mutex() const
{
	return _mutex;
}


inline bool RemoteObject::remoting__hasEvents() const
{
	return false;
}


} } // namespace Poco::RemotingNG


#endif // RemotingNG_RemoteObject_INCLUDED
