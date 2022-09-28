;
; File: shell/shlib.inc
;
; Descrição:
;     Rotinas de apoio para o Shell do Boot Manager.
;     2015 - Created.


; ========================
; show_new_prompt:    
;     Show the prompt string.
;     See: shmsg.inc

show_prompt_string:
    nop
show_new_prompt:

    mov esi, dword SHELL.prompt_string
    call os_output

    mov esi, dword SHELL.prompt_string_separator1
    call os_output

    mov esi, dword SHELL.prompt_string_separator1
    call os_output

    mov esi, dword SHELL.prompt_string_separator2
    call os_output

    ret

;.new_dir:	
	;mov esi, dword [DIRECTORY.atual]
	;call os_output

	;mov esi, dword DIRECTORY.separador    ; ':'
	;call os_output

	;mov esi, dword SHELL.separador1       ; '>'
	;call os_output

    ;mov eax, 0	
    ;ret
;--





;-----------------------------------------
; set_shell_volume:
;
;     Configura o endereço do volume atual. ??
;     Deve ser o endereço da string ?!
; in = eax.
;
;++
set_shell_volume:
    mov dword [SHELL.volume], eax
    mov dword [VOLUME.atual], eax
	;mov eax, 0
    ret
;--	


;-----------------------------------------	
; set_shell_volume:
;
;     Configura o endereço do directory atual.
;
; in = eax.
;
;++
set_shell_directory:
    mov dword [SHELL.directory], eax
    mov dword [DIRECTORY.atual], eax
	;mov eax, 0
    ret
;--


shelllibPrintVersion:
    call print_ver
    ret

;
; End.
;

