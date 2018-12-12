;;
;; FASM.ASM
;;
;;  Essa é uma versão modificada, na trentativa de portar o fasm para 
;; o sistema gramado 0.4
;;  Esse arquivo é compilado com a ide do fasm.
;;


;;
;; #todo
;; Ante de tudo precisamos criar um .bin compatível com gramado e que 
;; exiba alguma mensagem quando rodar no gramado. 
;; para isso vamos incluir a biblioteca asm.inc, que ja possui 
;; suporte a impressãod e strings no gamado.
;;


; flat assembler interface for Win32
; Copyright (c) 1999-2018, Tomasz Grysztar.
; All rights reserved.


	format PE console	
		
	;; #bugbug 
	;; no código start está começando em 0x400 .
	;; mas o assembler cria o símbolo start em 0x1000, que é o alinhamento padrão para PE.
	
    ;COMO A COMPILAÇÃO ATRAVÉS DA GUI TÁ DANDO PROBLEMA, PODEMOS TENTAR COMPILAR COM LINHA DE COMANDOS O 'FASM'	

section '.text' code readable executable

start:

    jmp after_my_awesome_stuff
	include 'c:\gramado\lib\asm\asm.inc'
	include 'gramado.inc'
after_my_awesome_stuff:

   	;xor eax, eax
	;mov al, 0xfA
    ;call print_hex 

	;mov al, 4
	;call print_spaces
	
   	;xor eax, eax
	;mov al, 0xed
    ;call print_hex 

	;mov al, 4
	;call print_spaces
	
	;mov al, 'F'
	;call putchar

	;mov al, 'R'
	;call putchar

	;mov al, 'E'
	;call putchar

	;mov al, 'D'
	;call putchar
	
	;mov al, 4
	;call print_spaces
	
	;; #importante
	;; Isso funciona. É o começo do arquivo. MZ.
    ;mov esi, 0x400000 
    ;call DisplayMessage	
	
	
	;mov esi, gramado_string_welcome
    ;call DisplayMessage	
	
    ;; #debug
	;; jmp $
	
	
	;#supenso. ??
	;mov [con_handle],STD_OUTPUT_HANDLE
	
	;; #suspenso 
	;;não funciona.
	mov	esi, _logo
    call DisplayMessage
	;call display_string
	
    ;;
	;; ## Step 1 ##
	;;
 
 	mov esi, gramado_string_step1
    call DisplayMessage	
	
	;;#importante
	;;pega os argumentos passados via linha de comandos.
    ;;ok isso funcionou. 
	
	;;call gramado_get_params_fake
	call get_params
	jc	information

    ;;
	;; ## Step 2 ##
	;;
	
 	mov esi, gramado_string_step2
    call DisplayMessage

 
    ;;#todo 
    ;;temos que chamar uma rotina quye inicialize a memória 
    ;;são vários elementos.	
	
	;call	init_memory
    call gramado_init_memory_fake
	
	
	;;
	;; fake fake init memory
	;;

	mov dword [memory_start], BUFFER1
	mov dword [memory_end],  BUFFER1_END
	mov dword [additional_memory], BUFFER2
	mov dword [additional_memory_end], BUFFER2_END
	
	;mov	esi,_memory_prefix
	;call	display_string
	
	mov esi, gramado_string_memory_prefix
	call DisplayMessage
	
	mov	eax,[memory_end]
	sub	eax,[memory_start]
	add	eax,[additional_memory_end]
	sub	eax,[additional_memory]
	shr	eax,10
	
	;;display number
	;; vamos tentar a função da lib do gramado.
	
	;call	display_number
	call print_hex
	
	
	;mov	esi, _memory_suffix
	;call	display_string

	mov esi, gramado_string_memory_suffix
	call DisplayMessage
	

		

	;;==============================================
    
	;;time 
	
	;; #SUSPENSO 
	;;suspenso toda essa coisa de tempo por enquanto.
	;call	[GetTickCount]
	;mov	[start_time],eax
	
	
	


	
	;;==============================================
	
	;;
	;; ## preprocessor ##
	;;
	
    ;;
	;; ## Step 3 ##
	;;	
	
 	mov esi, gramado_string_step3
    call DisplayMessage			
	
	
	and	[preprocessing_done],0
	
	;#supendendo o preprocessador.
	;faremos debug de cada uma das partes suspensas, individualmente 
	call	preprocessor
	;call preprocessor_interface
	
	or	[preprocessing_done],-1
	
	
   ;;#debug
	;jmp $		
	
	;;
	;; ## parser ##
	;;
	
    ;;
	;; ## Step 4 ##
	;;
	
 	mov esi, gramado_string_step4
    call DisplayMessage			

	;;#debug
	;mov esi, gramado_string_breakpoint
	;call DisplayMessage			
	;;#debug 
	;jmp $		
	
	call	parser
	;call parser_interface
	
	;;
	;; ## assembler ##
	;;
 	mov esi, gramado_string_step5
    call DisplayMessage	

	;;#debug
	;mov esi, gramado_string_breakpoint
	;call DisplayMessage			
	;;#debug 
	;jmp $		
	
	;;#suspensa a chamada ao assembler ... dá loop
	;faremos debug de cada uma das partes suspensas, individualmente 	
	;call	assembler
	;call assembler_interface
	
	
	
	;;
	;; ## formatter ##
	;;
	
    ;;
	;; ## Step 6 ##
	;;	
	
 	;mov esi, gramado_string_step6
    ;call DisplayMessage	

	;;#debug
	;mov esi, gramado_string_breakpoint
	;call DisplayMessage			
	;;#debug 
	;jmp $			
	
	;;#suspenso pois vai lidar muito com arquivo e 
	;;salvamento de arquivo.
	;faremos debug de cada uma das partes suspensas, individualmente 	
	;;call	formatter
	
	
    ;;
	;; ## Step 7 ##
	;;	
	
 	mov esi, gramado_string_step7
    call DisplayMessage	
	
	;;#debug
	;mov esi, gramado_string_breakpoint
	;call DisplayMessage			
	;#debug 
	;jmp $		

	;;supende: isso é firula.
	;;mostra alguma estatísitica ..
	;;manipula funções do windows
	;;call	display_user_messages
	
	
	;;#suspendendo várias coisas com timer.
	
	;movzx	eax, [current_pass]
	;inc	eax
	;call	display_number
	;call printf_hex
	
	;mov	esi, _passes_suffix
	;call	display_string
	
	;call	[GetTickCount]
	;sub	eax,[start_time]
	;xor	edx,edx
	;mov	ebx,100
	;div	ebx
	;or	eax,eax
	;jz	display_bytes_count
	;xor	edx,edx
	;mov	ebx,10
	;div	ebx
	
	;push	edx
	;call	display_number
	
	;mov	dl,'.'
	;call	display_character
	
	;pop	eax
	;call	display_number
	
	;mov	esi,_seconds_suffix
	;call	display_string
	
	;mostrar estatísticas,
	
