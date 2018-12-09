



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
    
	%include "asm.inc"
	
afterLibs:
    mov esi, string1
    call DisplayMessage	
    
hang9:
    pause
    ;#todo call exit
	jmp hang9	
    jmp $
	
string1 db "First app in assembly 32bit!", 13, 10, 0



;;======================
segment .data 
testdata: dd 0


;;======================
segment .bss
;;testbss: dd 0