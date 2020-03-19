
 uefi support
 
https://wiki.osdev.org/UEFI
https://wiki.osdev.org/UEFI_Bare_Bones 
 
 
Development environment:

Legacy bootloaders can be developed in any environment that can generate flat binary images: 
NASM, GCC, etc. UEFI applications can be developed in any language that can be compiled and linked 
into a PE executable file and supports the calling convention used to access functions established 
in memory by the UEFI firmware. In practice this means one of two development environments: 
Intel's TianoCore EDK2 or GNU-EFI.

TianoCore is a large, complex environment with its own build system. It can be configured to use GCC,
MinGW, Microsoft Visual C++, etc. as a cross-compiler. Not only can it be used to compile UEFI applications,
but it can also be used to compile UEFI firmware to be flashed to a BIOS ROM.

GNU-EFI is a set of libraries and headers for compiling UEFI applications with a system's native GCC.
It can't be used to compile UEFI firmware. Since it's just a couple of libraries against which a 
UEFI application can be linked, it is much easier to use than TianoCore.


;;============
A good starting point is writing a UEFI application that uses the System Table to fetch a memory map, and 
uses the "File" protocol to read files from FAT-formatted disks. The next step might be to use the 
System Table to locate ACPI tables.



#importante
Compilar as bibliotecas do gnuefi usando o comando make ARCH=ia32 ... NÃO usar apenas make.
precisa dos objetos em /obj