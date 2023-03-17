
# dev/
# Compile all the files and create ar_dev.o

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
OBJS = \
ata.o atadma.o atahdd.o atainfo.o atairq.o atapci.o \
disk_r.o disk_w.o storage.o \
bldisp.o \
xpixel.o line.o rect.o bitblt.o bg.o font.o char.o text.o graphics.o kgwm.o \
console.o vt.o \
i8042.o kbdmap.o ps2kbd.o ps2mouse.o keyboard.o mouse.o \
serial.o \
tty.o \
e1000.o \
devmgr.o io.o grinput.o \
pci.o pciinfo.o pciscan.o     

all:

# ata
	$(CC) -c blkdev/ata/ata.c     $(KERNEL_INCLUDE) $(CFLAGS) -o ata.o 
	$(CC) -c blkdev/ata/atadma.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atadma.o 
	$(CC) -c blkdev/ata/atahdd.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atahdd.o 
	$(CC) -c blkdev/ata/atainfo.c $(KERNEL_INCLUDE) $(CFLAGS) -o atainfo.o 
	$(CC) -c blkdev/ata/atairq.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atairq.o 
	$(CC) -c blkdev/ata/atapci.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atapci.o 

# storage
	$(CC) -c blkdev/disk_r.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_r.o
	$(CC) -c blkdev/disk_w.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_w.o
	$(CC) -c blkdev/storage.c $(KERNEL_INCLUDE) $(CFLAGS) -o storage.o 


# bl display device
	$(CC) -c chardev/display/bldisp/bldisp.c  $(KERNEL_INCLUDE) $(CFLAGS) -o bldisp.o
# graphics
	$(CC) -c chardev/display/xpixel.c   $(KERNEL_INCLUDE) $(CFLAGS) -o xpixel.o
	$(CC) -c chardev/display/line.c     $(KERNEL_INCLUDE) $(CFLAGS) -o line.o
	$(CC) -c chardev/display/rect.c     $(KERNEL_INCLUDE) $(CFLAGS) -o rect.o
	$(CC) -c chardev/display/bitblt.c   $(KERNEL_INCLUDE) $(CFLAGS) -o bitblt.o
	$(CC) -c chardev/display/font.c     $(KERNEL_INCLUDE) $(CFLAGS) -o font.o
	$(CC) -c chardev/display/char.c     $(KERNEL_INCLUDE) $(CFLAGS) -o char.o
	$(CC) -c chardev/display/text.c     $(KERNEL_INCLUDE) $(CFLAGS) -o text.o
	$(CC) -c chardev/display/bg.c       $(KERNEL_INCLUDE) $(CFLAGS) -o bg.o
	$(CC) -c chardev/display/graphics.c $(KERNEL_INCLUDE) $(CFLAGS) -o graphics.o
	$(CC) -c chardev/display/kgwm.c     $(KERNEL_INCLUDE) $(CFLAGS) -o kgwm.o
# kbd
	$(CC) -c chardev/kbd/kbdmap.c   $(KERNEL_INCLUDE) $(CFLAGS) -o kbdmap.o
	$(CC) -c chardev/kbd/keyboard.c $(KERNEL_INCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c chardev/kbd/ps2kbd.c   $(KERNEL_INCLUDE) $(CFLAGS) -o ps2kbd.o
# mouse
	$(CC) -c chardev/mouse/mouse.c    $(KERNEL_INCLUDE) $(CFLAGS) -o mouse.o
	$(CC) -c chardev/mouse/ps2mouse.c $(KERNEL_INCLUDE) $(CFLAGS) -o ps2mouse.o
# serial
	$(CC) -c chardev/serial/serial.c  $(KERNEL_INCLUDE) $(CFLAGS) -o serial.o
# tty
	$(CC) -c chardev/tty/tty.c      $(KERNEL_INCLUDE) $(CFLAGS) -o tty.o
	$(CC) -c chardev/tty/console.c  $(KERNEL_INCLUDE) $(CFLAGS) -o console.o 
	$(CC) -c chardev/tty/vt.c       $(KERNEL_INCLUDE) $(CFLAGS) -o vt.o
# ps2
	$(CC) -c chardev/i8042.c   $(KERNEL_INCLUDE) $(CFLAGS) -o i8042.o


# e1000
	$(CC) -c netdev/e1000/e1000.c  $(KERNEL_INCLUDE) $(CFLAGS) -o e1000.o 


# i/o
	$(CC) -c grinput.c  $(KERNEL_INCLUDE) $(CFLAGS) -o grinput.o
	$(CC) -c devmgr.c   $(KERNEL_INCLUDE) $(CFLAGS) -o devmgr.o 
	$(CC) -c io.c       $(KERNEL_INCLUDE) $(CFLAGS) -o io.o
# pci
	$(CC) -c pci.c      $(KERNEL_INCLUDE) $(CFLAGS) -o pci.o
	$(CC) -c pciinfo.c  $(KERNEL_INCLUDE) $(CFLAGS) -o pciinfo.o
	$(CC) -c pciscan.c  $(KERNEL_INCLUDE) $(CFLAGS) -o pciscan.o


# link
	$(LD) -r -o ar_dev.o $(OBJS)
	cp ar_dev.o ../
	rm *.o
	
clean:
	rm *.o    

