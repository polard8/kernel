

Sobre o diretório executive/sm:
==============================
   
    /sm  * o 'console' é a interface de administração do sistema,

     'System Management'.
     Esse diretório comtém os recursos de gerenciamento de sistema, independente se
estão em modo texto ou modo gráfico.


     Os serviços oferecidos por esses módulos do kernel base poderão ser solicitados
por utilitários do sistema em user mode que desejam configurara o sistema. Obs: Os utilitários utilizarão rotinas mais complexas e maiores que essas. Essas rotinas aqui serão as primitivas usadas por eles.


    Obs: INIT.TXT é o arquivo de configuração do sistema por enquanto.
         ele fica no diretório raiz por enquanto.
         /root/INIT.TXT.


   @todo: Criar pasta /devices.



   **** Importante:
        ===========


   Existe uma função chamada "void *systemGetSystemMetric(int number)" ... que retornará
  muitas medidas do sistema, usadas para criação em dimensões apropriadas e para análises diversas.

a função fica em sm\system\system.c. 