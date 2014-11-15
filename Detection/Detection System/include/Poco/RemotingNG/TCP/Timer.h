//
// Timer.h
//
// $Id: //poco/1.4/RemotingNG/TCP/include/Poco/RemotingNG/TCP/Timer.h#2 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  Timer
//
// Definition of the Timer class.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#ifndef RemotingNG_TCP_Timer_INCLUDED
#define RemotingNG_TCP_Timer_INCLUDED


#include "Poco/RemotingNG/TCP/TCP.h"
#include "Poco/TimedNotificationQueue.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


class RemotingNGTCP_API TimerTask: public Poco::RefCountedObject, public Poco::Runnable
	/// A task that can be scheduled for one-time or 
	/// repeated execution by a Timer.
	///
	/// This is an abstract class. Subclasses must override the run() member
	/// function to implement the actual task logic.
{
public:
	typedef Poco::AutoPtr<TimerTask> Ptr;
	
	TimerTask();
		/// Creates the TimerTask.
		
	void cancel();
		/// Cancels the execution of the timer.
		/// If the task has been scheduled for one-time execution and has 
		/// not yet run, or has not yet been scheduled, it will never run. 
		/// If the task has been scheduled for repeated execution, it will never 
		/// run again. If the task is running when this call occurs, the task 
		/// will run to completion, but will never run again.	
	
	bool isCancelled() const;
		/// Returns true iff the TimerTask has been cancelled by a call
		/// to cancel().
	
	Poco::Timestamp lastExecution() const;
		/// Returns the time of the last execution of the timer task.
		///
		/// Returns 0 if the timer has never been executed.
		
protected:
	~TimerTask();
		/// Destroys the TimerTask.
	
private:
	TimerTask(const TimerTask&);
	TimerTask& operator = (const TimerTask&);
	
	Poco::Timestamp _lastExecution;
	bool _isCancelled;
	
	friend class TaskNotification;
};


class RemotingNGTCP_API Timer: protected Poco::Runnable
	/// A Timer allows to schedule tasks (TimerTask objects) for future execution 
	/// in a background thread. Tasks may be scheduled for one-time execution, 
	/// or for repeated execution at regular intervals. 
	///
	/// The Timer object creates a thread that executes all scheduled tasks
	/// sequentially. Therefore, tasks should complete their work as quickly
	/// as possible, otherwise subsequent tasks may be delayed.
	///
	/// Timer is save for multithreaded use - multiple threads can schedule
	/// new tasks simultaneously.
	///
	/// This is a simplified version of the Poco::Util::Timer class.
{
public:
	Timer();
		/// Creates the Timer.
	
	~Timer();
		/// Destroys the Timer, cancelling all pending tasks.
		
	void cancel(bool wait = false);
		/// Cancels all pending tasks.
		///
		/// If a task is currently running, it is allowed to finish.
		///
		/// Task cancellation is done asynchronously. If wait
		/// is false, cancel() returns immediately and the
		/// task queue will be purged as soon as the currently
		/// running task finishes. If wait is true, waits
		/// until the queue has been purged.
			
	void scheduleAtFixedRate(TimerTask::Ptr pTask, long delay, long interval);
		/// Schedules a task for periodic execution at a fixed rate.
		///
		/// The task is first executed after the given delay.
		/// Subsequently, the task is executed periodically 
		/// every number of milliseconds specified by interval.
		///
		/// If task execution takes longer than the given interval,
		/// further executions are delayed.

protected:
	void run();
		
private:
	Timer(const Timer&);
	Timer& operator = (const Timer&);
	
	Poco::TimedNotificationQueue _queue;
	Poco::Thread _thread;
};


//
// inlines
//
inline bool TimerTask::isCancelled() const
{
	return _isCancelled;
}


inline Poco::Timestamp TimerTask::lastExecution() const
{
	return _lastExecution;
}


} } } // namespace Poco::RemotingNG::TCP


#endif // RemotingNG_TCP_Timer_INCLUDED
