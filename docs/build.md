## Gramado OS build instructions

## Fred's host machine
```
    Linux 5.4.0-77-generic x86_64
    gcc (Ubuntu) 7.5.0
    GNU ld (GNU Binutils for Ubuntu) 2.30
    NASM version 2.13.02
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


