
; unit1hw.asm
; This file handles the traps for the x86_64 processors.


align 16
__hw_fpu_buffer:
    times 512 db 0
align 16


;================================
global _DisableSSE
_DisableSSE:
    push rax
    mov rax, cr0
    or ax, 1 << 3    ;Set TS
    mov cr0, rax
    pop rax
    ret

;================================
global _EnableSSE
_EnableSSE:
    push rax
    mov rax, cr0
    and ax, ~(1 << 3)    ; Clear TS
    mov cr0, rax
    pop rax
    ret


;;=====================================================
;;  ## TIMER ##
;;=====================================================
;; _irq0: 
;; IRQ 0. 
;; Timer interrupt handler
;; See:
;; 1pump/arch/x86_64/pit.c
;; 0mem/core/ps/disp/ts.c
;;

;
; Imports
;

;;
;; == Context =================
;;

; See:
; x64cont.c

extern _contextSS        ; User Mode.
extern _contextRSP       ; User Mode.
extern _contextRFLAGS    ; User Mode.
extern _contextCS        ; User Mode.
extern _contextRIP       ; User Mode.

extern _contextDS
extern _contextES
extern _contextFS  ;?
extern _contextGS  ;?

extern _contextRAX
extern _contextRBX
extern _contextRCX
extern _contextRDX

extern _contextRSI
extern _contextRDI

extern _contextRBP

extern _contextR8
extern _contextR9
extern _contextR10
extern _contextR11
extern _contextR12
extern _contextR13
extern _contextR14
extern _contextR15

extern _contextCPL

; Array.
; Defined in x64cont.c
extern _context_fpu_buffer

; ...

;================================
extern _irq0_TIMER

; Capture context
global _irq0
_irq0:

    cli

; No caso do dispatcher lançar uma nova thread,
; então ele deve acionar enviar um EIO.

    ; mov dword [_irq0PendingEOI], 1

;; == Save context ====================
    
    ; Stack frame. (all double)
    pop qword [_contextRIP]     ; rip
    pop qword [_contextCS]      ; cs
    pop qword [_contextRFLAGS]  ; rflags
    pop qword [_contextRSP]     ; rsp
    pop qword [_contextSS]      ; ss

    mov qword [_contextRDX], rdx 
    mov qword [_contextRCX], rcx 
    mov qword [_contextRBX], rbx 
    mov qword [_contextRAX], rax
     
    mov qword [_contextRBP], rbp
 
    mov qword [_contextRDI], rdi 
    mov qword [_contextRSI], rsi 

; Segments

    xor rax, rax

    ; Is it used?
    mov ax, gs
    mov word [_contextGS], ax
    ; Is it used?
    mov ax, fs
    mov word [_contextFS], ax
    
    mov ax, es
    mov word [_contextES], ax
    mov ax, ds
    mov word [_contextDS], ax

; FPU
; See:
; https://wiki.osdev.org/SSE

    fxsave [_context_fpu_buffer]


; #todo
; Media, float pointers, debug.
; #important:
; We are using the kernel segment registers.
; Kernel data segments and stack.
; #bugbug: sempre a mesma pilha?
; Que pilha as interrupçoes de softwar estao usando?

;
; Calls
;

; cpl
; Get the first 2 bits of cs.
; see: x64cont.c
    mov rax, qword [_contextCS]
    and rax, 3
    mov [_contextCPL], rax

; Timer and taskswitching.
; See: ke/hal/x86_64/pit.c

    call _irq0_TIMER

; FPU

    fxrstor [_context_fpu_buffer]

; Release a bandit.
    jmp unit3Irq0Release
; --------------------------------------



; #todo: Move to unit 2
; ---------------------------------------------------------------------
; reboot -- Reboot the computer
hw_reboot:
	in al, 0x64
	test al, 00000010b		; Wait for an empty Input Buffer
	jne hw_reboot
	mov al, 0xFE
	out 0x64, al			; Send the reboot call to the keyboard controller
	jmp hw_reboot
