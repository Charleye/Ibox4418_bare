#ifndef __CLK_LINK_H__
#define __CLK_LINK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include <io.h>
#include <list.h>

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
