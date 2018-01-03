;
; File: head\x86\hardwarelib.inc
;
; Descrição:
;     Rotinas de apoio à hardware.inc.
;     Nome opcional para padrão 8.3 (hwlib.s)
;
; Versão 1.0, 2015, 2016.
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
	
	
;------------------------
; _test_write:
;     Testa hd.
;     funciona.
;
global _test_write
_test_write:
    mov eax, dword 0x0e00
	mov ebx, dword 1020
    call hd0_write_sector
    ret

	
;--------------------------------	
; _os_read_sector:
;
; Read sector on PATA PIO 0 MODE.
;
global _os_read_sector
_os_read_sector:
    push eax
	push ebx
	
	call _reset_ide0
	
	mov eax, dword [_hd_buffer]    ;[900004h]    ;buffer.
	mov ebx, dword [_hd_lba]       ;[900008h]    ;lba.
	call hd0_read_sector
	
	pop ebx
	pop eax
	ret

	
;-------------------------------
; _os_write_sector:
;     Write sector on PATA PIO 0 MODE.
;
global _os_write_sector
_os_write_sector:
    push eax
	push ebx
 
	;mov byte [0xb8000], byte 'r'
    ;mov byte [0xb8001], byte 9
    
	call _reset_ide0
	
	;mov byte [0xb8002], byte 'w'
    ;mov byte [0xb8003], byte 9
	
	mov eax, dword [_hd_buffer]    ;[900004h]    ;buffer.
	mov ebx, dword [_hd_lba]       ;[900008h]    ;lba.
	call hd0_write_sector
	
	;mov byte [0xb8004], byte '$'
    ;mov byte [0xb8005], byte 9
	
	pop ebx
	pop eax
	ret

	

;-------------------------------------------
; hd0_read_sector:
;     Read sector on PATA PIO 0 MODE.
;
; eax - endereço
; ebx - lba
; ecx - null
; edx - null
;

HD_BUFFER:  DD 0    ;A.
HD_L:       DB 0    ;B.
HD_B:       DB 0    ;C.
HD_A:       DB 0    ;D.
HD_LBA:     DD 0

hd0_read_sector:

    PUSH EBP
	MOV  EBP, ESP
    
	PUSHFD
	PUSHA
	
	CLI

	;;SALVA 	
	MOV DWORD [HD_BUFFER], EAX
	
   ;;lba esta em ebx
	
	;;LOW
	MOV AL, bl
	MOV BYTE [HD_A], AL
    
	shr ebx, 8
	MOV AL, bl
	MOV BYTE [HD_B], AL
	
	;;HIGH
	shr ebx, 8
	MOV AL, bl
	MOV BYTE [HD_L], AL

	;;
	;; Seleciona 'drive number, lba mode, head number.
    ;;
	mov  dx, word 01f6h    ;Drive and head port.
	mov  al,  0e0h         ;lba   ;Drive 0, head 0.
	out  dx, al
    
	;QUANTIDADE DE SETORES. (1 setor)
	mov dx, 1f2h         ;Sector count port.
	mov al, 1            ;Read one sector.
	out dx, al

	;LBA- teste 2304 900h
	
	;0-7
	mov dx, 1f3h
	MOV AL, BYTE [HD_A]    ;; - LOW.
	out dx, al
	
	;8-15
	mov dx, 1f4h
	MOV AL, BYTE [HD_B] 
	out dx, al

	;16-31
	mov dx, 1f5h
	MOV AL, BYTE [HD_L] 
	out dx, al	
	
	;comandos
	xor eax, eax
	mov  dx, 1f7h    ;Command port.
	mov  al, 20h     ;Read with retry. 30h write.
	out  dx, al
read_still_going:
	in al, dx
	
	test al, 8             ;This means the sector buffer requires servicing.			
	jz read_still_going    ;Don't continue until the sector buffer is ready.
	
	mov  cx,  256    ;; (512/2) ;One sector /2.
	
	PUSH EAX
	xor eax, eax
	MOV eax, DWORD [HD_BUFFER]
	mov edi, eax                ;dword  0x0900000 ;buffer ;offset buffer.
	POP EAX
	
	mov dx, 1f0h         ;Data port - data comes in and out of here.
	rep insw
	
    ;STI           ;;@todo bugbug isso pode acionar a irq0. e trocar de tarefa???
	
    ;call hd_wait 	
	call Small_Delay
	call Small_Delay
	call Small_Delay
	call Small_Delay
	call Small_Delay
	
	POPA
	POPFD
	
	POP EBP	 
	RET


