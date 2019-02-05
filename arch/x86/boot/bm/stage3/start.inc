;-----------------------------------------------------
; File: stage3/start.inc 
;
; Descrição: 
;     Início do modo protegido. 
;     O modo protegido já foi configurado e começam aqui as rotinas em 32bit. 
;
; Atribuições: 
;     +Efetivar a escolha do modo de inicialização.
;     +Passar o comando para Shell do Boot Manager
;      se essa for a escolha.
;     +Carregar o Boot Loader e passar o comando 
;      pra ele se essa for a escolha.
;
; Opções de inicialização:
; ========================
; +1 - Inicia o Shell do Boot Manager no modo texto.
; +2 - Inicia o Boot Loader (BL.BIN) no modo GRÁFICO. (GUI).
;
; Contexto dos registradores:
; ===========================
; Segments:
;    DS  =  stage2_DATA_SEL  
;    ES  =  stage2_DATA_SEL
; Stack:
;    Segment  =  stage2_DATA_SEL
;    Offset   =  0x0009FFFC  ?? @todo: Cuidado.
; Registers:
;    AL  = new initialization mode.
;    EBX = 0
;    ECX = 0
;	 EDX = 0
;
; 2015 - Created by Fred Nora.
;


;=======================================================
; start:
;     Início do modo protegido.
; IN:
;     AL = New mode.  (o modo a ser inicializado)
;
; Pega o modo de vídeo passado pelo stage 2 através de AL e salva no contexto 
; de 32 bits.
;

start:	
    
	;; #bugbug 
	;; Esse valor pode estar errado durante 
	;; a inicialização em modo texto.
	
	mov byte [BOOT.modo], al			    
    
	xor edx, edx
	xor ecx, ecx
	xor ebx, ebx
	xor eax, eax
	
;	
; ajusta_modo: 
;     Inicia um modo da configuração permanente.	
;     @todo: Trocar o nome.
;

ajusta_modo:
    nop
	
startSetupMode:

	;; #bugbug 
	;; Esse valor pode estar errado durante 
	;; a inicialização em modo texto.

	;Pega o modo de inicialisação do Boot Manager. 
	
	xor eax, eax
	mov al, byte [BOOT.modo]  
	
	
	; Escolhe o modo:
	; ==============
	;
	; modo 1 - Inicia o BL.BIN no modo TEXTO.(Default).
	; modo 2 - Inicia o BL.BIN no modo GRÁFICO.
	; modo 3 - Inicia a prompt de comandos do bootmanager.
	; modo 4 - (reservado)
	; Default.
	
	cmp al, byte 1  
	je startCLI
	
	cmp al, byte 2  
	je startGUI	
	
	; Default mode.
	
.default:	
	jmp startCLI 
	;jmp $
	

;============================
; startCLI:	
;     Inicia o Shell do Boot Manager. 
;	
startCLI:
	
	call setup_machine
	
	;Segmentos e pilha.
	cli
	mov ax, word 0x10  
	mov ds, ax		 
	mov es, ax 
	mov eax, stack_ptr
	mov esp, eax 
	
	;Configura volume.
	;;?? onde ?? blconfig.inc
	
	mov al, byte 1
	call set_fs_volume  
	
	;Configura fs type.
	
	mov al, byte 1
	call set_fs_type
	
	;Limpa a tela em modo texto.
	call clear_screen
	
    ;Habilita todas interrupções.
.enableInterrupts:	
	
	mov al, 0					                  
	out 0xA1, al                                   
	out 0x21, al    
	sti 
	
    ;;
    ;;  ##  SHELL LOOP  ##
    ;;    

	;; #importante
	;; O shell está em msm/shell
	;; Esse é loop do shell do boot manager.
	
startShellLoop:	
    
	;;shell.inc
	call shellPrintShellVersion    
	
.shellInit:	
    
	;;shell.inc
	call shellInit                
    
	; Sairemos do loop.
    ; 0 - Nenhuma alteração foi feita, 
	; não precisa salvar o metafile.
	cmp eax, 0
	je .exit0

	; Sairemos do loop.
    ; 1 - Alguma alteração foi feita, 
	; precisa salvar o metafile.
	cmp eax, 1
	je .exit1
	
	jmp startShellLoop	
	JMP $

