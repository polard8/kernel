Executive: (Internal Servers) 

   Sobre o diretório /executive:
   ============================

   O diretório /executive é dividido em três partes:
   /sm, /uitm e uigm.  


 
   Ambiente= ring0

   São os módulos servidores incluidos no Kernel Base.
   
   Os processos em user mode podem chamar esses serviços
   via interrupção, atraves do kernel


   Client --> Kernel --> Server


   pode haver algum tipo de encapsulamento de variáveis e estruturas
   desses módulos.
   o que permite alguma portabilidade desses módulos.



   *** Boa parte do codigo desses porcessos serão aproveitados 
   para drivers e servidores em user mode. por exemplo a GUI.


   @todo: Talvez criar a pasta posix para dar suporte em kernel mode à biblioteca.





