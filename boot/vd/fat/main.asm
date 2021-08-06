 ;
;; Gramado VHD - Esse é o arquivo principal de um VHD que será montado em 
;; assembly usando nasm. 
;; (c) Copyright 2019 - Fred Nora.
;;
;; File: main.asm 
;;
;; Descrição:
;;     Criaremos um VHD usando nasm. O arquivo principal, main.asm, é o 
;; MBR do VHD e tem por objetivo carregar o BM.BIN na memória em 0:8000h e 
;; passar o comando para ele, além de passar argumentos.
;;
;;     Também estão presentes no arquivo principal, o VBR no setor 63, 
;; incluido em hexadecimal para compatibilidade com sistema host na hora de 
;; carregar os arquivos para dentro do VHD. Os marcadores de início das duas 
;; FATs, o marcador de setores reservados, o marcador de diretório raiz,
;; o marcador de início da área de dados e por fim o footer do vhd.
;;     O arquivo principal só inclui o MBR, que por conveniência fica de fora
;; podendo ser subtituido na hora do teste.
;;     @todo: Podemos incluir também o VBR que está em hexadecimal.
;;     @todo: Agora que o BM.BIN é carregado ddo sistema de arquivos, temos
;; a opção de configurarmos uma GPT logo após o MBR.
;;
;;    O modo de vído usado é o modo texto, herdado do BIOS.
;; O modo de vídeo não será alterado no MBR.
;;
;;
;; Histórico:
;;     2017 - Created by Fred Nora.
;;     2019 -
;;     ...
;;


;;
;; codename db 'londrina'
;;

;;
;; A origem fica em 0, e os segmentos são configurados em 0x7c0, pois
;; o BIOS carrega o MBR em 0x07c0:0, ou seja 0x7c00.
;;


[ORG 0]



;16bit. Entry point do MBR.
[bits 16]


boot_main:

    ;;============================================
    ;;    ****    Entry point do MBR    ****    ;;
    ;;============================================
    ; Stage 1. Esse é o MBR. Carrega o stage 2.

    %include "stage1.asm"


;; Segue um deslocamento para colocar o VBR no lugar certo.
;;=========================================================
;; eof:                                                   ;
;;     End of file.                                       ;
;;     This is the end of Boot Manager.                   ;
;;     PS: The char 'b' is the number 62H                 ;
;;                                                        ;  
eof:                                                      ; 
    times (63*512) - (eof-boot_main) db 'b' ;63 sec.
;;=========================================================




;;=========================================================
;;                      ## VBR ##   #63
;;=========================================================
;;     O VBR da primeira partição fica no setor 63. #63

fs_fat16_vbr:
    %include "vbr1.asm"    



;;
;;  ## HIDDEN SECTORS ##
;;

;;========================================================
;; fs_hidden_sectors:
;;     Setores ocultos. (3 setores)

fs_hidden_sectors:
    times (512) db 'h' ;64
    times (512) db 'h' ;65
    times (512) db 'h' ;66

	
;;
;;  ## FAT 1 ##
;;


;;========================================================
;; fs_fat16_fat1:
;;     Aqui começa a primeira FAT.  #67
;;     Cada fat tem 246 setores
;;
fs_fat16_fat1: 
.firstSector:
    db 0xf8, 0xff, 0xff, 0xff
    times (512)-(4) db 0
.allTheRest:
    times (245*512) db 0 


;;
;;  ## FAT 2 ##
;;
	
;;========================================================
;; fs_fat16_fat2:
;;     Aqui começa a segunda FAT.    #313
;;     Cada fat tem 246 setores
;;
fs_fat16_fat2:
.firstSector:
    db 0xf8, 0xff, 0xff, 0xff
    times (512)-(4) db 0
.allTheRest:
    times (245*512) db 0 


;;
;;  ## ROOT DIR ##
;;
	
