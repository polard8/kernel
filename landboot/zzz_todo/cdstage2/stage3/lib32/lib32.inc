;
; File: lib32\lib32.inc 
;
; Descrição:
;     Rotinas para o Boot Manager.
;     O Boot Manager oferece recursos para o System4Nora através dessa
; biblioteca.
;
; In this file:
;     + Rotina de serviços oferecidos pelo Boot Mnager.
;     + Recursos gráficos.
;     + Outras rotinas gerais.
;
; Histórico:
;     Version 1.0, 2015 - Created by Fred Nora.
;     Version 1.0, 2016 - Revision.
;     Version 1.0, 2017 - Created lib32PrintChar and lib32PrintString. 
;     ... 
;

LIB32_BACKBUFFER EQU (0x1000000 - 0x800000)

;
; Variáveis internas.
;

TotalMemoryMB: dd 0
;...


;------------------------------------------
; _bmServices:
;     Serviços oferecidos pelo Boot Manager.
;
;
global _bmServices
_bmServices:
    ;
	; @todo: Essa rotina conterá os serviços oferecidos pelo Boot Manager.
	;
	ret
	

;
; Obs: As chamadas abaixo visam organização e não desempenho.
;

;==============================================================
; lib32PrintChar:
;     Imprime um caractere na tela em modo gráfico.
; Obs: O caractere precisa ser desenhado, píxel por pixel.
;
; @todo: Argumentos ... variáveis ...
;
; a =  cor (rrggbbaa)
; b =  x ignorado 
; c =  y ignorado
; d =  Char.
;	
; obs: x e y serão ignorados
;      e o char será pintado nas cordenadas do 'cursor'.
;	
lib32PrintChar:
	push eax
	push ebx
	push ecx 
	push edx

	mov dword [.color], eax    ;;salva color
    mov byte [.char], dl       ;;salva char.
    ;;...	
	
	;pega a coordenada x.
	mov eax, dword [g_cursor_x]
	
	
	;Se estivermos no fim da linha.
	cmp eax, dword 80
	jge .nextLine
	
	;;@todo:
	;; Última linha ??
	;mov eax, dword [g_cursor_y]
	;cmp eax, dword 25
	;jge .??
	
	;; CARRIAGE RETURN.
	cmp dl, byte 13    
	je .CR
	
	;; LINE FEED.
	cmp dl, byte 10    
	je .LF
		
	;;...
	
	;; não muda de linha
.thisLine:	
    
	;; x
    ;;calcula deslocamento na linha
	mov eax, dword [g_cursor_x]
	mov ebx, 8               ;; tamanho da largura do char dada em bits
	mul ebx  ;; multiplica, o resultado vai para eax.
	mov dword [.x], eax      ;; deslocamento em pixel na horizontal.


    mov eax, dword [g_cursor_y]
    mov ebx, 8 
    mul ebx 
    mov dword [.y], eax      ;; deslocamento em pixel na vertical.
	
	;desenha o pixel dadas as coordenadas.
.PutPixel:
    ; a =  cor (rrggbbaa)
    ; b =  x
    ; c =  y
    ; d =  Char.

	mov eax, dword [.color]
	mov ebx, dword [.x]
	mov ecx, dword [.y]
	xor edx, edx
	mov dl, byte [.char]
	
	call _my_buffer_char_blt
	
	;;incrementa o cursor depois de imprimir o char.
	push eax 
    mov eax, dword [g_cursor_x]
    inc eax 
	mov dword [g_cursor_x], eax 
	pop eax
	jmp .done

;Quando o caractere ultrapassar o tamanho da linha
;devemos desenhar o caractere no início da p´roxima linha.
.nextLine:
    ;Volta ao começo da linha.
    mov dword [g_cursor_x], 0

	;Próxima linha.
	mov eax, dword [g_cursor_y]
	inc eax 
    mov dword [g_cursor_y], eax
	
    ;Agora que estamos na linha certa, devemos calcular
	;legando em conta o tamanho do caractere.
	jmp .thisLine
	
.CR:	
    ;Volta ao começo da linha.
    mov dword [g_cursor_x], 0
	jmp .done 
	
  ;;muda de linha..	
.LF:
	
	;Próxima linha.
	mov eax, dword [g_cursor_y]
	inc eax 
    mov dword [g_cursor_y], eax 
    jmp .done	
	
