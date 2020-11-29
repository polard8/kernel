;
; File: fs\fat16header.inc
;
; Descrição:
;     Header de suporte para o módulo fat16 do Boot Manager.
;     O Mass Storage Manager oferece suporte ao sistema de arquivos fat16 
; em 32bit.
;     O propósito principal é carregar o sistema operacional se ele estiver 
; em um sistema de arquivos fat16.
;
; 2015 - Created by Fred Nora.
;


;
; Defines.
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
; # DEFINIÇÕES GLOBAIS PARA FAT1, FAT2, ROOT, DATAAREA,
;   SOMENTE PARA TESTE
;   PODEM SER ALTERADAS MANUALMENTE NA HORA DA COMPILAÇÃO.
;

;Fat16
GLOBAL_FAT1       EQU   0
GLOBAL_FAT2       EQU   0
GLOBAL_ROOTDIR    EQU   130  ;test
GLOBAL_DATAAREA   EQU   0

;Boot Loader
GLOBAL_BOOTLOADER_LBA  EQU 296
GLOBAL_BOOTLOADER_SIZE EQU 64


;
; Boot Manager, BM.BIN.
;

FAT16_BM_ADDRESS  equ 0x00000E00
FAT16_BM_LBA      equ 0 


;
; Boot Loader, BL.BIN.
;

IMAGE_ADDRESS              equ 0x00020000   
IMAGE_ADDRESS_ENTRY_POINT  equ 0x00021000   
IMAGE_SIZE                 equ 64   ;GLOBAL_BOOTLOADER_SIZE ;@todo: Tamanho do Boot Loader. ??
IMAGE_LBA                  equ 296  ;GLOBAL_BOOTLOADER_LBA  ;@todo: LBA inicial do Boot Loader. ??


;
; Data Area.
;
DATAAREA_LBA  equ 296    ;@todo: Início da área de dados  da partição 0. ??    


;
; Boot Loader, BL.BIN.
;

FAT16_IMAGE_ADDRESS              equ 0x00020000 
FAT16_IMAGE_ADDRESS_ENTRY_POINT  equ 0x00021000
FAT16_IMAGE_LBA                  equ 1088 ;296       ;Início da área de dados.

;                                                      
; MBR.
;

FAT16_MBR_ADDRESS  equ 0x00020000    ;@todo: Checar esse endereço.	
FAT16_MBR_LBA      equ 0             ;(@todo: Talvez em alguns discos deva ser lba 1.)


;
; Partição 0, Padrões do sistema.
;

;
; #BUGBUG
; @todo: 
;     Valores errados. Configurar, ou detectar ...
;

;Valores para formatação com imdisk. (volume 31mb)
FAT16_VBR_ADDRESS       equ 0x001A0000  ;0x00020000.
FAT16_VBR_LBA           equ 63 ;134         ;vbr.
FAT16_FAT_ADDRESS       equ 0x001B0000  ;0x00060000.
FAT16_FAT_LBA           equ 67 ;136         ;fat1. 
FAT16_ROOTDIR_ADDRESS   equ 0x001C0000  ;0x00080000.
FAT16_ROOTDIR_LBA       equ 559 ;264         ;root.
FAT16_DATAAREA_ADDRESS  equ 0x00100000
FAT16_DATAAREA_LBA      equ 591 ;296         ;data. 
 
 
 
;
; As quatro partições.
; 
 
;Partição 0.
P0_VBR_ADDRESS       equ 0x00020000
P0_VBR_LBA           equ 63; 134         ;vbr.
P0_FAT_ADDRESS       equ 0x00060000
P0_FAT_LBA           equ 136         ;fat1.
P0_ROOTDIR_ADDRESS   equ 0x00080000
P0_ROOTDIR_LBA       equ 496 ;264         ;root. 
P0_DATAAREA_ADDRESS  equ 0x00100000
P0_DATAAREA_LBA      equ 296         ;data.  
;Partição 1.
P1_VBR_ADDRESS       equ 0x00020000
P1_VBR_LBA           equ 0 
P1_FAT_ADDRESS       equ 0x00060000
P1_FAT_LBA           equ 0 
P1_ROOTDIR_ADDRESS   equ 0x00080000
P1_ROOTDIR_LBA       equ 0 
P1_DATAAREA_ADDRESS  equ 0x00100000
P1_DATAAREA_LBA      equ 0 
;Partição 2.
P2_VBR_ADDRESS       equ 0x00020000
P2_VBR_LBA           equ 0 
P2_FAT_ADDRESS       equ 0x00060000
P2_FAT_LBA           equ 0 
P2_ROOTDIR_ADDRESS   equ 0x00080000
P2_ROOTDIR_LBA       equ 0 
P2_DATAAREA_ADDRESS  equ 0x00100000
P2_DATAAREA_LBA      equ 0 
;Partição 3.
P3_VBR_ADDRESS       equ 0x00020000
P3_VBR_LBA           equ 0 
P3_FAT_ADDRESS       equ 0x00060000
P3_FAT_LBA           equ 0 
P3_ROOTDIR_ADDRESS   equ 0x00080000
P3_ROOTDIR_LBA       equ 0 
P3_DATAAREA_ADDRESS  equ 0x00100000
P3_DATAAREA_LBA      equ 0  



;
; Variáveis.
;

fat16_datasector    dw 0x0000
fat16_cluster       dw 0x0000

;
; Globais.
;

g_image_address     dd 0
g_image_entrypoint  dd 0


