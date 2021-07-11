;
; File: x86/headlib.s 
;
; Descrição:
;     Funções auxiliares de supporte a head.s do Kernel Base.
;
; History:
;     2015 - Created by Fred Nora.
;     ...
;

;
; Global variables.
;


;Se o kernel está inicializado ou não.
global _KernelStatus
_KernelStatus: 
    dd 0


;Variável sera usada pelo scheduler.
global _task_switch_salva_esp
_task_switch_salva_esp: 
    dd 0


;
; Variáveis locais.
;

current:       dd 0    ;current.
scr_loc:       dd 0    ;coisa da memória de vídeo.
bl_video_mode: db 0 
bl_lfb:        db 0  


;
; #todo:
; Nota sobre a pilha em ring0 configurada na tss:
; O valor atual é 0x00200000. Mas não é o que queremos,
; o que queremos é o equivalente físico à 0xC03FFFF0.
; Que seria (0x00100000 + 3FFFF0).
; O problema é que temos um aplicativo começando no 
; endereço físico 0x400000. Com isso a pilha sujaria
; o aplicativo.
; É necessário que o gerenciamento de memória física
; aloque memória física para os aplicativos em algum
; pool de memória física padronizado.
;
;

;
; TSS. 
;
;;como se a task fantasma estivesse em ring0.
ring0_ghost_task:
    jmp $

;============================================================
;tss0

;; #bugbug
;; o backlink tem 16bit ?? e os outros 16 são reservados ??
;; ?? o que é isso. ??

dd 0
dd 0
tss0:
	dd 0                    ;back link (0x401000)
	dd 0x003FFFF0           ;esp0    (pilha do kernel), endereço físico.
	dd 0x10                 ;ss0     (ss da pilha do kernel)
	dd 0                    ;esp1
	dd 0                    ;ss1
	dd 0                    ;esp2
	dd 0                    ;ss2
	dd 0x9C000              ;cr3  #bugbug: Isso deve ser o cr3 do processo em ring3.
	dd ring0_ghost_task     ;eip  ;0x401000  
	dd 0x00000200           ;eflags  (CPL = 3, interrupções habilitadas) ;0x00003200
	dd 0                    ;eax
	dd 0                    ;ecx
	dd 0                    ;edx
	dd 0                    ;ebx
	dd 0x0044FFF0           ;esp   (stack em user mode) (;;0x43ffff)
	dd 0                    ;ebp
	dd 0                    ;esi
	dd 0                    ;edi
	dd 0x10                 ;es  ;0x23 
	dd 0xB                  ;cs  ;0x1B 
	dd 0x10                 ;ss  ;0x23
	dd 0x10                 ;ds  ;0x23
	dd 0x10                 ;fs  ;0x23
	dd 0x10                 ;gs  ;0x23 
	dw LDT_TEST_SEL, 0      ;LDT, reserved
	dw 0, tss0_iopb - tss0  ;debug, IO permission bitmap (none)
tss0_iopb:
    times 8192 db 0FFh    ;#bugbug: Isso é realmente necessário.
tss0_end:



;=====================================================
;tss1
dd 0
dd 0
tss1:
	dd 0x401000             ;back link  _task0 #bugbug 
	dd 0x003FFFF0           ;esp0    (pilha do kernel), endereço físico.
	dd 0x10                 ;ss0      (ss da pilha do kernel)   
	dd 0                    ;esp1
	dd 0                    ;ss1
	dd 0                    ;esp2
	dd 0                    ;ss2
	dd 0x9C000              ;cr3 #bugbug: Isso deve ser o cr3 do processo em ring3.
	dd 0x401000             ;eip   
	dd 0x00003200           ;eflags  (CPL = 3, interrupções habilitadas)
	dd 0                    ;eax
	dd 0                    ;ecx
	dd 0                    ;edx
	dd 0                    ;ebx
	dd 0x0044FFF0           ;esp (stack em user mode) ;;0x43ffff
	dd 0                    ;ebp
	dd 0                    ;esi
	dd 0                    ;edi
	dd 0x23                 ;es 
	dd 0x1B                 ;cs 
	dd 0x23                 ;ss
	dd 0x23                 ;ds
	dd 0x23                 ;fs
	dd 0x23                 ;gs 
	dw LDT_TEST_SEL, 0      ;LDT, reserved
	dw 0, tss1_iopb - tss1  ;debug, IO permission bitmap (none)	
