;
; File: x86/hwlib.inc
;
; Descrição:
;     Hardware Lib.
;     Rotinas de apoio à hw.inc.
;     Nome opcional para padrão 8.3 (hwlib.s)
;
; 2015 - Created by Fred Nora.
;


;1F0 (Read and Write): Data Register
;1F1 (Read): Error Register
;1F1 (Write): Features Register
;1F2 (Read and Write): Sector Count Register
;1F3 (Read and Write): LBA Low Register
;1F4 (Read and Write): LBA Mid Register
;1F5 (Read and Write): LBA High Register
;1F6 (Read and Write): Drive/Head Register
;1F7 (Read): Status Register
;1F7 (Write): Command Register
;3F6 (Read): Alternate Status Register
;3F6 (Write): Device Control Register	

;----------------------------------
; PATA Comandos 
; Cmd (Commands, inside PATA class) 
;
; ReadPio	    0x20 *	 
; ReadPioExt    0x24	 
; ReadDma	    0xC8	 
; ReadDmaExt	0x25	 
; WritePio	    0x30 *	 
; WritePioExt	0x34	 
; WriteDma	    0xCA	 
; WriteDmaExt	0x35	 
; CacheFlush	0xE7	 
; CacheFlushExt	0xEA	 
; Packet	    0xA0	 
; IdentifyPacket    0xA1    PATAPI devices only.
; Identify	    0xEC	 
; Read	        0xA8	 
; Eject	        0x1B	 
;
; 
 
 
 
 
[BITS 32]  


extern _task_switch_status


;
; Globais usadas por read e write.
;

global _hd_buffer
_hd_buffer: dd 0

global _hd_lba
_hd_lba: dd 0



;----------------------------------------------
; _turn_task_switch_on:
;     + Cria um vetor para o timer, IRQ0.
;     + Habilita o funcionamento do mecanismo de taskswitch.
;       Essa função é chamada em microkernel\cpu\start.c
;

global _turn_task_switch_on
_turn_task_switch_on:

    cli 
    ;mov eax,  dword _timer_test ;provisório
    mov eax,  dword _irq0        ;definitivo
    mov ebx, dword 32
    call _setup_idt_vector

    ;recarrega a nova idt (talvez seja necessario)
    ;lidt [IDT_register]

    ;status do mecanismo de taskswitch.
    mov dword [_task_switch_status], dword 1    ;UNLOCKED.
    ret



;-------------------------------------------------------------
; _turn_task_switch_off:
;     Desabilita a IRQ0 responsável por fazer o task switch.
;
global _turn_task_switch_off
_turn_task_switch_off:

    cli
    ;mov eax,  dword _irq0
    mov eax,  dword _timer_test
    mov ebx, dword 32
    call _setup_idt_vector

    ;status do mecanismo de taskswitch.
    mov dword [_task_switch_status], dword 0    ;LOCKED.
    ret


;===================================
; _os_read_sector:
;
; Read sector on PATA PIO 0 MODE.
; IN: [_hd_lba] e [_hd_buffer]
;

global _os_read_sector
_os_read_sector:

    push eax
    push ebx

    ; Uma nova rotina, bem mais rápida.
    ; @param EAX Logical Block Address of sector
    ; @param CL  Number of sectors to read
    ; @param RDI The address of buffer to put data 
    ; obtained from disk
 
    mov eax, dword [_hd_lba]     
    xor ecx, ecx 
    mov cl, 1
    mov edi, dword [_hd_buffer]      

    call ata_lba_read

    pop ebx
    pop eax
    ret


;======================================
; _os_write_sector:
;     Write sector on PATA PIO 0 MODE.
; IN: [_hd_lba] e [_hd_buffer]
;

global _os_write_sector
_os_write_sector:

    push eax
    push ebx

    ; Uma nova rotina, bem mais rápida. 
    ; @param EAX Logical Block Address of sector
    ; @param CL  Number of sectors to write
    ; @param RDI The address of data to write to the disk 

    mov eax, dword [_hd_lba]     
    xor ecx, ecx 
    mov cl, 1
    mov edi, dword [_hd_buffer]      

    call ata_lba_write

    pop ebx
    pop eax
    ret



