#ifndef __S5P4418_GPIO_H__
#define __S5P4418_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <reg-gpio.h>
#include <gpio/gpio.h>

void s5p4418_gpiochip_init(void);
void s5p4418_gpiochip_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_GPIO_H__ */
