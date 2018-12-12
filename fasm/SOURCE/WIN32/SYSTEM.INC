
; flat assembler interface for Win32
; Copyright (c) 1999-2018, Tomasz Grysztar.
; All rights reserved.

CREATE_NEW	       = 1
CREATE_ALWAYS	       = 2
OPEN_EXISTING	       = 3
OPEN_ALWAYS	       = 4
TRUNCATE_EXISTING      = 5

FILE_SHARE_READ        = 1
FILE_SHARE_WRITE       = 2
FILE_SHARE_DELETE      = 4

GENERIC_READ	       = 80000000h
GENERIC_WRITE	       = 40000000h

STD_INPUT_HANDLE       = 0FFFFFFF6h
STD_OUTPUT_HANDLE      = 0FFFFFFF5h
STD_ERROR_HANDLE       = 0FFFFFFF4h

MEM_COMMIT	       = 1000h
MEM_RESERVE	       = 2000h
MEM_DECOMMIT	       = 4000h
MEM_RELEASE	       = 8000h
MEM_FREE	       = 10000h
MEM_PRIVATE	       = 20000h
MEM_MAPPED	       = 40000h
MEM_RESET	       = 80000h
MEM_TOP_DOWN	       = 100000h

PAGE_NOACCESS	       = 1
PAGE_READONLY	       = 2
PAGE_READWRITE	       = 4
PAGE_WRITECOPY	       = 8
PAGE_EXECUTE	       = 10h
PAGE_EXECUTE_READ      = 20h
PAGE_EXECUTE_READWRITE = 40h
PAGE_EXECUTE_WRITECOPY = 80h
PAGE_GUARD	       = 100h
PAGE_NOCACHE	       = 200h


;;
;; init memory
;;

init_memory:
	
	;inicializando a variável.
	xor	eax, eax
	mov	[memory_start], eax
	
	;;
	;; # pilha #
	;;
	
	
	;;atualizando o limite da pilha;
	;;salvo em [stack_limit]
	
	;;#bugbug #hackhack, vamos suspender essa parte e deixar a pilha do jeito que está.
	;;estamos adicionando mais pilha ...
	;;isso é perigoso e desnecessário.

	
	mov	eax, esp
	
	;;#bugbug 
	;;suspendendo.
	;;and	eax, not 0FFFh
	;;add	eax, 1000h-10000h   
	
	mov	[stack_limit], eax
	
	;;
	;; #memory setting
	;;
	
	;;#bugbug 
	;;estamos pegando um valor qu eu nem sei se está inicializado.
	
	;; caso memory setting não satisfaça 
	;; vamos chamar o alocador.
	
	mov	eax, [memory_setting]
	shl	eax, 10
	jnz	allocate_memory
	
	
	
	;; #importante:
	;; 'buffer' Isso é um ponteiro para uma estrutura
	;; onde o sistema deve colocar informações sobre memória.
	
    ;DWORD  dwLength;
    ;DWORD  dwMemoryLoad;
    ;SIZE_T dwTotalPhys;
    ;SIZE_T dwAvailPhys;
    ;SIZE_T dwTotalPageFile;
    ;SIZE_T dwAvailPageFile;
    ;SIZE_T dwTotalVirtual;
    ;SIZE_T dwAvailVirtual;	
	
	;;#IMPORTANTE: CANCELAMOS A CHAMADA QUE DÁ INFORMAÇÕES SOBRE A MEMÓRIA
	;push	buffer 
	;call	[GlobalMemoryStatus]
	;call gramado_GlobalMemoryStatus
	
	mov	eax, dword [buffer+20]
	mov	edx, dword [buffer+12]
	
	;;offset 20
	cmp	eax, 0
	jl	large_memory
	
	;;offset 12
	cmp	edx, 0
	jl	large_memory
	
	shr	eax, 2
	add	eax, edx
	
	jmp	allocate_memory
	

;; ============================================
;; Alocador de memória
;; #todo: Devemos usar o alocador do gramado.	
;; temos que criar uma rotina que aloque memória.
;; #todo: vamos tentar usar buffers por enquanto.
;;

;;alocar.
large_memory:
	mov	eax, 80000000h
	
