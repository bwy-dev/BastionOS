#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../drivers/screen.h"
#include "../kernel/string_manip.h"
#include "../drivers/serial.h"

void isr_install()
{
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
	set_idt();
}




void isr_handler(registers_t r)
{
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
		};
	char b[32];
	unsigned char* int_num = itoa(r.int_no, b, 10);
	print("\nrecieved interrupt: %d ", WHITE_ON_RED, 2, int_num);
	print(exception_messages[r.int_no],WHITE_ON_RED,0);
	s_print("[ERROR]: ",exception_messages[r.int_no]);
}