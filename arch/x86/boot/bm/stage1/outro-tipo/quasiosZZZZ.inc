;;
;; Gramado MBR - This is the stage 1 for Gramado Boot Manager.
;; It loads the BL.BIN from a fat16 file system and load the stage 2.
;; (c) Copyright 2017 - Fred Nora
;;
;; File: stage1\quasios.inc
;;

;;
;; @TODO:  DEVEMOS REPRODUZIR AQUI AS ROTINAS DE CARREGAMENTO USADAS PELO 'MBR'
;;         MAS AGORA PARA CARREGAR MOS O 'BL.BIN'.
;;

;;
;; codename='bergen'
;;

[BITS 16]


; Constants used on Stage1.
;

;Stage1. 
STAGE1_SEGMENT        equ 0
STAGE1_OFFSET         equ 0x8000   ;; *****
STAGE1_STACK_SEGMENT  equ 0 
STAGE1_STACK_POINTER  equ 0x0E00   ;; *****
 
;Stage2.
; @todo: Com o novo padrão de tamanho de setor,
;        certamente o início do stage2 terá uma nova localização.
;        O novo tamanho de setor será 4096 bytes. ?! 
;
STAGE2_SEGMENT        equ 0
STAGE2_OFFSET         equ 0x8200  ;; ***** um setor depois do stage 1.

BLBIN_SEGMENT        equ 0x2000
BLBIN_OFFSET         equ 0x0  

MBRROOT_SEGMENT EQU 0 
MBRROOT_OFFSET  EQU 0xA000

;fat: isso está antes do bl. 17c0:0200   2000:0000
MBRFAT_SEGMENT   EQU 0x17C0 
MBRFAT_OFFSET    EQU 0x200

;Assinatura do metafile.
;Usado para autorizar a execução do stage2.
;Para evitar que qualquer programa tente executar o Stage2.
MAGIC_NUMBER          equ 0xF0ED 

;
; Sector size:
; ============
;     O tamanho padrão de setor para os novos dispositivos
;     será 4096 byte (4KB) e não mais 512 bytes.
;
SECTOR_SIZE	EQU	512		;Sector size in bytes.
;SECTOR_SIZE EQU 4096   ;Sector size in bytes.(novo padrão).



;ORG 0x500
    
	jmp short qstage1Start  	;Salta para após o BPB.
    nop
	
qOEM_ID                db "MSDOS5.0"

s1_bpb:
qBytesPerSector        dw SECTOR_SIZE
qSectorsPerCluster     db 1
qReservedSectors       dw 3
qTotalFATs             db 0x02
qMaxRootEntries        dw 512
qTotalSectorsSmall     dw 0x0000
qMediaDescriptor       db 0xF8
qSectorsPerFAT         dw 246
qSectorsPerTrack       dw 0x11
qNumHeads              dw 4 
qHiddenSectors         dd 0x00000000
qTotalSectorsLarge     dd 0x00000000
qDriveNumber           db 0x80
qFlags                 db 0x00
qSignature             db 0x29
qVolumeID              dd 0x980E63F5
qVolumeLabel           db "QUASI  BOOT" ;gramado
qSystemID              db "FAT16   "



qstage1Start:
    ;;Ok deveríamos desabilitar a interrupção aqui e só habilitar novamente quando formos usar.	
	;cli
	;Stack. 
	XOR AX, AX          
    MOV SS, AX         
    MOV SP, word STAGE1_STACK_POINTER          
	;Data Segments. 
    MOV DS, AX 
	MOV ES, AX          
    ;Origem e destino.
    MOV SI, word 0x7C00        
    MOV DI, word 0x8000 ;0x0E00  ;STAGE1_OFFSET.       
    ;Contador.			
	MOV CX, word 0x0200       
    CLD                 
    REP MOVSB  
    ;Jumping using retf.	
    PUSH AX        ;0H         
    PUSH qretomada  ;0x0E20       
    RETF 	
;Alinhamento para a retomada.
;qtransfer_end:    
    ;TIMES 0x0020 - ( transfer_begin - transfer_end ) DB 0
;
;----------------------------------------;
;

 ;--------------------------------------------
; retomada:
;     Reinício do Stage1.
; 
qretomada:

    ;;
	;; **** OK ESTA FUNCIONADO O MBR FAT16 MAS FALTA IMPLEMENTAR A PASSAGEM DE ARGUMENTOS.  *****
	;;

	mov si, stage1msg
	call    qDisplayMessage 
	;JMP $


    ;Seguem os passos de 1 a 9.
