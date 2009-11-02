#ifndef __KATOMIC__
#define __KATOMIC__

namespace KAtomic
{

static inline unsigned long Exchange ( volatile unsigned long* pointer, unsigned long value )
	{ return __sync_lock_test_and_set(pointer, value); }
static inline bool CompareAndSwap ( volatile unsigned long* pointer, unsigned long oldValue, unsigned long newValue )
	{ return __sync_bool_compare_and_swap(pointer, oldValue, newValue); }

static inline unsigned long FetchAdd ( volatile unsigned long* pointer, long value )
	{ return __sync_fetch_and_add(pointer, value); }

template <class T>
static inline T* ExchangePtr ( volatile T** pointer, T* value )
	{ return (T*)Exchange((volatile unsigned long*)pointer, (unsigned long)value); }
template <class T>
static inline bool CompareAndSwapPtr ( volatile T** pointer, T* oldValue, T* newValue )
	{ return CompareAndSwap((volatile unsigned long*)pointer, (unsigned long)oldValue, (unsigned long)newValue); }

};

#endif
