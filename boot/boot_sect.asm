[org 0x7c00] 

	KERNEL_OFFSET equ 0x1000
	mov [BOOT_DRIVE], dl

	mov bp, 0x9000
	mov sp, bp

	mov si, MSG_REAL_MODE
	call print_string
	call load_kernel
	call clear_screen
	call switch_to_pm

	jmp $

%include "print_string.asm"
%include "disk_load.asm"
%include "gdt.asm"
%include "print_string_32.asm"
%include "switch_to_pm.asm"
%include "clear_screen.asm"

[bits 16]

load_kernel:
	mov si, MSG_LOAD_KERNEL
	call print_string 

	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	call disk_load
	ret

[bits 32]
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_32
	call KERNEL_OFFSET
	jmp $ 


;Global variables
BOOT_DRIVE: db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode...",0
MSG_PROT_MODE db "Successfully entered 32-bit Protected Mode",0
MSG_LOAD_KERNEL db "Loading Kernel into memory...",0

times 510-($-$$) db 0
dw 0xaa55
