;=====================================
; _asm_reboot:
;     Reboot the system via ps2 keyboard.
; Steps:
; Wait for an empty Input Buffer.
; Send the reboot call to the keyboard controller.
;

global _asm_reboot
_asm_reboot:

    xor rax, rax

    in al, 0x64
    test al, 00000010b
    ; Loop
    jne _asm_reboot

    mov al, 0xFE
    out 0x64, al

    ; #bugbug
    ; Com halt, sem loop.
    hlt
    ; fall through
unit4_reboot:
    jmp _asm_reboot
    
    





