## Gramado OS build instructions

## Fred's host machine

```
    Host machine: Ubuntu 20.04.5 LTS
    Linux 5.4.0-137-generic x86_64
    gcc (Ubuntu) 9.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.34
    NASM version 2.14.02
```


## Linux dependencies

**Debian / Ubuntu**
```console
sudo apt install build-essential nasm make qemu-system-x86-64 qemu-system-gui qemu-utils 
```

## Build on Linux

```console
$ make
$ cd core
$ ./run
```

The command 'make' will compile the GramadoOS and install the files 
into the 'core/control/disk' directory. It will also build 
a disk image into the 'core/' directory, called GRAMADO.VHD.

After that, You can go inside the directory 'core/' and 
run the disk image using the command './run' or the command './runkvm'. 
You also can run the disk image using the Virtualbox.

To clean the mess you can use the command 'make clean-all' inside
the directories 'gramado/' and 'core/'. 



