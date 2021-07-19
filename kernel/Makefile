
# todo:
# The first goal of this makefile is 
# mount the assembly files 
# in the folder kernel/1pump/arch/x86_64/pumpcore/
# Evething starts in the file head_64.asm


# Make variables (CC, etc...)
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


# See:
# https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html

#original: gramado 32bit
#CFLAGS := -m64 \
#	-std=gnu89 \
#	-nodefaultlibs \
#	-nostdinc \
#	-nostdlib \
#	-static \
#	-fgnu89-inline \
#	-ffreestanding \
#	-fno-builtin \
#	-fno-pie \
#	-fleading-underscore \
#	-fno-stack-protector \
#	-s \
#	-Werror=strict-prototypes    


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
USER_INCLUDE   := -I include/uapi/


# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I include/ $(USER_INCLUDE)  


# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -M --print-map:   Print a link map to the standard output.
# LDFLAGS := -m elf_x86_64 -static
LDFLAGS := -m elf_x86_64 -s -x -static  


# ========================
# Config

#test
CONFIG_MAIN=y
# ...

# ========================
# Objects (This is a test)
# We need classes: head | always | optional

# head
objects-y := head_64.o 

# always
objects-$(CONFIG_MAIN) += main.o 

# optional
objects-y += x64init.o \
ctype.o kstdio.o stdlib.o string.o unistd.o runtime.o system.o signal.o \
init.o debug.o info.o \
ports64.o pit.o rtc.o x64.o x64info.o hal.o detect.o \
pci.o pciinfo.o pciscan.o devmgr.o\
console.o tty.o video.o vsync.o screen.o serial.o \
storage.o \
ata.o atadma.o atahdd.o atainit.o atairq.o atapci.o \
i8042.o ps2kbd.o ps2mouse.o keyboard.o mouse.o \
font.o \
fs.o network.o socket.o pipe.o search.o \
disk_r.o disk_w.o \
sys.o \
io.o ws.o \
pixel.o bg.o char.o dtext.o line.o rect.o \
kgws.o kgwm.o vt.o \
desktop.o room.o usession.o logon.o logoff.o userenv.o \
ts.o dispatch.o spawn.o x64cont.o x64fault.o \
sched.o schedi.o \
process.o thread.o threadi.o create.o queue.o mk.o \
memory.o mminfo.o mmpool.o pages.o \
panic.o reboot.o request.o \
sci.o     


PHONY := all
all: kernel-header kernel-content kernel-footer \
link-kernel \
clean    


# The x86 head of the monster.
kernel-header:

	# unit 0, unit 1, unit 3, unit 4, visitor
	$(NASM) kernel/arch/x86_64/pumpcore/unit0/head_64.asm \
	$(KERNEL_INCLUDE) \
	-I kernel/arch/x86_64/pumpcore/unit0/ \
	-I kernel/arch/x86_64/pumpcore/unit1/ \
	-I kernel/arch/x86_64/pumpcore/unit3/ \
	-I kernel/arch/x86_64/pumpcore/unit4/ \
	-I kernel/arch/x86_64/pumpcore/visitor/ \
	-f elf64 -o head_64.o

	# unit 2
	$(CC) -c kernel/arch/x86_64/pumpcore/unit2/sci.c \
	$(KERNEL_INCLUDE) \
	$(CFLAGS) \
	-o sci.o    


kernel-content:

#
# == main ======== 
#
	$(CC) -c init/main.c  $(KERNEL_INCLUDE) $(CFLAGS) -o main.o

