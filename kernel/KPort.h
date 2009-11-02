#ifndef __KPORT__
#define __KPORT__

#include "KForward.h"
#include "machine/KAtomic.h"
#include "KPortMessage.h"

class KPort
{
private:
	volatile KPortMessage* queuedMessage;
	KWord refcount;
public:
	KPort () {}
	~KPort () {}
	
	KPort* Retain () { KAtomic::FetchAdd(&refcount, 1); return this; }
	void Release () { if (KAtomic::FetchAdd(&refcount, -1) == 1) delete this; }
	
	bool PushMessage ( KPortMessage* message );
	KPortMessage* PopMessage ();
};

#endif
