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
	
global malloc
malloc:
    ret 
	
global free
free:
    ret 
	
global getenv
getenv:
    ret 
	
global fopen
fopen:
    ret 
	
global fclose
fclose:
    ret 
	
global fread
fread:
    ret 
	
global fwrite
fwrite:
    ret 
	
global fseek
fseek: 
    ret
	
global ftell
ftell:
    ret 
	
global time
time:
    ret 
	
global exit
exit:
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
	
	pop eax 
	pop eax 
	pop eax
	
	;isso funcionou.
	;call _testWrite
    ret
	
global _xxxmsg	
_xxxmsg: 
    db "message", 0

	
global gettimeofday
gettimeofday:
    ret	



