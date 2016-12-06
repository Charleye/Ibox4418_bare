/*
 * libc/string/strchr.c
 */

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/string.h>

/*
 * Finds the first occurrence of a byte in a string
 */
char * strchr(const char * s, int c)
{
	for (; *s != (char)c; ++s)
		if (*s == '\0')
			return NULL;
	return (char *)s;
}
