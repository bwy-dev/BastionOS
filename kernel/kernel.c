#include "../drivers/screen.h"
#include "../drivers/serial.h"
#include "../kernel/kernel.h"
#include "../libc/string.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/paging.h"
#include "../drivers/keyboard.h"
#include "../drivers/pci.h"

void k_main()
{
	print("\nSuccessfully booted into 32bit protected mode.\n",0x07,0);
	print("\nLoading BastionOS...\n", GREEN_ON_BLACK,0);
	print("Kernel version %d\n", GREEN_ON_BLACK,1,KERNEL_VER);
	k_serial_setup();

	print("Initializing interrupts...\n", WHITE_ON_BLACK,0);
	isr_install();
	print("\nInterrupts successfully initialized\n",WHITE_ON_BLACK,0);
	pagefile_init();
	irq_init();
	pci_check_for_ahci();
}

void k_serial_setup()
{
	unsigned char *OK = "OK\n";
	unsigned char *ERROR = "ERROR\n";
	
	static char buf[32] = {0};
	int l, b, m;

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
	if((l = sconfig_line(LINE_VAL)) == LINE_VAL)
	{
		print(OK, WHITE_ON_GREEN,0);
	}
	else
	{
		print(ERROR, WHITE_ON_RED,0);
	}

	print("Setting up the serial buffer", WHITE_ON_BLACK,0);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((sconfig_buffer(BUFFER_VAL)) == 1)
	{
		print(OK, WHITE_ON_GREEN,0);
	}
	else
	{
		print(ERROR, WHITE_ON_RED,0);
	}

	print("Configuring the serial modem", WHITE_ON_BLACK,0);
	move_cur(MSG_OFFSET, cur_row(get_cur()));
	if((m = sconfig_modem(MODEM_VAL)) == MODEM_VAL)
	{
		print(OK, WHITE_ON_GREEN,0);
	}
	else
	{
		print(ERROR, WHITE_ON_RED,0);
	}

	print("Testing serial output...", WHITE_ON_BLACK,0);
	s_print(SINFO, "BEGIN serial debugger output.\n",0);	
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