disk_load:
	push dx			;push dx register to stack

	mov ah, 0x02	;the bios disk read function
	mov al, dh		;number of sectors to read loaded from dh

	mov ch, 0x00	;select cylinder 0
	mov dh, 0x00	;select head 0
	mov cl, 0x02	;select sector 2

	int 0x13		;bios interrupt to read

	jc disk_error   ;if carry flag set (error), print error

	pop dx			;pop dx register back
	cmp dh, al		;compare number of sectors read with number that were meant to be read
	jne disk_error  ;if there is a difference, wrong data was read, print error
	ret

disk_error:
	mov si, DISK_ERROR_MSG 
	call print_string
	jmp $

;Variables
DISK_ERROR_MSG db "Disk read error!",0