tss1_iopb:
    times 8192 db 0FFh      ;#todo: Isso é realmente necessário.?
tss1_end:
;;--


;;
;; == LDTs ============================================
;;

 
;
;ldt 0.
dd 0
dd 0
ldt0:
	dq 0x0000000000000000    ;null 
	dq 0x00c0fa01000003ff    ;0x0f, base = 0x10000
	dq 0x00c0f201000003ff    ;0x17

;
;ldt 1.
dd 0
dd 0
ldt1:
	dq 0x0000000000000000   ;null
	dq 0x00c0fa01000003ff   ;0x0f, base = 0x10000
    dq 0x00c0f201000003ff   ;0x17
;;--




;;==================================================================
; _setup_system_interrupt: 
;
;    Configura um vetor da IDT para a interrupção do sistema. 
;    O endereço do ISR e o número do vetor são passados via argumento.
;
; IN:
;    eax = endereço. (callback)(endereço do handler)
;    ebx = número do vetor (0x80).(número da interrupção.)
;

global _setup_system_interrupt
_setup_system_interrupt:

    pushad

    mov dword [.address], eax    ;endereço.
    mov dword  [.number], ebx    ;número do vetor.

    ;Calcula o deslocamaneto
    mov eax, dword 8
    mov ebx, dword [.number]
    mul ebx
    ;resuldado em eax

    ;Adiciona o deslocamento à base.
    mov edi, dword _idt               
    add edi, eax

    mov edx, dword [.address] 

    mov eax, dword 0x00080000    ; /* selector = 0x001B = user cs */
    mov ax, dx                   ; uma parte do endereço
    mov dx, word 0xEE00          ; /* interrupt gate - dpl=3, present */

    ;Coloca o vetor na idt
    mov dword [edi+0], eax
    mov dword [edi+4], edx

    ; Do not load.
    ;recarrega a nova idt
    ;lidt [IDT_register]

    popad
    ret

.address:  dd 0
.number:   dd 0
;;--


;=============================================
; setup_faults:
;    Configura vetores da idt para faults.
;

