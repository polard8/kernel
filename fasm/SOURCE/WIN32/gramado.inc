
 ; gramado.inc 
 ; Usado para portar fasm para gramado 0.4 
 
    
	gramado_command_line: db 'fasm test.asm test.exe'
 
    
	;Funções do windows chamada pelo fasm. 
 
    gramado_ExitProcess:
        ret 
		
    gramado_CreateFile:
        ret 
		
    gramado_ReadFile:
        ret 
		
    gramado_WriteFile:
        ret 
		
    gramado_CloseHandle:
        ret 
		
    gramado_SetFilePointer:
        ret 
		
	;;#todo
	;;estamos usando o endereço fake, mas já temos um endereço 
    ;;no qual o shell passa a command line para o aplicativo.	
    gramado_GetCommandLine:
	    mov eax, gramado_command_line
        ret
		
    gramado_GetEnvironmentVariable:
        ret 
		
    gramado_GetStdHandle:
        ret 

;;alocando memoria virtual.
;;Reserves, commits, or changes the state of a region of pages 
;;in the virtual address space of the calling process. 
;;Memory allocated by this function is automatically initialized to zero.	
;; LPVOID lpAddress,
;; SIZE_T dwSize,
;; DWORD  flAllocationType,
;; DWORD  flProtect	
gramado_VirtualAlloc:

    ret 
		 
    gramado_VirtualFree:
        ret 
		
    gramado_GetTickCount:
        ret 
		
    gramado_GetSystemTime:
        ret 


    ;;Isso pega informações sobre a memória e coloca no buffer 
	;;cujo ponteiro está na pilha.
    ;DWORD  dwLength;
    ;DWORD  dwMemoryLoad;
    ;SIZE_T dwTotalPhys;
    ;SIZE_T dwAvailPhys;
    ;SIZE_T dwTotalPageFile;
    ;SIZE_T dwAvailPageFile;
    ;SIZE_T dwTotalVirtual;
    ;SIZE_T dwAvailVirtual;			
gramado_GlobalMemoryStatus:
    pop eax ;;pega o ponteiro para o buffer
    
	;;vamos usar ebp para manipular o buffer.
	mov ebp, eax	
	
	mov [ebp +0],0
	mov [ebp +4],0
	mov [ebp +8],0
	mov [ebp +12],0
	mov [ebp +16],0
	mov [ebp +20],0
	mov [ebp +24],0
	ret	
 

gramado_create_fake:
	mov esi, gramado_string_create_fake
	call DisplayMessage
    ret

gramado_open_fake:
	mov esi, gramado_string_open_fake
	call DisplayMessage
    ret
	
gramado_close_fake:
	mov esi, gramado_string_close_fake
	call DisplayMessage
    ret

gramado_read_fake:
	mov esi, gramado_string_read_fake
	call DisplayMessage
    ret

gramado_write_fake:
	mov esi, gramado_string_write_fake
	call DisplayMessage
    ret
	
gramado_lseek_fake:
	mov esi, gramado_string_lseek_fake
	call DisplayMessage
    ret


gramado_init_memory_fake:
	
	mov esi, gramado_string_initmemory
	call DisplayMessage

    ret
	
	
gramado_assembler_error:
	mov esi, gramado_string_assembler_error
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

gramado_string_fim_do_programa db '*FIM DO PROGRAMA! :)',0Dh,0Ah,0


gramado_string_create_fake: db 'create_fake', 0Dh, 0Ah,0
gramado_string_read_fake: db 'read_fake', 0Dh, 0Ah,0
gramado_string_write_fake: db 'write_fake', 0Dh, 0Ah,0
gramado_string_open_fake: db 'open_fake', 0Dh, 0Ah,0
gramado_string_close_fake: db 'close_fake', 0Dh, 0Ah,0
gramado_string_lseek_fake: db 'lseek_fake', 0Dh, 0Ah,0

gramado_string_out_of_memory: db 'out_of_memory', 0Dh, 0Ah,0



gramado_string_error_with_source: db 'error_with_source', 0Dh, 0Ah,0
gramado_string_assembler_error: db 'assembler error', 0Dh, 0Ah,0
gramado_string_fatalerror: db 'fatal error', 0Dh, 0Ah,0
gramado_string_hang: db '*HANG', 0Dh, 0Ah,0
gramado_string_breakpoint: db '*BREAKPOINT', 0Dh, 0Ah,0


;;======================
;; mensagens do preprocessador
;gramado_string_preprocessor_init db 'Initializing preprocessor ...', 0Dh, 0Ah,0
;gramado_string_preprocessor_done db 'preprocessor done', 0Dh, 0Ah,0

gramado_string_preprocessor_characteres db 'preprocessor characteres', 0Dh, 0Ah,0
gramado_string_preprocessor_locals_counter db 'preprocessor locals_counter', 0Dh, 0Ah,0
gramado_string_preprocessor_environment_variable_support db 'preprocessor environment_variable_support', 0Dh, 0Ah,0



gramado_string_preprocessor_openfound db 'preprocessor openfound *hang', 0Dh, 0Ah,0
gramado_string_preprocessor_lseekfound db 'preprocessor lseekfound *hang', 0Dh, 0Ah,0

;;======================
;; mensagens do parser
;gramado_string_parser_init db 'Initializing parser ...', 0Dh, 0Ah,0
;gramado_string_parser_done db 'parser done', 0Dh, 0Ah,0

;;======================
;; mensagens do assembler

;gramado_string_assembler_init db 'Initializing assembler ...', 0Dh, 0Ah,0
;gramado_string_assembler_done db 'assembler done', 0Dh, 0Ah,0



;;...




;;
;; ===================================================================================
;;                                #### BUFFER  ####
;; ===================================================================================
;;

;; BUFFER PARA EVITARMOS ALOCAÇÃO POR ENQUANTO. 


BUFFER1:
    ;;8KB
    times 4096 DB 0  
	times 4096 DB 0  
BUFFER1_END:
    DB 0
	
BUFFER2:
    ;;8KB
    times 4096 DB 0  
	times 4096 DB 0  
BUFFER2_END:
    DB 0

BUFFER3:
    ;;4KB
    ;times 4096 DB 0  
BUFFER3_END:
    DB 0
	
BUFFER4:
    ;;4KB
    ;times 4096 DB 0  
BUFFER4_END:
    DB 0
	
	
	
	


