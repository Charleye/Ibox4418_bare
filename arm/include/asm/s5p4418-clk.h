#ifndef __S5P4418_CLK_H__
#define __S5P4418_CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rstcon.h>
#include <reg-sys.h>
#include <reg-clk.h>
#include <reg-timer.h>
#include <reg-pwm.h>
#include <clock/clk.h>

void s5p4418_clk_init(void);
void s5p4418_clk_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_CLK_H__ */
