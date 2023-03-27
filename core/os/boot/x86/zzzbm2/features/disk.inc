
;#todo
; Podemos melhorar as rotinas desse modulo
; tornando elas 'callables'. E entao chamar elas
; do arquivo main. Num loop que pode conter
; um dialogo e seleçao entre modo visual ou cli.
; no estilo mikeos.
;

;----------------------------------------------   
; Simply load the root dir.
; 0:0x1000
bootmanager_LOADROOT:

; Compute size of root directory and store in "cx".
    pusha
    xor cx, cx
    xor dx, dx
    mov ax, 0x0020                        ; 32 byte directory entry.
    mul WORD [bootmanagerMaxRootEntries]  ; Total size of directory.
    div WORD [bootmanagerBytesPerSector]  ; Sectors used by directory.
    mov word [ROOTDIRSIZE], ax
    mov cx, ax
    ;xchg ax, cx

; Compute location(LBA) of root directory and 
; store in "ax".

    xor ax, ax
    mov al, BYTE [bootmanagerTotalFATs]        ; Number of FATs.
    mul WORD [bootmanagerSectorsPerFAT]        ; Sectors used by FATs.
    add ax, WORD [bootmanagerReservedSectors]  ; Adjust for bootsector.
    add ax, WORD [bootmanagerHiddenSectors]

; Nesse momento ax contem o setor inicial do root dir.

    mov word [ROOTDIRSTART], ax   
    add  ax, cx
    mov WORD [bootmanagerdatasector], ax     ; base of root directory
    ;Read root directory into memory (0:1000) ?
    ;mov WORD [bootmanagerdatasector], 591  ;;SIMULADO In�cio da �rea de dados.

    mov ax, word [ROOTDIRSTART]  ; Inicio do root.
    mov cx, word [ROOTDIRSIZE]   ; Tamanho do root.
    mov bx, 0x1000               ; root_buffer. Copy root dir above bootcode
    call diskReadSectors  ;bootmanagerReadSectors

    ; not needed
    pusha
    mov si, bootmanagermsgCRLF
    call bootmanagerDisplayMessage
    popa

    ;Debug breakpoint.
    ;jmp $
    popa
     
    ret

;----------------------------

; --------------------------------
; 
search_image_name:

    pusha

    ;Browse root directory for binary image.
    mov cx, WORD [bootmanagerMaxRootEntries]  ; Load loop counter.
    mov di, 0x1000                            ; root_buffer, 0x1000, locate first root entry. ?

._loop:

    push cx  ;++Contador de chars
    mov cx, 0x000B                 ; eleven character name
    ;mov si, bootmanager_ImageName  ; image name to find
    mov si, word [image_name_pointer]
    pusha
    call bootmanagerDisplayMessage
    popa
    push di
    rep cmpsb                       ; test for entry match
    pop di
    je ._image_found  ;bootmanager_LOADFAT
    pop cx  ;--Contador de chars

    add di, 0x0020                  ; queue next directory entry
    loop ._loop

; The image was NOT found in the root directory.
._image_not_found:
    popa
    jmp diskFailure

; The image was found in the root directory.
._image_found:
    pop cx  ;--Contador de chars

    ; 'di' has the pointer to the entry
    ; where we found the image name.

    mov ax, di
    mov word [entry_address], ax
    
    popa
    ret
    
; -------------------------------------
entry_address: dw 0


;---------------------------------------------
; Load FAT
real_load_fat:
; Where? es:bx  0:0x1000

    pusha

    pusha
    mov si, bootmanagermsgFAT
    call bootmanagerDisplayMessage
    popa

; Read FAT into memory (es:bx).?? Onde ??
; ?? 0:0x1000 
; ?? Qual é o segmento e o offset da FAT ??

    pusha
    mov ax, 0 
    mov es, ax
; Compute location of FAT and store in "ax".
    mov ax, WORD [bootmanagerHiddenSectors]    ; adjust for bootsector.
    add ax, WORD [bootmanagerReservedSectors]  ; lba inicial da fat ?.
    mov cx, 8         ; (apenas 8 setores da fat.) (246/2)  ;; metade da fat  WORD [bootmanagerSectorsPerFAT]
    mov bx, 0x1000    ; fat_buffer ; copy FAT above bootcode.
    call diskReadSectors  ;bootmanagerReadSectors
    popa
    
    popa
    ret

