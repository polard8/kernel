


segment .text

[bits 64]

main:
    mov rax, qword 0x30200000  ;lfb
    mov qword [rax], qword 0xFF00FF
    jmp $
    
    