;display_bytes_count:

    ;;
	;; ## Step 8 ##
	;;

 	;mov esi, gramado_string_step8
    ;call DisplayMessage		
	
	;;#debug
	;mov esi, gramado_string_breakpoint
	;call DisplayMessage			
	;;#debug 
	;jmp $	
	
	;mov	eax, [written_size]
	;call display_number
	;call print_hex
	
	
	;mov	esi, gramado_string_bytes_suffix ;_bytes_suffix
	;call	display_string
	;call DisplayMessage 
	
	
	mov esi, gramado_string_fim_do_programa
	call DisplayMessage			
	
	
	;;return 0. OK
	xor	al,al
	jmp	exit_program
	
	
	;;
	;; #falhou
	;; Mostraremos uma mensagem de como usar e abortaremos.
	;;

information:
	
	;;#mesage.
	mov	esi, gramado_string_usage
	call DisplayMessage
	
	mov	al, 1
	jmp gramado_exit_program
	;jmp	exit_program
	
	
;;
;; ==========================================================
;; get_params
;; >>> Pegando os parâmetros da função.
;; ou seja a linha de comandos com os tokens usados.	
;; #todo: Isso será feito atravez de um endereço de memória compartilhado.
;; Essa rotina servirá de inspiração para pegar os argumentos da linha de comandos 
;; passada via memória.
;;

get_params:
    ;redirecionando.
	;jmp gramado_get_params
	;jmp $
	
	;;#suspendendo
	;;tentando habilitar essa função. 
	
	;; ??
	;;inicializando variáveis. ??
	
	mov	[input_file], 0
	mov	[output_file], 0
	mov	[symbols_file], 0
	mov	[memory_setting], 0
	mov	[passes_limit], 100
	
	;The return value is a pointer to the command-line string for the current process.
	;presumo que o ponteiro retorne em eax. 
	
	;call	[GetCommandLine] 
	call gramado_GetCommandLine 

	;sendo eax a command line 
	;torna-se a origem. 
	;param é o destino.
	
	mov	esi, eax
	mov	edi, params
	
	mov	[definitions_pointer], predefinitions
	
find_command_start:
	
	;pega al.
	lodsb
	
	;suprime espaços.
	cmp	al, 20h
	je find_command_start
	
	;;quote stuff
	cmp	al, 22h
	je	skip_quoted_name
	
