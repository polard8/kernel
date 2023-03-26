
; 2000h:0
; just like mikeos.
; We're gonna include a lot of files from the loader.
; Credits:
; Porting some stuff from mikeos. (BSD LICENSE)

bits 16

	%DEFINE MIKEOS_VER '4.7.0'	; OS version number
	%DEFINE MIKEOS_API_VER 18	; API version for programs to check


g16kern_main:

; Save boot device number
    mov [bootdev], dl

	cli				; Clear interrupts
	mov ax, 0
	mov ss, ax			; Set stack segment and pointer
	mov sp, 0FFFFh
	sti				; Restore interrupts

	cld				; The default direction for string operations
					; will be 'up' - incrementing address in RAM

; 2000H
	mov ax, 2000h		; Set all segments to match where kernel is loaded
	mov ds, ax			; After this, we don't need to bother with
	mov es, ax			; segments ever again, as MikeOS and its programs
	mov fs, ax			; live entirely in 64K
	mov gs, ax

;--------

    mov si, Message1
    call os_print_string


	push es
	mov ah, 8			; Get drive parameters
	int 13h
	pop es
	and cx, 3Fh			; Maximum sector number
	mov [SecsPerTrack], cx		; Sector numbers start at 1
	movzx dx, dh			; Maximum head number
	add dx, 1			; Head numbers start at 0 - add 1 for total
	mov [Sides], dx

	mov ax, 1003h			; Set text output with certain attributes
	mov bx, 0			; to be bright, and not blinking
	int 10h

option_screen:
    call os_command_line
    xor ax,ax
    int 0x16
    jmp option_screen    ; Offer menu/CLI choice after CLI has exited

end:

    mov si, Message2
    call os_print_string

    xor ax, ax
    int 0x16
    
    int 0x19
    jmp $
    
;
; --------------------------------
;

; 16bit includes.
    ;%include "features/s2metafile.inc"
    %include "features/s2header.inc"
    %include "features/s2bpb.inc"
    ;%include "features/s2gdt.inc"
    ;%include "features/s2vesa.inc" 
    %include "features/s2config16.inc" 
    ;%include "features/s2a20.inc"
    ;%include "features/s2lib.inc"
    ;%include "features/s2fat12.inc"
    ;%include "features/s2fat16.inc"
    ;%include "features/s2menu16.inc"
    ;%include "features/s2modes.inc"
    %include "features/s2detect.inc"
    %include "features/lib16.inc"
    ; ...

   
    
    
;------------------------------
os_command_line:
    
    ;#todo

	;call os_clear_screen

	mov si, version_msg
	call os_print_string
	mov si, help_text
	call os_print_string

get_cmd:				; Main processing loop
 
    mov si, prompt			; Main loop; prompt for input
    call os_print_string

	;mov si, input

	;mov di, exit_string		; 'EXIT' entered?
	;call os_string_compare
	;jc near exit

    ret


;------------------------------
g16kernDisplayMessage:
    lodsb                  ; load next character
    or al, al              ; test for NUL character
    jz .g16kern_done_message
    mov ah, 0x0E           ; BIOS teletype
    mov bh, 0x00           ; display page 0
    mov bl, 0x07           ; text attribute
    int 0x10               ; invoke BIOS
    jmp g16kernDisplayMessage
.g16kern_done_message:
    ret

os_print_string:
    jmp g16kernDisplayMessage

; messages
Message1 db  0x0D, 0x0A, "G16KERN.BIN: 2000H:0H position", 0x00
Message2 db  0x0D, 0x0A, "G16KERN.BIN: That is all", 0x00
version_msg		db 'MikeOS ', MIKEOS_VER, 13, 10, 0
help_text		db 'Commands: DIR, LS, COPY, REN, DEL, CAT, SIZE, CLS, HELP, TIME, DATE, VER, EXIT', 13, 10, 0

;
; features: 
; Everything bellow goes to the features/ folder.
;

; --------------------------------------------------------------------

	prompt			db '> ', 0


; ---------------------------------------------------------------------------
	Sides dw 2
	SecsPerTrack dw 18
; ******************************************************************
	bootdev db 0			; Boot device number
; ******************************************************************

