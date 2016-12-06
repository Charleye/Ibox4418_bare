#ifndef __S5P4418_TIMER_H__
#define __S5P4418_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/string.h>
#include <linux/stddef.h>
#include <io.h>
#include <s5p4418-rstcon.h>
#include <s5p4418-gpio.h>
#include <s5p4418-clk.h>
#include <reg-timer.h>

void s5p4418_timer_reset(void);
void s5p4418_timer_start(int ch, int irqon);
void s5p4418_timer_stop(int ch, int irqon);
u64_t s5p4418_timer_calc_tin(int ch, u32_t period);
void s5p4418_timer_count(int ch, u32_t cnt);
u32_t s5p4418_timer_read(int ch);
void s5p4418_timer_irq_clear(int ch);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_TIMER_H__ */
