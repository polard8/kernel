   /4Nora/b     (pasta de src para o sistema de boot.)    


    Sobre o sistema System4Nora, do 4Nora OS:
    ========================================




    ////    ****    ****    ////
    ////    ****    ****    ////
    ////    ****    ****    ////
    ////    ****    ****    ////




    O objetivo maior desse sistema 4Nora é criar um disco virtual chamado SYSTEM.VHD
e incluir dentro do disco virtual todas as outras partes do sistema operacional que já
foram compiladas anteriormente em outros projetos.




    ////    ****    ****    ////
    ////    ****    ****    ////
    ////    ****    ****    ////
    ////    ****    ****    ////



    O sistema é chamado SYSTEM.VHD. É um VHD de 32 MB, 
	feito em assembly. (NASM).
	Dentro do vhd pode ser carregado os arquivos do sistema, 
	como kernel boot loader e processos.
	A primeira parte é feita em assembly, é chamada de bootmanager ou 
	msm (Mass StorageManager). Por si só o msm é formado de 4 partes. 
	Ele pode rodar sozinho ou servir de inicialização para carregar o 
	arquivo BL.BIN, que carregará o resto do sistema.
	O MSM Comtém 4 programas compilados juntos no arquivo mais.asm.
    São eles:
       1, Boot Manager (16 e 32 bit).
       2, Boot Loader (32 bit). (@todo)
       3, Kernel (32 bit).      (@todo)
       4, Browser (32 bits).    (@todo)
	   
	Obs:
    Nesse modelo de sistema. NÃO se utiliza o arquivo BM.BIN,
    pois o código dele agora é o início do VHD criado em assembly.
  	
	   
    Observação sobre o Browser:
	    O nome é 4Nora Browser. É a interface gráfica. 
		É a área de trabalho onde aparecerão as páginas em html, 
		os atalhos para as aplicações ou os gerenciadores do sistema.
        
Sobre o subsistema:
===================
    O subsistema é chamado SYSTEM.BIN.
    É um programa em user mode feito em C.
    Serão usados os códigos do Boot Loader em C e
    do Kernel em C, já feitos.
    A atribuição do subsistema é ser uma interface
    entre as aplicações em user mode e o kernel em assembly.
	Também é o subsistema principal em usermode, podendo os outros 
	subsistemas em usermode se comunicarem com ele.
    
Sobre as aplicações:
===================
    As aplicações são programas feitos em 32bit.
    Rodam em user mode. 
	 
Como o VHD é montado:
=====================
    Ao usar o imdisk para montar o VHD e copiar os arquivos
    dentro do VHD, os parametros do sistema de arquivos são:
   
    FAT1 = LBA 256. (20000h) (size=20)
    FAT2 ~~ 
    ROOTDIR = LBA 510.
    DATAAREA = LBA (BL.BIN=542,KERNEL.BIN=2288). (25000h)
   
    Volume dir: 0x21000
    
	*IMPORTANTE:
    
	A implantação do MSM, (Mass Storage Manager):
	Na compilação 0011, introduz-se a idéia de que o
    Boot Manager deve ser um gerenciador de dispositivos
	de armazenamento de massa. Será chamado de MSM, 
	(Mass Storage Manager). Pois sempre haverá mudanças 
	nos dispositivos de armazenamento que dificultarão 
	a inicialização dos sistemas operacionais 
	de pequeno porte. Os pequenos empreendedores sempre terão 
	dificuldade de acompanharem as mudanças da grande indústria 
	de discos e terão dificuldades na inicialização dos seus sistema.
	É coerente pensar que o gerenciamenteo de disco seja o 
	cerne da inicialização de qualquer sistema e a prioridade do 
	desenvolvedor.


Detalhes da compilação 0004:
    #Carregou o BL.BIN e passou o comando para ele.






   

   bm-vhd ::


    Agora o vhd conterá apenas o stage 1,sendo qua a atribuição do stage 1 será apenas carregar o BM.BIN na memória em 0:8000h e passar o comando para ele em (0:8000H+offset).


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
    