#include "../kernel/ports.h"
  
unsigned char port_inb(unsigned short port)
{
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void port_outb(unsigned short port, unsigned char data)
{
	__asm__("out %%al, %%dx" : : "a" (data) , "d" (port));
}

unsigned short port_inw(unsigned short port)
{
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void port_outw(unsigned short port, unsigned short data)
{
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

void port_outl(unsigned short port, unsigned long data)
{
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

unsigned long port_inl(unsigned short port)
{
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}