/*
 * driver/clk/clk.c
 *
 * Copyright(c) 2007-2015 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <clock/clk.h>

struct clk_list_t
{
	struct clk_t * clk;
	struct list_head entry;
};

static struct clk_list_t __clk_list = {
	.entry = {
		.next	= &(__clk_list.entry),
		.prev	= &(__clk_list.entry),
	},
};

struct clk_t * clk_search(const char * name)
{
	struct clk_list_t * pos, * n;

	if(!name)
		return NULL;

	list_for_each_entry_safe(pos, n, &(__clk_list.entry), entry)
	{
		if(strcmp(pos->clk->name, name) == 0)
			return pos->clk;
	}

	return NULL;
}

bool_t clk_register(struct clk_t * clk)
{
	struct clk_list_t * cl;

	if(!clk || !clk->name)
		return FALSE;

	if(clk_search(clk->name))
		return FALSE;

	cl = malloc(sizeof(struct clk_list_t));
	if(!cl)
		return FALSE;

	cl->clk = clk;
	list_add_tail(&cl->entry, &(__clk_list.entry));

	return TRUE;
}

bool_t clk_unregister(struct clk_t * clk)
{
	struct clk_list_t * pos, * n;

	if(!clk || !clk->name)
		return FALSE;

	list_for_each_entry_safe(pos, n, &(__clk_list.entry), entry)
	{
		if(pos->clk == clk)
		{
			list_del(&(pos->entry));
			free(pos);
			return TRUE;
		}
	}

	return FALSE;
}

void clk_set_parent(const char * name, const char * pname)
{
	struct clk_t * clk = clk_search(name);
	struct clk_t * pclk = clk_search(pname);

	if(pclk && clk && clk->set_parent)
		clk->set_parent(clk, pname);
}

const char * clk_get_parent(const char * name)
{
	struct clk_t * clk = clk_search(name);

	if(clk && clk->get_parent)
		return clk->get_parent(clk);
	return NULL;
}

void clk_enable(const char * name)
{
	struct clk_t * clk = clk_search(name);

	if(!clk)
		return;

	if(clk->get_parent)
		clk_enable(clk->get_parent(clk));

	if(clk->set_enable)
		clk->set_enable(clk, TRUE);

	clk->count++;
}

void clk_disable(const char * name)
{
	struct clk_t * clk = clk_search(name);

	if(!clk)
		return;

	if(clk->count > 0)
		clk->count--;

	if(clk->count == 0)
	{
		if(clk->get_parent)
			clk_disable(clk->get_parent(clk));

		if(clk->set_enable)
			clk->set_enable(clk, FALSE);
	}
}

bool_t clk_status(const char * name)
{
	struct clk_t * clk = clk_search(name);

	if(!clk)
		return FALSE;

	if(!clk->get_parent(clk))
		return clk->get_enable(clk);

	if(clk->get_enable(clk))
		return clk_status(clk->get_parent(clk));

	return FALSE;
}

void clk_set_rate(const char * name, u64_t rate)
{
	struct clk_t * clk = clk_search(name);
	u64_t prate;

	if(!clk)
		return;

	if(clk->get_parent)
		prate = clk_get_rate(clk->get_parent(clk));
	else
		prate = 0;

	if(clk->set_rate)
		clk->set_rate(clk, prate, rate);
}

u64_t clk_get_rate(const char * name)
{
	struct clk_t * clk = clk_search(name);
	u64_t prate;

	if(!clk)
		return 0;

	if(clk->get_parent)
		prate = clk_get_rate(clk->get_parent(clk));
	else
		prate = 0;

	if(clk->get_rate)
		return clk->get_rate(clk, prate);

	return 0;
}
