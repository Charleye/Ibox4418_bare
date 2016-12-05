#ifndef __S5P4418_FB_H__
#define __S5P4418_FB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <string.h>
#include <stddef.h>
#include <malloc.h>
#include <io.h>
#include <graphic/surface.h>
#include <s5p4418-tick-delay.h>
#include <s5p4418/reg-gpio.h>
#include <s5p4418/reg-mlc.h>
#include <s5p4418/reg-dpc.h>
#include <s5p4418/reg-dpa.h>
#include <s5p4418-clk.h>
#include <s5p4418-pwm.h>
#include <graphic/surface.h>

void s5p4418_fb_initial(void);
struct surface_t * s5p4418_screen_surface(void);
void s5p4418_screen_swap(void);
void s5p4418_screen_flush(void);
void s5p4418_screen_backlight(int brightness);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_FB_H__ */
