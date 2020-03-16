
   kgwm - kernel gramado window manager.

   
 
   Nessa pasta ficarão as rotinas que pertencem ao window manager.
   Esse window manager ficará dentro do kernel base. Mas no futuro teremos 
outros window manager que ficarão fora do kernel base. Provavelmente serão
servidores em user mode.



    #todo: 
    Já existem rotinas de window manager em outra pasta. 
    Agora temos que trazer essas rotinas para cá. Separando claramente
    o window server, os drivers do window server e o window manager.



    /kdrivers/x = drivers do window server.
    /kservers/kgws =  window server.
    /kservers/kgwm =  window manager. 
