;
; File: x86/sw.inc 
;
; software interrupt handler.
;
; History:
;     2015 - Created by Fred Nora.
;


;;================================================
;;...
;;SW_ExitHelper3:
SW_ExitHelper2:
    sti
SW_ExitHelper1:
    iretd
    

;======================================
; _int128:  0x80
;
;    System interrupt
;
; (eax) = arg1 (Service number)
; (ebx) = arg2 (32bit argument)
; (ecx) = arg3 (32bit argument)
; (edx) = arg4 (32bit argument)
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

    ;; Environment:
    ;; + Interrupçoes desabilitadas.
    ;; + Usamos os segmentos do processo em ring3.


    ;; #bugbug
    ;; Com as interrupçoes desabilitadas, se a systemcall
    ;; realizar alguma operaçao em algum dispositivo, entao
    ;; nao tera como esperar por interrupçoes do dispositivo.

    ;cli 
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
        

    ;;---------------
    push dword edx    ; arg4
    push dword ecx    ; arg3 
    push dword ebx    ; arg2 
    push dword eax    ; arg1 {Service number}.

    ;; #todo
    ;; Podemos usar um arranjo diferente de segmentos dependendo
    ;; do numero da chamada.
    ;; por exemplo, uma chamada feita para pegar dados do kernel
    ;; ou setar dados do kernel.

    ; #test
    ; Podemos tentar usar fs para acessar coisas dentro do kernel.
    ; ok. testado.
    ; xor eax, eax
    ; mov ax, word KERNEL_DS 
    ; mov fs, ax

    ;; ds, es, xx, gs, ss permaneçem em ring3.
    ;; Dessa forma podemos pegar facilmente dados 
    ;; do processo.
    ;; #bugbug: Mas e se quem chamou nao esta em ring 3??

;.TheCall:
    call _sci0
    mov dword [.int128Ret], eax 

;.Restore128:
   
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
    
    ;jmp SW_ExitHelper2  ; sti and iretd
    ;sti
    iretd

.int128Ret: dd 0
;--  


;;=====================================
;; _int129: 0x81
extern _sci1
global _int129
_int129:

    ;; Environment:
    ;; + Interrupçoes permanece habilitadas.
    ;; + Usamos os segmentos do kernel.

    pushad
    push ds
    push es
    push fs
    push gs
    
    ;;---------------
    push dword edx    ; arg4
    push dword ecx    ; arg3 
    push dword ebx    ; arg2 
    push dword eax    ; arg1 {Service number}.

    xor eax, eax
    mov ax, word KERNEL_DS 
    mov ds, ax
    mov es, ax
    ;mov fs, ax
    ;mov gs, ax

    call _sci1

    mov dword [.int129Ret], eax 
    pop eax
    pop ebx
    pop ecx
    pop edx 
    ;;---------------
    
    pop gs
    pop fs
    pop es
    pop ds
    popad
    mov eax, dword [.int129Ret] 
    iretd

.int129Ret: dd 0
;;============================================


;;=====================================
;; _int130: 0x82
extern _sci2
global _int130
_int130:  
    ;; Environment:
    ;; + Interrupçoes permanece habilitadas.
    ;; + Usamos os segmentos do kernel.

    pushad
    push ds
    push es
    push fs
    push gs
    
    ;;---------------
    push dword edx    ; arg4
    push dword ecx    ; arg3 
    push dword ebx    ; arg2 
    push dword eax    ; arg1 {Service number}.

    xor eax, eax
    mov ax, word KERNEL_DS 
    mov ds, ax
    mov es, ax
    ;mov fs, ax
    ;mov gs, ax

    call _sci2

    mov dword [.int130Ret], eax 
    pop eax
    pop ebx
    pop ecx
    pop edx 
    ;;---------------
    
    pop gs
    pop fs
    pop es
    pop ds
    popad
    mov eax, dword [.int130Ret] 
    iretd

.int130Ret: dd 0
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


