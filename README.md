# Welcome to Gramado OS

Status: 
Porting Gramado to 64bit.
This is a work in progress.
Here, you can see the old [32bit version](https://github.com/gramado/build241/).

## kernel/  (In progress, almost done)
    The rin0 base kernel.
    (This is a work in progress.)

## lib/ (In progress, almost done)
    The ring 3 libraries.
    #todo We need to port some routines to 64bit.

## init/ (In progress, some few tests)
    This is the first ring3 process.
    (We are using this process to test the ring3 library)

## cmd/ (In progress, some few programs)
    Some ring3 commands.

## ws/ (In progress, Testing the server and some few clients)
    The ring 3 window server and clients.
    
## ns/ (In progress, not tested)
    The ring 3 network server.

## boot/x86/ (Done)
    This is the boot loader.
    (It is working fine.)

## boot/vd/ (Done)
    The virtual disk.

