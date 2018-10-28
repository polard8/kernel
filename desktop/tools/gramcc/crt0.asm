;;
;; File: crt0.asm
;;
;; Entry point.
;; Deve apenas chamar _mainGetMessage que prepara os argumentos para main.
;; @todo: Criar o crt0 em C e implementar o exit.
;;

[bits 32]

extern _mainGetMessage


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; __crt0Main:
;;     Entry point.
;;
global __crt0Main
__crt0Main:

    ;main.c
	call _mainGetMessage
	
hang:
    pause
    jmp hang


