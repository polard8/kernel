;
; File: head.s 
;
; Gramado Boot Loader - a Boot Loader entry point for x86 processors.
; It's a 32bit, kernel mode, system aplication used to load the 
; kernel and some other files.
;
; Descriçao:
; Esse arquivo � o entrypoint do Boot Loader. (BL.BIN).
; Parte inicial do n�cleo do Boot Loader para a arquitetura x86 de 32bit 
; para desktops.
; Startup module for the 32bit Boot Loader of a 32bit OS for desktops.
;
; Localiza��o:
; O Boot Loader � carregado em 0x00020000 com o entry point em 0x00021000.
;
; Atribui��es:   
;    + Inicializar a arquitetura x86. 
;    + Chamar c�digo em C para carregar o kernel.
;    + Passar o comando para o kernel.
;
; ATEN��O:
; Logo abaixo, no fim desse arquivo, est�o GDT, IDT e includes.
;
; History:
;     2015 - Created by Fred Nora.
;     2021 - Creating a 64bit boot loader.


; #todo:
; bl.bin é feito em 32bit e ainda em 32bit ele deve carregar
; o kernel que é um programa de 64bit. 
;  Ao fim de sua rotina em C 32bit ele faz as configurações
;  necessarias para entrar em 64bit. Poderá usar rotinas
; em assembly 64bit. 
; E por fim salta para o kernel de 64bit.


; Segmento onde inicia a parte em Assembly.
segment .head_x86
[bits 32]


;; See: gdef.h
extern ___last_valid_address 



; Vari�veis importadas.



; LFB - Linear Frame Buffer
; physical address.

extern _g_lbf_pa




;
; Imported
;

extern _OS_Loader_Main                ; * Entrada da parte em C.
extern _BlKernelModuleMain    ; * Reentrada do bl, agora na forma de m�dulo.
;extern _shell_main    ;Entrada do Shell do Boot Loader.

;...



; Image address:
; Physical address.

KRN_BASE        equ  0x00100000  ; Image base. 1MB mark.
KRN_ENTRYPOINT  equ  0x00101000  ; Entry point



; Directory and page table.
;PAGE_DIR_ADDRESS        equ     ??
;PAGE_TABLE_ADDRESS      equ     ??


;---------------------------------------------
; _OS_Loader_Entry_Point:
; 
;     Entry point do Boot Loader.
;
; IN:  al = 'G' (Graphic); 'T' (Text).
;      ebx = LFB address.
;      edx = Boot Block.
;
;++

; IN:
; al:  Boot mode.
; ebx: LFB physical addres.
; ecx: Boot block address.
; edx: Boot block address.
; ebp: Boot block address.
; edi: Gramado mode. (jail, p1, home ...)

global _OS_Loader_Entry_Point
_OS_Loader_Entry_Point:

   JMP StartLoader

    %include "header.inc"

StartLoader:

    ; #debug.
    ; text mode.

    mov byte [0xb8000], byte "B"
    mov byte [0xb8001], byte 9
    mov byte [0xb8002], byte "L"
    mov byte [0xb8003], byte 9

    ;Debug.
    ;JMP $

    ; Salva o modo de vídeo.
    mov byte [bl_video_mode], al

    ; Verifica se usa gui ou n�o.
    cmp al, byte 'G'
    je .useGUI
.dontuseGUI:
    mov dword [_SavedBootMode], 0    ;Text Mode flag.
    jmp .go 
.useGUI:
    mov dword [_SavedBootMode], 1    ;GUI flag.
.go:
	;Salva o LFB.
	;Global para endere�o f�sico do LFB.
    mov dword [_g_lbf_pa], ebx    

   ; @todo: 
   ;     Passar o bootblock em ebx e a flag em al.

    mov byte [bl_video_mode], al
    mov dword [_g_lbf_pa], ebx         ;Endere�o f�sico do LFB.



;
; == Boot Block ========================================
;

    ; BootBlock pointer.
    ; Ponteiro para o bootblock passado pelo boot manager.
    ; #todo
    ; We need to use this address to setup the base of the
    ; boot block strucure used in this BL.
    
    mov dword [_SavedBootBlock], edx 


    ; Gramado mode. (jail, p1, home ...)
    mov dword [_SavedGramadoMode], edi 