; ----------------------------------------------------------------------


;========================================
; _irq1:
;     IRQ 1 - Keyboard.
;
; See:
; 2io/dev/tty/chardev/hid/i8042/keyboard.c
;

extern _xxxxIRQ1_DEBUG_MESSAGE
extern _irq1_KEYBOARD

; Capture context
global _irq1  
_irq1:

    cli

    ;; Acumulator.
    push rax
   
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs
    push rsp
    pushfq
    cld

    ;xor rax, rax
    ;mov ax, word 0x10 ;KERNEL_DS
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax ; Is it used ?
    ;mov ss, ax ; Is it used ?


; See: 
; keyboard.c

    fxsave [__hw_fpu_buffer]

    call _irq1_KEYBOARD

    fxrstor [__hw_fpu_buffer]


    popfq
    pop rsp
    pop gs
    pop fs
    ;pop es
    ;pop ds

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    ; send EOI to XT keyboard
    ;in      al, 061h
    ;mov     ah, al
    ;or      al, 080h
    ;out     061h, al
    ;mov     al, ah
    ;out     061h, al

    ;; EOI - Only the first PIC.
    xor rax, rax 
    MOV AL, 020h
    OUT 020h, AL
    IODELAY  
    
    ;; The acumulator.
    pop rax

    sti
    iretq

;;===========================












;=======================================================
; IRQ 3 - serial port controller for serial port 2 
; (shared with serial port 4, if present)
; See: serial.c

;extern _serial2_handler
;extern _serial4_handler

; Capture context
global _irq3
_irq3:

    cli
    
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    ;call _serial2_handler
    ;call _serial4_handler

    ;; EOI - Only the first PIC.
    mov al, 0x20
    out 0x20, al
    IODELAY  
    
    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    sti
    iretq
    
;; ==========================================







;====================================================
; IRQ 4 - serial port controller for serial port 1 
;(shared with serial port 3, if present)
; See: serial.c

;extern _serial1_handler
;extern _serial3_handler

; Capture context
global _irq4
_irq4:

    cli
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    ;call _serial1_handler
    ;call _serial3_handler


    ;; EOI - Only the first PIC.
    mov al, 0x20
    out 0x20, al
    IODELAY  
    
    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    sti
    iretq
;================================






;--------------
; IRQ 5 - parallel port 2 and 3  or  sound card
;_irq5:
;    iretd



;--------------
; IRQ 6  floppy disk controller
;_irq6:
;    iretd



;===================================================
;IRQ 7 parallel port 1. 
; It is used for printers 
; or for any parallel port 
; if a printer is not present. It can also be potentially 
; be shared with a secondary sound card with careful 
; management of the port.

;; The correct way to handle an IRQ 7 is to first check the master PIC 
;; chip's ISR to see if the IRQ is a spurious IRQ or a real IRQ. 
;; If it is a real IRQ then it is treated the same as any other real 
;; IRQ. If it is a spurious IRQ then you ignore it 
;; (and do not send the EOI). 

; Capture context
global _irq7
_irq7:

    cli
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    ;; ++
    ;; ================================================
    ;; #test
    ;; Testing the spurious interrupt management.

    xor rax, rax
    mov  al, 03h                ; PIC.OCW3 set function to read ISR (In Service Register)
    out  23h, al                ; write to PIC.OCW3 master
    in   al, 20h                ; read ISR master.
    test al, 80h                           ; if the in-service register does not have IR7 bit set
    jz short _NotParallelPort  ; this would be a spurious interrupt.

    ;; ================================================
    ;; --

;; Not spurious
;; So this is a norma parallel por interrupt.

    ;call _first_parallel_port_Handler

; EOI. Master. for parallel port
_eoiForParallelPort:

    ;xor rax, rax
    mov al, 0x20
    out 0x20, al   
    IODELAY  

; No eoi for irq 7 spurious
_NotParallelPort:
  
    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    sti
    iretq
    
    
    



