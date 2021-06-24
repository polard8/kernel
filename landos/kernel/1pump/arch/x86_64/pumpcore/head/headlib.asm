

headlib_something:
	ret




;=================================================
; setup_idt:
;     Configura a IDT.
;     Dado o endereço da IDT, 
;     preenche todos os vetores, 
;     apontando para um só endereço. 'unhandled_int'.
;     See: sw.asm
;++

;; called by xxxhead.asm

setup_idt:

;     See: sw.asm

    ;pushad
    push rax
    push rcx
    push rdx
    
    ; #todo: x86_64: 64bit address
    mov rdx, qword unhandled_int  

    ; low 16 
    mov rax, rdx 
    mov word  [d_offset_15_0],  ax
 
    ; high 16
    mov rax, rdx
    shr rax, 16
    mov word  [d_offset_31_16], ax

    ; high 32
    mov rax, rdx
    shr rax, 32
    mov dword [d_offset_63_32], eax

 
    ;; Isso forma os primeiros 32bit da entrada.
    ;; (offset low and selector)
    ;mov eax, dword 0x00080000     ; Step1: selector = 0x0008 = cs  na parte alta.
    ;mov ax, dx                   ; Step2: uma parte do endereço na parte baixa (16 bits)
    ;mov ax, word  [d_offset_15_0] ; Step2: uma parte do endereço na parte baixa (16 bits)


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
    
    ;interrupt gate - dpl=0, present
    ;mov dx, word 0x8E00

    ;; Use this one.
    ;; obs: 0xEE00 tem funcionado bem para todos os casos.
    ;mov dx, word 0xEE00

    ;; The pointer. 64bit address
    mov rdi, qword _idt

    ;; The counter.
    mov rcx, qword 256

; loop
rp_sidt:

    ;; #bugbug
    ;; Nao sei se essa operação eh possivel,
    ;; mas queremos mover de double em double

    ;==========================
    ; Primeiros 32 bits. 
    ; (offset low and selector)
    xor rax, rax
    mov eax, dword 0x00080000     ; Step1: selector = 0x0008 = cs  na parte alta.
    mov ax, word  [d_offset_15_0] ; Step2: uma parte do endereço na parte baixa (16 bits)
    mov dword [rdi+0], eax   

    ;=========================================
    ; segundos 32 bit.
    xor rax, rax
    mov ax, word [d_offset_31_16]
    shl rax, 16
    mov ax, word 0xEE00
    mov dword [rdi+4], eax   

    ;=========================================
    ; terceiros 32 bit.
    xor rax, rax
    mov eax, dword [d_offset_63_32]
    mov dword [rdi+8], eax

    ;=========================================
    ; quartos 32 bit.
    xor rax, rax
    mov dword [rdi+12], eax

    ;; done: go to next

    add  rdi, qword 16    ;;  vai pra proxima entrada.
    dec rcx               ;;  decrementa o contador.

    jne rp_sidt           ;; circula


    ; #bugbug
    ; No. We will do this later.
    ; lidt [IDT_register]

    pop rdx
    pop rcx
    pop rax
    ;popad

    ret
;Offset address used in the function above.
d_offset_15_0:  dw 0
d_offset_31_16: dw 0
d_offset_63_32: dd 0
;;--
;;====================================




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


    push rax
    push rbx
    push rcx
    push rdx


    ; Endereço e índice na tabela.

    mov qword [d__address], rax    ;endereço. 64bit
    mov qword  [d__number], rbx    ;número do vetor.


    ; Calcula o deslocamaneto
    xor rax, rax
    mov rax, qword  16
    mov rbx, qword [d__number]
    mul rbx
    ; O resuldado está em rax.


    ; Adiciona o deslocamento à base rdi.
    ; A base é o início da idt.
    mov rdi, qword _idt               
    add rdi, rax   ; lembra? O resultado estava em rax.

    ; Agora rdi contém o endereço de memória
    ; dentro da idt, onde desejamos contruir a entrada.

