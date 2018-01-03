;
; File: main.asm 
;
; Descrição:
;     Esse é o arquivo principal de BM.BIN.
;     O objetivo é carregar BL.BIN na memória e passar o comando para ele.
; 
;     *** Importante: @todo: Um novo nome deve ser criado.
;     Arquivo principal do System4Nora. (Começa com o BM).
;
; *Importante:
; O arquivo main.asm faz uma sequencia de inclusões de módulos
; que compõem o Boot manager, começando pelos módulos de 16bit
; e depois os módulos de 32bit. O arquivo header32.inc deve ficar no 
; início das inclusões dos módulos de 32bit, para que os módulos
; de 32bit possam utiliza-lo adequadamente.
;
;Sobre o sistema System4Nora:
;========================================
;
;    O sistema é chamado SYSTEM.VHD.
;    É um VHD de 32 MB feito em assembly. (NASM).
;    Comtém 4 programas compilados juntos.
;    São eles:
;    
;       1, Boot Manager (16 e 32 bit).
;       2, Boot Loader (32 bit). (@todo)
;       3, Kernel (32 bit).      (@todo)
;       4, Browser (32 bits).    (@todo)
;       
;    Obs: 
;    ====
;        *IMPORTANTE: Os 4 programas do System4Nora
;                     podem usar as bibliotecas de 32bit
;                     que pertencem ao Boot Manager.
;
;       *O System4Nora permite a inicialização no Modo Texto e
;        e no Modo Gráfico. A seleção do modo é feita no arquivo stage2.inc.
;        mas a seleção do modo de inicilização poderá ser feita pelo
;        usuário administrador e pelo desenvolvedor.
;
;  1) Sobre o Boot Manager do System4Nora:
;       Faz a inicialização em 16 bits.
;
;  2) Sobre o Boot Loader do System4Nora:
;       É um Boot Loader interno que carrega o kernel interno
;
;  3) Sobre o Kernel do System4Nora:
;         O Kernel é mínimo, monotarefa.
;         Tecnologia semelhante ao DPMI.
;         Os recursos do System4Nora podem
;         ser acessados através de um Shell interno.
;         usado pelo desenvolvedor para gerenciamento de
;         inicialização.         
;       
;  4) Sobre o Browser do System4Nora:
;        O Browser é a interface gráfica. É a área de trabalho onde
;        aparecerão as páginas em html, os atalhos para as aplicações
;        ou os gerenciadores do sistema.
;        Essa inteface gráfica assim como o shell interno será
;        usada para gerenciamento de inicialização.
;
;Sobre o subsistema:
;===================
;    O subsistema é chamado SYSTEM.BIN.
;    É um programa em user mode feito em C.
;    Serão usados os códigos do Boot Loader em C e
;    do Kernel em C, já feitos.
;    A atribuição do subsistema é ser uma interface
;    entre as aplicações em user mode e o kernel em assembly.
;     
; Sobre as aplicações:
; ===================
;     As aplicações são programas feitos em C 32bit.
;     Rodam em user mode.
;
; @todo: Filtrar as informaçoes abaixo nesse comentário.
;
; Sobre o Boot Manager contido no System4Nora:
; ============================================
;     O Boot Manager é a primeira parte do System4Nora, ele começa com um MBR 
; em 16bit e stage 2 em 16bit depois muda pra 32bit.
; 
;     Arquivo principal do Boot Manager.
;     M0 - Módulos em ring0.
;
;     Boot Manager 16bit via BIOS.
;     Para HD IDE.
;     Tamanho = 32KB.
;
; Atribuições: 
; ===========
;+
;+ É carregado em 0x7C00 pelo bios.
;+ Copia o stage 1 para 0x0E00 e executa.
;+ Carrega o stage 2 em 0x1000 e executa.
;+ Carrega Boot Loader do System4Nora em 0x00020000.
;+ Executa Boot Loader do System4Nora em (entry point 0x00021000).
;+
;
; Partes:
;1 - Boot         - Stage 1, Stage 2 e pm.inc.
;2 - Boot Manager - Núcleo do Boot Manager. 
;
; Funcionamento:
;+ O stage 1(MBR) é carregado em 0x7C00 pelo BIOS.
;+ O stage 1 carrega à si próprio para 0x0E00. 
;+ O stage 1 carrega o resto do Boot Manager (stage2,os) para 0x00001000.
;+ O stage 2 inicializa o hardware.(setup).
;+ O Boot Manager carrega o Boot Loader e passa o comando para ele. 
;
; Video modes:
; ============
; VirtualBox:
; Oracle VirtualBox: 0x????   640x480x24bpp
; Oracle VirtualBox: 0x0115   800x600x24BPP
; Oracle VirtualBox: 0x0118  1024x768x24BPP
;
; Nvidia GeForce:  
; GeForce_8400_GS equ 0x06E4  
; GeForce 8400 GS: 0x0115   800x600x32BPP
;
; Obs: A resolução usada por enquanto em 32bit é 800x600x24BPP.
; 
; Continua ...
;
; OBS: 
;     O Boot Loader (BL.BIN) pode querer configurar o modo de vídeo. Então ele 
; salva o modo no metafile e reinicia a máquina. Para isso o Boot Manager deve 
; apenas pegar o valor que esta no metafile e não editar o metafile.
;
; Autor: Frederico Martins Nora - (frednora)
;
; Versão 1.0, Copyright (c) 2005 ~ 2016. 
;---------------------------------------------------

;;
;; codename db 'curitiba'
;;

;;
;; O arquivo foi carregado em 0:8000. Fica mais fácil lidar com a gdt 
;; configurando o org em 0x8000 e colocando os segmentos em 0.
;;

[ORG 0x8000]


;;====================================================
;;    ****    Entry point do Boot Manager    ****    ;;
;;====================================================


;;
;; 16bit: Estamos no primeiro setor do BM.BIN, ele começa em 16bit.
;;


