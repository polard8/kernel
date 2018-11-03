;
; File: msm\pm.inc
;
;     +Enable Protected Mode with no Paging.
;
; Segments:
;    DS = stage2_DATA_SEL  
;    ES = stage2_DATA_SEL
;
; Stack:
;    Segment = stage2_DATA_SEL
;    Offset  = 0x0009FFFC
; 
; Registers:
;    AL  = New initialization mode.
;    EBX = ECX = EDX = 0.
;
; Histórico:
;     Versão: 1.0, 2015 - Adaptado de versões antigas.
;     Versão: 1.0, Oct 2016 - Revisão.
;     ...
;


 
 msg_BUGBUG DB 'pmInit: #BUGBUG ENTRANDO NO MODO PROTEGIDO.',0
 

;====================================================================
; pmInit:
;     Switching to Protected Mode.
;     Obs: Talvez essa rotina deva receber argumentos. 
;     *Na inicialização essa rotina é chamada em modo texto.
;
pmInit:

    ;
	; @todo: Salva o metafile com todos os parametros 
	; detectados em modo real.
	;
	
	;call save_metafile

		
 	;
	; Pega o modo no metafile e poe em BL.
	; retorno em 'AL'.
	;
	
	call get_boot_mode  
	xor bx, bx
	mov bl, al    ;Salva em bl.
	
	
	pusha
    call Window.StatusBar
    mov si, msg_BUGBUG
    call PoeString
    popa	
	
	;debug
	;jmp $

    ; Configurando segmentos.
	
	cli
	
	;Data.
	mov  ax, 0        
    mov  ds, ax
    mov  es, ax
	;mov  fs, ax    ;Unused       
	;mov  gs, ax    ;Unused    
	
	;Stack.
	;STACK_POINTER
	;Reconfigurando no mesmo lugar de antes.
	
	XOR AX, AX
    mov ss, ax
    mov sp, 0x6000 
	
	;General purpose.
	xor ax, ax
	xor bx, bx ;; #bugbug Isso suja o boot mode salvo em bl.
	xor cx, cx
	xor dx, dx
	 
	;;
	;; GDTR
	;;
	
	;Carrega o gdtr do stage 2.	
	lgdt [stage2_gdtr]

	;;
	;; CR0 - PE
	;;
	
	;Muda PE.
	mov eax, cr0
    or al, 1
    mov cr0, eax
	
	;;
	;; Flush pipeline.
	;;
	
	;CS.
pmFlushPipeline:
    jmp stage2_CODE_SEL:pm32 
	
	;;
	;; ## 32 BIT START ##
	;;
	
	[BITS 32]
pm32:

    ;debug em modo texto.
    ;mov byte [0B8000h], byte 'P'
    ;jmp $

	
	;;
	;; ## Inicalizando modo de boot ##
	;;
	
	; Salva o boot mode em um endereço de 32 bits.
	; #bugbug: O bl foi zerado um pouco antes.
	; Provavelmente podemos deletar isso.
	; É preciso conferir se não usamos essa variável 
	; logo a frente.
	
	; Aqui estamos selecionando o modo '0'.
	mov byte [BOOT.modo], bl

	;;
	;; Reconfigurando registradores.
	;;

	;
	; @todo: 
	;    Talvez dê para passar outras coisas através dos 
	; registradores b,c,d.
	; Obs: 
	;     A pilha está bem perto do diretório do kernel. ??.
	;     Stack = 0x0009FFFC
	;     Directory = 9C000.  
	;
	
	;;
	;; Segmentos
	;;
	
	;Segmentos de dados e pilha.
    mov ax, stage2_DATA_SEL        
	mov ds, ax
	mov es, ax
	;mov fs, stage2_NULL_SEL    ;0.
	;mov gs, stage2_NULL_SEL    ;0.
	
	;;
	;; Pilha
	;;
	
	mov ss, ax
	mov esp, dword 0x0009FFFC
	
	;;
	;; Uso geral.
	;;
	
	;Zera os registradores.		
    mov edx, dword 0    ;#Voice,8?!
    mov ecx, dword 0
	mov ebx, dword 0	
    mov eax, dword 0    ;#Voice,14?!
	;