;++
; ===============================================

    ; Boot block starts at 0x00090000

    ; LFB_VA:        0x00090000 + 0
    ; WIDTH:         0x00090000 + 8
    ; HEIGHT:        0x00090000 + 16
    ; BPP:           0x00090000 + 24
    ; LAST_VALID:    0x00090000 + 32
    ; GRAMADO MODE:  0x00090000 + 40


;
; LFB_PA, X, Y, BPP
;

    ; 0x00090000 + 0
    xor eax, eax
    mov eax, dword [edx +0] 
    mov dword [_SavedLFB], eax
    mov dword [0x90000], eax
    mov dword [0x90000 + 4], 0

    ; 0x00090000 + 8
    xor eax, eax
    mov ax, word [edx +4] 
    mov dword [_SavedX], eax
    mov dword [0x90000 + 8], eax
    mov dword [0x90000 + 12], 0

    ; 0x00090000 + 16
    xor eax, eax
    mov ax, word [edx +8] 
    mov dword [_SavedY], eax
    mov dword [0x90000 + 16], eax
    mov dword [0x90000 + 20], 0

    ; 0x00090000 + 24
    xor eax, eax
    mov al, byte [edx +12] 
    mov dword [_SavedBPP], eax
    mov dword [0x90000 + 24], eax
    mov dword [0x90000 + 28], 0

    ; 0x00090000 + 32
    ; last valid
    ; See:

    ; 0x00090000 + 40
    xor eax, eax
    mov eax, dword [_SavedGramadoMode]  ;jail, p1, home ... 
    mov dword [0x90000 + 40], eax
    mov dword [0x90000 + 48], 0


; ===============================================
;--


	; #todo: 
	; Pode-se zerar os registradores nesse momento ?


	;Configura IDT. 
	;Aponta tudo para 'unhandled_int'.
	;Configura vetores de faults e exception.
	;Outros vetores.

    cli 
    call setup_idt 
    call setup_faults 
    call setup_vectors 

	;Carrega GDT e IDT.
	
	lgdt [GDT_register]
	lidt [IDT_register]
	
	; Setup registers.
	
	mov ax, DATA_SEL 
	mov ds, ax
	mov es, ax 
	;mov ax, NULL_SEL
	;mov fs, ax
	;mov gs, ax 
	mov ss, ax
	mov eax, _bootloader_stack_start 
	mov esp, eax 


	;PIC.
	cli
	mov al, 00010001b    ;Begin PIC 1 initialization.
	out 0x20, al
	IODELAY
	mov al, 00010001b    ;Begin PIC 2 initialization.
	out 0xA0, al	
	IODELAY
	mov al, 0x20		 ;IRQ 0-7: interrupts 20h-27h.
	out 0x21, al
	IODELAY
	mov al, 0x28		 ;IRQ 8-15: interrupts 28h-2Fh.
	out 0xA1, al
	IODELAY
	mov al, 4
	out 0x21, al
	IODELAY
	mov al, 2
	out 0xA1, al
	IODELAY
	mov al, 1
	out 0x21, al
	IODELAY
	out 0xA1, al
	IODELAY
	cli
	
	;unmask all interrupts

    mov al, 0
    out 0xa1, al 
    IODELAY
    out 0x21, al 
    IODELAY
    

;
; PIT
;

	;; PIT
	;; #importante
	;; Vamos deixar o kernel inicializar o PIT.

;
;  Call C part.
;

    ; Calling C part of the kernel base.
    ; See: main.c

    jmp _OS_Loader_Main


;
; == Go to kernel ================================
;

; O C salta para cá.
; See: pages.c

global _go_to_kernel
_go_to_kernel:

; Flush

    mov EAX, CR3  
    ; nop
    mov CR3, EAX


;
; cr0
;

; Enable paging to activate long mode
; Enable paging and protected mode.
; The paging was NOT enabled in pages.c

    mov ebx, cr0
    or ebx,0x80000001 
    mov cr0, ebx 


;
; GDT
;

