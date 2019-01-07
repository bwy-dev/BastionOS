#include "../cpu/idt.h"
void set_idt_gate(int n, unsigned long handler)
{
	idt[n].low_offset = low_16(handler);
	idt[n].selector = KERNEL_CS;
	idt[n].zero = 0;
	idt[n].flags = INTERRUPT_GATE;
	idt[n].high_offset = high_16(handler);
}

void set_idt()
{
	idt_reg.base = (unsigned int) &idt;
	idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) -1;
	__asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));
}