# Welcome to Gramado OS - Codename 'Gods'


This repository has the source code for:

* Gramado boot loader
* Gramado kernel
* Gramado Window Server
* Applications
* Commands

## What is Gramado?

    Gramado (c) is a 64bit multithreaded operating system.

## Kernel features.

> * Paging.
> * Threads.
> * FAT16 file system.
> * ps/2 keyboard. 
> * ps/2 mouse works fine only on qemu.
> * Serial port. 
> * IDE PATA. 
> * Window Server. See: gramado/core/

## Userland features.

> * Unix-like commands running in the virtual console.
> * Some few clients connected to the window server via unix-sockets.

## Libraries.

> * unix-like library. (rtl)
> * Lib for the window server's clients. (libgws)

## Fred's compilation on Linux.
```
    Host machine: Ubuntu 20.04.3 LTS
    Linux 5.11.0-43-generic x86_64
    gcc (Ubuntu) 9.3.0 
    GNU ld (GNU Binutils for Ubuntu) 2.34
    NASM version 2.14.02
```

## How to Build?

> See the [Gramado OS build instructions](https://github.com/frednora/gramado/blob/main/admin/docs/build.md)

## Testing

```
	$ ./run
	$ make qemu-test
```

Tested only on qemu and on my real machine.
My machine: Gigabyte/Intel Core 2 Duo/Chipset VIA.
Please, give us some feedback.

## Documentation

> See the [docs](https://github.com/frednora/gramado/tree/main/admin/docs).

## Author

* **Fred Nora** - [frednora](https://twitter.com/frednora)

## Contributors

* **Fred Nora** - [frednora78](https://facebook.com/frednora78)

## License

Gramado is a Free and Open Source operating system.
The source code uses the BSD license.

# Quotes:
> Oh boy, there is no spoon!