.GoToStart:
    nop
	; Mostra Msg se estivermos em modo texto.
.debug_textmode:    
    mov byte [0B8000h], byte 'P'
    mov byte [0B8001h], byte 7
	mov byte [0B8002h], byte 'M'
	mov byte [0B8003h], byte 7
	
	;jmp $
.debug_graphicmode:	
    nop    ;;Obs: Não testar aqui o modo gráfico.
	;jmp $
.do_start:
    
	; set IOPL to zero and reset all flags
	;push 0x00000002
	;popfd

	; initialize the math coprocessor
	;finit
	;fwait

	; enable PMC in userspace
	;mov eax, cr4
	;or eax, 0x100
	;mov cr4, eax
	
		
	;;
	;; IMPORTANTE: A ROTINA PARA VOLTAR PARA O MODO REAL E EXECUTAR UM SERVIÇO, FUNCIONOU CORRETAMENTE,
	;; MAS NÃO SERÁ CHAMADA NESSE MOMENTO.
	;;
	
	;
	; start:
	; Inicia o modo escolhido que foi salvo em 'BOOT.modo'.
	; IN: AL = Boot mode.
	; #bugbug podemos ter um proble nessa variável BOOT BOOT.modo.
    ;	
	mov al, byte [BOOT.modo]	
	JMP start
	JMP $
	

pmMsg1 db "[BM:] Starting PM in gm in Assembly..", 13,10,0	
	
;
; Contexto dos registradores após o JMP para o start.
; ==================================================	
;
; Segments:
;    DS = stage2_DATA_SEL  
;    ES = stage2_DATA_SEL
;
; Stack:
;    Segment = stage2_DATA_SEL
;    Offset  = 0x0009FFFC
;
; Registers:
;    AL  = New initialization mode.
;    EBX = ECX = EDX = 0.
;


;;
;;    ****    Voltando para o Modo Real.    ****
;;

;;
;; O que segue são rotinas de funções que serão chamadas do modo protegido
;; e serão atendidas com recursos do BIOS.
;; @todo: Os ponteiros para essas funções devem ser passados para o boot loader.
;; na verdade podemos passar um ponteiro para uma tabela de ponteiros. Cada
;; ponteiro do bloco será um ponteiro para uma rotina que atende serviços
;; usando recursos do bios. Esse bloco fica bem aqui.
;;

;;Essa tabela precisa ser inicializada.
;rm_services_block:
;    .shutdown dd 0     ;<<----- rmShutdown
;	;...


;;
;; 'rm' será a classe de funções que efetuam um serviço em modo real,
;; sendo chamadas do modo protegido.
;;

	
;;===========================================================
;; rmShutdown
;;     Desliga a máquina fica APM. Não tem argumentos. 
;;     Obs: Estamos usando a gdt do módulo de 32 bit        
;;
rmShutdown:
    mov ax, DATA_SEL    
	mov ds,ax
	mov es,ax
	;mov fs,ax
	;mov gs,ax
	mov ss,ax
	mov esp, dword 0x0009FFFC

    ;;
	;; *Importante:
	;; Daqui pra frente não usaremos mais o seletor para 32bit, somente 
	;; o seletor para modo protegido de 16bit.
	;;
	
    ;;Pula para o o modo protegido de 16bit, usando o seletor de 16bit.
	jmp RM_Code_Sel:pmode_16bit
[BITS 16]	
pmode_16bit:
    ; ajusta os seletores de codigo para modo protegido de 16 bits.
	mov	ax, RM_Data_Sel
	mov	ss, ax
	mov	ds, ax
	mov	es, ax
	;mov	fs, ax
	;mov	gs, ax

	lidt [ivtr_rm]  	;Carrega ivt = 0:0
	
