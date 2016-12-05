#ifndef __S5P4418_IRQ_H__
#define __S5P4418_IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <cp15.h>
#include <reg-gpio.h>
#include <reg-vic.h>
#include <interrupt.h>

void s5p4418_irq_init(void);
void s5p4418_irq_exit(void);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_IRQ_H__ */