;;alocar memória	
;; o valor está em eax
allocate_memory:

	;;#debug
	;mov esi, gramado_string_breakpoint
	;call DisplayMessage			
	;;#debug 
	;jmp $	
	
	mov	edx, eax
	shr	edx, 2
	mov	ecx, eax
	sub	ecx, edx
	
	mov	[memory_end], ecx
	mov	[additional_memory_end], edx
	
	;;
	;; # alocar memória #
	;;
	
	;;#BUGBUG VAMOS CANCELAR ESSSA CHAMADA POR ENQUANTO E DETERMINAR UM ENDEREÇO.
	mov eax, BUFFER1
	;mov eax, BUFFER2
	
	;; Chamando o Windows para alocar memória.
	
	;push PAGE_READWRITE
	;push MEM_COMMIT
	;push eax
	;push 0
	
	;call [VirtualAlloc]
	;call gramado_VirtualAlloc
	
	;; se der problemas, então não temos a memória que precisamos 
	;; vamos tentar de outro jeito, se não der certo, abortaremos. 
	
	or	eax, eax
	jz	not_enough_memory
	
	;; #importante:
	;; é o início da memória ;;
	;; podemos usar um buffer nesse momento. 
	
	;;configurando início e fim.
	;;isso tá estranho.
	;;o valor do fim não foi inicializado ainda, porque estamos usando.
	;;e usando desse jeito estranho.
	
	;;#BUGBUG 
	;;ESTAMOS DETERMINANDO O TAMANHO DA MEMÓRIA. 
	
	mov	[memory_start], eax
	add	eax, 4096  ;;[memory_end]   ;;4kb
	mov	[memory_end], eax
	
	;;configurando memória adicional.
	
	mov	[additional_memory],eax
	add	[additional_memory_end],eax
	
	ret
	
;; não temos a quantiodade de memória que precisamos,
;;tentatermos outra coisa e abortaremos se não conseguirmos.
	
not_enough_memory:

	mov	eax, [additional_memory_end]
	shl	eax, 1
	
	cmp	eax, 4000h
	jb	out_of_memory
	
	jmp	allocate_memory

	
;;
;; ## exit ##
;;	
	
exit_program:

    jmp gramado_exit_program
	jmp $
	
	;;#hack hack 
	;;estamos suspendendo esse tratamento de exit 
	;;e pulando para um mais básico, não precisamos liberar memória 
	;;po enquanto. 
	
	;movzx	eax,al
	;push	eax
	;mov	eax,[memory_start]
	;test	eax,eax
	;jz	do_exit
	;push	MEM_RELEASE
	;push	0
	;push	eax
	;call	[VirtualFree]
    do_exit:
	;call	[ExitProcess]
    jmp gramado_exit_program
	jmp $
	
;;
;;=================================
;; variáveis de ambiente.
;;	

;possivelmente esi comtem uma string "INCLUDE"
;e o destino é o 'memory start'.
get_environment_variable:
    
	;calculando o tamanho da memória.
	mov	ecx, [memory_end]
	sub	ecx, edi
	
	cmp	ecx, 4000h
	jbe	buffer_for_variable_ok
	
	;ajusta o buffer.
	;#bugbug: se não tem inventa .. kkk
	
	mov	ecx, 4000h
buffer_for_variable_ok:
	
	
	;;#bugbug 
	;;#hackhack 
	;;suspendendo essa parte de chamar o window para pegar 
	;;variáveis de ambiente 
	;;se elas relmente forem necessárias só saberemos no futuro. 
	
	;push	ecx
	;push	edi
	;push	esi
	;call	[GetEnvironmentVariable]
	
	;;#bugbug:
	;;#hackhack
	;;pelo jeito eax retorna o tamanho dá área onde ficam as 
	;;variáveis de ambiente ... e esse tamanho é adicionado a o destino. 
	;; em seguida compar com o fim da memória disponível ...
	;;; se naõ tem mais memória, acabou a brincadeira. 
	
	;;suspendendo essa adição pois não temos o valor de eax .
	;add	edi, eax
	
	cmp	edi, [memory_end]
	jae	out_of_memory
	
	ret
	
	;;========================================
	
;;
;; open
;;	
	

