#include "KPortMap.h"

KPortMap::KPortMap ()
{
	for (KWord i = 0; i < BITMAPS_PER_MAP; i++)
	{
		bitmaps[i] = 0UL;
	}
	overflow = NULL;
}

KPortMap::~KPortMap ()
{
	if (overflow)
		delete overflow;
	for (KWord i = 0; i < BITMAPS_PER_MAP; i++)
	{
		if (bitmaps[i])
		{
			for (KWord j = 0; j < KWordSize; j++)
			{
				if (bitmaps[i] & (1 << j))
				{
					ports[i*KWordSize + j]->Release();
				}
			}
		}
	}
}

KWord KPortMap::Insert ( KPort* port )
{
	for (KWord i = 0; i < BITMAPS_PER_MAP; i++)
	{
		if (bitmaps[i] == -1UL)
			continue;
		// find an insertion position in here
		// grab the bitmap
		KWord bitmap = bitmaps[i];
		// we're looking a 0
		// invert it
		bitmap = ~bitmap;
		// we're now looking for a one
		// count the number of trailing zeroes
		unsigned tz = KWordCTZ(bitmap);
		// mark the bitmap
		bitmaps[i] |= (1 << tz);
		// grab the slot
		KWord index = KWordSize*i + tz;
		ports[index] = port->Retain();
		return index;
	}
	if (!overflow)
	{
		overflow = new KPortMap;
	}
	return PORTS_PER_MAP + overflow->Insert(port);
}

void KPortMap::Remove ( KWord index )
{
	if (index > BITMAPS_PER_MAP)
	{
		if (overflow)
		{
			overflow->Remove(index - BITMAPS_PER_MAP);
		}
	}
	else
	{
		KWord mapID = index / KWordSize;
		bitmaps[mapID] &= ~(1 << index % KWordSize);
	}
}

KPort* KPortMap::GetPort ( KWord index )
{
	if (index > BITMAPS_PER_MAP)
	{
		if (overflow)
		{
			return overflow->GetPort(index - BITMAPS_PER_MAP);
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return ports[index];
	}
}