;==================================================
; ata_lba_read:
;     ATA read sectors (LBA mode) 
;
; @param EAX Logical Block Address of sector
; @param CL  Number of sectors to read
; @param RDI The address of buffer to put data 
; obtained from disk
;
; @return None
;;isso é bem rápido.
;====================================================
;;ide_channel0_master_read:

ata_lba_read:
    
    pushf
    and eax, 0x0FFFFFFF
    push eax
    push ebx
    push ecx
    push edx
    push edi
 
    mov ebx, eax         ; Save LBA in RBX
 
    mov edx, 0x01F6      ; Port to send drive and bit 24 - 27 of LBA
    shr eax, 24          ; Get bit 24 - 27 in al
    or al, 11100000b     ; Set bit 6 in al for LBA mode
    out dx, al
    IODELAY
 
    mov edx, 0x01F2      ; Port to send number of sectors
    mov al, cl           ; Get number of sectors from CL
    out dx, al
    IODELAY
 
    mov edx, 0x1F3       ; Port to send bit 0 - 7 of LBA
    mov eax, ebx         ; Get LBA from EBX
    out dx, al
    IODELAY
 
    mov edx, 0x1F4       ; Port to send bit 8 - 15 of LBA
    mov eax, ebx         ; Get LBA from EBX
    shr eax, 8           ; Get bit 8 - 15 in AL
    out dx, al
    IODELAY
 
    mov edx, 0x1F5       ; Port to send bit 16 - 23 of LBA
    mov eax, ebx         ; Get LBA from EBX
    shr eax, 16          ; Get bit 16 - 23 in AL
    out dx, al
    IODELAY
 
    mov edx, 0x1F7       ; Command port
    mov al, 0x20         ; Read with retry.
    out dx, al
    IODELAY
 
.still_going:  
    in al, dx
    test al, 8           ; the sector buffer requires servicing.
    jz .still_going      ; until the sector buffer is ready.
 
    mov eax, 256         ; to read 256 words = 1 sector
    xor bx, bx
    mov bl, cl           ; read CL sectors
    mul bx
    mov ecx, eax         ; RCX is counter for INSW
    mov edx, 0x1F0       ; Data port, in and out
    rep insw             ; in to [RDI]
 
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax
    popf
    ret


;=========================================
; ata_lba_write:
;     ATA write sectors (LBA mode) 
;
; @param EAX Logical Block Address of sector
; @param CL  Number of sectors to write
; @param RDI The address of data to write to the disk
;
; obs: Escreve apenas no canal 0, master.
;
; @return None
;=================================================
;;ide_channel0_master_write:

ata_lba_write:

    pushf
    and eax, 0x0FFFFFFF
    push eax
    push ebx
    push ecx
    push edx
    push edi
 
    mov ebx, eax         ; Save LBA in RBX
 
    mov edx, 0x01F6      ; Port to send drive and bit 24 - 27 of LBA
    shr eax, 24          ; Get bit 24 - 27 in al
    or al, 11100000b     ; Set bit 6 in al for LBA mode
    out dx, al
    IODELAY
 
    mov edx, 0x01F2      ; Port to send number of sectors
    mov al, cl           ; Get number of sectors from CL
    out dx, al
    IODELAY
 
    mov edx, 0x1F3       ; Port to send bit 0 - 7 of LBA
    mov eax, ebx         ; Get LBA from EBX
    out dx, al
    IODELAY
 
    mov edx, 0x1F4       ; Port to send bit 8 - 15 of LBA
    mov eax, ebx         ; Get LBA from EBX
    shr eax, 8           ; Get bit 8 - 15 in AL
    out dx, al
    IODELAY
 
    mov edx, 0x1F5       ; Port to send bit 16 - 23 of LBA
    mov eax, ebx         ; Get LBA from EBX
    shr eax, 16          ; Get bit 16 - 23 in AL
    out dx, al
    IODELAY
 
    mov edx, 0x1F7       ; Command port
    mov al, 0x30         ; Write with retry.
    out dx, al
    IODELAY
     
.still_going:  
    in al, dx
    test al, 8           ; the sector buffer requires servicing.
    jz .still_going      ; until the sector buffer is ready.
 
    mov eax, 256         ; to read 256 words = 1 sector
    xor bx, bx
    mov bl, cl           ; write CL sectors
    mul bx
    mov ecx, eax         ; RCX is counter for OUTSW
    mov edx, 0x1F0       ; Data port, in and out
    mov esi, edi
    rep outsw            ; out
 
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax
    popf
    ret


