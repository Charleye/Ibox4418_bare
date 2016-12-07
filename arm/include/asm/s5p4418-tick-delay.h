#ifndef __S5P4418_TICK_DELAY_H__
#define __S5P4418_TICK_DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <stddef.h>
#include <sizes.h>
#include <string.h>
#include <io.h>
#include <s5p4418-clk.h>
#include <s5p4418-tick.h>

void s5p4418_tick_delay_init(void);
void udelay(u32_t us);
void mdelay(u32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_TICK_DELAY_H__ */
