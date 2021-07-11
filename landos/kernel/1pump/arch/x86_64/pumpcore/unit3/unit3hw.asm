
extern _task_switch_status


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
    