.done:	
	pop edx 
	pop ecx 
	pop ebx 
	pop eax 
	ret

.color: dd 0	
.x: dd 0
.y: dd 0
.char: db 0
;;--



;===========================================================
; lib32PrintString:
;     Imprime uma string na tela em modo gráfico.
; Um ponteiro para string deve estar em alguma registrador.
; ESI = string
; ; a =  cor (rrggbbaa)
;
;	
lib32PrintString:

    pushad 
	
    cmp eax, 0
	jne .notBlack
    
.colorBlack:
    ;muda a cor, para não mistura com o fundo preto.
	mov eax, 0x00FF0000  ;; outra cor, não preto.	
	
.notBlack:
	mov dword [.color], eax    ;;salva color
	
	push eax
	push ebx
	push ecx 
	push edx 
.nextChar:
    lodsb
    or al, al
    jz .done

    ; a =  cor (rrggbbaa)
    ; b =  x
    ; c =  y
    ; d =  Char.
     
	mov dl, al                 ;;char 
	mov eax, dword [.color]    ;;color 
	call lib32PrintChar
	
	jmp .nextChar
.done:
	pop edx 
	pop ecx 
	pop ebx 
	pop eax 
	
	popad 
	ret
.color: dd 0
.char: db 0


	
	
;
; lib32Putpixel:
;     Coloca um pixel no Back Buffer.
;
lib32PutPixel:
    call _gui_buffer_putpixel
    ret	
	
;
; lib32DirectPutPixel:
;     Coloca um pixel direto no LFB.
;	
lib32DirectPutPixel:
    call _gui_direct_putpixel
    ret	


lib32DrawHorizontalLine:
    call draw_horizontal_line
    ret


lib32DrawRect:
    call draw_rect
	ret
	
lib32CreateWindow:
    call CreateWindow
    ret

lib32FadeSreen:
    call _fade_screen
	ret
	
lib32Background:
    call _background
    ret
	
lib32RefreshScreen:
    call _asm_refresh_screen
	ret
	
lib32GetRAMSize:
    call get_ram_size
	ret
	

lib32GetBootDrive:
    call Get_Boot_Drive
    ret

lib32SetLFBAddress:
    call Set_LFB_Address
    ret	

	
lib32GetLFBAddress:
    call Get_LFB_Address
	ret
	
lib32SetupGDT: 
    call setup_gdt
	ret

lib32SetupIDT:
    call setup_idt
    ret	
	

	
;; Continua...	
	
	
;####################################################
; _gui_buffer_putpixel:
;     Coloca um pixel no Back Buffer.
;
; a =  cor (rrggbbaa)
; b =  x
; c =  y
; d = ?
;
global _gui_buffer_putpixel
_gui_buffer_putpixel:

    ;inicio da função.
	push es
    push ecx
   
   ;ajuste provisorio ...
	mov dword [.cor], eax    ;salva cor.
	mov dword [.x],   ebx    ;salva x.
	mov dword [.y],   ecx    ;salva y.
    mov eax, dword [.x]
	mov ebx, dword [.y]      ;coloca y em ebx.
	mov ecx, dword [.cor]    ;coloca a cor em ecx.
	
	;ecx (cor) (rrggbbaa)

	mov byte [.a], cl    ;a.
	shr ecx, 8
	mov byte [.r], cl    ;b.
	shr ecx, 8
	mov byte [.g], cl    ;g.
	shr ecx, 8
	mov byte [.b], cl    ;r.
    
	;segmento ES ... poderia ser 0x10
	push eax
	mov ax, 0x10
	mov es, ax
    pop eax   
	
	;;[BytesPerScanLineMOS] ; ebx = y * y multiplier 800*4 ;1024*4 ;640*4
	
	imul ebx, 800*3 ;640*3        
    
	;eax*3
	mov ecx, dword 3
	mul ecx
	add eax, ebx    ;Adiciona ebx.
	
	mov  edi, eax ;dword [ebx+eax*3]  ;[ebx+eax*4] ; edi = x*4+(y*y multiplier)
    
	;mov eax, ecx       ;[MenColor] ; eax = color
    
	 
	;(base) buffer 1 
    mov ecx, dword LIB32_BACKBUFFER ;0x01000000  ;endereço fisico do backbuffer ;[ModeInfo_PhysBasePtr]
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
; v. local.		
.cor: dd 0
.x: dd 0
.y: dd 0
.r db 0
.g db 0
.b db 0
.a db 0


