#ifndef CACHEFLUSH_H
#define CACHEFLUSH_H

/* SPDX-License-Identifier: GPL-2.0 */

#ifdef __cplusplus
extern "C" {
#endif

void flush_data_cache(const void *start, const void *end);

#ifdef __cplusplus
}
#endif

#endif
