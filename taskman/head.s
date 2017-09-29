;
; Gramado Task Manager - This is a 32bit, user mode, system application. 
; It's a task manager to manage the system while we are in user mode.
; (c) Copyright 2015-2016 Fred Nora.
;
; File: head.s 
;
; Descrição:
;     Parte principal Task Manager, TASKMAN.BIN. 
;     É o entry point do programa na arquitetura x86.
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
;; codename db 'israel'
;;

segment .head_x86

 
[bits 32]
 
;
; Funções importadas.
;

extern _appMain
;extern _exit


;==================================================
; _taskmanager_entry_point:
;     Entry point
;
; IN: ??
;
;
global _taskmanager_entry_point              
_taskmanager_entry_point:
    NOP	
	call _appMain
	
	cmp eax, dword 0
	je retOk

HANG:	
	NOP
	JMP HANG

retOk:	
	;
	; tornar zombie
	;
    ;pushd eax
	;call _exit
	;mov byte [0x800000], byte "z"	
    ;mov byte [0x800001], byte 0x09	
	JMP HANG

;
; End.
;
