
Sobre o kernel base:
====================
    O kernel base tem 2 gerenciadores, process.c e modules.c
	O resto são módulos do tipo MB e processos do tipo PB.


Lista de diretórios:
===================

/hal          - Hardware abstraction layer
/microkernel  - Kernel mínimo e fundamental. (tasks)
/executive    - Drivers VIPs, que ficam em kernel mode.



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
;
; fim.
;