;	
;Saimos do loop do shell.
;Nenhuma alteração foi feita, não precisa salvar o metafile.
;Apenas reiniciamos o sistema.
.exit0:
	mov esi, start_msg_rebooting
	call os_output	
    jmp keyboardReboot
	jmp $

;	
;Saimos do loop do shell.
;Alguma alteração foi feita, precisamos salvar o metafile.
;Reiniciamos o sistema para validar as alterações feitas no metafile. 
.exit1:
	mov esi, start_msg_saving_metafile
	call os_output	
	;obs: Essa rotina deve ser realizada em 32bit.
    call fs32SaveMetafile ;@todo (fs\fs32.inc) 
	
	mov esi, start_msg_rebooting
	call os_output		
	jmp keyboardReboot
	jmp $	
	
	
start_msg_saving_metafile  db 'start: Saving metafile..',13,10,0
start_msg_rebooting        db 'start: Rebooting..',13,10,0
	
	
;==========================================================================
; startGUI:
;     Inicia o BL.BIN no modo gráfico.
;	  Obs: Quando retornamos para o modo real e ativamos o modo gráfico,
; satalmos para cá com a opção de usamos mensagens em modo gráfico em modo protegido.
;
;
;; * IMPORTANTE:
;;   O OBJETIVO É CHEGARMOS AQUI COM O ARQUIVO BL.BIN CARREGADO NA MEMÓRIA
;;   E PASSARMOS O COMANDO PARA ELE, SEM TERMOS QUE CARREGA LO USANDO RECURSOS DE 32BIT.

	;; *Importante:
	;; Fazendo configurações aqui mesmo ao invés de chamarmos 
	;; 'setup_machine' ou ainda não fazendo essas configurações, 
	;; pois já estamos em modo protegido com as interrupções 
	;; desabilitadas e em modo gráfico ..
	;; Podemos deixar que o boot loader faça suas inicializações. 
	;; Obs: Isso está funcionando bem.
	;; Mas o timer foi configurado várias vezes.

	;;===============
	;;setup machine

startGUI:

	cli
	
	;GDT and IDT. 
	lgdt [lgdt_opcode] 
	lidt [lidt_opcode]	
	
	;; @todo: Nessa hora alguns vetores podem ser configurados.
	;;        primeiro as excessões e depois as ISRs.
	;; Selecting the 'Processor Interrup Mode'.
	;; * PIC MODE *
    ;; Todos os componentes APIC são ignorados e o sistema opera
    ;; no modo single-thread usando LINT0.

