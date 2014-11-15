//
// StateProvider.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/StateProvider.h#1 $
//
// Library: UPnP/GENA
// Package: StateVariables
// Module:  StateProvider
//
// Definition of the EventModerationPolicy class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_GENA_StateProvider_INCLUDED
#define UPnP_GENA_StateProvider_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include <utility>
#include <vector>


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API StateProvider
	/// This interface should be provided by all UPnP services
	/// supporting evented state variables. This interface will
	/// be used by the framework to obtain the current state
	/// of the service whenever a new event subscription is
	/// received.
{
public:
	typedef std::pair<std::string, std::string> NameValuePair;
	typedef std::vector<NameValuePair> StateVec;
	
	virtual StateVec currentState() const = 0;
		/// Returns a vector containing the name and value of
		/// all evented state variables.
		
protected:
	virtual ~StateProvider();
};


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_StateProvider_INCLUDED
