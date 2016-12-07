/*
 * driver/interrupt/interrupt.c
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

#include <interrupt.h>

struct irq_list_t
{
	struct irq_t * irq;
	struct list_head entry;
};

struct irq_list_t __irq_list = {
	.entry = {
		.next	= &(__irq_list.entry),
		.prev	= &(__irq_list.entry),
	},
};

static void null_interrupt_function(void * data)
{
}

static struct irq_t * irq_search(const char * name)
{
	struct irq_list_t * pos, * n;

	if(!name)
		return NULL;

	list_for_each_entry_safe(pos, n, &(__irq_list.entry), entry)
	{
		if(strcmp(pos->irq->name, name) == 0)
			return pos->irq;
	}

	return NULL;
}

bool_t irq_register(struct irq_t * irq)
{
	struct irq_list_t * il;

	if(!irq || !irq->name)
		return FALSE;

	if(irq_search(irq->name))
		return FALSE;

	il = malloc(sizeof(struct irq_list_t));
	if(!il)
		return FALSE;

	irq->handler->func = null_interrupt_function;
	irq->handler->data = NULL;
	if(irq->set_type)
		irq->set_type(irq, IRQ_TYPE_NONE);
	if(irq->disable)
		irq->disable(irq);
	il->irq = irq;
	list_add_tail(&il->entry, &(__irq_list.entry));

	return TRUE;
}

bool_t irq_unregister(struct irq_t * irq)
{
	struct irq_list_t * pos, * n;

	if(!irq || !irq->name)
		return FALSE;

	list_for_each_entry_safe(pos, n, &(__irq_list.entry), entry)
	{
		if(pos->irq == irq)
		{
			irq->handler->func = null_interrupt_function;
			irq->handler->data = NULL;
			if(pos->irq->set_type)
				pos->irq->set_type(irq, IRQ_TYPE_NONE);
			if(pos->irq->disable)
				pos->irq->disable(pos->irq);

			list_del(&(pos->entry));
			free(pos);
			return TRUE;
		}
	}

	return FALSE;
}

bool_t request_irq(const char * name, void (*func)(void *), enum irq_type_t type, void * data)
{
	struct irq_t * irq;

	if(!name || !func)
		return FALSE;

	irq = irq_search(name);
	if(!irq)
		return FALSE;

	if(irq->handler->func != null_interrupt_function)
		return FALSE;

	irq->handler->func = func;
	irq->handler->data = data;
	if(irq->set_type)
		irq->set_type(irq, type);
	if(irq->enable)
		irq->enable(irq);

	return TRUE;
}

bool_t free_irq(const char * name)
{
	struct irq_t * irq;

	if(!name)
		return FALSE;

	irq = irq_search(name);
	if(!irq)
		return FALSE;

	if(irq->handler->func == null_interrupt_function)
		return FALSE;

	irq->handler->func = null_interrupt_function;
	irq->handler->data = NULL;
	if(irq->set_type)
		irq->set_type(irq, IRQ_TYPE_NONE);
	if(irq->disable)
		irq->disable(irq);

	return TRUE;
}

void enable_irq(const char * name)
{
	struct irq_t * irq = irq_search(name);

	if(irq && irq->enable)
		irq->enable(irq);
}

void disable_irq(const char * name)
{
	struct irq_t * irq = irq_search(name);

	if(irq && irq->disable)
		irq->disable(irq);
}
