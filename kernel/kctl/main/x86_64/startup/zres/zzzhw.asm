;
; File: x86/pumpcore/hw.inc 
;
; Descrição:
;     Interrupções de hardware.
;     Irqs e interrupções reservadas (faults,etc).
;     Ordem: Primeiro as irqs, depois as outras.
;
; History:
;     2015 - Created by Fred Nora.
;


;; See:
;; https://wiki.osdev.org/8259_PIC#Spurious_IRQs
;;


;; from interwebs: "
;; There are several reasons for the interrupt to disappear. 
;; In my experience the most common reason is software sending an 
;; EOI at the wrong time. Other reasons include noise on IRQ lines
;; (or the INTR line). "

;; For a spurious IRQ, there is no real IRQ and the PIC chip's 
;; ISR (In Service Register) flag for the corresponding IRQ will 
;; not be set. 
;; This means that the interrupt handler must not send an EOI back to 
;; the PIC to reset the ISR flag. 

;; Also note that some operating systems (e.g. Linux) 
;; keep track of the number of spurious IRQs that have occurred 
;; (e.g. by incrementing a counter when a spurious IRQ occurs). 
;; This can be useful for detecting problems in software 
;; (e.g. sending EOIs at the wrong time) and detecting problems in
;; hardware (e.g. line noise). 



;;
;; == Imports =======================================
;;


;;
;; == IRQs =======================================
;;

;; See: pic.h

extern _irq0_TIMER
extern _irq1_KEYBOARD 
extern _irq8_RTC
extern _irq_E1000
extern _irq12_MOUSE
extern _irq_SHARED0
extern _irq_SHARED1
extern _irq_SHARED2
extern _irq_SHARED3
extern _irq14_PRIMARY_IDE
extern _irq15_SECONDARY_IDE


;;
;; == Task switch =======================================
;;


;; It is used bu the irq0.
extern _psTaskSwitch 


;; @todo:
;;?? Em que arquivo está essa função ??
extern _current_process_pagedirectory_address
;;...



;;=====================================================
;;  ## TIMER ##
;;=====================================================
;; _irq0: 
;;
;; IRQ 0. 
;; Timer interrupt handler
;;
;; See:
;; 1pump/arch/x86/pit.c
;; 0mem/core/ps/disp/ts.c
;;

; extern _irq0PendingEOI

global _irq0
_irq0:

    cli
    
    ; No caso do dispatcher lançar uma nova thread,
    ; então ele deve acionar enviar um EIO.
    ; mov dword [_irq0PendingEOI], 1

    ;; == Save context ====================
    
    ;; Stack frame. (all double)
    pop dword [_contextEIP]     ; eip
    pop dword [_contextCS]      ; cs
    pop dword [_contextEFLAGS]  ; eflags
    pop dword [_contextESP]     ; esp
    pop dword [_contextSS]      ; ss

    mov dword [_contextEDX], edx 
    mov dword [_contextECX], ecx 
    mov dword [_contextEBX], ebx 
    mov dword [_contextEAX], eax 
    mov dword [_contextEBP], ebp 
    mov dword [_contextEDI], edi 
    mov dword [_contextESI], esi 

    ; Segments
    xor eax, eax
    mov ax, gs
    mov word [_contextGS], ax
    mov ax, fs
    mov word [_contextFS], ax
    mov ax, es
    mov word [_contextES], ax
    mov ax, ds
    mov word [_contextDS], ax

    ;; #todo
    ;; Media, float pointers, debug.

    ;; #important:
    ;; We are using the kernel segment registers.
    ;; Kernel data segments and stack.
    ;; #bugbug: sempre a mesma pilha?
    ;; Que pilha as interrupçoes de softwar estao usando?

    xor eax, eax
    mov ax, word KERNEL_DS
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov eax, 0x003FFFF0 
    mov esp, eax

    ;; Timer support. No task switch.
    call _irq0_TIMER

    ;; Task switching.
    call _psTaskSwitch

    ;Flush TLB.
    jmp dummy_flush
    ;; NOP
