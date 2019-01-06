#ifndef KERNEL_H
#define KERNEL_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

// Screen I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void main();
void screen_init();
void clear_screen();
int get_cursor();
void set_cursor(int offset);
void print_at(char* message, int row, int col);
void print_char(char character, int col, int row, char attribute_byte);
void print(char *message);
int get_screen_offset(int col, int row);


unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);

#endif