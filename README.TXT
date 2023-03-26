--------------------------------------
Product names:

    Gramado Kernel - core/
    Gramado DE     - desktop/

--------------------------------------
    core/    - Boot loader, kernel and commands. 
    desktop/ - Gramado Window System. (Window server and clients). (DE).
--------------------------------------
Build:
    Type 'make'
Clean up the mess:
    Go into the 'core/' directory and type 'make clean-all'
Running:
    Go into the core/ folder and type './run' or './runkvm'
--------------------------------------
Configuration file:
    include/config/superv/config.h

--------------------------------------
The boot loader starts at:
    core/os/boot/vd/fat/main.asm
--------------------------------------
The kernel starts at:
    core/os/kernel/ke/x86_64/startup/
    


