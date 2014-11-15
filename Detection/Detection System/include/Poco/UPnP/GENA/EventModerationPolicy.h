//
// EventModerationPolicy.h
//
// $Id: //poco/1.4/UPnP/GENA/include/Poco/UPnP/GENA/EventModerationPolicy.h#1 $
//
// Library: UPnP/GENA
// Package: StateVariables
// Module:  EventModerationPolicy
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


#ifndef UPnP_GENA_EventModerationPolicy_INCLUDED
#define UPnP_GENA_EventModerationPolicy_INCLUDED


#include "Poco/UPnP/GENA/GENA.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTaskAdapter.h"
#include "Poco/BasicEvent.h"
#include "Poco/Mutex.h"


namespace Poco {
namespace UPnP {
namespace GENA {


class UPnPGENA_API EventModerationPolicy
	/// An EventModerationPolicy controls the frequency of events
	/// sent when an evented state variable changes. Any class or
	/// class template that fulfills the following criteria can be 
	/// used as EventModerationPolicy:
	///    * The class must provide a public member function
	///      named valueChanged that takes as only argument
	///      the new value of the state variable (either passed
	///      by value or by const reference).
	///    * valueChanged() must check whether the criteria
	///      for firing an event are fulfilled, and in if this is 
	///      the case, fire the event.
	///    * Typically, the Poco::BasicEvent instance will be
	///      passed to the policy object through the constructor.
{
};


template <typename T>
class NoModerationPolicy: public EventModerationPolicy
	/// This event moderation policy does no moderation and
	/// fires an event whenever the event variable's value changes
	/// (the valueChanged() member function is called).
	///
	/// This moderation policy can be used with any event value type
	/// (numeric and string).
{
public:
	typedef Poco::BasicEvent<const T> Event;

	NoModerationPolicy(Event& event):
		_pEvent(&event)
	{
	}
	
	void valueChanged(const T& newValue)
	{
		(*_pEvent)(this, newValue);
	}
	
private:
	NoModerationPolicy();
	
	Event* _pEvent;
};


template <typename T>
class MinimumDeltaModerationPolicy: public EventModerationPolicy
	/// This event moderation policy will fire an event whenever the
	/// value of an event variable changes more than the given
	/// minimum delta since the last time an event was sent.
	///
	/// This moderation policy can only be used with numeric (int, float, etc.)
	/// event value types.
{
public:
	typedef Poco::BasicEvent<const T> Event;
	
	MinimumDeltaModerationPolicy(Event& event, T initialValue, T minimumDelta):
		_pEvent(&event),
		_value(initialValue),
		_minimumDelta(minimumDelta)
	{
	}
	
	MinimumDeltaModerationPolicy(const MinimumDeltaModerationPolicy& other):
		_pEvent(other._pEvent),
		_value(other._value),
		_minimumDelta(other._minimumDelta)
	{
	}
	
	MinimumDeltaModerationPolicy& operator = (const MinimumDeltaModerationPolicy& other)
	{
		if (&other != this)
		{
			_pEvent       = other._pEvent;
			_value        = other._value;
			_minimumDelta = other._minimumDelta;
		}
		return *this;
	}
	
	void valueChanged(T value)
	{
		T diff = value - _value;
		if (diff < 0) diff = -diff;
		if (diff >= _minimumDelta)
		{
			_value = value;
			(*_pEvent)(this, _value);
		}
	}
	
private:
	Event* _pEvent;
	T _value;
	T _minimumDelta;
};


template <typename T>
class MaximumRateModerationPolicy: public EventModerationPolicy
	/// This event moderation policy will fire an event at most every n seconds.
	/// An external Poco::Util::Timer instance must be supplied.
{
public:
	typedef Poco::BasicEvent<const T> Event;

	MaximumRateModerationPolicy(Event& event, const T& initialValue, int maximumRate, Poco::Util::Timer& timer):
		_pEvent(&event),
		_value(initialValue),
		_maximumRate(maximumRate),
		_lastEvent(0),
		_pTimer(&timer)
	{
	}
	
	MaximumRateModerationPolicy(const MaximumRateModerationPolicy& other):
		_pEvent(other._pEvent),
		_value(other._value),
		_maximumRate(other._maximumRate),
		_lastEvent(0),
		_pTimer(other._pTimer)
	{
	}
	
	MaximumRateModerationPolicy& operator = (const MaximumRateModerationPolicy& other)
	{
		if (&other != this)
		{
			_pEvent      = other._pEvent;
			_value       = other._value;
			_maximumRate = other._maximumRate;
			_pTimer      = other._pTimer;
		}
		return *this;
	}

	void valueChanged(const T& newValue)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (newValue != _value)
		{
			_value = newValue;
			if (_lastEvent.elapsed()/Poco::Timestamp::resolution() >= _maximumRate)
			{
				if (_pTimerTask)
				{
					_pTimerTask->cancel();
					_pTimerTask = 0;
				}
				(*_pEvent)(this, _value);
				_lastEvent.update();
			}
			else if (!_pTimerTask)
			{
				_pTimerTask = new Poco::Util::TimerTaskAdapter<MaximumRateModerationPolicy>(*this, &MaximumRateModerationPolicy::onTimer);
				_pTimer->schedule(_pTimerTask, _lastEvent + _maximumRate*Poco::Timestamp::resolution());
			}
		}
	}
	
protected:
	void onTimer(Poco::Util::TimerTask&)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		
		(*_pEvent)(this, _value);
		_lastEvent.update();
		_pTimerTask = 0;
	}
	
private:
	MaximumRateModerationPolicy();
	
	Event* _pEvent;
	T _value;
	int _maximumRate;
	Poco::Timestamp _lastEvent;
	Poco::Util::Timer* _pTimer;
	Poco::Util::TimerTask::Ptr _pTimerTask;
	Poco::FastMutex _mutex;
};


} } } // namespace Poco::UPnP::GENA


#endif // UPnP_GENA_EventModerationPolicy_INCLUDED
