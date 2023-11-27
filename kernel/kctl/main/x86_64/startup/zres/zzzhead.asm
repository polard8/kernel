;
; File: x86/pumpcore/head.asm 
; 
;     The kernel entry point for x86 processors.
;     32 bit.
;
; The kernel image was loaded in the physical address 0x00100000,
; with the entry point in 0x00101000. 
; The linear address is 0xC0000000.
; The boot loader made some initial memory configuration. Only
; enough to jump to the entry point in 0xC0001000.
;
; Heap and Stack:
; KERNEL_HEAP_START, KERNEL_HEAP_END
; KERNEL_STACK_START, KERNEL_STACK_END
; See: include/globals/gva.h
;
; In the end of the document you are gonna find 
; the GDT and the IDT tables.
;
; History:
;     2005 - Create by Fred Nora.
;     2006 ~ 2020 Some new routines.
;



HEAD_CURRENT_ARCH_X86 EQU 1000


;;
;; Imported.
;;

; See: gdef.h
extern _blSavedLastValidAddress;
extern _blSavedMetafileAddress;
extern _blSavedDiskNumber;
extern _blSavedHeads;
extern _blSavedSPT;
extern _blSavedCylinders;
;; ...


; Buffers 
; See: gdef.h
extern _g_frontbuffer_pa
; ...


; Stacks.
; ps: It needs to be the same in the tss.
; See: include/mm/x86mm.h
extern _kernel_stack_start      
extern _kernel_stack_start_pa   ;; Used in the TSS.
; ...


;;
;; == Context =============================================
;;

extern _contextSS        ; User Mode.
extern _contextESP       ; User Mode.
extern _contextEFLAGS    ; User Mode.
extern _contextCS        ; User Mode.
extern _contextEIP       ; User Mode.
extern _contextDS
extern _contextES
extern _contextFS
extern _contextGS
extern _contextEAX
extern _contextEBX
extern _contextECX
extern _contextEDX
extern _contextESI
extern _contextEDI
extern _contextEBP
; ...

; GUI flag.
extern _g_useGUI
; ...


;;
;; == Imported functions =======================================
;;

;; Entry point for the architecture independent routine.
extern _kernel_main

;; Entry point for the x86 initialization.
extern _x86main



;; ==================================================
;; head_init:
;;
;; IN: 
;;    al = 'G' (Graphic Mode).
;;    al = 'T' (Text Mode).
;;    ebx = LFB.
;;    ecx = BootBlock pointer.
;;    edx = BootBlock pointer.
;;    ebp = BootBlock pointer.
;; Called by _kernel_begin in head_32.asm

head_init:

; Saving

    mov dword [_kArg1], eax
    mov dword [_kArg2], ebx
    mov dword [_kArg3], ecx
    mov dword [_kArg4], edx

; #debug
; The vga memory was mapped in 0x800000 by the boot loader.

    ;mov byte [0x800000], byte "K"
    ;mov byte [0x800001], byte 9
    ;mov byte [0xb8000], byte "k"
    ;mov byte [0xb8000], byte 9


    ;; #debug
    ;; Testing GUI routines.

    ;mov eax, 0xc0c0c0
    ;mov ebx, 500
    ;mov ecx, 500
    ;call _gui_buffer_putpixel

    ;call _asm_refresh_screen 
    ;jmp $

    ;;
    ;; Magic byte for gui mode.
    ;;

; This flag tell us that we are in graphics mode.

    cmp al, byte 'G'
    je .LuseGUI

; Fail. No GUI.
.Lfail_nogui:
    mov byte [0xb8000], byte "T"
    mov byte [0xb8001], byte 9
    mov byte [0xb8002], byte "M"
    mov byte [0xb8003], byte 9
.Lnogui_hang:
    cli
    hlt
    jmp .Lnogui_hang

;
; == Use GUI =======================================
;

.LuseGUI:

; Check again.

    cmp al, byte 'G'
    jne .Lfail_nogui

; #important
; Saving flags.
; 1=gui

    mov dword [_g_useGUI],       dword 1
    mov dword [_SavedBootMode],  dword 1