;================================================
; _irq8:
;     System CMOS, Realtime clock.
;     IRQ 8 - real-time clock (RTC)
;

; Capture context
global _irq8
_irq8:

    cli
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    ;call _irq8_RTC

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    
    sti
    iretq

;;============================


;=========================================================
; IRQ 9

;extern _xxxe1000handler

; Capture context
global _irq9
_irq9:
    
    ;; #test
    jmp unhandled_irq
    jmp $

    cli
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs



    ;jmp _asm_reboot
    ;call _xxxe1000handler

    ;call _acpiHandler

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    sti
    iretq

;;==========================================



;========================================================
; IRQ 10  The Interrupt is left open for the use 
; of peripherals (open interrupt/available, SCSI or NIC)
; nvidia

; Capture context
global _irq10
_irq10:

    ;; #test
    jmp unhandled_irq
    jmp $

    cli
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    ;call _KiPciHandler1

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    sti
    iretq

;;==========================================


;;===============================================
;;  interrupção 41. irq 9;

; Capture context
global _nic_handler
_nic_handler:
    
    cli
    
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    ;call _irq_E1000

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    out 0x20, al

    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    sti
    iretd

;==================

;=======================================
; IRQ 11 - The Interrupt is left open for 
; the use of peripherals (open interrupt/available, SCSI or NIC)
; audio.

; Capture context
global _irq11
_irq11:

    ;; #test
    jmp unhandled_irq
    jmp $

    cli
    ;pushad
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    ;call _KiPciHandler2

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    ;popad
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax


    sti
    iretq

;===================


;=======================================
; IRQ 12 - mouse on PS/2 connector
; See: /i8042/mouse.c

extern _irq12_MOUSE

; Capture context
global _irq12
_irq12:

    cli
; Acumulator.
    push rax

    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs
    push rsp
    pushfq
    cld

; See: 
; mouse.c

    fxsave [__hw_fpu_buffer]

    call _irq12_MOUSE

    fxrstor [__hw_fpu_buffer]

    popfq
    pop rsp
    pop gs
    pop fs
    ;pop es
    ;pop ds

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

;EOI order: Second, first.

    mov al, 0x20
    out 0xA0, al 
    IODELAY 
    out 0x20, al
    IODELAY 

;The acumulator.
    pop rax

    sti
    iretq
;;=================


;;============================================================	
; IRQ 13 
; CPU co-processor  or  integrated floating point unit  
; or  inter-processor interrupt (use depends on OS)
;

; Capture context
global _irq13
_irq13:

    ;; #test
    jmp unhandled_irq
    jmp $

    cli

    ;push ax 
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs



    ;call _coprocessorHandler

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    ;pop ax
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax


    sti
    iretq

;==========================================


;============================================
; _irq14:
;     Tratador de interrupções para unidade master.
;     IRQ 14 - primary ATA channel 
;     ( ATA interface usually serves hard disk drives and CD drives ) 
;     O timer precisa ser desbilitado. ??

extern _irq14_PRIMARY_IDE

; Capture context
global _irq14
_irq14:
   
    cli 
    
    ;push eax
    ;PUSHAD
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    fxsave [__hw_fpu_buffer]

    call _irq14_PRIMARY_IDE

    fxrstor [__hw_fpu_buffer]



    ;; EOI.
    ;; Order: Second, first.
    MOV AL,020h
    OUT 0A0h,AL
    IODELAY
    IODELAY  
    OUT 020h,AL
    IODELAY
    IODELAY  
    
    ;POPAD
    ;pop eax
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    sti

    IRETQ    
    

;=================================================	
; _irq15:
;     Tratador de interrupções para unidade slave.
;     IRQ 15 - secondary ATA channel
;     O timer precisa ser desbilitado. ??

;; The correct way to handle an IRQ 15 is similar, but a little trickier 
;; due to the interaction between the slave PIC and the master PIC. 
;; First check the slave PIC chip's ISR to see if the IRQ is a spurious 
;; IRQ or a real IRQ. If it is a real IRQ then it is treated the same 
;; as any other real IRQ. If it's a spurious IRQ then don't send the 
;; EOI to the slave PIC; however you will still need to send the EOI 
;; to the master PIC because the master PIC itself won't know that it 
;; was a spurious IRQ from the slave. 