[bits 16]

System4Nora_BootManager:
boot_main:    


;;
;; ===========================================================================
;;

;=================
; Obs: Aqui é oomeço do Stage2 do Boot Manager.
; Saltaremos a área de dados no início do arquivo.
;
; ** PRIMEIRO SETOR DE BM.BIN ** ;;
;    


ROOTDIRSTART EQU (bootmanagerOEM_ID)
ROOTDIRSIZE  EQU (bootmanagerOEM_ID+4)

    jmp bootmanagerSTART

bootmanagerOEM_ID                db "QUASI-OS"
bootmanagerBytesPerSector        dw 0x0200
bootmanagerSectorsPerCluster     db 1
bootmanagerReservedSectors       dw 62
bootmanagerTotalFATs             db 0x02
bootmanagerMaxRootEntries        dw 0x0200
bootmanagerTotalSectorsSmall     dw 0x0000
bootmanagerMediaDescriptor       db 0xF8
bootmanagerSectorsPerFAT         dw 246
bootmanagerSectorsPerTrack       dw 0x11
bootmanagerNumHeads              dw 4
bootmanagerHiddenSectors         dd 5       ;; 1+1+3 (mbr+vbr+reserved sectors depois do vbr)
bootmanagerTotalSectorsLarge     dd 0
bootmanagerDriveNumber           db 0x80
bootmanagerFlags                 db 0x00
bootmanagerSignature             db 0x29
bootmanagerVolumeID              dd 0x980E63F5
bootmanagerVolumeLabel           db "QUASI  BMBM"
bootmanagerSystemID              db "FAT16   "

;;
;; Salvando alguns argumentos passados pelo MBR. 
save_cylinder_numbers: dw 0  ;Número de cilindros do disco.
;;...


    ;;
	;; --------------------------------------------------------------
	;; 'bootmanagerSTART' Recepcionará os argumentos passados pelo MBR.
	;; Obs: O MBR se sacrifica muito para pegar esses argumentos,
	;; devemos recepcioná-los com respeito.
	;;
	;; São eles:
	;; ==========
	;; bx = Magic number.
	;; ax = Number of heads.    (*IMPORTANTE) 
	;; dl = Drive number.       (*IMPORTANTE)
    ;; cl = Sectors per track.  (*IMPORTANTE)
    ;; di = cylinder numbers    (*IMPORTANTE) 
	;; si = offet do ponteiro para o BPB.
	;; ----------------------------------------------------------------
	;;
	
;;====================================================================
;; Real entry point.
bootmanagerSTART:

;;;setupRegisters:
	
    ;;
    ;; Configuranso registradores
    ;;
	
    ;Code located at 0000:0x8000, adjust segment registers.
    cli
	mov ax, 0
    mov ds, ax
    mov es, ax
     
    ;Create stack.
    mov ax, 0x0000
    mov ss, ax
    mov sp, 0x6000  ;;?? Por que aqui ??
    sti
	
	
    ;;
	;; Argumento passado pelo MBR. 
	;;
	
	;Disk number.
	mov byte [bootmanagerDriveNumber], dl
	;mov dh, 0
    mov byte [META$FILE.DISK_NUMBER], dl  
	
	;CMP DL, BYTE 0x80
	;JE __GO

	;int 0x16 
	;int 0x19	

;;getDiskInfo:	
	
    ;;
	;; Pegando informações sobre o disco.
	;;
	
	;;========================================
	
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
	;Number of heads.
	mov word [bootmanagerNumHeads], ax	
	mov word [META$FILE.HEADS], ax
	
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
	mov byte [SectorsPerTrack], al    ;BPB (word).
	;Sectors per track.
	mov ah, 0                                   ;;enviamos apenas 'al' 
	mov word [bootmanagerSectorsPerTrack], ax 	;;enviamos apenas 'al'
    mov word [META$FILE.SPT], ax	
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
	;Número de cilindros do disco.
	mov word [save_cylinder_numbers], ax	
	mov word [META$FILE.CYLINDERS], ax
	
	;;;========================================

   


	;;
	;; Carregar root.
	;;

bootmanagerLOAD_ROOT:
    
	;Compute size of root directory and store in "cx".
    
	xor cx, cx
    xor dx, dx
    mov ax, 0x0020                          ; 32 byte directory entry.
    mul WORD [bootmanagerMaxRootEntries]    ; Total size of directory.
    div WORD [bootmanagerBytesPerSector]    ; Sectors used by directory.
    mov word [ROOTDIRSIZE], ax
	mov cx, ax
	;xchg ax, cx
 
    ;Compute location(LBA) of root directory and store in "ax".
    xor ax, ax
	mov al, BYTE [bootmanagerTotalFATs]                ; number of FATs
    mul WORD [bootmanagerSectorsPerFAT]                ; sectors used by FATs
	add ax, WORD [bootmanagerReservedSectors]          ; adjust for bootsector
    add ax, WORD [bootmanagerHiddenSectors]
	
	mov word [ROOTDIRSTART], ax              ; *** Nesse momento ax contem o setor inicial do root dir ***
	add  ax, cx
    mov WORD [bootmanagerdatasector], ax               ; base of root directory
    ;Read root directory into memory (8000:1000) ?
    ;mov WORD [bootmanagerdatasector], 591  ;;SIMULADO Início da área de dados.
	
	
    mov ax, word [ROOTDIRSTART] ;559                            ;;Início do root.
    mov cx, word [ROOTDIRSIZE] ;1                              ;;Size.
    mov bx, 0x1000                         ;;root_buffer. Copy root dir above bootcode
    call bootmanagerReadSectors

    pusha
    mov si, bootmanagermsgCRLF
    call bootmanagerDisplayMessage
    popa

    ;Debug breakpoint.
    ;jmp $

    ;Browse root directory for binary image.
    mov cx, WORD [bootmanagerMaxRootEntries] ;Load loop counter.
    mov di, 0x1000                           ;root_buffer, 0x1000, locate first root entry. ?
