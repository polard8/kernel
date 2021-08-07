;
; Imports
;

extern _task_switch_status


;;
;; == Context =============================================
;;

; See:
; x64cont.c

extern _contextSS        ; User Mode.
extern _contextRSP       ; User Mode.
extern _contextRFLAGS    ; User Mode.
extern _contextCS        ; User Mode.
extern _contextRIP       ; User Mode.

extern _contextDS
extern _contextES
extern _contextFS  ;?
extern _contextGS  ;?

extern _contextRAX
extern _contextRBX
extern _contextRCX
extern _contextRDX

extern _contextRSI
extern _contextRDI

extern _contextRBP

extern _contextR8
extern _contextR9
extern _contextR10
extern _contextR11
extern _contextR12
extern _contextR13
extern _contextR14
extern _contextR15

; ...


; Irq0 release.
; Timer interrupt.
unit3Irq0Release:

    ; 64bit
    ; This is a 64bit pointer to the pml4 table.

    mov RAX, CR3  
    IODELAY 
    nop
    nop
    nop
    nop
    mov CR3, RAX  

    ;IODELAY 
    ;IODELAY 
    ;IODELAY 
    ;IODELAY 

;
; == Restore context ====================
;

    ; Segments
    xor rax, rax
    mov ax, word [_contextDS]
    mov ds, ax
    mov ax, word [_contextES]
    mov es, ax
    mov ax, word [_contextFS]
    mov fs, ax
    mov ax, word [_contextGS]
    mov gs, ax

    mov rsi, qword [_contextRSI] 
    mov rdi, qword [_contextRDI] 
    
    mov rbp, qword [_contextRBP] 
    
    mov rax, qword [_contextRAX] 
    mov rbx, qword [_contextRBX] 
    mov rcx, qword [_contextRCX] 
    mov rdx, qword [_contextRDX] 


    ;; Stack frame. (all double)
    push qword [_contextSS]      ; ss
    push qword [_contextRSP]     ; rsp
    push qword [_contextRFLAGS]  ; rflags
    push qword [_contextCS]      ; cs
    push qword [_contextRIP]     ; rip

    ; EOI - Only the first PIC.
    mov al, 20h
    out 20h, al  
    IODELAY  

    ;; variável usada pelo dispatcher.
    ;mov dword [_irq0PendingEOI], 0


    ; Acumulator.
    mov rax, qword [_contextRAX]

    ;; #bugbug
    ;; We do NOT need the 'sti'. 
    ;; The flags in the 'eflags' will reenable it.
    
    sti
    iretq
    
    
    
    




;; #delete
hwlib_something: 
    ret


;----------------------------------------------
; _turn_task_switch_on:
;     + Cria um vetor para o timer, IRQ0.
;     + Habilita o funcionamento do mecanismo de taskswitch.
;       Essa função é chamada em microkernel\cpu\start.c
;

global _turn_task_switch_on
_turn_task_switch_on:

    cli 
    mov rax, qword _irq0        ;definitivo
    mov rbx, qword 32
    call _setup_system_interrupt

    ;recarrega a nova idt (talvez seja necessario)
    ;lidt [IDT_register]

    ;status do mecanismo de taskswitch.
    mov qword [_task_switch_status], qword 1    ;UNLOCKED.
    ret



;-------------------------------------------------------------
; _turn_task_switch_off:
;     Desabilita a IRQ0 responsável por fazer o task switch.
;
global _turn_task_switch_off
_turn_task_switch_off:

    cli
    mov rax, qword unhandled_irq
    mov rbx, qword 32
    call _setup_system_interrupt

    ;status do mecanismo de taskswitch.
    mov qword [_task_switch_status], qword 0    ;LOCKED.
    ret