Step1:   
    ;cli	
	;stack.
    ;mov ax, word STAGE1_STACK_SEGMENT
    ;mov ss, ax
    ;mov sp, word STAGE1_STACK_POINTER
	;data segments. (cancelado, o data segmento ja foi configurado logo acima.)
    ;mov ax, STAGE1_SEGMENT 
    ;mov ds, ax
    ;mov es, ax
    ;sti
	;;Save disk number.
Step2:
    ;mov byte [qDriveNumber], byte dl 
	;;Clear the Screen.
Step3:   
	;mov ax, 02h
    ;int 010h
Step4:	 
	 
Step6:	
    ;
	; Get drive parameters: 
	; =====================
    ; Return: CF set on error.
    ; AH = status (07h).
    ; CF clear if successful.
    ; AH = 00h.
    ; AL = 00h on at least some BIOSes.
    ; BL = drive type (AT/PS2 floppies only). 
    ; CH = low eight bits of maximum cylinder number.
    ; CL = maximum sector number (bits 5-0).
    ;      high two bits of maximum cylinder number (bits 7-6).
    ; DH = maximum head number.
    ; DL = number of drives.
	;
	
	;xor ax, ax
	;mov ah, byte 08h
   ; mov ax, 0x0800
	;int 0x13 
	
	;;
	;; *** obs: Por falta de espaço pegaremos apenas a quantidade de cilindros.
	;; os outros estão determinados no BPB.
	;;
	
	;
	;Heads.
	;Número de heads.
	;Logical last index of heads = (number_of - 1). 
	;(Because index starts with 0).
	;
	; Obs: 
	; O valor de Heads foi gravado no BPB mas precisará ser passado a diante
	; para uso posterior.
	;
	;xor ax, ax
	;mov al, dh
	;inc ax				              ;From 0-based to count.
	;mov word [qNumHeads], ax    ;BPB.
	
	;
    ; Sectors Per Track e Cylinders.
    ; Essas informações apresentam meio truncadas
    ; O valor do número de cilindros é aprentado
    ; de forma parcial, uma parte em cada registrador.
    ;	
	
	;spt.
	;  bits [5:0] logical last index of sectors per track = number_of 
	;  (because index starts with 1).
	;cyl.
	;   bits [7:6] [15:8] logical last index of cylinders = number_of - 1 
	;  (because index starts with 0).

	;
	; Sectors Per Track - (SPT).
	; "Esconde 2 bits que pertencem a quantidade de setores".
	;
	; Obs: 
	; O valor de SPT foi gravado no BPB mas precisará ser passado a diante
	; para uso posterior.
    ;	
	;xor eax, eax 
	;mov al, cl
	;and al, byte 00111111b                   ;03Fh			
	;mov byte [qSectorsPerTrack], al    ;BPB (word).
	
    ;
	; Cylinders
	; Obs: 
	; O valor de CylinderNumbers foi gravado em variável mas precisará ser 
	; passado a diante para uso posterior.
	;
	xor eax, eax
	mov al, cl   					;Two high bits of cylinder number in bits 6&7.
	and al, 11000000b				;Mask it.
	shl ax, 2						;Move them to bits 8&9.
	mov al, ch						;Rest of the cylinder bits.(low 8 bits)
	inc eax							;Number is 0-based.
	mov dword [qCylinderNumbers], eax		 
	 
	 
	 ;;
	 ;;
	 ;;
	
    ;Message (Loading ROOT.)	
	;mov si, qmsgLoadingROOT
	;call    qDisplayMessage 
	
	;debug
	;jmp $

qLOAD_ROOT:


    ;;
	;; ignorar o cálculo da localização d área de dados.
	;;
; compute size of root directory and store in "cx"
     ;xor     cx, cx
     ;xor     dx, dx
     ;mov     ax, 0x0020                          ; 32 byte directory entry
     ;mul     WORD [qMaxRootEntries]               ; total size of directory
     ;div     WORD [qBytesPerSector]               ; sectors used by directory
     ;xchg    ax, cx