; Load the 64-bit global descriptor table.

    lgdt [GDT64.Pointer]

    ; Maybe we are still in compatibility mode,
    ; so, this way we can setup DS, ES and SS.

    ; #todo: Rever isso.
    ; Os modos de operação são determinados via CS.L e CS.D
    ; Modo 64-bit = CS.L = 1 e CS.D = 0
    ; Modo compatibilidade 32-bit CS.L = 0 e CS.D = 1
    ; Modo compatibilidade 16-bit CS.L = CS.D = 0

    xor eax, eax
    mov ax, 0x10    ;GDT64.Data
    mov ds, ax
    mov es, ax


;
; Go!
;

; IN:
; Temos um bootblock em 0x00090000.
; Temos também outro boot block em [] 
; que não foi devidamente observado.

; #todo: 
; Vamos precisa passar o 'Gramado mode',
; muita coisa no sistema depende disso.


    ; Isso funciona na maq real.
    ;xor eax, eax
    ;xor ebx, ebx
    ;xor ecx, ecx
    mov edx, dword 1234

    ; Jump to the 64bit code in KERNEL.BIN.
    ; It will change the game and we will enter in 64bit long mode.

    jmp GDT64.Code:0x30001000

; Hang

bl_Loop:
    cli
    hlt
    jmp bl_Loop


;;
;; ===============================================================
;;

align 8

;; See:
;; https://wiki.osdev.org/Setting_Up_Long_Mode
GDT64:                           ; Global Descriptor Table (64-bit).
.Null: equ $ - GDT64         ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
.Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
.Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
.Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.


;; ==================================================

align 8


;========================================================
; BL_BootBlock:
;     
;     Not used, i guess
;
;     Bloco de configura��o de inicializa��o.
;     LFB address.

;; #bugbug
;; isso tem que ser igual ao do BM.BIN
;; Essa tabela é a que é mandada para o kernel.

;; ok ta igual ao do bm.

BL_BootBlock:
    .lfb: dd 0                   ;  0 - LFB address.
    .x:   dd 0                   ;  4 - Width in pixels.
    .y:   dd 0                   ;  8 - Height in pixel.
    .bpp: dd 0                   ; 12 - bpp address.
    .last_valid_address: dd 0    ; 16 - last valid ram address when finding mem size.
    .metafile_address:   dd 0    ;; 20
    .disk_number: dd 0           ;; 24
    .heads: dd 0                 ;; 28
    .spt: dd 0                   ;; 32
    .cylinders: dd 0             ;; 36 
    .boot_mode:  dd 0            ;; 40
    .gramado_mode dd 0           ;; 44
    
    
    


;Continua...




;;
;; Salvando alguns valores.
;;
	
;----------------------------------------
; _SavedBootBlock:
;     Salvando os argumentos passados pelo Boot Manager em 
;     vari�veis globais.
;	
global _SavedBootBlock
_SavedBootBlock:  
    dd 0
global _SavedLFB
_SavedLFB:  
    dd 0
global _SavedX
_SavedX:  
    dd 0
global _SavedY
_SavedY:  
    dd 0
global _SavedBPP
_SavedBPP:  
    dd 0	
global _SavedBootMode    ;;1=GUI; 0=Text Mode.
_SavedBootMode:
    dd 0
global _SavedGramadoMode   ; jail, p1, home ...
_SavedGramadoMode:  
    dd 0





;
; gdt ----------------------------
;


gdt:

; Nulo.
NULL_SEL equ $-gdt
    dd 0
    dd 0

; Segmento de c�digo.
CODE_SEL equ $-gdt
    dw 0xFFFF
    dw 0
    db 0 
    db 0x9A    ; present, ring0, code, non-confirming, readble.
    db 0xCF
    db 0

; Segmento de dados.
DATA_SEL equ $-gdt
    dw 0xFFFF
    dw 0
    db 0 
    db 0x92   ; present, ring0, data, expanded up, writeble. (BITS)
    db 0xCF
    db 0

;video
VIDEO_SEL equ $-gdt	
    dq 0x00c0920b80000002     ;/* screen 0x18 - for display */

;tss0
TSS0_SEL equ $-gdt	
    dq 0x0000e90100000068     ;# TSS0 descr 0x20

