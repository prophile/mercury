#ifndef __KPORTMAP__
#define __KPORTMAP__

#include "KPort.h"
#include "machine/KSize.h"

class KPortMap
{
private:
	static const KWord PORTS_PER_MAP = 128;
	static const KWord BITMAPS_PER_MAP = PORTS_PER_MAP / KWordSize;
	KWord bitmaps[BITMAPS_PER_MAP];
	KPort* ports[PORTS_PER_MAP];
	KPortMap* overflow;
public:
	KPortMap ();
	~KPortMap ();
	
	unsigned long Insert ( KPort* port );
	void Remove ( KWord index );
	KPort* GetPort ( KWord index );
};

#endif
