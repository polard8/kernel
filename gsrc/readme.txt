
 Gramado:
 =======

     'Gramado OS'
     Esse será o nome do sistema operacional.
     Servirá de guia para todos os componentes criados, como:
     bm, bl, kernel, idle, shell, taskman ...


 Diretórios:
 ==========

     A organização dos diretórios no desenvolvimento do sistema operacional Gramado utilizando 
a plataforma Windows:

************************************************
 Principais:
 ===========
 
         /gbuild    - Scripts e documentação para compilação.
	 /gdocs     - Documentação.
	 /gramado   - Destino de binários e arquivos de configuração.
	 /gsdk      - Ferramentas para desenvolvimento.
	 /gsrc      - *Códigos.
	 
	 
***********************************************
 Organização do diretório /gsrc:
 ==============================
 
         /boot   - Programas utilizados na inicialização.
	 /config - Arquivos de configuração.
	 /gapps  - Aplicações em user mode.
	 /glibs  - Bibliotecas e frameworks para user mode. (backend support??)
         /gshell - Conjunto de programas para interação com o usuário.
	 /gutil  - Utilitários do sistema.
	 /kernel - O programa kernel.
	 

 As camadas principais em user mode devem ser:
 =============================================
    +Shells           /gshell
    +Utilities        /gutil
    +Applications     /gapp
    +Libraries        /glib