.bootmanagerLOOP:
    push cx
    mov cx, 0x000B                    ; eleven character name
    mov si, bootmanagerImageName      ; image name to find
    pusha
    call bootmanagerDisplayMessage
    popa
    push di
    rep cmpsb                         ; test for entry match
    pop di
    je bootmanagerLOAD_FAT
    pop cx
    add di, 0x0020                    ; queue next directory entry
    loop .bootmanagerLOOP
    jmp bootmanagerFAILURE

    ;;
    ;; Carregar a FAT.
    ;;
	 
;; Se o nome for encontrado.
bootmanagerLOAD_FAT:
    pusha
    mov si, bootmanagermsgFAT
    call bootmanagerDisplayMessage
    popa

    ;Debug breakpoint.
	;mov ah, 0x00
    ;int 0x16

    ; Save starting cluster of boot image.
    mov dx, WORD [di + 0x001A]
    mov WORD [bootmanagercluster], dx             ; file's first cluster.

	;;
	;; #BUGBUG NÃO ESTAMOS CARREGANDO A FAT INTEIRA.
	;;         CARREGAR A FAT INTEIRA DÁ PROBLEMA.
	;;
     
	 
    ; Read FAT into memory (es:bx).?? Onde ??
	; ?? 0:0x1000 ?? Por que ??
	; ?? Qual é o segmento e o offset da FAT ??
	mov ax, 0 
    mov es, ax

    ; Compute location of FAT and store in "ax".
    mov ax, WORD [bootmanagerHiddenSectors]       ; adjust for bootsector.
	add ax, WORD [bootmanagerReservedSectors]	
	;mov ax, 67            ;SIMULADO Onde ?LBA inicial da FAT.?
	mov cx, 8             ;(apenas 8 setores da fat.) (246/2)  ;; metade da fat  WORD [bootmanagerSectorsPerFAT]
	mov bx, 0x1000        ;fat_buffer ; copy FAT above bootcode.
    call bootmanagerReadSectors	

	;;
	;; Nesse momento já carregamos a FAT.
	;;
	 
	;Debug breakpoint. 
	;jmp $
	 
    ; Read image file into memory (0x2000:0)(es:bx)
    	
	;Mensagem.
	mov si, bootmanagermsgImg
    call bootmanagerDisplayMessage

	; Opção de mensagem.
	; mov si, bootmanagermsgCRLF
    ; call bootmanagerDisplayMessage
	 
    ;es:bx para a imagem BL(2000:0)   ... gs para a fat.
	mov ax, 0x2000    
    mov es, ax        ;Destination for image.
    mov bx, 0x0000    ;Destination for image.
     
	;gs:bx para a FAT.
	push bx    ;Salva o offset da imagem.
	
	;FAT segment.
 	mov ax, 0     	
    mov gs, ax     

;; Carregar a imagem. 
bootmanagerLOAD_IMAGE:
    mov ax, WORD [bootmanagercluster]  ;Cluster to read.
    pop bx                             ;Buffer to read into (offset da imagem).
    call bootmanagerClusterLBA         ;Convert cluster to LBA.
	 
    xor cx, cx
    mov cl, BYTE 1    ;[bootmanagerSectorsPerCluster] ;sectors to read.
    call bootmanagerReadSectors
     
	push bx
    ;Compute next cluster.
    mov ax, WORD [bootmanagercluster]    ; Identify current cluster.
    add ax, ax							 ; 16 bit(2 byte) FAT entry.
    mov bx, 0x1000                       ; fat_buffer, offset.
	add bx, ax                           ; Index into FAT.
    ;TESTANDO...
	mov dx, WORD [gs:bx]                 ; Read two bytes from FAT.
.bootmanagerDONE:
    mov WORD [bootmanagercluster], dx    ; store new cluster.
	 
	;EOF.
	cmp dx, 0xFFFF                       ; 0x0FF0 test for end of file.
	jne bootmanagerLOAD_IMAGE
	;jnb bootmanagerLOAD_IMAGE ;Opção. 
bootmanagerDONE:
    
	;Opção de mensagem.
	;mov si, bootmanagermsgCRLF
    ;call bootmanagerDisplayMessage
	
	;;========================
    ;; Atenção:
    ;;     Esse é primeiro setor do BM.BIN, ele irá carregar o arquivo BL.BIN 
	;; e irá passar o comando para o stage 2 do (BM).
    ;;=======================	

    ;Mensagem de sucesso.	 
    mov si, bootmanagermsgOK 
    call bootmanagerDisplayMessage
	
	;Debug breakpoint.
	;jmp $
	
	;; ===================================================================
	;; *Importante:
	;;
	;; >> Nesse momento já conseguimos carregar o BL.BIN em 0x2000:0. Agora 
	;; passamos o comando para o stage2 do BM, onde configuramos o máquina,
	;; entramos em modo gráfico, em modo protegido e por fim entramos no 
	;; mini-shell do BM.
	;; >> Observe que o início do BM está em 16bit. Aproveitamos isso para
	;; carregarmos o arquivo BL.BIN com a ajuda dos recursos do BIOS. Isso
	;; nos oferece um pouco de tranquilidade. Então, já que o BM, cumpriu 
	;; seu principal objetivo logo no início do código, podemos usar o resto 
	;; dele para rotinas mais detalhadas de obtenção de informações sobre a 
	;; arquitetura x86. Assim podemos passar para o BL.BIN o maior número de 
	;; informções possíveis, e deixá-lo em um estado confortável.
	;; Sendo assim, o BM.BIN, pode ser um programa com um tamanho um pouco 
	;; maior, mas talvez isso torne o trabalho o MBR mais difícil.
	;;======================================================================

