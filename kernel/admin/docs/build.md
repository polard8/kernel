## Gramado OS build instructions

## Fred's host machine
```
    Host machine: Ubuntu 22.10
    Linux 5.19.0-23-generic x86_64
    gcc (Ubuntu) 12.2.0 
    GNU ld (GNU Binutils for Ubuntu) 2.39
    NASM version 2.25.05
```

## Build on Linux

```bash
$ make
$ cd kernel
$ ./run
```

## Linux dependencies

**Debian / Ubuntu**
```bash
sudo apt install build-essential make qemu-system-i386 qemu-utils nasm
```


