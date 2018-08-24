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
;; codename db 'miami'
;;


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
global _idle_entry_point              
_idle_entry_point:
    nop
.checkFlag:	
	
	;Inicializa chamando main().
	cmp edx, dword 0
	je do_initMain
	
	;Inicializa o servidor INIT.
	cmp edx, dword 0x00001234
    je do_InitializeDriver    	     ;; Initialize driver.	
	
	;Finaliza o servidor INIT.
	cmp edx, dword 0x00004321
	je do_UninitializeDriver        ;; Uninitialize driver.
	
	;Chama algum serviço do servidor se ele estiver inicializado.
	cmp edx, dword 0x12345678       ;; Magic para usar serviços do servidor.
	je do_services
	
.default:
    nop
	
	;;
	;;    * IDLE LOOP
	;;
	
;;#bugbug
;;Normalmente a thread idle deve ficar em kernelmode
;;para invocar a instrução hlt	
IdleLoop:
    NOP
	PAUSE
    PAUSE
    PAUSE
    PAUSE	
    JMP IdleLoop 
	
	
	
	
;;====================================================================	
;; do_initMain:
;;
;;  ## Sem argumentos.  ##
;;
extern _initMain
do_initMain:
	call _initMain 
    jmp	IdleLoop
	
	
;;====================================================================	
;; InitializeDriver:
;;     Esse processo será inicializado como um driver em user mode.
;; 
extern _driverInitialize  ;Envia um sinal pro kernel inicializar esse driver.  
do_InitializeDriver:
    call _driverInitialize	
    JMP IdleLoop 
	
	
;;====================================================================	
;; UninitializeDriver:
;;     O processo deixa de atuar como um driver em user mode.
;;
extern _driverUninitialize	 	
do_UninitializeDriver:
    call _driverUninitialize
    JMP IdleLoop 
	
	
;;======================================================================
;; services:
;;     Chamaremos algum dos serviços oferecidos, que obviamente só
;; funcionarão se o driver estiver inicializado.
;;
;; IN:
;;     eax = Número do serviço solicitado.
;;     ebx = arg1
;;     ecx = arg2
;;     edx = magic. (Precisa ser 0x12345678)
;;
extern _idleServices
do_services:
    
	;; Magic para usar serviços do servidor.
	cmp edx, dword 0x12345678       
	jne .fail

	;;#EDX
	;Limpa a magic.
	xor edx, edx 
	
	;;#ECX
	;colocar o argumento 2 na pilha
	push ecx

	;;#EBX
	;colocar o argumento 1 na pilha
	push ebx
	
	;;#EAX
	;; Coloca o número do serviço na pilha.
	push eax
	

	;;
	;;  ## Chama o serviço solicitado ##
	;;
	
	
    call _idleServices 
	mov dword [.ret_val], eax
	
	
	;;
	;; Aqui podemos fazer alguma coisa com o valor retornado.
	;;
	
.fail:	
    nop	
.done:	
    JMP IdleLoop     	
	
	
.ret_val: dd 0

;
;End.
;
