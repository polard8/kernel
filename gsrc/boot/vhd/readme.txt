    /vhd/readme.txt

    O objetivo maior é criar um disco virtual chamado SYSTEM.VHD
e incluir dentro do disco virtual todas as outras partes do sistema 
operacional que já foram compiladas anteriormente em outros projetos.

    O sistema é chamado SYSTEM.VHD. É um VHD de 32 MB, feito em 
	Assembly. (NASM).
	Dentro do vhd podem ser carregados os arquivos do sistema, como kernel, 
	boot loader e processos.
	            
Sobre as aplicações:
===================
    As aplicações são programas feitos em 32bit.
    Rodam em user mode. 
	 
Como o VHD é montado:
=====================
    Ao usar o imdisk para montar o VHD e copiar os arquivos
    dentro do VHD, os parametros do sistema de arquivos são:
    
	imdisk -a -f SYSTEM.VHD -s 31M -m F: -b 63b

    Agora o vhd conterá apenas o stage 1, sendo qua a atribuição do stage 1 será apenas 
	carregar o BM.BIN na memória em 0:8000h e passar o comando para ele em (0:8000H+offset).


;;setores

    0 = mbr
   63 = vbr
   67 = fat1
  313 = fat2
  559 = root
  591 = data area
  

;
; Fim.
;
    