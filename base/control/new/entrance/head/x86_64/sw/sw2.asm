
; sw2.asm

;; ==============================================
;; unhandled interrupts
;; We use EOI only for IRQs.
;; called by setup_idt in headlib.asm

unhandled_int:
; #bugbug: 
; Talvez uma irq esta chamando isso e precisa de eoi.
; #todo: 
; Criar um contador para isso.
    iretq


    
    