;
; Reserva espaço para trabalhar o caminho atual.
;

; #todo: 
; Talvez não precise ser tão grande ainda.
CURRENT_PATH:
    TIMES 256 DB 0x00 



;-----------------------
;Caminhos strings.
;
PATH:
    .atual:     dd 0    ;Endereço do nome do caminho atual.	
    .root_p0    db "volume0:/root"   ,0
    .root_p1    db "volume1:/root"   ,0
    .root_p2    db "volume2:/root"   ,0
    .root_p3    db "volume3:/root"   ,0
    .boot_p0    db "volume0:/boot"   ,0
    .boot_p1    db "volume1:/boot"   ,0
    .boot_p2    db "volume2:/boot"   ,0
    .boot_p3    db "volume3:/boot"   ,0	
    .system_p0  db "volume0:/system" ,0
    .system_p1  db "volume1:/system" ,0
    .system_p2  db "volume2:/system" ,0
    .system_p3  db "volume3:/system" ,0
    .user_p0    db "volume0:/user"   ,0
    .user_p1    db "volume1:/user"   ,0
    .user_p2    db "volume2:/user"   ,0
    .user_p3    db "volume3:/user"   ,0
	;...
	
	
;-------------------	
;Volume strings.
; @todo: Tem muita string aqui.
;
; O número do volume não tem relação
; com o disco que o volume está.
; Pois cada volume pode estar em um disco diferente.
;

VOLUME:
    .number: db 0                   ;Número do volume atual.
    .separador     db ":",0
    .atual:        dd 0             ;Endereço do nome do volume atual.
    .boot_manager  db "BM-SHELL",0  ;Estamos no Boot Manager antes de qualquer partição.
    .p0_name       db "volume0" ,0
    .p1_name       db "volume1" ,0
    .p2_name       db "volume2" ,0
    .p3_name       db "volume3" ,0
    .p4_name       db "volume4" ,0
    .p5_name       db "volume5" ,0
    .p6_name       db "volume6" ,0
    .p7_name       db "volume7" ,0
    .p8_name       db "volume8" ,0
    ;...



;Directory strings.
DIRECTORY:
    ;.number:       db 0
    .separador     db "/",0
    .atual:        dd 0            ;Endereço do nome do diretório atual.
    .boot_manager  db 0            ;No caso do Boot Manager.
    .boot          db "/boot"   ,0
    .system        db "/system" ,0
    .user          db "/user"   ,0
    .root          db "/root"   ,0
    ;...


;
; Nome do arquivo.
;
fat16_ImageName      db 0    ;Salva aqui um endereço de um nome de arquivo.
fat16_ImageAddress   dd 0    ;Salva aqui o endereço do nome do arquivo.
fat16_Buffer         dd 0    ;Buffer do arrquivo.    	
	
;
; BPB:
; ====
;
; Partição 0 - (8MB).
;
;vbr  - ?  ;134  (Depende do tanto de setores reservados.)
;fat1 - 136
;fat2 - 200
;root - 264
;data - 296
;	
fat16_OEM_ID: db "FAT16BPB"
;Extended BPB 
fat16_bpb:
	.BytesPerSector:     dw 512
	.SectorsPerCluster:  db 1
	.ReservedSectors:    dw 3
	.TotalFATs:          db 2
	.MaxRootEntries:     dw 512         ;512 entradas de 32bytes = 32 setores.
	.TotalSectorsSmall:  dw 0
	.MediaDescriptor:    db 0xF8
	.SectorsPerFAT:      dw 246          ;64      
	.SectorsPerTrack:    dw 0x11           ;Pegar via BIOS.     
	.NumHeads:           dw 4           ;Pegar via BIOS.        
	.HiddenSectors:      dd 0x00000000
	.TotalSectorsLarge:  dd 0x00000000
	;For extended.
	.DriveNumber:        db 0x80     
	.Flags:              db 0x00
	.Signature:          db 29           ;Extended Boot Signature.
	.VolumeID:           dd 0x980E63F5
	.VolumeLabel:        db "FREDNORA8MB"
	.SystemID:           db "FAT16   "	
	
	
;
; Mensagens.
;

;Status.
msg_fat16_CRLF     db 0x0D, 0x0A, 0x00
msg_fat16_Progress db ".", 0x00
msg_fat16_space    db " ", 0x00
msg_fat16_Loading  db "FAT16: Loading"   ,10,13,0
msg_fat16_Failure  db "FAT16: Error"     ,10,13,0
msg_fat16_Done     db "FAT16: Done"      ,10,13,0
msg_fat16_RootOk   db "FAT16: Root"      ,10,13,0
msg_fat16_FatOk    db "FAT16: FAT Ok"    ,10,13,0
msg_fat16_FatFail  db "FAT16: FAT fail"  ,10,13,0
msg_fat16_diskfail db "FAT16: Disk fail" ,10,13,0

;Steps.
msg_fat16_step1 db "Step1: Calculating DATA AREA",13,10,0
msg_fat16_step2 db "Step2: Loading ROOT"         ,13,10,0
msg_fat16_step3 db "Step3: Searching file"       ,13,10,0
msg_fat16_step4 db "Step4: Loading FAT"          ,13,10,0
msg_fat16_step5 db "Step5: Loading file"         ,13,10,0

; File.
msg_file_ok:
    db "[BM.BIN]: File found", 13, 10, 0
msg_file_not_found: 
    db "[BM.BIN]: File not found! HANG" , 13, 10, 0


;
;fim
;