;--------------------------------------------
; hd0_write_sector:
;     Write sector on PATA PIO 0 MODE.
;
; eax - endereço
; ebx - lba
; ecx - null
; edx - null
;
hd0_write_sector:

    PUSH EBP
	MOV  EBP, ESP
    
	PUSHFD
	PUSHA
	
	CLI

	;;SALVA 	
	MOV DWORD [HD_BUFFER] , EAX
  	
	;;LOW
	MOV AL, bl
	MOV BYTE [HD_A] , AL
    
	shr ebx, 8
	MOV AL, bl
	MOV BYTE [HD_B] , AL
	
	;;HIGH
	shr ebx, 8
	MOV AL, bl
	MOV BYTE [HD_L] , AL
	
	;; Seleciona 'drive number, lba mode, head number
    mov  dx, word 01f6h    ;Drive and head port.
	mov  al, 0e0h          ;lba   ;Drive 0, head 0.
	out  dx, al
    
	;QUANTIDADE DE SETORES. (1 setor)
	mov dx, 1f2h         ;Sector count port.
	mov al, 1            ;Read one sector.
	out dx, al

	;LBA
	
	;0-7
	mov dx, 1f3h
	MOV AL, BYTE [HD_A]    ;LOW.
	out dx, al
	
	;8-15
	mov dx, 1f4h
	MOV AL, BYTE [HD_B] 
	out dx, al

	;16-31
	mov dx, 1f5h
	MOV AL, BYTE [HD_L] 
	out dx, al
		
	;comandos
	xor eax, eax
	mov dx, 01f7h    ;Command port.
	mov al, 30h      ;with retry. 30h write.
	out dx, al
  	
write_still_going:	
	in  al, dx
	
	test al, byte 8          ;This means the sector buffer requires servicing.
	jz write_still_going     ;Don't continue until the sector buffer is ready.
	
	mov ecx, dword 256    ;(512/2) ;One sector /2.	
	mov dx, 01f0h         ;Data port - data comes in and out of here.
	
	MOV esi, DWORD [HD_BUFFER]
	rep outsw
    	
    ;STI
	
    ;call hd_wait    ;Test. 		
	call Small_Delay
	call Small_Delay
	call Small_Delay
	call Small_Delay
	call Small_Delay	
		
	POPA
	POPFD
	
	POP EBP
	RET
	
;-------------------------------
; hd_wait:
;     Hard Disk Wait Function.
; 
hd_wait: 
    cli 
    mov dx, 1F7h 
waitloop:  
    in al, dx 
    
	cmp al, 50h 
    je waitok     
	
	cmp al, 0 
    je waitok
	
	jmp waitloop 
waitok: 
    ;sti 
    ret 


;--------------------------------
; _reset_ide0:
;
global _reset_ide0
_reset_ide0:
    mov dl, byte 0
	call IDE_RESET_DISK
	ret

;--------------------------------	
; init_ide0_master:	
;     Reseta o ide0 master.
;
;
init_ide0_master:
    mov dl, byte 0
	call IDE_RESET_DISK
	ret

;--------------------------------------------
; IDE_RESET_DISK:
;
;   dl = Drive (0=master,1=slave)
;
;   Note: 
;       Some disks will respond to the reset command 
;       if the other is given it.
;
IDE_RESET_DISK:

	and dl, 01           ;isolate bit 0.
	mov al, dl           ;al = dl.
	shl al, 4            ;move drive selector into bit 4.
	or al, 0A0h          ;make bits 7 and 5 a 1.
	mov dx, 01F6h        ;dx = drive/head regsiter port address.
	out dx, al           ;write to drive/head register.
	mov al, 10h          ;Command 1xh: Recalibrate.
	inc dx                         ;dx is now 01F7h, port address of command register.
	mov byte [lastcommand], 10h    ;Tell our ISR what we are doing.
	out dx, al                     ;Recalibrate.

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


;------------------------
; Small_Delay:                                        
;
Small_Delay:
    push ecx
    mov  ecx, 0xfffff
BusyDelay3a:                                  
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    loop BusyDelay3a
    pop ecx
    ret
	
;
; CMOS ------------------------------
;


;
; Save info from CMOS.
global _hour
_hour:    db 0
global _minute
_minute:  db 0
global _second
_second:  db 0



;--------------------------------------------
; CMOS_GET_DATE:
;     Pega Hora, Minuto e Segundo.
;
;
global _CMOS_GET_DATE	
_CMOS_GET_DATE:
    
	PUSHAD
    
	; get the "second" byte.
	MOV  al, 0x00           
    OUT  0x70, AL
    IN   AL, 0x71 
	CALL  BCD2bin
    MOV  BYTE [_second], AL
		
    ; get the "minute" byte.
	MOV  AL, 0x02           
    OUT  0x70, AL
    IN   AL, 0x71
    CALL  BCD2bin
    MOV  BYTE [_minute], AL	
		
	; get the "hour" byte.	
    MOV  AL, 0x04           
    OUT  0x70, AL
    IN  AL, 0x71
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


	
;
; End.
;	
	