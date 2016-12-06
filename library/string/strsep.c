/*
 * libc/string/strsep.c
 */

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/string.h>

/*
 * Extract token from string
 */
char * strsep(char ** s, const char * ct)
{
	char * sbegin = *s;
	char * end;

	if (sbegin == NULL)
		return NULL;

	end = strpbrk(sbegin, ct);
	if (end)
		*end++ = '\0';
	*s = end;

	return sbegin;
}
