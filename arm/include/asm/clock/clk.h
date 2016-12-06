#ifndef __CLK_H__
#define __CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/malloc.h>
#include <linux/stdlib.h>
#include <io.h>
#include <linux/list.h>
#include <clock/clk-fixed.h>
#include <clock/clk-fixed-factor.h>
#include <clock/clk-gate.h>
#include <clock/clk-divider.h>
#include <clock/clk-mux.h>
#include <clock/clk-pll.h>
#include <clock/clk-link.h>

enum clk_type_t {
	CLK_TYPE_FIXED,
	CLK_TYPE_FIXED_FACTOR,
	CLK_TYPE_PLL,
	CLK_TYPE_MUX,
	CLK_TYPE_DIVIDER,
	CLK_TYPE_GATE,
	CLK_TYPE_LINK,
};

struct clk_t
{
	const char * name;
	enum clk_type_t type;
	int count;

	void (*set_parent)(struct clk_t * clk, const char * pname);
	const char * (*get_parent)(struct clk_t * clk);
	void (*set_enable)(struct clk_t * clk, bool_t enable);
	bool_t (*get_enable)(struct clk_t * clk);
	void (*set_rate)(struct clk_t * clk, u64_t prate, u64_t rate);
	u64_t (*get_rate)(struct clk_t * clk, u64_t prate);

	void * priv;
};

struct clk_t * clk_search(const char * name);
bool_t clk_register(struct clk_t * clk);
bool_t clk_unregister(struct clk_t * clk);

void clk_set_parent(const char * name, const char * pname);
const char * clk_get_parent(const char * name);
void clk_enable(const char * name);
void clk_disable(const char * name);
bool_t clk_status(const char * name);
void clk_set_rate(const char * name, u64_t rate);
u64_t clk_get_rate(const char * name);

#ifdef __cplusplus
}
#endif

#endif /* __CLK_H__ */