dummy_flush:
    mov EAX, CR3  
    IODELAY 
    nop
    nop
    nop
    nop
    nop
    mov CR3, EAX  

    ;; == Restore context ====================

    ; Segments
    xor eax, eax
    mov ax, word [_contextDS]
    mov ds, ax
    mov ax, word [_contextES]
    mov es, ax
    mov ax, word [_contextFS]
    mov fs, ax
    mov ax, word [_contextGS]
    mov gs, ax

    mov esi, dword [_contextESI] 
    mov edi, dword [_contextEDI] 
    mov ebp, dword [_contextEBP] 
    mov eax, dword [_contextEAX] 
    mov ebx, dword [_contextEBX] 
    mov ecx, dword [_contextECX] 
    mov edx, dword [_contextEDX] 

    ;; Stack frame. (all double)
    push dword [_contextSS]      ; ss
    push dword [_contextESP]     ; esp
    push dword [_contextEFLAGS]  ; eflags
    push dword [_contextCS]      ; cs
    push dword [_contextEIP]     ; eip

    ; EOI - Only the first PIC.
    mov al, 20h
    out 20h, al  
    IODELAY  

    ;; variável usada pelo dispatcher.
    ;mov dword [_irq0PendingEOI], 0


    ; Acumulator.
    mov eax, dword [_contextEAX]

    ;; #bugbug
    ;; We do NOT need the 'sti'. 
    ;; The flags in the 'eflags' will reenable it.
    ;; sti

    iretd


;;==========================================
; _timer_test:
;     Timer sem multitarefas. 
;     (usado antes de acionar a multitarefa)
;

global _timer_test
_timer_test:
    jmp unhandled_irq
    jmp $

timer_interrupt:
    jmp unhandled_irq
    jmp $




;; ??
;; #todo:
;; Move these thing to another place.

_currentTask:
    dd 0
_nextTask:
    dd 0
_stackPointers: 
    times 512 dd 0    ;;@todo: Isso é útil ?





;========================================
; _irq1:
;     IRQ 1 - Keyboard.
;
; See:
; 2io/dev/tty/chardev/hid/i8042/keyboard.c
;

global _irq1  
_irq1:

    cli

    ;; Acumulator.
    push dword eax

    pushad
    push ds
    push es
    push fs
    push gs

    ;; Kernel data segments
    xor eax, eax
    mov ax, word KERNEL_DS 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ;; #bugbug:
    ;; The stack.

    call _irq1_KEYBOARD

    pop gs
    pop fs
    pop es
    pop ds
    popad

    ; send EOI to XT keyboard
    ;in      al, 061h
    ;mov     ah, al
    ;or      al, 080h
    ;out     061h, al
    ;mov     al, ah
    ;out     061h, al

    ;; EOI - Only the first PIC.
    xor eax, eax 
    MOV AL, 020h
    OUT 020h, AL
    IODELAY  
    
    ;; The acumulator.
    pop eax

    sti
    iretd



;=======================================
; _irq2 - IRQ 2 – cascaded signals from IRQs 8–15 
; (any devices configured to use IRQ 2 will actually be using IRQ 9)
;
; Nothing.
;



;=======================================================
; IRQ 3 - serial port controller for serial port 2 
; (shared with serial port 4, if present)
; See: serial.c

extern _serial2_handler
extern _serial4_handler

global _irq3
_irq3:

    cli
    pushad

    call _serial2_handler
    ;call _serial4_handler

    ;; EOI - Only the first PIC.
    mov al, 0x20
    out 0x20, al
    IODELAY  
    
    popad
    sti
    iretd



;====================================================
; IRQ 4 - serial port controller for serial port 1 
;(shared with serial port 3, if present)
; See: serial.c

extern _serial1_handler
extern _serial3_handler

global _irq4
_irq4:

    cli
    pushad

    call _serial1_handler
    ;call _serial3_handler

    ;; EOI - Only the first PIC.
    mov al, 0x20
    out 0x20, al
    IODELAY  
    
    popad
    sti
    iretd



;--------------
; IRQ 5 - parallel port 2 and 3  or  sound card
;_irq5:
;    iretd



;--------------
; IRQ 6 – floppy disk controller
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



