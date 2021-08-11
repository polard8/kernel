
; sw.asm
; This file handles syscall for x86_64 processors.
; 0x80, 0x81, 0x82


;;-----
; _int128
; 
;     System Call number 0x80
;
;     + It is never called from kernel mode.
;     + It calls a system service without changing the segment registers.
;
;     It has four parameters:
;     rax - Argument 1
;     rbx - Argument 2
;     rcx - Argument 3
;     rdx - Argument 4
;
;;-----


extern _xxxxINT128_DEBUG_MESSAGE
extern _sci0
; Capture context
global _int128
_int128:

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

    mov rax, qword [.int128Ret] 
    iretq
.int128Ret: dq 0
;--  






;;-----
; _int129
; 
;     System Call number 0x81
;
;     + It is never called from kernel mode.
;     + It chamges the segment registers before calling the system service.
;
;     It has four parameters:
;     rax - Argument 1
;     rbx - Argument 2
;     rcx - Argument 3
;     rdx - Argument 4
;
;;-----

;extern _xxxxINT129_DEBUG_MESSAGE
extern _sci1
; Capture context
global _int129
_int129:

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

    mov rax, qword [.int129Ret] 
    iretq
.int129Ret: dq 0
;--  




;;-----
; _int128
; 
;     System Call number 0x82
;
;     + It is never called from kernel mode.
;     + It chamges the segment registers before calling the system service.
;
;     It has four parameters:
;     rax - Argument 1
;     rbx - Argument 2
;     rcx - Argument 3
;     rdx - Argument 4
;
;;-----

;extern _xxxxINT130_DEBUG_MESSAGE
extern _sci2
; Capture context
global _int130
_int130:

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

    mov rax, qword [.int130Ret] 
    iretq
.int130Ret: dq 0
;--    


global _int199
_int199:

    pop qword [frameRIP]
    pop qword [frameCS]
    pop qword [frameRFLAGS]

    mov qword [frameRFLAGS], 0x0000000000003200
    ;mov qword [frameRFLAGS], 0x0000000000003202

    push qword [frameRFLAGS]
    push qword [frameCS]
    push qword [frameRIP]
    iretq

frameRIP:     dq 0
frameCS:      dq 0
frameRFLAGS:  dq 0







