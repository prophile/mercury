#ifndef __KCORE__
#define __KCORE__

#include "KForward.h"
#include "machine/KContext.h"

class KCore
{
private:
	KWord id;
	KPort* controlPort;
	KThread* activeThread;
	KContext context;
	static const KWord STACKSIZE = 2048;
	unsigned char stack[STACKSIZE];
public:
	KCore ( KWord id );
	~KCore ();
	
	KPort* GetControlPort () { return controlPort; }
	KThread* GetActiveThread () { return activeThread; }
	
	void Loop ();
	
	void HandleInterrupt ( KWord interrupt );
};

#endif
