;
; File: software.inc 
;
; Descrição:
;     Interrupções de software.
;     * As primeiras são em ordem numérica.
;     * As outras são genéricas ou especiais.
;	  * As interrupções de software começam na 48! vão até 255.
;
; Histórico:
; Versão: 1.0, 2015 - Created.
; Versão: 1.0, 2016 - Revisão.
;


extern _new_task_scheduler ;;@todo: deletar.


;;D
global _int48
_int48:
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd
	
;;C	
global _int49
_int49:		
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd

;;B
global _int50
_int50:		
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd

;;A
global _int51
_int51:		
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd

;;G
global _int52
_int52:		
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd

;;F
global _int53
_int53:		
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd

;;E - Error.	
global _int54
_int54:		
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd

	
;	
; ?? Continua ...	
;	
	
	
;------------------------
; _int100: 
;     Interrupção de sistema (opcional, segunda opção).
; 	
global _int100
_int100:
    cli		
    mov al, 0x20
    out 0x20, al 
	sti
	iretd

	
 
;---------------------------------
; _int200:
;    Interrupção de SISTEMA. (padrão).
;
; eax = ;arg1 (numero)
; ebx = ;arg2 (arg2)
; ecx = ;arg3 (arg3)
; edx = ;arg4 (arg4)
; ...  
;
;++
extern _services
global _int200
_int200:  
	cli 
	pushad 

    ;Argumentos.	
    push dword edx    ;arg4.
    push dword ecx    ;arg3. 
    push dword ebx    ;arg2. 
    push dword eax    ;arg1 = {Número do serviço}.
	
	call _services  ;;handler em executive\sm\sys\services.c.
	mov dword [.int200Ret], eax    
    
	;Argumentos.
	pop eax	
    pop ebx
    pop ecx
    pop edx 
	
	popad	
	
    ;mov al, 0x20
    ;out 0x20, al
	
	mov eax, dword [.int200Ret] 
	sti
	iretd
.int200Ret: dd 0
;--  
  

;Change procedure.
global _int201 
_int201:
	cli
	mov al, 20h
    out 20h, al   
	sti	
    iretd
  
;---------------------
; _int213:
;      Executa nova tarefa.
; 
global _int213  
_int213:
	cli
	mov al, 20h
    out 20h, al   
	sti	
    iretd
	
	
;------------------------------------------------------
; _int216:
;     Chamada rápida e direta para criação de janela.
;     Obs: Isso ainda é um experimento.
; IN:
;	eax    ;; x
;	ebx    ;; y 
;	ecx    ;; width
;	edx    ;; height
;	esi    ;; name 
;	edi    ;; type
;	ebp    ;; (Nothing).  
;
;++
extern _CreateWindow
global _int216
_int216:  
	cli 
	
	;salva.
	pushad 
	
	;
	; Salvando os registradores com parâmetros.
	;
	
	mov dword [.arg5], eax    ;; x
	mov dword [.arg6], ebx    ;; y
	mov dword [.arg7], ecx    ;; width
	mov dword [.arg8], edx    ;; height
	mov dword [.arg4], esi    ;; name
	mov dword [.arg1], edi    ;; type
	;;mov dword [.res], ebp    ;; (nothing)
	
	;;
	;; Colocando na pilha.
	;;
	
	;Argumentos.
	push dword [.arg12]  ; color (unsigned long)
	push dword [.arg11]  ; arg11 reservado 
	push dword [.arg10]  ; onde ?? (unsigned long)
	push dword [.arg9]   ; parent window (struct window_d *)
	
	push dword [.arg8]  ; height  
	push dword [.arg7]  ; width
	push dword [.arg6]  ; y
    push dword [.arg5]  ; x                               	
    
	push dword [.arg4]  ;arg4 = Window Name. (char*)
    push dword [.arg3]  ;arg3 = view. (unsigned long)
    push dword [.arg2]  ;arg2 = Status. (unsigned long) 
    push dword [.arg1]  ;arg1 = Type. (unsigned long)
	
	call _CreateWindow   
	mov dword [.int216Ret], eax    
    
	;Argumentos.
	pop eax
	pop eax	
	pop eax	
	pop eax		

	pop eax
	pop eax	
	pop eax	
	pop eax		

	pop eax
	pop eax	
	pop eax	
	pop eax

	;recupera.
	popad	
	
    mov al, 0x20
    out 0x20, al
	
	mov eax, dword [.int216Ret] 
	sti
	iretd
.int216Ret: dd 0
.arg12: dd 0 ;;color
.arg11: dd 0
.arg10: dd 0
.arg9: dd 0
.arg8: dd 0
.arg7: dd 0
.arg6: dd 0
.arg5: dd 0
.arg4: dd 0
.arg3: dd 0
.arg2: dd 0
.arg1: dd 0 ;;type
.res:  dd 0 ;;reserved.
;--  	
;-----------------------------------------------
; Handler's genéricos para interrupções negligenciadas. 
; 
ignore_int:
system_interrupt:
unhandled_int:
    cli
    mov al, 0x20
    out 0x20, al
    out 0xA0, al 
    sti
	iretd
	
;
; End.
;  
	