setup_faults:

    push eax
    push ebx

	;#0  
    mov eax, dword _fault_N0
    mov ebx, dword 0
    call _setup_system_interrupt

	;#1  
    mov eax, dword _fault_N1
    mov ebx, dword 1
    call _setup_system_interrupt

	;#2  
	mov eax, dword _fault_N2
	mov ebx, dword 2
	call _setup_system_interrupt
	
	;#3  
	mov eax, dword _fault_N3
	mov ebx, dword 3
	call _setup_system_interrupt

	;#4  
	mov eax, dword _fault_N4
	mov ebx, dword 4
	call _setup_system_interrupt
	
	;#5  
	mov eax, dword _fault_N5
	mov ebx, dword 5
	call _setup_system_interrupt	

	;#6 - Instrução inválida.
	mov eax, dword _fault_INTRUCAO_INVALIDA
	mov ebx, dword 6
	call _setup_system_interrupt
	
	;#7  
	mov eax, dword _fault_N7
	mov ebx, dword 7
	call _setup_system_interrupt
	
	;#8 - double fault
	mov eax, dword _fault_DOUBLE
	mov ebx, dword 8
	call _setup_system_interrupt	
	
	;#9  
	mov eax, dword _fault_N9
	mov ebx, dword 9
	call _setup_system_interrupt

	;#10  
	mov eax, dword _fault_N10
	mov ebx, dword 10
	call _setup_system_interrupt

	;#11  
	mov eax, dword _fault_N11
	mov ebx, dword 11
	call _setup_system_interrupt
	
	;#12 - stack
	mov eax, dword _fault_STACK
	mov ebx, dword 12
	call _setup_system_interrupt		
	
	;#13 - general protection
	mov eax, dword _fault_GP
	mov ebx, dword 13
	call _setup_system_interrupt	
	
	;#14  
	mov eax, dword _fault_N14
	mov ebx, dword 14
	call _setup_system_interrupt	

	;#15 
	mov eax, dword _fault_N15
	mov ebx, dword 15
	call _setup_system_interrupt	

	;#16 
	mov eax, dword _fault_N16
	mov ebx, dword 16
	call _setup_system_interrupt	

	;#17  
	mov eax, dword _fault_N17
	mov ebx, dword 17
	call _setup_system_interrupt	

	;#18  
	mov eax, dword _fault_N18
	mov ebx, dword 18
	call _setup_system_interrupt	

	;#19  
	mov eax, dword _fault_N19
	mov ebx, dword 19
	call _setup_system_interrupt	

	;#20  
	mov eax, dword _fault_N20
	mov ebx, dword 20
	call _setup_system_interrupt	

	;#21  
	mov eax, dword _fault_N21
	mov ebx, dword 21
	call _setup_system_interrupt	

	;#22  
	mov eax, dword _fault_N22
	mov ebx, dword 22
	call _setup_system_interrupt	

	;#23 
	mov eax, dword _fault_N23
	mov ebx, dword 23
	call _setup_system_interrupt	

	;#24  
	mov eax, dword _fault_N24
	mov ebx, dword 24
	call _setup_system_interrupt	

	;#25  
	mov eax, dword _fault_N25
	mov ebx, dword 25
	call _setup_system_interrupt	

	;#26 
	mov eax, dword _fault_N26
	mov ebx, dword 26
	call _setup_system_interrupt	

	;#27  
	mov eax, dword _fault_N27
	mov ebx, dword 27
	call _setup_system_interrupt	

	;#28 
	mov eax, dword _fault_N28
	mov ebx, dword 28
	call _setup_system_interrupt	

	;#29  
	mov eax, dword _fault_N29
	mov ebx, dword 29
	call _setup_system_interrupt	

	;#30  
	mov eax, dword _fault_N30
	mov ebx, dword 30
	call _setup_system_interrupt	

	;#31 
	mov eax, dword _fault_N31
	mov ebx, dword 31
	call _setup_system_interrupt

	pop ebx
	pop eax
    ret



;=====================================
; setup_vectors:
;
;     Setup some IDT vectors.
;

setup_vectors:

    push eax
    push ebx 

    ; 32 - Timer.
    ; Iniciamos um timer provisório, depois o main() inicia o definitivo.
    mov eax,  dword _timer_test    
    mov ebx,  dword 32
    call _setup_system_interrupt

    ; 33 - Keyboard.
    mov eax,  dword _irq1
    mov ebx,  dword 33
    call _setup_system_interrupt

    ; 40 - Clock, rtc.
    mov eax,  dword _irq8
    mov ebx,  dword 40
    call _setup_system_interrupt

    ; 44 - Mouse.
    mov eax,  dword _irq12
    mov ebx,  dword 44
    call _setup_system_interrupt

    ; 46 - ide
    mov eax,  dword _irq14 
    mov ebx,  dword 46
    call _setup_system_interrupt

    ; 47 - ide
    mov eax,  dword _irq15 
    mov ebx,  dword 47
    call _setup_system_interrupt

    ;;
    ;; == System calls ===========================
    ;;

    ; System interrupts
    ; 128 - 0x80
    ; 129 - 0x81
    ; 130 - 0x82
    ; ...

    ;; 0x80
    mov eax,  dword _int128
    mov ebx,  dword 128
    call _setup_system_interrupt  

    ;; 0x81
    mov eax,  dword _int129
    mov ebx,  dword 129
    call _setup_system_interrupt  

    ;; 0x82
    mov eax,  dword _int130
    mov ebx,  dword 130
    call _setup_system_interrupt  

    ;; ...

    ;; =====================
    
    ;; #test
    ;; Uma interrupção para habilitar as interrupções mascaráveis.
    ;; quem usará isso será a thread primária do processo init.
    ;; apenas uma vez.
    
    mov eax,  dword _int199
    mov ebx,  dword 199
    call _setup_system_interrupt  

    ;; ...

    pop ebx
    pop eax
    ret



