;
; Gramado Idle - This is a 32bit, user mode, system application.
; It's the idle process to run when the system is with few activity.
; (c) Copyright 2015-2017 Fred Nora.
;
; File: head.s  
;
; Descrição:
;     É o entry point do programa IDLE.BIN na plataforma x86. 
;     Faz a vez do crt0.s por enquanto.
;
;
; Alguns parâmetros: (@todo: rever)
; ================== 
;  4MB à partir de 400000.
;  físico = virtual      
;  400000 = 400000
;
;  + O kernel carrega o programa em 0x00400000 com o entry point em 0x0041000.
;  + Quem configurou a paginação foi o Boot Loader, mas o kernel refez.
;
;   Stack: (rever)
;   ss  = 0x23
;   esp = 0x00709fff0  ???
;
; Histórico:
;     2015 - Created by fred Nora.
;     2016 - Revision.
;

;;
;; codename db 'cali'
;;


;
; Função importadas.
;





segment .head_x86


 
[bits 32]


 


	;
	; Atuando como driver:
	; ====================
	; Para o Kernel utilizar esse processo como driver, ele precisa linkar 
	; esse processo ao processo Kernel. Vamos fazer isso de forma simples 
	; agora como um teste, depois melhoraremos a maneira de fazer. 
	; O que faremos aqui é atender a solicitação do Kernel de inicializar o 
	; driver. Logo após inicializarmos o driver, enviaremos uma mensagem para 
	; o Kernel na forma de system call, então o Kernel linkará ao sistema o 
	; driver inicializado.
	;

	;
	; Testar se devemos ou não inicializar o driver:
	; ==============================================
	; O Kernel envia uma flag no registrado edx, se a flag for encontrada,
	; significa que devemos inicializar o driver, caso contrário, não.
	;
	; Status do teste: Ok, funcionou. Podemos usar outros argumentos para 
	; efetuarmos outras operações no driver. Como uninitilization.
	;

	
;;============================================
;; _idle_entry_point:
;;     Entry point
;;
;; Argumentos recebidos:
;; ====================
;;     + Temos quatro argumentos na pilha e
;;     + edx comtém uma flag.
;;     + EAX={Número do serviço solicitado.}
;;

extern _testtest_main

global _idle_entry_point              
_idle_entry_point:
    nop
.checkFlag:	
	
	
	call _testtest_main
	
	;;
	;;    * IDLE LOOP
	;;
	
IdleLoop:
    NOP
    JMP IdleLoop 
 
	
 
;
;End.
;
