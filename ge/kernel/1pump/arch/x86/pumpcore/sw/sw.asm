;
; File: x86/sw.inc 
;
; software interrupt handler.
;
; History:
;     2015 - Created by Fred Nora.
;



;======================================
; _int128:  0x80
;
;    System interrupt
;
; eax = ;arg1 (numero)
; ebx = ;arg2 (arg2)
; ecx = ;arg3 (arg3)
; edx = ;arg4 (arg4)
; ...  
; 
; #todo: 
; Pelo jeito eh natural entrar com muito mais argumentos, 
; passados pelos registradores ebp, esi, edi.
; See: sci/sci.c
;++

extern _sci0

global _int128
_int128: 

    cli 
    pushad 

    push ds
    push es
    push fs
    push gs


    ;; #bugbug
    ;; We are not changing the segment registers.
    ;; This way the kernel is able to access all the user data.
    ;; Normally it is preserved only the register 'fs' to access
    ;; the user data.
    
    ;; This way, probably we are not able to get the data 
    ;; inside the base kernel. It's because the data will point to another
    ;; place, probably inside the application.
    
    ;; Are we switching the page directory ???
    
    ;; #test
    ;; Kernel data segments
    ;; se fizer isso vai dar problema. 
    ;; e se nao fizer teremos problemas para ler as coisas dentro do kernel.
    ;; #todo:
    ;; Sera preciso um gerenciamento melhor dos registradores de segmento
    ;; para podermos pegar informaçao tanto no kernel quanto no aplicativo.
        
    ;xor eax, eax
    ;mov ax, word 0x10 
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax


    ;;---------------
    push dword edx    ; arg4
    push dword ecx    ; arg3 
    push dword ebx    ; arg2 
    push dword eax    ; arg1 {Service number}.
    
    call _sci0
    
    mov dword [.int128Ret], eax 
    pop eax
    pop ebx
    pop ecx
    pop edx 
    ;;---------------

    pop gs
    pop fs
    pop es
    pop ds

    ;; No EOI!
    
    popad
    mov eax, dword [.int128Ret] 
    sti

    iretd
    
.int128Ret: dd 0
;--  


;;=====================================
;; _int129: 0x81
extern _sci1
global _int129
_int129:  
    ;; Nothing
    iretd
;;============================================


;;=====================================
;; _int130: 0x82
extern _sci2
global _int130
_int130:  
    ;; Nothing
    iretd
;;============================================



;;==========================
;; _int199:
;;
;; Isso � chamado pelo processo INIT.BIN.
;;
;; Uma interrup��o para habilitar as interrup��es mascar�veis.
;; quem usar� isso ser� a thread prim�ria do processo init.
;; apenas uma vez.

global _int199
_int199:

    pop dword [.frameEIP]
    pop dword [.frameCS]
    pop dword [.frameEFLAGS]
   
    mov dword [.frameEFLAGS], 0x3200

    push dword [.frameEFLAGS]
    push dword [.frameCS]
    push dword [.frameEIP]
    iretd

.frameEIP:     dd 0
.frameCS:      dd 0
.frameEFLAGS:  dd 0

;;===================================================



;; ==============================================
;; unhandled interrupts
;; We use EOI only for IRQs.
;;

unhandled_int:
    cli
    ;nothing
    sti
    iretd



;
; End.
;  


