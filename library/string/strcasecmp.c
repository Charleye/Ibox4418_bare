/*
 * libc/string/strcasecmp.c
 */

#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/string.h>

/*
 * Compare two strings ignoring case
 */
int strcasecmp(const char * s1, const char * s2)
{
	int c1, c2;

	do {
		c1 = tolower(*s1++);
		c2 = tolower(*s2++);
	} while (c1 == c2 && c1 != 0);

	return c1 - c2;
}
