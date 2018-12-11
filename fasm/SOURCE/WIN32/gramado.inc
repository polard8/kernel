;gramado.inc 
;usado para portar fasm para gramado 0.4 



gramado_init_memory_fake:
	mov esi, gramado_string_initmemory
	call DisplayMessage

    ret

	
;;#todo	
gramado_init_memory:
    ret
;;
;; get param
;;

;;
;; ==========================================================
;; get_params
;; >>> Pegando os parâmtros da função.
;; ou seja a linha de comandos com os tokens usados.	
;; #todo: Isso será feito atravez de um endereço de memória compartilhado.
;; Essa rotina servirá de inspiração para pegar os argumentos da linha de comandos 
;; passada via memória.
;;

gramado_get_params_fake:
	mov esi, gramado_string_getparam
	call DisplayMessage

	mov	[input_file],0
	mov	[output_file],0
	mov	[symbols_file],0
	mov	[memory_setting],0
	mov	[passes_limit],100
    ret

gramado_get_params:

	mov esi, gramado_string_getparam
	call DisplayMessage

	mov	[input_file],0
	mov	[output_file],0
	mov	[symbols_file],0
	mov	[memory_setting],0
	mov	[passes_limit],100
	call	[GetCommandLine]
	mov	[definitions_pointer],predefinitions
	mov	esi,eax
	mov	edi,params
find_command_start:
	lodsb
	cmp	al,20h
	je	find_command_start
	cmp	al,22h
	je	skip_quoted_name
skip_name:
	lodsb
	cmp	al,20h
	je	find_param
	or	al,al
	jz	all_params
	jmp	skip_name
skip_quoted_name:
	lodsb
	cmp	al,22h
	je	find_param
	or	al,al
	jz	all_params
	jmp	skip_quoted_name
find_param:
	lodsb
	cmp	al,20h
	je	find_param
	cmp	al,'-'
	je	option_param
	cmp	al,0Dh
	je	all_params
	or	al,al
	jz	all_params
	cmp	[input_file],0
	jne	get_output_file
	mov	[input_file],edi
	jmp	process_param
get_output_file:
	cmp	[output_file],0
	jne	bad_params
	mov	[output_file],edi
process_param:
	cmp	al,22h
	je	string_param
    copy_param:
	cmp	edi,params+1000h
	jae	bad_params
	stosb
	lodsb
	cmp	al,20h
	je	param_end
	cmp	al,0Dh
	je	param_end
	or	al,al
	jz	param_end
	jmp	copy_param
string_param:
	lodsb
	cmp	al,22h
	je	string_param_end
	cmp	al,0Dh
	je	param_end
	or	al,al
	jz	param_end
	cmp	edi,params+1000h
	jae	bad_params
	stosb
	jmp	string_param
option_param:
	lodsb
	cmp	al,'m'
	je	memory_option
	cmp	al,'M'
	je	memory_option
	cmp	al,'p'
	je	passes_option
	cmp	al,'P'
	je	passes_option
	cmp	al,'d'
	je	definition_option
	cmp	al,'D'
	je	definition_option
	cmp	al,'s'
	je	symbols_option
	cmp	al,'S'
	je	symbols_option
bad_params:
	stc
	ret
    get_option_value:
	xor	eax,eax
	mov	edx,eax
get_option_digit:
	lodsb
	cmp	al,20h
	je	option_value_ok
	cmp	al,0Dh
	je	option_value_ok
	or	al,al
	jz	option_value_ok
	sub	al,30h
	jc	invalid_option_value
	cmp	al,9
	ja	invalid_option_value
	imul	edx,10
	jo	invalid_option_value
	add	edx,eax
	jc	invalid_option_value
	jmp	get_option_digit
option_value_ok:
	dec	esi
	clc
	ret
invalid_option_value:
	stc
	ret
memory_option:
	lodsb
	cmp	al,20h
	je	memory_option
	cmp	al,0Dh
	je	bad_params
	or	al,al
	jz	bad_params
	dec	esi
	call	get_option_value
	or	edx,edx
	jz	bad_params
	cmp	edx,1 shl (32-10)
	jae	bad_params
	mov	[memory_setting],edx
	jmp	find_param
passes_option:
	lodsb
	cmp	al,20h
	je	passes_option
	cmp	al,0Dh
	je	bad_params
	or	al,al
	jz	bad_params
	dec	esi
	call	get_option_value
	or	edx,edx
	jz	bad_params
	cmp	edx,10000h
	ja	bad_params
	mov	[passes_limit],dx
	jmp	find_param
definition_option:
	lodsb
	cmp	al,20h
	je	definition_option
	cmp	al,0Dh
	je	bad_params
	or	al,al
	jz	bad_params
	dec	esi
	push	edi
	mov	edi,[definitions_pointer]
	call	convert_definition_option
	mov	[definitions_pointer],edi
	pop	edi
	jc	bad_params
	jmp	find_param
