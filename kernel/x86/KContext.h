#ifndef __KCONTEXT__
#define __KCONTEXT__

#include "KSize.h"

struct KContext
{
	KWord ip, sp, bp, ax, bx, cx, dx, si, di;
#ifdef __LP64__
	KWord r8, r9, r10, r11, r12, r13, r14, r15;
#endif

	KContext() {}
	~KContext () {}
	
	void InitState ( KWord code, KWord stackAddress, bool inKernel )
	{
		ip = code;
		sp = bp = stackAddress;
		ax = bx = cx = dx = si = di = 0;
	}
	
	void InitCall ( KWord funcAddress, KWord argument, KWord stackAddress, KWord stackSize, bool inKernel )
	{
		bp = stackAddress + stackSize;
		KWord* stack = (KWord*)(bp);
		ip = funcAddress;
		*(--stack) = 0; // return address
#ifndef __LP64__
		*(--stack) = argument; // function argument
#endif
		sp = (KWord)stack;
		ax = bx = cx = dx = si = di = 0;
#ifdef __LP64__
		si = argument;
		r8 = r9 = r10 = r11 = r12 = r13 = r14 = r15 = 0;
#endif
	}
	
	// get the context from before the interrupt
	static void GetInterrupt ( KContext& ctx );
	static void Get ( KContext& ctx );
	static void Set ( const KContext& ctx );
	static void Swap ( KContext& oldContext, const KContext& newContext );
};

#endif
