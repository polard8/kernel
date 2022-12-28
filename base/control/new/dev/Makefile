
# dev/
# Compile all the files and create archive_dev.o

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
pci.o pciinfo.o pciscan.o \
devmgr.o \
serial.o \
storage.o \
ata.o atadma.o atahdd.o atainit.o atairq.o atapci.o \
video.o vsync.o screen.o \
xpixel.o line.o rect.o bg.o \
font.o char.o text.o \
graphics.o \
e1000.o \
i8042.o kbdmap.o ps2kbd.o ps2mouse.o keyboard.o mouse.o \
console.o vt.o kgwm.o    

all:

	$(CC) -c disk_r.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_r.o
	$(CC) -c disk_w.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_w.o
	$(CC) -c storage.c $(KERNEL_INCLUDE) $(CFLAGS) -o storage.o 
	$(CC) -c io.c      $(KERNEL_INCLUDE) $(CFLAGS) -o io.o
	$(CC) -c devmgr.c  $(KERNEL_INCLUDE) $(CFLAGS) -o devmgr.o 
	$(CC) -c i8042.c   $(KERNEL_INCLUDE) $(CFLAGS) -o i8042.o

# ata
	$(CC) -c ata/ata.c     $(KERNEL_INCLUDE) $(CFLAGS) -o ata.o 
	$(CC) -c ata/atadma.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atadma.o 
	$(CC) -c ata/atahdd.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atahdd.o 
	$(CC) -c ata/atainit.c $(KERNEL_INCLUDE) $(CFLAGS) -o atainit.o 
	$(CC) -c ata/atairq.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atairq.o 
	$(CC) -c ata/atapci.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atapci.o 

# e1000
	$(CC) -c e1000/e1000.c  $(KERNEL_INCLUDE) $(CFLAGS) -o e1000.o 

# fb/hw
	$(CC) -c fb/hw/video.c  $(KERNEL_INCLUDE) $(CFLAGS) -o video.o
	$(CC) -c fb/hw/vsync.c  $(KERNEL_INCLUDE) $(CFLAGS) -o vsync.o
	$(CC) -c fb/hw/screen.c $(KERNEL_INCLUDE) $(CFLAGS) -o screen.o

	$(CC) -c fb/gr/xpixel.c   $(KERNEL_INCLUDE) $(CFLAGS) -o xpixel.o
	$(CC) -c fb/gr/line.c     $(KERNEL_INCLUDE) $(CFLAGS) -o line.o
	$(CC) -c fb/gr/rect.c     $(KERNEL_INCLUDE) $(CFLAGS) -o rect.o
	$(CC) -c fb/gr/font.c     $(KERNEL_INCLUDE) $(CFLAGS) -o font.o
	$(CC) -c fb/gr/char.c     $(KERNEL_INCLUDE) $(CFLAGS) -o char.o
	$(CC) -c fb/gr/text.c     $(KERNEL_INCLUDE) $(CFLAGS) -o text.o
	$(CC) -c fb/gr/bg.c       $(KERNEL_INCLUDE) $(CFLAGS) -o bg.o
	$(CC) -c fb/gr/graphics.c $(KERNEL_INCLUDE) $(CFLAGS) -o graphics.o

# kbd
	$(CC) -c kbd/kbdmap.c   $(KERNEL_INCLUDE) $(CFLAGS) -o kbdmap.o
	$(CC) -c kbd/keyboard.c $(KERNEL_INCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c kbd/ps2kbd.c   $(KERNEL_INCLUDE) $(CFLAGS) -o ps2kbd.o

# mouse
	$(CC) -c mouse/mouse.c    $(KERNEL_INCLUDE) $(CFLAGS) -o mouse.o
	$(CC) -c mouse/ps2mouse.c $(KERNEL_INCLUDE) $(CFLAGS) -o ps2mouse.o

# pci
	$(CC) -c pci/pci.c     $(KERNEL_INCLUDE) $(CFLAGS) -o pci.o
	$(CC) -c pci/pciinfo.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciinfo.o
	$(CC) -c pci/pciscan.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciscan.o

# serial
	$(CC) -c serial/serial.c  $(KERNEL_INCLUDE) $(CFLAGS) -o serial.o

# tty
	$(CC) -c tty/tty.c      $(KERNEL_INCLUDE) $(CFLAGS) -o tty.o
	$(CC) -c tty/console.c  $(KERNEL_INCLUDE) $(CFLAGS) -o console.o 
	$(CC) -c tty/vt.c       $(KERNEL_INCLUDE) $(CFLAGS) -o vt.o

	$(CC) -c tty/kgwm.c     $(KERNEL_INCLUDE) $(CFLAGS) -o kgwm.o

# link
	$(LD) -r -o archive_dev.o $(OBJS)
	cp archive_dev.o ../
	rm *.o
	
	
