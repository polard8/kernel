

;extern _Module0EntryPoint

; dirty: The registers are dirty.
global _asm_initialize_module0
_asm_initialize_module0:

    mov rdi, qword 1000   ; Reason = Initialize module.
    ;call _Module0EntryPoint
    ;call 0x30A00000
    ret

;=====================================
; _asm_reboot:
;     Reboot the system via ps2 keyboard.
; Steps:
; Wait for an empty Input Buffer.
; Send the reboot call to the keyboard controller.
;

PS2KEYBOARD_CMD_REBOOT EQU  0xFE

global _asm_reboot
_asm_reboot:

    xor rax, rax
    in al, 0x64

; #test ? Status ?
    test al, 00000010b
    jne _asm_reboot

; Send command.
    mov al, PS2KEYBOARD_CMD_REBOOT
    out 0x64, al

.Lloop:
    cli
    hlt
    jmp .Lloop

; ---------------------------
; Reboot procedure.  
; Wrapper
unit4_reboot:
    jmp _asm_reboot
    
    





