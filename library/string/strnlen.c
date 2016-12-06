/*
 * libc/string/strnlen.c
 */

#include <linux/types.h>
#include <linux/string.h>

/*
 * Determine the length of a fixed-size string
 */
size_t strnlen(const char * s, size_t n)
{
	const char * sc;

	for (sc = s; n-- && *sc != '\0'; ++sc);
	return sc - s;
}
