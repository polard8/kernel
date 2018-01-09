;
; File: bootloader.inc 
;
; Descrição:
;     Inicia o Boot Loader da partição ativa.
;     Carrega o BL.BIN para a memória e executa.
;     O Boot Loader pode estar em qualquer partição de qualquer disco, 
; mesmo que o disco não seja bootável.
;
; Versão 1.0, 2015.
;



;  
; Boot Loader name.
; Obs: Esse é programaque deve ser carregado pelo Boot Manager.
;

boot_loader_name  db  'BL      BIN',0


;------------------------------------------
; BootBlock:
;     Argumentos que serão passador para o Boot Loader.
;     Passa para o Boot Loader um ponteiro para os serviços oferecidos pelo 
; Boot Manager.
;     * Informações sobre modo de vídeo.
;     * ...
;     *
;
; Obs: Isso é um Meta-Objeto: Um vetor contendo variáveis e métodos.
; Obs: .bmServices conterá o endereço de _bmServices:. que esta em lib32.inc.
;
; Obs: Criaremos um bloco de informações seguindo o padrão da 'Multiboot Specification'.
; O Boot Manager, o Boot Loader e o Kernel base deverão seguir esse padrão de boot.
; Para tirarmos proveito da padronização do processo de boot para open source.
;
BootBlock:
    .lfb:    dd 0
    .x:      dd 0
    .y:      dd 0
    .bpp:    dd 0
    .metafile_address:  dd 0
    .bmServices: dd 0 
    ;Continua...


;;
;;  Bloco de informações para o multiboot.
;;	
MultiBootBlock:
    dd 0
    dd 0
    dd 0
    dd 0
;;...

	
	
;Status da instalação do boot.
bootloader_install_status: dd 0



;-----------------------------------------------
; bootloader:
;     Carrega e inicia o Boot Loader da partição ativa.
;
;++
bootloader: 
	;suspensa.
	;call load_boot_loader
	;call start_bootloader
	ret	
;--	

	
	
	
;====================================================
; load_boot_loader:
;     Carrega o Boot Loader (BL.BIN) na memória.
;     Essa rotina é chamada em start.inc para carregar o BL.BIN na memória.
;     Essa rotina chama os recursos de \fs da classe fs16XXXX. 
;
load_boot_loader:
    nop
.initHardware:
	call init_ide0_master
.readFile:
	push eax
	push ebx 
    mov eax, dword boot_loader_name
    ;call fat16_read_file
	call fat16ReadFile
	jc .fail
	pop ebx
	pop eax
    clc
	ret
.fail:	
    ;@todo: Some message.
    ;push eax
	;push ebx
	;push ecx 
	;push edx
	mov esi, msm_load_boot_loader_fail 
	call lib32PrintString
	;pop edx 
	;pop ecx 
	;pop ebx 
	;pop eax 
	call _asm_refresh_screen 
	jmp $

msm_load_boot_loader_fail: db "load_boot_loader: fail.",13,10,0	
	
;----------------------------------------------
; start_bootloader:
;     Executa o Boot Loader do System4Nora. No modo texto apenas.
;
start_bootloader:

    call os_screen_clear
	call reset_cursor
	
    ;cabeçalho PE.
    cmp byte [IMAGE_ADDRESS], byte 'L'
	je .ok
	
	;Erro.
    mov esi, bl_bl_nao_presente
	call os_output	

	;Debug
	jmp $
.ok:	
    ;Debug
	;Mostra o arquivo. (ou um pedaço dele.)
    ;mov esi, IMAGE_ADDRESS
	;call os_output
	
	mov esi, bl_bl_test
	call os_output
   
	;
	;@todo: Passar argumentos.
    ;
    ; al = modo de video
	; ebx = lfb.
    ;
	
	mov al, byte 'T' 
 	;mov al, byte 'G'                       ;Flag. (useing graphics)	
	;mov ebx, dword [ModeInfo_PhysBasePtr]  ;LFB address
	;mov ecx, dword [ModeInfo_XResolution]  ;Width in pixels.
	;mov edx, dword [ModeInfo_YResolution]  ;height in pixel.	
	
	;
	; Go!.
	;
	jmp 8:IMAGE_ADDRESS_ENTRY_POINT
	jmp $
	
	;jmp System4Nora_BootLoader  ;Passa o comando para o Boot Loader.  
	;call System4Nora_BootLoader 