;.setupPICMODE:	

	;PIC.
	cli
	mov al, 00010001b		;begin PIC 1 initialization.
	out 0x20, al
	mov al, 00010001b		;begin PIC 2 initialization.
	out 0xA0, al	
	mov al, 0x20			;IRQ 0-7: interrupts 20h-27h.
	out 0x21, al
	mov al, 0x28			;IRQ 8-15: interrupts 28h-2Fh.
	out 0xA1, al
	mov al, 4
	out 0x21, al
	mov al, 2
	out 0xA1, al
	mov al, 1
	out 0x21, al
	out 0xA1, al
	
	
	;;@todo:
	;;Init RTC.

	
	;;step 
    ;;@todo: memory caching control.	
	
	;;step 
	;processor Discovery and initialization
	;(cpuid threads and cores, start inter-processor interrupt sipi, ap wakeu pstate,
	;wakeup vector alignment, caching consdarations,ap idle state)	
	;apenas o básico para o boot manager.
	
		
	;;
	;; Fazendo alguma inicialização de dispositivos de I/O suportados.
	;;

	;step
	;i/o devices
	;( embedded controller EC, super io SIO, legacy free systems, miscellaneous io devices)
    ;Nesse momento os dispositivos de i/o suportados aqui são (keyboard, IDE, graphic card).
	
	;;
	;; #bugbug
	;; Cancelado.
	;; Não precisamos disso, pois vamos configurar o teclado 
	;; durante a inicialização do i8042 no kernel.
	;;	
	
	;KEYBOARD.
	;call keyboardInit		
	
	
	;IDE0.   #BUGUBG NO QEMU
	;;call init_ide0_master
	
		
	
	;LFB.   #BUGUBG NO QEMU
	;;call configura_lfb   ;;?? onde está essa rotina ??
	
	

	
	;
	; #BUGBUG
	; @todo:
	;     Aqui estamos usando constantes, porem esses valores precisam ser
	; detectados, pois variam à cada formatação.
	;
	
	;Detectar os parâmetros do sistema de arquivos FAT16.
	;fat lba, root lba ...
	;call fat16DetectFSParameters  ;;fat16lib.inc
	
	;Setup current dir.
    mov dword [g_current_fat_lba],        FAT16_FAT_LBA       ;Fat do volume atual
    mov dword [g_current_directory_lba],  FAT16_ROOTDIR_LBA   ;Diretório do volume atual.
	mov dword [g_current_dataarea_lba],   FAT16_DATAAREA_LBA  ;?? ;lba do inicio da area de dados do volume atual.
	;Continua...	
	

	
    ;; Configurando PCI. (O básico suportado pelo Boot Manager.)
	;; O boot manager está carregando o BL utilizando recursos 
	;; do BIOS em modo real. Mas se o BM fosse carregar o BL 
	;; de um dispositivo SATA em 32bit teria que configurar o PCI.
	;; (Se possível deixaremos para o BL o penoso trabalho de lidar
	;; com PCI, já que o BL é feito em C, isso deve ser mais fácil para
	;; o BL do que para o BM.)
	
	;step
	;;PCI device descovery.	

	
	;CURSOR.
	call reset_cursor 
	

	;
	; Continua ...
	;
	
	;mask all interrupts.
	
	cli 
	mov al, 255
	out 0xA1, al
	out 0x21, al		
	
	; setup registers.
	
	mov ax, word 0x10  
	mov ds, ax		 
	mov es, ax 
	mov eax, stack_ptr
	mov esp, eax 
	
	;Configura volume.
	mov al, byte 1
	call set_fs_volume
	
	;Configura fs type.
	mov al, byte 1
	call set_fs_type
	
	;;internas.
    ;Configura LFB e Buffer.
	call configura_lfb
	
	
    ;; #bugbug
    ;; Cancelando isso.
	;; Pois esses valores estão acima do limite de 16MB.
	;; Qualquer coisa para sistemas acima de 16MB serão 
	;; configuradas pelo kernel depois de detectar a 
	;; quantidade de memória.
	
    ;call configura_buffer
	
	;
	;se configurar o modo 3 não tem como 
	;reconfigurar atravez desse modo ainda.
	;entao salva modo 1
	;	
	;mov eax, dword 1
	;call blconfig_set_modo	
	;call do_save
	
	;@todo: Não é certo pintar um backgraund direto na memória de video.
    ;o Boot Manger não tem sincronização vertical ainda.	 
	 
	;background test!
    ;call _background
	;call _background_teste       
	;call _fade_screen
	;jmp $
	
	
	;;
	;; **** TESTING STRINGS ****
	;;
	
	;; bug bug as rotinas de 'char' 'string' e 'load' aparentemente
	;; estão travando o sistema, as duas janelas de status estão funcionando
	;; quando não chamamos essas funções.
	
	
	;
	; * Aqui vamos testar a rotina de mostrar strings no modo gráfico.
	;   O caractere deve ser construído, píxel por píxel, utilizando
	; o mapa de caracteres do BIOS.
	;
	
.testingStrings:
    nop
	;@todo: Testar rotina de mostrar uma string.
    

	;debug break
	;jmp $
	
	;Debug:
	;Pinta uma janela pra testar modo gráfico.
	
	;mov eax, 0    ;x.
	;mov ebx, 0    ;y.
	;mov ecx, 20   ;largura.
	;mov edx, 20   ;altura.	
    ;mov edi, dword  0x80808000    ;blue    	
	;call CreateWindow
	;call _asm_refresh_screen
	
  
    ;; #BUGBUG
    ;; O teste indicou que as rotinas de char e string estão
    ;; com mal funcionamento, travando o sistema.
    ;; a segunda janale não aparece que sinaliza prograsso não aparece.
  
  
    ;; @todo: Fazer debug da função print char antes de tudo ...
    ;; status: testando ...
  
;Char.
    ;
    ; a =  cor (rrggbbaa)
    ; b =  x
    ; c =  y
    ; d =  Char.
    ;	    
  