; -----------------------------------------
; Load image.
; Read image file into memory (0x2000:0)(es:bx)
; Destination for the image.
; es:bx = (2000:0).
real_load_image:

    pusha

; --------------------------------
; Ajust the image segment.
; Es:bx para a imagem.
    mov ax, 0x2000 
    mov es, ax
    mov bx, 0x0000
; Salva o offset da imagem.
    push bx 

; --------------------------------
; Ajust FAT segment.
; gs:bx para a FAT.
    mov ax, 0 
    mov gs, ax 

; Loading the image.
loop_bootmanager_LOADIMAGE_Sector:
    mov ax, WORD [bootmanagercluster]  ; Cluster to read.
    pop bx                             ; Buffer to read into (offset da imagem).
    call diskClusterLBA  ;bootmanagerClusterLBA         ; Convert cluster to LBA.
    xor cx, cx
    mov cl, BYTE 1    ;[bootmanagerSectorsPerCluster] ;sectors to read.
    call diskReadSectors  ;bootmanagerReadSectors
    push bx
    ;Compute next cluster.
    mov ax, WORD [bootmanagercluster]  ; Identify current cluster.
    add ax, ax                         ; 16 bit(2 byte) FAT entry.
    mov bx, 0x1000                     ; fat_buffer, offset.
    add bx, ax                         ; Index into FAT.
    ;TESTANDO...
    mov dx, WORD [gs:bx]               ; Read two bytes from FAT.
.bootmanagerDONE:
    mov WORD [bootmanagercluster], dx  ; store new cluster.
; EOF
; 0x0FF0 test for end of file.
; Se o loop voltar, então tem o pop em cima,
; se não voltar, entaõ tem o pop em baixo.
    cmp dx, 0xFFFF
    jne loop_bootmanager_LOADIMAGE_Sector
    pop bx

;---------------------------------------
; The image was loaded.
bootmanagerDONE:

    mov si, bootmanagermsgDONE
    call bootmanagerDisplayMessage

    popa
    ret

    ; see: finish.inc
    ;push WORD 0
    ;push WORD AFTER_DATA 
    ;retf

; ========================================
; :)
; Load the image.
; (load fat, root and image).
; IN:
; ax = pointer to the image name.
test_load_bl_image:
; Carregamos uma imagem cujo ponteiro para o nome
; esta e 'ax'.
; #todo:
; Podemos carregar o boot loader e mudarmos para 32bit ou
; uma aplicação em 16 e permanecermos em 16bit.

    pusha

    ;cmp ax, 0
    ;je diskFailure

; save the pointer to the image name
    mov word [image_name_pointer], ax

    ; Simply load the root dir at 0h:0x1000.
    call bootmanager_LOADROOT

    ; Search the name and 
    ; save the entry address in [entry_address]. 
    call search_image_name

; Save starting cluster of boot image.
; Offset '0x001A' of the entry that starts in 'di'.
; After saving we can override the root.
    ; Parameter
    mov ax, word [entry_address]
    mov di, ax
    mov dx, WORD [di + 0x001A]
    mov WORD [bootmanagercluster], dx  ; file's first cluster.

    ; Where? es:bx  0:0x1000
    call real_load_fat

    ;pusha

    ; Message.
    mov si, bootmanagermsgImg
    call bootmanagerDisplayMessage
    
    call real_load_image

    popa
    ret

image_name_pointer: dw 0

;---------------------------------------------
    
; Fail. 
; #todo: Colocar uma mensagem de erro.
bootmanagerFAILURE:
diskFailure:
    int 0x18
    jmp $
    ;mov  si, bootmanagermsgFailure
    ;call  bootmanagerDisplayMessage
    ;mov  ah, 0x00
    ;int  0x16         ; await keypress
    ;int  0x19         ; warm boot computer

; bootmanagerReadSectors:
;     Reads "cx" sectors from disk starting at "ax" into memory location 
; "es:bx".
;     Carrega na mem�ria, em es:bx, 'cx' setores do disco, come�ando pela 
; LBA 'ax'.
diskReadSectors:
;bootmanagerReadSectors:
    mov WORD [bootmanagerDAPBuffer], bx
    mov WORD [bootmanagerDAPBuffer+2], es
    mov WORD [bootmanagerDAPStart], ax
