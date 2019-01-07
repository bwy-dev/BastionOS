#include "../kernel/string_manip.h"
/*
char* itoa(int val, int base)
{
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
}*/

char* itoa( int value, char* str, int base )
{
    char * rc;
    char * ptr;
    char * low;
    // Check for supported base.
    if ( base < 2 || base > 36 )
    {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if ( value < 0 && base == 10 )
    {
        *ptr++ = '-';
    }
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do
    {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while ( value );
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while ( low < ptr )
    {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}

char* strcat(char* str1, char* str2)
{
	int i =0;
	int j =0;

	while(str1[i] != '\0') {i++;}
	while(str2[j] != '\0') {str1[i] = str2[j]; j++; i++;}
	str1[i] = '\0';

	return str1;
}

int strlen(char* str)
{
    int i;
    for(i=0; str[i] != '\0'; i++){;}
    return i;
}

int strarraylen(char* str[])
{
        int i;
    for(i=0; str[i] != '\0'; i++){;}
    return i;
}