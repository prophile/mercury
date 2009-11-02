#ifndef __KTHREAD__
#define __KTHREAD__

#include "KForward.h"
#include "KSchedulingPolicy.h"

enum KThreadState
{
	K_THREAD_WAITING, // in scheduler run queues, waiting to be executed
	K_THREAD_RUNNING, // actively running as we speak
	K_THREAD_BLOCKED, // blocking on port activity
	K_THREAD_KIA,     // thread died while running, waiting for core to clean up
	K_THREAD_MIA      // thread died while not running, waiting for other cleanup
};

class KThread
{
private:
	KThreadState threadState;
	KContext context;
	KSchedulingPolicy* schedPolicy;
	KThread* nextThread;
public:
	KThread ( KWord code, KWord stackAddress );
	~KThread () { delete schedPolicy; }
	
	KThreadState GetState () const { return threadState; }
	void SetState ( KThreadState newState ) { threadState = newState; }
	KContext& GetContext () { return context; }
	void SetSchedulingPolicy ( KSchedulingPolicy* policy ) { delete schedPolicy; schedPolicy = policy; }
	KSchedulingPolicy* GetSchedulingPolicy () { return schedPolicy; }
	KThread* GetNextThread () { return nextThread; }
	void SetNextThread ( KThread* nt ) { nextThread = nt; }
};

#endif