skip_name:
	
	lodsb
	
	;se for espaço vamos procurar o parametro, antes suprimindo os espaços.
	cmp	al, 20h
	je	find_param
	
	;;ok não é espaço.
	or	al, al
	jz all_params  ;;#sensível.
	
	jmp	skip_name
	
skip_quoted_name:
	lodsb
	
	;suprime coisas do tipo.
	cmp al, 22h
	je find_param
	
	or al, al
	jz all_params   ;#sensível.
	jmp	skip_quoted_name
	
find_param:
	lodsb
	
	;suprime espaços.
	cmp	al, 20h
	je find_param
	
	;;se encontramos o '-'
	;;parametro de operação. 
	
	cmp	al, '-'
	je option_param
	
	;cr ou lf. ??
	cmp	al, 0Dh
	je all_params ;#sensível.
	
	or	al, al
	jz	all_params ;#sensível.
	
	;;??
	;;se já temos um ponteiro para o arquivo de entrada então 
	;;presizamos do arquivo de saída.
	;;acho que estamos falando da string do nome.
	
	cmp	[input_file], 0
	jne	get_output_file
	
	;;#bugbug
	;; De forma determinística o fasm assume que agora temos um nome.
	
	mov	[input_file], edi
	jmp	process_param


;;vamos pegar o arquivo de saída pois já temos o de entrada.    
get_output_file:
	cmp	[output_file],0
	jne	bad_params
	mov	[output_file],edi
 
;;vamos processar parâmtro. Mas qual ? 
process_param:
	
	;??
	cmp al, 22h
	je string_param
    
	;;copiar o parâmetro.
copy_param:
	
	;;comparamos o destino com um endereço da tabela.
	;;se der errado falhamos.
	cmp	edi, params+1000h
	jae	bad_params
	
	stosb
	lodsb
	
	;é um espaço. ??
	cmp	al, 20h
	je param_end
	
	cmp	al, 0Dh
	je param_end
	
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

   ;; estamos aqui porque encontramos o '-'.	
option_param:
	lodsb
	
	;;flag memória.
	cmp al, 'm'
	je	memory_option
	cmp	al,'M'
	je memory_option
	
	;flag passes
	cmp	al, 'p'
	je	passes_option
	cmp	al, 'P'
	je	passes_option
	
	;flag definition
	cmp	al,'d'
	je	definition_option
	cmp	al,'D'
	je	definition_option
	
	;flag symbol
	cmp	al,'s'
	je	symbols_option
	cmp	al,'S'
	je	symbols_option

   ;;
   ;; #error: Nenhuma switch válida.
   ;;
	
bad_params:
	stc
	ret
    
get_option_value:
	xor	eax, eax
	mov	edx, eax
	
get_option_digit:
	
	lodsb
	
	cmp	al, 20h
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
    
;;flag m selecionada.
memory_option:
	lodsb
	
	;;suprime espaços.
	cmp	al, 20h
	je	memory_option
	
	cmp	al,0Dh
	je	bad_params
	
	or	al,al
	jz	bad_params
	dec	esi
	
	call	get_option_value
	
	or	edx,edx
	jz	bad_params
	
	cmp	edx, 1 shl (32-10)
	jae	bad_params
	
	mov	[memory_setting], edx
	jmp	find_param

;;flag p selecionada.    
passes_option:
	
	lodsb
	
	;;suprimir espaços.
	cmp	al,20h
	je	passes_option
	
	cmp	al,0Dh
	je	bad_params
	
	or	al,al
	jz	bad_params
	
	dec	esi
	
	call	get_option_value
	
	or	edx, edx
	jz	bad_params
	
	cmp	edx, 10000h
	ja	bad_params
	
	mov	[passes_limit], dx
	jmp	find_param

;;flag d selecionada.    
definition_option:
	lodsb
	cmp	al, 20h
	je	definition_option
	
	cmp	al, 0Dh
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

;;flag s selecionada.    
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
	cmp	edi, params+1000h
	jae	bad_params
	xor	al,al
	stosb
	jmp	find_param

   ;; ??	
all_params:
	
	;;falhou nosso arquivo de entrada.
	cmp	[input_file], 0
	je	bad_params
	
	mov eax, [definitions_pointer]
	mov	byte [eax], 0
	mov	[initial_definitions], predefinitions
	clc
	ret
	
convert_definition_option:
	mov	ecx, edi
	
	cmp	edi, predefinitions+1000h
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
	
	cmp	edi, predefinitions+1000h
	jae	bad_definition_option
	
	stosb
	inc	byte [ecx]
	jnz	copy_definition_name
	
bad_definition_option:
	stc
	ret
	
