#include "../libc/mem.h"

void memcpy(const unsigned char *src, unsigned char *dest, int count)
{
	int i;
	for(i=0; i<count;i++){*(dest+i) = *(src+i);}
}

void memset( unsigned char val, unsigned char *dest, int count)
{
	int i;
	for(i=0;i<count;i++){dest[i] = val;}
}