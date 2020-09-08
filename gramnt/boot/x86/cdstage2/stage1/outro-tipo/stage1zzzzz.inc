;
; Gramado MBR -- a 16bit MBR written in Assembly for x86 processors.
; (c) Copyright 2015-2017 Fred Nora.
;  
; File: stage1\stage1.inc
;
; Obs:
;     A partição ativa precisa estar formatada em FAT16.
;
; Descrição:
;     MBR, Primeiro setor do disco.
;     O MBR é primeira parte do Mass Storage Manager.
;     A segunda parte será o stage2.
;     Obs: Tem um BPB no estilo DOS pra efeito de compatibilidade.
;
; Atribuições:
;     +O stage1 é carregado em 0:7C00 pelo BIOS.
;     +O stage1 carrega a si próprio para 0:0x0E00. 
;     +O stage1 carrega o stage2 para 0:0x1000, logo após 
;      sua nova localização (0x0E00).
;     +O stage1 passa o comando para o stage2.
;
;     Obs: Os discos modernos terão um novo padrão de tamanho de setor.
;          Passarão dos atuais 512 bytes para 4KB.
;          Com a mudança do tamanho padrão dos setores de disco
;          vários ajustes devem ser feitos. 
;     @todo: Novo padrão de tamanho de setor em discos modernos.
;    
;    *IMPORTANTE: 
;    É necessário rotinas eficientes de identificação de parâmetros de disco, 
;    e detecção de diretórios e arquivos, pois qualquer falha nessas rotinas 
;    implicam em não carregamento do sistema. Logicamente o sistema será 
;    instalado em discos diferentes, com parâmetros diferentes.
;
;    @TODO: 
;    Talvez, para um suporte adequado ao gerenciamento de disco,
;    seja necessário aumentar o tamanho do programa MSM feito 
;    em assembly 16/32 bit. Talvez para 64KB, 128KB ou mais.
;    Isso implica mudar no stage1, a quantidade de setores 
;    carregados por ele.
;
; Versão: 1.0.
; 
; Histórico:
;     2015 - Created by Fred Nora.
;     2016 - Revision.
;     2017 - Revision.  
;

;;
;; codename db 'bergen'
;;

;
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


;-------------------------------------------------
; stage1_main:
;     Início do Stage1.
;     Começa transferindo a si mesmo para 0:0x0E00.
;     Depois retoma a execução no novo endereço.
;
stage1_main:
transfer_begin:
	jmp short stage1Start  	;Salta para após o BPB.
	nop
	
s1_OEM_ID:  DB "MSDOS"  ;"GRAMADO "
s1_VERSION: DB "5.0"
;Extended BPB 
s1_bpb:
	.BytesPerSector:       dw SECTOR_SIZE  ;512 or 4096.
	.SectorsPerCluster:    db 1
	.ReservedSectors:      dw 3    ;imdisk fez assim.
	.TotalFATs:            db 2
	.MaxRootEntries:       dw 512  ;512 entradas de 32bytes = (32 setores).
	.TotalSectorsSmall:    dw 0    ;(4*17*963-8) ;4*17*963-2 ; (963 cyl, 4 heads, 17 sectors).  
	                               ;Number of sectors - number of hidden. (0 when 32 bit sector number)
								   ;Será 0 se o total for um valor de 32bit.
	.MediaDescriptor:      db 0xF8
	.SectorsPerFAT:        dw 246  ;imdisk fez assim. ;64,(Sectors Per FAT) (Depende do tamanho do disco).   
	.SectorsPerTrack:      dw 0x11 ;17, Pegar via BIOS.     
	.NumHeads:             dw 4    ;4,  Pegar via BIOS.        
	.HiddenSectors:        dd 0x00000000  ;0x00000011 ??
	.TotalSectorsLarge:    dd 0x00000000    ; 32 bit version of number of sectors
	 ;For extended.
	.DriveNumber:          db 0x80       ;Pegar via BIOS.
	.Flags:                db 0x00       ;Antigamente era 'Current Head'.
	.Signature:            db 0x29       ;Extended Boot Signature. (41)
	.VolumeID:             dd 0x980E63F5      ;Serial Number.
	.VolumeLabel:          db "GRAMADO VHD"
	.SystemID:             db "FAT16   "	
	
	
	;Obs: 
	; Quando o número total de setores for um valor de 32 bit,
	; ao formatar, 'Hidden sectors' e 'total sectors large'
	; poderão ser setados para 0.
	
	
    ;;
	;; Podemos sobrescrever a rotina MbrStart, depois de termos usado ela.
	;; Para isso precisaremos desses 'equ's.
	;;
	
