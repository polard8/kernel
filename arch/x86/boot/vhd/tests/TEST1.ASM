
;;chasm -e 0x400000 <nome do arquivo>
;; ai ele vai gerar <nome do arquivo sem .asm>.bin

start:
	 
 
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	 
	;f 
	mov dl, 102
	mov cl, 102
	mov bl, 102 
	mov al, 65     ;número do serviço
	
    int 0x80	 


	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	
	;r 
	mov dl, 114
	mov cl, 114
	mov bl, 114 
	mov al, 65     ;número do serviço
	
    int 0x80	 


	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	
	;e 
	mov dl, 101
	mov cl, 101
	mov bl, 101 
	mov al, 65     ;número do serviço
	
    int 0x80	 

	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx

	;d 
	mov dl, 100
	mov cl, 100
	mov bl, 100 
	mov al, 65     ;número do serviço
	
    int 0x80	 


	;xor eax, eax
	;xor ebx, ebx
	;xor ecx, ecx
	;xor edx, edx

	;mov al, 112 
	;call display_char 
	
	;xor eax, eax
	;xor ebx, ebx
	;xor ecx, ecx
	;xor edx, edx	
	
	;mov al, 113 
	;call display_char 
	
	
	;xor eax, eax
	;xor ebx, ebx
	;xor ecx, ecx
	;xor edx, edx
	
	mov al, 114 
	call display_char 
	
	mov al, 114 
	call display_char 
	
	mov al, 114 
	call display_char 
	
	mov al, 115
	call display_char2 	
	
	mov esi, string1
    call DisplayMessage

	 
halt:
	jmp halt
	

display_char2:
	
	;push eax
	;push ebx
	;push ecx
	;push edx
	
	;mov [SaveChar], al
	
	;push eax
	
	xor edx, edx
	xor ecx, ecx
	xor ebx, ebx
	;xor eax, eax
	
	
	mov dl, al ;[SaveChar]
	mov cl, al ;[SaveChar]
	mov bl, al ;[SaveChar]
	
	xor eax, eax	
	mov al, 65
	
	int 0x80

	;pop edx 
	;pop ecx
	;pop ebx
	;pop eax
    ret



;;in:al
display_char:
	;push eax
	;push ebx
	;push ecx
	;push edx
	
	;mov [SaveChar], al
	
	xor edx, edx
	xor ecx, ecx
	xor ebx, ebx
	xor eax, eax
	
	mov dl, 114; [SaveChar]
	mov cl, 114; [SaveChar]
	mov bl, 114; [SaveChar]
	mov al, 65
	
	int 0x80

	;pop edx 
	;pop ecx
	;pop ebx
	;pop eax
    ret
	
SaveChar:
	db 0


DisplayMessage:
    lodsb                                    ; Load next character.
    or  al, al                               ; Test for NUL character.
    jz  DisplayMessage.DONE
    
	;mov  ah, 0x0E                            ; BIOS teletype.                           
    ;mov  bx, 0x0007                          ; Página e atributo.  
	;int  0x10                                ; Invoke BIOS.
	
	;mov al, (char) 
	call display_char2 
    
	jmp  DisplayMessage
DisplayMessage.DONE:
    ret
	

string1: db "testing string ...", 0xd, 0x10,0


