#include "../drivers/screen.h"
#include "../drivers/serial.h"
#include "../kernel/kernel.h"
#include "../kernel/string_manip.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/paging.h"

void k_main()
{
	clear_screen();

	print("Loading BastionOS...\n", GREEN_ON_BLACK,0);
	print("Kernel version.0.0.1\n", GREEN_ON_BLACK,0);
	k_serial_setup();
	isr_install();
	pagefile_init();
}

void k_serial_setup()
{
	unsigned char *SERROR = "[ERROR]: ";
	unsigned char *SDEBUG = "[DEBUG]: ";
	unsigned char *SINFO  = "[INFO]: ";
	unsigned char *OK = "OK\n";
	unsigned char *ERROR = "ERROR\n";
	const int MSG_OFFSET = 70;
	static char buf[32] = {0};
	int l, b, m;
	unsigned char line_val = 0x03;
	unsigned char buffer_val = 0xe7;
	unsigned char modem_val = 0x03;
	int baud_rate_max = 115200;
	int divisor = 1;
	int baud_rate = baud_rate_max / divisor;
	unsigned char* baud_rate_str = itoa(baud_rate, buf, 10);

	print("\nSetting serial port to COM1 with baud rate of %d ", WHITE_ON_BLACK, 1 , baud_rate_str);
	s_set_port(1); 
	sconfig_baud_rate(divisor);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	print(OK, WHITE_ON_GREEN,0);

	print("Configuring Line", WHITE_ON_BLACK,0);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((l = sconfig_line(line_val)) == line_val)
	{
		print(OK, WHITE_ON_GREEN,0);
	}
	else
	{
		print(ERROR, WHITE_ON_RED,0);
	}

	print("Setting up the serial buffer", WHITE_ON_BLACK,0);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((sconfig_buffer(buffer_val)) == 1)
	{
		print(OK, WHITE_ON_GREEN,0);
	}
	else
	{
		print(ERROR, WHITE_ON_RED,0);
	}

	print("Configuring the serial modem", WHITE_ON_BLACK,0);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((m = sconfig_modem(modem_val)) == modem_val)
	{
		print(OK, WHITE_ON_GREEN,0);
	}
	else
	{
		print(ERROR, WHITE_ON_RED,0);
	}

	print("Testing serial output...", WHITE_ON_BLACK,0);
	s_print(SINFO, "BEGIN serial debugger output.\n");	
	int i = s_await_buffer_empty();
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if(i == 1)
	{
		print(OK, WHITE_ON_GREEN,0);
	}
	else
	{
		print(ERROR, WHITE_ON_RED,0);
	}
}