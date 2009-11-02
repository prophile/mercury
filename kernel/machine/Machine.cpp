#include "KSize.h"
#include "KAtomic.h"
#include "KContext.h"
#include "KTime.h"
#include "KInterrupts.h"

KWord K_INTERRUPT_CLOCK;
KWord K_INTERRUPT_SYSCALL;
KWord K_INTERRUPT_ILLEGAL_INSTRUCTION;
KWord K_INTERRUPT_PROTECTION_FAULT;

KWord KMachineClock ()
{
	static KWord ticks = 0;
	return ++ticks;
}

KWord KClockTicksPerSecond ()
{
	return 1000;
}

extern void context_get_interrupt(void*) __asm__("ctx.geti");
extern void context_get(void*) __asm__("ctx.get");
extern void context_set(void*) __asm__("ctx.set");

void KContext::GetInterrupt ( KContext& ctx )
{	
	context_get_interrupt((void*)&ctx);
}

void KContext::Get ( KContext& ctx )
{
	context_get((void*)&ctx);
}

void KContext::Set ( const KContext& ctx )
{
	context_set((void*)&ctx);
}

const static KWord AX_TRAQ = 0x12345678;

void KContext::Swap ( KContext& oldContext, const KContext& newContext )
{
	oldContext.ax = AX_TRAQ;
	Get(oldContext);
	if (oldContext.ax == AX_TRAQ)
	{
		Set(newContext);
	}
}
