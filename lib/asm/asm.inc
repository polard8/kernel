


;; IN: a, b, c ,d 
;;OUT a = return value.
asm_system_call:

    push ebx
	push ecx
	push edx
	
    int 200
	
	pop edx
	pop ecx 
	pop ebx
	
	ret
	
	
;;===================================
;; putchar	
;; IN: eax = char e, 'al'	
;;
putchar:
    
	mov byte [.saveChar], al

	xor edx, edx	
	xor ecx, ecx 
	xor ebx, ebx	
	xor eax, eax   

	mov dl, byte [.saveChar]
	mov cl, byte [.saveChar]
	mov bl, byte [.saveChar] 
	mov al, 65     ;número do serviço
	
    int 200

	xor edx, edx	
	xor ecx, ecx 
	xor ebx, ebx	
	xor eax, eax   
	
    ret	
	
.saveChar:
    db 0
	
	
	
;;=====================================
;; DisplayMessage
;; IN: esi =  ponteiro para string	
;;

DisplayMessage:
    lodsb                                    ; Load next character.
    or  al, al                               ; Test for NUL character.
    jz  .DONE
    
	;al = char que queremos exibir.
	mov ah, 0
	xor ebx, ebx 
	call putchar 
	
	;mov  ah, 0x0E                            ; BIOS teletype.                           
    ;mov  bx, 0x0007                          ; Página e atributo.  
	;int  0x10                                ; Invoke BIOS.
    
	jmp  DisplayMessage
.DONE:
    ret
	
	
	
	

    

	
	
