
 /init
 
     All the services here runs in ring 3. It's used to initialize the system.


Folders:

    /init2 -  init process.
    
    /grammgr - 
        Main program to manage the critical processes. 
        Those one that is essential to keed the system alive.
        
ps: 
It will not manage the ws and the wm, it's because ws and wm are 
part of the garden system. So /gramado is gonna live with a 
minimal window server (kgws), just enough to print chars in the screen.
                 
        grammgr.bin will initialize the ili environment. 
The ili environment is gonna initialize gws and gwm.
