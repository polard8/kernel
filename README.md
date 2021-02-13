# Welcome to Gramado 1.0

This repository has the source code for:

* Gramado boot loader
* Gramado kernel
* Gramado Window Server
* Applications
* Commands

## What is Gramado?

    Gramado (c) is a 32 bit multithreaded operating system.

## Kernel features.

> Paging.
> Threads.
> FAT16 file system.
> ps2/keyboard, serial port, IDE PATA, e1000 NIC.

## Userland features.

* Working on a Window Server. (gws)
* Working on a virtual terminal. 
* unix-like commands running in the virtual console.

## Libraries.

> unix-like library. (rtl)
> API for setup environment. (libcore)
> Lib for the window server's clients. (libgws)

## Fred's compilation on Linux.
```
    Linux 5.4.0-42-generic x86_64
    gcc (Ubuntu) 7.5.0
    GNU ld (GNU Binutils for Ubuntu) 2.30
    NASM version 2.13.02
```
## How to Build?

See the [Gramado OS build instructions](https://github.com/frednora/gramado/blob/master/base/GRAMADO/DOCS/BUILD.MD)

## Testing

```
	$ ./run
	$ make qemu-test
```

You can run the VHD on Oracle Virtual Box and qemu.
Please, give us some feedback.

## Documentation

See the [DOCS](https://github.com/frednora/gramado/blob/master/base/GRAMADO/DOCS/)

## More information

Gramado is a Free and Open Source operating system created by Fred Nora.
The source code uses the BSD license.

# Quotes:
> Oh boy, there is no spoon!

