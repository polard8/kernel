;
; File: bl\bl.inc
;
; Descrição:
;     Arquivo principal do módulo Boot Loader do system4Nora.
;
; Atribuições:
;     O Boot Loader do System4Nora oferece rotinas de gerenciamento de 
; arquivos. As bibliotecas de 32bit usadas pelo Boot Loader pertencem 
; ao Boot manager, não há problema nisso.
;     O Boot Loader passa o comando para o kernel.
;
; Obs:
;    O Boot Manager já havia feito configurações de hardware talvez há 
; alguma configuração pra se fazer. Mas na verdade o Boot Loader vai ser 
; uma mas uma biblioteca mesmo oferecendo recursos de gerenciamento de 
; arquivos, utilizando recursos do Boot Manager.
;
;
; Versão 1.0, 2015. 
;


;----------------------------------
; BootLoader_Main:
;     Função principal do Boot Loader do System4Nora.
;
;
BootLoader_Main:

	pushad
	
	mov esi, msg_bootloader_testing
	call os_output	
	
	
	;
	; @ Fazer configurações:
	;
	
	 ;Endereço físico do Linear Frame Buffer, LFB.
	
	
;Configura IDT. 
    ;cli    
	;call setup_idt 	      ;Aponta tudo para 'unhandled_int'.
	;call setup_faults     ;Configura vetores de faults e exception.
	;call setup_vectors    ;Outros vetores.

	;Carrega GDT e IDT.
	;lgdt [GDT_register]	
	;lidt [IDT_register]
	
	;Segmentos.
	;mov ax, DATA_SEL 
	;mov ds, ax		 
	;mov es, ax 
	
	;mov ax, NULL_SEL
	;mov fs, ax		 
	;mov gs, ax 
	
	
	;Stack.
	;mov ss, ax
	;mov eax,  _bootloader_stack_start 
	;mov esp, eax 
		 

	;PIT.
	mov al, byte 0x36
	mov dx, word 0x43
	out dx, al	
	mov eax, dword 11930  ;timer frequency 100 HZ 
	mov dx, word 0x40
	out dx, al
	mov al, ah
	out dx, al

	
	;PIC.
	;cli
	;mov al, 00010001b    ;Begin PIC 1 initialization.
	;out 0x20, al
	;mov al, 00010001b    ;Begin PIC 2 initialization.
	;out 0xA0, al	
	;mov al, 0x20		 ;IRQ 0-7: interrupts 20h-27h.
	;out 0x21, al
	;mov al, 0x28		 ;IRQ 8-15: interrupts 28h-2Fh.
	;out 0xA1, al
	;mov al, 4
	;out 0x21, al
	;mov al, 2
	;out 0xA1, al
	;mov al, 1
	;out 0x21, al
	;out 0xA1, al

	;cli
	
	;Mascara todas as interrupções.
	;mov  al, 255					                  
	;out  0xa1, al                                   
	;out  0x21, al    
	  
	;unmask all interrupts	
	;mov  al, 0					                  
	;out  0xa1, al                                   
	;out  0x21, al    
	
	
	;
	; Teste de LFB:
	;     Testando se o Boot Loader está escrevendo no LFB.
	;
	
	;call _background

	;Debug.
	; jmp $
	
		
	
    ;
	; @todo: COnfigurar as páginas.
	;
	
	;
    ; Registrar o diretório em cr3.
	; Colocando no CR3 o endereço do diretório de páginas 
	; que o Kernel usará.
	; 
	; @todo: 
	;     Usar variável ou constante.
	;
	
	;xor eax, eax             	
	;mov eax, dword 0x9C000          
	;mov cr3, eax                  
	
  
    ;Flush TLB.
    jmp dummy_flush
dummy_flush:	
    
	;TLB.
	mov EAX, CR3  
    nop
	nop
	nop
	nop
	nop
	mov CR3, EAX  

	;
	; Configura CR0  #(PG).
	;
	
	;mov eax, cr0                    
	;or eax, dword 0x80000000        
	;mov cr0, eax   
	
	
	
;
; Done: Go to Kernel.
;	

    popad
	
	;
	; Go to Kernel.
	;
	
	;jmp System4Nora_Kernel
	call System4Nora_Kernel
	mov eax, 0
    RET	
		
	;OPÇÃO.	
	jmp $

	
;
; Boot Loader messages.
;	

msg_bootloader_testing db '[BL:] Starting',13,10,0

;
; End.
;