;5. Clear the PE flag in the CR0 register to switch to real-address mode.
   mov eax, cr0
   and al, 0xFE
   mov cr0, eax
   
;#############################################################################
;6. Execute a far JMP instruction to jump to a real-address mode program. 
; This operation flushes the instruction queue and loads the appropriate 
; base and access rights values in the CS register.

    ;; Usando um jmp de 16 bits modo real.
	JMP 0:do_rm 	
    ;;
do_rm:
    
	;7. Load the SS, DS, ES, FS, and GS registers as needed by the 
	; real-address mode code. If any of the registers are not going 
	; to be used in real-address mode, write 0s to them.
	
	cli
    mov ax, 0x0000        ;;segmento 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; Create stack
    mov ax, 0x0000
    mov ss, ax
    mov sp, 0xFFFF
	
	;Reprogram PIC: 
	;change IRQ 0-7 to INT 08h-0Fh, and  
	;       IRQ 8-15 to INT 70h-77h

    mov al, 10001b       ; begin PIC 1 initialization
    out 20h, al
    mov al, 10001b       ; begin PIC 2 initialization
    out 0A0h, al
	
    mov al, 08h          ; IRQ 0-7: back to ints 8h-Fh
    out 21h, al
	
    mov al, 70h          ; IRQ 8-15: back to ints 70h-77h
    out 0A1h, al
	
    mov al, 100b         ; slave connected to IRQ2
    out 21h, al
    mov al, 2
    out 0A1h, al
    mov al, 1            ; Intel environment, manual EOI
    out 21h, al
    out 0A1h, al
    in al, 21h
	
	;Mask off all interrupts for now. 
	;PERMITE TODAS AS INTS.
	mov	al, 0		
	out	0x21, al
	out	0xA1, al
	
    sti    ;enable interrupts

.enableTextMode:	
	;set text mode
    mov   ax,0x0003      ; set text mode for screen
    int   0x10

	 ;*Importante:
	 ;Mensagem em modo real.
 	
	mov si, rm_shutdown_msg1
	call DisplayMessage	
	
.stop:
    ; wait for a key	
    xor AX, AX    
    int 16h
	
	;Another message.
	;mov si, rm_shutdown_msg1
	;call DisplayMessage	

.doShutdown:
	call stage2Shutdown
	jmp $
	
;;Mensagens para a rotina de shut down.	
rm_shutdown_msg1 db 'pm.inc: RM, Press a key to shutdown',13,10,0		
;rm_shutdown_msg2 db '*',13,10,0
;rm_shutdown_msg3 db '.',13,10,0
;rm_shutdown_msg4 db '.',13,10,0
;...

;; Temos que mdar para 32bit [bits 32]
;; para não estragar codigos subsequêntes.			
[bits 32]   



;;
;; =========================================================================
;;	

;;=================================================================================
;; rmStartGUI:
;;     Inicializa o modo gráfico padrão.
;;     Essa rotina poderá ser chamada pelo shell em 32 bit modo texto,
;; que está dentro do boot manager. 
;;     Obs: Estamos usando a gdt do módulo de 32 bit      
;;
;; *******   IMPORTANTE *********
;; CONSEGUIMOS QUE O MBR CARREGASSE O BL.BIN DO DIRETÓRIO RAIZ
;; DO SISTEMA DE ARQUIVOS FAT16 E TAMBEM CARREGASSE O STAGE 2,
;; ENTÃO NÃO DEVEMOS CARREGAR NOVAMENTE O BL.BIN USANDO RECURSOS DE 32BIT,
;; E ESSA É A INTENSÃO ... O QUE NOS RESTA É PASSAR O COMANDO PARA ELE.
;; OBS: PODEMOS FAZER UM TESTE ANTES PRA VER SE ELE ESTÁ PRESENTE NA MEMÓRIA.
;;; 'L' (PE).          
;;
rmStartGUI:
    mov ax, DATA_SEL    
	mov ds,ax
	mov es,ax
	;mov fs,ax
	;mov gs,ax
	mov ss,ax
	mov esp, dword 0x0009FFFC
	

    ;;
	;; *Importante:
	;; Daqui pra frente não usaremos mais o seletor para 32bit, somente 
	;; o seletor para modo protegido de 16bit.
	;;
	
    ;;Pula para o o modo protegido de 16bit, usando o seletor de 16bit.
	jmp RM_Code_Sel:pmode_16bit_startgui
