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
	ctx.ip  = ISR_ctx[ 0];
	ctx.sp  = ISR_ctx[ 1];
	ctx.bp  = ISR_ctx[ 2];
	ctx.ax  = ISR_ctx[ 3];
	ctx.bx  = ISR_ctx[ 4];
	ctx.cx  = ISR_ctx[ 5];
	ctx.dx  = ISR_ctx[ 6];
	ctx.si  = ISR_ctx[ 7];
	ctx.di  = ISR_ctx[ 8];
	ctx.r8  = ISR_ctx[ 9];
	ctx.r9  = ISR_ctx[10];
	ctx.r10 = ISR_ctx[11];
	ctx.r11 = ISR_ctx[12];
	ctx.r12 = ISR_ctx[13];
	ctx.r13 = ISR_ctx[14];
	ctx.r14 = ISR_ctx[15];
	ctx.r15 = ISR_ctx[16];
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