;Five retries for error. (8??)
.bootmanagerMAIN:
    mov di, 0x0005
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

    jnc .bootmanagerSUCCESS    ; test for read error
    xor ax, ax                 ; BIOS reset disk
    int 0x13                   ; invoke BIOS
    dec di                     ; decrement error counter
    pop cx
    pop bx
    pop ax
    jnz .bootmanagerSECTORLOOP    ; attempt to read again
; Fail
    int 0x18

.bootmanagerSUCCESS:
    mov si, bootmanagermsgProgress
    call bootmanagerDisplayMessage
    pop cx
    pop bx
    pop ax
    add bx, WORD [bootmanagerBytesPerSector]    ; queue next buffer
    cmp bx, 0x0000  ;;??
    jne .bootmanagerNextSector
    push ax
    mov ax, es
    add ax, 0x1000
    mov es, ax
    pop ax
.bootmanagerNextSector:
    inc ax                               ; queue next sector
    mov WORD [bootmanagerDAPBuffer], bx    
    mov WORD [bootmanagerDAPStart], ax
    loop .bootmanagerMAIN                ; read next sector
    ret


; ====
; bootmanagerClusterLBA:
; convert FAT cluster into LBA addressing scheme
; LBA = (cluster - 2) * sectors per cluster

diskClusterLBA:
;bootmanagerClusterLBA:
    sub ax, 0x0002     ; zero base cluster number.
    xor cx, cx
    mov cl, BYTE  1    ;[bootmanagerSectorsPerCluster] ; convert byte to word.
    mul cx
    add ax, WORD 591   ;[bootmanagerdatasector] ; base data sector.(#bugbug Valor determinado.)
    ret


; ===============================
; Dados de supporte.

; DAP.
bootmanagerDAPSizeOfPacket  db  10h
bootmanagerDAPReserved      db  00h
bootmanagerDAPTransfer      dw  0001h
bootmanagerDAPBuffer        dd  00000000h
bootmanagerDAPStart         dq  0000000000000000h

; Sector, Head, Track.
bootmanagerabsoluteSector   db 0x00
bootmanagerabsoluteHead     db 0x00
bootmanagerabsoluteTrack    db 0x00

bootmanagerdatasector  dw 0x0000  ; Data sector.
bootmanagercluster     dw 0x0000  ; Cluster.

; ===============================================
; Messages and strings.
; File name.

;bootmanager_ImageName:  db "BL      BIN", 0x0D, 0x0A, 0x00

; Strings.
bootmanagermsgFAT       db  0x0D, 0x0A, "Loading FAT",   0x0D, 0x0A, 0x00
bootmanagermsgImg       db  0x0D, 0x0A, "Loading Image", 0x0D, 0x0A, 0x00
bootmanagermsgFailure   db  0x0D, 0x0A, "ROOT", 0x00
bootmanagermsgFail      db  "Read", 0x00
bootmanagermsgSearch    db  "S", 0x00
bootmanagermsgProgress  db  "*", 0x00
bootmanagermsgDONE      db  0x0D, 0x0A, "DONE", 0x0D, 0x0A, 0x00
bootmanagermsgCRLF      db  0x0D, 0x0A, 0x00
;; ...


;---------------------------------------
;; #todo
;; Change some names here!
bootmanagerOEM_ID             db "GRAMA-OS"
bootmanagerBytesPerSector     dw 0x0200
bootmanagerSectorsPerCluster  db 1
bootmanagerReservedSectors    dw 62
bootmanagerTotalFATs          db 0x02
bootmanagerMaxRootEntries     dw 0x0200
bootmanagerTotalSectorsSmall  dw 0x0000
bootmanagerMediaDescriptor    db 0xF8
bootmanagerSectorsPerFAT      dw 246
bootmanagerSectorsPerTrack    dw 0x11
bootmanagerNumHeads           dw 4
; Hidden sectors:  1+1+3 (mbr+vbr+reserved sectors depois do vbr).
bootmanagerHiddenSectors      dd 5
bootmanagerTotalSectorsLarge  dd 0
bootmanagerDriveNumber        db 0x80
bootmanagerFlags              db 0x00
bootmanagerSignature          db 0x29
bootmanagerVolumeID           dd 0x980E63F5
bootmanagerVolumeLabel        db "GRAMA  BMBM"
bootmanagerSystemID           db "FAT16   "

; Número de cilindros do disco.
; Salvando alguns argumentos passados pelo MBR. 
save_cylinder_numbers: dw 0
; ...

