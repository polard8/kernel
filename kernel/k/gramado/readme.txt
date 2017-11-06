

/gramado

     Gramado é uma interface gráfica, ela deve ficar dentro do
kernel base, para efeito de desempenho, mas fora dos outros componentes
do kernel base, para efeito de portabilidade. Desse modo poderemos
portar a interface gráfica 'gramado' para outros kernel base com menos dificuldade.
     Muitas funções serão redefinidas e terão o nome traduzido para um nome
agradável para a camada gramado. Essas funções serão canonizadas, permanecendo as
mesmas mesmo que a camada gramado seja usda em outro kernel.
    Ex: gramado_printf = kprintf


Diretórios em /k/gramado:
========================	
	\gui     - Recursos gráficos padrão. 
	\logoff  - A parte do kernelbase referente a gerência de logoff.
	\logon   - A parte do kernelbase referente a gerência de logon.
	\user    - A parte do kernelbase referente a gerencia de contas e usuários.
	
	
gramado\gui

    Recursos de suporte a interface gráfica de usuário.
    O propósito é oferecer recursos gráficos de forma rápida e direta.
Esse é o meio mais direto de um processo acessar recursos gráficos.
Muitas rotinas primitivas de recursos gráficos serão oferecidas dentro do
próprio kernel base para efeito de maior desempenho. Porém haverão bibliotecas em servidores de recursos gráficos 
em um user mode e em kernel mode. Cada servidor
de recurso gráficos terá um desempenho e um privilégio diferente. Os servidores de recursos gráficos poderão utilizar 
das primitivas oferecidas pelo kernel base.

    Um servidor que ofereça recursos gráficos de forma mais direta e com maior desempenho derá seu nome 
	relacionado com a palavra DIRECT ou FAST.
Ex: DIRECTMEDIA, DIRECTVIDEO, FASTVIDEO ... ETC...



Sobre o modulo gramado\gui:
===========================
    O propósito do módulo /gui é oferecer recursos para a interface gráfica de usuário. 
	para que o usuário possa interagir com o sistema através de uma interface gráfica, u
	sando janelas e menus...
    O módulo \gui da da interface gráfica Gramado é o responsável pela parte da apresentação
da interface, SÃO OS ELEMENTOS GRÁFICOS PROPRIAMENTE DITOS. outros módulos dentro da pasta
\gramado poderão ser criados para outras funcionalidades da interface gráfica.

Outros módulos:
==============  
    Outro módulos de suporte a recursos gráficos poderão ser criados aqui na camada \gramado.
modulos que gerenciem o suporte aos recurso necessários para se ter uma boa interface 
de usuário em modo gráfico. Ex: Podem gerenciar os recursos de hardware como aceleração 
2d e 3d entre outras funcionalidades. Como configrações de propriedades físicas do video. 
Ex: Retraço vertical...etc...Lembrando que quem acessará o hardware será o módulo hal, 
aquia ficarão alguns gerenciadores em camada mais alta.


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

   + Uma opção seria uma rotina em usermode de criação de janela realiza varias chamadas ao kernel soliciatando 
   primitivas de rotinas
     gráficas. Ex: Uma chamda estabelece as dimensões da janela e outra as cores, epor fim uma rotina monta o 
	 window frame todo
     com os elementos previamente passados. 

     *importante:
     Obs: Uma rotina de inicialização do procedimento de pintura garante exclusividade para
     o processo, assim nenhum outro processo poderá realizar essa rotina de pintura enquanto o processo não 
	 tiver acabado.
	 
	 
	 
	 


    