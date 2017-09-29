;
; File: softwarelib.inc
;
; Descrição:
;     Biblioteca para funções de interrupções de software.
;     Oferece alguns serviços básicos em assembly. 
;     Nome opcional para padrão 8.3 (swlib.s)
;
; Histórico:
; Versão: 1.0, 2015 - Created.
; Versão: 1.0, 2016 - Revisão.
;


extern _vsync
	
	
;-------------------------------------
; _my_buffer_load_bitmap_16x16:
;     Copia um bitmap .BMP da memória para o backbuffer.
; @todo: Essa rotina pode ser feita em C, facilmente e 
; dar um suporte mais completo para o formato bmp.
; porém essa rotina de 16x16 800x600x24 pode continuar aqui.
; pelo meno por enquanto.
;
; Argumentos:
;     eax = Endreço do arquivo .BMP. 
;     ebx = x. (x no backbuffer).
;     ecx = y. (y no backbuffer).
;     edx = null.
;
global _my_buffer_load_bitmap_16x16     
_my_buffer_load_bitmap_16x16:
    
	;pushad
	
	;Salva argumentos.
	mov dword [.endereco], eax
	mov dword [.x]       , ebx
	mov dword [.y]       , ecx
	xor edx, edx

    ;
    ;Prepara a origem, (ESI).   
	;
	
	;Preparando o inicio da area de dados.
	;Adiciona o offset da área de dados do arquivo .BMP à base.
    add eax, dword 036h  	
	mov esi, eax         

	;
	;Prepara o destino, (EDI).
	;
	
	;calcula x.
	mov eax, ebx        ;pega x.
	mov ebx, dword 3    ;3 bytes por pixel.
	mul ebx
	mov ebx, eax        ;eax contém o deslocamento de x.
	
	;calcula y e adiciona x.
	mov eax, ecx            ;pega y.
	mov edx, dword 640*3    ;(pixel por linha * bytes por pixel) = bytes por linha.
	mul edx                 ;(número de linhas * bytes por linha).   
    add eax, ebx            ;adiciona x.	
    
	
    ;'eax' - contém o deslocamento em relação ao início do buffer.
	
	 
    mov edx, dword 0xC0800000  ;backbuffer.
	add eax, edx               ;adiciona o buffer.
    mov edi, eax               ;posição (esquerda/cima) da imagem na tela.
	
	;sabendo a altura da imagem ...
	mov eax, edi
	add eax, dword 640*3*16    ;(bytes por linha * altura).
	
	;eax contém a posição (baixo/esquerda) da imagem, '|____'.
	mov edi, eax
	
	;
	;A sincronização vertical.
	;
	;call _vsync
	
	;quantidade de linhas
    mov ecx, dword 16
;Loop:	
.pinta_bmp:	
	;pega uma linha
    movq  mm0, [esi]        ;2 primeiros pixels.      
	movq  mm1, [esi+8]    
	movq  mm2, [esi+16]
	movq  mm3, [esi+24]
	movq  mm4, [esi+32]
	movq  mm5, [esi+40]
	;movq  mm6, [esi+48]
	;movq  mm7, [esi+56]

    movq  [edi]   , mm0
	movq  [edi+8] , mm1
	movq  [edi+16], mm2
	movq  [edi+24], mm3
	movq  [edi+32], mm4
	movq  [edi+40], mm5
	;movq  [edi+48], mm6
	;movq  [edi+56], mm7
    
	;próxima linha da bmp.
	mov eax, esi 
	add eax, dword 48    ;64 ; adiciona 64 bytes.
	mov esi, eax
	
	;linha anterior do buffer
	mov eax, edi 
	sub eax, dword 640*3    ;Adiciona a quantidade de bytes por linha.
	mov edi, eax
	
	loop .pinta_bmp
	
	;pushad
	emms 
	ret	
.endereco: dd 0
.x: dd 0
.y: dd 0


;--------------------------------
; _um_buffer_putpixel:
;     Coloca um pixel no backbuffer.
;     @todo: Deletar essa função.
;
; a =  cor
; b =  x
; c =  y
; d = ?
;
global _um_buffer_putpixel
_um_buffer_putpixel:
    jmp _gui_buffer_putpixel
    jmp $
	
	