;;=================================================
;;     # NIC #
;;
;; O kernel chma isso provisoriamente para criar uma entrada
;; na idt para o nic intel.
;;
;; #bugbug: isso está em nicintel.c , mas precisa ser global para que todos 
;; possam usar.
;; talvez em kernel.h
;; isso funcionou, tentar configurar outras interupções com isso.
;;

;; Isso foi declarado em nicintel.c
;;pegaremos o valor 41 e o endereço do handler.
extern _nic_idt_entry_new_number
extern _nic_idt_entry_new_address


global _asm_nic_create_new_idt_entry
_asm_nic_create_new_idt_entry:
	
	pushad

    ;; Isso é o endereço da rotina de handler, em assembly;
    ;; está em hw.asm
    ;; #bugbug: não usaremos o endereço enviado pois temos que configurar 
    ;; o EOI e a pilha da rotina de handler.
    mov eax, _nic_handler
	;mov eax, dword [_nic_idt_entry_new_address]

    ;; Isso é o número da interrupção. (41)
    mov ebx, dword [_nic_idt_entry_new_number]
    ;mov ebx, dword 41

	call _setup_system_interrupt
	
	;;#test: Não sei se precisa carregar novamente.
	;;ok, sem problemas.
	lidt [_IDT_register] 
	
	popad
	ret 



;;============================================
; set_base:
;     ??
; in: 
;    eax - logic addr.
;    ebx = base addr. 
;    ecx - table addr. 
;    edi - descriptors offset.
;

set_base:

    add eax, ebx
    add edi, ecx
    mov [edi+2], word ax

    ror eax, 16

    mov [edi + 4], al
    mov [edi +7],  ah
    ror eax, 16
    ret


;------------------------------------------------------------
; _x86_test_cpuid_support:
;
;     Testar via eflags se a cpu suporta a instrução cpuid. 
;     cpuid supported?
;

global _x86_test_cpuid_support
_x86_test_cpuid_support:

    pushfd                  ;push the flags onto the stack.
    pop eax                 ;pop them back out, into EAX.

    mov ebx, eax            ;keep original.

    xor eax, 00200000h      ;turn bit 21 on.

    push eax                ;put altered EAX on stack.
    popfd                   ;pop stack into flags.

    pushfd                  ;push flags back onto stack.
    pop eax                 ;put them back into EAX.
    
    cmp eax, ebx
    jnz _CPUID_SUPPORTED    ;COOL.
                
    mov eax, dword 1
    ;blah                   ;booo.
    stc
    RET
 
_CPUID_SUPPORTED:
    mov eax, dword 0
    clc 
    RET



;==============================================
; _get_page_dir:
;     Pega o valor de cr3.
;     page dir. 
;	  _headlibGetPageDirectoryAddress

global _get_page_dir
_get_page_dir:
    mov eax, cr3
    ret


;===========================================
; _set_page_dir:
;     configura o cr3
;     page dir. 
;     _headlibSetPageDirectoryAddress

global _set_page_dir
_set_page_dir:
    mov cr3, eax
    ret


;=============================================
; _get_page_fault_adr: 
;     Pega o cr2.
;     endereço quando da pagefault.
;

global _get_page_fault_adr
_get_page_fault_adr:
    mov eax, cr2
    ret



;;===============================================
;; __die:
;;
;;

global __die
__die:
    cli
    hlt
    jmp  __die



;;===============================================
; _halt:
;    Executa a instrução hlt.

global _halt
_halt:
    hlt
    ret



;;============================
;; Para ser usada por uma thread idle em ring 0, 
;; pois habilita as interrupções

global _idle_halt_cpu
_idle_halt_cpu:
    sti
    hlt
    jmp _idle_halt_cpu



;; =============================
;; flush TLB
global _hal_flush_tlb
_hal_flush_tlb:
    push eax
    mov eax, cr3
    ;; todo: delay ?
    ;; nop
    mov cr3, eax
    pop eax
    ret


global _arch_pause
_arch_pause:
    pause
    ret

global _interrupts_enable
_interrupts_enable:
    sti
    ret

