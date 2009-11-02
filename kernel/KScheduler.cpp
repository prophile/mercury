#include "KScheduler.h"

static KScheduler* sharedScheduler = NULL;

KScheduler& KScheduler::SharedScheduler ()
{
	if (!sharedScheduler)
	{
		// TODO: make this thread-safe
		sharedScheduler = new KScheduler;
	}
	return *sharedScheduler;
}

void KScheduler::Schedule ( KThread* thread )
{
	KWord priorityLevel = thread->GetSchedulingPolicy()->GetPriority();
	queues[priorityLevel].InsertThread(thread);
	thread->SetState(K_THREAD_WAITING);
}

KThread* KScheduler::NextThread ()
{
	for (KWord i = PRIORITIES; i >= 0; i--)
	{
		if (!queues[i].IsEmpty())
		{
			KThread* thread = queues[i].GetThread();
			thread->SetState(K_THREAD_RUNNING);
			return thread;
		}
	}
	return NULL;
}
