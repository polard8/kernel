;sw_something: 
;    ret


extern _xxxxINT128_DEBUG_MESSAGE
extern _sci0

global _int128
_int128:

    ;; Acumulator.
    ;push rax
   
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs
    push rsp
    pushfq


    ;;---------------
    push qword rdx    ; arg4
    push qword rcx    ; arg3 
    push qword rbx    ; arg2 
    push qword rax    ; arg1 {Service number}.

    ;call _xxxxINT128_DEBUG_MESSAGE
    call _sci0
    
    pop rax
    pop rbx
    pop rcx
    pop rdx 
    ;;---------------


    popfq
    pop rsp
    pop gs
    pop fs
    ;pop es
    ;pop ds

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ;; The acumulator.
    ;pop rax


    iretq

.int128Ret: dq 0
;--  


;; ==============================================
;; unhandled interrupts
;; We use EOI only for IRQs.
;;

;; called by setup_idt in headlib.asm

unhandled_int:
    ;jmp $
    ;cli
    ;nothing
    ;sti
    iretq