global _irq7
_irq7:

    cli
    pushad

    ;call _first_parallel_port_Handler

    ;; ++
    ;; ================================================
    ;; #test
    ;; Testing the spurious interrupt management.

    xor eax, eax
    mov  al, 03h                ; PIC.OCW3 set function to read ISR (In Service Register)
    out  23h, al                ; write to PIC.OCW3 master
    in   al, 20h                ; read ISR master.
    test al, 80h                ; if the in-service register does not have IR7 bit set
    jz short __RETURN_Spurious  ; this would be a spurious interrupt.
    
    ;; ================================================
    ;; --

;; Not spurious

    ;; EOI. Master.
    ;; for irq7
    mov al, 0x20
    out 0x20, al   
    IODELAY  
    
__RETURN_Spurious:

    ;; No eoi for irq 7 spurious
    
    popad
    sti
    iretd




;================================================
; _irq8:
;     System CMOS, Realtime clock.
;     IRQ 8 - real-time clock (RTC)
;

global _irq8
_irq8:

    cli
    pushad

    call _irq8_RTC

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    popad
    sti
    iret



;=========================================================
; IRQ 9

extern _xxxe1000handler

global _irq9
_irq9:
    
    ;; #test
    jmp unhandled_irq
    jmp $

    cli
    pushad

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
    
    popad
    sti
    iretd


;========================================================
; IRQ 10 – The Interrupt is left open for the use 
; of peripherals (open interrupt/available, SCSI or NIC)
; nvidia

global _irq10
_irq10:

    ;; #test
    jmp unhandled_irq
    jmp $

    cli
    pushad

    ;call _KiPciHandler1

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    popad
    sti
    iretd


;;===============================================
;;  interrupção 41. irq 9;

global _nic_handler
_nic_handler:
    cli
    pushad

    call _irq_E1000

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    out 0x20, al

    popad
    sti
    iretd


;=======================================
; IRQ 11 - The Interrupt is left open for 
; the use of peripherals (open interrupt/available, SCSI or NIC)
; audio.
global _irq11
_irq11:

    ;; #test
    jmp unhandled_irq
    jmp $

    cli
    pushad

    ;call _KiPciHandler2

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    popad
    sti

    iretd



;=======================================
; IRQ 12 - mouse on PS/2 connector
;
; See:
; 2io/dev/tty/chardev/hid/i8042/mouse.c
;

global _irq12
_irq12:

    cli

    pushad
    push ds
    push es
    push fs
    push gs
    push ss 

    call _irq12_MOUSE

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    
    out 0xA0, al 
    IODELAY 
    
    out 0x20, al
    IODELAY 

    pop ss
    pop gs 
    pop fs 
    pop es 
    pop ds
    popad

    sti
    iretd



;;============================================================	
; IRQ 13 
; CPU co-processor  or  integrated floating point unit  
; or  inter-processor interrupt (use depends on OS)
;

global _irq13
_irq13:

    ;; #test
    jmp unhandled_irq
    jmp $

    cli
    push ax 

    ;call _coprocessorHandler

    ;; EOI.
    ;; Order: Second, first.
    mov al, 0x20
    out 0xA0, al  
    IODELAY  
    out 0x20, al
    IODELAY  
    
    pop ax
    sti

    iretd


;=================================================	
; _irq14:
;     Tratador de interrupções para unidade master.
;     IRQ 14 - primary ATA channel 
;     ( ATA interface usually serves hard disk drives and CD drives ) 
;     O timer precisa ser desbilitado. ??
;


global _irq14
_irq14:
   
    cli 
    push eax
    PUSHAD

    call _irq14_PRIMARY_IDE

    ;; EOI.
    ;; Order: Second, first.
    MOV AL,020h
    OUT 0A0h,AL
    IODELAY
    IODELAY  
    OUT 020h,AL
    IODELAY
    IODELAY  
    
    POPAD
    pop eax
    sti

    IRETD


;=================================================	
; _irq15:
;     Tratador de interrupções para unidade slave.
;     IRQ 15 - secondary ATA channel
;     O timer precisa ser desbilitado. ??
;

