
executive/uigm

    UIGM - User Interface Graphic Mode.
    Recursos de suporte a interface gráfica de usuário.
    O proósito é oferecer recursos gráficos de forma rápida e direta.
Esse é o meio mais direto de um processo acessar recursos gráficos.
Muitas rotinas primitivas de recursos gráficos serão oferecidas dentro do
próprio kernel base para efeito de maior desempenho. Porém haverão bibliotecas em servidores de recursos gráficos em um user mode e em kernel mode. Cada servidor
de recurso gráficos terá um desempenho e um privilégio diferente. Os servidores de recursos gráficos poderão utiizar das primitivas oferecidas pelo kernel base.

    Um servidor que ofereça recursos gráficos de forma mais direta e com maior desempenho derá seu nome relacionado com a palavra DIRECT ou FAST.
Ex: DIRECTMEDIA, DIRECTVIDEO, FASTVIDEO ... ETC...



Sobre o modulo /gui:
===================
    O propósito do módulo /gui é oferecer recursos para a interface gráfica de usuário. para que o usuário possa interagir com o sistema através de uma interface gráfica, usando janelas e menus...


Outros módulos:
==============  
    Outro módulos de suporte a recursos gráficos poderão ser criados aqui.
modulos que gerenciem o suporte aos recurso necessários para se ter uma boa interface de usuário em modo gráfico. Ex: Podem gerenciar os recursos de hardware como aceleração 2d e 3d entre outras funcionalidades. Como configrações de propriedades físicas do video. Ex: Retraço vertical...etc...Lembrando que quem acessará o hardware será o módulo hal, aquia ficarão alguns gerenciadores em camada mais alta.


 @todo:
 +Graphic Mode configuration.
 +Temas.
 +O diretório de imagens usadas pelo modo gráfico
 +o arquivo que salva as configurações de modo gráfico.



  @todo:
  Sobre o processo de criação de janelas quando a rotina de criação de janelas é chamada por um processo em user mode:
  ====================================================================================================================
  
  *iMPORTANTE: Pode haver mais de um método de criação de janela. Tanto eles podem coexistirem, quando podemos
               selecionar o melhor com o passar do tempo.

   + Uma opção seria uma rotina em usermode de criação de janela realiza varias chamadas ao kernel soliciatando primitivas de rotinas
     gráficas. Ex: Uma chamda estabelece as dimensões da janela e outra as cores, epor fim uma rotina monta o window frame todo
     com os elementos previamente passados. 

     *importante:
     Obs: Uma rotina de inicialização do procedimento de pintura garante exclusividade para
     o processo, assim nenhum outro processo poderá realizar essa rotina de pintura enquanto o processo não tiver acabado.