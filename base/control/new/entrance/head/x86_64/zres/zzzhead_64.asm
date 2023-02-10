;;
;; File: 1pump/arch/x86/pumpcore/head_64.asm
;;
;; The entry point of the base kernel for the x86_64 arch.
;; This documment will includo some other files.
;;
;; 2021 - Created by Fred Nora.
;;      - ported from the 32bit version
;;


; See: 
; kernel/include/land/

%include "land/head.inc"

;
; Segmento .head_x86_64:
;     Parte inicial do kernel. 
;     Esse marcador precisa ficar no começo do arquivo.
;

; segment .head_x86_64
__HEAD

[bits 64]


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
;;     Boot x86_64 entry point.
;;     The kernel starts here for x86_64 arch.
;;

global _kernel_begin 
_kernel_begin:

; #bugbug
; Porque estamos usando um jmp, sem nem mesmo configurarmos
; os registradores de segmento. Estamos confiando na configuração
; feita pelo BL.BIN.
; Bom mesmos seria começarmos com a configuração da gdt e dos 
; registradores de segmento.
; #todo
; Precismos carregar a gdt o mais rápido possível.


.Lheadhang:
    cli
    hlt
    JMP .Lheadhang

    ; #todo
    ; Ainda não sei se é possivel realizar esse salto.
    ; Então vamos parar por aqui.

    JMP START

align 4


;; =============================================================
mboot_start:

    ;   +-------------------+
    ;0  | magic: 0x1BADB002 |	(required)
    ;4  | flags             |	(required)
    ;8  | checksum          |	(required)
    ;   +-------------------+
    ;8  | header_addr       |	(present if flags[16] is set)
    ;12 | load_addr         |	(present if flags[16] is set)
    ;16 | load_end_addr     |	(present if flags[16] is set)
    ;20 | bss_end_addr      |	(present if flags[16] is set)
    ;24 | entry_addr        |	(present if flags[16] is set)
    ;   +-------------------+

    dd  MULTIBOOT_MAGIC
    dd  multiboot_flags
    dd  multiboot_checksum

; fields used if MULTIBOOT_AOUT_KLUDGE is set in 
; MULTIBOOT_HEADER_FLAGS

; for MULTIBOOT_MEMORY_INFO
    dd  0x00000000    ;; header_addr   - mboot_start    ; these are PHYSICAL addresses
    dd  0x00000000    ;; load_addr     - _code_begin    ; start of kernel .text (code) section
    dd  0x00000000    ;; load_end_addr - _data_end      ; end of kernel .data section
    dd  0x00000000    ;; bss_end_addr  - _bss_end       ; end of kernel BSS
    dd  0x00000000    ;; entry_addr    - _kernel_begin  ; kernel entry point (initial EIP)

; for MULTIBOOT_VIDEO_MODE
    dd  0x00000000    ;; mode_type 
    dd  800           ;; width 
    dd  600           ;; height 
    dd  24            ;; depth 


mboot_end:
;; =============================================================

align 4

    %include "head/header.inc"
    ;; ...

; Restart the boot routine.
START:

    cld
    cli

; IN: 
; al = 'G' (Graphic Mode).
; al = 'T' (Text Mode).
; ebx = LFB.
; ecx = BootBlock pointer.
; edx = BootBlock pointer.
; ebp = BootBlock pointer.
; #importante
; AL e EBX foram configurados pelo BL.BIN ??
; See: head.asm

    ;call head_init
    jmp head_init

    ; Not reached 

not_reached_loop:
    cli
    hlt
    jmp not_reached_loop



; Includes:
; ========
; Esses includes são padronizados. Não acrescentar outros.


; Inicialização.
; Funções de apoio à inicialização do Kernel 32bit.

    %include "head/head.asm" 
    %include "head/headlib.asm" 

; Interrupções de hardware (irqs) e faults.

    %include "hw/hw.asm"
    %include "hw/hwlib.asm"

; Interrupções de software.

    %include "sw/sw.asm"
    %include "sw/swlib.asm"


;=================================================================
; DATA: 
;     Início do Segmento de dados.
;     Coloca uma assinatura no todo.

segment .data
global _data_start
_data_start:
    db 0x55
    db 0xAA


;=================================================================
; BSS:
;     Início do segmento BSS.
;     Coloca uma assinatura no todo.
;     Mas normalmente limpamos essa área.

segment .bss
global _bss_start
_bss_start:
    ;db 0x55
    ;db 0xAA



;
; End
;



