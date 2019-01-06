#include "../kernel/ports.h"
#include "../drivers/serial.h"

unsigned short com;

void s_set_port(unsigned short port)
{
	if(port == 1){com = SERIAL_COM1_BASE;}
	else if (port ==2){com = SERIAL_COM2_BASE;}
	else if (port ==3){com = SERIAL_COM3_BASE;}
	else if (port ==4){com = SERIAL_COM4_BASE;}
}

/* 
*	sets the speed (baud rate) of the serial transmission
*  the base rate of transfer via serial is 115200 bits/s
*  the "divisor" argument sets the speed as a division of that rate
*  the "com" argument specifies which port to configure
*/
void sconfig_baud_rate(unsigned short divisor)
{
	port_byte_out(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	port_byte_out(SERIAL_DATA_PORT(com), (divisor >>8) & 0x00ff);
	port_byte_out(SERIAL_DATA_PORT(com), divisor & 0x00ff);
}

/*
*	content:|d|b|prt|s|dl|
*	value:  |0|0|000|0|11| (0x03 in hex)
*	meanings:
*		d:   enables(1) or disables(0) DLAB
*		b:   enables(1) or disables(0) break control
*		prt: the umber of parity bits to use
*		s:   the number of stop bits to use (value of 0 = 1 bit or 1 = 1.5-2 bits)
*		dl:  describes the length of the data
*	results:
*		data is set to length of 8 bits, with no parity bits, 1 stop bit and 
*		with break control disabled.
*/
void sconfig_line(unsigned char value)
{
	if(value == 0){value = 0x03;}
	port_byte_out(SERIAL_LINE_COMMAND_PORT(com), value);
}

/*
*  content:|lvl|bs|r|dma|clt|clr|e|
*  value:  |11 |0 |0|0  |1  |1  |1|
*  meanings:
*		lvl: How many bytes to store
*		bs:  If the buffers should be 16 on 64 bytes large
*		r:   Reserved for future use
*		dma: How the serial port data should be accessed
*		clt: Clear the transmission FIFO buffer
*		clr: Clear the reciever FIFO buffer
*		e:	  Enables the FIFO buffer
*/
void sconfig_buffer(unsigned char value)
{
	if(value == 0){value = 0xc7;}
	port_byte_out(SERIAL_FIFO_COMMAND_PORT(com), value);
}

void sconfig_modem(unsigned char value)
{
	if(value == 0){value = 0x03;}
	port_byte_out(SERIAL_MODEM_COMMAND_PORT(com), value);
}

unsigned short s_fifo_empty()
{
	return port_byte_in(SERIAL_LINE_STATUS_PORT(com)& 0x20);
}

void s_write(volatile unsigned char c)
{
	while(s_fifo_empty() != 0)
	{
	port_byte_out(SERIAL_DATA_PORT(com), c);
	}
}

void s_print(volatile unsigned char *msg)
{
	for(int i = 0; msg[i] != 0; i++) 
   {
     	s_write(msg[i]);
   }
}

