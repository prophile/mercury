#include "KSize.h"
#include "KAtomic.h"
#include "KContext.h"
#include "KTime.h"
#include "KInterrupts.h"

KWord K_INTERRUPT_CLOCK;
KWord K_INTERRUPT_SYSCALL = 3;
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

const void* KHeapBase = (const void*)0x40000;

extern void context_get(void*) __asm__("ctx.get");
extern void context_set(void*) __asm__("ctx.set");

extern KWord* ISR_ctx __asm__("__ISR_regs");

void KContext::GetInterrupt ( KContext& ctx )
{	
	ctx.ip  = ISR_ctx[0];
	ctx.lr  = ISR_ctx[1];
	ctx.ctr = ISR_ctx[2];
	for (int i = 0; i < 32; i++)
	{
		ctx.gprs[i] = ISR_ctx[i];
	}
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

void ISR () __asm__("_ISR");

void ISR ()
{
}