;MBRDISKINFO:
    ; Usando 'dword'.
    ;MBRDISKINFO_DRIVENUMBER EQU (MBRDISKINFO+0)  ;Drive number. 
    ;MBRDISKINFO_CYLINDERS   EQU (MBRDISKINFO+4)  ;C
    ;MBRDISKINFO_HEADS       EQU (MBRDISKINFO+8)  ;H 
    ;MBRDISKINFO_SECTORS     EQU (MBRDISKINFO+12) ;S
    ;MBRDISKINFO_P0LBA       EQU (MBRDISKINFO+16) ;LBA inicial da partição 0. 
    ;MBRDISKINFO_P1LBA       EQU (MBRDISKINFO+20) ;LBA inicial da partição 1.
    ;MBRDISKINFO_P2LBA       EQU (MBRDISKINFO+20) ;LBA inicial da partição 2.
    ;MBRDISKINFO_P3LBA       EQU (MBRDISKINFO+20) ;LBA inicial da partição 3.
    ;;...	
	
	; Iniciando o código que faz a transferência.	
stage1Start:
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
    PUSH retomada  ;0x0E20       
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
retomada:
    ;Seguem os passos de 1 a 9.
Step1:   
    cli	
	;stack.
    mov ax, word STAGE1_STACK_SEGMENT
    mov ss, ax
    mov sp, word STAGE1_STACK_POINTER
	;data segments.
    mov ax, STAGE1_SEGMENT 
    mov ds, ax
    mov es, ax
    sti
	;;Save disk number.
Step2:
    mov byte [s1_bpb.DriveNumber], byte dl 
	;;Clear the Screen.
Step3:   
	mov ax, 02h
    int 010h
Step4:	
	;@todo: Certificar que int 13h é suportada.
Step5:	
    ;@todo: Reset driver.
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
	
	xor ax, ax
	mov ah, byte 08h
    int 0x13 
	
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
	xor ax, ax
	mov al, dh
	inc ax				              ;From 0-based to count.
	mov word [s1_bpb.NumHeads], ax    ;BPB.
	
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
	xor eax, eax 
	mov al, cl
	and al, byte 00111111b                   ;03Fh			
	mov byte [s1_bpb.SectorsPerTrack], al    ;BPB (word).
	
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
	mov dword [CylinderNumbers], eax		
Step7:
    ;Carregar o resto do Boot Manager.
	
;
;load_stage2:
;    Carrega o Stage2 em 0x00001000. 
;
load_stage2:
	;Limpa registradores e reseta o controlador.	
	xor ax, ax
	xor bx, bx
	xor cx, cx
	xor dx, dx
	mov dl, byte [s1_bpb.DriveNumber]
    int 0x13   
    
    ;
    ;Prepara os registradores.
    ; 	

;++    
	;ES:BX
	mov ax, word STAGE2_SEGMENT
    mov es, ax
    mov bx, word STAGE2_OFFSET 
	
	;Setor inicial do stage2. (segundo setor).
	xor ax, ax
	mov al, byte 1  
	
    ;Quantidade de setores da stage2. (64-1) = 31,5 KB.	
	xor cx, cx
	mov cl, byte 63   
	
	;
	; Ler os setores:
	; Reads "cx" sectors from disk starting at "ax" into memory location 
	; "es:bx".
	;
	
	call s1_ReadSectors
;-- 

    ;
	; Passando o comando para o Stage2.
	;
Step8:
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
	mov bx, word MAGIC_NUMBER	
    ;Data.
	XOR AX, AX
	MOV DS, AX 
	MOV ES, AX          	
    ;Stack.
    MOV AX, STAGE1_STACK_SEGMENT
	MOV SS, AX          
    MOV SP, STAGE1_STACK_POINTER        
    ;Disk parameters.
	mov ax, word [s1_bpb.NumHeads]         ;Heads.
    mov dl, byte [s1_bpb.DriveNumber]	   ;*Disk Number.	
	mov cl, byte [s1_bpb.SectorsPerTrack]  ;Sectors Per Track.
	mov ch, byte 0                         ;Nothing. 
	mov di, word [CylinderNumbers]         ;Cylinders.
	;BPB.
	mov si, word s1_bpb                    ;BPB. ;ds:si = 0:si
	;Done.
Step9:	
    ;Go!
	PUSH STAGE2_SEGMENT
	PUSH STAGE2_OFFSET
	RETF
	
	;mov si, msg_s1_error
	;jmp s1printError
	
;Print error.
;IN: si = string pointer.	
s1printError:	
    call displayMessage
s1Hang:
    ;hlt
    jmp s1Hang
;--	
 
;
;-----------------------------------------------------------;
;
 
;
; Funções internas do Stage1.
;
  
;****************************************************************************
; s1_ReadSectors:
; Reads "cx" sectors from disk starting at "ax" into memory location "es:bx".
; Lê 'cx' setores do 'disco' começando em 'ax' e coloca na memória em 'es:bx'
;****************************************************************************
;stage1ReadSectors:
s1_ReadSectors:
s1_mainloop:
    mov di, word 0x0005  ;Five retries for error.
.SECTORLOOP:
    push ax
    push bx
    push cx
    call s1_LBACHS
	mov ax, 0x0201                       ;BIOS read sector. Read one sector. 
    mov ch, BYTE [s1_absoluteTrack]      ;Track
    mov cl, BYTE [s1_absoluteSector]     ;Sector.
    mov dh, BYTE [s1_absoluteHead]       ;Head.
    mov dl, BYTE [s1_bpb.DriveNumber]    ;Drive.
