#include <system_init.h>
#include <led.h>

int tester_led(int argc, char * argv[])
{
	int index = 0;

	while(1)
	{
		led_set_status(LED_NAME_LED1, LED_STATUS_OFF);
		led_set_status(LED_NAME_LED2, LED_STATUS_OFF);

		switch(index)
		{
		case 0:
			led_set_status(LED_NAME_LED1, LED_STATUS_ON);
			break;

		case 1:
			led_set_status(LED_NAME_LED2, LED_STATUS_ON);
			break;

		default:
			break;
		}

		mdelay(300);
        index = (index + 1) % 2;
	}

	return 0;
}

int main(int argc, char* argv[])
{
    system_init ();
    led_init();

    tester_led(argc, argv);

    return 0;
}
