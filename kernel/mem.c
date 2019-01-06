#include "../kernel/mem.h"

unsigned char *memcpy(const unsigned char *src, unsigned char *dest, int count)
{
	int i;
	for(i=0; i<count;i++){dest[i] = src[i];}
	return dest;
}

unsigned char *memset( unsigned char val, unsigned char *dest, int count)
{
	int i;
	for(i=0;i<count;i++){dest[i] = val;}
	return dest;
}