;#################################################
; _gui_direct_putpixel:
;     Coloca um pixel direto no LFB.
;
; a =  cor (rrggbbaa)
; b =  x
; c =  y
; d = ?
;
global _gui_direct_putpixel
_gui_direct_putpixel:

    ;inicio da função.
	push  es
    push  ecx
     
    ;ajuste provisorio ...
	mov dword [.cor], eax    ;salva cor.
	mov dword [.x],   ebx    ;salva x.
	mov dword [.y],   ecx    ;salva y.		
    mov eax, dword [.x]
	mov ebx, dword [.y]      ;coloca y em ebx.	 	
	mov ecx, dword [.cor]    ;coloca a cor em ecx.
	
	;ecx (cor) (rrggbbaa)

	mov byte [.a], cl    ;a.
	shr ecx, 8
	mov byte [.r], cl    ;b.
	shr ecx, 8
	mov byte [.g], cl    ;g.
	shr ecx, 8
	mov byte [.b], cl    ;r.
    
	;segmento ES ... poderia ser 0x10
	push eax
	mov ax, 0x10
	mov es, ax
    pop eax   
	
	;;[BytesPerScanLineMOS] ; ebx = y * y multiplier 800*4 ;1024*4 ;640*4      
	
	imul ebx, 800*3 ;640*3
    
	;eax*3
	mov ecx, dword 3
	mul ecx
	add eax, ebx    ;Adiciona ebx.
	
	mov  edi, eax ;dword [ebx+eax*3]  ;[ebx+eax*4] ; edi = x*4+(y*y multiplier)
    
	;mov eax, ecx       ;[MenColor] ; eax = color
    
	;(base) buffer 1   
    mov ecx, dword [ModeInfo_PhysBasePtr]
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
; v. local
.cor: dd 0
.x: dd 0
.y: dd 0
.r db 0
.g db 0
.b db 0
.a db 0


	
;--------------------------------------
; draw_horizontal_line:
;     Pinta uma linha horizontal. no back buffer.
;
; eax = x1
; ebx = x2
; ecx = y
; edx = cor (rrggbbaa)
;
draw_horizontal_line:

    pushad	
    mov dword [.x1],    eax    ;x1
    mov dword [.x2],    ebx    ;x2
    mov dword [.y],     ecx    ;y
    mov dword [.color], edx    ;color
.nextPixel:
	mov eax, dword [.color]  ;cor
    mov ebx, dword [.x1]     ;x
    mov ecx, dword [.y]	     ;y
	;call _gui_direct_putpixel
	call _gui_buffer_putpixel

	mov ebx, dword [.x1]
	
	inc ebx  ;incrementa x

	mov dword [.x1], ebx
	
	cmp ebx, dword [.x2]
	jne .nextPixel
	
	popad
	ret
.x1: dd 0
.x2: dd 0
.y: dd 0
.color: dd 0


;-------------------------
; draw_rect:
;     Desenha um retângulo.
; a = x1
; b = x2
; c = y1
; d = y2
; edi = color (rrggbbaa)
;
draw_rect:

    pushad
    mov dword [.x1],    eax    ;x1
    mov dword [.x2],    ebx    ;x2
    mov dword [.y1],    ecx    ;y1
    mov dword [.y2],    edx    ;y2
    mov dword [.color], edi    ;color
.nextLine:
	mov eax, dword [.x1]    ;x1
	mov ebx, dword [.x2]    ;x2
	mov ecx, dword [.y1]    ;y
	mov edx, dword [.color] 
	call draw_horizontal_line
	
	
	mov edx, dword [.y1]
	inc edx
	mov dword [.y1], edx
	
	cmp edx, dword [.y2]
	jne .nextLine
	
	popad
    ret
.x1: dd 0 ;
.x2: dd 0 ;
.y1: dd 0 ;
.y2: dd 0 ;
.color: dd 0 ;



