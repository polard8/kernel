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
;; codename db 'los angeles'
;;


segment .head_x86

 
[bits 32]

 
extern _crt0
;extern _GramadoMain
;extern _exit


;;=====================================================
;; _shell_entry_point: 
;;     Entry point for the application.
;;
;;
;; IN:
;;     eax =  índice (Número de serviço)
;;     ebx =  arg1
;;     ecx =  arg2
;;     edx =  arg3
;;
global _shell_entry_point              
_shell_entry_point:
    nop
	
	;; enviando argumentos
	;;push 0
	;;push 0
	;;push 0
	;;push 0
	
	
	;;
	;; ## RECEBER E EMPILHAR OS ARGUMENTOS ##
	;;	

	;push eax                       ; indice
    ;MOV DWORD [_VECTOR._ebx], EBX  ;;arg1
    ;MOV DWORD [_VECTOR._ecx], ECX  ;;arg2
    ;MOV DWORD [_VECTOR._edx], EDX  ;;arg3
	;; talvez possamos receber mais argumentos 
	;; via registradores como RDI e RSI.
	;;...
	;push DWORD _VECTOR    ; INÍCIO DO VETOR.
	;;#BUGBUG talvez main.c precise de usar exern 
	;;para acessar o ponteiro do vetor.
	
	call _crt0
	
	;; atualizando a pilha
	;;pop 0
	;;pop 0
	;;pop 0
	;;pop 0
	
	;;
	;; Obs: o retorno de main é to tipo (void*)
	;;
	
	cmp eax, dword 0
	je retOk

HANG:   
    NOP
	JMP HANG

retOk:	
	;
	; tornar zombie
	;
    ;call __exit
	;mov byte [0x800000], byte "z"	
    ;mov byte [0x800001], byte 0x09	
	JMP HANG
	
	
;;
;; Vetor enviado para main().
;;
	
global _VECTOR 	
_VECTOR:
._ebx:	
    DD 0
._ecx:	
	DD 0
._edx:	
    DD 0
;
; End.
;