;	
; Go!	
; Agora saltamos para a trap que existe no início do META$FILE. 
; 
.goToFisrtTrap:	 

	push WORD 0      
    push WORD stage2Trap1  ;Trap 1.
    retf
	;JMP $  ;Fail.
	
	;;Opção.
	;;Obs: Isso funcionou.
	;push WORD 0                 
    ;push WORD stage2Trap8  ;Trap 8.
    ;retf	
	;JMP $  ;Fail.
	
	;;Opção.
	;JMP stage2_main
    ;PUSH CODE_SEGMENT 
	;PUSH stage2Trap2    ;; *fat16 (Padrão) Quando carregado pe stage 1.      
    ;RETF

	
;Fail. 
bootmanagerFAILURE:
	int 0x18
	jmp $
	
	;mov ax, 0x8000 ;0x07C0
    ;mov ds, ax
    ;mov es, ax

    ;mov  si, bootmanagermsgFailure
    ;call  bootmanagerDisplayMessage
    ;mov  ah, 0x00
    ;int  0x16         ; await keypress
    ;int  0x19         ; warm boot computer


;*************************************************************************
; bootmanagerDisplayMessage:
;     Display ASCIIZ string at "ds:si" via BIOS.
;*************************************************************************
bootmanagerDisplayMessage:
    lodsb                                   ; load next character
    or al, al                               ; test for NUL character
    jz .bootmanagerDONE
    mov ah, 0x0E                            ; BIOS teletype
    mov bh, 0x00                            ; display page 0
    mov bl, 0x07                            ; text attribute
    int 0x10                                ; invoke BIOS
    jmp bootmanagerDisplayMessage
.bootmanagerDONE:
    ret
	
;**************************************************************************
; bootmanagerReadSectors:
;     Reads "cx" sectors from disk starting at "ax" into memory location 
; "es:bx".
;     Carrega na memória, em es:bx, 'cx' setores do disco, começando pela 
; LBA 'ax'. 
;**************************************************************************
bootmanagerReadSectors:
	mov WORD [bootmanagerDAPBuffer], bx
	mov WORD [bootmanagerDAPBuffer+2], es
	mov WORD [bootmanagerDAPStart], ax
.bootmanagerMAIN:
    mov di, 0x0005           ;Five retries for error. (8??)
.bootmanagerSECTORLOOP:
    push ax
    push bx
    push cx
	 
    push si
    mov ah, 0x42
    mov dl, 0x80
    mov si, bootmanagerDAPSizeOfPacket
    int 0x13
    pop si
	 
    jnc .bootmanagerSUCCESS                            ; test for read error
    xor ax, ax                              ; BIOS reset disk
    int 0x13                                ; invoke BIOS
    dec di                                  ; decrement error counter
    pop cx
    pop bx
    pop ax
	jnz .bootmanagerSECTORLOOP                         ; attempt to read again
	int 0x18
.bootmanagerSUCCESS:
    mov si, bootmanagermsgProgress
    call bootmanagerDisplayMessage
    pop cx
    pop bx
    pop ax
    add bx, WORD [bootmanagerBytesPerSector]           ; queue next buffer
	cmp	bx, 0x0000  ;;??	
	jne	 .bootmanagerNextSector
	push ax
	mov ax, es
	add	ax, 0x1000
    mov es, ax
	pop ax
.bootmanagerNextSector:
    inc ax                               ; queue next sector
	mov WORD [bootmanagerDAPBuffer], bx    
    mov WORD [bootmanagerDAPStart], ax
    loop .bootmanagerMAIN                ; read next sector
    ret
 
 
;*************************************************************************
; bootmanagerClusterLBA:
; convert FAT cluster into LBA addressing scheme
; LBA = (cluster - 2) * sectors per cluster
;*************************************************************************
bootmanagerClusterLBA:
    sub ax, 0x0002     ; zero base cluster number.
    xor cx, cx
    mov cl, BYTE  1    ;[bootmanagerSectorsPerCluster] ; convert byte to word.
    mul cx
    add ax, WORD 591   ;[bootmanagerdatasector] ; base data sector.
	ret


;;
;; Dados de supporte.
;;
	
;DAP.	
bootmanagerDAPSizeOfPacket  db 10h
bootmanagerDAPReserved		db 00h
bootmanagerDAPTransfer		dw 0001h
bootmanagerDAPBuffer		dd 00000000h
bootmanagerDAPStart		    dq 0000000000000000h

;Sector, Head, Track.
bootmanagerabsoluteSector   db 0x00
bootmanagerabsoluteHead     db 0x00
bootmanagerabsoluteTrack    db 0x00

;Data sector.
bootmanagerdatasector dw 0x0000

;Cluster.
bootmanagercluster dw 0x0000

;;
;; Messages and strings.
;;

;File name.
bootmanagerImageName    db "BL      BIN" ,0x0D, 0x0A,0x00

;strings.
bootmanagermsgFAT		db  0x0D, 0x0A,"Loading FAT", 0x0D, 0x0A, 0x00
bootmanagermsgImg		db "L... I", 0x0D, 0x0A, 0x00
bootmanagermsgFailure   db 0x0D, 0x0A, "ROOT", 0x00
bootmanagermsgFail		db "Read",0x00
bootmanagermsgSearch    db "S",0
bootmanagermsgProgress  db "*", 0x00
bootmanagermsgOK        db "#",0
bootmanagermsgCRLF      db 0x0D, 0x0A, 0x00
;;...



;=================
; Obs: Aqui é o fim do Stage1 do Boot Manager.
;

;;
;; ***************************************************************
;;	
	
;=================
; Obs: Aqui é oomeço do Stage2 do Boot Manager.
;
	
	
	
	
	
[bits 16]
	;Stage 2.
	;Esse é o segundo setor.
    ;*Daqui pra frente temos código de inicialização.	
	;; ** SEGUNDO SETOR ** ;;
	
	;;
	;;=====================================================
	;;
	
	;;%include "stage2.inc"       ;Inicialisa a arquitetura presente.(setup).
	