;
; == Boot block ========================================
;

; Now we're gonna grap all the offsets in the block.

    ;; #todo:
    ;; We need to put all these information in the same document
    ;; and use the same prefix.
    ;; These variables was defined here in this document.
    ;; See: include/globals/gdef.h for the globals.


    ; BootBlock pointer.
    ; With this pointer we can create a boot block structure.
    ; ecx = BootBlock pointer.
    ; edx = LoaderBlock pointer.

    mov dword [_SavedBootBlock], edx
    ;;mov dword [_SavedBootBlock], ebp


; 0 - LFB.
; FrontBuffer Address, (LFB)
; Physical address.

    xor eax, eax
    mov eax, dword [edx +0] 
    mov dword [_SavedLFB],          eax
    mov dword [_g_frontbuffer_pa],  eax


    ; 4 - X.
    xor eax, eax
    mov ax, word [edx +4] 
    mov dword [_SavedX], eax

    ; 8 - Y.
    xor eax, eax
    mov ax, word [edx +8] 
    mov dword [_SavedY], eax

    ; 12 - BPP.
    xor eax, eax
    mov al, byte [edx +12] 
    mov dword [_SavedBPP], eax

    ;; 16 - Last valid ram address.
    ;; Used to know the size of the RAM.
    xor eax, eax
    mov eax, dword [edx +16] 
    mov dword [_blSavedLastValidAddress], eax

    ;; 20 - Metafile address.
    xor eax, eax
    mov eax, dword [edx +20] 
    mov dword [_blSavedMetafileAddress], eax

    ;; 24 - disk number
    xor eax, eax
    mov eax, dword [edx +24] 
    mov dword [_blSavedDiskNumber], eax

    ;; 28 - heads
    xor eax, eax
    mov eax, dword [edx +28] 
    mov dword [_blSavedHeads], eax

    ;; 32 - spt
    xor eax, eax
    mov eax, dword [edx +32] 
    mov dword [_blSavedSPT], eax

    ;; 36 - cylinders
    xor eax, eax
    mov eax, dword [edx +36] 
    mov dword [_blSavedCylinders], eax

    ;; #todo
    ;; We can create a robust bootblock.
    ;; ...

;
; == Interrupts support ==============================
;

    ;; This is the order here:
    ;; gdt, idt, ldt, tss+tr.


; No interrupts for now. 
; It was already done is head_32.asm

    cli
    
    
    ;; Memory management registes:
    ;; GDTR, IDTR, LDTR and TR.

;
; == GDT ================================================
;

; We have another configuration in another place.

    lgdt [_GDT_register] 


    ;; #todo
    ;; Vamos tentar colocar aqui a configuração dos registradores
    ;; de segmento. Essa configuração no momento está logo abaixo.
    ;; Pelo menos os segmentos de dados.

    ; #todo
    ; Temos que configurar os registradores novamente,
    ; logo após configurarmos a GDT.
    
    ; #todo
    ; Devemos fazer o mesmo se o código em C carregar uma 
    ; nova GDT, e ele faz.

    ;xor eax, eax
    ;mov ax, word 0x10
    mov ax, word  __BOOT_DS
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax


;
; == IDT ================================================
;

; We have another configuration in another place.

    call setup_idt      ; Create a common handler, 'unhandled_int'.
    call setup_faults   ; Setup vectors for faults and exceptions.
    call setup_vectors  ; Some new vectors.
    lidt [_IDT_register] 

;
; == LDT ================================================
;

; Clear LDT

    xor eax, eax
    lldt ax


;
; == TR (tss) ======================================
;


    ;; The tr configuration is little bit confused here.
    ;; There is another configuration in another place.
    ;; We're gonna work on this in the future.

    ; Flush TSS:
    ; Load the index of our TSS structure.
    ; The index is 0x28, as it is the 5th selector and 
    ; each is 8 bytes long, but we set the bottom two bits (making 0x2B)
    ; so that it has an RPL of 3, not zero.
    ; Load 0x2B into the task state register.

    ; #important:
    ; We need to put the TSS address into the GDT.

    ;; ?? 
    ;; We already did this. (103)
    ;; mov word [gdt6], tss0_end - tss0 - 1 

