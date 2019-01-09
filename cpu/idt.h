#ifndef IDT_H
#define IDT_H

extern void load_idt();

#define IDT_ENTRIES 256
#define KERNEL_CS 0x08
#define INTERRUPT_GATE 0x8e
#define low_16(address) (unsigned short)((address) & 0xffff)
#define high_16(address) (unsigned short)(((address) >> 16) & 0xffff)

typedef struct
{
	unsigned short low_offset;
	unsigned short selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short high_offset;
}__attribute__((packed)) idt_gate_t;

typedef struct
{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed)) idt_register_t;

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, unsigned long handler);
void set_idt();

#endif