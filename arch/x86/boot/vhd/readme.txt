#todo:
     
    +As informações aqui precisam ser revistas.
    +Criar arquivo de configuração da GUI. GUI.TXT.
     
    //----------


    Sobre a pasta /vhd:

    Essa pasta comtém o arquivo principal em assembly
que constroi o VHD, algumas pastas e arquivos de configuração.

    /images - Imagens usadas pelo sistema. Serão transferidas para dentro do VHD.
    /stage1 - MBR.
    /tests  - Arquivos de teste.Serão transferidas para dentro do VHD.
  
   


    O objetivo maior desse sistema 4Nora é criar um disco virtual chamado GRAMADO.VHD
e incluir dentro do disco virtual todas as outras partes do sistema operacional que já
foram compiladas anteriormente em outros projetos.


    
    ;;setores
    #todo: Checar se esses valores estão corretos.
           Desejamos valores fixos para facilitar a instalação.

    0 = mbr
   63 = vbr
   67 = fat1
  313 = fat2
  559 = root
  591 = data area
  
    Fred Nora, 12 de outubro 2018.


;
; Fim.
;
    