;;========================================================
;; fs_fat16_rootdir:
;;     Aqui começa o diretório raiz. #559
	
fs_fat16_rootdir:
.firstEntry:   

    ;; ## Volume1 entry ##
    
    ;; Label (GRAMAD1)
    db 0x47, 0x52, 0x41, 0x4D, 0x41, 0x44, 0x31, 0x20
    db 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00 
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0x7B
    db 0x1B, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

    ; Metafile (GRAMAD2)
    db 0x47, 0x52, 0x41, 0x4D, 0x41, 0x44, 0x32, 0x20
    db 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00 
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0x7B
    db 0x1B, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00


    ;; Podemos criar mais uma entrada aqui,
    ;; como o root dir eh frequentemente carregado pelos boot loader,
    ;; ele podera usar as primeiras entradas como metafiles.
    ;; Essas entrada podem ter nomes como METAVID, METAXX ... HRAMADO
    ;; O sistema operaciona pode editar essas entradas sem nem mesmo
    ;; tocar na fat.
    ;; Podemos limitar o numero de metafiles a '1',
    ;; assim nao teremos muitos arquivos que nao podem ser tocados,
    ;; apenas dois, os dois primeiros.
    ;; Teremos que compactar as informaçoes dentro da entrada.
    ;; #todo: todos os metafiles podem apontar para o mesmo
    ;; cluster apontado pela label ... que provavelmente eh nenhum ...
    ;; ou aponta para os dois primeiros, que estao fora do range
    ;; usado pela fat16.
    
    
    
    ;; Completando o diretório raiz do volume de boot.
    ;; 512 entradas de 32 bytes cada.

    ;;times (32*512) - (32*1) db 0   ;; Com apenas a label   GRAMADO
    times (32*512) - (32*2) db 0     ;; Incluindo o metafile BRAMADO for boot configuration.

    ;; We can setup what boot manager name to load.
    ;; This way we can load a lot of different operating systems.
    ;; Ex: BM, BM1, BM2, BM3 ~ BM9.
        
    ;; We can setup what boot loader name to load.
    ;; This way we can load a lot of different operating systems.
    ;; Ex: BL, BL1, BL2, BL3 ~ BL9.

    ;; We can setup what kernel name to load.
    ;; This way we can load a lot of different operating systems.
    ;; Ex: KERNEL, KERNEL1, KERNEL2, KERNEL3 ~ KERNEL9.

    ;; This way we only need the BRAMADO metafile.
    ;; We will change only 3 bytes in the entry.
    ;; The default files are BM, BL and KERNEL.
    ;; The extended files are BMx, BLx and KERNELx.
    
    

;;
;;  ##  DATA AREA  ##
;;

;;=====================================================================
;; fs_fat16_data_area:                                                ;
;;     DATA AREA.               #591                                  ;
;;                                                                    ;
fs_fat16_data_area:                                                   
    
	;; Essa área compreende o espaço entre o início da área de dados 
	;; da primeira partição até o fim do disco virtual, onde deve ficar o 
	;; footer do vhd conectix da Microsoft.
	;; Nesse caso o disco tem 32MB. Esse será o padrão de tamanho para 
	;; discos vhd usados pelo Gramado.
	;; Outras opções de tamanho serão criadas depois.
	;; Obs: Outra partição poderá ser criada dentro desse espaço.
	;;      Será a partição do sistema, usando o sistema de arquivos ext2.
	
    ;; Completaremos com zeros até o fim do disco.
    ;; 32MB menos a área já utilizada pelas partes criadas anteriormente,
	;; menos 4 bytes de assinatura antes do footer.
	
	;Full data area with zeros.                                           
    times  (32*1024*1024) -( fs_fat16_data_area - boot_main ) -(4) db 0  

.end_of_disk:    
    db '*EOD'    ;; ## END OF DISK ##        
;;====================================================================


;; VHD footer
    %include "footer1.asm"
;
; End
;