.TestingPrintChar:  
	
	;push eax
	;push ebx
	;push ecx 
	;push edx 
	;mov eax, 0x00ffff00  ;; Color
	;xor edx, edx 
	;mov dl, 'a'          ;; Caractere de teste.	
	;call lib32PrintChar	
	;pop edx 
	;pop ecx 
	;pop ebx 
	;pop eax 
	;call _asm_refresh_screen
	
	
	;push eax
	;push ebx
	;push ecx 
	;push edx 	
	;mov eax, 0x00ffff00  ;; Color
	;xor edx, edx 
	;mov dl, 'b'          ;; Caractere de teste.	
	;call lib32PrintChar	
	;pop edx 
	;pop ecx 
	;pop ebx 
	;pop eax 
    ;call _asm_refresh_screen


	;push eax
	;push ebx
	;push ecx 
	;push edx 
	;mov eax, 0x00ffff00  ;; Color
	;xor edx, edx 
	;mov dl, 'A'          ;; Caractere de teste.	
	;call lib32PrintChar	
	;pop edx 
	;pop ecx 
	;pop ebx 
	;pop eax 
    ;call _asm_refresh_screen

	;push eax
	;push ebx
	;push ecx 
	;push edx 
	;mov eax, 0x00ffff00  ;; Color
	;xor edx, edx 
	;mov dl, 'B'          ;; Caractere de teste.	
	;call lib32PrintChar	
	;pop edx 
	;pop ecx 
	;pop ebx 
	;pop eax 	
	;call _asm_refresh_screen
	
	;debug break
	;jmp $

.TestingPrintString:	
	
	;;Cursor.
	mov dword [g_cursor_x], 4
	mov dword [g_cursor_y], 4		
	
	;String
	;mov esi, msg_start_loading
	;call lib32PrintString
	;call _asm_refresh_screen	
	
  	;;debug
	mov esi, startMsgTest1   
	call lib32PrintString
    call _asm_refresh_screen
	;;jmp $	
	
	;
	; @todo: testando modos no geforce.
	;
    ;jmp $
	
    ;
	; @todo: 
	;     Não há funções de string em modo gráfico no bootmanager ainda.
	;     Então para o carregamento do BL.BIN não há mensagens.      
	;

	
	; Carrega o Boot Loader.
	; Carrega o arquivo  BL.BIN na memória e passa o comando para ele.
	; Enviando argumento em AL, e EBX.
	
.LoadBootLoader:	
	
    ;;;;
	;;;;    ****  ATENÇÃO   ****
	;;;;
	;;;; O BL.BIN FOI CARREGADO PELO MBR USANDO RECURSOS DO BIOS.
	;;;;  *NÃO* DEVEMOS CARREGA-LO NOVAMENTE NESSE MOMENTO USANDO RECURSO DE 32BIT.
	;;;;
	
	
	; Obs: Não carrega mais pois ele está em assembly 
	; e faz parte do System4Nora.
	; Obs: Estamos sinalizando o progresso desenhando janelas,
	;      más haverá uma rotina de imprime caracteres.
	
	;mov eax, 40  ;x.
	;mov ebx, 0   ;y.
	;mov ecx, 20  ;largura.
	;mov edx, 20  ;altura.	
    ;mov edi, dword  0x80808000    ;blue    	
	;call CreateWindow
	;call _asm_refresh_screen

	;mov esi, msg_start_ok
	;call lib32PrintString	
	;call _asm_refresh_screen
	
;;
;;======================
;;
;.StartBootLoader:

    ;; #bugbug
	;; Essa mensagem atraza muito.
	;; Por causa do refresh screen

	;mov esi, msg_start_jumping
	;call lib32PrintString
	;call _asm_refresh_screen
    ;jmp $
	
	
	
	;; #bugbug
	;; Temos que permitir o formato elf.
	
	;;
    ;; Check PE binary in BL.BIN.
	;;
	
	;IMAGE_ADDRESS
	
	mov edx, dword 0x20000   
	mov eax, [edx]
    
	;first byte.
	cmp al, byte 'L'
	jne .peFail	
	
	inc edx 
	mov eax, [edx]

	;second byte.
	cmp al, byte 0x01
	jne .peFail	
	