;===================================================================
; _gui_buffer_putpixel:
;     Coloca um pixel no backbuffer.
;     O módulo /hal deve chamar essa rotina e não a /gui. 
;
;
; a =  cor
; b =  x
; c =  y
; d = ?
;
global _gui_buffer_putpixel
_gui_buffer_putpixel:

	push  es
    push  ecx   
   
    ;Ajuste provisório.
	mov dword [.cor], eax    ;salva cor.
	mov dword [.x],   ebx    ;salva x.
	mov dword [.y],   ecx    ;salva y.		
    mov eax, dword [.x]
	mov ebx, dword [.y]      ;coloca y em ebx.	 	
	mov ecx, dword [.cor]    ;coloca a cor em ecx.
	
	;ecx (cor) AABBGGRR  

	mov byte [.a], cl	 ;a.
	shr ecx, 8
	mov byte [.r], cl	 ;r.
	shr ecx, 8
	mov byte [.g], cl    ;g.
	shr ecx, 8
	mov byte [.b], cl    ;b.
    
	;segmento ES ... poderia ser 0x10
	push eax
	mov ax, 0x10
	mov es, ax
    pop eax   
	
	;;[BytesPerScanLineMOS] ; ebx = y * y multiplier 800*4 ;1024*4 ;640*4      
	
	imul ebx, 800*3    ;640*3        
    
	;eax*3
	mov ecx, dword 3
	mul ecx
	add eax, ebx    ;Adiciona ebx.
	
	mov  edi, eax ;dword [ebx+eax*3]  ;[ebx+eax*4] ; edi = x*4+(y*y multiplier)
    
	;mov eax, ecx       ;[MenColor] ; eax = color
    
	;(base) buffer 1 
	mov ecx, dword 0xC0800000 ;;[ModeInfo_PhysBasePtr] 0x01000000 ; buffer [5000h]  
    add edi, ecx     ;(deslocamento)
   	
	;a
	;mov al, byte [.a]
	;stosb 	
	;envia r, g e b.
	mov al, byte [.r]
	stosb 
	mov al, byte [.g]
	stosb 
	mov al, byte [.b]
	stosb 
    
	pop ecx
    pop es
    ret		
.cor: dd 0
.x: dd 0
.y: dd 0
.r db 0	
.g db 0
.b db 0	
.a db 0	



;---------------------------
; _background:
;     Pinta um pano de fundo no backbuffer.
;     Obs: Essa rotina também existe em C. /gui.
;
; Input: 
;     EAX = COLOR.
;
global _background
_background:		
.fade_screen: 

    ;Estamos pintando no backbuffer. Não precisa sincronismo vertical.
	;call _vsync 
	
	pushad  
	;COR
	;mov al, byte 0
	;mov byte [.a], al	 ;a.
	mov al, byte 0x00     
	mov byte [.r], al	 ;r.
	mov al, byte 0x00
	mov byte [.g], al    ;g.
	mov al, byte 0xFE
	mov byte [.b], al    ;b.
	
	;LFB - Endereço lógico do LFB, configurado pelo bootloader.
	;mov   edx, DWORD 0xC0400000 
    ;mov   edi, edx
	
	;BUFFER 1
	mov edi, dword 0xC0800000
	mov edi, edx
	
	;contador de linhas
	mov   ebx, dword 600    ;480          ;Número de linhas.	    
.bg_newline:     	
	;contador de pixel por linha.
    mov   ecx, dword 800*3    ;640*3    ;3 bytes por pixel. (800 pixel por linha).	
.bg_newpixel:      
	;mov al, byte [.a]
	;stosb 	
	mov al, byte [.r]
	stosb 	
	mov al, byte [.g]
	stosb 	
	mov al, byte [.b]
	stosb 
    
	loop  .bg_newpixel    ;Próximo pixel. 

    dec  ebx         
	cmp ebx, dword 0
	jne .bg_newline    ;Próxima linha.
.exit_bg:
    popad	
    RET
.a db 0		
.r db 0	
.g db 0
.b db 0	




;------------------------------------------------
;  _asm_refresh_screen: 
;      Passa o conteúdo do buffer1 para a tela.
;      A tela toda.
;
; @todo: Essa rotina poderia se chamar _softwarelibRefreshScreen.
;
global _asm_refresh_screen
_asm_refresh_screen:		

    ;Sincroniza o retraço vertical.  
	call _vsync  
	
	push esi
	push edi
	push ecx
	push edx
	
	;
    ; Origem  - BackBuffer.
    ; Destino - LFB.
	mov esi, dword 0xC0800000    ;Endereço lógico do backbuffer.
	mov edx, dword 0xC0400000    ;Endereço logico do LFB. Configurado no bootloader.
    mov edi, edx
	
	;
	; Uma tela de 800x600:
	; 800 pixel de 3 bytes por linha é igual a 2400 bytes por linha.   
	; 2400 byte por linhas é igual a 600 dwords por linha.
    mov ecx, dword (800*600)    ;(640*480)    ;(600*600); 800x600.   
    rep movsd
	
	pop edx
	pop ecx
	pop edi
    pop esi   	
    RET	

	
;-------------------
; write_char:
;     Escreve um caractere no modo texto.
;
write_char:
    ;;Nothing for now.
	ret	

;
; End.
;	
	