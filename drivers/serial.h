#ifndef SERIAL_H
#define SERIAL_H

#define COM1		 					0x3f8
#define COM2							0x2f8
#define COM3							0x3e8
#define COM4							0x2e8
#define DATA_PORT(base) 			(base)
#define BUFFER_PORT(base)  (base+2)
#define LINE_COMMAND_PORT(base)  (base+3)
#define MODEM_COMMAND_PORT(base) (base+4)
#define LINE_STATUS_PORT(base)	(base+5)

#define LINE_ENABLE_DLAB 0x80

void s_set_port(unsigned short port);
void sconfig_baud_rate(unsigned short divisor);
int sconfig_line(unsigned char value);
int sconfig_buffer(unsigned char value);
int sconfig_modem(unsigned char value);
int  s_is_transmit_empty();
void s_write(unsigned char c);
void s_print(unsigned char *msg);

#endif