; compute location(LBA) of root directory and store in "ax"
     ;mov     al, BYTE [qTotalFATs]                ; number of FATs
     ;mul     WORD [qSectorsPerFAT]                ; sectors used by FATs
     ;add     ax, WORD [qReservedSectors]          ; adjust for bootsector
	 ;add	 ax, WORD [qHiddenSectors]
	 ;mov     WORD [qdatasector], ax               
     ;add     WORD [qdatasector], cx   ;; LBA da área de dados.
	 
	 ;determinando onde fica a área de dados.
	 mov word [qdatasector], word 591
	 
	 
; read root directory into memory (7C00:0200)
    
	mov dx, MBRROOT_SEGMENT ;0
	mov ds, dx
	mov es, dx
	
	mov bx, MBRROOT_OFFSET ;0xA000 ;0x0200                          ; copy root dir above bootcode
    mov cx, 1 ;;carregar apenas um setor do diretório raiz.
	
	mov ax, 559    ;; LBA inicial do diretório raiz.
	call    qReadSectors


;cancelando a mensagem para economizar.	 
;pusha
;mov     si, qmsgCRLF
;call    qDisplayMessage
;popa
 
 ;;
 ;; browse root directory for binary image
 ;;

.searchFile:
	
	mov dx, MBRROOT_SEGMENT ;0
	mov ds, dx
	mov es, dx 
 
     mov     cx, WORD [qMaxRootEntries]           ; load loop counter
     mov     di, MBRROOT_OFFSET ;0xA000     ;0x0200                    ; locate first root entry
.qLOOP:
     push    cx
     mov     cx, 0x000B                          ; eleven character name

     mov     si, qImageName                       ; image name to find
	 ;pusha
	 ;call    qDisplayMessage
	 ;popa
	 
	 push    di
	 rep     cmpsb                               ; test for entry match
     pop     di
     
	 je      qLOAD_FAT
     pop     cx
     add     di, 0x0020                          ; queue next directory entry
     loop    .qLOOP
     jmp     qFAILURE


	
	 
qLOAD_FAT:

   ;; O arquivo foi encontrado no primeiro setor do diretório raiz, vamos carregar a fat.
    ;Message (Loading FAT.)	
	;mov si, qmsgLoadingFAT
	;call    qDisplayMessage 

	;debug
	;jmp $

;cancelando a mensagem para economizar.
;pusha
;mov     si, qmsgFAT
;call    qDisplayMessage
;mov ah,0x00
;int 0x16
;popa

; save starting cluster of boot image
     mov     dx, WORD [di + 0x001A]
     mov     WORD [qcluster], dx                  ; file's first cluster
; compute size of FAT and store in "cx"
    ;mov cx, WORD [qSectorsPerFAT]
     mov cx, WORD 8                              ;; carreegar apenas 8 setores da fat.
	 
; compute location of FAT and store in "ax"
     mov     ax, WORD [qHiddenSectors]         	 ; adjust for bootsector
	 add     ax, WORD [qReservedSectors]
	 
; read FAT into memory (17C0:0200)
     push 	 ax
	 mov     ax, MBRFAT_SEGMENT ;0x17C0
     mov     es, ax
	 pop 	 ax ;; LBA inicial.
	 mov     bx, MBRFAT_OFFSET ;0x0200                          ; copy FAT above bootcode
    
	;; **** carregando menos setores da fat.
	mov ax, 67   ;início da fat setor 67
	call    qReadSectors	

; read image file into memory (37C0:0100)(es:bx)
     ;cancelando a mensagem para ecoonomizar
	 ;mov     si, qmsgCRLF
     ;call    qDisplayMessage
	 ;mov     si, qmsgImg
     ;call    qDisplayMessage
	 
    ;Message (Loading FILE.)	
	;mov si, qmsgLoadingFILE
	;call    qDisplayMessage 

     ;;
	 ;; Aqui a fat tambem foi carregada, vamos iniciar o carrregamento do arquivo.
	 ;;
	 
	;debug
	;jmp $
	
	 
     mov     ax, BLBIN_SEGMENT
     mov     es, ax                              ; destination for image
     mov     bx, BLBIN_OFFSET                    ; destination for image
     push    bx
	 mov     ax, MBRFAT_SEGMENT 				 ; *FAT Segment	
     mov     gs, ax     
	 
qLOAD_IMAGE:
     mov     ax, WORD [qcluster]              	 ; cluster to read
     pop     bx                                  ; buffer to read into
     call    qClusterLBA                          ; convert cluster to LBA
     xor     cx, cx
     mov     cl, BYTE [qSectorsPerCluster]        ; sectors to read
     call    qReadSectors
     push    bx
