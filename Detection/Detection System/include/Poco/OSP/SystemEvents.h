//
// SystemEvents.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/SystemEvents.h#1 $
//
// Library: OSP
// Package: Core
// Module:  SystemEvents
//
// Definition of the SystemEvents class.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef OSP_SystemEvents_INCLUDED
#define OSP_SystemEvents_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/BasicEvent.h"


namespace Poco {
namespace OSP {


class OSP_API SystemEvents
	/// This class provides various events that interested
	/// parties can subscribe to to become notified
	/// whenever the state of the OSP system changes.
	///
	/// Normally, these events are fired by the OSPSubsystem
	/// class. An application not using the OSPSubsystem class
	/// has to provide an instance of this class itself and
	/// fire these events at the appropriate time.
{
public:
	enum EventKind
	{
		EV_SYSTEM_STARTED,
		EV_SYSTEM_SHUTTING_DOWN
	};
	
	Poco::BasicEvent<EventKind> systemStarted;
		/// Fired after the OSP environment has been initialized
		/// and all bundles have been started.

	Poco::BasicEvent<EventKind> systemShuttingDown;
		/// Fired before the OSP environment is shut down.

	SystemEvents();
		/// Creates a SystemEvents object.
		
	~SystemEvents();
		/// Destroys the SystemEvents object.
		
private:
	SystemEvents(const SystemEvents&);
	SystemEvents& operator = (const SystemEvents&);
};


} } // namespace Poco::OSP


#endif // OSP_SystemEvents_INCLUDED