;ldt
LDT0_SEL equ $-gdt
    dq 0x0000e20100000040     ;# LDT0 descr 0x28

;tss1
TSS1_SEL equ $-gdt	
    dq 0x0000e90100000068     ;# TSS1 descr 0x30

;ldt1
LDT1_SEL equ $-gdt
    dq 0x0000e20100000040     ;# LDT1 descr 0x38	

end_gdt:
    dd 0


;
; GDT_register - registro.
;  
GDT_register:
    dw (end_gdt-gdt)-1
    dd gdt 


;
; idt ---------------------------
;


;Constantes usandas nas entradas da IDT.
sys_interrupt  equ  0x8E  
sys_code       equ  8        ;Seletor de c�digo.


;========================================;
;    IDT.                                ;
;========================================;
idt:

;0 interrupt 0h, Div error.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;1 interrupt 1h, Debug exception.
	dw 0                    		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;2 interrupt 2h, Non maskable interrupt.
	dw 0                    		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;3 interrupt 3h, int3 trap.
	dw 0                        		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;4 interrupt 4h, into trap.
	dw 0                        		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;5 interrupt 5h, bound trap.
	dw 0                          		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;6 interrupt 6h, invalid instruction.
	dw 0                        		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;7 interrupt 7h, no coprocessor.
	dw 0                         	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;8 interrupt 8h, Double fault.
	dw 0                         	  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;9 interrupt 9h, Coprocessor segment overrun 1.
	dw 0                         	    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;10 interrupt Ah, Invalid tss.
	dw 0                     		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;11 interrupt Bh, Segment not present.
	dw 0                        		  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;12 interrupt Ch, Stack fault.
	dw 0                            	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;13 interrupt Dh, #GPF, General Protection Fault.
	dw 0           			   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;14 interrupt Eh, #PF, Page Fault.
	dw 0           			   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;15 interrupt Fh, Reserved.
	dw 0                		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;16 interrupt 10h, Coprocessor error.
	dw 0                  		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;17 interrupt 11h, Alignment check.
	dw 0                  		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;18 interrupt 12h, Machine check. 
	dw 0 		  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;19 interrupt 13h, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;20 interrupt 14h, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;21 interrupt 15h, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;22 interrupt 16h, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;23 interrupt 17h, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;24 interrupt 18h, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;25 interrupt 19h, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;26 interrupt 1Ah, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;27 interrupt 1Bh, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;28 interrupt 1Ch, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;29 interrupt 1Dh, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;30 interrupt 1Eh, Reserved.
	dw 0		   
	dw sys_code		
	db 0
	db sys_interrupt
	dw 0

;31 interrupt 1Fh, Reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

	
;
;IRQs.
;

;32 interrupt 20h, _irq0, TIMER, IRQ0.
	dw 0         
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;33 interrupt 21h, Keyboard, IRQ1.
	dw 0               
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;34 interrupt 22h, Reserved, IRQ2.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;35 interrupt 23h, Reserved, IRQ3.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;36 interrupt 24h, Reserved, IRQ4.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;37 interrupt 25h, Reserved, IRQ5.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;38 interrupt 26h, Reserved, IRQ6.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;39 interrupt 27h, Reserved, IRQ7.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;40 interrupt 28h, Reserved, IRQ8.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;41 interrupt 29h, Reserved, IRQ9.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;42 interrupt 2Ah, Reserved, IRQ10.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;43 interrupt 2Bh, Reserved, IRQ11.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;44 interrupt 2Ch, Reserved, IRQ12.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;45 interrupt 2Dh, Reserved, IRQ13.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;46 interrupt 2Eh, Reserved, IRQ 14.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;47 interrupt 2Fh, Reserved, IRQ15.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

	
;
;
;

