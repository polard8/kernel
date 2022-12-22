## Gramado OS build instructions

## Fred's host machine
```
    Host machine: Ubuntu 22.10
    Linux 5.19.0-23-generic x86_64
    gcc (Ubuntu) 12.2.0 
    GNU ld (GNU Binutils for Ubuntu) 2.39
    NASM version 2.25.05
```

## Linux dependencies

**Debian / Ubuntu**
```console
sudo apt install build-essential nasm make qemu-system-x86 qemu-system-gui qemu-utils 
```

## Build on Linux

```console
$ make
$ cd kernel
$ ./run
```

The command 'make' will compile the GramadoOS and install the files 
into the 'gramado/kernel/control/disk' directory. It will also build 
a disk image into the 'gramado/kernel' directory, called GRAMADO.VHD.

After that, You can go inside the directory 'gramado/kernel' and 
run the disk image using the command './run' or the command './runkvm'. 
You also can run the disk image using the Virtualbox.

To clean the mess you can use the command 'make clean-all' inside
the directories 'gramado/' and 'gramado/kernel'. 