;
; Lidando com o endereço.
;

    ; Salva o endereço de 64bi em rdx.
    mov rdx, qword [d__address] 

    ; low 16 
    mov rax, rdx 
    mov word  [address_offset_15_0],  ax
 
    ; high 16
    mov rax, rdx
    shr rax, 16
    mov word  [address_offset_31_16], ax

    ; high 32
    mov rax, rdx
    shr rax, 32
    mov dword [address_offset_63_32], eax



   ;------------------

    ; Lembre-se: 
    ; rdi contém o endereço de memória
    ; dentro da idt, onde desejamos contruir a entrada.

    ;; #bugbug
    ;; Nao sei se essa operação eh possivel,
    ;; mas queremos mover de double em double

    ;==========================
    ; Primeiros 32 bits. 
    ; (offset low and selector)
    xor rax, rax
    mov eax, dword 0x00080000     ; Step1: selector = 0x0008 = cs  na parte alta.
    mov ax, word  [address_offset_15_0] ; Step2: uma parte do endereço na parte baixa (16 bits)
    mov dword [rdi+0], eax   

    ;=========================================
    ; segundos 32 bit.
    xor rax, rax
    mov ax, word [address_offset_31_16]
    shl rax, 16
    mov ax, word 0xEE00
    mov dword [rdi+4], eax   

    ;=========================================
    ; terceiros 32 bit.
    xor rax, rax
    mov eax, dword [address_offset_63_32]
    mov dword [rdi+8], eax

    ;=========================================
    ; quartos 32 bit.
    xor rax, rax
    mov dword [rdi+12], eax

   ;-----------------

    ; Do not load.
    ;recarrega a nova idt
    ;lidt [IDT_register]

    pop rdx
    pop rcx
    pop rbx
    pop rax

    ret

d__address:  dq 0
d__number:   dq 0
;Offset address used in the function above.
address_offset_15_0:  dw 0
address_offset_31_16: dw 0
address_offset_63_32: dd 0
;;--



;=============================================
; setup_faults:
;    Configura vetores da idt para faults.
;

setup_faults:

    push rax
    push rbx

    ;#0  
    mov rax, qword _fault_N0
    mov rbx, qword 0
    call _setup_system_interrupt

    ;#1  
    mov rax, qword _fault_N1
    mov rbx, qword 1
    call _setup_system_interrupt

    ;#2  
    mov rax, qword _fault_N2
    mov rbx, qword 2
    call _setup_system_interrupt

    ;#3  debug
    mov rax, qword _fault_N3
    mov rbx, qword 3
    call _setup_system_interrupt

    ;#4  
    mov rax, qword _fault_N4
    mov rbx, qword 4
    call _setup_system_interrupt

    ;#5  
    mov rax, qword _fault_N5
    mov rbx, qword 5
    call _setup_system_interrupt

    ;#6 - Instrução inválida.
    mov rax, qword _fault_INTRUCAO_INVALIDA
    mov rbx, qword 6
    call _setup_system_interrupt

    ;#7  
    mov rax, qword _fault_N7
    mov rbx, qword 7
    call _setup_system_interrupt

    ;#8 - double fault
    mov rax, qword _fault_DOUBLE
    mov rbx, qword 8
    call _setup_system_interrupt

    ;#9  
    mov rax, qword _fault_N9
    mov rbx, qword 9
    call _setup_system_interrupt

    ;#10  
    mov rax, qword _fault_N10
    mov rbx, qword 10
    call _setup_system_interrupt

    ;#11  
    mov rax, qword _fault_N11
    mov rbx, qword 11
    call _setup_system_interrupt

    ;#12 - stack
    mov rax, qword _fault_STACK
    mov rbx, qword 12
    call _setup_system_interrupt

    ;#13 - general protection
    mov rax, qword _fault_GP
    mov rbx, qword 13
    call _setup_system_interrupt

    ;#14  
    mov rax, qword _fault_N14
    mov rbx, qword 14
    call _setup_system_interrupt

    ;#15 
    mov rax, qword _fault_N15
    mov rbx, qword 15
    call _setup_system_interrupt

    ;#16 
    mov rax, qword _fault_N16
    mov rbx, qword 16
    call _setup_system_interrupt

    ;#17  
    mov rax, qword _fault_N17
    mov rbx, qword 17
    call _setup_system_interrupt

    ;#18  
    mov rax, qword _fault_N18
    mov rbx, qword 18
    call _setup_system_interrupt

    ;#19  
    mov rax, qword _fault_N19
    mov rbx, qword 19
    call _setup_system_interrupt

    ;#20  
    mov rax, qword _fault_N20
    mov rbx, qword 20
    call _setup_system_interrupt

    ;#21  
    mov rax, qword _fault_N21
    mov rbx, qword 21
    call _setup_system_interrupt

    ;#22  
    mov rax, qword _fault_N22
    mov rbx, qword 22
    call _setup_system_interrupt

    ;#23 
    mov rax, qword _fault_N23
    mov rbx, qword 23
    call _setup_system_interrupt

    ;#24  
    mov rax, qword _fault_N24
    mov rbx, qword 24
    call _setup_system_interrupt

    ;#25  
    mov rax, qword _fault_N25
    mov rbx, qword 25
    call _setup_system_interrupt

    ;#26 
    mov rax, qword _fault_N26
    mov rbx, qword 26
    call _setup_system_interrupt

    ;#27  
    mov rax, qword _fault_N27
    mov rbx, qword 27
    call _setup_system_interrupt

    ;#28 
    mov rax, qword _fault_N28
    mov rbx, qword 28
    call _setup_system_interrupt

    ;#29  
    mov rax, qword _fault_N29
    mov rbx, qword 29
    call _setup_system_interrupt

    ;#30  
    mov rax, qword _fault_N30
    mov rbx, qword 30
    call _setup_system_interrupt

    ;#31 
    mov rax, qword _fault_N31
    mov rbx, qword 31
    call _setup_system_interrupt

    pop rbx
    pop rax
    
    ret

