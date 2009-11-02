#ifndef __KSCHEDULER__
#define __KSCHEDULER__

#include "KForward.h"
#include "KThread.h"
#include "KSpinLock.h"
#include "machine/KSize.h"

class KScheduler
{
public:
	static const int PRIORITIES = 70;
private:
	KSpinLock lock;
	class RunQueue
	{
	private:
		static const KWord RQSIZE = 14;
		KWord length;
		KThread* queue[RQSIZE];
		RunQueue* overflow;
	public:
		RunQueue () : length(0), overflow(NULL) {}
		~RunQueue () { if (overflow) delete overflow; }
		
		bool IsEmpty () const { return length == 0; }
		void InsertThread ( KThread* thread )
		{
			if (length == RQSIZE)
			{
				if (!overflow)
				{
					overflow = new RunQueue;
				}
				// tail recursive
				overflow->InsertThread(thread);
			}
			else
			{
				queue[length++] = thread;
			}
		}
		KThread* GetThread ()
		{
			KThread* result = queue[0];
			KThread* backshift = NULL;
			if (overflow)
			{
				backshift = overflow->GetThread();
				if (overflow->IsEmpty())
				{
					delete overflow;
					overflow = NULL;
				}
			}
			length--;
			for (KWord i = 0; i < length; i++)
			{
				queue[i] = queue[i + 1];
			}
			if (backshift)
			{
				queue[length++] = backshift;
			}
			return result;
		}
	};
	RunQueue queues[PRIORITIES];

	KScheduler () {}
	~KScheduler () {}
public:	
	static KScheduler& SharedScheduler ();
	
	void Lock () { lock.Lock(); }
	void Unlock () { lock.Unlock(); }
	
	void Schedule ( KThread* thread );
	KThread* NextThread ();
};


#endif
