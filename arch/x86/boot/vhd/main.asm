;;
;; Gramado VHD - Esse é o arquivo principal de um VHD que será montado em 
;; assembly usando nasm. 
;; (c) Copyright 2017 - Fred Nora.
;;
;; File: main.asm 
;;
;; Descrição:
;;     Criaremos um VHD usando nasm. O arquivo principal, main.asm, é o 
;; MBR do VHD e tem por objetivo carregar o BM.BIN na memória em 0:8000h e 
;; passar o comando para ele, além de passar argumentos.
;;
;;     Também estão presentes no arquivo principal, o VBR no setor 63, 
;; incluido em hexadecimal para compatibilidade com sistema host na hora de 
;; carregar os arquivos para dentro do VHD. Os marcadores de início das duas 
;; FATs, o marcador de setores reservados, o marcador de diretório raiz,
;; o marcador de início da área de dados e por fim o footer do vhd.
;;     O arquivo principal só inclui o MBR, que por conveniência fica de fora
;; podendo ser subtituido na hora do teste.
;;     @todo: Podemos incluir também o VBR que está em hexadecimal.
;;     @todo: Agora que o BM.BIN é carregado ddo sistema de arquivos, temos
;; a opção de configurarmos uma GPT logo após o MBR.
;;
;;    O modo de vído usado é o modo texto, herdado do BIOS.
;; O modo de vídeo não será alterado no MBR.
;;
;;
;; Histórico:
;;     2017 - Created by Fred Nora.
;;     ...
;;


;;
;; codename db 'londrina'
;;

;;
;; A origem fica em 0, e os segmentos são configurados em 0x7c0, pois
;; o BIOS carrega o MBR em 0x07c0:0, ou seja 0x7c00.
;;


[ORG 0]



;;===========================================
;;    ****    Entry point do MBR    ****    ;;
;;===========================================


;16bit. Entry point do MBR.
[bits 16]


System4Nora_BootManager:
boot_main:
    ;Stage 1.


	;*Esse é o MBR, a rotina nela carrega o stage 2.
	;; ** PRIMEIRO SETOR ** ;;
    %include "QUASI-OS.ASM"


;;
;; Segue um deslocamento para colocar o VBR no lugar certo.
;;


;;=========================================================
;; eof:                                                   ;
;;     End of file.                                       ;
;;     This is the end of Boot Manager.                   ;
;;     PS: The char 'b' is the number 62H                 ;
;;                                                        ;  
eof:                                                      ; 
	times (63*512) - (eof-boot_main) db 'b' ;63 sec.
;;=========================================================

	
;;=========================================================
;;                      ## VBR ##   #63
;;=========================================================

;; fs_fat16_vbr:
;;     VBR
;;     O VBR da primeira partição fica no setor 63. #63
;;
fs_fat16_vbr:

;;
;; VBR para a partição de boot no estilo (Microsoft).
;; O volume começa no setor 63 com esse VBR (boot sector do volume).
;; A FAT1 fica no setor 67, a FAT2 fica no setor ??, o root dir fica 
;; no setor 559 a área de dados começa no setor 591.
;;	
   
    ;#opções:
    ;incluir o VBR editado em outro arquivo.
    ;%include "vbrhex1.inc" 
    ;%include "vbrhex2.inc"
	;... 


;;	
;;  ## VBR ##	
;;

;; unsigned char JumpInstruction[3];
db 0xEB, 0x3C, 0x90

;; unsigned char OemName[8];
;; Compatibilidade com host.
db "MSDOS5.0" 
;;db 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2E, 0x30

;; unsigned short BytesPerSector;
;; 0x0200
;;Bytes per Sector. The size of a hardware sector. 
;;For most disks in use in the United States, 
;;the value of this field is 512.
db 0x00, 0x02

;;  unsigned char SectorsPerCluster;
;; Sectors Per Cluster. The number of sectors in a cluster. 
;; The default cluster size for a volume depends on the volume size 
;; and the file system.
db 0x01

;; ? 
;; unsigned short NumberOfReservedSectors;
;; O número de setores reservados que ficam entre o vbr e a primeira fat.
;; #bugbug o certo é 3, mas não consigo mudar sem dar problemas.
;; Reserved Sectors. The number of sectors from the Partition Boot Sector 
;; to the start of the first file allocation table, *(including) the 
;; Partition Boot Sector. The minimum value is 1. 
;; If the value is greater than 1, it means that the bootstrap code 
;; is too long to fit completely in the Partition Boot Sector.
db 0x04, 0x00 


