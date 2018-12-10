;; crt0.asm
;; Ponto de entrada do aplicativo teditor.bin
;; deve apenas chamar _mainGetMessage para 
;; enviar as mensagens que estão na pilha.
;;


[bits 32]


extern _gramtext_main


global __crt0Main
__crt0Main:

	call _gramtext_main
	
hang:
    pause
    jmp hang


