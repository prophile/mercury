#include "KForward.h"
#include "KCore.h"
#include "KMemory.h"

void entry_primary () __asm__("_start");
void entry_secondary () __asm__("_start2");

void entry_primary ()
{
	kmeminit();
	KCore* firstCore = new KCore(0);
	firstCore->Loop();
}
