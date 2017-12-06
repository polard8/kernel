Executive: (Internal Servers) 

   Sobre o diretório /executive:
   ============================

   O diretório /executive é dividido em partes:
   
    /ram  - (Gerenciamento de memória primária).
    /sm   - (gerenciamento do sistema:logon,logoff,user ...).
    /tty  - (fluxo de caractere: teclado-->processo, processo-->monitor).
    /uitm - (gerenciamento do modo texto)
    /uigm - (gerenciamento do modo gráfico)
    /sci  - systemcall interface. 
 
   Ambiente= ring0

   São os módulos servidores incluidos no Kernel Base.
   
   Os processos em user mode podem chamar esses serviços via interrupção, 
através do kernel


   Client --> Kernel --> Server


   Pode haver algum tipo de encapsulamento de variáveis e estruturas
   desses módulos, o que permite alguma portabilidade desses módulos.



   *** Boa parte do código desses porcessos serão aproveitados 
   para drivers e servidores em user mode. por exemplo a GUI.



   //
   //    ****    O SHELL E O EXECUTIVE    ****
   //


 O utilitário 	SHELL.BIN em user mode poderá chamar, atravéz de comandos, vários programas,
ou funcionalidades internas. Quando o shell ou outro programa chamar rotinas de gerenciamento de sistema ele deve interacir principalmente com o módulo /sm, que é o console do sistema.

   //
   //    ****    OS UTILITÁRIOS E O EXECUTIVE    ****
   //



    Como os utilitários tem por objetivo principal algum tipo de análise ou gerenciamento do sistema,
é natural que eles interajam com o módulo /executive. sendo o executive a principal porta de entrada
para os utilitários ... em especial o módulo /executive/sm, que é o console do sistema.

  Na verdade topo programa em user mode devera utilizar o executive como porta de entrada, mas apenas os utilitários utilizarão mais as funcionalidades de console /sm.





























