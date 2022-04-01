
AS	= as
LD	= ld
CC	= gcc
AR	= ar
MAKE	= make
NASM	= nasm
OBJCOPY	= objcopy
OBJDUMP	= objdump
LEX	= flex
YACC	= bison
PERL	= perl
PYTHON	= python
PYTHON2	= python2
PYTHON3	= python3
RUBY	= ruby


# test: gramado 64bit
# See: https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html
CFLAGS := \
	-Wall \
	-Wundef \
	-Wmissing-prototypes \
	-Wno-uninitialized \
	-Wno-format-security \
	-Wno-trigraphs \
	-Werror=strict-prototypes \
	-Werror=implicit-function-declaration \
	-Werror=implicit-int \
	-Werror=return-type \
	-std=gnu89 \
	-m64 \
	-s \
	-static \
	-fcommon \
	-fgnu89-inline \
	-finline-functions \
	-fshort-wchar \
	-ffreestanding \
	-fleading-underscore \
	-fstrict-overflow \
	-nostdlib \
	-nodefaultlibs \
	-nostdinc \
	-fno-builtin \
	-fno-stack-protector \
	-fno-strict-aliasing \
	-fno-PIE \
	-fno-pie \
	-fno-omit-frame-pointer \
	-fno-optimize-sibling-calls    


# Exported files. Kernel api;
# Used by the kernel modules and user space applications.
USER_INCLUDE   := -I ../include/uapi/


# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I ../include/ $(USER_INCLUDE)  


# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -M --print-map:   Print a link map to the standard output.
# LDFLAGS := -m elf_x86_64 -static
LDFLAGS := -m elf_x86_64 -s -x -static  


# Everything is a file.
OBJS = tty.o \
io.o \
disk_r.o disk_w.o \
ws.o \
pci.o pciinfo.o pciscan.o \
devmgr.o \
serial.o \
storage.o \
ata.o atadma.o atahdd.o atainit.o atairq.o atapci.o \
video.o vsync.o screen.o \
xpixel.o line.o rect.o bg.o \
i8042.o ps2kbd.o ps2mouse.o keyboard.o mouse.o    


all:

	$(CC) -c storage/storage.c  $(KERNEL_INCLUDE) $(CFLAGS) -o storage.o 

	$(CC) -c storage/ata/ata.c      $(KERNEL_INCLUDE) $(CFLAGS) -o ata.o 
	$(CC) -c storage/ata/atadma.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atadma.o 
	$(CC) -c storage/ata/atahdd.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atahdd.o 
	$(CC) -c storage/ata/atainit.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atainit.o 
	$(CC) -c storage/ata/atairq.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atairq.o 
	$(CC) -c storage/ata/atapci.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atapci.o 
	
	$(CC) -c storage/disk_r.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_r.o
	$(CC) -c storage/disk_w.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_w.o

	$(CC) -c tty/tty.c  $(KERNEL_INCLUDE) $(CFLAGS) -o tty.o

	$(CC) -c io.c  $(KERNEL_INCLUDE) $(CFLAGS) -o io.o
	$(CC) -c ws.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ws.o

	$(CC) -c pcibus/pci.c     $(KERNEL_INCLUDE) $(CFLAGS) -o pci.o
	$(CC) -c pcibus/pciinfo.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciinfo.o
	$(CC) -c pcibus/pciscan.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciscan.o

	$(CC) -c devmgr.c  $(KERNEL_INCLUDE) $(CFLAGS) -o devmgr.o 


	$(CC) -c serial/serial.c  $(KERNEL_INCLUDE) $(CFLAGS) -o serial.o

	$(CC) -c video/video.c   $(KERNEL_INCLUDE) $(CFLAGS) -o video.o
	$(CC) -c video/vsync.c   $(KERNEL_INCLUDE) $(CFLAGS) -o vsync.o
	$(CC) -c video/screen.c  $(KERNEL_INCLUDE) $(CFLAGS) -o screen.o


	$(CC) -c input/i8042/i8042.c     $(KERNEL_INCLUDE) $(CFLAGS) -o i8042.o
	$(CC) -c input/i8042/keyboard.c  $(KERNEL_INCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c input/i8042/ps2kbd.c    $(KERNEL_INCLUDE) $(CFLAGS) -o ps2kbd.o
	$(CC) -c input/i8042/mouse.c     $(KERNEL_INCLUDE) $(CFLAGS) -o mouse.o
	$(CC) -c input/i8042/ps2mouse.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ps2mouse.o


	$(CC) -c video/fbdev/xpixel.c  $(KERNEL_INCLUDE) $(CFLAGS) -o xpixel.o

	$(CC) -c video/fbdev/line.c   $(KERNEL_INCLUDE) $(CFLAGS) -o line.o
	$(CC) -c video/fbdev/rect.c   $(KERNEL_INCLUDE) $(CFLAGS) -o rect.o
	$(CC) -c video/fbdev/bg.c     $(KERNEL_INCLUDE) $(CFLAGS) -o bg.o


#link

	$(LD) -r -o archive_drivers.o $(OBJS)


# todo: vamos ligar tudo e enviar somente a biblioteca.
	#cp *.o ../
	cp archive_drivers.o ../
	rm *.o













