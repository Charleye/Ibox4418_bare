/*
 * serial.c
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

#include <s5p4418-serial.h>

static void s5p4418_serial_init(int ch)
{
	switch(ch)
	{
	case 0:
		clk_enable("GATE-UART0");
		gpio_set_cfg(S5P4418_GPIOD(14), 0x1);
		gpio_set_cfg(S5P4418_GPIOD(18), 0x1);
		gpio_set_direction(S5P4418_GPIOD(14), GPIO_DIRECTION_INPUT);
		gpio_set_direction(S5P4418_GPIOD(18), GPIO_DIRECTION_OUTPUT);
		break;

	case 1:
		clk_enable("GATE-UART1");
		gpio_set_cfg(S5P4418_GPIOD(15), 0x1);
		gpio_set_cfg(S5P4418_GPIOD(19), 0x1);
		gpio_set_direction(S5P4418_GPIOD(15), GPIO_DIRECTION_INPUT);
		gpio_set_direction(S5P4418_GPIOD(19), GPIO_DIRECTION_OUTPUT);
		break;

	case 2:
		clk_enable("GATE-UART2");
		gpio_set_cfg(S5P4418_GPIOD(16), 0x1);
		gpio_set_cfg(S5P4418_GPIOD(20), 0x1);
		gpio_set_direction(S5P4418_GPIOD(16), GPIO_DIRECTION_INPUT);
		gpio_set_direction(S5P4418_GPIOD(20), GPIO_DIRECTION_OUTPUT);
		break;

	case 3:
		clk_enable("GATE-UART3");
		gpio_set_cfg(S5P4418_GPIOD(17), 0x1);
		gpio_set_cfg(S5P4418_GPIOD(21), 0x1);
		gpio_set_direction(S5P4418_GPIOD(17), GPIO_DIRECTION_INPUT);
		gpio_set_direction(S5P4418_GPIOD(21), GPIO_DIRECTION_OUTPUT);
		break;

	default:
		return;
	}

	s5p4418_serial_setup(ch, B115200, DATA_BITS_8, PARITY_NONE, STOP_BITS_1);
}

void s5p4418_serial_initial(void)
{
	s5p4418_serial_init(0);
	s5p4418_serial_init(1);
	s5p4418_serial_init(2);
	s5p4418_serial_init(3);
}

bool_t s5p4418_serial_setup(int ch, enum baud_rate_t baud, enum data_bits_t data, enum parity_bits_t parity, enum stop_bits_t stop)
{
	u32_t base = S5P4418_UART0_BASE;
	u32_t ibaud, divider, fraction;
	u32_t temp, remainder;
	u8_t data_bit_reg, parity_reg, stop_bit_reg;
	u64_t uclk;

	switch(ch)
	{
	case 0:
		base = S5P4418_UART0_BASE;
		break;
	case 1:
		base = S5P4418_UART1_BASE;
		break;
	case 2:
		base = S5P4418_UART2_BASE;
		break;
	case 3:
		base = S5P4418_UART3_BASE;
		break;
	default:
		break;
	}

	switch(baud)
	{
	case B50:
		ibaud = 50;
		break;
	case B75:
		ibaud = 75;
		break;
	case B110:
		ibaud = 110;
		break;
	case B134:
		ibaud = 134;
		break;
	case B200:
		ibaud = 200;
		break;
	case B300:
		ibaud = 300;
		break;
	case B600:
		ibaud = 600;
		break;
	case B1200:
		ibaud = 1200;
		break;
	case B1800:
		ibaud = 1800;
		break;
	case B2400:
		ibaud = 2400;
		break;
	case B4800:
		ibaud = 4800;
		break;
	case B9600:
		ibaud = 9600;
		break;
	case B19200:
		ibaud = 19200;
		break;
	case B38400:
		ibaud = 38400;
		break;
	case B57600:
		ibaud = 57600;
		break;
	case B76800:
		ibaud = 76800;
		break;
	case B115200:
		ibaud = 115200;
		break;
	case B230400:
		ibaud = 230400;
		break;
	case B380400:
		ibaud = 380400;
		break;
	case B460800:
		ibaud = 460800;
		break;
	case B921600:
		ibaud = 921600;
		break;
	default:
		return FALSE;
	}

	switch(data)
	{
	case DATA_BITS_5:
		data_bit_reg = 0x0;
		break;
	case DATA_BITS_6:
		data_bit_reg = 0x1;
		break;
	case DATA_BITS_7:
		data_bit_reg = 0x2;
		break;
	case DATA_BITS_8:
		data_bit_reg = 0x3;
		break;
	default:
		return FALSE;
	}

	switch(parity)
	{
	case PARITY_NONE:
		parity_reg = 0x0;
		break;
	case PARITY_EVEN:
		parity_reg = 0x2;
		break;
	case PARITY_ODD:
		parity_reg = 0x1;
		break;
	default:
		return FALSE;
	}

	switch(stop)
	{
	case STOP_BITS_1:
		stop_bit_reg = 0;		break;
	case STOP_BITS_1_5:
		return -1;
	case STOP_BITS_2:
		stop_bit_reg = 1;		break;
	default:
		return -1;
	}

	switch(ch)
	{
	case 0:
		uclk = clk_get_rate("GATE-UART0");
		break;
	case 1:
		uclk = clk_get_rate("GATE-UART1");
		break;
	case 2:
		uclk = clk_get_rate("GATE-UART2");
		break;
	case 3:
		uclk = clk_get_rate("GATE-UART3");
		break;
	default:
		return FALSE;
	}

	/*
	 * IBRD = UART_CLK / (16 * BAUD_RATE)
	 * FBRD = ROUND((64 * MOD(UART_CLK, (16 * BAUD_RATE))) / (16 * BAUD_RATE))
	 */
	temp = 16 * ibaud;
	divider = (u32_t)(uclk / temp);
	remainder = (u32_t)(uclk % temp);
	temp = (8 * remainder) / ibaud;
	fraction = (temp >> 1) + (temp & 1);

	write32(phys_to_virt(base + UART_IBRD), divider);
	write32(phys_to_virt(base + UART_FBRD), fraction);
	write32(phys_to_virt(base + UART_LCRH), (1 << 4) | (data_bit_reg<<5 | stop_bit_reg<<3 | parity_reg<<1));

	return TRUE;
}

