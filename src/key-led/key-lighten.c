#include <system_init.h>
#include <led.h>
#include <key.h>

void ligten_led (void)
{
    u32_t keyup, keydown;

    led_set_status(LED_NAME_LED1, LED_STATUS_OFF);
    led_set_status(LED_NAME_LED2, LED_STATUS_OFF);

    while (1)
    {
        if(get_key_event(&keyup, &keydown))
        {
            if(keyup != 0)
            {
                if (keyup & KEY_NAME_UP)
                    led_set_status(LED_NAME_LED1, LED_STATUS_OFF);
                if (keyup & KEY_NAME_DOWN)
                    led_set_status(LED_NAME_LED2, LED_STATUS_OFF);
            }

            if(keydown != 0)
            {
                if (keydown & KEY_NAME_UP)
                    led_set_status(LED_NAME_LED1, LED_STATUS_ON);
                if (keydown & KEY_NAME_DOWN)
                    led_set_status(LED_NAME_LED2, LED_STATUS_ON);
            }
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
