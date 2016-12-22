#include<s5p4418-gpio.h>
#include <led.h>

void led_set_status(led_name_t name, led_status_t status)
{
    switch(name)
    {
        case LED_NAME_LED1:
            if(status == LED_STATUS_ON)
                gpio_direction_output(S5P4418_GPIOC(7), 0);
            else if (status == LED_STATUS_OFF)
                gpio_direction_output(S5P4418_GPIOC(7), 1);
            break;

        case LED_NAME_LED2:
            if(status == LED_STATUS_ON)
                gpio_direction_output(S5P4418_GPIOC(12), 0);
            else if(status == LED_STATUS_OFF)
                gpio_direction_output(S5P4418_GPIOC(12), 1);
            break;

        default:
            break;
    }
}

void led_init(void)
{
    /* LED 1 */
    gpio_set_pull(S5P4418_GPIOC(7), GPIO_PULL_UP);
    gpio_direction_output(S5P4418_GPIOC(7), 1);

    /* LED 2 */
    gpio_set_pull(S5P4418_GPIOC(12), GPIO_PULL_UP);
    gpio_direction_output(S5P4418_GPIOC(12), 1);
}
