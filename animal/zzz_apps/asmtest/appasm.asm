



;[org 0x400000]
[bits 32]


;;alinhamento do entrypoint
;;não precisa o linker faz isso
;;times 0x1000 db 0

;;======================
segment .text

;; entry point
app_main:
    jmp afterLibs
    
	;;lib
	%include "asm.inc"
	
afterLibs:
    
	mov al, 4
	call print_spaces
	
	xor eax, eax
	mov al, 0xf1
    call print_hex 
	
	mov al, 4
	call print_spaces	

	mov eax, 0xDEADBEAF
    call print_hex 
	
	mov al, 4
	call print_spaces
	
    mov esi, string1
    call DisplayMessage	
	
	mov eax, 0
	mov ebx, 0
	call asm_set_cursor

    mov esi, string2
    call DisplayMessage	
	
	mov eax, 10
	mov ebx, 10
	call asm_set_cursor

    mov esi, string3
    call DisplayMessage		
    
	mov eax, 20
	mov ebx, 20
	call asm_set_cursor

    mov esi, string4
    call DisplayMessage		
	
	
hang9:
    pause
    ;#todo call exit
	jmp hang9	
    jmp $
	
string1 db "First app in assembly 32bit!", 13, 10, 0
string2 db "String 2", 13, 10, 0
string3 db "String 3", 13, 10, 0
string4 db "String 4", 13, 10, 0

;;======================
segment .data 
testdata: dd 0


;;======================
segment .bss
;;testbss: dd 0