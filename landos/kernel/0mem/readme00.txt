
    The base kernel 
    This is the folder for the base kernel's source code.
    Everything here is gonna run in ring 0, 32bit protected mode.
    It will generate the image KERNEL.BIN.
    2020 - Fred Nora
 
 
Folders:

hwi/
    Low level components. It is hardware dependent.

include/
    All the headers for the Kernel.


system/ps/
    Process structure.
    process, thread, mm, ipc, scheduler.

sci/ 
    system call inteface

