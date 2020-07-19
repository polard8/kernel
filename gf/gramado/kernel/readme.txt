
    The base kernel 
    This is the folder for the base kernel's source code.
    Everything here is gonna run in ring 0, 32bit protected mode.
    It will generate the image KERNEL.BIN.
    2020 - Fred Nora
 
 
Folders:

bottom/
    Low level components. It is hardware dependent.

include/
    All the headers for the Kernel.

lib/
    Libraries.
ps/
    Process structure.
    process, thread, mm, ipc, scheduler.
top/
    High level components. It is hardware independent.
    net support.
    system management.
    kgws - window server
    kgwm - window manager
    sci - system call inteface

