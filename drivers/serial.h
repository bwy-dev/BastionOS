#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_COM1_BASE 					0x3f8
#define SERIAL_COM2_BASE					0x2f8
#define SERIAL_COM3_BASE					0x3e8
#define SERIAL_COM4_BASE					0x2e8
#define SERIAL_DATA_PORT(base) 			(base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base+2)
#define SERIAL_LINE_COMMAND_PORT(base) (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base)(base+4)
#define SERIAL_LINE_STATUS_PORT(base)	(base+5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

void s_set_port(unsigned short port);
void sconfig_baud_rate(unsigned short divisor);
void sconfig_line(unsigned char value);
void sconfig_buffer(unsigned char value);
void sconfig_modem(unsigned char value);
unsigned short s_fifo_empty();
void s_write(volatile unsigned char c);
void s_print(volatile unsigned char *msg);

#endif