
extern _xxxxINT128_DEBUG_MESSAGE
extern _sci0
; Capture context
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

    ; Parameters:
    ; RDI, RSI, RDX, RCX, R8, and R9 are used 
    ; for integer and memory address arguments

    mov rdi, rax  ; arg1: service number
    mov rsi, rbx  ; arg2:
    push rdx      ; Saving arg4
    mov rdx, rcx  ; arg3:
    pop rcx       ; arg4: 

    ;call _xxxxINT128_DEBUG_MESSAGE
    call _sci0

    jmp unit3_int128_release
; ---

;extern _xxxxINT129_DEBUG_MESSAGE
extern _sci1
; Capture context
global _int129
_int129:
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

    ; Parameters:
    ; RDI, RSI, RDX, RCX, R8, and R9 are used 
    ; for integer and memory address arguments

    mov rdi, rax  ; arg1: service number
    mov rsi, rbx  ; arg2:
    push rdx      ; Saving arg4
    mov rdx, rcx  ; arg3:
    pop rcx       ; arg4: 

    ;call _xxxxINT129_DEBUG_MESSAGE
    call _sci1

    jmp unit3_int129_release
; ---


;extern _xxxxINT130_DEBUG_MESSAGE
extern _sci2
; Capture context
global _int130
_int130:
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

    ; Parameters:
    ; RDI, RSI, RDX, RCX, R8, and R9 are used 
    ; for integer and memory address arguments

    mov rdi, rax  ; arg1: service number
    mov rsi, rbx  ; arg2:
    push rdx      ; Saving arg4
    mov rdx, rcx  ; arg3:
    pop rcx       ; arg4: 

    ;call _xxxxINT130_DEBUG_MESSAGE
    call _sci2

    jmp unit3_int130_release
; ---



;; ==============================================
;; unhandled interrupts
;; We use EOI only for IRQs.
;;

;; called by setup_idt in headlib.asm

unhandled_int:
    jmp unit3_unhandled_int_release
    
    
    
    
