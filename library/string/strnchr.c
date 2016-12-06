/*
 * libc/string/strnchr.c
 */

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/string.h>

/*
 * Finds the first occurrence of a byte in a string
 */
char * strnchr(const char * s, size_t n, int c)
{
	for (; n-- && *s != '\0'; ++s)
		if (*s == (char)c)
			return (char *)s;
	return NULL;
}