;
; Gramado Boot Manager - This is the stage 2 for the boot manager.
; It's a 16bit/32bit program to make some basic system initialization and 
; to load the Boot Loader program.
; (c) Copyright 2015-2017 Fred Nora.
;
; File: stage2.inc
;
; It starts on second sector.
;
; *Importante:
; O arquivo stage2.inc faz uma sequência de inclusões de módulos
; de 16bit que compõem o stage2. Os promeiros devem ser s2metafile.inc 
; e s2header.inc que servirão de suporte para todos os outros modulos
; do stage2.
;
; *IMPORTANTE:
;      É IMPRESSINDÍVEL A POSSIBILIDADE DE CARREGAR O 'BOOT LOADER' USANDO 
; OS RECURSOS DO BIOS DE 16BIT. Esse arquivo deve chamar a rotina de 
; carregamento de arquivo. Obs: Já está implementada a rotina de carregar 
; um setor usando fat16 em 16bit usando recursos do BIOS.   
;
; Atribuições:
;     +1 - Configura o sistema. 
;     +2 - Entra no modo de inicialização configurado. 
;
; Modo de vídeo do Boot Manager:
; =============================
;     O Boot Manager usa o modo de texto, mas configura o modo de video
; de acordo com as especificações do metafile que está no segundo setor.
;
; Estado dos registradores:
; ========================
; O 'stage2 e o resto do Boot Manager' são carregados em 0000h:1000h pelo 
; stage1 (MBR).
; O stage 2 inicia com os seguintes valores nos registradores:
;
;       ;cs:ip. 
;       CS = 0x0000
;       IP = 0x1000
;
;       ;Segmentos.
;       DS = 0x0000
;       ES = 0x0000
;
;       ;ss:sp. 
;       SS = 0x0000
;       SP = 0x0E00
;
;       SI = Bios Parameter Block
;
;       BX = Magic number (0xF0ED).
;       AX = Number of heads.
;       DL = Drive number.
;       CL = Sectors per track.
;
; Memory map:
; ==========
;     +VBR        = 8000:7c00 (Primeiro setor da partição ativa).
;     +FAT        = 6000:0000
;     +ROOT       = 4000:0000
;     +BootLoader = 2000:0000
;
; Informações sobre as partições:
; ==============================
; Partição 0 - (31MB).
;     vbr  - ?    
;     fat1 - ?
;     fat2 - ?
;     root - ?
;     data - ?
; Partição 1 - Não usada.
; Partição 2 - Não usada.
; Partição 3 - Não usada.
;
; OBS: 
; É importante receber bem os parâmetros de disco passados pelo stage1. 
; O stage2 salva os parâmetros de disco no META$FILE carregado na memória. 
; (volátil).  
;
; Histórico:
;     2015 - Created.
;     2016 - Revision.
;     2017 - Revision.
;     ...  
;



[BITS 16] 


;
; Algumas constantes usadas pelo stage 2.
; Obs: Por conveniência, o desenvolvedor pode manipular essas constantes.
;

;;Tipos de bootloader que poderão ser carregados pelo boot manager.
;BOOTLOADER_TYPE_NONE      EQU 0  ;Sem tipo definido. Negligenciado.
;BOOTLOADER_TYPE_GRAMADO   EQU 1  ;Boot Loader do sistema operacional Gramado.
;BOOTLOADER_TYPE_MULTIBOOT EQU 1  ;Usando o padrão multiboot.
;BOOTLOADER_TYPE_UNKNOW    EQU 2  ;Desconhecido.
;;...

;==========================================
; *Importante:
;     nesse momento determinamos a localização, no disco, dos elementos do 
; sistema de arquivos FAT16.
; Não é isso o que queremos. Essas informações precisam ser obtidas através 
; de rotinas de sondagem. 
;

;stage 2.
CODE_SEGMENT   equ 0
DATA_SEGMENT   equ 0  
STACK_SEGMENT  equ 0
STACK_POINTER  equ 0x6000 

;vbr.
VBR_SEGMENT    equ 8000H
VBR_OFFSET     equ 7C00H
VBR_LBA        equ 63    

;fat.
FAT_SEGMENT    equ 6000H
FAT_OFFSET     equ 0
FAT_LBA        equ 67    

;root.
ROOT_SEGMENT   equ 4000H
ROOT_OFFSET    equ 0
ROOT_LBA       equ 559    


;;========================
;; Aqui está a localização do bootloader na memória. 
;; A LBAnão importa, pois ele foi carregado do sistema sistema de 
;; arquivos e a LBA inicial dele estava armazenada na entrada do 
;; diretório raiz.
;;

;Boot Loader.
BL_SEGMENT     equ 2000H
BL_OFFSET      equ 0
BL_LBA         equ 0    
 

;--------------------------------------- 
;Algum suporte para cores no modo texto. 
;BLUE    equ     01f00h
;RED     equ     02f00h        
;GREEN   equ     04f00h


;========================================================================
; stage2_main:
;     Início do stage 2. 
;     O stage 2 começa com um metafile. No início do metafile tem uma trap 
; para o real início do stage 2.
;     O endereço do stage 2 é 0000H:1000H.
;     O stage 2 fica no segundo setor do disco.
;-------------------------------------------------
stage2_main:

    ;
	; Includes.
	;

	;metafile.
    ;*IMPORTANTE	
	;Obs: (No início do metafile tem uma trap para AFTER_DATA).
	%include "s2metafile.inc"
    
	;header.
	%include "s2header.inc"
	
	;bpb.
	%include "s2bpb.inc"
	
	;dados.
	%include "s2gdt.inc"
	%include "s2vesa.inc"      
	%include "s2config16.inc"    ;Configurações de inicialização.

	;lib.
	%include "s2a20.inc"
	%include "s2lib.inc"	
    %include "s2fat12.inc"
	%include "s2fat16.inc"
    %include "s2menu16.inc"
	%include "s2modes.inc"
	%include "s2detect.inc"
	%include "lib16.inc"  ;;lib16
	;;continua ...

	
	