[BITS 16]	
pmode_16bit_startgui:
    ; ajusta os seletores de codigo para modo protegido de 16 bits.
	mov	ax, RM_Data_Sel
	mov	ss, ax
	mov	ds, ax
	mov	es, ax
	;mov	fs, ax
	;mov	gs, ax
	
	
	;debug
	;jmp $
	

	lidt [ivtr_rm]  	;Carrega ivt = 0:0
	
;5. Clear the PE flag in the CR0 register to switch to real-address mode.
   mov eax, cr0
   and al, 0xFE
   mov cr0, eax
   
;#############################################################################
;6. Execute a far JMP instruction to jump to a real-address mode program. 
; This operation flushes the instruction queue and loads the appropriate 
; base and access rights values in the CS register.

    ;; Usando um jmp de 16 bits modo real.
	JMP 0:do_rm_startgui 	
    ;;
do_rm_startgui:
    
	;7. Load the SS, DS, ES, FS, and GS registers as needed by the 
	; real-address mode code. If any of the registers are not going 
	; to be used in real-address mode, write 0s to them.
	
	cli
    mov ax, 0x0000        ;;segmento 0
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; Create stack
    mov ax, 0x0000
    mov ss, ax
    mov sp, 0xFFFF
	
	;Reprogram PIC: 
	;change IRQ 0-7 to INT 08h-0Fh, and  
	;       IRQ 8-15 to INT 70h-77h

    mov al, 10001b       ; begin PIC 1 initialization
    out 20h, al
    mov al, 10001b       ; begin PIC 2 initialization
    out 0A0h, al
	
    mov al, 08h          ; IRQ 0-7: back to ints 8h-Fh
    out 21h, al
	
    mov al, 70h          ; IRQ 8-15: back to ints 70h-77h
    out 0A1h, al
	
    mov al, 100b         ; slave connected to IRQ2
    out 21h, al
    mov al, 2
    out 0A1h, al
    mov al, 1            ; Intel environment, manual EOI
    out 21h, al
    out 0A1h, al
    in al, 21h
	
	;Mask off all interrupts for now. 
	;PERMITE TODAS AS INTS.
	mov	al, 0		
	out	0x21, al
	out	0xA1, al
	
    sti    ;enable interrupts

.enableTextMode:	
	;set text mode
    mov   ax,0x0003      ; set text mode for screen
    int   0x10

	 ;*Importante:
	 ;Mensagem em modo real.
 	
	mov si, rm_startgui_msg1
	call DisplayMessage	
	
.stop:
    ; wait for a key	
    xor AX, AX    
    int 16h

.doStartGUI:
	;Set mode.
	mov al, byte BOOTMODE_GUI
	call set_boot_mode

	mov word [META$FILE.VIDEO_MODE], 0x115   
	;mov ax, 0x115
	;call set_video_mode	
    
	;Inicializa o modo selecionado.
	JMP s2modesActivateMode    ;(lib16\s2modes.inc) 
	jmp $
	
;;Mensagens para a rotina de shut down.	
rm_startgui_msg1 db 'pm.inc: RM, Press a key to start GUI',13,10,0		
;rm_startgui_msg2 db '*',13,10,0
;rm_startgui_msg3 db '.',13,10,0
;rm_startgui_msg4 db '.',13,10,0
;...

;; Temos que mdar para 32bit [bits 32]
;; para não estragar codigos subsequêntes.			
[bits 32]   	
	
;
;End.
;


