.rSec:
    int 0x13                             ;Invoke BIOS.
    jc .rSec                             ;Test for read error.
.SUCCESS:
    mov si, msg_s1_progress
    call displayMessage
    pop cx
    pop bx
    pop ax
    add bx, WORD [s1_bpb.BytesPerSector]    ;Queue next buffer.
    inc ax                                  ;Queue next sector.
    loop s1_mainloop                        ;Read next sector.
    ret	

	
;***************************************************************************
; s1_LBACHS:
;     Convert "ax", LBA addressing scheme, to CHS addressing scheme.
;
; absolute sector = (logical sector / sectors per track) + 1.
; absolute head   = (logical sector / sectors per track) MOD number of heads.
; absolute track  = (logical sector / (sectors per track * number of heads)).
;***************************************************************************
s1_LBACHS:    
    xor dx, dx                           ;Prepare dx:ax for operation.                 
	div WORD [s1_bpb.SectorsPerTrack]    ;Divide por SPT - 11h.
	inc dl                               ;Adjust for sector 0.    
    mov BYTE [s1_absoluteSector], dl
	xor dx, dx                           ;Prepare dx:ax for operation.
    div WORD [s1_bpb.NumHeads]               
    mov BYTE [s1_absoluteHead], dl
    mov BYTE [s1_absoluteTrack], al
    ret

;----------------------------------
; displayMessage:
;     Display ASCIIZ string at "ds:si" via BIOS.
;
displayMessage:
    lodsb                 ;Load next character.
    or al, al             ;Test for NULL character.
    jz .DONE
    mov ah, 0x0E          ;BIOS teletype.
	mov bx, 0x0007    ;Display page 0, Text attribute.
    int 0x10              
    jmp displayMessage
.DONE:
    ret

;
; Área de dados. ----------------------
;	

;
; Variáveis.
;	
s1_absoluteSector db 0x00
s1_absoluteHead   db 0x00
s1_absoluteTrack  db 0x00
vbr_lba:          dw 0

;
; Mensagens.
; 
msg_s1_progress db ".",0

; Salvando variáveis.
CylinderNumbers:  dd 0	

;
; Pointer Table:
; =============
; Quatro (4) ponteiros principais para identificadores do MBR.
;
PointerTable:
;.Cyl                  dw CylinderNumbers 
.SystemName           dw s1_OEM_ID     ;O nome poderá ser longo
.SystemVersion        dw s1_VERSION    ;A versão poderá ser longa.
.SystemBPB            dw s1_bpb        ;O BPB poderá ficar em quaquer lugar do MBR.
.SystemSignature      dw 0xAA55        ;Assinatura do sistema.


;
; Partition Table:
; ================
;

;
;partição 0 - (8MB)
;
;vbr  - ?  ;134  (depende do tanto de setores reservados.)
;fat1 - 136
;fat2 - 200
;root - 264
;data - 296
;

;
;Partition Table Format.
;
;0x01BE: 0x80                - Bootable flag (0x00 for flag off, 0x80 for on).
;0x01BF: 0x00 0x00 0x00      - Starting head, cylinder and sector.
;0x01C2: 0x00                - File system descriptor.
;0x01C3: 0x00 0x00 0x00      - Ending head, cylinder and sector.
;0x01C6: 0x00 0x00 0x00 0x00 - Starting sector (relative to start of disk).
;0x01CA: 0x00 0x00 0x00 0x00 - Number of sectors in partition.
;

;Colocando a partition table no lugar certo.(0x1BE).
    TIMES 446-($-$$) DB 0  ;0x1BE
	
	
GRAMADO_PARTITION_TYPE EQU 4    ;;O Mesmo que o DOS fat16.	
	
;partition 0. 
P0:
.flag:                db  0x80            ;0 ativa.
.hcs_inicial:         db  1, 1, 0      
.os_type:             db  GRAMADO_PARTITION_TYPE  ;4 = FAT16 < 32MB ;0x0E FAT16, (32MB to 2GB), (LBA Support).
.hcs_final:           db  0, 0, 0
.lba_inicial:         dd  0x3F            ; Setor inicial da partição. (63, vbr)
.tamanho_da_particao: dd  (31*1024*1024)  ; quantidade de setores na partição.
;partitions 1, 2 and 3.
P1: dd 0,0,0,0
P2: dd 0,0,0,0
P3: dd 0,0,0,0  
	
;;
;;  os_type (4) DOS 16-bit FAT (up to 32M) partition type descriptor.
;;	
	
;
; Assinatura para MBR de discos com setores de tamanho 512 bytes.
;	
SECTOR_512BYTES_SIG:
    DB 0x55
	DB 0xAA	
	
;
; @todo:
;     Com o novo tamanho padrão se setor
;     a assinatura deve mudar de lugar.
;
; TIMES xxxxx -($-$$) DB 0  	
	
;SECTOR_4KB_SIG:
    ;DB 0x55
	;DB 0xAA	

	
;
; End.
;
