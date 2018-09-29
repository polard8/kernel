;; crt0.asm
;; Ponto de entrada do aplicativo teditor.bin
;; deve apenas chamar _mainGetMessage para 
;; enviar as mensagens que estão na pilha.
;;


[bits 32]


extern _mainGetMessage
;;extern _mainTextEditor


global __crt0Main
__crt0Main:

	call _mainGetMessage
	;call _mainTextEditor
	
hang:
    pause
    jmp hang


