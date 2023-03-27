

; bootmanagerDisplayMessage:
;     Display ASCIIZ string at "ds:si" via BIOS.

bootmanagerDisplayMessage:
    lodsb                  ; load next character
    or al, al              ; test for NUL character
    jz .bootmanagerDONE
    mov ah, 0x0E           ; BIOS teletype
    mov bh, 0x00           ; display page 0
    mov bl, 0x07           ; text attribute
    int 0x10               ; invoke BIOS
    jmp bootmanagerDisplayMessage
.bootmanagerDONE:
    ret