;; unsigned char NumberOfFATs;
;; Number of file allocation tables (FATs). 
;; The number of copies of the file allocation table on the volume. 
;; Typically, the value of this field is 2.
db 0x02 

;; unsigned short NumberOfRootDirectoryEntries;
;; 0x0200
;; Root Entries. The total number of file name entries 
;; that can be stored in the root folder of the volume. 
;; One entry is always used as a Volume Label. 
;; Files with long filenames use up multiple entries per file. 
;; Therefore, the largest number of files in the root folder is 
;; typically 511, but you will run out of entries sooner if you 
;; use long filenames.
db 0x00, 0x02

;; ??
;; unsigned short TotalSectorCount16;
;; Small Sectors. The number of sectors on the volume if 
;; the number fits in 16 bits (65535). For volumes larger than 65536 sectors, 
;; this field has a value of 0 and the Large Sectors field is used instead.
db 0x00, 0xF8 ;;63488 (31MB)

;; ??
;; unsigned char Media;
;; media descriptor. ok.
;; Media Type. Provides information about the media being used. 
;; A value of 0xF8 indicates a hard disk.
db 0xF8

;; ??
;; unsigned short SectorsPerFAT;
;; Sectors per file allocation table (FAT). 
;;Number of sectors occupied by each of the file allocation tables 
;;on the volume. By using this information, together with the 
;;Number of FATs and Reserved Sectors, you can compute where 
;;the root folder begins. By using the number of entries in the root folder, 
;;you can also compute where the user data area of the volume begins.
db 0xF6, 0x00 

;; ??
;; unsigned short SectorsPerTrack;
;; Sectors per Track. The apparent disk geometry in use when 
;;the disk was low-level formatted.
db 0x3F, 0x00 

;; ??
;; unsigned short NumberOfHeads;
;; Number of Heads. The apparent disk geometry in use when 
;;the disk was low-level formatted.
db 0x04, 0x00
;;db 0x08, 0x00

;; ??
;; unsigned long NumberOfHiddenSectors;
;; ?? Hidden Sectors. Same as the Relative Sector field in the Partition Table.

db 0x3F, 0x00, 0x00, 0x00 ;;@todo: talvez sejam os 63 escondidos.
;;db 0x01, 0x00, 0x00, 0x00 

;; ??
;; unsigned long TotalSectorCount32;
;; Large Sectors. If the Small Sectors field is zero, 
;;this field contains the total number of sectors in the volume. 
;;If Small Sectors is nonzero, this field contains zero.
db 0x00, 0x00, 0x00, 0x00 

;; unsigned char DriveNumber;
;; Physical Disk Number. This is related to the BIOS physical disk number. 
;;Floppy drives are numbered starting with 0x00 for the A disk. 
;;Physical hard disks are numbered starting with 0x80. 
;;The value is typically 0x80 for hard disks, regardless of how many 
;;physical disk drives exist, because the value is only relevant if 
;;the device is the startup disk.
db 0x80

;; ??
;; unsigned char Reserved1;
;; Current Head. Not used by the FAT file system.
;; @todo: precisa ser 0.
db 0x01

;; unsigned char ExtendedBootSignature;
;; Signature. Must be either 0x28 or 0x29 in
;; order to be recognized by Windows NT.
db 0x29

;; ??
;; #importante
;; unsigned long VolumeSerialNumber;
;; Volume Serial Number. A unique number that is created when you 
;; format the volume.
db 0xE3, 0x50, 0xB1, 0x6E



;; unsigned char VolumeLabel[11];
;; Volume Label. This field was used to store the volume label, 
;; but the volume label is now stored as special file in the root directory.
db "GRAMADO VBR"
;db 0x4E, 0x4F, 0x20, 0x4E, 0x41 
;db 0x4D, 0x45, 0x20, 0x20, 0x20 
;db 0x20, 0x46, 0x41, 0x54