open:
    ;redirecionando 
	jmp gramado_open_fake
	
	push	0
	push	0
	push	OPEN_EXISTING
	push	0
	push	FILE_SHARE_READ
	push	GENERIC_READ
	push	edx
	call	[CreateFile]
	cmp	eax,-1
	je	file_error
	mov	ebx,eax
	clc
	ret
    file_error:
	stc
	ret
	
create:
    ;redirecionando
	jmp gramado_create_fake
	
	push	0
	push	0
	push	CREATE_ALWAYS
	push	0
	push	FILE_SHARE_READ
	push	GENERIC_WRITE
	push	edx
	call	[CreateFile]
	cmp	eax,-1
	je	file_error
	mov	ebx,eax
	clc
	ret
	
write:
    ;redirecionando
	jmp gramado_write_fake
	
	push	0
	push	bytes_count
	push	ecx
	push	edx
	push	ebx
	call	[WriteFile]
	or	eax,eax
	jz	file_error
	clc
	ret
	
	
read:
    ;redirecionando 
	jmp gramado_read_fake
	
	mov	ebp,ecx
	push	0
	push	bytes_count
	push	ecx
	push	edx
	push	ebx
	call	[ReadFile]
	or	eax,eax
	jz	file_error
	cmp	ebp,[bytes_count]
	jne	file_error
	clc
	ret
	
	
close:
    ;redirecionando 
	jmp gramado_close_fake
	
	push	ebx
	call	[CloseHandle]
	ret
	
lseek:
    ;redirecionando
	jmp gramado_lseek_fake
	
	movzx	eax,al
	push	eax
	push	0
	push	edx
	push	ebx
	call	[SetFilePointer]
	cmp	eax,-1
	je	file_error
	clc
	ret

	
;;
;; Display string
;;	

display_string:
    ;chamando rotina na lib asm.inc
    call DisplayMessage
	ret
;preservando o código original
.original:
	push	[con_handle]
	call	[GetStdHandle]
	mov	ebp,eax
	mov	edi,esi
	or	ecx,-1
	xor	al,al
	repne	scasb
	neg	ecx
	sub	ecx,2
	push	0
	push	bytes_count
	push	ecx
	push	esi
	push	ebp
	call	[WriteFile]
	ret
	
display_character:
    call putchar 
	ret 
.original:	
	push	ebx
	mov	[character],dl
	push	[con_handle]
	call	[GetStdHandle]
	mov	ebx,eax
	push	0
	push	bytes_count
	push	1
	push	character
	push	ebx
	call	[WriteFile]
	pop	ebx
	ret
	
display_number:
    call print_hex
	ret 
	
.original:
	push	ebx
	mov	ecx,1000000000
	xor	edx,edx
	xor	bl,bl
      display_loop:
	div	ecx
	push	edx
	cmp	ecx,1
	je	display_digit
	or	bl,bl
	jnz	display_digit
	or	al,al
	jz	digit_ok
	not	bl
      display_digit:
	mov	dl,al
	add	dl,30h
	push	ecx
	call	display_character
	pop	ecx
      digit_ok:
	mov	eax,ecx
	xor	edx,edx
	mov	ecx,10
	div	ecx
	mov	ecx,eax
	pop	eax
	or	ecx,ecx
	jnz	display_loop
	pop	ebx
	ret
	
;;
;; ## display user messages ##
;;	

display_user_messages:
	
	mov	[displayed_count],0
	call	show_display_buffer
	
	cmp	[displayed_count],1
	jb	line_break_ok
	je	make_line_break
	
	mov	ax,word [last_displayed]
	cmp	ax,0A0Dh
	je	line_break_ok
	
	cmp	ax,0D0Ah
	je	line_break_ok
	
make_line_break:
	mov	word [buffer],0A0Dh
	push	[con_handle]
	call	[GetStdHandle]
	push	0
	push	bytes_count
	push	2
	push	buffer
	push	eax
	call	[WriteFile]
line_break_ok:
	ret

	
