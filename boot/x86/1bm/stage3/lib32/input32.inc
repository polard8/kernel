;
; File: input32.inc
;   
; Descriçao:
;     Tratamento de entrada de digita��es.
;
; Obs: 
; Essa funçao eh muito importante para o Shell do Boot Manager e 
; para o gerenciamento de arquivos.
;
; ==============================================================
; Autor:
; BareMetal -- a 64-bit OS written in Assembly for x86-64 systems.
; Copyright (C) 2008-2013 Return Infinity -- see LICENSE.
;
; Input Functions
; ==============================================================
;
; History:
;     2015.
;

align 2
    db 'DEBUG: INPUT '
align 2


;; =================================================================
; os_input:
;     Take string from keyboard entry.
;
;  IN:
;       EDI = Location where string will be stored.
;       ECX = Maximum number of characters to accept.
; OUT:
;       ECX = Length of string that was inputed (NULL not counted).
;             All other registers preserved.
;

os_input:

    push edi
    push edx    ;Counter to keep track of max accepted characters.
    push eax

    mov edx, ecx    ; Max chars to accept.
    xor ecx, ecx    ; Offset from start.


;++
os_input_more:
	
	;Prompt.
	mov al, '_'
	call os_output_char
	call os_dec_cursor
	
	;Get key.
	call os_input_key    ;Pega o char gerado pela irq1.
	jnc os_halt_and_more
	;jnc os_input_halt	 ;No key entered, halt until an interrupt is received.
	
	;Enter.
	cmp al, 0x1C		;If 'Enter' key pressed, finish.
	je os_input_done    
	
	;Backspace.
	cmp al, 0x0E			
	je os_input_backspace
	
	;In ASCII range (32 - 126)?
	cmp al, 32			
	jl os_input_more
	
	;Limite.
	cmp al, 126
	jg os_input_more
	
	;Max.
	cmp ecx, edx	    ;Check if we have reached the max number of chars.
	je os_input_more	;Jump if we have (should beep as well).
	
	;Coloca na string.
	stosb				   ;Store AL at EDI and increment EDI by 1.
	inc ecx				   ;Increment the couter.
	
	call os_output_char    ;Display char.
	
	jmp os_input_more
;--	
	
;Backspace.
os_input_backspace:
	cmp ecx, 0			;Backspace at the beginning? get a new char.
	je os_input_more    
	
	mov al, ' '			   ;0x20 is the character for a space.
	call os_output_char    ;Write over the last typed character with the space.
	
	call os_dec_cursor		;Decrement the cursor again.
	call os_dec_cursor		;Decrement the cursor.
	dec edi				    ;Go back one in the string.
	mov byte [edi], 0x00	;NULL out the char.
	dec ecx				    ;Decrement the counter by one.
	jmp os_input_more
os_input_halt:
os_halt_and_more:	
	hlt				        ;Halt until another keystroke is received.
	jmp os_input_more
os_input_done:	
	mov al, 0x00
	stosb				    ;We NULL terminate the string.


    mov al, ' '
    call os_output_char

    pop eax
    pop edx
    pop edi
    RET
;--------------------



;;=====================================================
; os_input_key:
;     Scans keyboard for input.
;
;  IN:	Nothing
; OUT:	AL = 0 if no key pressed, 
;       otherwise ASCII code, other regs preserved
;	    Carry flag is set if there was a keystoke, 
;       clear if there was not.
;	    All other registers preserved.
;

os_input_key:

    mov al, [key]    ;Pega.

    cmp al, 0
    je os_input_key_no_key

    mov byte [key], 0x00    ;Clear the variable as the keystroke is in AL now.
    stc                     ;Set the carry flag.
    ret

os_input_key_no_key:
    clc                     ;Clear the carry flag.
    ret
;--------------------


;
; End.
;