extern _irq15_SECONDARY_IDE

; Capture context
global _irq15
_irq15:

    cli
    
    ;push eax
    ;PUSHAD
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    
    ;push ds
    ;push es
    push fs
    push gs


    fxsave [__hw_fpu_buffer]

    call _irq15_SECONDARY_IDE

    fxrstor [__hw_fpu_buffer]


    ;; #bugbug
    ;; #todo
    ;; Spurious int for irq15.
    ;; It's different from irq7

    ;; EOI.
    ;; Order: Second, first.
    MOV AL, 020h
    OUT 0A0h, AL
    IODELAY
    IODELAY  
    OUT 020h, AL
    IODELAY
    IODELAY  
    
    
    ;POPAD
    ;pop eax
    pop gs
    pop fs
    ;pop es
    ;pop ds
    
    ;#bugbug
    ;#todo: Pop the registers.
    ;popad
    
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    
    sti
    IRETQ

; =======================












;========================================
; unhandled_irq:
;     Interrupção de hardware genérica. 
;++ 

;; #bugbug
;; Não podemos efetuar EOI para todos 
;; somente para as irqs.

extern _faults

unhandled_irq:

    cli
    push rax


    ;#debug
    ;call _faults

    mov al, 0x20
    
    out 0xA0, al
    IODELAY  
    IODELAY  
    
    out 0x20, al
    IODELAY
    IODELAY  

    pop rax
    sti 

    iretq
;--


align 8

;----------------------------

; Building trampolines for the faults.

; int 0 
global _fault_N0
_fault_N0:
    mov qword [_save_fault_number], qword 0
    jmp all_faults

; int 1 
global _fault_N1
_fault_N1:
     mov qword [_save_fault_number], qword 1
    jmp all_faults

; int 2 
global _fault_N2
_fault_N2:
    mov qword [_save_fault_number], qword 2
    jmp all_faults

; int 3 
global _fault_N3
_fault_N3:
    mov qword [_save_fault_number], qword 3
    jmp all_faults

; int 4 
global _fault_N4
_fault_N4:
    mov qword [_save_fault_number], qword 4
    jmp all_faults

; int 5 
global _fault_N5
_fault_N5:
     mov qword [_save_fault_number], qword 5
    jmp all_faults

; #todo: Change this name.
; int 6 - Instrução inválida.
global _fault_INTRUCAO_INVALIDA
_fault_INTRUCAO_INVALIDA:
    mov qword [_save_fault_number], qword 6
    jmp all_faults

; int 7
global _fault_N7
_fault_N7:
    mov qword [_save_fault_number], qword 7
    jmp all_faults

; int 8 - double fault
global _fault_DOUBLE
_fault_DOUBLE:
    mov qword [_save_fault_number], qword 8
    jmp all_faults

; int 9 
global _fault_N9
_fault_N9:
    mov qword [_save_fault_number], qword 9
    jmp all_faults

; int 10 
global _fault_N10
_fault_N10:
    mov qword [_save_fault_number], qword 10
    jmp all_faults

; int 11
global _fault_N11
_fault_N11:
    mov qword [_save_fault_number], qword 11
    jmp all_faults

; int 12 - Falha de pilha (interrupção 12).
global _fault_STACK
_fault_STACK:
    mov qword [_save_fault_number], qword 12
    jmp all_faults

; int 13 - general protection fault (GPF).
global _fault_GP
_fault_GP:   
    mov qword [_save_fault_number], qword 13
    jmp all_faults

; int 14 - Page Fault (PF).
; #todo:
; The hardware pushes a stack frame with the context and generate
; an error code describing the error.
global _fault_N14
_fault_N14:
    mov qword [_save_fault_number], qword 14
    jmp all_faults

