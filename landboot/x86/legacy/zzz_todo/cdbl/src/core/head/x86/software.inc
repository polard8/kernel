;
; File: software.inc
;
; Descrição:
;     Rotinas de software para o boot loader.
;     Interrupções de software.
;
; Obs:
;     *As primeiras são em ordem numérica.
;     *As outras são genéricas ou especiais.
;     *As interrupções de software começam na 48 e vão até 255.
;
; Versão 1.0, 2015~2016.
;


;
; Funções importadas.
;

extern _system_services    ;System services oferecidos pelo boot loader.
;extern _change_procedure   ;Muda o procedimento.
;...



;----------------------------------------
; unhandled_int:
;     Interrupção de software genérica.
;
unhandled_int:
    ;cli
	pusha 
    mov al, 0x20
    out 0x20, al
    popa
    iretd
	
;---------------------------------------------
; unhandled_int:
;     Outra interrupção de software genérica.
;     Coloca um char na tela.
;
ignore_int:
	push ds
	push eax
	mov ax, word 0x10
	mov ds, ax
	mov eax, dword 67    ;print 'C'.
	call write_char
	pop eax
	pop ds
	iret
 

global _int48
_int48:		
    mov al, 0x20
    out 0x20, al 
	iretd
	
global _int49
_int49:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int50
_int50:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int51
_int51:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int52
_int52:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int53
_int53:		
    mov al, 0x20
    out 0x20, al 
	iretd	
	
global _int54
_int54:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int55
_int55:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int56
_int56:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int57
_int57:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int58
_int58:		
    mov al, 0x20
    out 0x20, al 
	iretd

global _int59
_int59:		
    mov al, 0x20
    out 0x20, al 
	iretd
	
;Continua ...	
	

;--------------------------
; _int100:    ??
; 	
global _int100
_int100:
    mov al, 0x20
    out 0x20, al 
    iretd
	
  
;--------------------------------
; _int200:
;     INTERRUPÇÃO DE SISTEMA.
;  
global _int200
_int200:
    
	;cli    
	;Confere o número do serviço.
	
	;sem numero do serviço
	cmp dword [0x00900000], dword 0 
    je .exit_serv

	;numero alem do limite.
	cmp dword [0x00900000], dword 2048 
    jg .exit_serv
	
	;chama a rotina de atendimento aos serviços.
	;se a interrupção foi chamada com um numero de serviço
	;válido.
	call _system_services
    ;Nothing.
.exit_serv:	
    mov al, 0x20
    out 0x20, al
    ;sti	
    iretd
  
  
;--------------------------------
; _int201:
;     Mudar procedimento
;    @todo: Não usar change procedure assim... 
;           usar na interruçãode sistema.
;
global _int201 
_int201:
	;call _change_procedure 
    mov al, 0x20
    out 0x20, al 
	iretd
	

;-----------------------------------
; _int213:
;     Executa nova tarefa.
;     @todo: Boot Loader não tem tarefas.
; 
global _int213  
_int213:
	;cli
	mov al, 20h
    out 20h, al   
	sti	
    iretd


;----------------------------------------
; system_interrupt:
;     Outra interrupção de sistema.
;
system_interrupt:
    ;...
	iretd
  
;
; fim.
;

