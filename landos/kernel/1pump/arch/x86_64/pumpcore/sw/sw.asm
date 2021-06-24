sw_something: 
    ret


extern _xxxxINT128_DEBUG_MESSAGE
global _int128
_int128:
    call _xxxxINT128_DEBUG_MESSAGE
    iretq

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