;=====================================
; setup_vectors:
;
;     Setup some IDT vectors.
;

setup_vectors:

    push rax
    push rbx 




    ; 32 - Timer.
    ; Iniciamos um timer provisório, depois o main() inicia o definitivo.
    mov rax,  qword unhandled_irq
    ;mov rax,  qword  _irq0 
    mov rbx,  qword 32
    call _setup_system_interrupt


    ; 33 - Keyboard.
    ; #todo: The ps2 is not initialized yet.
    ;mov rax,  qword unhandled_irq 
    mov rax,  qword _irq1
    mov rbx,  qword 33
    call _setup_system_interrupt
    
    
    
    

    ; 40 - Clock, rtc.
    mov rax,  qword unhandled_irq ; _irq8
    mov rbx,  qword 40
    call _setup_system_interrupt

    ; 44 - Mouse.
    mov rax,  qword unhandled_irq ; _irq12
    mov rbx,  qword 44
    call _setup_system_interrupt

    ; 46 - ide
    mov rax,  qword unhandled_irq ; _irq14 
    mov rbx,  qword 46
    call _setup_system_interrupt

    ; 47 - ide
    mov rax,  qword unhandled_irq ; _irq15 
    mov rbx,  qword 47
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
    ;mov eax,  dword _int129
    ;mov ebx,  dword 129
    ;call _setup_system_interrupt  

    ;; 0x82
    ;mov eax,  dword _int130
    ;mov ebx,  dword 130
    ;call _setup_system_interrupt  

    ;; ...

    ;; =====================
    
    ;; #test
    ;; Uma interrupção para habilitar as interrupções mascaráveis.
    ;; quem usará isso será a thread primária do processo init.
    ;; apenas uma vez.
    
    ;mov eax,  dword _int199
    ;mov ebx,  dword 199
    ;call _setup_system_interrupt  

    ;; ...

    pop rbx
    pop rax

    ret





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

    xor rax, rax

    in al, 0x64
    test al, 00000010b
    ; Loop
    jne _asm_reboot

    mov al, 0xFE
    out 0x64, al

    ; #bugbug
    ; Com halt, sem loop.
    hlt
    
    jmp _asm_reboot
;; =================================















