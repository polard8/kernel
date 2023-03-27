
; 1 = Starts system GUI.
; 0 = Starts the Boot Manager CLI.
finish_saved_boot_option db 0

; ==============================================================
; AFTER_DATA:
; Inicio real do stage 2.
; A primeira coisa a se fazer eh salvar os parametros de disco 
; passados pelo stage1.
; Argumentos recebidos:
;     bx = Magic number. (autorizaçao)
;     ax = Number of heads.
;     dl = Drive number.
;     cl = Sectors per track.
;     si = BPB.

AFTER_DATA:

; Segments at '0'.

    mov ax, 0 
    mov ds, ax
    mov es, ax 

; Message: Boot Manager Splash.
; See: s2header.inc

    mov si, msg_bm_splash
    call DisplayMessage

    ; Debug.
    ; jmp $

;; Checar se a assinatura PE est� na mem�ria, se estiver, pularemos e
;; a etapa de carregamento do arquivo.
;; #todo
;; Rever essa assinatudo, pois tudo no sistema agora usa ELF.

xxx_checkSig:

    mov ax, 0x2000
    mov gs, ax 

; Testando o 4C
    xor bx, bx
    mov al, byte [gs:bx]    ; 0x2000:0 
    cmp al, byte 0x4C         ;'L' primeiro byte
    jne .sigNotFound

; Testando o 01
    mov bx, 1
    mov al, byte [gs:bx]    ; 0x2000:1 
    cmp al, byte 0x01         ; Segundo byte
    jne .sigNotFound

; Se os dois char n�o est�o ausentes, 
; significa que o arquivo eta no lugar.
    jmp .sigFound

; ========
; Not Found
; A assinatura n�o foi encontrada,
; o arqui n�o est� na mem�ria.
; message: 
; O arquivo n�o esta presente na mem�ria.
.sigNotFound:
    mov si, stage2_msg_pe_sigNotFound
    call DisplayMessage
.sigHalt:
    cli
    hlt
    jmp .sigHalt

; ========
; Found
; A assinatura foi encontrada ... 
; prosseguimos com o stage2.
; message: 
; O arquivo esta presente na mem�ria.
.sigFound:
    mov si, stage2_msg_pe_sigFound
    call DisplayMessage
    ;debug
    ;jmp $
; Turn off fdc motor.
xxx_turnoffFDCMotor:
    mov dx, 3F2h 
    mov al, 0 
    out dx, al
; Reset PS/2 mouse.
xxx_setupPS2Mouse:
    mov ax, 0c201h
    int 15h
xxx_setupRegisters:
    cli
    mov ax, 0 
    mov ds, ax
    mov es, ax
    ;mov fs, ax 
    ;mov gs, ax 
    xor ax, ax
    mov ss, ax
    mov sp, 0x6000
    xor dx, dx
    xor cx, cx
    xor bx, bx
    xor ax, ax
    sti

; Enable a20 line.
; see: rm/s2a20.inc
xxx_setupA20:

    pusha
    call A20_fast_enable
    ;; call A20_enable
    mov si, msg_a20
    call DisplayMessage
    popa

; xxx_Config
; Configurando o modo de inicializaçao do Boot Manager:
; ======================================
; Seleciona um modo de inicializa�ao para o Boot Manager.
; A op��o est� salva no metafile do Boot Mananger.
; Op��es:
;     +1 ~ Shell do boot manager.
;     +2 ~ GUI
; Configura o metafile. META$FILE.INIT_MODE = al

xxx_Config:

; Message
; See: s2header.inc
.setupBootMode:
    mov si, msg_selecting_videomode
    call DisplayMessage

    ; #debug
    ; JMP $

;; ++
;; =====================================
.preSelection:

; 1 = Starts system GUI.
; 0 = Starts the Boot Manager CLI.

; Select GUI. 
; No bm-shell in 32bit assembly.
    
    mov al, byte [finish_saved_boot_option]
    ;mov al, 1

    ; Initialize Gramado boot loader.
    cmp al, 1
    je .xxxxGUI
    cmp al, 0
    je .xxxxCLI

    jmp .xxxxGUI
;; =====================================
;; --


;;
;; == Text mode ==============================
;;

; text mode.
;   ## SET UP BOOT MODE ##
.xxxxCLI:
    mov al, byte BOOTMODE_SHELL
    call set_boot_mode
    jmp .xxxxGO

;;
;; == Graphics mode ==========================
;;


; gui mode.
; Initialize Gramado boot loader.
;   ## SET UP BOOT MODE ##
.xxxxGUI:
    mov word [META$FILE.VIDEO_MODE], G_VIDEO_MODE
    mov al, byte BOOTMODE_GUI
    call set_boot_mode
    jmp .xxxxGO

;
; Go!
;

;
; == \o/ ========
;

; Initialize Gramado boot loader.
; Activate the chosen mode.
; (s2modes.inc)
.xxxxGO:
    JMP s2modesActivateMode  
    JMP $

;
; == \o/ ========
;

; =======================================================
; Messages

stage2_msg_pe_sigNotFound: 
    db "bm-xxx_checkSig: Signature not found", 13, 10, 0
stage2_msg_pe_sigFound: 
    db "bm-xxx_checkSig: Signature found", 13, 10, 0