; compute next cluster
     mov     ax, WORD [qcluster]              	 ; identify current cluster
     mov     bx, MBRFAT_OFFSET ;0x0200                          ; location of FAT in memory
     add	 ax, ax								 ; 16 bit(2 byte) FAT entry
	 add     bx, ax                              ; index into FAT
     mov     dx, WORD [gs:bx]                    ; read two bytes from FAT
.qDONE:
     mov     WORD [qcluster], dx              	 ; store new cluster
	 cmp     dx, 0xffff ;0x0FF0                          ; test for end of file
     jnb      qLOAD_IMAGE
qDONE:
     ;mov     si, qmsgCRLF
     ;call    qDisplayMessage
     ;push    WORD 0x37C0
     ;push    WORD 0x0100
     ;retf
	 
	;;MENSAGEM INDICANDO QUE A IMAGEM FOI CARREGADA COM SUCESSO. 
    mov     si, qmsgIMAGEOK   
    call    qDisplayMessage	 
	
	;debug
	;jmp $	
	 
;;=================================================
;;
;;
    ;;aqui a imagem ja foi carregada. 
    ;;carregando o stage 2 em 0:1000
	
	;ES:BX
	mov ax, word STAGE2_SEGMENT
    mov es, ax
    mov bx, word STAGE2_OFFSET 
	
	;Setor inicial do stage2. (segundo setor).
	;xor ax, ax
	;mov al, byte 1
    mov ax, word 0x0001	
	
    ;Quantidade de setores da stage2. (64-1) = 31,5 KB.	
	;xor cx, cx
	;mov cl, byte 63   
	mov cx, word 63
	
	;
	; Ler os setores:
	; Reads "cx" sectors from disk starting at "ax" into memory location 
	; "es:bx".
	;
	
	call qReadSectors
	
	
    ;
    ; Preparando os parametros para entrar no stage2. 
	; Parameters: 
	; ==========
	; Como o stage 2 está em 0:0x1000, configura a pilha para 0:0x0E00.
	; bx = Magic number.
	; ax = Number of heads.    (*IMPORTANTE) 
	; dl = Drive number.       (*IMPORTANTE)
    ; cl = Sectors per track.  (*IMPORTANTE)
    ; di = cylinder numbers    (*IMPORTANTE)
	;
	
	;
	; Obs: No stage 2 essas informações serão passadas para o metafile,
	; pois no stage 1 ainda não temos acesso ao metafile.
	;
	
	;Magic.
	;mov bx, word 0xf0ed ;MAGIC_NUMBER	
    ;Data.
	;XOR AX, AX
	;MOV DS, AX 
	;MOV ES, AX          	
    ;Stack.
    ;MOV AX, STAGE1_STACK_SEGMENT
	;MOV SS, AX          
    ;MOV SP, STAGE1_STACK_POINTER        
    ;Disk parameters.
	mov ax, word [qNumHeads]         ;Heads.
    mov dl, byte [qDriveNumber]	   ;*Disk Number.	
	mov cl, byte [qSectorsPerTrack]  ;Sectors Per Track.
	;mov ch, byte 0                         ;Nothing. 
	mov di, word [qCylinderNumbers]         ;Cylinders. ??
	;BPB.
	;mov si, word s1_bpb                    ;BPB. ;ds:si = 0:si
	;Done.
qStep9:	
	;mov     si, qmsgGO
    ;call    qDisplayMessage	
	;Debug
	;jmp $

    ;Go!
	PUSH STAGE2_SEGMENT
	PUSH STAGE2_OFFSET
	RETF	 
	 
	 
	 
qFAILURE:
    ;int 0x18
	;jmp $ 
	;;cancelada por falta de espaço.
	;mov     si, qmsgFailure
   ; call    qDisplayMessage
    jmp $
	;mov     ah, 0x00
    ;int     0x16                                ; await keypress
    ;int     0x19                                ; warm boot computer


;*************************************************************************
; PROCEDURE DisplayMessage
; display ASCIIZ string at "ds:si" via BIOS
;*************************************************************************
qDisplayMessage:
     lodsb                                       ; load next character
     or      al, al                              ; test for NUL character
     jz      .qDONE
     mov     ah, 0x0E                            ; BIOS teletype    
	 ;mov     bh, 0x00                            ; display page 0
     ;mov     bl, 0x07                            ; text attribute
     mov bx, 0x0007 
	 int     0x10                                ; invoke BIOS
     jmp     qDisplayMessage
