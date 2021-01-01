;;
;; File: iso/stage1/stage1.asm
;;
;; Esse e' o stage1 do arquivo .ISO.
;; O propo'sito e' carregar o stage2 que esta' em boot/gramado/stage2.bin 
;; CDFS Bootable ISO9660
;;
;; History:
;; 2018 - Created by Nelson Cole. (Sirius OS)
;; 2019 - Fred Nora. Changing some strings.
;;


;; Offset para o arquivo stage2.bin.
LOADSEG equ 0x8000   

;; Usado para root dir.
LDSBASE equ 0x2000   

        org     0x7c00
        bits    16
        section .text

    ;Salta a área de dados.
    
    jmp 0:start
    
    times 8-($-$$)   	db 0
    BootPvd		 	dd 0
    BootLocationofExtent   	dd 0
    BootDataLength      	dd 0
    BootChecsum 	 	dd 0
    BootRsv times 40  	db 0


start:
    
    ;Segmentos.
    mov ax, cs
    mov ds, ax
    mov es, ax

    ;;salva o número do disco.
    mov byte [bootdevnum], dl

    mov ax, 3
    int 0x10

    mov si, string1
    call Prints

    mov cx, 1
    mov eax, dword[BootPvd]
    mov di,  LDSBASE / 0x10
    xor bx, bx
    call ReadSectors

    mov ax, word [LDSBASE+128]
    mov word [BytesPerSectors], ax

    mov eax, dword [LDSBASE + 156 +2]
    mov dword [LocationofExtent], eax

    mov eax, dword [LDSBASE + 156 + 10]
    mov dword [DataLength], eax

nextsearch:

    xor edx, edx
    xor ebx, ebx
    
    mov eax, dword [DataLength]
    mov bx, word [BytesPerSectors]
    div bx 
    mov cx, ax
    
    cmp dx, 0
    jz .par
    
    inc cx
.par:	
    mov eax, dword [LocationofExtent]
    mov di, LDSBASE / 0x10
    xor bx, bx
    call ReadSectors

    lea bx, [LDSBASE]

    cmp byte [crtl], 1
    jz .SIRIUS
    
    cmp byte [crtl], 2
    jz .STAGE2.BIN
	
.BOOT:
    cmp byte [bx +0], 0
    jz BootError

    mov cx, 5
    lea si, [bx + 33]
    mov di, string3
    cld
    rep cmpsb
    jz .done

    xor ax, ax
    mov al, byte [bx + 0]
    add bx, ax

    jmp .BOOT

  ;; #importante
  ;; Carregando o diretório /gramado

.SIRIUS:

    ;; #importante
    ;; Se o o diretório /gramado não for encontrado.
	
    cmp byte [bx +0], 0
    jz gramadoNotFound 

    ;; ??
    mov cx, 7
    lea si, [bx + 33]
    mov di, string4
    cld
    rep cmpsb
    jz .done

    xor ax, ax
    mov al, byte [bx + 0]
    add bx, ax

    jmp .SIRIUS

    ;; #importante
    ;; Carregando o arquivo stage2.bin

.STAGE2.BIN:
  
    ;; #importante
    ;; Se o arquivo stage2 não for encontrado.

    cmp byte [bx +0], 0
    jz stage2NotFound 

    ;;??
    mov cx, 12
    lea si, [bx + 33]
    mov di, string5
    cld
    rep cmpsb
    jz ExecStage2

    xor ax, ax
    mov al, byte[bx + 0]
    add bx, ax

    jmp .STAGE2.BIN

.done:
    mov eax, dword [bx + 2]
    mov dword [LocationofExtent], eax
    mov eax,dword [bx +10]
    mov dword [DataLength], eax

    inc byte [crtl]
    jmp nextsearch
    
ExecStage2:
    mov eax, dword [bx + 2]
    mov dword [LocationofExtent], eax
    mov eax, dword [bx +10]
    mov dword [DataLength], eax

    xor edx, edx
    xor ebx, ebx
    
    mov eax, dword [DataLength]
    mov bx, word [BytesPerSectors]
    div ebx 
    mov cx, ax
    cmp dx, 0
    jz .par
    inc cx
    
