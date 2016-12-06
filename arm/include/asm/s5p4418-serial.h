#ifndef __S5P4418_SERIAL_H__
#define __S5P4418_SERIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/types.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/stddef.h>
#include <io.h>
#include <reg-uart.h>
#include <s5p4418-gpio.h>
#include <s5p4418-clk.h>

enum baud_rate_t {
	B50,
	B75,
	B110,
	B134,
	B200,
	B300,
	B600,
	B1200,
	B1800,
	B2400,
	B4800,
	B9600,
	B19200,
	B38400,
	B57600,
	B76800,
	B115200,
	B230400,
	B380400,
	B460800,
	B921600
};

enum data_bits_t {
	DATA_BITS_5,
	DATA_BITS_6,
	DATA_BITS_7,
	DATA_BITS_8,
};

enum parity_bits_t {
	PARITY_NONE,
	PARITY_EVEN,
	PARITY_ODD,
};

enum stop_bits_t {
	STOP_BITS_1,
	STOP_BITS_1_5,
	STOP_BITS_2,
};

void s5p4418_serial_initial(void);
bool_t s5p4418_serial_setup(int ch, enum baud_rate_t baud, enum data_bits_t data, enum parity_bits_t parity, enum stop_bits_t stop);
ssize_t s5p4418_serial_read(int ch, u8_t * buf, size_t count);
ssize_t s5p4418_serial_write(int ch, u8_t * buf, size_t count);
ssize_t s5p4418_serial_write_string(int ch, const char * buf);

#ifdef __cplusplus
}
#endif

#endif /* __S5P4418_SERIAL_H__ */
