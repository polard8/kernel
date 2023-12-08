# The kernel for Gramado OS.

```
    gramadoOS
```

## Here are some screenshots of Gramado Operating System.

![Screenshot](https://raw.githubusercontent.com/gijinka/screenshots/main/gramado-8.png)
![Screenshot](https://raw.githubusercontent.com/gijinka/screenshots/main/gramado-3.png)

## What is Gramado Operating System?

GramadoOS is a graphical operating system for x86_64 computers.

## What is the category it belongs to? 

Gramado is a hobby operating system, not a commercial operating system, 
because it is a small system and has only some few features, 
not all the features needed by a commercial operating system.

## Kernel features.

> * hw - cpu: Intel and AMD. 64bit only.
> * hw - mm: Paging. Chunck of 2MB, using 4KB pages.
> * hw - blk device: IDE PATA.
> * hw - char device: ps/2 keyboard. 
> * hw - char device: ps/2 mouse works fine only on qemu.
> * hw - char device: Serial port. (COM). Used for debug. 
> * hw - network device: e1000 Intel NIC. Works on Oracle virtual box.

> * sw - Processes: Process structure and Thread structure.
> * sw - Scheduler: Round robin. (Threads only).
> * sw - Syscalls using software interrups. (Traps).
> * sw - IPC: sockets.
> * sw - IPC: System messages using a queue in the thread structure. 
> * sw - tty: It has 4 ring 0 kernel virtual consoles in fullscreen raw mode. 
> * sw - tty: General use ttys and ptys for ring3 virtual terminals. 
> * sw - fs: FAT16 file system for boot partition. No system partition yet.
> * sw - posix libc: Ring0 implementation of libc functions called by the ring3 libraries.
> * sw - network: Small support for sockets.
> * sw - network: Small ring0 implementation of protocol stack. (ETHERNET, ARP, IP, UDP, TCP and DHCP).
> * sw - display: Bootloader display device. VESA.
> * sw - user: Very small implementation of user structure.
> * sw - APIs: 
> * sw - One loadable ring0 module, using static address.

## Userland features.

> * Display Server. 
> * Unix-like commands running in the virtual console.
> * Some few clients connected to the display server via unix-sockets.
> * Ring3 processes can access the i/o ports via syscall. (For ring3 drivers only).


## userland system programs.

> * The network server.

## The source code.

You can find the source code on Github in the internet, 
where you can clone the repository, contribute to the project or
download the code. The address is https://github.com/gramado/kernel.
We ned to import some dependencies to get the posix commands, the display server 
and the client-side GUI applications.

## A description of the directories in the Gramado source code.

    The next few lines has a brief description of the subdirectories:

```
 ... #todo
```

## Who are the developers?

The main developer is Fred Nora, a brazilian developer.
Fred Nora is the creator and main maintainer of the project.
Contributions are welcome.

## Building and running on vm

```bash
$ make
$ ./run
```

## Clean up the unused files to make a fresh compilation

```bash
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
```
    Host machine: Ubuntu 22.04.2 LTS
    Linux 5.15.0-78-generic x86_64
    gcc (Ubuntu) 11.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```
```
    Host machine: Ubuntu 22.04.2 LTS
    Linux 5.15.0-83-generic x86_64
    gcc (Ubuntu) 11.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```
```
    Host machine: Ubuntu 22.04.2 LTS
    Linux 5.15.0-84-generic x86_64
    gcc (Ubuntu) 11.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```
```
    Host machine: Ubuntu 22.04.2 LTS
    Linux 5.15.0-87-generic x86_64
    gcc (Ubuntu) 11.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```
```
    Host machine: Ubuntu 22.04.2 LTS
    Linux 5.15.0-89-generic x86_64
    gcc (Ubuntu) 11.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
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

## Author

* **Fred Nora** - [Fred Nora's Twitter account](https://twitter.com/frednora)
* **Fred Nora** - [Fred Nora's Facebook account](https://facebook.com/frednora)

## Contributors

* **Fred Nora** - [Fred Nora's Facebook account](https://facebook.com/frednora)
* **Fred Nora 2** - [Fred Nora's Facebook account](https://facebook.com/frednora)


## How to Build?

> See the [Gramado OS build instructions](https://github.com/gramado/kernel/blob/main/docs/2-developer/build.md)


# Warning

You're reaching the boring area of this document!


## Documentation

The project has a folder for documentation and design notes. 
The folder is docs/.

> See the [docs](https://github.com/gramado/kernel/tree/main/docs).

The project is looking for some people to create a better documentation, for free, 
as a contribuition to the open source community. To create this new documentation 
we can use the documentation in docs/ and the design notes 
found all over the project.

## License

Gramado is a Free and Open Source operating system.
The source code uses the BSD license.

## Quotes:

```
  * Transfiguration
  * "Close to the borders and beyond." (Grace).
```
