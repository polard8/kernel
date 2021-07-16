
unit3_unhandled_int_release: 
    iretq



; unit 3: 
; int 128 release.
unit3_int128_release:

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


; unit 3: 
; int 129 release.
unit3_int129_release:

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


; unit 3: 
; int 130 release.
unit3_int130_release:

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







