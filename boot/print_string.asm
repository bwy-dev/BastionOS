print_string:
	mov ah, 0x0e ;initialize teletype BIOS routine
.repeat:
	lodsb 		 ;load sing byte of data from the source register to al register
	cmp al,0	 ;check to see if byte loaded is 0 (the end of the null terminated string)
	je .done	 ;if it is equal, jump to done
	int 0x10	 ;interrupt to print the char in al onto screen
	jmp .repeat  ;loop 
.done:
	ret