;;
;; @todo: Criar essas traps lá em baixo desse arquivo, em 16bit mesmo.
;;	

;;procisório.
;stage2Trap1:  ;;Essa trap está localizada logo abaixo.
stage2Trap2:
stage2Trap3:
stage2Trap4:
stage2Trap5:
stage2Trap6:
stage2Trap7:
stage2Trap8:
    ;nop         ;;@todo: Traps não implementadas.
	mov si, msg_stage2_trap_fail
	call DisplayMessage 
	jmp $
	
msg_stage2_trap_fail db 'BM: stage2 TRAP FAIL',0


	
;------------------------------------------
; AFTER_DATA:
;     Início real do stage 2.
;     A primeira coisa a se fazer é salvar os parâmetros de disco passados 
; pelo stage1.
;
; Argumentos recebidos:
;     bx = Magic number. (autorização)
;     ax = Number of heads.
;     dl = Drive number.
;     cl = Sectors per track.
;     si = BPB.
;
AFTER_DATA:
    nop
stage2Trap1:  

   ;;
   ;; *Suspendendo alguns argumentos porque no MBR está faltando espaço.
   ;;   
   
	;Confere a autorização. (Magic Number)
	;cmp bx, word 0xF0ED
	;jne s2_FAILURE
	
	;;
	;; META$FILE.
	;;
	
	;;Initialize variables in the META$FILE.
stage2InitializeMetafile:
    ;nop
.saveMagicNumberMetafile:    	; * Salva o magic number no metafile.
	;mov word [META$FILE.MAGIC_NUMBER], bx     ;magic number.
.diskParametersMetafile:       	; * Salva os parâmetros de disco no META$FILE.
	
	;;#bugbug. não salvaremos no metafile porque ja fizemos isso no início do bm.
	
	;mov word [META$FILE.S1_BPB_POINTER], si   ;Ponteiro para o BPB do stage 1, do MBR.		
	;Disk Number, heads, spt, cylinders.
	;mov byte [META$FILE.DISK_NUMBER], dl      ;Disk number.
	;mov word [META$FILE.HEADS], ax            ;Heads.
	;mov byte [META$FILE.SPT], cl              ;SPT, Sectors Per Track.
	;mov word [META$FILE.CYLINDERS], di        ;Cylinders, Quantidade de cilindros, (Word).
	;@todo: Talvez o stage1 passe mais argumentos, talvez em ch.
	;...
	
	;;
	;;    ****    BPB    ****
	;;

	;Configura e inicializa alguns BPBs.
stage2BPBSupport:
	
	;;
	;; FAT16 BPB.
	;;
	
	; * Salva os parâmetros do disco no BPB do módulo de fat16.
.diskParameters_fat16_bpb:
	;Disk Number, heads, spt.
    ;mov byte [fat16_bpb.DriveNumber], dl      ;Disk number.
	;mov word [fat16_bpb.NumHeads], ax         ;Heads.
	;mov byte [fat16_bpb.SectorsPerTrack], cl  ;SPT, Sectors Per Track.
    ;...	
		
	;;
	;; S2 BPB.
	;;
	
	; * Salva os parâmetros do disco no BPB do stage2.
.diskParameters_s2_bpb:	
	; Disk Number, heads, spt.
	;mov byte [s2_bpb.DriveNumber], dl         ;Disk number.
	;mov word [s2_bpb.NumHeads], ax            ;Heads.
	;mov byte [s2_bpb.SectorsPerTrack], cl     ;SPT, Sectors Per Track.
    ;...	
	
	;;
	;; SAVE POINTERS.
	;;
	
stage2SavePointers:
    ;nop	
.s1BPBPointer:  ;Em 16bit.	
	;mov word [salva_s1_bpb], si    ;stage1 bpb.	
	;mov word [g_Stage1BPB], si     ;stage1 bpb.	
.s2BPBPointer:  ;Em 16bit.
	;mov ax, word s2_bpb
	;mov word [g_Stage2BPB], ax     ;stage2 bpb.
.sfat16BPBPointer:  ;Em 32bit.
   ; xor eax, eax	
	;mov ax, word fat16_bpb
	;mov word [g_Fat16BPB], ax     ;fat16 bpb.
		
	;
	; Inicializações ...
	;
	
stage2Initializations:	
	;nop
	
    ;
	; Configuração de vídeo.
	; Set text output with certain attributes to be bright, and not blinking.
	;
	
    ;mov eax, 1003h                       
    ;mov ebx, 0                            
    ;int 10h
	
.showMessages:	
	
	
HERE:	
	mov ax, 0 ;0x0800
	mov ds, ax
	mov es, ax 
	
	;Boot Manager Splash.
	mov si, msg_bm_splash
	call DisplayMessage 	
	
	;Message.
	;mov si, msg_s2_init
	;call DisplayMessage 
	
	;Debug.
	;jmp $
	
	
;;
;; ****  TESTANDO SE O BL.BIN ESTÁ NA MEMÓRIA ****
;;	
;; Se não estiver, tentaremos mais uma vez carrega-lo usando recursos do BIOS.
;; Porém não vamos carregar o ROOT nem a FAT novamente, vamos supor que pelo menos
;; isso o MBR fez direito.
;;
	
;;
;; ROOT DIR ADDRESS = 0:0xA000 (CHECAR SE É POSSIVEL.)
;; FAT ADDRESS = 0x5000:0x0200 (CHECAR SE É POSSIVEL.)
;; 
;;	
	
