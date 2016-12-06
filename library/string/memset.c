/*
 * libc/string/memset.c
 */

#include <linux/types.h>
#include <linux/string.h>

static void * __memset(void * s, int c, size_t n)
{
	char * xs = s;

	while (n--)
		*xs++ = c;

	return s;
}

/*
 * Fills a buffer with a repeated byte/wchar_t
 */
extern __typeof(__memset) memset __attribute__((weak, alias("__memset")));
