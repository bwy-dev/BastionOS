[bits 32] 
KERNEL_STACK_SIZE equ 4096

mov esp, kernel_stack_end
 
section .bss
	align 4
	kernel_stack:
		resb KERNEL_STACK_SIZE
	kernel_stack_end:

 