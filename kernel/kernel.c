#include "../drivers/screen.h"
#include "../drivers/serial.h"
#include "../kernel/kernel.h"



void k_main()
{
	clear_screen();

	print("Loading BastionOS...\n", GREEN_ON_BLACK);
	print("Kernel version.0.0.1\n", GREEN_ON_BLACK);

	k_serial_setup();
}

void k_serial_setup()
{
	volatile unsigned char* OK = "OK\n";
	volatile unsigned char* ERROR = "ERROR\n";
	const int MSG_OFFSET = 40;
	int l, b, m;

	print("\nSetting serial port to COM1\n", WHITE_ON_BLACK);
	s_set_port(1); 
	print("Setting baud rate to 115200b/s\n", WHITE_ON_BLACK);
	sconfig_baud_rate(1);

	print("Configuring Line", WHITE_ON_BLACK);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((l = sconfig_line(0x03)) == 0x03)
	{
		print(OK, WHITE_ON_GREEN);
	}
	else
	{
		print(ERROR, WHITE_ON_RED);
	}

	print("Setting up the serial buffer", WHITE_ON_BLACK);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((sconfig_buffer(0)) == 1)
	{
		print(OK, WHITE_ON_GREEN);
	}
	else
	{
		print(ERROR, WHITE_ON_RED);
	}

	print("Configuring the modem", WHITE_ON_BLACK);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((m = sconfig_modem(0x03)) == 0x03)
	{
		print(OK, WHITE_ON_GREEN);
	}
	else
	{
		print(ERROR, WHITE_ON_RED);
	}

	print("Testing serial output...", WHITE_ON_BLACK);
	s_print("BEGIN serial debugger output.");	
	int i = s_await_buffer_empty();
	if(i == 1)
	{
		move_cur(MSG_OFFSET, cur_row(get_cur()));
		print(OK, WHITE_ON_GREEN);
	}
}