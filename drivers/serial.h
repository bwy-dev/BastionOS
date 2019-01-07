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

#define LINE_VAL  	0x03
#define BUFFER_VAL 	0xe7
#define MODEM_VAL 	0x03

#define SINFO "[INFO]: "
#define SINTERRUPT "[INTERRUPT}]: "
#define SERROR "[ERROR]: "
#define SDEBUG "[DEBUG]: "

void s_set_port(unsigned short port);
void sconfig_baud_rate(unsigned short divisor);
int sconfig_line(unsigned char value);
int sconfig_buffer(unsigned char value);
int sconfig_modem(unsigned char value);
int  s_is_transmit_empty();
void s_write(unsigned char c);
void s_print(unsigned char* msgtype, unsigned char *msg);
int s_await_buffer_empty();

#endif