;; unsigned char FileSystemType[8];
;; System ID. Either FAT12 or FAT16, depending on the format of the disk.
db "FAT16   "
;db 0x31, 0x36, 0x20, 0x20
;db 0x20, 0x33, 0xC9, 0x8E


;;
;; ?? Ainda não sei se posso usar outra coisa aqui nessa área de código.
;;

;; unsigned char BootCode[448];
db 0xD1, 0xBC, 0xF0, 0x7B, 0x8E, 0xD9, 0xB8, 0x00, 0x20, 0x8E, 0xC0, 0xFC, 0xBD, 0x00, 0x7C, 0x38 
db 0x4E, 0x24, 0x7D, 0x24, 0x8B, 0xC1, 0x99, 0xE8, 0x3C, 0x01, 0x72, 0x1C, 0x83, 0xEB, 0x3A, 0x66
db 0xA1, 0x1C, 0x7C, 0x26, 0x66, 0x3B, 0x07, 0x26, 0x8A, 0x57, 0xFC, 0x75, 0x06, 0x80, 0xCA, 0x02
db 0x88, 0x56, 0x02, 0x80, 0xC3, 0x10, 0x73, 0xEB, 0x33, 0xC9, 0x8A, 0x46, 0x10, 0x98, 0xF7, 0x66
db 0x16, 0x03, 0x46, 0x1C, 0x13, 0x56, 0x1E, 0x03, 0x46, 0x0E, 0x13, 0xD1, 0x8B, 0x76, 0x11, 0x60
db 0x89, 0x46, 0xFC, 0x89, 0x56, 0xFE, 0xB8, 0x20, 0x00, 0xF7, 0xE6, 0x8B, 0x5E, 0x0B, 0x03, 0xC3
db 0x48, 0xF7, 0xF3, 0x01, 0x46, 0xFC, 0x11, 0x4E, 0xFE, 0x61, 0xBF, 0x00, 0x00, 0xE8, 0xE6, 0x00
db 0x72, 0x39, 0x26, 0x38, 0x2D, 0x74, 0x17, 0x60, 0xB1, 0x0B, 0xBE, 0xA1, 0x7D, 0xF3, 0xA6, 0x61
db 0x74, 0x32, 0x4E, 0x74, 0x09, 0x83, 0xC7, 0x20, 0x3B, 0xFB, 0x72, 0xE6, 0xEB, 0xDC, 0xA0, 0xFB
db 0x7D, 0xB4, 0x7D, 0x8B, 0xF0, 0xAC, 0x98, 0x40, 0x74, 0x0C, 0x48, 0x74, 0x13, 0xB4, 0x0E, 0xBB
db 0x07, 0x00, 0xCD, 0x10, 0xEB, 0xEF, 0xA0, 0xFD, 0x7D, 0xEB, 0xE6, 0xA0, 0xFC, 0x7D, 0xEB, 0xE1
db 0xCD, 0x16, 0xCD, 0x19, 0x26, 0x8B, 0x55, 0x1A, 0x52, 0xB0, 0x01, 0xBB, 0x00, 0x00, 0xE8, 0x3B
db 0x00, 0x72, 0xE8, 0x5B, 0x8A, 0x56, 0x24, 0xBE, 0x0B, 0x7C, 0x8B, 0xFC, 0xC7, 0x46, 0xF0, 0x3D
db 0x7D, 0xC7, 0x46, 0xF4, 0x29, 0x7D, 0x8C, 0xD9, 0x89, 0x4E, 0xF2, 0x89, 0x4E, 0xF6, 0xC6, 0x06
db 0x96, 0x7D, 0xCB, 0xEA, 0x03, 0x00, 0x00, 0x20, 0x0F, 0xB6, 0xC8, 0x66, 0x8B, 0x46, 0xF8, 0x66
db 0x03, 0x46, 0x1C, 0x66, 0x8B, 0xD0, 0x66, 0xC1, 0xEA, 0x10, 0xEB, 0x5E, 0x0F, 0xB6, 0xC8, 0x4A
db 0x4A, 0x8A, 0x46, 0x0D, 0x32, 0xE4, 0xF7, 0xE2, 0x03, 0x46, 0xFC, 0x13, 0x56, 0xFE, 0xEB, 0x4A
db 0x52, 0x50, 0x06, 0x53, 0x6A, 0x01, 0x6A, 0x10, 0x91, 0x8B, 0x46, 0x18, 0x96, 0x92, 0x33, 0xD2
db 0xF7, 0xF6, 0x91, 0xF7, 0xF6, 0x42, 0x87, 0xCA, 0xF7, 0x76, 0x1A, 0x8A, 0xF2, 0x8A, 0xE8, 0xC0
db 0xCC, 0x02, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0x80, 0x7E, 0x02, 0x0E, 0x75, 0x04, 0xB4, 0x42, 0x8B
db 0xF4, 0x8A, 0x56, 0x24, 0xCD, 0x13, 0x61, 0x61, 0x72, 0x0B, 0x40, 0x75, 0x01, 0x42, 0x03, 0x5E
db 0x0B, 0x49, 0x75, 0x06, 0xF8, 0xC3, 0x41, 0xBB, 0x00, 0x00, 0x60, 0x66, 0x6A, 0x00, 0xEB, 0xB0
db 0x42, 0x4F, 0x4F, 0x54, 0x4D, 0x47, 0x52, 0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x52, 0x65, 0x6D
db 0x6F, 0x76, 0x61, 0x20, 0x64, 0x69, 0x73, 0x63, 0x6F, 0x73, 0x20, 0x6F, 0x75, 0x80, 0x01, 0x01
db 0x00, 0x04, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00
db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

