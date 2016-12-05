#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <io.h>
#include <list.h>

struct pwm_t
{
	const char * name;

	bool_t __enable;
	u32_t  __duty;
	u32_t  __period;
	bool_t __polarity;

	void (*config)(struct pwm_t * pwm, u32_t duty, u32_t period, bool_t polarity);
	void (*enable)(struct pwm_t * pwm);
	void (*disable)(struct pwm_t * pwm);

	void * priv;
};

struct pwm_list_t
{
	struct pwm_t * pwm;
	struct list_head entry;
};

extern struct pwm_list_t __pwm_list;

struct pwm_t * search_pwm(const char * name);
bool_t register_pwm(struct pwm_t * pwm);
bool_t unregister_pwm(struct pwm_t * pwm);
void pwm_config(struct pwm_t * pwm, u32_t duty, u32_t period, bool_t polarity);
void pwm_enable(struct pwm_t * pwm);
void pwm_disable(struct pwm_t * pwm);

#ifdef __cplusplus
}
#endif

#endif /* __PWM_H__ */
