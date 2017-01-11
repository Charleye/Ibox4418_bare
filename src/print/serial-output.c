#include <system_init.h>

int main (int argc, char *argv[])
{
    system_init();

    serial_printf (0, "CLKMODE = 0x%x\n\r", read32(0xC0010000));
    serial_printf (0, "PLL0 = 0x%x\n\r", read32(0xC0010008));
    serial_printf (0, "PLL1 = 0x%x\n\r", read32(0xC001000C));
    serial_printf (0, "PLL2 = 0x%x\n\r", read32(0xC0010010));
    serial_printf (0, "PLL3 = 0x%x\n\r", read32(0xC0010014));

    serial_printf (0, "DIV0 = 0x%x\n\r", read32(0xC0010020));
    serial_printf (0, "DIV1 = 0x%x\n\r", read32(0xC0010024));
    serial_printf (0, "DIV2 = 0x%x\n\r", read32(0xC0010028));
    serial_printf (0, "DIV3 = 0x%x\n\r", read32(0xC001002C));

    serial_printf (0, "0x%u\n\r", clk_get_rate("GATE-UART0"));
    serial_printf (0, "0x%x\n\r", read32(0xC00A9004));
    serial_printf (0, "0x%d\n\r", clk_get_rate("MUX-UART0"));
    serial_printf (0, "0x%u\n\r", clk_get_rate("DIV-UART0"));

    while (1)
    {
    }
    return 0;
}