;; The correct way to handle an IRQ 15 is similar, but a little trickier 
;; due to the interaction between the slave PIC and the master PIC. 
;; First check the slave PIC chip's ISR to see if the IRQ is a spurious 
;; IRQ or a real IRQ. If it is a real IRQ then it is treated the same 
;; as any other real IRQ. If it's a spurious IRQ then don't send the 
;; EOI to the slave PIC; however you will still need to send the EOI 
;; to the master PIC because the master PIC itself won't know that it 
;; was a spurious IRQ from the slave. 



global _irq15
_irq15:

    cli
    push eax
    PUSHAD

    call _irq15_SECONDARY_IDE
    
    
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
    POPAD
    pop eax
    sti

    IRETD


;========================================
; unhandled_irq:
;     Interrupção de hardware genérica. 
;++ 

;; #bugbug
;; Não podemos efetuar EOI para todos 
;; somente para as irqs.

unhandled_irq:

    cli
    ;pushad  ;;#todo
    push eax

    mov al, 0x20
    out 0xA0, al
    IODELAY  
    IODELAY  
    out 0x20, al
    IODELAY
    IODELAY  

    pop eax
    ;popad;;#todo
    sti 

    iretd
;--


;;
;; == # FAULTS # ================ 
;;


; Tratamento das faltas.


extern _faults

;
; Obs: Enquanto tratamos uma excessão ou flaul, não desejamos
; que uma interrupção de timer atrapalhe, então vamos desabilitar
; as interrupções.
;

;
; int 0 
global _fault_N0
_fault_N0:
    mov dword [save_fault_number], dword 0
    jmp all_faults

;
; int 1 
global _fault_N1
_fault_N1:
     mov dword [save_fault_number], dword 1
    jmp all_faults

;
; int 2 
global _fault_N2
_fault_N2:
    mov dword [save_fault_number], dword 2
    jmp all_faults

;
; int 3 
global _fault_N3
_fault_N3:
    mov dword [save_fault_number], dword 3
    jmp all_faults

;
; int 4 
global _fault_N4
_fault_N4:
    mov dword [save_fault_number], dword 4
    jmp all_faults


;
; int 5 
global _fault_N5
_fault_N5:
     mov dword [save_fault_number], dword 5
    jmp all_faults

;
; int 6 - Instrução inválida.
global _fault_INTRUCAO_INVALIDA
_fault_INTRUCAO_INVALIDA:
    mov dword [save_fault_number], dword 6
    jmp all_faults

;
; int 7
global _fault_N7
_fault_N7:
    mov dword [save_fault_number], dword 7
    jmp all_faults

;
; int 8 - double fault
global _fault_DOUBLE
_fault_DOUBLE:
    mov dword [save_fault_number], dword 8
    jmp all_faults

;
; int 9 
global _fault_N9
_fault_N9:
    mov dword [save_fault_number], dword 9
    jmp all_faults

;
; int 10 
global _fault_N10
_fault_N10:
    mov dword [save_fault_number], dword 10
    jmp all_faults

;
; int 11
global _fault_N11
_fault_N11:
    mov dword [save_fault_number], dword 11
    jmp all_faults

;
; int 12 - Falha de pilha (interrupção 12).
global _fault_STACK
_fault_STACK:
    mov dword [save_fault_number], dword 12
    jmp all_faults

;
; int 13 - general protection fault (GPF).
global _fault_GP
_fault_GP:   
    mov dword [save_fault_number], dword 13
    jmp all_faults

;
; int 14 - Page Fault (PF).
global _fault_N14
_fault_N14:
    mov dword [save_fault_number], dword 14
    jmp all_faults

;
; int 15 
global _fault_N15
_fault_N15:
    mov dword [save_fault_number], dword 15
    jmp all_faults

;
; int 16 
global _fault_N16
_fault_N16:
    mov dword [save_fault_number], dword 16
    jmp all_faults

;
; int 17 
global _fault_N17
_fault_N17:
    mov dword [save_fault_number], dword 17
    jmp all_faults

;
; int 18
global _fault_N18
_fault_N18:
    mov dword [save_fault_number], dword 18
    jmp all_faults

;
; int 19
global _fault_N19
_fault_N19:
    mov dword [save_fault_number], dword 19
    jmp all_faults

