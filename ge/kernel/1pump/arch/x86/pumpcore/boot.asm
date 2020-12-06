;; File: hwi/init/x86/boot.asm
;; 
;; para dar suporte ao multiboot.
;; Esse será o primeiro ponto de entrada do kernel para x86
;; Ele será simples e pequeno, dando uma visão geral
;; de todas as áreas do kernel. (code,data,stack)


; Ordem padrão dos arquivos em assembly:
; ======================================
; (0) boot.asm
; (1) head.asm
; (2) headlib.asm
; (3) hw.asm
; (4) hwlib.asm
; (5) sw.asm
; (6) swlib.asm
; Obs: Essa é uma ordem padrão, nunca mudar, nunca excluir arquivos, 
;      nunca incluir outros arquivos.



;
; Segmento .head_x86:
;     Parte inicial do kernel. 
;     Esse marcador precisa ficar no começo do arquivo.
;
segment .head_x86

[bits 32]

    ; Imports.
    extern _code_begin
    extern _data_end
    extern _bss_end


    ; Multiboot support.
    MULTIBOOT_MAGIC        equ  0x1badb002
    MULTIBOOT_PAGE_ALIGN   equ  0x1
    MULTIBOOT_MEMORY_INFO  equ  0x2
    MULTIBOOT_VIDEO_MODE   equ  0x4
    multiboot_flags        equ  MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_VIDEO_MODE
    multiboot_checksum     equ  -(MULTIBOOT_MAGIC + multiboot_flags)


;;==================================
;; _kernel_begin:
;;     The kernel starts here for x86 arch.
;;

global _kernel_begin              
_kernel_begin:

    JMP START

align 4


;; =============================================================
mboot_start:

    ;	+-------------------+
    ;0	| magic: 0x1BADB002 |	(required)
    ;4	| flags		        |	(required)
    ;8	| checksum	        |	(required)
    ;	+-------------------+
    ;8	| header_addr	    |	(present if flags[16] is set)
    ;12	| load_addr	        |	(present if flags[16] is set)
    ;16	| load_end_addr	    |	(present if flags[16] is set)
    ;20	| bss_end_addr	    |	(present if flags[16] is set)
    ;24	| entry_addr	    |	(present if flags[16] is set)
    ;	+-------------------+


    dd  MULTIBOOT_MAGIC
    dd  multiboot_flags
    dd  multiboot_checksum

    ; fields used if MULTIBOOT_AOUT_KLUDGE is set in 
    ; MULTIBOOT_HEADER_FLAGS

    ;; for MULTIBOOT_MEMORY_INFO
    dd  0x00000000    ;; header_addr   - mboot_start    ; these are PHYSICAL addresses
    dd  0x00000000    ;; load_addr     - _code_begin    ; start of kernel .text (code) section
    dd  0x00000000    ;; load_end_addr - _data_end      ; end of kernel .data section
    dd  0x00000000    ;; bss_end_addr  - _bss_end       ; end of kernel BSS
    dd  0x00000000    ;; entry_addr    - _kernel_begin  ; kernel entry point (initial EIP)

    ;; for MULTIBOOT_VIDEO_MODE
    dd  0x00000000    ;; mode_type 
    dd  800           ;; width 
    dd  600           ;; height 
    dd  24            ;; depth 


mboot_end:
;; =============================================================

align 4

    %include "bootmx/header.inc"
    ;; ...

; Restart the boot routine.
START:

    ; #test: Clean flags.
    
    ;push dword 0
    ;popfd 

    cli
    cld

    ; IN: 
    ; al = 'G' (Graphic Mode).
    ; al = 'T' (Text Mode).
    ; ebx = LFB.
    ; ecx = BootBlock pointer.
    ; edx = BootBlock pointer.
    ; ebp = BootBlock pointer.
    ; #importante
    ; AL e EBX foram configurados pelo BL.BIN ??

    call head_init
    cli

loop:
    hlt
    jmp loop


;
; Includes:
; ========
; Esses includes são padronizados. Não acrescentar outros.
;

    ;Inicialização.
    ;Funções de apoio à inicialização do Kernel 32bit.
    %include "bootmx/head.asm" 
    %include "bootmx/headlib.asm" 

    ;Interrupções de hardware (irqs) e faults.
    %include "iomx/hw.asm"
    %include "iomx/hwlib.asm"

    ;Interrupções de software.
    %include "appmx/sw.asm"
    %include "appmx/swlib.asm"


; DATA: 
;     Início do Segmento de dados.
;     Coloca uma assinatura no todo.

segment .data
global _data_start
_data_start:
    db 0x55    ;data magic.
    db 0xAA    ;data magic.


; BSS:
;     Início do segmento BSS.
;     Coloca uma assinatura no todo.
;     Mas normalmente limpamos essa área.
segment .bss
global _bss_start
_bss_start:
    ;db 0x55    ;data magic.
    ;db 0xAA    ;data magic.



;
; End
;



