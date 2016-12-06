/*
 * libc/string/strncat.c
 */

#include <linux/types.h>
#include <linux/string.h>

/*
 * Appends no more than n bytes from one string to another
 */
char * strncat(char * dest, const char * src, size_t n)
{
	char * tmp = dest;

	if (n)
	{
		while (*dest)
			dest++;
		while ((*dest++ = *src++) != 0)
		{
			if (--n == 0)
			{
				*dest = '\0';
				break;
			}
		}
	}

	return tmp;
}