.par:	
    mov eax, dword [LocationofExtent]
    mov di, LOADSEG / 0x10
    mov bx, 0
    call ReadSectors
	
    mov si, goString
    call Prints	

    ;hang
    xor ax, ax
    int 0x16	

    mov dl, byte [bootdevnum]
    push dx
    
    ;; #importante
    ;; Salta para o stage2.bin em 0:0x8000
    
    jmp 0:LOADSEG



;;==================================
;;  ## ERROR MESSAGES ##
;;

gramadoNotFound:
    mov si, gramadoNotFoundString
    call Prints	
    jmp BootError
	
stage2NotFound:
    mov si, stage2NotFoundString
    call Prints
    jmp BootError
	
BootError:
    mov si,string2
    call Prints

    xor ax, ax
    int 0x16
    int 0x19

	
;;data	
PHYSICALDAPA: 
    times 0x10 db 0
    
    
;;=============================================
;; ReadSectors:
;;
;; IN:
;;     cx  = count
;;     di  = Segmento
;;     bx  = Offset
;;     eax = Starting sector LBA47
;;
ReadSectors:
    ;nop
.next:
    
    pusha
    push ds
    
    mov si, PHYSICALDAPA
    mov [si], byte 0x10	; Tamanho da DAP
    mov [si+1], byte 0		; reservado
    mov [si+2], word 1		; Sector count
    mov word [si+4], bx		; Offset
    mov word [si+6], di		; Segment
    mov dword [si+8], eax		; Start sector LBA47
    mov [si+12], dword 0	; Starting sector LBA47
    mov dl, byte [bootdevnum]
    mov ah, 0x42
    
    int 0x13
    jc .err
    
    pop ds
    popa

    push eax
    push edx

    xor dx, dx
    mov ax, word [BytesPerSectors]	
    mov bx, 16
    div bx

    add di, ax

    pop edx
    pop eax

    xor ebx, ebx
    
    add eax,1
    loop .next
    
.end:	
    ret
.err:
    pop ds
    popa
    jmp BootError


;;==========================================
;; Prints
;;     Print message.
;;

Prints:
    pusha
.next:
    cld 
    lodsb
    
    cmp al, 0
    je  .end	
    
    mov ah, 0x0e
    int 0x10
    
    jmp .next
.end:
    popa
    ret

;Next line.
line: 
    db 10, 13,0

;hexa table.
table_hexa db "0123456789ABCDEF"

;;========================
;; putx:
;;     Put hexa.
;;
putx:
    pusha
    
    mov bx,table_hexa
    mov al, dh
    shr al,4
    xlat
    
    mov ah, 0xe
    int 0x10
    
    mov al, dh
    and al,0x0F	
    xlat
    
    mov ah, 0xe
    int 0x10
    
    popa
    ret	


;;========================
;; Printx:
;;     Print hexa.
;;
Printx:
    call putx
    xchg dl, dh
    call putx	
    ret


;data
bootdevnum 		db 0
BytesPerSectors  	dw 0 ; Logical Block Size  
LocationofExtent     	dd 0
DataLength      	dd 0
crtl			db 0


;Strings

string1:
    db 'Gramado: Starting ISO ...',10,13,0
	
string2:   
    db 'CD Bootable Error!',10,13,0

string3:
	db 'BOOT',0	
        
string4:
    db 'GRAMADO',0
    
string5:
	db 'STAGE2.BIN;1',0
	
gramadoNotFoundString:
    db 'gramado folder not found!', 10, 13, 0
	
stage2NotFoundString:
    db 'stage2 not found!', 10, 13, 0
	
goString:
    db 'Press a key to start stage2', 10, 13, 0   


;; Padding
times 2046 - ($-$$) db 0

;;sig
dw 0xaa55


;;
;; End.
;;

