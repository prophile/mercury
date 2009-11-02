#include "KThread.h"

KThread::KThread ( KWord code, KWord stackAddress )
: threadState(K_THREAD_WAITING), nextThread(NULL)
{
	context.InitState(code, stackAddress, false);
	schedPolicy = new KFixedSchedulingPolicy(this, 40);
}