symbols_option:
	mov	[symbols_file],edi
find_symbols_file_name:
	lodsb
	cmp	al,20h
	jne	process_param
	jmp	find_symbols_file_name
param_end:
	dec	esi
string_param_end:
	cmp	edi,params+1000h
	jae	bad_params
	xor	al,al
	stosb
	jmp	find_param
all_params:
	cmp	[input_file],0
	je	bad_params
	mov	eax,[definitions_pointer]
	mov	byte [eax],0
	mov	[initial_definitions],predefinitions
	clc
	ret
convert_definition_option:
	mov	ecx,edi
	cmp	edi,predefinitions+1000h
	jae	bad_definition_option
	xor	al,al
	stosb
copy_definition_name:
	lodsb
	cmp	al,'='
	je	copy_definition_value
	cmp	al,20h
	je	bad_definition_option
	cmp	al,0Dh
	je	bad_definition_option
	or	al,al
	jz	bad_definition_option
	cmp	edi,predefinitions+1000h
	jae	bad_definition_option
	stosb
	inc	byte [ecx]
	jnz	copy_definition_name
bad_definition_option:
	stc
	ret
copy_definition_value:
	lodsb
	cmp	al,20h
	je	definition_value_end
	cmp	al,0Dh
	je	definition_value_end
	or	al,al
	jz	definition_value_end
	cmp	al,'\'
	jne	definition_value_character
	cmp	byte [esi],20h
	jne	definition_value_character
	lodsb
definition_value_character:
	cmp	edi,predefinitions+1000h
	jae	bad_definition_option
	stosb
	jmp	copy_definition_value
definition_value_end:
	dec	esi
	cmp	edi,predefinitions+1000h
	jae	bad_definition_option
	xor	al,al
	stosb
	clc
	ret




;;
;; #exit
;;

gramado_exit_program:

    ;;#todo:
	;;chamar a system call exit 
	
	mov esi, gramado_string_hang
	call DisplayMessage
	
.hang:	
    pause
	jmp .hang
    jmp $
	
;;
;;  ## Messages ##
;;


gramado_string_string1: db 'Running fasm on Gramado 0.4', 0Dh, 0Ah,0
gramado_string_welcome: db 'Welcome to fasm for gramado 0.4', 0Dh, 0Ah,0

;; debug messages
gramado_string_step1: db 'Step1', 0Dh, 0Ah,0
gramado_string_step2: db 'Step2', 0Dh, 0Ah,0
gramado_string_step3: db 'Step3', 0Dh, 0Ah,0
gramado_string_step4: db 'Step4', 0Dh, 0Ah,0
gramado_string_step5: db 'Step5', 0Dh, 0Ah,0
gramado_string_step6: db 'Step6', 0Dh, 0Ah,0
gramado_string_step7: db 'Step7', 0Dh, 0Ah,0
gramado_string_step8: db 'Step8', 0Dh, 0Ah,0


gramado_string_getparam: db 'Getting param', 0Dh, 0Ah,0
gramado_string_initmemory: db 'Init memory', 0Dh, 0Ah,0
;;...


gramado_string_copyright db 'Copyright (c) 1999-2018, Tomasz Grysztar',0Dh,0Ah,0


;gramado_string_logo db 'flat assembler  version ',VERSION_STRING,0
gramado_string_logo db 'flat assembler  version ','1.73',0

gramado_string_usage db 0Dh,0Ah
       db 'usage: fasm <source> [output]',0Dh,0Ah
       db 'optional settings:',0Dh,0Ah
       db ' -m <limit>         set the limit in kilobytes for the available memory',0Dh,0Ah
       db ' -p <limit>         set the maximum allowed number of passes',0Dh,0Ah
       db ' -d <name>=<value>  define symbolic variable',0Dh,0Ah
       db ' -s <file>          dump symbolic information for debugging',0Dh,0Ah
       db 0
gramado_string_memory_prefix db '  (',0
gramado_string_memory_suffix db ' kilobytes memory)',0Dh,0Ah,0
gramado_string_passes_suffix db ' passes, ',0
gramado_string_seconds_suffix db ' seconds, ',0
gramado_string_bytes_suffix db ' bytes.',0Dh,0Ah,0



gramado_string_hang: db '*HANG', 0Dh, 0Ah,0


;;
;; ===================================================================================
;;                                #### BUFFER  ####
;; ===================================================================================
;;

;; BUFFER PARA EVITARMOS ALOCAÇÃO POR ENQUANTO. 


BUFFER1:
    ;;4KB
    times 4096 DB 0  
BUFFER1_END:
    DB 0
	
BUFFER2:
    ;;4KB
    times 4096 DB 0  
BUFFER2_END:
    DB 0

BUFFER3:
    ;;4KB
    times 4096 DB 0  
BUFFER3_END:
    DB 0
	
BUFFER4:
    ;;4KB
    times 4096 DB 0  
BUFFER4_END:
    DB 0
	
	
	
	


