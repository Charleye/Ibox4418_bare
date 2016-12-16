#include <system_init.h>

#define SWRSTENB    (1 << 3)    // Software Reset Enable
#define SWRST       (1 << 12)

void software_reset()
{
    int i, val;
    serial_printf(0, "Ibox4418 Board Reseting ...\r\n");

    for(i = 5; i > 0; i--)
    {
        serial_printf(0, "%d seconds\r\n", i);
        mdelay(1000);   //delay 1s
    }

    val = read32(phys_to_virt(S5P4418_SYS_PWRCONT));
    val &= ~SWRSTENB;   // bit[3] clear zero
    val |= SWRSTENB;
    write32(phys_to_virt(S5P4418_SYS_PWRCONT), val);

    val = read32(phys_to_virt(S5P4418_SYS_PWRMODE));
    val &= ~SWRST;      // bit[12] clear zero
    val |= SWRST;
    write32(phys_to_virt(S5P4418_SYS_PWRMODE), val);
}
int main(int argc, char* argv[])
{
    system_init ();
    software_reset();

    return 0;
}