#
# == kernel/ ======== 
#

	gcc -c kernel/panic.c    $(KERNEL_INCLUDE) $(CFLAGS) -o panic.o
	gcc -c kernel/reboot.c   $(KERNEL_INCLUDE) $(CFLAGS) -o reboot.o
	gcc -c kernel/request.c  $(KERNEL_INCLUDE) $(CFLAGS) -o request.o


	gcc -c kernel/arch/detect.c  $(KERNEL_INCLUDE) $(CFLAGS) -o detect.o
	gcc -c kernel/arch/hal.c     $(KERNEL_INCLUDE) $(CFLAGS) -o hal.o

	# kernel/arch/x86_64
	gcc -c kernel/arch/x86_64/pit.c      $(KERNEL_INCLUDE) $(CFLAGS) -o pit.o
	gcc -c kernel/arch/x86_64/ports64.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ports64.o
	gcc -c kernel/arch/x86_64/rtc.c      $(KERNEL_INCLUDE) $(CFLAGS) -o rtc.o
	gcc -c kernel/arch/x86_64/x64init.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64init.o
	gcc -c kernel/arch/x86_64/x64.c      $(KERNEL_INCLUDE) $(CFLAGS) -o x64.o
	gcc -c kernel/arch/x86_64/x64info.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64info.o


	# ps
	gcc -c kernel/ps/process.c  $(KERNEL_INCLUDE) $(CFLAGS) -o process.o
	gcc -c kernel/ps/thread.c   $(KERNEL_INCLUDE) $(CFLAGS) -o thread.o
	gcc -c kernel/ps/threadi.c  $(KERNEL_INCLUDE) $(CFLAGS) -o threadi.o
	gcc -c kernel/ps/create.c   $(KERNEL_INCLUDE) $(CFLAGS) -o create.o
	gcc -c kernel/ps/x86_64/x64fault.c      $(KERNEL_INCLUDE) $(CFLAGS) -o x64fault.o
	gcc -c kernel/ps/queue.c   $(KERNEL_INCLUDE) $(CFLAGS) -o queue.o
	gcc -c kernel/ps/mk.c      $(KERNEL_INCLUDE) $(CFLAGS) -o mk.o

	# ps/disp
	gcc -c kernel/ps/disp/ts.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o ts.o  
	gcc -c kernel/ps/disp/dispatch.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o dispatch.o  
	gcc -c kernel/ps/disp/spawn.c     $(KERNEL_INCLUDE)  $(CFLAGS) -o spawn.o  

	gcc -c kernel/ps/disp/x86_64/x64cont.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o x64cont.o  

	gcc -c kernel/ps/sched/sched.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o sched.o  
	gcc -c kernel/ps/sched/schedi.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o schedi.o  


#
# == mm/ ======== 
#

	# 0mem
	gcc -c mm/memory.c  $(KERNEL_INCLUDE) $(CFLAGS) -o memory.o
	gcc -c mm/mminfo.c  $(KERNEL_INCLUDE) $(CFLAGS) -o mminfo.o
	gcc -c mm/mmpool.c  $(KERNEL_INCLUDE) $(CFLAGS) -o mmpool.o
	gcc -c mm/pages.c   $(KERNEL_INCLUDE) $(CFLAGS) -o pages.o

	# == Gramado Core ====
	# Architecture independent layer.

	gcc -c mm/core/info.c     $(KERNEL_INCLUDE) $(CFLAGS) -o info.o
	gcc -c mm/core/init.c     $(KERNEL_INCLUDE) $(CFLAGS) -o init.o
	gcc -c mm/core/runtime.c  $(KERNEL_INCLUDE) $(CFLAGS) -o runtime.o
	gcc -c mm/core/system.c   $(KERNEL_INCLUDE) $(CFLAGS) -o system.o

	# debug
	gcc -c mm/core/debug/debug.c  $(KERNEL_INCLUDE) $(CFLAGS) -o debug.o


	gcc -c mm/sci/net/network/network.c  $(KERNEL_INCLUDE) $(CFLAGS) -o network.o
	gcc -c mm/sci/net/socket/socket.c    $(KERNEL_INCLUDE) $(CFLAGS) -o socket.o

	# 0mem/rtl
	gcc -c mm/rtl/ctype.c   $(KERNEL_INCLUDE) $(CFLAGS) -o ctype.o
	gcc -c mm/rtl/string.c  $(KERNEL_INCLUDE) $(CFLAGS) -o string.o
	gcc -c mm/rtl/stdlib.c  $(KERNEL_INCLUDE) $(CFLAGS) -o stdlib.o
	gcc -c mm/rtl/kstdio.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kstdio.o
	gcc -c mm/rtl/signal.c  $(KERNEL_INCLUDE) $(CFLAGS) -o signal.o
	gcc -c mm/rtl/unistd.c  $(KERNEL_INCLUDE) $(CFLAGS) -o unistd.o


	gcc -c mm/sci/sys/sys.c  $(KERNEL_INCLUDE) $(CFLAGS) -o sys.o


