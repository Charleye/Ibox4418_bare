#ifndef __S5P4418_TICK_H__
#define __S5P4418_TICK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/sizes.h>
#include <linux/string.h>
#include <io.h>
#include <s5p4418-clk.h>
#include <s5p4418-timer.h>
#include <s5p4418-irq.h>

/*
 * When HZ = 1000, The Max delay is 24 days
 */
#define time_after(a, b)		(((s32_t)(b) - (s32_t)(a) < 0))
#define time_before(a, b)		time_after(b, a)
#define time_after_eq(a,b)		(((s32_t)(a) - (s32_t)(b) >= 0))
#define time_before_eq(a,b)		time_after_eq(b, a)

extern volatile u32_t jiffies;

void s5p4418_tick_initial(void);
u32_t get_system_hz(void);
u64_t clock_gettime(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_TICK_H__ */
