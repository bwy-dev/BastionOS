#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../drivers/screen.h"
#include "../kernel/string_manip.h"
#include "../drivers/serial.h"

isr_t interrupt_handlers[256];
int testing;
/*TODO:
	ADD ACTUAL WAYS TO CONFIRM EVERYTHING HAS BEEN CONFIGURED SUCCESSFULLY AND IS WORKING */
void isr_install()
{
	print("Setting up ISRs...", WHITE_ON_BLACK,0);
	set_idt_gate(0, (unsigned long)isr0);
	set_idt_gate(1, (unsigned long)isr1);
	set_idt_gate(2, (unsigned long)isr2);
	set_idt_gate(3, (unsigned long)isr3);
	set_idt_gate(4, (unsigned long)isr4);
	set_idt_gate(5, (unsigned long)isr5);
	set_idt_gate(6, (unsigned long)isr6);
	set_idt_gate(7, (unsigned long)isr7);
	set_idt_gate(8, (unsigned long)isr8);
	set_idt_gate(9, (unsigned long)isr9);
	set_idt_gate(10, (unsigned long)isr10);
	set_idt_gate(11, (unsigned long)isr11);
	set_idt_gate(12, (unsigned long)isr12);
	set_idt_gate(13, (unsigned long)isr13);
	set_idt_gate(14, (unsigned long)isr14);
	set_idt_gate(15, (unsigned long)isr15);
	set_idt_gate(16, (unsigned long)isr16);
	set_idt_gate(17, (unsigned long)isr17);
	set_idt_gate(18, (unsigned long)isr18);
	set_idt_gate(19, (unsigned long)isr19);
	set_idt_gate(20, (unsigned long)isr20);
	set_idt_gate(21, (unsigned long)isr21);
	set_idt_gate(22, (unsigned long)isr22);
	set_idt_gate(23, (unsigned long)isr23);
	set_idt_gate(24, (unsigned long)isr24);
	set_idt_gate(25, (unsigned long)isr25);
	set_idt_gate(26, (unsigned long)isr26);
	set_idt_gate(27, (unsigned long)isr27);
	set_idt_gate(28, (unsigned long)isr28);
	set_idt_gate(29, (unsigned long)isr29);
	set_idt_gate(30, (unsigned long)isr30);
	set_idt_gate(31, (unsigned long)isr31);
	print(" ISRs configured successfully\n", WHITE_ON_BLACK,0);
	print("Setting up IRQs...",WHITE_ON_BLACK,0);
	port_byte_out(0x20, 0x11);
	port_byte_out(0xa0, 0x11);
	port_byte_out(0x21, 0x20);
	port_byte_out(0xa1, 0x28);
	port_byte_out(0x21, 0x04);
	port_byte_out(0xa1, 0x02);
	port_byte_out(0x21, 0x01);
	port_byte_out(0xa1, 0x01);
	port_byte_out(0x21, 0x0);
	port_byte_out(0xa1, 0x0);

	set_idt_gate(32, (unsigned long)irq0);
	set_idt_gate(33, (unsigned long)irq1);
	set_idt_gate(34, (unsigned long)irq2);
	set_idt_gate(35, (unsigned long)irq3);
	set_idt_gate(36, (unsigned long)irq4);
	set_idt_gate(37, (unsigned long)irq5);
	set_idt_gate(38, (unsigned long)irq6);
	set_idt_gate(39, (unsigned long)irq7);
	set_idt_gate(40, (unsigned long)irq8);
	set_idt_gate(41, (unsigned long)irq9);
	set_idt_gate(42, (unsigned long)irq10);
	set_idt_gate(43, (unsigned long)irq11);
	set_idt_gate(44, (unsigned long)irq12);
	set_idt_gate(45, (unsigned long)irq13);
	set_idt_gate(46, (unsigned long)irq14);
	set_idt_gate(47, (unsigned long)irq15);
	print(" IRQs configured successfully.\n",WHITE_ON_BLACK,0);
	set_idt();
	print("IDT configured, Exceptions and PICs functioning.\n",WHITE_ON_BLACK,0);
	s_print(SINFO, "IDT configured, interrupts enabled.\n");
}



void isr_handler(registers_t r)
{
	char b[8];
	unsigned char* int_num = itoa(r.int_no, b, 10);
	//unsigned char *SINTERRUPT = "[INTERRUPT]: ";
	//unsigned char *SINFO = ;
	unsigned char *exception_messages[] =
		{
	    "Division By Zero",
	    "Debug",
	    "Non Maskable Interrupt",
	    "Breakpoint",
	    "Into Detected Overflow",
	    "Out of Bounds",
	    "Invalid Opcode",
	    "No Coprocessor",

	    "Double Fault",
	    "Coprocessor Segment Overrun",
	    "Bad TSS",
	    "Segment Not Present",
	    "Stack Fault",
	    "General Protection Fault",
	    "Page Fault",
	    "Unknown Interrupt",

	    "Coprocessor Fault",
	    "Alignment Check",
	    "Machine Check",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
	    "Reserved",
		};

		print("\n%drecieved interrupt %d : %d ", WHITE_ON_RED, 
		2, SINTERRUPT, int_num, exception_messages[r.int_no]);
		s_print(SINTERRUPT,exception_messages[r.int_no]);
}

void register_interrupt_handler(unsigned char n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r)
{
	if (r.int_no >=40){port_byte_out(0xa0,0x20);}
	port_byte_out(0x20,0x20);

	if(interrupt_handlers[r.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[r.int_no];
		handler(r);
	}
}