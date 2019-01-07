#ifndef KEYBOARD_H
#define KEYBOARD_H
#define KEYBOARD_PORT 0x60
void keyboard_init();
void print_letter(unsigned char scancode);
#endif