ssize_t s5p4418_serial_read(int ch, u8_t * buf, size_t count)
{
	u32_t base = S5P4418_UART0_BASE;
	ssize_t i;

	switch(ch)
	{
	case 0:
		base = S5P4418_UART0_BASE;
		break;
	case 1:
		base = S5P4418_UART1_BASE;
		break;
	case 2:
		base = S5P4418_UART2_BASE;
		break;
	case 3:
		base = S5P4418_UART3_BASE;
		break;
	default:
		break;
	}

	for(i = 0; i < count; i++)
	{
		if( !(read8(phys_to_virt(base + UART_FR)) & UART_FR_RXFE) )
			buf[i] = read8(phys_to_virt(base + UART_DATA));
		else
			break;
	}

	return i;
}

ssize_t s5p4418_serial_write(int ch, u8_t * buf, size_t count)
{
	u32_t base = S5P4418_UART0_BASE;
	ssize_t i;

	switch(ch)
	{
	case 0:
		base = S5P4418_UART0_BASE;
		break;
	case 1:
		base = S5P4418_UART1_BASE;
		break;
	case 2:
		base = S5P4418_UART2_BASE;
		break;
	case 3:
		base = S5P4418_UART3_BASE;
		break;
	default:
		break;
	}

	for(i = 0; i < count; i++)
	{
		while( (read8(phys_to_virt(base + UART_FR)) & UART_FR_TXFF) );
		write8(phys_to_virt(base + UART_DATA), buf[i]);
	}

	return i;
}

ssize_t s5p4418_serial_write_string(int ch, const char * buf)
{
	return s5p4418_serial_write(ch, (u8_t *)buf, strlen(buf));
}