;--------------------------------
; _reset_ide0:
;

global _reset_ide0
_reset_ide0:

    push dx
    mov dl, byte 0
    call IDE_RESET_DISK
    pop dx
    ret


;--------------------------------
; init_ide0_master:
;     Reseta o ide0 master.

init_ide0_master:

    push dx
    mov dl, byte 0
    call IDE_RESET_DISK
    pop dx
    ret


;==============================================
; IDE_RESET_DISK:
;
; Some disks will respond to the reset command 
; if the other is given it.
;
; IN: 
;     dl = Drive (0=master,1=slave)
;

IDE_RESET_DISK:

    and dl, 01           ;isolate bit 0.
    mov al, dl           ;al = dl.
    shl al, 4            ;move drive selector into bit 4.
    or al, 0A0h          ;make bits 7 and 5 a 1.

    mov dx, 01F6h        ;dx = drive/head regsiter port address.
    out dx, al           ;write to drive/head register.
    IODELAY

    mov al, 10h                    ;Command 1xh: Recalibrate.
    inc dx                         ;dx is now 01F7h, port address of command register.
    mov byte [lastcommand], 10h    ;Tell our ISR what we are doing.
    out dx, al                     ;Recalibrate.
    IODELAY
 
    mov ax,0FFFFh                 ;loop var = 0FFFFh.
    xor dl,dl
    mov byte [commanddone], dl    ;init commanddone with 0.
again:
    cmp byte [commanddone], 1
    je resetisdone

    cmp ax, 0
    je noreset

    dec ax
    jmp again
resetisdone:
    cli
    mov byte [lastcommand], 01h    ;Set this in case of unexpected command.
    ;sti
    clc    ;its all good.
    ret    
noreset:
    cli
    mov byte [lastcommand], 01h    ;Set this in case of unexpected command.
    ;sti
    stc     ;Error.
    ret                 
; end of IDE_RESET_DISK.
lastcommand db 0    ;The last command given to the disk.
commanddone db 0    ;Command done flag.
commandok   db 0    ;Command completed properly flag.	


;;
;;  ## CMOS ##
;;


;; Hour
global _hour
_hour:          
    db 0

;; Minute
global _minute
_minute:
    db 0

;; Second
global _second
_second: 
    db 0



;==================================
; CMOS_GET_DATE:
;     Pega Hora, Minuto e Segundo.

global _CMOS_GET_DATE
_CMOS_GET_DATE:

    PUSHAD

    ; get the "second" byte.
    MOV  al, 0x00           
    OUT  0x70, AL
    IODELAY
    IN   AL, 0x71 
    IODELAY
    CALL  BCD2bin
    MOV  BYTE [_second], AL

    ; get the "minute" byte.
    MOV  AL, 0x02           
    OUT  0x70, AL
    IODELAY
    IN   AL, 0x71
    IODELAY
    CALL  BCD2bin
    MOV  BYTE [_minute], AL

    ; get the "hour" byte.
    MOV  AL, 0x04           
    OUT  0x70, AL
    IODELAY
    IN  AL, 0x71
    IODELAY
    CALL  BCD2bin
    MOV  BYTE [_hour], AL

    POPAD
    RET


;---------------------------------------------- 
; BCD2bin:
;     Calculate binary from BCD. 
;
;  in:  AL = BCD. 
; out:  AL = bin.
;

BCD2bin:

    PUSH  EBX  
    MOV BL, AL
    AND BL, 0x0F
    SHR AL, 4     ;AL = (AL/16).
    MOV BH, 10
    MUL BH        ;multiply by 10.
    ADD AL, BL    ;add in low nib. 
    POP  EBX
    RET


 
; Enable L2 Cache (Not supported on P4 or Atom)
;	mov ecx, 0x0000011E		; Control register 3: used to configure the L2 Cache
;	rdmsr
;	bts eax, 8			; Set L2 Enabled (Bit 8)
;	wrmsr

; Enable Prefetchers (Not supported on P4 or Atom)
;	mov ecx, 0x000001A0
;	rdmsr
;	and eax, 0xFFF7FDFF		; Clear Hardware Prefetcher Disable (Bit 9) and Adjacent Cache Line Prefetch Disable (Bit 19)
;	and edx, 0xFFFFFFAF		; Clear DCU Prefetcher Disable (Bit 37) and IP Prefetcher Disable (Bit 39)
;	wrmsr
	