display_block:
	add	[displayed_count],ecx
	cmp	ecx,1
	ja	take_last_two_characters
	jb	block_displayed
	mov	al,[last_displayed+1]
	mov	ah,[esi]
	mov	word [last_displayed],ax
	jmp	block_ok
      take_last_two_characters:
	mov	ax,[esi+ecx-2]
	mov	word [last_displayed],ax
      block_ok:
	push	ecx
	push	[con_handle]
	call	[GetStdHandle]
	pop	ecx
	push	0
	push	bytes_count
	push	ecx
	push	esi
	push	eax
	call	[WriteFile]
block_displayed:
	ret
	
;;===========================================================
;; ## fatal error ##
;;	

fatal_error:
	
	mov esi, gramado_string_fatalerror
	call DisplayMessage
	
	;;#suspensa todo esse tratamento.
	;mov	[con_handle],STD_ERROR_HANDLE
	;mov	esi,error_prefix
	;call	display_string
	;pop	esi
	;call	display_string
	;mov	esi,error_suffix
	;call	display_string
	;mov	al,0FFh
	
	jmp	exit_program
	
	
;;===================================================
;; ## assembler error ##
;;	
	
assembler_error:

    ;;#suspensa.
	;;suspenderemos esse tratamentod e erro.
	
	jmp gramado_assembler_error
	jmp $
	
	;mov	[con_handle],STD_ERROR_HANDLE
	;call	display_user_messages
	;mov	ebx,[current_line]
	;test	ebx,ebx
	;jz	display_error_message
	;push	dword 0
    ;  get_error_lines:
	;mov	eax,[ebx]
	;cmp	byte [eax],0
	;je	get_next_error_line
	;push	ebx
	;test	byte [ebx+7],80h
	;jz	display_error_line
	;mov	edx,ebx
    ;  find_definition_origin:
	;mov	edx,[edx+12]
	;test	byte [edx+7],80h
	;jnz	find_definition_origin
	;push	edx
    ;  get_next_error_line:
	;mov	ebx,[ebx+8]
	;jmp	get_error_lines
    ;  display_error_line:
	;mov	esi,[ebx]
	;call	display_string
	;mov	esi,line_number_start
	;call	display_string
	;mov	eax,[ebx+4]
	;and	eax,7FFFFFFFh
	;call	display_number
	;mov	dl,']'
	;call	display_character
	;pop	esi
	;cmp	ebx,esi
	;je	line_number_ok
	;mov	dl,20h
	;call	display_character
	;push	esi
	;mov	esi,[esi]
	;movzx	ecx,byte [esi]
	;inc	esi
	;call	display_block
	;mov	esi,line_number_start
	;call	display_string
	;pop	esi
	;mov	eax,[esi+4]
	;and	eax,7FFFFFFFh
	;call	display_number
	;mov	dl,']'
	;call	display_character
    ;  line_number_ok:
	;mov	esi,line_data_start
	;call	display_string
	;mov	esi,ebx
	;mov	edx,[esi]
	;call	open
	;mov	al,2
	;xor	edx,edx
	;call	lseek
	;mov	edx,[esi+8]
	;sub	eax,edx
	;jz	line_data_displayed
	;push	eax
	;xor	al,al
	;call	lseek
	;mov	ecx,[esp]
	;mov	edx,[additional_memory]
	;lea	eax,[edx+ecx]
	;cmp	eax,[additional_memory_end]
	;ja	out_of_memory
	;call	read
	;call	close
	;pop	ecx
	;mov	esi,[additional_memory]
    ;  get_line_data:
	;mov	al,[esi]
	;cmp	al,0Ah
	;je	display_line_data
	;cmp	al,0Dh
	;je	display_line_data
	;cmp	al,1Ah
	;je	display_line_data
	;or	al,al
	;jz	display_line_data
	;inc	esi
	;loop	get_line_data
    ;  display_line_data:
	;mov	ecx,esi
	;mov	esi,[additional_memory]
	;sub	ecx,esi
	;call	display_block
    ;  line_data_displayed:
	;mov	esi,cr_lf
	;call	display_string
	;pop	ebx
	;or	ebx,ebx
	;jnz	display_error_line
	;cmp	[preprocessing_done],0
	;je	display_error_message
	;mov	esi,preprocessed_instruction_prefix
	;call	display_string
	;mov	esi,[current_line]
	;add	esi,16
	;mov	edi,[additional_memory]
	;xor	dl,dl
    ;  convert_instruction:
	;lodsb
	;cmp	al,1Ah
	;je	copy_symbol
	;cmp	al,22h
	;je	copy_symbol
	;cmp	al,3Bh
	;je	instruction_converted
	;stosb
	;or	al,al
	;jz	instruction_converted
	;xor	dl,dl
	;jmp	convert_instruction
    ;  copy_symbol:
	;or	dl,dl
	;jz	space_ok
	;mov	byte [edi],20h
	;inc	edi
    ;  space_ok:
	;cmp	al,22h
	;je	quoted
	;lodsb
	;movzx	ecx,al
	;rep	movsb
	;or	dl,-1
	;jmp	convert_instruction
    ;  quoted:
	;mov	al,27h
	;stosb
	;lodsd
	;mov	ecx,eax
	;jecxz	quoted_copied
    ;  copy_quoted:
	;lodsb
	;stosb
	;cmp	al,27h
	;jne	quote_ok
	;stosb
    ;  quote_ok:
	;loop	copy_quoted
    ;  quoted_copied:
	;mov	al,27h
	;stosb
	;or	dl,-1
	;jmp	convert_instruction
    ;  instruction_converted:
	;xor	al,al
	;stosb
	;mov	esi,[additional_memory]
	;call	display_string
	;mov	esi,cr_lf
	;call	display_string
    ;  display_error_message:
	;mov	esi,error_prefix
	;call	display_string
	;pop	esi
	;call	display_string
	;mov	esi,error_suffix
	;call	display_string
	;mov	al,2
	;jmp	exit_program