;; Checar se a assinatura PE está na memória, se estiver, pularemos e
;;a etapa de carregamento do arquivo.	
.checkSig:
    mov ax, 0x2000
	mov gs, ax 
	
	;;testando o 4C
	xor bx, bx
    mov al, byte [gs:bx] ; 0x2000:0 
	cmp al, byte 0x4C ;'L' primeiro byte
    jne .sigNotFound

	;;testando o 01
	mov bx, 1
    mov al, byte [gs:bx] ; 0x2000:1 
	cmp al, byte 0x01  ;;segundo byte
    jne .sigNotFound
	
	;; Se os dois char não estão ausentes, significa que o arquivo eta no lugar.
	jmp .sigFound
	
;;A assinatura não foi encontrada, o arqui não está na memória.	
.sigNotFound:
    ;;message: o arquivo não esta presente na memória.
	mov si, stage2_msg_pe_sig
	call DisplayMessage
;.searchFile: ;;procurar e carregar.
;;tentaremos pela segunda vez carregar o arquivo.
.sigHalt:
    hlt	
	jmp .sigHalt
	
;;a assinatura foi encontrada ... prosseguimos com o stage2.
.sigFound:
    ;;message: o arquivo esta presente na memória.
	mov si, stage2_msg_pe_sigOK
	call DisplayMessage
	;jmp $	
	
	;debug mostrar 'L'
	;push ds
    ;push es
    ;push si
    ;mov ax, 0x2000 
    ;mov ds, ax
    ;mov es, ax	
   	;mov si, 0
	;call DisplayMessage
    ;pop si
    ;pop es
    ;pop ds	

	;;?? fail???
	;debug: mostrar o entry point. (Æ..€..BÆ..€...Æ.)
	;push ds
    ;push es
    ;push si
    ;mov ax, 0x2000 
    ;mov ds, ax
    ;mov es, ax	
   	;mov si, 0x1000
	;call DisplayMessage
    ;pop si
    ;pop es
    ;pop ds	
	
	;;
	;; O arquivo me parece estar corrompido, foi carregado com setores desordenados... coisa que não acontece com a rotina de 32bit.
	;;
	
	;DEBUG:   **** USAR BASTANTE ESSE DEBUG PARA TER CERTEZA QUE TEMOS TODO O ARQUIVO ONDE QUEREMOS.
	;;REPETIR ESSE DEBUG EM OUTRAS PARTES DO BM ... EM MUITAS PARTES SE PRECISO ... FAZER ALGO SEMELHANTE EM 32BIT
	;jmp $
	
	
	
    ;Turn off FDC motor.
.turnoffFDCMotor:	
	mov dx, 3F2h 
    mov al, 0 
    out dx, al
	
    ;Setup registers.
.setupRegisters:	
    cli
	;Data.
	mov  ax, 0; 0x0800 ;DATA_SEGMENT    ;0.        
    mov  ds, ax
    mov  es, ax
	;mov  fs, ax    ;Unused       
	;mov  gs, ax    ;Unused    
	;Stack.
	XOR AX, AX
    mov ss, ax
    mov sp, 0x6000 ;STACK_POINTER
	;General purpose.
	xor ax, ax
	xor bx, bx
	xor cx, cx
	xor dx, dx
	sti
	
.setupA20:
	
	;Enable a20 line.
	pusha
    call A20_enable
	popa
	
	;Message
	mov si, msg_a20
	call DisplayMessage

	;jmp $
	
    ;
	; Detect Hardware:
	; ================
	; Detecta hardware presente usando rotinas de 16 bits via BIOS.
	; Obs: É possível detectar vários componente de hardware usando os 
	; recursos oferecidos pelo BIOS. Esses parametros serão salvos no 
	; META$FILE, passados para Boot Loader, que passara para o Kernel.
	;

.detectHardware:
	
	;Message
	;mov si, msg_detect_harware
	;call DisplayMessage
    ;call DetectionMain
	
	;
	; @todo:
	;     Tentando carregar o boot loader (BL.BIN)
	; usando uma rotina em modo real.
	; AX = ?? "BL      BIN"
	;
	;; Status: Essa rotina esta funcionando parcialmente.
	;; @todo: Fazer debug dessa rotina e corrigir as partes 
    ;; que não são eficazes.
	;;
.readingFile:
	

	;;
	;; Carregaremos o BL usando os recursos do BIOS antes de entrarmos no shell do bm, que está em 32bit.
	;; @bugbug Nessa versão essa função está incompleta.
	
	;mov ax, word s2header_boot_loader_name
	;call s2fat16ReadFile    ;;s2fat16.inc
	
	
	
    ;
	; Configurando o modo de inicialização do Boot Manager:
	; ====================================================
	; Seleciona um modo de inicializaçao para o Boot Manager.
	; A opção está salva no metafile do Boot Mananger.
	; Opções:
	;     +1 ~ Shell do boot manager.
	;     +2 ~ GUI
	;
    
	;
	; Configura o metafile. META$FILE.INIT_MODE = al
	;

.setupBootMode:
	;Message
	mov si, msg_selecting_videomode
	call DisplayMessage
	
	;JMP $

	;;
	
.preSelection:	
	mov al, byte BOOTMODE_SHELL
	;mov al, byte BOOTMODE_GUI
	call set_boot_mode	

	;;
	;; *Importante:
	;;  A partir de agora sempre inicializaremos no modo shell,
	;; pois temos um comando que inicializa o modo gráfico.
	;;

	;
	; video:
	; Faz a primeira seleção de modo de video. Salvando o modo no metafile.
	; + 0x4115 is 800x600x24bit	(*gui) (3 bytes por pixel) (0xrrggbbrrggbb).
	;
		
	mov word [META$FILE.VIDEO_MODE], 0x115   
	;mov ax, 0x115
	;call set_video_mode

	
	; Ativar o modo escolhido.
	JMP s2modesActivateMode    ;(lib16\s2modes.inc) 
	JMP $
	
	