; This is the address os our tss ?

    mov eax, dword tss0

; This is the place for the tss0 into the gdt.

    mov [gdt6 + 2], ax
    shr eax, 16
    mov [gdt6 + 4],  al
    mov [gdt6 + 7],  ah

; Load TR.
; 0x2B = (0x28+3).

    mov ax, word 0x2B
    ltr ax

;
; ========================================================
;

; Jump to flush it.

    ;; jmp 8:_trJumpToFlush
    jmp __BOOT_CS:_trJumpToFlush
    nop
_trJumpToFlush:
    nop


; Order:
; PIC and PIT early initialization 


;
; == PIC ========================================
;

; Early PIC initialization.

picEarlyInitialization:

    ;; ??
    ;; PIC MODE
    ;; Selecting the 'Processor Interrup Mode'.
    ;; All the APIC components are ignored here, and
    ;; the system will operate in the single-thread mode
    ;; using LINT0.


    cli

    ;xor eax, eax
    mov al, 00010001b    ; begin PIC1 initialization.
    out 0x20, al
    IODELAY
    mov al, 00010001b    ; begin PIC2 initialization.
    out 0xA0, al
    IODELAY
    mov al, 0x20         ; IRQ 0-7: interrupts 20h-27h.
    out 0x21, al
    IODELAY
    mov al, 0x28         ; IRQ 8-15: interrupts 28h-2Fh.
    out 0xA1, al
    IODELAY
    mov al, 4
    out 0x21, al
    IODELAY
    mov al, 2
    out 0xA1, al
    IODELAY
    ;mov al, 00010001b    ; 11 sfnm 80x86 support.
    mov al, 00000001b     ; 01 80x86 support.
    out 0x21, al
    IODELAY
    out 0xA1, al
    IODELAY


; Mask all interrupts.


    cli
    mov  al, 255
    out  0xA1,  al
    IODELAY
    out  0x21,  al
    IODELAY


;
; == PIT ========================================
;

; Early PIT initialization.

pitEarlyInitialization:

    ;; Setup system timers.

    ;; ??
    ;; Some frequencies to remember.
    ;; PIT 8253 e 8254 = (1234DD) 1193181.6666 / 100 = 11930. ; 1.19MHz.
    ;; APIC timer      = 3,579,545 / 100 = 35796  3.5 MHz.
    ;; 11931    ; (1193181.6666 / 100 = 11930) timer frequency 100 HZ.

    ;xor eax, eax
    mov al, byte 0x36
    mov dx, word 0x43
    out dx, al
    IODELAY
    mov eax, dword 11931
    mov dx, word 0x40
    out dx, al
    IODELAY
    mov al, ah
    out dx, al
    IODELAY


;
; == RTC ========================================
;

; Early RTC initialization.

;rtcEarlyInitialization:
    ;#todo 
    ; Nothing for now


    ;; #todo: 
    ;; memory caching control.


; Unmask all interrupts.

    mov al, 0
    out 0xA1, al
    IODELAY
    out 0x21, al
    IODELAY

; No interrupts.

    cli


;
; == Set up registers ==================================
;


; Debug registers:
; DR0 ~ DR7
; Debug registers.
; Disable break points.

    xor eax, eax
    ;mov dr2, eax
    mov dr7, eax
    ;; ...


;
; Data segments for ring 0.
;

    ;; #todo
    ;; Devemos antecipar essa configuração o máximo possível,
    ;; colocarmos perto do carregamento do gdtr.

    ;xor eax, eax
    ;mov ax, word 0x10
    mov ax, word  __BOOT_DS
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax


;
; Stack
;

; Initialize and save.
; Is it the same in the tss ?
    
    mov eax, 0x003FFFF0 
    mov esp, eax 
    mov dword [_kernel_stack_start],    eax 
    mov dword [_kernel_stack_start_pa], eax 


