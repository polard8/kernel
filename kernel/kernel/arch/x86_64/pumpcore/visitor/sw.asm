
; sw.asm

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

    ;jmp unit3_int128_release
; ---
; int 128 release.
;unit3_int128_release:

    mov qword [.int128Ret], rax 

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
    
    mov rax, qword [.int128Ret] 
    iretq
.int128Ret: dq 0
;--  








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

    ;#test
    xor rax, rax
    mov ax, word 0x10 ;KERNEL_DS 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ;call _xxxxINT129_DEBUG_MESSAGE
    call _sci1

    ;jmp unit3_int129_release
; ---
; int 129 release.
;unit3_int129_release:

    mov qword [.int129Ret], rax 

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
    
    mov rax, qword [.int129Ret] 
    iretq
.int129Ret: dq 0
;--  





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

    ;#test
    xor rax, rax
    mov ax, word 0x10 ;KERNEL_DS 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ;call _xxxxINT130_DEBUG_MESSAGE
    call _sci2

    ;jmp unit3_int130_release
; ---
; unit 3: 
; int 130 release.
;unit3_int130_release:

    mov qword [.int130Ret], rax 

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
    
    mov rax, qword [.int130Ret] 
    iretq
.int130Ret: dq 0
;--    