.qDONE:
     ret

;*************************************************************************
; PROCEDURE ReadSectors
; reads "cx" sectors from disk starting at "ax" into memory location "es:bx"
;*************************************************************************
qReadSectors:
	 mov WORD[qDAPBuffer],   bx ;offset
	 mov WORD[qDAPBuffer+2], es ;segment
	 mov WORD[qDAPStart],    ax ;lba inicial.
.qMAIN:
     mov     di, 0x0005                          ; five retries for error
.qSECTORLOOP:
     push    ax
     push    bx
     push    cx
	 
     push si
     mov ah,0x42
     mov dl,0x80
     mov si,qDAPSizeOfPacket
     int 0x13
     pop si
	 
     jnc     .qSUCCESS                            ; test for read error
     xor     ax, ax                              ; BIOS reset disk
     int     0x13                                ; invoke BIOS
     dec     di                                  ; decrement error counter
     pop     cx
     pop     bx
     pop     ax
	 jnz     .qSECTORLOOP                         ; attempt to read again
	int     0x18 
.qSUCCESS:
     ;mensagem suspensa por falta de espaço.
	 ;mov     si, qmsgProgress
     ;call    qDisplayMessage
	 
     pop     cx
     pop     bx
     pop     ax
     add     bx, WORD [qBytesPerSector]           ; queue next buffer
	 cmp	 bx,0x0000	
	 jne	 .qNextSector
	 
	 ;push 	 ax
	 ;mov	 ax, es
	 ;add	 ax, 0x1000
     ;mov     es, ax
	 ;pop 	 ax
	 
.qNextSector:
     inc     ax                                  ; queue next sector
	 mov WORD[qDAPBuffer],bx
	 mov WORD[qDAPStart],ax
     loop    .qMAIN                               ; read next sector
     ret
 
 
;*************************************************************************
; PROCEDURE ClusterLBA
; convert FAT cluster into LBA addressing scheme
; LBA = (cluster - 2) * sectors per cluster
;*************************************************************************
qClusterLBA:
     sub     ax, 0x0002                          ; zero base cluster number
     xor     cx, cx
     mov     cl, BYTE [qSectorsPerCluster]        ; convert byte to word
     mul     cx
     add     ax, WORD [qdatasector]               ; base data sector
	 ret


; Salvando variáveis.
qCylinderNumbers:  dd 0		 

qDAPSizeOfPacket db 10h
qDAPReserved	 db 00h
qDAPTransfer	 dw 0001h
qDAPBuffer		 dd 00000000h
qDAPStart		 dq 0000000000000000h


qabsoluteSector db 0x00
qabsoluteHead   db 0x00
qabsoluteTrack  db 0x00

qdatasector 	dw 0x0000
qcluster     dw 0x0000
qImageName   db "BL      BIN" ,0x0D, 0x0A,0x00
qmsgCRLF     db 0x0D, 0x0A, 0x00
qmsgProgress db "*", 0x00
qmsgFailure  db "F", 0x00 ;; Arquivo não encontrado.
;qmsgFail	 db "r", 0x00 ;;Read
;qmsgFAT		 db "f", 0x00 ;;Loading FAT
;qmsgImg		 db "I", 0x00 ;;Loading Image

;MENSAGENS.
;qmsgLoadingROOT  db "1",0x0D, 0x0A,0x00 ;;suspenso para economizar espaço
;qmsgLoadingFAT   db "2",0x0D, 0x0A,0x00 ;;suspenso para economizar espaço
;qmsgLoadingFILE  db "3",0x0D, 0x0A,0x00
;qmsgReadSectorFail db "rs", 0x00 ;;FALHA NA ROTINA READSECTOR.
qmsgIMAGEOK db "$", 0x00    ;;MENSAGEM INDICANDO QUE A IMAGEM FOI CARREGADA COM SUCESSO. 
qmsgGO db "G", 0x00   ;; GO ... vamos saltar para o stage 2.
stage1msg db 'BM.BIN: This is the first sector of BM.BIN.',0

;;
;; esse é o primeiro setor do BM.BIN , não tem tabela aqui.
;;

     TIMES 510-($-$$) DB 0
     DW 0xAA55
;*************************************************************************
