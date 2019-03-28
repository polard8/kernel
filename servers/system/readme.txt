https://en.wikipedia.org/wiki/Runlevel

    ===================================
   /system

   Conjunto de programas que são usados durante a inicialização do sistema.
   Um desses programas podem ser o primeiro processo a rodar, normalmente 
   é o programa INIT.BIN.

   Ambiente: Apenas Ring 3.
   
   Várias servidores de gerenciamento do sistema farão parte
   desse ambiente chamado systemd.
   
   Em system/core/ ficarão os programas principais do system.
   
   +init é um processo que serve para ser clonado para que o
   shell execute um programa no ambiente gramado core. Isso é provisório.
   
   +shell é um ambiente de usuário, tem um terminal de comandos
    e um servidor de recursos gráficos chamado gws.
   
   +taskman será o gerenciador principal.
   
   
   Outros programas farão parte do ambiente system, todos voltados
   ao gerenciamento de recursos básicos do sistema.

   
   ===============================================
   /system/core

   Gramado Core Environment.

   Ambiente básico onde esses programas de habitam.
   Outros componentes do sistema podem atuar diretamente 
   no gramado core.

   Os programas do gramado core são:
   /system/core/init
   /system/core/shell
   /system/core/taskman   
   
   ==============================================

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
  