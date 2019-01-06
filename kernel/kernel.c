#include "../drivers/screen.h"
#include "../drivers/serial.h"
void k_main()
{
	move_cur(0,0);
	clear_screen();
	move_cur(0,0);

	//volatile unsigned char *str = "";
	print("Loading BastionOS...\n");
	print("Kernel version.0.0.1\n");

	print("\nSetting serial port to COM1\n");
	s_set_port(1); 
	print("Setting baud rate to 57600b/s\n");
	sconfig_baud_rate(1);
	print("Configuring Line\n");
	sconfig_line(0);
	print("Setting up the serial buffer\n");
	sconfig_buffer(0);
	print("Configuring the modem\n");
	sconfig_modem(0);
	print("Testing serial output...\n");
	s_print("Hello World");
}