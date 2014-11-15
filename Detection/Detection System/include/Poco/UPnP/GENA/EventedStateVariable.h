//
// EventedStateVariable.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/EventedStateVariable.h#3 $
//
// Library: UPnP/GENA
// Package: StateVariables
// Module:  EventedStateVariable
//
// Definition of the EventedStateVariable class.
//
// Copyright (c) 2008-2011, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef UPnP_GENA_EventedStateVariable_INCLUDED
#define UPnP_GENA_EventedStateVariable_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/NumberFormatter.h"
#include <sstream>


namespace Poco {
namespace UPnP {
namespace GENA {


template <typename T, typename MP>
class EventedStateVariable
	/// A helper class template for implementing UPnP evented state
	/// variables.
	///
	/// Firing of events is controlled by a moderation policy.
	/// An EventModerationPolicy must be a class providing a member
	/// function named valueChanged() that takes as argument
	/// the new value. Three policy classes are predefined:
	///   - NoModerationPolicy: fires an event whenever the value
	///     changes.
	///   - MinimumDeltaModerationPolicy: fires an event when the value changes
	///     to a certain amount since the last time an event was sent.
	///   - MaximumRateModerationPolicy: fires an event at most every <n> seconds.
{
public:
	EventedStateVariable(const std::string& name, const T& initialValue, const MP& moderationPolicy):
		_name(name),
		_value(initialValue),
		_moderationPolicy(moderationPolicy)
		/// Creates a new EventedStateVariable with the given name and initialValue.
		/// The given moderation policy object is used to control the firing of
		/// events when the variable's value changes.
	{
	}
	
	~EventedStateVariable()
	{
	}

	const std::string& name() const
	{
		return _name;
	}
	
	const T& get() const
	{
		return _value;
	}
	
	void set(const T& value)
	{
		if (value != _value)
		{
			_value = value;
			_moderationPolicy.valueChanged(_value);
		}
	}
	
	std::string toString() const
	{
		return toString(_value);
	}
	
protected:
	static std::string toString(Poco::Int8 value)
	{
		return toString(static_cast<Poco::Int32>(value));
	}

	static std::string toString(Poco::UInt8 value)
	{
		return toString(static_cast<Poco::UInt32>(value));
	}

	static std::string toString(Poco::Int16 value)
	{
		return toString(static_cast<Poco::Int32>(value));
	}

	static std::string toString(Poco::UInt16 value)
	{
		return toString(static_cast<Poco::UInt32>(value));
	}

	static std::string toString(Poco::Int32 value)
	{
		return Poco::NumberFormatter::format(value);
	}

	static std::string toString(Poco::UInt32 value)
	{
		return Poco::NumberFormatter::format(value);
	}

	static std::string toString(float value)
	{
		return Poco::NumberFormatter::format(value);
	}

	static std::string toString(double value)
	{
		return Poco::NumberFormatter::format(value);
	}

	static std::string toString(bool value)
	{
		return value ? "1" : "0";
	}
	
	static std::string toString(const std::string& value)
	{
		return value;
	}
	
private:
	EventedStateVariable();

	std::string _name;
	T _value;
	MP _moderationPolicy;
};


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_EventedStateVariable_INCLUDED
