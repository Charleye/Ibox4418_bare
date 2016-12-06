#ifndef __S5P4418_SERIAL_STDIO_H__
#define __S5P4418_SERIAL_STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

int serial_printf(int ch, const char * fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_SERIAL_STDIO_H__ */