; int 15 
global _fault_N15
_fault_N15:
    mov qword [_save_fault_number], qword 15
    jmp all_faults

; int 16 
global _fault_N16
_fault_N16:
    mov qword [_save_fault_number], qword 16
    jmp all_faults

; int 17 
global _fault_N17
_fault_N17:
    mov qword [_save_fault_number], qword 17
    jmp all_faults

; int 18
global _fault_N18
_fault_N18:
    mov qword [_save_fault_number], qword 18
    jmp all_faults

; int 19
global _fault_N19
_fault_N19:
    mov qword [_save_fault_number], qword 19
    jmp all_faults

; int 20 
global _fault_N20
_fault_N20:
    mov qword [_save_fault_number], qword 20
    jmp all_faults

; int 21
global _fault_N21
_fault_N21:
    mov qword [_save_fault_number], qword 21
    jmp all_faults

; int 22
global _fault_N22
_fault_N22:
    mov qword [_save_fault_number], qword 22
    jmp all_faults

; int 23 
global _fault_N23
_fault_N23:
    mov qword [_save_fault_number], qword 23
    jmp all_faults

; int 24 
global _fault_N24
_fault_N24:
    mov qword [_save_fault_number], qword 24
    jmp all_faults

; int 25 
global _fault_N25
_fault_N25:
    mov qword [_save_fault_number], qword 25
    jmp all_faults

; int 26 
global _fault_N26
_fault_N26:
    mov qword [_save_fault_number], qword 26
    jmp all_faults

; int 27 
global _fault_N27
_fault_N27:
    mov qword [_save_fault_number], qword 27
    jmp all_faults

; int 28 
global _fault_N28
_fault_N28:
    mov qword [_save_fault_number], qword 28
    jmp all_faults

; int 29
global _fault_N29
_fault_N29:
    mov qword [_save_fault_number], qword 29
    jmp all_faults

; int 30
global _fault_N30
_fault_N30:
    mov qword [_save_fault_number], qword 30
    jmp all_faults

; int 31 
global _fault_N31
_fault_N31:
    mov qword [_save_fault_number], qword 31
    jmp all_faults


;---------------------------------------
; One trampoline above jumps here.
; rdi for first parameter.
; New calling conventions for x86_64.
; Chama código em C. 
; (x64fault.c)

; #todo
; Temos que salvar o contexto,
; pois vamos retornar após alguns tipos de fault,
; como é o caso de PF.

extern _faults

all_faults:

; Save context.

    cli

    pop qword [_contextRIP]     ; rip
    pop qword [_contextCS]      ; cs
    pop qword [_contextRFLAGS]  ; rflags
    pop qword [_contextRSP]     ; rsp
    pop qword [_contextSS]      ; ss

    mov qword [_contextRDX], rdx 
    mov qword [_contextRCX], rcx 
    mov qword [_contextRBX], rbx 
    mov qword [_contextRAX], rax

    mov qword [_contextRBP], rbp

    mov qword [_contextRDI], rdi 
    mov qword [_contextRSI], rsi 

; Segments

    xor rax, rax
    
    ; Is it used?
    mov ax, gs
    mov word [_contextGS], ax
    ; Is it used?
    mov ax, fs
    mov word [_contextFS], ax
    
    mov ax, es
    mov word [_contextES], ax
    mov ax, ds
    mov word [_contextDS], ax

    ; cpl
    ; see: x64cont.c

    mov rax, qword [_contextCS]
    and rax, 3
    mov [_contextCPL], rax


; Call c routine in x64fault.c.
    mov rax, qword [_save_fault_number]
    mov rdi, rax 
    call _faults 

; #todo
; We're gonna restore the execution in some cases,
; just like PF.

; Release a bandit.
    ;jmp unit3Irq0Release
    
; Provisório
_AllFaultsHang:
    cli
    hlt
    jmp _AllFaultsHang



; Salva aqui o número da fault.	
global _save_fault_number
_save_fault_number: 
    dq 0
    
align 8




