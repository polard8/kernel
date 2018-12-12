;;
;; File: crt0.asm
;;
;; Entry point.
;;

[bits 32]


extern _gramc_main

extern fasm_main 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; __crt0Main:
;;     Entry point.
;;
global __crt0Main
__crt0Main:

    call fasm_main
	
    ;main.c
	call _gramc_main
	
hang:
    pause
    jmp hang
	
	
;;
;; ## as chamada daqui pra baixo vem do fasm ligado como objeto ##
;;	
extern _malloc	
global malloc
malloc:
    ;ecx 
	push ecx
	call _malloc
	;;eax, retorna o endereço virtual.
	pop ecx
    ret 
	
global free
free:
    ret 
	
extern _getenv	
global getenv
getenv:
    push esi
    call _getenv 
	;retorno em eax.
	pop edx
    ret 
	
	
extern _fopen	
global fopen
fopen:
    ;;#todo FALTA PEGAR O ARGUMENTO.
    call _fopen
	ret 
	
	
extern _fclose	
global fclose
fclose:
    push ebx
    call _fclose
    pop ebx
	ret 
	
	
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
	
	
extern _ftell	
global ftell
ftell:
    push ebx
	call _ftell
	;retorn em eax
	pop ebx
	ret 
	
	
;extern _time	
global time
time:
    ;call _time
    ret 
	
extern _exit	
global exit
exit:

    ;;isso provavelmente não retorne.
    push eax 
	call _exit
	pop eax
    ret

;;#bugbug esse é diferente
extern _write
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
	call _write
	
	pop ebx 
	pop ebx 
	pop ebx
	
	;isso funcionou.
	;call _testWrite
    ret
	


	
;extern _gettimeofday	
global gettimeofday
gettimeofday:
    ;call _gettimeofday
    ret	
	
	
	
global _xxxmsg	
_xxxmsg: 
    db "message", 0



