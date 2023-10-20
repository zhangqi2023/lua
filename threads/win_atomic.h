#ifndef SKYNET_WIN_ATOMIC_H
#define SKYNET_WIN_ATOMIC_H

#ifdef _WIN32

#include <Windows.h>

#define atomic_flag_ int
#define ATOMIC_FLAG_INIT_ 0

#define __sync_synchronize _mm_mfence
#define __sync_bool_compare_and_swap(SRC, OLD, NEW) InterlockedCompareExchange(SRC, NEW, OLD)

inline int __sync_lock_test_and_set(int* addr, int val)
{
	return static_cast<int>(_InterlockedExchange((long*)addr, val));
}

inline int __sync_lock_release(int* addr)
{
	return static_cast<int>(_InterlockedExchange((long*)addr, 0));
}

inline int __sync_fetch_and_add(int* addr, int val)
{
	return static_cast<int>(_InterlockedExchangeAdd((long*)addr, val));
}
inline int __sync_fetch_and_sub(int* addr, int val)
{
	return static_cast<int>(_InterlockedExchangeAdd((long*)addr, -val));
}
inline size_t __sync_fetch_and_sub(volatile size_t* addr, int val)
{
	return static_cast<size_t>(_InterlockedExchangeAdd((long*)addr, -val));
}
inline int __sync_add_and_fetch(int* addr, int val)
{
	return static_cast<int>(_InterlockedExchangeAdd((long*)addr, val) + val);
}
inline int __sync_sub_and_fetch(int* addr, int val)
{
    return static_cast<int>(_InterlockedExchangeAdd((long*)addr, -val) - val);
}
#endif

#endif
