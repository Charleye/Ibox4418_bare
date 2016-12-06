/*
 * libc/string/strdup.c
 */

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/malloc.h>
#include <linux/string.h>

/*
 * Allocates and duplicates a string
 */
char * strdup(const char * s)
{
	char * p;

	if(!s)
		return NULL;

	p = malloc(strlen(s) + 1);
	if(p)
		return(strcpy(p, s));

	return NULL;
}
