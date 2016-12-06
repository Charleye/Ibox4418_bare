
#include <common.h>

void system_init(void)
{
    malloc_init();
    s5p4418_clk_init();
    s5p4418_gpiochip_init();
    s5p4418_irq_init();
    s5p4418_pwm_init();
    s5p4418_serial_init();
    s5p4418_tick_init();
    s5p4418_tick_delay_init();
}