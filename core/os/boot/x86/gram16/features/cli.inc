

;------------------------------

    ;#todo
    
os_command_line:

	call os_clear_screen

	mov si, version_msg
	call os_print_string
	mov si, help_text
	call os_print_string

get_cmd:				; Main processing loop
 
	mov di, command			; Clear single command buffer
	mov cx, 32
	rep stosb

	mov si, prompt			; Main loop; prompt for input
	call os_print_string

	mov ax, input			; Get command string from user
	mov bx, 64
	call os_input_string

	call os_print_newline

	mov ax, input			; Remove trailing spaces
	call os_string_chomp

	mov si, input			; If just enter pressed, prompt again
	cmp byte [si], 0
	je get_cmd

	mov si, input			; Separate out the individual command
	mov al, ' '
	call os_string_tokenize

	mov word [param_list], di	; Store location of full parameters

	mov si, input			; Store copy of command for later modifications
	mov di, command
	call os_string_copy

	; First, let's check to see if it's an internal command...

	mov ax, input
	call os_string_uppercase

	mov si, input

; ---------------------------

	mov di, exit_string		; 'EXIT' entered?
	call os_string_compare
	jc near do_exit


	mov di, help_string		; 'HELP' entered?
	call os_string_compare
	jc near print_help

	mov di, cls_string		; 'CLS' entered?
	call os_string_compare
	jc near clear_screen

	mov di, ver_string		; 'VER' entered?
	call os_string_compare
	jc near print_ver


    jmp get_cmd


execute_bin:

	;mov ax, 0			; Clear all registers
	;mov bx, 0
	;mov cx, 0
	;mov dx, 0
	;mov word si, [param_list]
	;mov di, 0

	;call 32768			; Call the external program

    jmp get_cmd
; =====================================================================


; ------------------------------------------------------------------
do_exit:
    RET


; ------------------------------------------------------------------

print_help:
	mov si, help_text
	call os_print_string
	jmp get_cmd

; ------------------------------------------------------------------

clear_screen:
	call os_clear_screen
	jmp get_cmd


; ------------------------------------------------------------------

print_ver:
	mov si, version_msg
	call os_print_string
	jmp get_cmd


; =====================================================================


	input			times 64 db 0
	command			times 32 db 0

	dirlist			times 1024 db 0
	tmp_string		times 15 db 0

	file_size		dw 0
	param_list		dw 0

	bin_extension		db '.BIN', 0
	bas_extension		db '.BAS', 0
	pcx_extension		db '.PCX', 0

	prompt			db '> ', 0

	help_text		db 'Commands: DIR, LS, COPY, REN, DEL, CAT, SIZE, CLS, HELP, TIME, DATE, VER, EXIT', 13, 10, 0
	invalid_msg		db 'No such command or program', 13, 10, 0
	nofilename_msg		db 'No filename or not enough filenames', 13, 10, 0
	notfound_msg		db 'File not found', 13, 10, 0
	writefail_msg		db 'Could not write file. Write protected or invalid filename?', 13, 10, 0
	exists_msg		db 'Target file already exists!', 13, 10, 0
	finished_msg		db '>>> Program finished, press any key to continue...', 0

	version_msg		db 'MikeOS ', MIKEOS_VER, 13, 10, 0

	exit_string		db 'EXIT', 0
	help_string		db 'HELP', 0
	cls_string		db 'CLS', 0
	dir_string		db 'DIR', 0
	time_string		db 'TIME', 0
	date_string		db 'DATE', 0
	ver_string		db 'VER', 0
	cat_string		db 'CAT', 0
	del_string		db 'DEL', 0
	ren_string		db 'REN', 0
	copy_string		db 'COPY', 0
	size_string		db 'SIZE', 0
	list_string		db 'LS', 0

	kern_file_string	db 'KERNEL', 0
	kern_warn_msg		db 'Cannot execute kernel file!', 13, 10, 0


; ==================================================================

