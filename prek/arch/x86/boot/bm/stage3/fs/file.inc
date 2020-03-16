;
; Arquivo: fs\file.inc
;
; Descrição: 
;     Operações com arquivos.
;
; Versão 1.0, 2015, 2016.
;



;
; Boot Loader info. (BL.BIN em C) (valores desatualizados)
;

FILE_IMG_ADDRESS             equ 0x00009000   ;20000 
FILE_IMG_ADDRESS_ENTRY_POINT equ 0x00009200   ;21000
FILE_IMG_LBA                 equ 2336          
FILE_IMG_SIZE                equ 64 



;--------------------------------------------
; start_program:
;    Carrega um arquivo e executa.
;
; eax = endereço do nome do arquivo.
;
start_program:   
    ;
	;call fat16_read_file  
    ;call FILE_IMG_ADDRESS_ENTRY_POINT
	;
	ret

	
;
;fim.
;	
