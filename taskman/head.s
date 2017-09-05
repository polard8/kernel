;
; Gramado Task Manager - This is a 32bit, user mode, system application. 
; It's a task manager to manage the system while we are in user mode.
; (c) Copyright 2015-2016 Fred Nora.
;
; File: head.s 
;
; Descrição:
;     Parte principal Task Manager, TASKMAN.BIN. 
;     É o entry point do programa.
;     Faz a vez do crt0.o por enquanto.
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
;; codename db 'oslo'
;;

segment .head_x86

 
[bits 32]
 
;
; Funções importadas.
;

extern _appMain
;extern _exit


;
; _taskmanager_entry_point:
;     Entry point
;
global _taskmanager_entry_point              
_taskmanager_entry_point:

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
	
  ;  mov byte [0x800000], byte "t"	
  ;  mov byte [0x800001], byte 0x0f	
  ;  mov byte [0x800002], byte "m"	
  ;  mov byte [0x800003], byte 0x0f	
  ;  mov byte [0x800004], byte "n"	
  ;  mov byte [0x800005], byte 0x0f	
  ;  mov byte [0x800006], byte "g"	
  ;  mov byte [0x800007], byte 0x0f	
  ;  mov byte [0x800008], byte "r"	
  ;  mov byte [0x800009], byte 0x0f	
	
	
	call _appMain
	
	cmp eax, dword 0
	je .retOk

    mov byte [0x800000], byte "r"	
    mov byte [0x800001], byte 0x09		
	jmp $

.retOk:	
	;
	; tornar zombie
	;
    ;pushd eax
	;call _exit
	mov byte [0x800000], byte "z"	
    mov byte [0x800001], byte 0x09	
    jmp $

;
; End.
;