;
; == Kernel Status ===================================
;

    ;; #bugbug
    ;; It does not make sanse.
    ;;  Why changing to '1' if _kernel_main changes to '0'?
    ;; we need to think about this flag.

    mov dword [_KernelStatus], dword 1
    ;; mov dword [_KernelStatus], dword 0


    ; # test: 
    ; Clean flags.
    ; # perigo
    ; Como ficam as interrupções?

    ;; push dword 0
    ;; popfd 


;
; == Calling the C part ===============================
;


;; .Lcall_c_code:


; We only have one argument. The arch type.
; See: kernel/0mem/main.c 

    mov eax, dword HEAD_CURRENT_ARCH_X86
    push eax

    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

; #bugbug
; We need to check what kind of jum we can use in this case.
; For AMD and for Intel.
; 32 ? 64 ?
; call ? ret ?
; There are limitations.

    call _kernel_main

; We really don't wanna reach this point.
; We are in graphics mode and we can't print an error message.
; We will not return to boot.asm.

    jmp _EarlyRing0IdleThread

; #todo
; Maybe we can export this
; as a main loop for all processes.
; For now we have a idle thread.

global _EarlyRing0IdleThread
_EarlyRing0IdleThread:
    cli
    hlt
    jmp _EarlyRing0IdleThread


;
; == Data area ==================================
;


;; ====================================================
;; _SavedBootBlock:
;;     To save the arguments that came from Boot Manager.
;;     It's about video ...
;;

global _SavedBootBlock
_SavedBootBlock:    dd 0

global _SavedLFB
_SavedLFB:          dd 0

global _SavedX
_SavedX:            dd 0

global _SavedY
_SavedY:            dd 0

global _SavedBPP
_SavedBPP:          dd 0

global _SavedLastValidAddress
_SavedLastValidAddress:    dd 0

;; 1 = GUI ; 0 = Text Mode
global _SavedBootMode
_SavedBootMode:      dd 0


;;
;;================================================= 
;; Kernel arguments.
;;

global _kArg1
_kArg1:    dd 0

global _kArg2
_kArg2:    dd 0

global _kArg3
_kArg3:    dd 0

global _kArg4
_kArg4:    dd 0



;;
;; == Segment ==========================================
;;

segment .text 


;; #ps
;; The gdt and the idt are in the code segment.
;; protection ?

;;
;; == GDT ====================================================
;;

;;
;; TYPES:
;; The TYPE values for these are 
;;
;;  >> 0101 for a task gate,          5
;;  >> D110 for a interrupt gate,     E
;;  >> D111 for a trap gate,          F
;;
;; where D is 1 for 32 bit gate and 0 for a 16 bit gate. 
;;


global _gdt
_gdt:
;Selector 0 - Null.
NULL_SEL equ $-_gdt
    dd 0
    dd 0
;Selector 8 - Code, kernel mode.  
__BOOT_CS equ $-_gdt
CODE_SEL  equ $-_gdt
    dw 0xFFFF
    dw 0
    db 0
    db 0x9A   ; present, ring0, code, non-confirming, readble.
    db 0xCF
    db 0
;Selector 0x10 - Data, kernel mode.
__BOOT_DS equ $-_gdt
DATA_SEL  equ $-_gdt
    dw 0xFFFF
    dw 0
    db 0 
    db 0x92    ; present, ring0, data, expanded up, writeble. (BITS)
    db 0xCF
    db 0
;Selector 18h - Code, user mode.
USER_CODE_SEL equ $-_gdt
    dw 0xFFFF
    dw 0
    db 0 
    db 0xF8   ;;0xFE   ;;5,E,F ;;A  ; 1111b ,ah  [ ( present|ring3|1 )  A = CODE ]
    db 0xCF
    db 0

    ;dw     0xffff
    ;dw     0x0000
    ;db     0x00
    ;dw     11011111b *256 +11111010b
    ;db     0x00

;Selector 20h - Data, user mode.
USER_DATA_SEL equ $-_gdt
    dw 0xFFFF
    dw 0
    db 0 
    db 0xF2   ; 1111b ,2h  [ ( present|ring3|1 )  ,  2 = DATA ]
    db 0xCF
    db 0

    ;dw     0xffff
    ;dw     0x0000
    ;db     0x00
    ;dw     11011111b *256 +11110010b
    ;db     0x00

