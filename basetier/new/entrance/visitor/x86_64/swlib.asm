
; swlib.asm

;; ==============================================
;; unhandled interrupts
;; We use EOI only for IRQs.
;;

;; called by setup_idt in headlib.asm

unhandled_int:
    ;jmp unit3_unhandled_int_release
;unit3_unhandled_int_release:
    ; nop 
    iretq


;
; Window Manager callback support
;

global _wmData_RDI
_wmData_RDI:  dq 0

global _wmData_RSI
_wmData_RSI:  dq 0

global _wmData_RDX
_wmData_RDX:  dq 0

global _wmData_RCX
_wmData_RCX:  dq 0

global _wmData_Callback0
_wmData_Callback0:  dq 0

global _wmData_Callback1
_wmData_Callback1:  dq 0

global _wmData_Callback2
_wmData_Callback2:  dq 0

global _wmWindowMananer_SendMessage
_wmWindowMananer_SendMessage:
    mov rdi, qword [_wmData_RDI]
    mov rsi, qword [_wmData_RSI]
    mov rdx, qword [_wmData_RDX]
    mov rcx, qword [_wmData_RCX]
    call [_wmData_Callback0]
; Return in rax
    ret


