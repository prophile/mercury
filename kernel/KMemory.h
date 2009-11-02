#ifndef __KMEMORY__
#define __KMEMORY__

#include "machine/KSize.h"

void kmeminit ();
void* kmalloc ( KWord length );
void kfree ( void* ptr );

inline void* operator new ( unsigned long length ) { return kmalloc(length); }
inline void operator delete ( void* ptr ) { kfree(ptr); }
inline void* operator new [] ( unsigned long length ) { return kmalloc(length); }
inline void operator delete [] ( void* ptr ) { kfree(ptr); }

#endif