;Tem que ter pelo menos uma tss para mudar para user mode, 
;sen�o da falta.
;Selector 28h - Tss.
TSS_DATA_SEL equ $-_gdt
gdt6:
    dw 104 ;;103
    dw 0
    db 0
    db 0x89 ;;0x89   ;; presente, ring0(onde esta a tss??), s=0(segmento do sistema) /  ;;89h ((Present|Executable|Accessed)) 1001  bit3=32bitcode
    db 0x10
    db 0

;Selector 30h - Ldt.
LDT_TEST_SEL equ $-_gdt
    db 0xff
    db 0x0
    db 0x0
    db 0xd1
    db 0x0
    db 0x82
    db 0x0
    db 0x0

global _end_gdt
_end_gdt:
    dd 0

; _GDT_register

global  _GDT_register
_GDT_register:
    dw  (_end_gdt-_gdt)-1
    dd  _gdt



;;
;; == IDT ====================================================
;;


;
; Usadas nas entradas da idt.
;

sys_interrupt equ    0x8E 
sys_code      equ    8     ;Code selector.


;==================================================;
;  Idt.                                            ;
;  Interrupt vectors for intel x86                 ;
;==================================================;

global _idt
_idt:

;0 interrupt 0h, div error.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0
	
;1 interrupt 1h, debug exception.
	dw 0 
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;2 interrupt 2h, non maskable interrupt.
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

;5 interrupt 5h,  bound trap.
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

;8 interrupt 8h, double fault.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;9 interrupt 9h, coprocessor segment overrun 1.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;10 interrupt Ah, invalid tss.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;11 interrupt Bh, segment not present.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;12 interrupt Ch, stack fault.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;13 interrupt Dh, general protection fault.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;14 interrupt Eh, page fault.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;15 interrupt Fh, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;16 interrupt 10h, coprocessor error.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;17 interrupt 11h, alignment check.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;18 interrupt 12h, machine check. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0
	
	;;
	;; ## Intel reserveds ##
	;;

;19 interrupt 13h, reserved.
	dw 0		   
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;20 interrupt 14h, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;21 interrupt 15h, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;22 interrupt 16h, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;23 interrupt 17h, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;24 interrupt 18h, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;25 interrupt 19h, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;26 interrupt 1Ah, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;27 interrupt 1Bh, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;28 interrupt 1Ch, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;29 interrupt 1Dh, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;30 interrupt 1Eh, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;31 interrupt 1Fh, reserved.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

  ;; 
  ;;  ##  IRQs ##
  ;;

;32 interrupt 20h, IRQ0, TIMER.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;33 interrupt 21h, IRQ1, TECLADO.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;34 interrupt 22h, IRQ2.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;35 interrupt 23h, IRQ3.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;36 interrupt 24h, IRQ4.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;37 interrupt 25h, IRQ5.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;38 interrupt 26h, IRQ6.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;39 interrupt 27h, IRQ7.
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;40 interrupt 28h, IRQ8. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;41 interrupt 29h, IRQ9. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;42 interrupt 2Ah, IRQ10. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;43 interrupt 2Bh, IRQ11. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;44 interrupt 2Ch, IRQ12. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;45 interrupt 2Dh, IRQ13. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;46 interrupt 2Eh, IRQ 14. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

;47 interrupt 2Fh, IRQ15. 
	dw 0
	dw sys_code
	db 0
	db sys_interrupt
	dw 0

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

;89 interrupt 59h
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

;104 interrupt 68h
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
	
	;;
	;;  ## system call ##
	;;
	
	;;#importante
	;;Essa agora vai ser a system call.
	;;Ela � UNIX-like e usada em muitos sistemas.

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

  ;;#obs
  ;;Essa n�o � mais a interrup��o do sistema.
  ;;Agora � a tradicional 128 (0x80)   
	
;200 interrupt C8h, 
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
; IDT_register
;

global _IDT_register
_IDT_register:

    dw  (256*8) - (1)
    dd _idt 



;
; End
;

