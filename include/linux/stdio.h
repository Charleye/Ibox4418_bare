#ifndef __STDIO_H__
#define __STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/ctype.h>
#include <linux/errno.h>
#include <linux/stdarg.h>
#include <linux/stddef.h>
#include <linux/stdlib.h>
#include <linux/limits.h>
#include <linux/string.h>

int vsnprintf(char * buf, size_t n, const char * fmt, va_list ap);
int vsscanf(const char * buf, const char * fmt, va_list ap);
int sprintf(char * buf, const char * fmt, ...);
int snprintf(char * buf, size_t n, const char * fmt, ...);
int sscanf(const char * buf, const char * fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __STDIO_H__ */
