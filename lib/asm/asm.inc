

;; System call
;; IN: eax, ebx, ecx, edx 
;; OUT: eax

asm_system_call:
    
	push eax
	push ebx
	push ecx
	push edx
	
	;int 200
	int 0x80 
	
	mov dword [.sc_ret], eax
	
	pop edx
	pop ecx 
	pop ebx 
	pop eax
	
	mov eax, dword [.sc_ret]
	ret 
	
.sc_ret
    dd 0
	
	
	
;; Create Window
;; IN: ebx = Endereço do buffer que contém os argumentos.
;; OUT: ebx = return

asm_create_window:
	
	mov eax, 118
	;int 200	
	int 0x80 
	xor eax, eax
	xor ebx, ebx
	ret
	
	
asm_refresh_screen:
	
	mov eax, 11
	;int 200	
	int 0x80 
	xor eax, eax
	ret
	
	
asm_reboot:
	
	mov eax, 110
	;int 200	
	int 0x80 
	xor eax, eax
	ret
	
	
	
;;IN: ebx = x ; ecx = y
;;OUT:
	
asm_set_cursor:
    
	mov eax, 34
	;int 200
    int 0x80 
    xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	ret 
	

;; IN: Nothing
;; OUT: eax = pointer x position.
	
asm_get_cursor_x:
	mov eax, 240
	;int 200
	int 0x80 
    ret 
    
;; IN: Nothing
;; OUT: eax = pointer y position.
	
asm_get_cursor_y:
	mov eax, 241
	;int 200
    int 0x80 
	ret 
	
	
	
	
;; Obtem informações sobre dimensões e posicionamentos.
;; IN: ebx = index
;; OUT: eax = value

asm_get_system_metrics:	
    mov eax, 250
	;int 200
	int 0x80 
	xor ebx, ebx
    ret	
	
	
	
	

