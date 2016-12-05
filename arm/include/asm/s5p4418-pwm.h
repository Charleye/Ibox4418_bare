#ifndef __S5P4418_PWM_H__
#define __S5P4418_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <pwm/pwm.h>
#include <s5p4418-rstcon.h>
#include <s5p4418-gpio.h>
#include <s5p4418-clk.h>
#include <reg-pwm.h>
#include <pwm/pwm.h>

void s5p4418_pwm_init(void);
void s5p4418_pwm_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_PWM_H__ */
