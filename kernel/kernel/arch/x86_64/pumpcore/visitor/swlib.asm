
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


