/* SPDX-License-Identifier: GPL-2.0 */

/* taken from $LINUX_SOURCE/arch/x86/include */

#include <immintrin.h>

#define mb()	_mm_mfence()

static inline void clflush_cache_range_opt(void *vaddr, unsigned long size)
{
	const unsigned long clflush_size = 64; // boot_cpu_data.x86_clflush_size;
	void *p = (void *)((unsigned long)vaddr & ~(clflush_size - 1));
	void *vend = (char*)vaddr + size;

	if (p >= vend)
		return;

	for (; p < vend; p += clflush_size)
		_mm_clflush(p);
}

/**
 * clflush_cache_range - flush a cache range with clflush
 * @vaddr:	virtual start address
 * @size:	number of bytes to flush
 *
 * CLFLUSHOPT is an unordered instruction which needs fencing with MFENCE or
 * SFENCE to avoid ordering issues.
 */
static inline void clflush_cache_range(void *vaddr, unsigned long size)
{
	mb();
	clflush_cache_range_opt(vaddr, size);
	mb();
}

void flush_data_cache(void *start, void *end)
{
	clflush_cache_range(start, end - start);
}