copy_definition_value:
	lodsb
	
	cmp	al, 20h
	je	definition_value_end
	
	cmp	al, 0Dh
	je	definition_value_end
	
	or	al, al
	jz	definition_value_end
	
	cmp	al, '\'
	jne	definition_value_character
	
	cmp	byte [esi], 20h
	jne	definition_value_character
	
	lodsb
	
definition_value_character:
	cmp	edi, predefinitions+1000h
	jae	bad_definition_option
	stosb
	jmp	copy_definition_value
	
definition_value_end:
	dec	esi
	cmp	edi, predefinitions+1000h
	jae	bad_definition_option
	xor	al,al
	stosb
	clc
	ret
	
;;=========================================	

include 'system.inc'

include '..\errors.inc'
include '..\symbdump.inc'
include '..\preproce.inc'
include '..\parser.inc'
include '..\exprpars.inc'
include '..\assemble.inc'
include '..\exprcalc.inc'
include '..\formats.inc'
include '..\x86_64.inc'
include '..\avx.inc'

include '..\tables.inc'
include '..\messages.inc'


;;#bugbug 
;;mudando isso de lugar para deixar as mensagems na sessão de código.
;;section '.data' data readable writeable

include '..\version.inc'

_copyright db 'Copyright (c) 1999-2018, Tomasz Grysztar', 0Dh, 0Ah, 0
_logo      db 'flat assembler  version ', VERSION_STRING, 0Dh, 0Ah,0
_memory_prefix   db '  (',0
_memory_suffix   db ' kilobytes memory)', 0Dh, 0Ah,0
_passes_suffix   db ' passes, ',0
_seconds_suffix  db ' seconds, ',0
_bytes_suffix    db ' bytes.', 0Dh, 0Ah,0
_usage db 0Dh, 0Ah
       db 'usage: fasm <source> [output]', 0Dh, 0Ah
       db 'optional settings:', 0Dh, 0Ah
       db ' -m <limit>         set the limit in kilobytes for the available memory',0Dh,0Ah
       db ' -p <limit>         set the maximum allowed number of passes',0Dh,0Ah
       db ' -d <name>=<value>  define symbolic variable',0Dh,0Ah
       db ' -s <file>          dump symbolic information for debugging',0Dh,0Ah
       db 0

align 4

section '.data' data readable writeable

include '..\variable.inc'

con_handle dd ?
memory_setting dd ?
start_time dd ?
definitions_pointer dd ?
bytes_count dd ?
displayed_count dd ?
character db ?
last_displayed rb 2
preprocessing_done db ?

params rb 1000h
options rb 1000h
predefinitions rb 1000h
buffer rb 4000h

stack 10000h

section '.idata' import data readable writeable

  dd 0,0,0,rva kernel_name,rva kernel_table
  dd 0,0,0,0,0

;Funções do windows chamada pelo fasm. 
;isso não será mais usado, chmaremos funções similares 
;feitas em gramado.inc 
kernel_table:
    ExitProcess             dd rva _ExitProcess
    CreateFile              dd rva _CreateFileA
    ReadFile                dd rva _ReadFile
    WriteFile               dd rva _WriteFile
    CloseHandle             dd rva _CloseHandle
    SetFilePointer          dd rva _SetFilePointer
    GetCommandLine          dd rva _GetCommandLineA
    GetEnvironmentVariable  dd rva _GetEnvironmentVariable
    GetStdHandle            dd rva _GetStdHandle
    VirtualAlloc            dd rva _VirtualAlloc
    VirtualFree             dd rva _VirtualFree
    GetTickCount            dd rva _GetTickCount
    GetSystemTime           dd rva _GetSystemTime
    GlobalMemoryStatus      dd rva _GlobalMemoryStatus
    dd 0

  kernel_name db 'KERNEL32.DLL',0

  _ExitProcess dw 0
    db 'ExitProcess',0
  _CreateFileA dw 0
    db 'CreateFileA',0
  _ReadFile dw 0
    db 'ReadFile',0
  _WriteFile dw 0
    db 'WriteFile',0
  _CloseHandle dw 0
    db 'CloseHandle',0
  _SetFilePointer dw 0
    db 'SetFilePointer',0
  _GetCommandLineA dw 0
    db 'GetCommandLineA',0
  _GetEnvironmentVariable dw 0
    db 'GetEnvironmentVariableA',0
  _GetStdHandle dw 0
    db 'GetStdHandle',0
  _VirtualAlloc dw 0
    db 'VirtualAlloc',0
  _VirtualFree dw 0
    db 'VirtualFree',0
  _GetTickCount dw 0
    db 'GetTickCount',0
  _GetSystemTime dw 0
    db 'GetSystemTime',0
  _GlobalMemoryStatus dw 0
    db 'GlobalMemoryStatus',0

section '.reloc' fixups data readable discardable
