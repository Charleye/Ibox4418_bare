/*
 * tick.c
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

#include <s5p4418-tick.h>

volatile u32_t jiffies = 0;
static u32_t tick_hz = 0;

#define TICK_TIMER_CHANNEL		(0)

static void timer_interrupt(void * data)
{
	jiffies++;
	s5p4418_timer_irq_clear(TICK_TIMER_CHANNEL);
}

void s5p4418_tick_initial(void)
{
	u64_t rate;

	s5p4418_timer_reset();

	request_irq("TIMER0", timer_interrupt, IRQ_TYPE_NONE, NULL);

	/* 40ns ~ 25MHZ */
	rate = s5p4418_timer_calc_tin(TICK_TIMER_CHANNEL, 40);
	s5p4418_timer_stop(TICK_TIMER_CHANNEL, 1);
	s5p4418_timer_count(TICK_TIMER_CHANNEL, rate / 100);
	s5p4418_timer_start(TICK_TIMER_CHANNEL, 1);

	/* initial system tick */
	tick_hz = 100;
	jiffies = 0;
}

u32_t get_system_hz(void)
{
	return tick_hz;
}

u64_t clock_gettime(void)
{
	if(get_system_hz() > 0)
		return (u64_t)jiffies * 1000000 / get_system_hz();

	return 0;
}
