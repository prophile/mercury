#ifndef __KSPINLOCK__
#define __KSPINLOCK__

#include "machine/KAtomic.h"

class KSpinLock
{
private:
	unsigned long value;
public:
	KSpinLock () : value(0) {}
	
	bool TryLock () { return KAtomic::Exchange(&value, 1) == 0; }
	void Lock () { while (!TryLock()); }
	void Unlock () { value = 0; }
};

#endif
