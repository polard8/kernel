;;
;; File: crt0.asm
;;
;; Entry point of the fasm.bin for gramado 0.4
;;

[bits 32]


;;está em main.c.
extern _fasm_main 


;;está em FASM.ASM
extern asm_fasm_start

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; __crt0Main:
;;     Entry point.
;;
global __crt0Main
__crt0Main:

    
	;; devemos chamar o assembler depois de termos 
	;; chamado o código em C, que inicializará a 'runtime', pegará a linha de comando,
	;; providenciará todos os arquivos e buffers necessários e passará tudo 
	;; para o assembler.
	
	
   ;;
   ;; ## chamando C ##
   ;;   

	
	;;main.c
    call _fasm_main


    ;;
    ;; ## chamando ASM ##
    ;;   
	
	;;FASM.ASM
	call asm_fasm_start
	

	
hang:
    pause
    jmp hang
	
	
;;=========================================================================
;; ## as chamada daqui pra baixo vem do fasm ligado como objeto ##
;;


;;===================================================
;;isso funciona.	
extern _fasm_malloc	;;main.c
global malloc
malloc:
    ;ecx 
	push ecx
	call _fasm_malloc
	;;eax, retorna o endereço virtual.
	pop ecx
    ret 
	
global free
free:
    ret 
	

;;===================================================	
extern _getenv	
global getenv
getenv:
    push esi
    call _getenv 
	;retorno em eax.
	pop edx
    ret 
	

;;===================================================	
extern _fasm_fopen	;;main.c
extern _fopen	
global fopen
fopen:
    ;;#todo FALTA PEGAR O ARGUMENTO.
	mov ebp, esp
	
	;mov ebx, dword [ebp+0]
	mov ecx, dword [ebp+4]
	mov edx, dword [ebp+8]
	
	;push ebx 
	;push ecx 
	;push edx
	
	push edx 
	push ecx
	
	call _fasm_fopen  ;;especial usado para checar os argumentos.
    ;call _fopen
	
	;eax é o retorno.
	
	pop ecx 
	pop edx
	
	;pop edx
	;pop ecx 
	;pop ebx
	
	ret 
	

;;===================================================	
extern _fclose	
global fclose
fclose:
    push ebx
    call _fclose
    pop ebx
	ret 
	

;;===================================================	
;extern _fread	
global fread
fread:
    
	push edx
	push ecx
	push 1
	push ebx
	
	;call _fread
	
	pop edx
	pop edx
	pop edx
	pop edx
    ret 
	

;;===================================================	
;extern _fwrite	
global fwrite
fwrite:
	push edx
	push ecx
	push 1
	push ebx
	
	;call _fwrite
	
	pop edx
	pop edx
	pop edx
	pop edx
    ret 

	
;;===================================================	
extern _fseek	
global fseek
fseek: 
    push ebx 
	push edx 
	push eax
    call _fseek
	;;retorno em eax.
    pop edx
	pop edx
	pop edx
	ret
	

;;===================================================	
extern _ftell	
global ftell
ftell:
    push ebx
	call _ftell
	;retorn em eax
	pop ebx
	ret 
	

;;===================================================	
;extern _time	
global time
time:
    ;call _time
    ret 


;;===================================================	
extern _exit	
extern _fasm_exit	
global exit
exit:

    ;;isso provavelmente não retorne.
    push eax 
	call _fasm_exit
	;call _exit
	pop eax
    ret

	
;;===================================================	
;;#importante: isso funciona.	
;;#bugbug esse é diferente
extern _fasm_write
extern _testWrite
global write
write:
    
	; fd, buffer, count
 
    ;;test
    ;mov ebp, esp
 
    mov ecx, 1;dword [ebp+0]
	;mov ecx, 8
	push ecx
	
	xor ebx, ebx 
	mov byte [_xxxmsg], dl 
	;mov ebx, dword [ebp+4]
	mov ebx, _xxxmsg
	push ebx 
	
	;mov eax, dword [ebp+8]
	xor eax, eax 
	push eax 

	
	; fd, buffer, count
	call _fasm_write
	
	pop ebx 
	pop ebx 
	pop ebx
	
	;isso funcionou.
	;call _testWrite
    ret
	


;;===================================================	
;extern _gettimeofday	
global gettimeofday
gettimeofday:
    ;call _gettimeofday
    ret	
	
	
	
;;===================================================	
global _xxxmsg	
_xxxmsg: 
    db "message", 0