;----------------------------------
; CreateWindow:
;     Desenha uma janela.
; a = x
; b = y
; c = width
; d = height
; edi = color ;(cor) rrggbbaa 
;
CreateWindow:
    
	pushad
	mov dword [.x],    eax    ;x
    mov dword [.y],    ebx    ;y
    mov dword [.width],   ecx    ;largura
    mov dword [.height],  edx    ;altura
    mov dword [.color],   edi    ;color

	;bg
	mov eax, dword [.x] ;x1
	mov ebx, dword [.x] ;x2
	add ebx, dword [.width]
	mov ecx, dword [.y] ;y1
	mov edx, dword [.y] ;y2
 	add edx, dword [.height]
    mov edi, dword [.color]    
	call draw_rect	
	
    ;barra de titulos
	mov eax, dword [.x] ;x1
	mov ebx, dword [.x] ;x2
	add ebx, dword [.width]
	mov ecx, dword [.y] ;y1
	mov edx, dword [.y] ;y2
 	add edx, dword 16 ;[.height]
    mov edi, dword 0x0000CC00     ;Blue (rrggbbaa) (color)
	call draw_rect
	
	popad
    ret
.x: dd 0
.y: dd 0
.width: dd 0
.height: dd 0
.color: dd 0


;------------------------------------
; _fade_screen:
;     Fade background screen.
;     Pinta uma parte do background em degradê.
;     Pinta diretamente no LFB.
;     @todo: #bugbug Precisamos de sincronização vertical.
;
;
global _fade_screen
_fade_screen:
    
	;
	; @todo: Sincronização vertical.
	;
	
	;Get LFB address.
	mov  edx, dword [ModeInfo_PhysBasePtr]
    
	;Destino.
	mov edi, edx
    
	xor eax, eax
    mov al, 0xc5
    
	xor ebx, ebx
    mov bl, 195 
DoLoop:    
    mov cx, 640*2 
    dec eax    
    rep stosd     ;Envia.
    dec ebx
    jnz DoLoop    ;Loop.
	
	;
	; No return !
	;
	
	jmp $


;------------------------------
; _background:
;    Pinta um pano de fundo direto na memória de vídeo, LFB.
;
; @todo: Precisamos de sincronização vertical.
;
; EAX = COR.
;
global _background
_background:		
.fade_screen:

    ;call _vsync ; Sincroniza o retraço vertical.
	
	pushad
	
	;COR. 
	mov al, byte 0x00
	mov byte [.a], al    ;a
	mov al, byte 0x00     
	mov byte [.r], al	 ;r
	mov al, byte 0x0e
	mov byte [.g], al    ;g
	mov al, byte 0xfe
	mov byte [.b], al    ;b

	;LFB
	;mov edx, DWORD [ModeInfo_PhysBasePtr]
	mov   edx, DWORD  [ModeInfo_PhysBasePtr] 
    mov   edi, edx
		
	;contador de linhas
	mov   ebx, dword 600   ; numero de linhas	    
.bg_newline:     	
	;contador de pixel por linha.
    mov   ecx, dword 800*3 ; 3 bytes por pixel. (800 pixel por linha)	
.bg_newpixel:     
	mov al, byte [.a]
	stosb 
	mov al, byte [.r]
	stosb 	
	mov al, byte [.g]
	stosb 	
	mov al, byte [.b]
	stosb 
    
	loop   .bg_newpixel ; proximo pixel. 

    dec   ebx         	
	cmp ebx, dword 0
	jne .bg_newline ; proxima linha
.exit_bg:
    popad	
    RET
.a: db 0	
.r: db 0	
.g: db 0
.b: db 0	



;--------------------------------------------------
; _background_teste:
;    Pinta algumas linhas direto na memória de video.
;
; EAX = COR
;
global _background_teste
_background_teste:		
.fade_screen: 
    
	;
	; Direto
	;
	
	;call _vsync 
	
	pushad
	  
	;COR 
	mov al, byte 0x00
	mov byte [.a], al    ;a
	mov al, byte 0xfe     
	mov byte [.r], al	 ;r
	mov al, byte 0x00
	mov byte [.g], al    ;g
	mov al, byte 0x00
	mov byte [.b], al    ;b
	
	;LFB
	mov edx, DWORD [ModeInfo_PhysBasePtr]
	;mov edx, DWORD [VIDEO.lfb]  
    mov edi, edx
	
	;contador de linhas
	mov   ebx, dword 600   ; numero de linhas	    
.bg_newline:     	
	;contador de pixel por linha.
    mov   ecx, dword 800*3 ; 3 bytes por pixel.  	
.bg_newpixel:     
    
	;mov al, byte [.a]
	;stosb 
	mov al, byte [.r]
	stosb 
	mov al, byte [.g]
	stosb 
	mov al, byte [.b]
	stosb 
    
	loop   .bg_newpixel ; proximo pixel. 

    dec ebx
	cmp ebx, dword 0
	jne .bg_newline ; proxima linha	
