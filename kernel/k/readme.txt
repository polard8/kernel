
Sobre o kernel base:
====================
    O kernel base é o núcleo do sistema operacional, roda no ambiente
ring0 e é construido em camadas. O executável chama-se KERNEL.BIN.	
   
   

*******************************************************************************************
Lista de diretórios do kernel base:
===================================

    /gramado      - (4) GUI.
    /executive    - (3) Drivers VIPs, que ficam em kernel mode.
    /microkernel  - (2) Kernel mínimo e fundamental. (processos e threads).	
    /hal          - (1) Hardware abstraction layer

	
    Os diretórios representam as camadas do kernel base. 
	
    A camada mais alta é a camada /gramado, que é a interface gráfica.
    A camada mais baixa é a camada /hal que lida liretamente com o hardware. Mas
essa camada poderá inda chamar um modulo externo em kernel mode que possivelmente será criado
e chamará HAL.BIN, para efeito de portabilidade do kernel base, o módulo externo HAL.BIN
se encarregará das diferenças de arquitetura deixando para o módulo interno /hal o trabalho
de interface entre o kernel base e o módulo externo HAL.BIN.	
*********************************************************************************************	


Sobre o executive:
    Sâo modulos incluidos ao 'kernel base' na hora da compilação
    pois são modulos e drivers sistemicamente importantes.
    os módulos do kernel que serão ligados dinamicamente serão
 módulos de menor importancia para o funcionamento do sistema, como o kd.
   por exermplo: não se deve fazer um modulo para o timer.

...
 

Obs:
    A outra parte do controle do hardware fica em user mode. 
    (servers, drivers)

     *@todo:
     * No futuro serão esses 3 diretórios, so que com outros nomes.
       pois a estrutura hal,microkernel e executive pertencem a M$. 
       ex: /hardware /microkernel /system




Design Notes 1.


Notas de Design que descreve as principais partes do Kernel Base.
Estamos no diretório /k e cada um dos diretórios contidos aqui representam uma
das partes fundamentais do Kernel Base, São elas /hal, /microkernel e /executive.


Pode-se imaginas o kernel dividido em 3 classes principais. As classes do kernel são: hal, microkernel, executive.


    k.hal
    k.microkernel
    k.executive

    Kernel classes (k.____).
	
/gramado é a camada mais externa.	


Versão do documento: 1.0, 2016.
   


  
;
; fim.
;