; habilita o uso.
;push eax
;mov  eax, cr0
;and  eax, #0x9fff   ;; clear CD and NW
;mov  cr0, eax
;pop  eax
	

;;
;; Keyboard leds.
;;	
	
;SetKeyBoardLeds:
;   push  eax
;   mov   al,0xed                 
;   out   60h,al                 
;KeyBoardWait:
;   in    al,64h
;   test  al,10b                 
;   jne   KeyBoardWait              
;   mov   al,byte [keyBoardStatus]
;   and   al,111b
;   out   60h,al                 
;   pop   eax
;   ret

;exemplo
;   mov   [keyBoardStatus],0xb0    ; Initialise keyboard LED state
;   call  SetKeyBoardLeds      
;--------------------------------- This will toggle CapsLock LED
;   xor   [keyBoardStatus],4
;   call  SetKeyBoardLeds
;---------------------------------
;   and   [keyBoardStatus],0xfb
;   call  SetKeyBoardLeds
; 
;where keyBoardStatus is a byte (It will hold the current keyboard LED state).
;


;
; Configura o counter do PIT.
;set_PIT_count:
;	pushfd
;	cli
;	out 0x40, al        ; Set low byte of reload value
;	rol ax, 8           ; al = high byte, ah = low byte
;	out 0x40, al        ; Set high byte of reload value
;	rol ax, 8           ; al = low byte, ah = high byte (ax = original reload value)
;	popfd
;	ret



	
;;
;; ============================ Mouse support ============================
;;	

; Format Of Mouse Packet Data.
;MOUSE_LEFT_BTN	  EQU 0x01
;MOUSE_RIGHT_BTN	  EQU 0x02
;MOUSE_MIDDLE_BTN  EQU 0x04
;MOUSE_X_SIGN	  EQU 0x10
;MOUSE_Y_SIGN	  EQU 0x20
;MOUSE_X_OVERFLOW  EQU 0x40
;MOUSE_Y_OVERFLOW  EQU 0x80

;Posicionamento do cursor.
;X.
;global _mouse_x
;_mouse_x:
;    dd 0
;Y.
;global _mouse_y
;_mouse_y:
;    dd 0

;Bytes do controlador.
;Status.
;global _mouse_packet_data 
;_mouse_packet_data:
;    db 0
;Delta x.
;global _mouse_packet_x
;_mouse_packet_x:
;    db 0
;Delta y.
;global _mouse_packet_y
;_mouse_packet_y:
;    db 0
;Scroll.
;global _mouse_packet_scroll
;_mouse_packet_scroll:
;    db 0


;;=====================================================
;; _update_mouse:
;;     Updates the mouse position.
;;
;; Credits:
;;     Omar Mohammad. Maadi, Cairo, Egypt.
;;
;global _update_mouse
;_update_mouse:
;    nop

;;======== X ==========	

    ;
	; Testando o sinal de x.
	;

; Do the x pos first.
;.do_x:
	
	;;pega o delta x
	;movzx eax, byte [_mouse_packet_x]
	;testa o sinal para x
	;test byte [_mouse_packet_data], MOUSE_X_SIGN
	;jnz .x_neg

;caso x seja positivo.	
;.x_pos:
	;add [_mouse_x], eax
	;jmp .do_y

;;caso x seja negativo.	
;.x_neg:
	;not al
	;inc al
	;sub [_mouse_x], eax
	;jns .do_y

	;xor eax, eax
	;mov [_mouse_x], eax

	
;;======== Y ==========	

    ;
	; Testando o sinal de x.
	;

; Do the same for y position.	
;.do_y:

	;Pega o delta y.
	;movzx eax, byte [_mouse_packet_y]
	;Testa o sinal para y.
	;test byte[_mouse_packet_data], MOUSE_Y_SIGN
	;jnz .y_neg

;Caso y seja positivo.	
;.y_pos:
	;sub [_mouse_y], eax
	;jns .quit

	;xor eax, eax
	;mov [_mouse_y], eax
	;jmp .quit

;Caso y seja negativo. 	
;.y_neg:
	;not al
	;inc al
	;add [_mouse_y], eax
	
;Done.
;.quit:
	;ret
	
	
;
; End.
;



