#ifndef __KSCHEDULINGPOLICY__
#define __KSCHEDULINGPOLICY__

#include "KForward.h"

class KSchedulingPolicy
{
private:
	KThread* thread;
public:
	KSchedulingPolicy ( KThread* thr ) : thread(thr) {}
	virtual ~KSchedulingPolicy () {}
	
	const KThread* GetThread () const { return thread; }
	virtual int GetPriority () { return 0; }
};

class KFixedSchedulingPolicy : public KSchedulingPolicy
{
private:
	int prio;
public:
	KFixedSchedulingPolicy ( KThread* thr, int priority ) : KSchedulingPolicy(thr), prio(priority) {}
	virtual ~KFixedSchedulingPolicy () {}
	
	virtual int GetPriority () { return prio; }
};

#endif
