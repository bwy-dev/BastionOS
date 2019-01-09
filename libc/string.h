#ifndef STRING_H
#define STRING_H

char* itoa(int val, char* str, int base);
char* strcat( char* str1, char* str2,int count, ...);
int strlen(char* str);
int strarraylen(char* str[]);
#endif