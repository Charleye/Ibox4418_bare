#ifndef _S5P4418_LED_H_
#define _S5P4418_LED_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LED_NAME_LED1   = 0x01,
    LED_NAME_LED2   = 0x01 << 1
}led_name_t;

typedef enum {
    LED_STATUS_OFF  = 0x00,
    LED_STATUS_ON   = 0x01
}led_status_t;

void led_set_status (led_name_t name, led_status_t status);
void led_init (void);

#ifdef __cplusplus
}
#endif

#endif /* _S5P4418_LED_H_ */
