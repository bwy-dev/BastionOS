[bits 32]

;constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_32:
	pusha
	mov edx, VIDEO_MEMORY 
.repeat:
	mov al, [ebx]					;load sing byte of data from the source register to al register
	mov ah, WHITE_ON_BLACK 		
	cmp al,0					;check to see if byte loaded is 0 (the end of the null terminated string)
	je .done	 				;if it is equal, jump to done
	mov [edx], ax
	add ebx, 1
	add edx, 2
	jmp .repeat  				;loop 
.done:
	popa
	ret
