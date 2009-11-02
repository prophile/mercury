#include "KCore.h"
#include "KThread.h"
#include "KScheduler.h"
#include "machine/KInterrupts.h"

static void dispatch_loop ( KWord word );

KCore::KCore ( KWord coreID )
: id(coreID), activeThread(NULL)
{
	controlPort = new KPort;
	context.InitCall((KWord)dispatch_loop, (KWord)this, (KWord)stack, STACKSIZE, true);
}

KCore::~KCore ()
{
	controlPort->Release();
}

void KCore::Loop ()
{
	// release last thread
	KScheduler& sched = KScheduler::SharedScheduler();
	sched.Lock();
	if (activeThread)
	{
		if (activeThread->GetState() != K_THREAD_KIA)
		{
			sched.Schedule(activeThread);
		}
		else
		{
			delete activeThread;
		}
	}
	activeThread = NULL;
	sched.Unlock();
	// handle port messages here
	sched.Lock();
	activeThread = sched.NextThread();
	sched.Unlock();
}

static void dispatch_loop ( KWord word )
{
	KCore* core = (KCore*)word;
	core->Loop();
	if (activeThread)
	{
		// run it
		KContext::Set(activeThread->GetContext());
	}
	else
	{
		// sleep
		__asm__("hlt");
	}
}

void HandleInterrupt ( KWord interrupt )
{
	KContext oldContext;
	GetInterrupt(oldContext);
	if (activeThread)
	{
		activeThread->GetContext() = oldContext;
	}
	if (interrupt == K_INTERRUPT_SYSCALL)
	{
		// handle syscall
	}
	else if (interrupt == K_INTERRUPT_CLOCK)
	{
		// handle clock
	}
	else if (interrupt == K_INTERRUPT_ILLEGAL_INSTRUCTION)
	{
		// handle illegal instruction
		activeThread->SetState(K_THREAD_KIA);
	}
	else if (interrupt == K_INTERRUPT_PROTECTION_FAULT)
	{
		// handle protection fault - this may be valid, don't assume kill
		// well, actually, do
		activeThread->SetState(K_THREAD_KIA);
	}
}
