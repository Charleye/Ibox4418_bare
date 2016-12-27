#include <s5p4418-serial-stdio.h>
#include <s5p4418-gpio.h>
#include <s5p4418-tick-delay.h>
#include <key.h>

/*
 * SW1 -> GPIOA_28
 * SW2 -> GPIOB_31
 */
void key_init(void)
{
    gpio_set_pull(S5P4418_GPIOA(28), GPIO_PULL_UP);
    gpio_direction_input(S5P4418_GPIOA(28));

    gpio_set_pull(S5P4418_GPIOB(31), GPIO_PULL_UP);
    gpio_direction_input(S5P4418_GPIOB(31));
}

static u32_t __get_key_status(void)
{
    u32_t key = 0;

    if(gpio_get_value(S5P4418_GPIOA(28)) == 0)
        key |= KEY_NAME_UP;

    if(gpio_get_value(S5P4418_GPIOB(31)) == 0)
        key |= KEY_NAME_DOWN;

    return key;
}

u32_t get_key_status(u32_t *key)
{
    u32_t a = 0, b = 0, c = 0, d = 0;

    a = __get_key_status();
    b = __get_key_status();
    mdelay(1);
    c = __get_key_status();
    mdelay(1);
    d = __get_key_status();

    if ((a == b) && (a == c) && (a == d))
    {
        *key = a;
        return 1;
    }
    return 0;
}

u32_t get_key_event(u32_t *keyup, u32_t *keydown)
{
    static u32_t key_old = 0x00;
    u32_t key;

    if(!get_key_status(&key))
        return 0;

    if(key != key_old)
    {
        *keyup = key & 0x01;
        *keydown = key & 0x02;
        key_old = key;

        return 1;
    }

    return 0;
}
