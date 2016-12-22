#include <system_init.h>
#include <led.h>
#include <key.h>

void ligten_led (void)
{
    u32_t keyup, keydown;
    u32_t led1 =0, led2 = 0;

    led_set_status(LED_NAME_LED1, LED_STATUS_OFF);
    led_set_status(LED_NAME_LED2, LED_STATUS_OFF);

    while (1)
    {
        if (get_key_event(&keyup, &keydown))
        {
            if (keyup & KEY_NAME_UP)
            {
                led1++;
            }

            if(keydown & KEY_NAME_DOWN)
            {
                led2++;
            }

            if (led1)
            {
                led_set_status(LED_NAME_LED1, LED_STATUS_ON);
                led1 --;
            }
            else led_set_status(LED_NAME_LED1, LED_STATUS_OFF);

            if (led2)
            {
                led_set_status(LED_NAME_LED2, LED_STATUS_ON);
                led2--;
            }
            else led_set_status(LED_NAME_LED2, LED_STATUS_OFF);
        }
    }
}

int main(int argc, char* argv[])
{
    system_init ();
    led_init();
    key_init();


    ligten_led();
    return 0;
}
