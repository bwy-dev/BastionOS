#include "../kernel/ports.h"
#include "../drivers/serial.h"

unsigned short com;
unsigned short div;

void s_set_port(unsigned short port)
{
	if(port == 1){com = COM1;}
	else if (port ==2){com = COM2;}
	else if (port ==3){com = COM3;}
	else if (port ==4){com = COM4;}
}

/* 
*	sets the speed (baud rate) of the serial transmission
*  the base rate of transfer via serial is 115200 bits/s
*  the "divisor" argument sets the speed as a division of that rate
*  the "com" argument specifies which port to configure
*/
void sconfig_baud_rate(unsigned short divisor)
{
	div = divisor;
	port_byte_out(LINE_COMMAND_PORT(com), LINE_ENABLE_DLAB);
	port_byte_out(DATA_PORT(com), (divisor >>8) & 0x00ff);
	port_byte_out(DATA_PORT(com), divisor & 0x00ff);
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
int sconfig_line(unsigned char value)
{
	if(value == 0){value = 0x03;}
	port_byte_out(LINE_COMMAND_PORT(com), value);
	return port_byte_in(LINE_COMMAND_PORT(com)) & value;
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
int sconfig_buffer(unsigned char value)
{
	if(value == 0){value = 0xe7;}
	port_byte_out(BUFFER_PORT(com), value);
	return 1;
}

int sconfig_modem(unsigned char value)
{
	if(value == 0){value = 0x03;}
	port_byte_out(MODEM_COMMAND_PORT(com), value);
	return port_byte_in(MODEM_COMMAND_PORT(com)) & value;
}

/*
*	returns 0 if transmit FIFO is NOT empty.
*  returns 1 if transmit FIFO IS empty. 
*/
int s_is_transmit_empty()
{
	return port_byte_in(LINE_STATUS_PORT(com))& 0x20;
}

void s_write(unsigned char c)
{
	if(s_is_transmit_empty() != 0)
	{
		port_byte_out(DATA_PORT(com), c);
	}
	else
	{
		s_write(c);
	}
}

void s_print(unsigned char *msgtype, unsigned char *msg)
{
	int i;
	
	for(i = 0; msgtype[i] != 0; i++) 
   {
   	s_write(msgtype[i]);     	
   }

   i=0;

	for(i = 0; msg[i] != 0; i++) 
   {
   	s_write(msg[i]);     	
   }
   s_write('\n');
}

int s_await_buffer_empty()
{
	int i;
	int j=0;
	while ((i =s_is_transmit_empty()) == 0)
	{
	s_await_buffer_empty();
	j++;
	if(j>1){return 0;}
	}
	return 1;
}
