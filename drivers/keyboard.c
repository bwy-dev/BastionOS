#include "../drivers/keyboard.h"
#include "../kernel/ports.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/mem.h"

static void keyboard_callback(registers_t regs)
{
	unsigned char scancode = port_byte_in(KEYBOARD_PORT);
	char buffer[8];
	print_letter(scancode);
}

void keyboard_init(){register_interrupt_handler(IRQ1,keyboard_callback);}

void print_letter(unsigned char scancode) {
    switch (scancode) {
        case 0x0:
            print("ERROR", WHITE_ON_BLACK,0);
            break;
        case 0x1:
            print("ESC", WHITE_ON_BLACK,0);
            break;
        case 0x2:
            print("1", WHITE_ON_BLACK,0);
            break;
        case 0x3:
            print("2", WHITE_ON_BLACK,0);
            break;
        case 0x4:
            print("3", WHITE_ON_BLACK,0);
            break;
        case 0x5:
            print("4", WHITE_ON_BLACK,0);
            break;
        case 0x6:
            print("5", WHITE_ON_BLACK,0);
            break;
        case 0x7:
            print("6", WHITE_ON_BLACK,0);
            break;
        case 0x8:
            print("7", WHITE_ON_BLACK,0);
            break;
        case 0x9:
            print("8", WHITE_ON_BLACK,0);
            break;
        case 0x0A:
            print("9", WHITE_ON_BLACK,0);
            break;
        case 0x0B:
            print("0", WHITE_ON_BLACK,0);
            break;
        case 0x0C:
            print("-", WHITE_ON_BLACK,0);
            break;
        case 0x0D:
            print("+", WHITE_ON_BLACK,0);
            break;
        case 0x0E:
            //Backspace
            memset(0,(void*)(VIDEO_ADDRESS + (get_cur()-2)),1);
            set_cur(get_cur()-2);
            break;
        case 0x0F:
            print("   ", WHITE_ON_BLACK,0);
            break;
        case 0x10:
            print("Q", WHITE_ON_BLACK,0);
            break;
        case 0x11:
            print("W", WHITE_ON_BLACK,0);
            break;
        case 0x12:
            print("E", WHITE_ON_BLACK,0);
            break;
        case 0x13:
            print("R", WHITE_ON_BLACK,0);
            break;
        case 0x14:
            print("T", WHITE_ON_BLACK,0);
            break;
        case 0x15:
            print("Y", WHITE_ON_BLACK,0);
            break;
        case 0x16:
            print("U", WHITE_ON_BLACK,0);
            break;
        case 0x17:
            print("I", WHITE_ON_BLACK,0);
            break;
        case 0x18:
            print("O", WHITE_ON_BLACK,0);
            break;
        case 0x19:
            print("P", WHITE_ON_BLACK,0);
            break;
			case 0x1A:
				print("[", WHITE_ON_BLACK,0);
				break;
			case 0x1B:
				print("]", WHITE_ON_BLACK,0);
				break;
			case 0x1C:
				print("\n", WHITE_ON_BLACK,0);
				break;
			case 0x1D:
				print("LCtrl", WHITE_ON_BLACK,0);
				break;
			case 0x1E:
				print("A", WHITE_ON_BLACK,0);
				break;
			case 0x1F:
				print("S", WHITE_ON_BLACK,0);
				break;
        case 0x20:
            print("D", WHITE_ON_BLACK,0);
            break;
        case 0x21:
            print("F", WHITE_ON_BLACK,0);
            break;
        case 0x22:
            print("G", WHITE_ON_BLACK,0);
            break;
        case 0x23:
            print("H", WHITE_ON_BLACK,0);
            break;
        case 0x24:
            print("J", WHITE_ON_BLACK,0);
            break;
        case 0x25:
            print("K", WHITE_ON_BLACK,0);
            break;
        case 0x26:
            print("L", WHITE_ON_BLACK,0);
            break;
        case 0x27:
            print(";", WHITE_ON_BLACK,0);
            break;
        case 0x28:
            print("'", WHITE_ON_BLACK,0);
            break;
        case 0x29:
            print("`", WHITE_ON_BLACK,0);
            break;
			case 0x2A:
				print("LShift", WHITE_ON_BLACK,0);
				break;
			case 0x2B:
				print("\\", WHITE_ON_BLACK,0);
				break;
			case 0x2C:
				print("Z", WHITE_ON_BLACK,0);
				break;
			case 0x2D:
				print("X", WHITE_ON_BLACK,0);
				break;
			case 0x2E:
				print("C", WHITE_ON_BLACK,0);
				break;
			case 0x2F:
				print("V", WHITE_ON_BLACK,0);
				break;
        case 0x30:
            print("B", WHITE_ON_BLACK,0);
            break;
        case 0x31:
            print("N", WHITE_ON_BLACK,0);
            break;
        case 0x32:
            print("M", WHITE_ON_BLACK,0);
            break;
        case 0x33:
            print(",", WHITE_ON_BLACK,0);
            break;
        case 0x34:
            print(".", WHITE_ON_BLACK,0);
            break;
        case 0x35:
            print("/", WHITE_ON_BLACK,0);
            break;
        case 0x36:
            print("Rshift", WHITE_ON_BLACK,0);
            break;
        case 0x37:
            print("Keypad *", WHITE_ON_BLACK,0);
            break;
        case 0x38:
            print("LAlt", WHITE_ON_BLACK,0);
            break;
        case 0x39:
            print(" ", WHITE_ON_BLACK,0);
            break;
    }
}


