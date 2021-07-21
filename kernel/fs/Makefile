
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



OBJS = fs.o \
pipe.o \
search.o \
disk_r.o disk_w.o \
io.o \
ws.o \
pci.o pciinfo.o pciscan.o \
devmgr.o \
serial.o \
storage.o \
ata.o atadma.o atahdd.o atainit.o atairq.o atapci.o \
tty.o \
video.o vsync.o screen.o \
i8042.o ps2kbd.o ps2mouse.o keyboard.o mouse.o    



all:

	# fs
	$(CC) -c fs.c      $(KERNEL_INCLUDE) $(CFLAGS) -o fs.o
	$(CC) -c pipe.c    $(KERNEL_INCLUDE) $(CFLAGS) -o pipe.o
	$(CC) -c search.c  $(KERNEL_INCLUDE) $(CFLAGS) -o search.o
	$(CC) -c sdi/disk_r.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_r.o
	$(CC) -c sdi/disk_w.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_w.o

	$(CC) -c io.c  $(KERNEL_INCLUDE) $(CFLAGS) -o io.o
	$(CC) -c ws.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ws.o

	$(CC) -c bus/pcibus/pci.c     $(KERNEL_INCLUDE) $(CFLAGS) -o pci.o
	$(CC) -c bus/pcibus/pciinfo.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciinfo.o
	$(CC) -c bus/pcibus/pciscan.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciscan.o

	$(CC) -c dev/devmgr.c  $(KERNEL_INCLUDE) $(CFLAGS) -o devmgr.o 
	$(CC) -c dev/serial.c  $(KERNEL_INCLUDE) $(CFLAGS) -o serial.o

	$(CC) -c dev/blkdev/storage.c  $(KERNEL_INCLUDE) $(CFLAGS) -o storage.o 

	$(CC) -c dev/blkdev/ide/ata.c      $(KERNEL_INCLUDE) $(CFLAGS) -o ata.o 
	$(CC) -c dev/blkdev/ide/atadma.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atadma.o 
	$(CC) -c dev/blkdev/ide/atahdd.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atahdd.o 
	$(CC) -c dev/blkdev/ide/atainit.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atainit.o 
	$(CC) -c dev/blkdev/ide/atairq.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atairq.o 
	$(CC) -c dev/blkdev/ide/atapci.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atapci.o 


	$(CC) -c dev/tty/tty.c  $(KERNEL_INCLUDE) $(CFLAGS) -o tty.o


	$(CC) -c dev/graphics/video.c   $(KERNEL_INCLUDE) $(CFLAGS) -o video.o
	$(CC) -c dev/graphics/vsync.c   $(KERNEL_INCLUDE) $(CFLAGS) -o vsync.o
	$(CC) -c dev/graphics/screen.c  $(KERNEL_INCLUDE) $(CFLAGS) -o screen.o


	$(CC) -c dev/hid/i8042.c     $(KERNEL_INCLUDE) $(CFLAGS) -o i8042.o
	$(CC) -c dev/hid/ps2kbd.c    $(KERNEL_INCLUDE) $(CFLAGS) -o ps2kbd.o
	$(CC) -c dev/hid/ps2mouse.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ps2mouse.o
	$(CC) -c dev/hid/keyboard.c  $(KERNEL_INCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c dev/hid/mouse.c     $(KERNEL_INCLUDE) $(CFLAGS) -o mouse.o


#link

	$(LD) -r -o archive_fs.o $(OBJS)


# todo: vamos ligar tudo e enviar somente a biblioteca.
	#cp *.o ../
	cp archive_fs.o ../
	rm *.o













