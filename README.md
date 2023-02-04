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
![Screenshot](https://raw.githubusercontent.com/frednora/screenshots/main/gramado-3.png)

## Kernel features.

> * Paging.
> * Threads.
> * FAT16 file system.
> * e1000 NIC driver.
> * IDE PATA. 
> * ps/2 keyboard. 
> * ps/2 mouse works fine only on qemu.
> * Serial port. 

## Userland features.

> * Window Server. See: gramland/burgundy/server/
> * Some few clients connected to the window server via unix-sockets.
> * Unix-like commands running in the virtual console.

## Libraries.

> * unix-like library. (rtl)
> * Lib for the window server's clients. (libgws)

## Folders.
A brief description of the directories.

    Gramado Kernel - base/
    Gramado DE     - gramland/
    Gramado Games  - meta/

 * `base/` - Low basic components of the system.  
   * `control` - Ring 0 stuff.
     * `boot` - The boot loader.
     * `disk` - The root directory for the boot partition.
     * `new` - The Gramado OS kernel.
   * `exposed` - Ring 3 stuff.
 * `gramland/` - The window server and it's clients.
 * `meta/` - Games and 3D experiments.

## Fred's host machine

```
    Host machine: Ubuntu 20.04.5 LTS
    Linux 5.4.0-137-generic x86_64
    gcc (Ubuntu) 9.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.34
    NASM version 2.14.02
```

## How to Build?

> See the [Gramado OS build instructions](https://github.com/frednora/gramado/blob/master/base/admin/docs/build.md)

## Building and running on vm

```bash
$ make
$ cd base
$ ./run
```

## Clean up the mess

```bash
$ cd base
$ make clean-all
```

The old versions were tested for a long period of time on my 
real machine. A Gigabyte/Intel Core 2 Duo/Chipset VIA.
Now i'm testing only on qemu and virtualbox.
Please, give us some feedback.

## Documentation

> See the [docs](https://github.com/frednora/gramado/tree/master/base/admin/docs).

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
