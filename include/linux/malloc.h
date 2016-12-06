#ifndef __MALLOC_H__
#define __MALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/assert.h>
#include <linux/sizes.h>
#include <linux/string.h>

void * memory_pool_create(void * pool, size_t size);
void memory_pool_destroy(void * pool);
void memory_pool_stat(void * pool, size_t * used, size_t * free);

void malloc_init(void);
void malloc_exit(void);

void * malloc(size_t size);
void * memalign(size_t align, size_t size);
void * realloc(void * ptr, size_t size);
void * calloc(size_t nmemb, size_t size);
void free(void * ptr);

#ifdef __cplusplus
}
#endif

#endif /* __MALLOC_H__ */