;48 interrupt 30h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;49 interrupt 31h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;50 interrupt 32h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;51 interrupt 33h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;52 interrupt 34h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;53 interrupt 35h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;54 interrupt 36h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;55 interrupt 37h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;56 interrupt 38h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;57 interrupt 39h.
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;58 interrupt 3Ah.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;59 interrupt 3Bh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;60 interrupt 3Ch.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;61 interrupt 3Dh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;62 interrupt 3Eh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;63 interrupt 3Fh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;64 interrupt 40h.
	dw 0		  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;65 interrupt 41h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;66 interrupt 42h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;67 interrupt 43h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;68 interrupt 44h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;69 interrupt 45h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;70 interrupt 46h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;71 interrupt 47h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;72 interrupt 48h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;73 interrupt 49h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;74 interrupt 4Ah.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;75 interrupt 4Bh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;76 interrupt 4Ch.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;77 interrupt 4Dh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;78 interrupt 4Eh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;79 interrupt 4Fh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;80 interrupt 50h.
	dw 0		          
	dw sys_code		
	db 0
	db sys_interrupt
	dw 0

;81 interrupt 51h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;82 interrupt 52h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;83 interrupt 53h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;84 interrupt 54h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;85 interrupt 55h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;86 interrupt 56h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;87 interrupt 57h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;88 interrupt 58h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;89 interrupt 59h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;90 interrupt 5Ah.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;91 interrupt 5Bh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;92 interrupt 5Ch.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;93 interrupt 5Dh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;94 interrupt 5Eh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;95 interrupt 5Fh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;96 interrupt 60h. 
	dw 0			   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;97 interrupt 61h.  
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;98 interrupt 62h.  
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;99 interrupt 63h.  
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;100 interrupt 64h.  
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;101 interrupt 65h.  
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;102 interrupt 66h.  
	dw 0			  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;103 interrupt 67h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;104 interrupt 68h.  
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;105 interrupt 69h.  
	dw 0	    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;106 interrupt 6Ah.  
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;107 interrupt 6Bh.  
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;108 interrupt 6Ch.
	dw 0			    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;109 interrupt 6Dh. 
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;110 interrupt 6Eh.  
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;111 interrupt 6Fh.  
	dw 0		    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;112 interrupt 70h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;113 interrupt 71h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;114 interrupt 72h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;115 interrupt 73h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;116 interrupt 74h.	
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;117 interrupt 75h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;118 interrupt 76h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;119 interrupt 77h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;120 interrupt 78h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;121 interrupt 79h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;122 interrupt 7Ah.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;123 interrupt 7Bh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;124 interrupt 7Ch.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;125 interrupt 7Dh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;126 interrupt 7Eh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;127 interrupt 7Fh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;128 interrupt 80h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;129 interrupt 81h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;130 interrupt 82h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;131 interrupt 83h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;132 interrupt 84h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;133 interrupt 85h.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;134 interrupt 86h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;135 interrupt 87h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;136 interrupt 88h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;137 interrupt 89h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;138 interrupt 8Ah.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;139 interrupt 8Bh.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;140 interrupt 8Ch.
	dw 0  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;141 interrupt 8Dh.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;142 interrupt 8Eh.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;143 interrupt 8Fh.
	dw 0   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;144 interrupt 90h.
	dw 0		   
	dw sys_code		
	db 0
	db sys_interrupt
	dw 0

;145 interrupt 91h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;146 interrupt 92h.
	dw 0	  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;147 interrupt 93h.
	dw 0   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;148 interrupt 94h.
	dw 0		  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;149 interrupt 95h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;150 interrupt 96h.
	dw 0	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;151 interrupt 97h.
	dw 0        
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;152 interrupt 98h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;153 interrupt 99h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;154 interrupt 9Ah.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;155 interrupt 9Bh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;156 interrupt 9Ch.
	dw 0 	  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;157 interrupt 9Dh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;158 interrupt 9Eh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;159 interrupt 9Fh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;160 interrupt A0h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;161 interrupt A1h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;162 interrupt A2h.
	dw 0 	 
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;163 interrupt A3h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;164 interrupt A4h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;165 interrupt A5h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;166 interrupt A6h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;167 interrupt A7h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;168 interrupt A8h.
	dw 0    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;169 interrupt A9h.
	dw 0    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;170 interrupt AAh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;171 interrupt ABh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;172 interrupt ACh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;173 interrupt ADh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;174 interrupt AEh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;175 interrupt AFh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;176 interrupt B0h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;177 interrupt B1h.
	dw 0 	   
	dw sys_code		
	db 0
	db sys_interrupt
	dw 0