.exit_bg:
    popad
    RET
.a: db 0
.r: db 0
.g: db 0
.b: db 0


;---------------------------------------------------------
; _my_direct_load_bitmap_16x16:
;     Copia um bitmap .BMP da memória direto no LFB.
;
; Argumentos:
;     eax = Endreço do arquivo .BMP. 
;     ebx = x. (x no LFB).
;     ecx = y. (y no LFB).
;     edx = null.
;
global _my_direct_load_bitmap_16x16     
_my_direct_load_bitmap_16x16:
	;; Suspensa para economizar espaço.
	ret


;-------------------------------------------------------
;  _asm_refresh_screen: 
;      Passa o conteúdo do buffer1 para a tela. A tela toda.
;
;
global _asm_refresh_screen
_asm_refresh_screen:		

    ;Sincroniza o retraço vertical.
    
	;call _vsync  
	
	push esi
	push edi
	push ecx
	push edx
	
	;
    ; Origem  - Buffer.
    ; Destino - LFB.
	mov esi, dword LIB32_BACKBUFFER ;0x01000000
	mov edx, dword [ModeInfo_PhysBasePtr]
    mov edi, edx
	
	;
	; Uma tela de 800x600:
	; 800 pixel de 3 bytes por linha é igual a 2400 bytes por linha.   
	; 2400 byte por linhas é igual a 600 dwords por linha.
	;
    mov ecx, dword (800*600)    ;(600*600); 800x600.   
    rep movsd
	
	pop edx
	pop ecx
	pop edi
    pop esi   	
    RET	

	
;=======================================================  ;
; Get RAM size.                                           ;
;=======================================================  ;
get_ram_size:						  ;
    mov	eax, dword [TotalMemoryMB]    ;
    ret	

	
;=======================================================  ;
; Get Boot Drive.                                         ;
;=======================================================  ;
Get_Boot_Drive: 					        ;
	mov	al, byte [META$FILE.DISK_NUMBER]    ;
	ret		

	
;-------------------------------
; Set_LFB_Address:	
;     Set LFB Address.
;
Set_LFB_Address: 
	mov	dword [META$FILE.LFB], eax
	ret


;-------------------------------
; Get_LFB_Address:
;     Get LFB Address.
;
Get_LFB_Address:
	mov	eax, dword [META$FILE.LFB]
	ret


;-------------------
; setup_gdt:
;     Carrega gdtr.
;++
setup_gdt:
	lgdt [lgdt_opcode]
	ret
;--


;---------------------
; setup_idt:
;     Configura a IDT.
;
setup_idt:

	;lea edx, ignore_int
    mov edx, ignore_int
	mov eax, dword 0x00080000
	mov ax, dx		     ;/* selector = 0x0008 = cs */
	mov dx, word 0x8E00	 ;/* interrupt gate - dpl=0, present */
	;lea edi, idt
	mov edi, idt
	
	mov ecx, dword 256
rp_sidt:
	mov dword [edi]  , eax	
	mov dword [edi+4], edx
	add  edi, dword 8
	dec ecx
	jne rp_sidt
	
	lidt [lidt_opcode]
	ret
	
	
;-------------------------------
; set_base:	
;# in: 
;#
;#%eax - logic addr; 
;#%ebx = base addr ; 
;#%ecx - table addr; 
;#%edi - descriptors offset.
;#
set_base:
	add eax, ebx
	add edi, ecx
	mov [edi+2], word ax
	
	ror eax, 16
	
	mov [edi + 4], al
	mov [edi +7],  ah
	ror eax, 16
	ret

	
	
;------------------------------------
; init_prompt:
;	
init_prompt:
    push eax	
    xor eax, eax
    call set_scr_loc
    call set_cursor_x
    call set_cursor_y
	pop eax
	ret

	
;
; set_scr_loc:
;     Configura o deslocamento dentro da tela.
;
; in: eax 
;
set_scr_loc:
    mov dword [scr_loc], eax
	ret
	
;
; get_scr_loc:
;	
get_scr_loc:
    mov eax, dword [scr_loc]
	ret	
	
set_cursor_x:	
    mov dword [g_cursor_x], eax
	ret

set_cursor_y:	
    mov dword [g_cursor_y], eax
	ret
	
