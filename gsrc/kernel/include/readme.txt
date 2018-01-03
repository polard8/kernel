sobre o diretório /include:
============================


   /include stuff.


   O diretório /include contém headers da biblioteca padrão C e os principais
   header do kernel, principalmente os que tem atuação global e não se
   incluem nos módulos /executive /hal /microkernel e /gramado.


*****************************************************
 Os diretórios são:
 ==================

/gramado          - Headers para a GUI.
/executive        - Headers para o executive do kernel.
/microkernel      - Headers para o microkernel do kernel.
/hal              - Headers para o hal do kernel.
 

Obs: Cada diretório é uma camada do kernel, sendo /gramado a
camada mais alta, compreendendo os recursos de interface gráfica.

*******************************************************


   Criado o arquivo de definições globais 'gdef.h'
   ele deve ficar no início das definições, pois
   servirá à todos os módulos.
  
   set 2017.