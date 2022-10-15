# Welcome to Gramado OS


This repository has the source code for:

* Gramado boot loader
* Gramado kernel
* Gramado Window Server
* Applications
* Commands

## What is Gramado?

    Gramado (c) is a 64bit multithreaded operating system.

## Screenshots

![Screenshot](https://raw.githubusercontent.com/frednora/screenshots/main/gramado-1.png)
![Screenshot](https://raw.githubusercontent.com/frednora/screenshots/main/gramado-2.png)

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
    Linux 5.15.0-41-generic x86_64
    gcc (Ubuntu) 11.2.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```

## How to Build?

> See the [Gramado OS build instructions](https://github.com/frednora/gramado/blob/master/admin/docs/build.md)

## Testing

```
	$ ./run
	$ make qemu-test
```

The old versions were tested for a long period of time on my 
real machine. A Gigabyte/Intel Core 2 Duo/Chipset VIA.
Now i'm testing only on qemu and virtualbox.
Please, give us some feedback.

## Documentation

> See the [docs](https://github.com/frednora/gramado/tree/main/admin/docs).

## Author

* **Fred Nora** - [frednora](https://twitter.com/frednora)

## Contributors

* **Fred Nora** - [frednora](https://facebook.com/frednora)

## License

Gramado is a Free and Open Source operating system.
The source code uses the BSD license.

# Quotes:
> Oh boy, there is no spoon!
> The beast hates science and the scientist.
