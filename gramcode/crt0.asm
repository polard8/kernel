;; crt0.asm
;; Ponto de entrada do aplicativo teditor.bin
;; deve apenas chamar _mainGetMessage para 
;; enviar as mensagens que estão na pilha.
;;


[bits 32]


extern _gramcode_main


global __crt0Main
__crt0Main:

	call _gramcode_main
	
hang:
    pause
    jmp hang


