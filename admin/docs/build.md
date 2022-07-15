## Gramado OS build instructions

## Fred's host machine
```
    Host machine: Ubuntu 20.04.3 LTS
    Linux 5.15.0-41-generic x86_64
    gcc (Ubuntu) 11.2.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```

## Build on Linux

```bash
$ cd gramado
$ make
$ ./run
```

## Linux dependencies

**Debian / Ubuntu**
```bash
sudo apt install build-essential make qemu-system-i386 qemu-utils nasm
```