stage2_msg_pe_sig   db "BM:stage2Initializations: *PE SIG",0
stage2_msg_pe_sigOK db "BM:stage2Initializations: SIG OK",13,10,0	
	
;;============================================
;; stage2Shutdown:
;;     Desliga o computador via APM, using BIOS.
;;     Obs: Isso é um teste.
;;     #Funcionou, Criar um comando no shell do boot manager para isso.	
;;                 isso pode ser chamado quando uma aplicação em user mode
;;                 chamar uma rotina de retorno para o modo real.
;;
stage2Shutdown:	
    ;Connect to APM API
    MOV     AX, 5301h
    XOR     BX,BX
    INT     15h

    ;Try to set APM version (to 1.2)
    MOV     AX, 530Eh
    XOR     BX,BX
    MOV     CX, 0102h
    INT     15h

    ;Turn off the system
    MOV     AX, 5307h
    MOV     BX, 0001h
    MOV     CX, 0003h
    INT     15h

    ;Exit (for good measure and in case of failure)
    RET	
	
;
; End.
;


	
	
	
	
	;pm
	%include "pm.inc"	        ;Comuta para o modo protegido.

;--------------------------------------------------------
; 32 bits - (Boot Manager 32bit Asm.)
;--------------------------------------------------------
[bits 32]
bootmanager_main:

	;
	; Em ordem de prioridade na compilação.
	;
	
	;14, Header principal. 
	;Definições globais usadas em 32bit.
	;Header principal em 32 bits.
	%include "header32.inc"	    

	;13, Headers. 
	%include "system.inc"       ;Arquivo de configuração do sistema.
	%include "init.inc"   	    ;Arquivo de configuração da inicialização.
	%include "sysvar32.inc"     ;Variáveis do sistema.
    %include "gdt32.inc"        ;Gdt.
    %include "idt32.inc"        ;Idt.
    %include "ldt32.inc"        ;Ldt.
    %include "tss32.inc"        ;Tss.
    %include "stacks32.inc"     ;Stacks.
    %include "ints32.inc"       ;Handles para as interrupções.
	%include "fat16header.inc"	;Headers para o sistema de arquivos fat16.
		
    ;12, Monitor.
    %include "screen32.inc"     ;Rotinas de screen em 32 bits.
    %include "input32.inc"      ;Rotinas de input 2m 32 bits.
    %include "string32.inc"     ;Rotinas de strings em 32 bits.
    %include "font32.inc"       ;Fonte.

	;11, Hardware.
    %include "cpuinfo.inc"      ;Rotinas de detecção e configuração de cpu.
    %include "hardware.inc"     ;Rotinas de detecção e configuração de hardware.
	;...

	;10, Irqs.
	%include "timer.inc"        ;Irq 0, Timer.
    %include "keyboard.inc"     ;Irq 1, Keyboard.
    %include "fdc32.inc"        ;Irq 6, Fdc. (@todo: Suspender o suporte.)
	%include "clock.inc"        ;Irq 8, Clock.
	%include "hdd32.inc"        ;Irq 14/15, Hdd.
	;...

    ;9 - Tasks. (#no tasks)
    %include "tasks32.inc"     ;Rotinas de inicialização do sistema de tarefas.

    ;8 - lib32.	
    %include "lib32.inc"       ;Rotinas em 32 bits.

	;7 - setup  
	%include "setup.inc"       ;Inicializa arquitetura.

	;6 - Disk.
	%include "fat12pm.inc"     ;FAT12 em 32 bits.
	%include "fat16lib.inc"    ;FAT16 (rotinas).
    %include "fat16.inc"       ;FAT16 (funções principais).
	%include "ramfs.inc"       ;RamDisk fs.
    %include "format.inc"      ;Formata.
	%include "fs32.inc"        ;fs, (gerência os sistemas de arquivos).	
	
	;5 - File.
    %include "installer.inc"   ;Instala metafiles em LBAs específicas.
	%include "file.inc"        ;Operações com aquivos.
	%include "bootloader.inc"  ;Carrega o Boot Loader (BL.BIN).

	;4 - Debug.
	%include "debug.inc"       ;System debug.

	;3 - blconfig.
	%include "blconfig.inc"    ;Gerência a inicialização.

	;2 - Boot Manager Mini-Shell.
	%include "shell.inc"       ;Prompt de comandos.
    
	;1 - Start.
	%include "start.inc"


;;===============================================
;;    ****    INÍCIO DO BOOT LOADER    ****    ;;
;;===============================================

System4Nora_BootLoader:
    %include "bl.inc"
    ;;Nothing for now!
    jmp $


;;==========================================
;;    ****    INÍCIO DO KERNEL    ****    ;;
;;==========================================
System4Nora_Kernel:
    %include "kernel.inc"
    ;;Nothing for now!
    jmp $

	
;;===========================================
;;    ****    INÍCIO DO BROWSER    ****    ;;
;;===========================================
System4Nora_Browser:
    %include "browser.inc"
    ;;Nothing for now!
    jmp $

	
	

	
;;
;; *Ok, Chegamos no limite, para que o stage 2 continue com o mesmo
;; tamanho precisamos simplicar algum código e economizar caracteres.
;;
	
;;=========================================================
;; eof:                                                   ;
;;     End of file.                                       ;
;;     This is the end of Boot Manager.                   ;
;;     PS: The char 'b' is the number 62H                 ;
;;                                                        ;  
eof:                                                      ; 
    ;times (63*512) - (eof-boot_main) -(3) db 'b' ;63 s.   ;
    ;times (63*512) - (eof-boot_main) db 0  	 ;63 s.   ;
    ;times (32*1024)-(eof-boot_main) db 0  	     ;32 KB.  ;
.bmSignature:                                             ;
    ;db '*BM'                                              ;
;;=========================================================

root_buffer:
fat_buffer:

;
;fim.
;


