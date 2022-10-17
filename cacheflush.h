#ifndef CACHEFLUSH_H
#define CACHEFLUSH_H

/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifdef __cplusplus
extern "C" {
#endif

void flush_data_cache(void *start, void *end);

#ifdef __cplusplus
}
#endif

#endif