#
# == fs/ ======== 
#

	# fs
	gcc -c fs/fs.c      $(KERNEL_INCLUDE) $(CFLAGS) -o fs.o
	gcc -c fs/pipe.c    $(KERNEL_INCLUDE) $(CFLAGS) -o pipe.o
	gcc -c fs/search.c  $(KERNEL_INCLUDE) $(CFLAGS) -o search.o
	gcc -c fs/sdi/disk_r.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_r.o
	gcc -c fs/sdi/disk_w.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_w.o


	gcc -c fs/io.c  $(KERNEL_INCLUDE) $(CFLAGS) -o io.o
	gcc -c fs/ws.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ws.o

	# fs/bus/pcibus/
	gcc -c fs/bus/pcibus/pci.c     $(KERNEL_INCLUDE) $(CFLAGS) -o pci.o
	gcc -c fs/bus/pcibus/pciinfo.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciinfo.o
	gcc -c fs/bus/pcibus/pciscan.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciscan.o

	# fs/dev/
	gcc -c fs/dev/devmgr.c  $(KERNEL_INCLUDE) $(CFLAGS) -o devmgr.o 
	gcc -c fs/dev/serial.c  $(KERNEL_INCLUDE) $(CFLAGS) -o serial.o

	# fs/dev/blkdev
	gcc -c fs/dev/blkdev/storage.c  $(KERNEL_INCLUDE) $(CFLAGS) -o storage.o 

	# fs/dev/blkdev/ide
	gcc -c fs/dev/blkdev/ide/ata.c      $(KERNEL_INCLUDE) $(CFLAGS) -o ata.o 
	gcc -c fs/dev/blkdev/ide/atadma.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atadma.o 
	gcc -c fs/dev/blkdev/ide/atahdd.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atahdd.o 
	gcc -c fs/dev/blkdev/ide/atainit.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atainit.o 
	gcc -c fs/dev/blkdev/ide/atairq.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atairq.o 
	gcc -c fs/dev/blkdev/ide/atapci.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atapci.o 

	# fs/dev/tty/
	gcc -c fs/dev/tty/tty.c  $(KERNEL_INCLUDE) $(CFLAGS) -o tty.o

	# 2io/dev/graphics
	gcc -c fs/dev/graphics/video.c   $(KERNEL_INCLUDE) $(CFLAGS) -o video.o
	gcc -c fs/dev/graphics/vsync.c   $(KERNEL_INCLUDE) $(CFLAGS) -o vsync.o
	gcc -c fs/dev/graphics/screen.c  $(KERNEL_INCLUDE) $(CFLAGS) -o screen.o

	# 2io/dev/hid
	gcc -c fs/dev/hid/i8042.c     $(KERNEL_INCLUDE) $(CFLAGS) -o i8042.o
	gcc -c fs/dev/hid/ps2kbd.c    $(KERNEL_INCLUDE) $(CFLAGS) -o ps2kbd.o
	gcc -c fs/dev/hid/ps2mouse.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ps2mouse.o
	gcc -c fs/dev/hid/keyboard.c  $(KERNEL_INCLUDE) $(CFLAGS) -o keyboard.o
	gcc -c fs/dev/hid/mouse.c     $(KERNEL_INCLUDE) $(CFLAGS) -o mouse.o

#
# == user ======== 
#

	gcc -c user/kgws.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kgws.o
	gcc -c user/kgwm.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kgwm.o

	gcc -c user/vt.c   $(KERNEL_INCLUDE) $(CFLAGS) -o vt.o

	# ctrl
	gcc -c user/ctrl/console.c  $(KERNEL_INCLUDE) $(CFLAGS) -o console.o 

	# user/model
	gcc -c user/model/font.c  $(KERNEL_INCLUDE) $(CFLAGS) -o font.o


	# user/security
	gcc -c user/security/desktop.c   $(KERNEL_INCLUDE) $(CFLAGS) -o desktop.o
	gcc -c user/security/room.c      $(KERNEL_INCLUDE) $(CFLAGS) -o room.o
	gcc -c user/security/usession.c  $(KERNEL_INCLUDE) $(CFLAGS) -o usession.o
	gcc -c user/security/logoff.c    $(KERNEL_INCLUDE) $(CFLAGS) -o logoff.o
	gcc -c user/security/logon.c     $(KERNEL_INCLUDE) $(CFLAGS) -o logon.o
	gcc -c user/security/userenv.c   $(KERNEL_INCLUDE) $(CFLAGS) -o userenv.o


	# user/view
	gcc -c user/view/bg.c     $(KERNEL_INCLUDE) $(CFLAGS) -o bg.o
	gcc -c user/view/char.c   $(KERNEL_INCLUDE) $(CFLAGS) -o char.o
	gcc -c user/view/dtext.c  $(KERNEL_INCLUDE) $(CFLAGS) -o dtext.o
	gcc -c user/view/line.c   $(KERNEL_INCLUDE) $(CFLAGS) -o line.o
	gcc -c user/view/pixel.c  $(KERNEL_INCLUDE) $(CFLAGS) -o pixel.o
	gcc -c user/view/rect.c   $(KERNEL_INCLUDE) $(CFLAGS) -o rect.o
    # ...

kernel-footer:
	# Nothing for now.

link-kernel:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	$(LD) $(LDFLAGS) -T link.ld -o KERNEL.BIN $(objects-y)  

clean:
	rm -rf *.o   