;; unsigned short Signature;
db 0x55, 0xAA


;;
;;  ## RESERVED SECTORS ##
;;

;;========================================================
;; fs_reserved_sectors:
;;     Setores reservados. (3 setores)
;;
fs_reserved_sectors:
    times (512) db 'r' ;64
    times (512) db 'r' ;65
    times (512) db 'r' ;66

	
;;
;;  ## FAT 1 ##
;;


;;========================================================
;; fs_fat16_fat1:
;;     Aqui começa a primeira FAT.  #67
;;     Cada fat tem 246 setores
;;
fs_fat16_fat1: 
.firstSector:	
	db 0xf8, 0xff, 0xff, 0xff
    times (512)-(4) db 0
.allTheRest:	
    times (245*512) db 0 


;;
;;  ## FAT 2 ##
;;
	
;;========================================================
;; fs_fat16_fat2:
;;     Aqui começa a segunda FAT.    #313
;;     Cada fat tem 246 setores
;;
fs_fat16_fat2:
.firstSector:
	db 0xf8, 0xff, 0xff, 0xff
    times (512)-(4) db 0
.allTheRest:
    times (245*512) db 0 


;;
;;  ## ROOT DIR ##
;;
	
;;========================================================
;; fs_fat16_rootdir:
;;     Aqui começa o diretório raiz. #559
;;     
;;	
fs_fat16_rootdir:
.firstEntry:   

    ;; ## Volume1 entry ##
	
    db 0x47, 0x52, 0x41, 0x4D, 0x41, 0x44, 0x4F, 0x20
	db 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00 
	db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0x7B
	db 0x1B, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    
	;; Completando o diretório raiz do volume de boot.
	;; 512 entradas de 32 bytes cada.
	
	times (32*512) - (32) db 0    

	
;;
;;  ##  DATA AREA  ##
;;

;;=========================================================================
;; fs_fat16_data_area:                                                    ;
;;     DATA AREA.               #591                                      ;
;;                                                                        ;
fs_fat16_data_area:                                                       ;
    
	;;
	;; Essa área compreende o espaço entre o início da área de dados 
	;; da primeira partição até o fim do disco virtual, onde deve ficar o 
	;; footer do vhd conectix da Microsoft.
	;; Nesse caso o disco tem 32MB. Esse será o padrão de tamanho para 
	;; discos vhd usados pelo Gramado.
	;; Outras opções de tamanho serão criadas depois.
	;; Obs: Outra partição poderá ser criada dentro desse espaço.
	;;      Será a partição do sistema, usando o sistema de arquivos ext2.
	;;
	
    ;;
    ;; Completaremos com zeros até o fim do disco.
    ;; 32MB menos a área já utilizada pelas partes criadas anteriormente,
	;; menos 4 bytes de assinatura antes do footer.
	
	;Full data area with zeros.                                           ;
	times  (32*1024*1024) -( fs_fat16_data_area - boot_main ) -(4) db 0  ;
		
