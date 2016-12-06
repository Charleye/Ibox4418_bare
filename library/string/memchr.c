/*
 * libc/string/memchr.c
 */

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/string.h>

/*
 * Finds the first occurrence of a byte in a buffer
 */
void * memchr(const void * s, int c, size_t n)
{
	const unsigned char *p = s;

	while (n-- != 0)
	{
        if ((unsigned char)c == *p++)
        {
			return (void *)(p - 1);
		}
	}

	return NULL;
}
