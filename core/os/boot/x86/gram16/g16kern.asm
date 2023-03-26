
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

; option 1
	mov ax, os_init_msg		; Set up the welcome screen
	mov bx, os_version_msg
	mov cx, 10011111b		; Colour: white text on light blue
	call os_draw_background

	mov ax, dialog_string_1		; Ask if user wants app selector or command-line
	mov bx, dialog_string_2
	mov cx, dialog_string_3
	mov dx, 1			; We want a two-option dialog box (OK or Cancel)
	call os_dialog_box
    ;jmp $

	cmp ax, 1			; If OK (option 0) chosen, start app selector
	jne near app_selector

; option 2
	call os_clear_screen		; Otherwise clean screen and start the CLI
	call os_command_line

    jmp option_screen    ; Offer menu/CLI choice after CLI has exited


	; Data for the above code...

	os_init_msg		db 'Welcome to MikeOS', 0
	os_version_msg		db 'Version ', MIKEOS_VER, 0

	dialog_string_1		db 'Thanks for trying out MikeOS!', 0
	dialog_string_2		db 'Please select an interface: OK for the', 0
	dialog_string_3		db 'program menu, Cancel for command line.', 0


; ------------------------------------------------------------------
; #todo
app_selector:

	mov ax, os_init_msg		; Draw main screen layout
	mov bx, os_version_msg
	mov cx, 10011111b		; Colour: white text on light blue
	call os_draw_background

    mov si, test_app_selector_msg
    call os_print_string

    xor ax,ax
    int 0x16
    jmp app_selector		; and go back to the program list

; ------------------------------------------------------------------
    test_app_selector_msg		db 'app selector', 0
    
; ------------------------------------------------------------------
; SYSTEM VARIABLES -- Settings for programs and system calls


	; Time and date formatting

	fmt_12_24	db 0		; Non-zero = 24-hr format

	fmt_date	db 0, '/'	; 0, 1, 2 = M/D/Y, D/M/Y or Y/M/D
					; Bit 7 = use name for months
					; If bit 7 = 0, second byte = separator character

;
; --------------------------------
;

; 16bit includes.
    ;%include "features/s2metafile.inc"
    ;%include "features/s2header.inc"
    ;%include "features/s2bpb.inc"
    ;%include "features/s2gdt.inc"
    ;%include "features/s2vesa.inc" 
    ;%include "features/s2config16.inc" 
    ;%include "features/s2a20.inc"
    ;%include "features/s2lib.inc"
    ;%include "features/s2fat12.inc"
    ;%include "features/s2fat16.inc"
    ;%include "features/s2menu16.inc"
    ;%include "features/s2modes.inc"
    ;%include "features/s2detect.inc"
    ;%include "features/lib16.inc"
    ; ...
    %include "features/cli.inc"
    %include "features/disk.inc"
    %include "features/keyboard.inc"
    %include "features/screen.inc"
    %include "features/string.inc"

; messages
Message1 db  0x0D, 0x0A, "G16KERN.BIN: 2000H:0H position", 0x00
Message2 db  0x0D, 0x0A, "G16KERN.BIN: That is all", 0x00
;version_msg		db 'MikeOS ', MIKEOS_VER, 13, 10, 0
;help_text		db 'Commands: DIR, LS, COPY, REN, DEL, CAT, SIZE, CLS, HELP, TIME, DATE, VER, EXIT', 13, 10, 0