get_cursor_x:	
    mov eax, dword [g_cursor_x]
	ret

get_cursor_y:	
    mov eax, dword [g_cursor_y]
	ret


;-----------------------------------
; write_char:
;     Write a char in text mode.
;
write_char:
	push eax
	push ebx
	push edx
	
	mov edx, dword 0x000B8000
	mov ebx, dword [scr_loc]
	
	shl ebx, 1
	
	;#manda um char pra memória de vídeo.
	mov [edx + ebx], byte al
	
	shr ebx, 1
	
	inc ebx
	
	cmp ebx, dword 2000
	jb ._1f
	mov ebx, dword 0
._1f:	
    mov dword [scr_loc], ebx
	pop edx
	pop ebx
	pop eax
	RET


;--------------------------------------
; DisplayMessage32:
;     Mostra uma string. de ESI. Em text mode.
;
DisplayMessage32:
.proxCar:
    lodsb
    or al, al
    jz .volta

    call write_char
	jmp .proxCar
.volta:
    ret


;-----------------------------------
; clear_screen:
;     Clear screen in text mode.
;	
clear_screen:   
    push eax
    push ecx
    
	;Reinicia o offset.
	xor eax, eax
	call set_scr_loc
	
    mov ecx, dword (80*25*2)
.again:	
	mov al, byte " "
	call write_char
	loop .again

    pop ecx
    pop eax	
	ret

textmode_ClearScreen:
    call clear_screen
    RET	

textmode_DisplayMessage:
    call DisplayMessage32
    RET

textmode_WriteChar:
    call write_char	
	RET
	
	
	
	
;;====================================================================
;; DRAW CHAR:
;;     Teste para tentar desenhar um caractere em modo gráfico 32bit.
;;
;; draw-char
;;     Desenha um char em assembly, usando o mapa de caracteres do BIOS.
;;     Será usado no Boot Manager, para produzir mensagens em 32bit assembly.
;; na hora de carregar o boot loader.
;;
;;
;; Variáveis usadas.
;;

;;Variáveis do sistema.
;;Configuração salva no sistema.
_gfontAddress:
    dd 0
_gcharWidth:
    dd 0
_gcharHeight:
    dd 0
	

;_c:
;    dd 0
	
	
;_work_char:
;    dw 0  

;_work_char_address:
;  dd 0	
  
; byte que representa uma linha do char a ser pintado  
CHAR_PART:
    DB 0

;;endereço do byte que representa a parte do char a ser pintada.	
CHAR_PART_ADDRESS:
    DD 0	
	
;;offset dentro do charmap do BIOS,
;;para encontrar o byte que representa a linha do char a ser pintada.	
CHAR_PART_OFFSET:
    DB 0  
  
_y2:
    dd 0
_x2:
    dd 0
_y:
    dd 0	
_x:
    dd 0
_color:
    dd 0
_bit_mask:
    db 0

	

