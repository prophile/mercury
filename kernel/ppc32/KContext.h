#ifndef __KCONTEXT__
#define __KCONTEXT__

#include "KSize.h"

struct KContext
{
	KWord ip, lr, ctr;
	KWord gprs[32];

	KContext() {}
	~KContext () {}
	
	void InitState ( KWord code, KWord stackAddress, bool inKernel )
	{
		ip = code;
		lr = 0;
		ctr = 0;
		for (int i = 0; i < 32; i++)
		{
			gprs[i] = 0;
		}
		gprs[1] = stackAddress;
	}
	
	void InitCall ( KWord funcAddress, KWord argument, KWord stackAddress, KWord stackSize, bool inKernel )
	{
		InitState(funcAddress, stackAddress + stackSize, inKernel);
		gprs[3] = argument;
	}
	
	// get the context from before the interrupt
	static void GetInterrupt ( KContext& ctx );
	static void Get ( KContext& ctx );
	static void Set ( const KContext& ctx );
	static void Swap ( KContext& oldContext, const KContext& newContext );
};

#endif