.preparandoArgumentos:
 
    ;;
	;;  ## Boot Block ## 
	;;
	
	;; Prepara a tabela.
	;; Estamos preparando a tabela para enviarmos para o Boot Loader.
	
	;; #todo
	;; Precismos passar mais informações sobre o disco.
	
	; LFB address.
	; Width in pixels.
	; Height in pixel.
	; BPP.
	; metafile address
	; ...
	
	xor eax, eax
	mov eax, dword [ModeInfo_PhysBasePtr]  	
	mov dword [BootBlock.lfb], eax	
	
	xor eax, eax
	mov ax, word [ModeInfo_XResolution]    
	mov dword [BootBlock.x], eax 	
	
	xor eax, eax
	mov ax, word [ModeInfo_YResolution]    
	mov dword [BootBlock.y], eax 	
	
	xor eax, eax
	mov al, byte [ModeInfo_BitsPerPixel]   
	mov dword [BootBlock.bpp], eax 

	xor eax, eax
	mov eax, dword META$FILE                 	
	mov dword [BootBlock.metafile_address], eax	
    
	;Continua...
	
	;xor eax, eax
	mov al, byte 'G'                       ;Flag. (useing graphics)	
	mov ebx, dword [ModeInfo_PhysBasePtr]  ;LFB address (endereço físico)
	
	mov ebp, dword BootBlock
	mov ecx, ebp                           ;tabela
	mov edx, ebp                           ;tabela
	
.goBL:

	;
    ; Go!  
    ;	
	
	;( Passa o comando para o entrypoint do Boot Loader. ) BL.BIN.
	
	jmp 8:IMAGE_ADDRESS_ENTRY_POINT
	JMP $
	
	;;
	;;  ## fail ##
	;;
	
;O arquivo não está presente na memória.	
.peFail:

    mov eax, 0x00ffff00 ;color
	mov esi, msg_start_sig
	call lib32PrintString
	
	
    mov eax, 0x00ffff00 ;color
	mov esi, 0x20000
	call lib32PrintString
	
    call _asm_refresh_screen
    jmp $

		
	;
	; @fim, 
	; Começam as rotinas internas do arquivo.
	;
	
;;=======================================================================
;;=======================================================================
	
;
; Libs --------------------------------------------
;


;-------------------------------------
; configura_lfb:
;     Atualiza LFB address.
;     Salva LFB.
;++

;startSetupLFB:
	
configura_lfb:	 
	push edx   
	mov  edx, dword [ModeInfo_PhysBasePtr]    	
	mov dword [VIDEO.lfb], edx	
	pop edx
	ret
;--

	
;-------------------------------------
; configura_buffer:
;     Configura buffer para modo gráfico.
;     
;  #bugbug 
; nem lembro desses endereços, 
; mas eles estão acima de 16MB e isso é problema, pois o 
; sistema tem a configuração mínima de 16MB.
;
;     @todo: Confirmar os endereços dos buffer.
;            Configurar páginas para eles.  
;
;++

;startSetupBuffer:
	
configura_buffer:

    ;; #bugbug
    ;; Cancelando isso.
	;; Pois esses valores estão acima do limite de 16MB.
	;; Qualquer coisa para sistemas acima de 16MB serão 
	;; configuradas pelo kernel depois de detectar a 
	;; quantidade de memória.
	
	;buffer 1,2 e 3.
	;push edx
   	;mov edx, dword 0x01000000		
	;mov dword [VIDEO.buffer1], edx
   	;mov edx, dword 0x01500000		
	;mov dword [VIDEO.buffer2], edx
   	;mov edx, dword 0x01A00000		
	;mov dword [VIDEO.buffer3], edx 
	;pop edx
	
	ret
;--	
	
	
;
; Start mensagens.
;

;usando em start.
startMsgTest1        db "BM:startGUI: startGUI:", 13, 10, 0
msg_start_ok         db "BM:startGUI: OK", 13, 10, 0	
msg_start_jumping    db "BM:startGUI: Jumping to BL.BIN", 13, 10, 0		
msg_start_sig        db "BM:startGUI: PE sig fail", 13, 10, 0	

;filtrar.
;msg_start_debug_hang db "BM: *start: Debug hang!", 13,10,0	
;msg_start1           db "BM: Start1", 13,10,0	
;msg_start2           db "BM: Start2", 13,10,0
;msg_start3           db "BM: Start3", 13,10,0
;msg_start4           db "BM: Start4", 13,10,0	
;msg_start_loading    db "BM: Loading BL.BIN..", 13,10,0
;msg_no_new_mode_todo db "BM: @todo: save new mode in a file.", 13,10,0	
;msg_no_new_mode      db "BM error: video mode fail!", 13,10,0	
;msg_iniciando_shell  db "BM: Starting Boot Manager Shell..", 13,10,0
;...

;
; End.
;