.done:	
	mov eax, 0	
	RET
	
	;mov esi, bl_bl_fail_text
	;call os_output	
	
	;Opção.
	JMP $
	

;;==================================================================
;; start_bootloader_on_graphic_mode:
;;     Executa o programa BL.BIN no modo gráfico.
;;
;;
;;   **** PASSANDO O COMANDO PARA O BL.BIN    ****
;;
;;
;; @todo: Verificar antes se ele está presenta na memória.
;;
start_bootloader_on_graphic_mode:
;bootloaderStartOnGraphicMode:	
	;
	; Meta-Object: @todo:
	; ============
	;     O Boot Manager passar para o Boot Loader um Meta-Objeto na forma 
	; de vetor, contendo variáveis e métodos.
	;     O principal método à se passar é _bmServices contendo o método
	; que o Boot Manager usa para oferecer serviços. Desse módo o Boot Manager
	; pode atuar como um módulo do kernel em kernel mode. Para isso o
	; Boot Loader terá que passar esse método para o Kernel Base.
	;
	
	;
	; Prepara argumentos.
	;
	; EBP = BootBlock.
	; al = 'G'
	; ebx = LFB.
	;
	;
	
	;Prepara a tabela.
	mov ebp, dword BootBlock
	
	xor eax, eax
	mov eax, dword [ModeInfo_PhysBasePtr]  ;LFB address.	
	mov dword [BootBlock.lfb], eax	
	
	xor eax, eax
	mov ax, word [ModeInfo_XResolution]    ;Width in pixels.
	mov dword [BootBlock.x], eax 	
	
	xor eax, eax
	mov ax, word [ModeInfo_YResolution]    ;Height in pixel.
	mov dword [BootBlock.y], eax 	
	
	xor eax, eax
	mov al, byte [ModeInfo_BitsPerPixel]   ;bpp.
	mov dword [BootBlock.bpp], eax 


	xor eax, eax
	mov eax, dword META$FILE                 ;metafile address	
	mov dword [BootBlock.metafile_address], eax	
    
	;Continua...
	
	xor eax, eax
	mov al, byte 'G'                       ;Flag. (useing graphics)	
	mov ebx, dword [ModeInfo_PhysBasePtr]  ;LFB address (endereço físico)
	mov ecx, ebp
	mov edx, ebp                           ;tabela
	
	;
    ; Go! ( Passa o comando para o entrypoint do Boot Loader. ) BL.BIN. 
    ;	
	
	;call _background_teste
	;call _background
	;call _fade_screen
	;jmp $
	
	
    ;cabeçalho PE. no BL.BIN.
    cmp byte [IMAGE_ADDRESS], byte 'L'
	jne .peFail	

	mov esi, msg_bootloader_jumping
	call lib32PrintString
	call _asm_refresh_screen		
	
	;debug
	jmp $
	
	
	jmp 8:IMAGE_ADDRESS_ENTRY_POINT
	JMP $

;O arquivo não está presente na memória.	
.peFail:
	mov esi, msg_bootloader_sig
	call lib32PrintString
	call _asm_refresh_screen		
    jmp $

msg_bootloader_sig     db "start_bootloader_on_graphic_mode: A assinatura PE de BL.BIN falhou ... *HANG",0	
msg_bootloader_jumping db "start_bootloader_on_graphic_mode: Passando o comando para o BL.BIN ... *HANG",0	
	
;
; Messages.
;

;Erros.
bl_bl_fail_text      db "start_bootloader error: Text Mode fail!",13,10,0
bl_bl_fail_graphics  db "start_bootloader error: Graphic mode fail!",13,10,0	
bl_bl_presente       db "start_bootloader error: BL.BIN Validation!",13,10,0
bl_bl_nao_presente   db "start_bootloader error: BL.BIN Validation!",13,10,0
bl_bl_test           db "start_bootloader: Passa o comando para o Boot Loader..",13,10,0

;
;fim.
;	
 