
unit3_unhandled_int_release: 
    iretq



; unit 3: 
; int 128 release.
unit3_int128_release:

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

