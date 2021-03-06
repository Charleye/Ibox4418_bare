
#include <system_init.h>
void system_init(void)
{
    malloc_init();          /* Create TLSF DMA(Dynamic Memory Allocator */
    s5p4418_clk_init();
    s5p4418_gpiochip_init();
    s5p4418_irq_init();
    s5p4418_serial_initial();
    s5p4418_tick_init();
    s5p4418_tick_delay_init();
}