make_timestamp:
    ;;#suspensa
	ret
	
	;push	buffer
	;call	[GetSystemTime]
	;movzx	ecx,word [buffer]
	;mov	eax,ecx
	;sub	eax,1970
	;mov	ebx,365
	;mul	ebx
	;mov	ebp,eax
	;mov	eax,ecx
	;sub	eax,1969
	;shr	eax,2
	;add	ebp,eax
	;mov	eax,ecx
	;sub	eax,1901
	;mov	ebx,100
	;div	ebx
	;sub	ebp,eax
	;mov	eax,ecx
	;xor	edx,edx
	;sub	eax,1601
	;mov	ebx,400
	;div	ebx
	;add	ebp,eax
	;movzx	ecx,word [buffer+2]
	;mov	eax,ecx
	;dec	eax
	;mov	ebx,30
	;mul	ebx
	;add	ebp,eax
	;cmp	ecx,8
	;jbe	months_correction
	;mov	eax,ecx
	;sub	eax,7
	;shr	eax,1
	;add	ebp,eax
	;mov	ecx,8
    ;  months_correction:
	;mov	eax,ecx
	;shr	eax,1
	;add	ebp,eax
	;cmp	ecx,2
	;jbe	day_correction_ok
	;sub	ebp,2
	;movzx	ecx,word [buffer]
	;test	ecx,11b
	;jnz	day_correction_ok
	;xor	edx,edx
	;mov	eax,ecx
	;mov	ebx,100
	;div	ebx
	;or	edx,edx
	;jnz	day_correction
	;mov	eax,ecx
	;mov	ebx,400
	;div	ebx
	;or	edx,edx
	;jnz	day_correction_ok
    ;  day_correction:
	;inc	ebp
    ;  day_correction_ok:
	;movzx	eax,word [buffer+6]
	;dec	eax
	;add	eax,ebp
	;mov	ebx,24
	;mul	ebx
	;movzx	ecx,word [buffer+8]
	;add	eax,ecx
	;mov	ebx,60
	;mul	ebx
	;movzx	ecx,word [buffer+10]
	;add	eax,ecx
	;mov	ebx,60
	;mul	ebx
	;movzx	ecx,word [buffer+12]
	;add	eax,ecx
	;adc	edx,0
	;ret

error_prefix db 'error: ',0
error_suffix db '.'
cr_lf db 0Dh,0Ah,0
line_number_start db ' [',0
line_data_start db ':',0Dh,0Ah,0
preprocessed_instruction_prefix db 'processed: ',0