;-----------------------------------------
; _my_buffer_char_blt:
;     Função para desenhar um caractere usando o mapa de 
; caracteres do BIOS.
;
; @todo: Argumentos ... variáveis ...
;
; a =  cor (rrggbbaa)
; b =  x
; c =  y
; d =  Char.
;	
global _my_buffer_char_blt
_my_buffer_char_blt:

	;salvamentos
	

    mov dword [.color], eax  ;;color  	 
	mov dword [.x], ebx      ;;x
	mov dword [.y], ecx      ;;y
	mov byte [.char], dl     ;;char  (deslocamento)

	
	pushad
	
	
	;;configuração provisoria para testes...
	mov dword [_gfontAddress], 0x000FFA6E ;;Mapa de caracteres do BIOS.   
	mov byte [_gcharWidth], 8              
	mov byte [_gcharHeight], 8
	
	;color
	mov eax, dword [.color]	
	mov dword [_color], eax    ;; Color
	
	;x 
	mov eax, dword [.x]
	mov dword [_x], eax        ;; x
	
	;y
	mov eax, dword [.y]
	mov dword [_y], eax        ;; y
	
	;char 
	mov al, byte [.char]
	mov byte [CHAR_PART_OFFSET], al        
	
    ;;inicializando uma linha do char a ser desenhado. 	
	mov byte [CHAR_PART], 11111111b  ;; CHARPART  SUJO, TUDO 1.inicializando.
	
    ;criando a máscara de bits
	mov byte [_bit_mask], 0x80
 
    ;;
	;; A variável [_work_char] conterá o sesuldado dessa adição aqui.
	;;
	;; work_char = (void *) gfontAddress + (c * gcharHeight);
    ;;
	
	;
	; Calculamos o deslocamento para pegarmos o caractere certo na fonte.
	;
	
	;; Deslocamento no char map do BIOS.
	xor eax, eax
	mov al, byte [CHAR_PART_OFFSET]    	
	
	;;O valor do deslocamento deve ser multiplicado pela altura do char
	;;para encontrarmos o real deslocamento.
	push ebx ;salva
	xor ebx, ebx
	mov ebx, 8; [_gcharHeight]
	mul ebx    ;; realiza a multiplicação e coloca o resultado em eax.    
	pop ebx ;recupera 	
	
	;;adicionando a base ao deslocamento..
	add eax, 0x000FFA6E    ;[_gfontAddress]   
	
	;; Encontramos o endereço do byte que iremos pegar 
	;; para servir de parte do char que queremos desenhar.
	mov dword [CHAR_PART_ADDRESS], eax
	
	;;
	;; '********' CHAR PART 
	;; Pegando o byte encontrado dentro do char map do BIOS.
	;;
	
	push ebx
	xor ebx, ebx
	mov bl, [eax]
	mov byte [CHAR_PART], bl	
	pop ebx
	
	;;
	;; Começa um 'for'.
	;;
	
	;;for( y2 = 0; y2 < gcharHeight; y2++ )
	
	;; Zerando o contador [_y2] ...
	mov dword [_y2], 0
.L4_comeca_um_for:
    ;debug
    ;pushad 
 	;mov eax, 200  ;x.
	;mov ebx, 0   ;y.
	;mov ecx, 30  ;largura.
	;mov edx, 30  ;altura.	
    ;mov edi, dword  0x00108000    ;blue    	
	;call CreateWindow
	;call _asm_refresh_screen
    ;popad 
	
	

	
	;;
	;; Se o [_gcharHeight] for maior ou igual ao [_y2], que está 
	;; armazenado em eax.
	;;
	
	XOR EAX, EAX
	mov eax, [_y2]		
	
    cmp dword eax, 8    ;[_gcharHeight] ;8
	jge	.L1_done_fim_do_Height
	
	;; Inicializando a variável [_bit_mask]
	mov byte [_bit_mask], 0x80

	;;
	;; Começa de outro 'for'.
	;;

    ;;for( x2 = 0; x2 < gcharWidth; x2++ )
	
    ;; Zerando o contador [_x2] ...	
	mov dword [_x2], 0
.L7_comeca_outro_for:  ;;for de largura.

    ;pushad 
 	;mov eax, 400  ;x.
	;mov ebx, 0   ;y.
	;mov ecx, 30  ;largura.
	;mov edx, 30  ;altura.	
    ;mov edi, dword  0x00108000    ;blue    	
	;call CreateWindow
	;call _asm_refresh_screen
   ; popad 
	
    ;;coloca o [_x2] em eax.
	
    ;;
	;; Se o [_gcharWidth] for maior ou igual ao [_x2],
	;; que está armazenado em eax.	
	;;

	XOR EAX, EAX
	mov eax, [_x2]
	
	cmp dword eax, 8 ;[_gcharWidth]
	jge	.L8_fim_do_Width
	
	;;
	;; if( (*work_char & bit_mask) )
	;;
	
    ;push eax 
	;push edx
	
	xor eax, eax
    xor edx, edx
	
	mov al, [CHAR_PART]    ;;; *********** PROBLEMAS NA TROCA DO WORKCHAR ************
	mov dl, [_bit_mask]
    and al, dl	
	;mov byte [CHAR_PART], al

	;; prepara pra sair.
	;test eax, eax                ;set ZF to 1 if al == 0
	;;
	;; Se al for igual a '0', então seta zf para 1.
	;;
	;test al, al
	;pop edx
	;pop eax
	
	;; Se al for igual a '0', então seta zf para 1.
	;;
	;test ax, ax
    ;js .L10_nao_mostra_pixel	
	;je .L10_nao_mostra_pixel
	;je .L10_nao_mostra_pixel    ;jump if ZF == 1
	
	cmp al, 0
	je .L10_nao_mostra_pixel
	
	;;
	;; se não saltou no jmp acima é porque decidiu mostrar o pixel.
	;;
	
