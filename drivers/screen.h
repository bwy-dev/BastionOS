#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

// Screen I/O ports
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void move_cur(int col, int row);
int get_cur();
void set_cur(int offset);
void print_char(volatile unsigned char c, int col, int row, char att);
void print(volatile unsigned char *msg);
int get_screen_offset(int col, int row);

#endif