#include <system_init.h>

enum led_name {
	LED_NAME_LED1		= 1,
	LED_NAME_LED2		= 2,
};

enum led_status {
	LED_STATUS_OFF		= 0,
	LED_STATUS_ON		= 1,
};

/*
 * LED1 -> S5P4418_GPIOC(7)
 * LED2 -> S5P4418_GPIOC(12)
 */
void led_initial(void)
{
	/* LED1 */
	gpio_set_pull(S5P4418_GPIOC(7), GPIO_PULL_UP);
	gpio_direction_output(S5P4418_GPIOC(7), 1);

	/* LED2 */
	gpio_set_pull(S5P4418_GPIOC(12), GPIO_PULL_UP);
	gpio_direction_output(S5P4418_GPIOC(12), 1);
}

void led_set_status(enum led_name name, enum led_status status)
{
	switch(name)
	{
	case LED_NAME_LED1:
		if(status == LED_STATUS_ON)
			gpio_direction_output(S5P4418_GPIOC(7), 0);
		else if(status == LED_STATUS_OFF)
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

		mdelay(150);
        index = (index + 1) % 2;
	}

	return 0;
}
extern void led_on(void);
int main(int argc, char* argv[])
{
    system_init ();
    tester_led(argc, argv);

    return 0;
}
