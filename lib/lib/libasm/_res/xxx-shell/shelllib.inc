;
; File: shell\shelllib.inc
;
; Descrição:
;     Rotinas de apoio para o Shell do Boot Manager.
;
; 2015 - Created.
; 2017 - ??
;


;---------------------------------------------------
; show_new_prompt:    
;     Cria um prompt de acordo com as configurações.
;     Ex: BMShell>_
;++ 
show_new_prompt:

    ;
	; Questões:
	; Em que partição está o Shell?
    ; Em que diretorio está o Shell?
	;
	
	mov ebx, 0x00FF0000
	mov [os_Font_Color], ebx
	
	;pega
	mov eax, dword [VOLUME.atual]    ;VOL
	
	;Se temos um novo, Colocamos ele.
	cmp eax, dword 0
	jne .new_vol

	;
	; Se não temos um novo, 
	; colocamos o volume 'null' (BM-SHELL:)
	;
	
	;Volume.
	mov eax, dword VOLUME.boot_manager
	call set_volume_atual

.new_vol:	
	;Mostra o volume atual.
	mov esi, dword [VOLUME.atual]    ;volumeX.
	call os_output

	;Mostra o separador ':'.
	mov esi, dword VOLUME.separador    ;:.
	call os_output
	
	mov esi, dword DIRECTORY.separador    ;/.
	call os_output

	;Pega diretório.
	mov eax, dword [DIRECTORY.atual]    ;dir.
	
	cmp eax, dword 0
	jne .new_dir 

	mov esi, dword SHELL.separador1    ;>.
	call os_output	
    ret
	
.new_dir:	
	mov esi, dword [DIRECTORY.atual]
	call os_output

	mov esi, dword DIRECTORY.separador    ;:.
	call os_output

	mov esi, dword SHELL.separador1    ;>.
	call os_output

    ;mov eax, 0	
    ret
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
;fim.
;

