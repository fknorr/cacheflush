/* SPDX-License-Identifier: GPL-2.0 */

/* taken from $LINUX_SOURCE/arch/powerpc/include */

#define mb()   __asm__ __volatile__ ("sync" : : : "memory")

static inline unsigned int l1_dcache_shift(void)
{
	// return ppc64_caches.l1d.log_block_size;
	return 7; // aka ilog2(l1_dcache_bytes)
}

static inline unsigned int l1_dcache_bytes(void)
{
	// return ppc64_caches.l1d.block_size;
	return 128; // POWER9 cache line size is 128
}

static inline void dcbf(void *addr)
{
	__asm__ __volatile__ ("dcbf 0, %0" : : "r"(addr) : "memory");
}

/**
 * flush_dcache_range(): Write any modified data cache blocks out to memory and
 * invalidate them. Does not invalidate the corresponding instruction cache
 * blocks.
 *
 * @start: the start address
 * @stop: the stop address (exclusive)
 */
static inline void flush_dcache_range(unsigned long start, unsigned long stop)
{
	unsigned long shift = l1_dcache_shift();
	unsigned long bytes = l1_dcache_bytes();
	void *addr = (void *)(start & ~(bytes - 1));
	unsigned long size = stop - (unsigned long)addr + (bytes - 1);
	unsigned long i;

	if (1) // (IS_ENABLED(CONFIG_PPC64))
		mb();	/* sync */

	for (i = 0; i < size >> shift; i++, addr += bytes)
		dcbf(addr);
	mb();	/* sync */

}

void flush_data_cache(void *start, void *end)
{
	flush_dcache_range((unsigned long) start, (unsigned long) end);
}