;
; int 20 
global _fault_N20
_fault_N20:
    mov dword [save_fault_number], dword 20
    jmp all_faults

;
; int 21
global _fault_N21
_fault_N21:
    mov dword [save_fault_number], dword 21
    jmp all_faults

;
; int 22
global _fault_N22
_fault_N22:
    mov dword [save_fault_number], dword 22
    jmp all_faults

;
; int 23 
global _fault_N23
_fault_N23:
    mov dword [save_fault_number], dword 23
    jmp all_faults

;
; int 24 
global _fault_N24
_fault_N24:
    mov dword [save_fault_number], dword 24
    jmp all_faults

;
; int 25 
global _fault_N25
_fault_N25:
    mov dword [save_fault_number], dword 25
    jmp all_faults

;
; int 26 
global _fault_N26
_fault_N26:
    mov dword [save_fault_number], dword 26
    jmp all_faults

;
; int 27 
global _fault_N27
_fault_N27:
    mov dword [save_fault_number], dword 27
    jmp all_faults

;
; int 28 
global _fault_N28
_fault_N28:
    mov dword [save_fault_number], dword 28
    jmp all_faults

;
; int 29
global _fault_N29
_fault_N29:
    mov dword [save_fault_number], dword 29
    jmp all_faults

;
; int 30
global _fault_N30
_fault_N30:
    mov dword [save_fault_number], dword 30
    jmp all_faults

;
; int 31 
global _fault_N31
_fault_N31:
    mov dword [save_fault_number], dword 31
    jmp all_faults


;===============================================
; all_faults:
;     As faltas são tratadas em kernel mode, tem que ajustar 
; os registradores para isso.
;     
; #todo: 
; Enviar o número a falta para uma variável global.
; Essa rotina poderia se chamar hwAllFaults.
;

;; Pushing an error code (for some exceptions): 
;; For some specific exceptions such as page faults, 
;; the CPU pushes an error code, which describes the cause of the exception.

all_faults:

	;d,c,b,a
	mov dword [_contextEDX], edx
	mov dword [_contextECX], ecx
	mov dword [_contextEBX], ebx
	mov dword [_contextEAX], eax

	;ebp,edi,esi
	mov eax, ebp
	mov dword [_contextEBP], eax
	mov eax, edi
	mov dword [_contextEDI], eax
	mov eax, esi
	mov dword [_contextESI], eax

    ;gs, fs, es, ds
    xor eax, eax
    mov ax, gs
    mov word [_contextGS], ax
    mov ax, fs
    mov word [_contextFS], ax
    mov ax, es
    mov word [_contextES], ax
    mov ax, ds
    mov word [_contextDS], ax

	;(DOUBLE), eip, cs, eflags, esp, ss 
    
    ; #bugbug: 
    ; No caso de der falha no primeiro salto para ring3:
    ; Pegamos esses valores da pilha.
    ; Mas precisamos saber se esses valores refletem
    ; a parte do código que estava executando na hora da falha,
    ; ou se é o valor configurado antes do primeiro salto para ring3.
    
	pop eax
	mov dword [_contextEIP], eax
	pop eax
	mov dword [_contextCS], eax
	pop eax
	mov dword [_contextEFLAGS], eax
	pop eax
	mov dword [_contextESP], eax
	pop eax
	mov dword [_contextSS], eax
    
    ;;
    ;; Reajustando os segmentos para rodarmos tranquilos em ring0.
    ;;
    
    ; Load the Kernel Data Segment descriptor.
    xor eax, eax
    mov ax, word KERNEL_DS   
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ;; ??
    ;; e a stack, ainda não tínhamos colocado uma configuração de
    ;; stack aqui.
    
    ;; #todo #todo #todo STACK STACK STACK

    
    ;;
    ;; O número da falta.
    ;;
    
    ; Chama a rotina em C.
    ;Passa o argumento via pilha.
    push dword [save_fault_number]

    ;Chama código em C. (faults.c)
    call _faults 

.hang:
    cli
    hlt
    jmp .hang


	; @todo: 
	;     Existe ERROR NUMBER em algumas exceções ?

;Salva aqui o número da fault.	
save_fault_number: 
    dd 0

;
; End.
;
