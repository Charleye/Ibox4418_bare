#ifndef __CLK_LINK_H__
#define __CLK_LINK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/malloc.h>
#include <linux/stdlib.h>
#include <linux/list.h>
#include <io.h>

struct clk_link_t {
	const char * name;
	const char * parent;
};

bool_t clk_link_register(struct clk_link_t * lclk);
bool_t clk_link_unregister(struct clk_link_t * lclk);

#ifdef __cplusplus
}
#endif

#endif /* __CLK_LINK_H__ */