.end_of_disk:                                             ;
    db '*EOD'  ;; ## END OF DISK ##                                                              ;
;;=========================================================================


;;=============================================================
;; vhd_footer:
;;     VHD FOOTER.
;;
;VHD_FEATURES  EQU  0  ;features
;VHD_FILE_FORMAT_VERSION  EQU 0x00001000 ;file format version 
;VHD_CREATOR_APP EQU 0x61766D6A  ;;0x6A,0x6D,0x76,0x61 ;creator app
;VHD_PLATFORM_VERSION EQU 0x0A000400
;VHD_PLATFORM_CODE_WI2R  EQU  0x57693272  ;WI2R
;VHD_PLATFORM_CODE_WI2K  EQU  0x5769326B  ;WI2K
;VHD_PLATFORM_CODE_W2RU  EQU  0x57327275  ;W2RU
;VHD_PLATFORM_CODE_W2KU  EQU  0x57326B75  ;W2KU
;VHD_PLATFORM_CODE_NONE  EQU  0           ;NONE
;VHD_PLATFORM_CODE_MAC   EQU  0x4D163220  ;MAC
;VHD_PLATFORM_CODE_MACX  EQU  0x4D163258  ;MACX
;VHD_PLATFORM_TEST  EQU  0x6B326957       ;já funcionou.
;VHD_PLATFORM  EQU  VHD_PLATFORM_TEST 
;VHD_ORIGINAL_SIZE_PART1 EQU 0
;VHD_ORIGINAL_SIZE_PART2 EQU 0x00000001 ;16MB
;VHD_ORIGINAL_SIZE_PART2 EQU 0x00000002 ;32MB
;VHD_CURRENT_SIZE_PART1 EQU 0
;VHD_CURRENT_SIZE_PART2 EQU 0x00000001 ;16MB   
;VHD_CURRENT_SIZE_PART2 EQU 0x00000002 ;32MB   
;VHD_FOOTER_DISK_GEOMETRY_CYLINDER    EQU  0xC303  ;*49923
;VHD_FOOTER_DISK_GEOMETRY_HEADS       EQU  4       ;*4
;VHD_FOOTER_DISK_GEOMETRY_SECTORS     EQU  0x11    ;*17
;VHD_FOOTER_DISK_TYPE  EQU  2  ;FIXED   0x02000000
;VHD_FOOTER_DISK_TYPE  EQU  3  ;DYNAMIC
;VHD_FOOTER_DISK_TYPE  EQU  4  ;DIFFERENCING 
;VHD_FOOTER_CHECKSUM EQU 0xDBE6FFFF ;vhdSize=32MB partitionSize=8
;VHD_FOOTER_CHECKSUM EQU 0xDBE6FFFF ;vhdSize=32MB partitionSize=16
;VHD_FOOTER_CHECKSUM EQU 0xD0E8FFFF ;vhdSize=32MB partitionSize=16
;VHD_FOOTER_CHECKSUM EQU 0xC2E7FFFF ;funcionou com vhdsize=32MB patitionSize=32MB.
;;...
;;
;;
vhd_footer:
    ;;
.cookie:
	db 'conectix'
.features:
	dd 0
.version:
    dd 0x00001000
.dataOffset:
    dd 0xFFFFFFFF,0xFFFFFFFF
.timeStamp:
    dd 0x5868091E
.creatorApp:
    db 0x6A,0x6D,0x76,0x61
.creatorVersion:
    dd 0x0A000400
.creatorOS:
    dd 0x6B326957
.originalSyze:
	dd 0, 0x00000002    ;bytes.
.currentSyze:
    dd 0, 0x00000002    ;bytes.
.diskGeometry:
    dw 0xC303           ;# Cylinders.
    db 4                ;# Heads.
    db 0x11             ;# Sectors.
.diskType:
    dd 0x02000000       ;fixed.
.chechsum:
    dd 0xC2E7FFFF
.uniqueID:
	db 0x11, 0x80, 0xF2, 0x62
	db 0xD4, 0x95, 0x65, 0x44
    db 0x88, 0x4E, 0x78, 0x5A
	db 0x58, 0xBF, 0x82, 0xCE
.savedState:
	db 0
.reserved:
	times 427 db 0


;
;fim.
;


