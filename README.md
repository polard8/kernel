# GramadoOS

Gramado Operating System.

## What is Gramado Operating System?

GramadoOS is a graphical operating system for x86_64 computers.

## What is the category it belongs to? 

Gramado is a hobby operating system, not a commercial operating system, 
because it is a small system and has only some few features, 
not all the features needed by a commercial operating system.

## What are the features of Gramado Operating system?

The core features are:

> * Paging.
> * Threads.
> * FAT16 file system.
> * e1000 NIC driver.
> * IDE PATA. 
> * ps/2 keyboard. 
> * ps/2 mouse works fine only on qemu.
> * Serial port. 

The desktop features are:

> * Window Server. See: gramland/burgundy/server/
> * Some few clients connected to the window server via unix-sockets.
> * Unix-like commands running in the virtual console.

The libraries are:

> * unix-like library. (rtl)
> * Lib for the window server's clients. (libgws)

## The source code.

You can find the source code on Github in the internet, 
where you can clone the repository, contribute to the project or
download the code. The address is https://github.com/frednora/gramado.

## A description of the directories in the Gramado source code.

There are only two main subdirectories: core/ and desktop/.
core/ is a place for the low level code and
desktop/ is a place for the graphical user interface.

    Gramado Kernel - core/
    Gramado DE     - desktop/

    The next few lines has a brief description of the subdirectories:

 * `core/` - Low level basic components of the system.  
   * `commands` - Unix-like commands and more.
   * `init` - The init process.
   * `libs` - Libraries.
   * `net` - Network stuff.
   * `os` - Main ring0 Components.
     * `boot` - The boot loader.
     * `disk` - The root directory for the boot partition.
     * `kernel` - The Gramado OS kernel.
 * `desktop/` - The window server and it's clients.
   * `apps` - Client applications.
   * `eng` - Graphics engine.
   * `gramland` - Window server.
   * `libs` - Libraries.

## Who are the developers?

The main developer is Fred Nora, a brazilian developer.
Fred Nora is the creator and main maintainer of the project.

## How to Build?

> See the [Gramado OS build instructions](https://github.com/frednora/gramado/blob/master/core/admin/docs/build.md)

## Building and running on vm

```bash
$ make
$ cd core
$ ./run
```

## Clean up the unused files to make a fresh compilation

```bash
$ cd core
$ make clean-all
```

## What are the host machine to build the project?

For now the system has been compiled on Ubuntu operating system,
LTS releases. 

```
    Host machine: Ubuntu 20.04.5 LTS
    Linux 5.4.0-146-generic x86_64
    gcc (Ubuntu) 9.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.34
    NASM version 2.14.02
```

## Can I test the system on a virtual machine?

Yes, you can test the system on a virtual machine.
The system has been tested by Fred Nora on qemu, qemu with kvm and virtualbox.
Now, Fred Nora is testing the system only on qemu and virtualbox.

## Can I test the system on a real machine?

Yes, we can test the system in the real machines. 
This way we can improve the system. 
The older versions of the system were tested for a long period of time 
on a real machine. That machine was a Gigabyte machine 
with an Intel Core 2 Duo processor and a VIA chipset.

## Do we need some feedback from the users and from the developers?

Yes, we need some feedback. 
Please make some comments on Github or send messages to Fred Nora.

## Documentation

The project has a folder for documentation and design notes. 
The folder is core/admin/docs/.

> See the [docs](https://github.com/frednora/gramado/tree/master/core/admin/docs).

The project is looking for some people to create a better documentation, for free, 
as a contribuition to the open source community. To create this new documentation 
we can use the documentation in core/admin/docs/ and the design notes 
found all over the project.

## Author

* **Fred Nora** - [Fred Nora's Twitter account](https://twitter.com/frednora)
* **Fred Nora** - [Fred Nora's Facebook account](https://facebook.com/frednora)

## Contributors

* **Fred Nora** - [Fred Nora's Facebook account](https://facebook.com/frednora)
* **Fred Nora** - [Fred Nora's Facebook account](https://facebook.com/frednora)

## License

Gramado is a Free and Open Source operating system.
The source code uses the BSD license.

## Here are some screenshots of Gramado Operating System.

![Screenshot](https://raw.githubusercontent.com/frednora/screenshots/main/gramado-7.png)
![Screenshot](https://raw.githubusercontent.com/frednora/screenshots/main/gramado-3.png)


# Quotes:
> * Oh boy, there is no fork!
> * Ii.
> * Ww. 
> * The beast hates science and the scientist.