;;++	
	;
	; my_buffer_put_pixel(color, x + x2, y, 0);
	;
	
	;
	; Preparando a pilha para a chamada.
	; Obs: Esses argumentos podem ser passados via registradores, 
	; depende da rotina chamada.
	; No nosso caso no Boot Manager, usaremos registradores e não pilha.
	; @todo: Usar registradores.
	;
	
    ;
    ; a =  cor (rrggbbaa)
    ; b =  x
    ; c =  y
    ; d = ?
    ;
	
	;;
	;; Observação: Essa rotina pode ser reduzina,
	;; excluindo algumas instruções desnecessárias.
	;;
	
	
	push eax 
	push ebx 
	push ecx 
	push edx 	
	
	;0 (d)
	mov edx, 0     ;; d
	;y (c)
	mov ecx, [_y]  ;; c
	;x+x2 (x) ??
	mov eax, [_x2]
	add eax, [_x]	  
    mov ebx, eax       ;; x
	;color (a)
	mov eax, [_color]    ;; a
.showPixel:	
	call lib32PutPixel  ;;Put pixel on back buffer.
	
	;debug
	;ok para teste, daremos um refresh na tela para cada pixel pintado.
	; espero que isso não suje os registradores.
	;;call _asm_refresh_screen

	pop edx 
	pop ecx 
	pop ebx 
	pop eax
	
;;--
    ;
.L10_nao_mostra_pixel:

    ;debug
    ;pushad 
 	;mov eax, 100  ;x.
	;mov ebx, 0   ;y.
	;mov ecx, 30  ;largura.
	;mov edx, 30  ;altura.	
    ;mov edi, dword  0x00804000    ;blue    	
	;call CreateWindow
	;call _asm_refresh_screen
   ; popad 

	
	;;o bit mask precisa mudar sem estragar eax...
    ;;bit_mask = (bit_mask >> 1);

	;; shr
	push eax
	mov al, byte [_bit_mask] 
	shr al, 1         
	mov byte [_bit_mask], al
	pop eax
	
	; Incrementando o contador...
	
	push eax
	mov eax, [_x2]   
	inc eax
	mov [_x2], eax
	pop eax
	
	jmp	.L7_comeca_outro_for
	;
	
;
; Qaundo finalmente pintarmos 8 pixel na horizontal, é o fim da largura.
;	
	
.L8_fim_do_Width:

    ;debug
    ;pushad 
 	;mov eax, 300  ;x.
	;mov ebx, 0   ;y.
	;mov ecx, 30  ;largura.
	;mov edx, 30  ;altura.	
    ;mov edi, dword  0x30808000    ;blue    	
	;call CreateWindow
	;call _asm_refresh_screen
    ;popad 

	
    ;; Aqui existem três incrementos,
    
	;; y++;
	;; Um endereço de memória. Posicionamento de pixel.
	mov eax, [_y]      
	inc dword eax
    mov [_y], eax	
	
    ;;
	;; Incrementando para irmos para a p´roxima linha do char
	;; representada por um byte. ??
	;;
	
	;; work_char++;
	;mov eax, [_work_char]
	;inc dword [eax]
	
	
    mov eax, dword [CHAR_PART_ADDRESS]	
	inc eax        ;; pegaremos o byte do endEreço seguinte, que conterá a próxima linha do char.
	mov dword [CHAR_PART_ADDRESS], eax  ;;novo endereço.atualiza o endereço que estamos usando.
	
	mov ebx,  dword [CHAR_PART_ADDRESS] ;;atualiza O CHAR PART.
	mov al, [ebx]
	mov byte [CHAR_PART], al            ;;atualiza O CHAR PART.
	
	;; Contador...
	mov eax, [_y2]
	inc dword eax
	mov [_y2], eax
	
	jmp	.L4_comeca_um_for
	;
.L11:
.L1_done_fim_do_Height:
    ;debug
    ;pushad 
 	;mov eax, 700  ;x.
	;mov ebx, 0   ;y.
	;mov ecx, 90  ;largura.
	;mov edx, 90  ;altura.	
    ;mov edi, dword  0x00808000    ;blue    	
	;call CreateWindow
	;call _asm_refresh_screen
    ;popad 

	
	;leave
	popad
	ret

.tmp: 
    dd 0

.char: db 0
.color: dd 0
.x: dd 0
.y: dd 0
 
;
;fim
;


