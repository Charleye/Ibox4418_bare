/*
 * libc/string/strrchr.c
 */

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/string.h>

/*
 * Finds the last occurrence of a byte in a string
 */
char * strrchr(const char * s, int c)
{
	const char * p = s + strlen(s);

	do {
	   if (*p == (char)c)
		   return (char *)p;
	} while (--p >= s);

	return NULL;
}