;178 interrupt B2h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;179 interrupt B3h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;180 interrupt B4h.
	dw 0    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;181 interrupt B5h.
	dw 0 		  
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;182 interrupt B6h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;183 interrupt B7h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;184 interrupt B8h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;185 interrupt B9h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;186 interrupt BAh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;187 interrupt BBh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;188 interrupt BCh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;189 interrupt BDh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;190 interrupt BEh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;191 interrupt BFh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;192 interrupt C0h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;193 interrupt C1h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;194 interrupt C2h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;195 interrupt C3h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;196 interrupt C4h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;197 interrupt C5h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;198 interrupt C6h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;199 interrupt C7h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0
	
;
; *** Interrup��o do sistema.
;	

;200 interrupt C8h, System Call.
	dw 0    
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;201 interrupt C9h.
	dw 0 
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;202 interrupt CAh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;203 interrupt CBh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;204 interrupt CCh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;205 interrupt CDh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;206 interrupt CEh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;207 interrupt CFh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;208 interrupt D0h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;209 interrupt D1h.
	dw 0 	   
	dw sys_code		
	db 0
	db sys_interrupt
	dw 0

;210 interrupt D2h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0
;211 interrupt D3h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;212 interrupt D4h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;213 interrupt D5h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;214 interrupt D6H.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;215 interrupt D7h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;216 interrupt D8h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;217 interrupt D9h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;218 interrupt DAh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;219 interrupt DBh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;220 interrupt DCh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;221 interrupt DDh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;222 interrupt DEh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;223 interrupt DFh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;224 interrupt E0h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;225 interrupt E1h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;226 interrupt E2h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;227 interrupt E3h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;228 interrupt E4h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;229 interrupt E5h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;230 interrupt E6h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;231 interrupt E7h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;232 interrupt E8h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;233 interrupt E9h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;234 interrupt EAh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;235 interrupt EBh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;236 interrupt ECh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;237 interrupt EDh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;238 interrupt EEh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;239 interrupt EFh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;240 interrupt F0h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;241 interrupt F1h.
	dw 0 		   
	dw sys_code		
	db 0
	db sys_interrupt
	dw 0

;242 interrupt F2h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;243 interrupt F3h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;244 interrupt F4h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;245 interrupt F5h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;246 interrupt F6h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;247 interrupt F7h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;248 interrupt F8h.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;249 interrupt F9h.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;250 interrupt FAh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;251 interrupt FBh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;252 interrupt FCh.
	dw 0 	   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;253 interrupt FDh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;254 interrupt FEh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;255 interrupt FFh.
	dw 0 		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0
idt_end:
dd 0


;
; IDT_register - Registro.
;


IDT_register:
    dw  (256*8) - (1)
    dd idt 


;
; Includes ---------------------------------------
;

;
; Os includes est�o padronizados assim:
;
; head, headlib.
; hardware, hardwarelib.
; software, softwarelib.
;


    ;Fun��es de apoio a inicializa��o do boot loader.
    %include "headlib.s"

	;Interrup��es de hardware (irqs) e faults.(reservadas).
    %include "hardware.inc"
    %include "hardwarelib.inc"

	;interrup��es de software
	%include "software.inc"
    %include "softwarelib.inc"


;
; DATA: in�cio do data segment.
;
segment .data
global _data_start
_data_start:
    db 0x55    ;Data magic.
    db 0xAA    ;Data magic.



;;
;; ## BSS  ##
;;

segment .bss
global _bss_start
_bss_start:
    ;times (512*2) db 0 #bugbug isso n�o pode.

	
	
;;
;; ## HEAP  ##
;;
	
	
;heap
;inicio do heap do bootloader, ainda parte de bss.
segment .bss_heap
global _bootloader_heap_start
_bootloader_heap_start:
    times (512*2) db 0
global _bootloader_heap_end 
_bootloader_heap_end:

;;
;; ## STACK  ##
;;


;stack
;inicio da stack do bootloader, ainda parte de bss.
segment .bss_stack
global _bootloader_stack_end
_bootloader_stack_end:
    times (512*2) db 0
global _bootloader_stack_start
_bootloader_stack_start:


;
;@_FIM
;


