;
; Gramado Shell - This is a 32bit, user mode, system application.
; It's a shell utility to access the system resources using command line
; interface in a graphic mode environment.
; (c) Copyright 2015-2016 Fred Nora.
;
; File: head.s 
;
; Descrição:
;     Entry point do utilitário SHELL.BIN. 
;     Obs: Faz a vez do crt0.s por enquanto.
;
; Alguns parâmetros: (@todo: rever)
; ================== 
;  4MB à partir de 400000.
;  físico = virtual      
;  400000 = 400000
;
;  +O kernel é carrega o programa em 0x00400000 
;   com o entry point em 0x0041000.
;  +Quem configurou a paginação foi o Boot Loader.
;
;   Stack: (rever)
;   ss  = 0x23
;   esp = 0x00709fff0  ???
;
;
; Versão 1.0, 2015, 2016.
;

;;
;; codename db 'bergen'
;;


segment .head_x86

 
[bits 32]

 

extern _app_main
;extern _exit


;
; _idle_entry_point - Entry point
;
global _shell_entry_point              
_shell_entry_point:

	;
	; tentando confirmar a entrada no app
	;


    NOP
    NOP
    NOP
    NOP
    mov ax, word 0x1 
    mov ax, word 0x2 
    mov ax, word 0x3 
    mov ax, word 0x4 
	
    ;mov byte [0x800000], byte "s"	
    ;mov byte [0x800001], byte 0x0f	
    ;mov byte [0x800002], byte "h"	
    ;mov byte [0x800003], byte 0x0f	
    ;mov byte [0x800004], byte "e"	
    ;mov byte [0x800005], byte 0x0f	
    ;mov byte [0x800006], byte "l"	
    ;mov byte [0x800007], byte 0x0f	
    ;mov byte [0x800008], byte "l"	
    ;mov byte [0x800009], byte 0x0f	
	
	call _app_main
	
	cmp eax, dword 0
	je ret_ok

    mov byte [0x800000], byte "r"	
    mov byte [0x800001], byte 0x09		
	jmp $

	
	
ret_ok:	
	;
	; tornar zombie
	;
    ;call __exit
	mov byte [0x800000], byte "z"	
    mov byte [0x800001], byte 0x09	
    jmp $

;
; End.
;