global _interrupts_disable
_interrupts_disable:
    cli
    ret


;================================================
; setup_gdt:
;     Carrega gdtr.
;

setup_gdt:
    lgdt [_GDT_register]
    ret



;=================================================
; setup_idt:
;     Configura a IDT.
;     Dado o endereço da IDT, 
;     preenche todos os vetores, 
;     apontando para um só endereço. 'unhandled_int'.
;++

setup_idt:

    pushad
    mov edx, unhandled_int  

    mov eax, dword 0x00080000    ; selector = 0x0008 = cs 
    mov ax, dx                   ; uma parte do endereço
 
    ;; #test
    ;; Se a intenção é nos proteger
    ;; das interrupções de hardware inesperadas, então devemos
    ;; configurar a idt semelhante ao jeto que configuramos
    ;; para as irqs ... já que as interrupções de software
    ;; só ocorrerão depois de inicializadas as entradas para 
    ;; system call.
    ;; #importante: Porém não usaremos eoi ... e apontaremos
    ;; tudo para unhandled_int e não para umhandled_irq.
    ;; Ou seja, sem eoi.
    
    ;;obs: 0xEE00 tem funcionado bem para todos os casos.
 
    ;interrupt gate - dpl=0, present
    ;mov dx, word 0x8E00

    ;; Use this one.
    mov dx, word 0xEE00

    mov edi, dword _idt

    mov ecx, dword 256

rp_sidt:

    mov dword [edi+0], eax
    mov dword [edi+4], edx
    add  edi, dword 8
    dec ecx
    jne rp_sidt

	;#bugbug
	;lidt [IDT_register]	

    popad
    ret
;;--


;=====================================
; _setup_idt_vector:
;     Configura um vetor da IDT.
; IN:
; eax = endereço
; ebx = número do vetor
;

global _setup_idt_vector
_setup_idt_vector:

    ;cli
    pushad

    mov dword [.address], eax    ;endereço.
    mov dword [.number],  ebx    ;numero do vetor.

    ;calcula o deslocamaneto
    mov eax, dword 8
    mov ebx, dword [.number]
    mul ebx
    ;resuldado em eax

    ;adiciona o deslocamento à base.
    mov edi, dword _idt
    add edi, eax

    mov edx, dword [.address]

    mov eax, dword 0x00080000    ;/* selector = 0x0008 = cs */	
    mov ax, dx                   ;uma parte do endereço

    ;;para hardware
    mov dx, word 0xEE00

    ; coloca o vetor na idt
    mov dword [edi+0], eax
    mov dword [edi+4], edx

	;recarrega a nova idt
	;lidt [IDT_register]	

    popad
    ;sti
    ret
.address: dd 0
.number: dd 0


 
;=====================================
; _x86_enable_pse:
;     Enable PSE para páginas de 4MB.
;     Não usaremos isso.
;

global _x86_enable_pse
_x86_enable_pse:
    push eax
    mov eax, cr4
    or eax, 0x00000010
    mov cr4, eax
    pop eax
    ret


;=====================================
; _asm_shut_down:
; * shut down
; @todo: ainda não implementada.
;

global _asm_shut_down
_asm_shut_down:
    jmp _asm_reboot  ;;Errado.      
    jmp $



;=====================================
; _asm_reboot:
;
;     Reboot the system via ps2 keyboard.
;
; Steps:
; Wait for an empty Input Buffer.
; Send the reboot call to the keyboard controller.
;

global _asm_reboot
_asm_reboot:

    xor eax, eax

    in al, 0x64
    test al, 00000010b
    jne _asm_reboot

    mov al, 0xFE
    out 0x64, al

    hlt
    jmp _asm_reboot
;; =================================


;; ==================================
;; limpar a flag nt em eflags. 
;; e da refresh na pipeline.

global _x86_clear_nt_flag
_x86_clear_nt_flag:
    
    ; salvando o que vamos usar.
    push eax
    push ebx
    
    ; pegando as flags.
    pushfd
    pop eax
    mov ebx, 0x00004000
    not ebx
    and eax, ebx
    push eax
    popfd
    
    pop ebx
    pop eax
    
    ret
    


;
; End.
;
