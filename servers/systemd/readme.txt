https://en.wikipedia.org/wiki/Runlevel

    ===================================
   /systemd

   Conjunto de programas que são usados durante a inicialização do sistema.
   Um desses programas podem ser o primeiro processo a rodar, normalmente 
   é o programa INIT.BIN.

   Ambiente: Apenas Ring 3.
   
   Várias servidores de gerenciamento do sistema farão parte
   desse ambiente chamado systemd.
   
   Em systemd/core/ ficarão os programas principais do systemd.
   
   +init é um processo que serve para ser clonado para que o
   shell execute um programa no ambiente gramado core. Isso é provisório.
   
   +shell é um ambiente de usuário, tem um terminal de comandos
    e um servidor de recursos gráficos chamado gws.
   
   +taskman será o gerenciador principal.
   
   
   Outros programas farão parte do ambiente systemd, todos voltados
   ao gerenciamento de recursos básicos do sistema.

   
   ===============================================
   /systemd/core

   Gramado Core Environment.

   Ambiente básico onde esses programas de habitam.
   Outros componentes do sistema podem atuar diretamente 
   no gramado core.

   Os programas do gramado core são:
   /systemd/core/init
   /systemd/core/shell
   /systemd/core/taskman   
   
   ==============================================

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
  