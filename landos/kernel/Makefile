# Compiling KERNEL.BIN
# 2020 - Fred Nora.

ARCH ?= x86
#ARCH ?= x86_64

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

# ===================
# x86
ifeq ($(ARCH),x86)

CFLAGS = -m32 \
	-std=gnu89 \
	-nodefaultlibs \
	-nostdinc \
	-nostdlib \
	-static \
	-fgnu89-inline \
	-ffreestanding \
	-fno-builtin \
	-fno-pie \
	-fleading-underscore \
	-fno-stack-protector \
	-s \
	-Werror=strict-prototypes    

LDFLAGS = -m elf_i386 

endif

# ===================
# x86_64
ifeq ($(ARCH),x86_64)

CFLAGS = -m64 \
	-std=gnu89 \
	-nodefaultlibs \
	-nostdinc \
	-nostdlib \
	-static \
	-fgnu89-inline \
	-ffreestanding \
	-fno-builtin \
	-fno-pie \
	-no-pie \
	-fleading-underscore \
	-fno-stack-protector \
	-s \
	-Werror=strict-prototypes    

#LDFLAGS = -m elf_i386    

endif


KINCLUDE = -I include/
#KINCLUDE = -I 0mem/include/


#
# Objects
#

ifeq ($(ARCH),x86)

	ENTRY_OBJECTS := head_32.o main.o x86init.o 

	EXECVE_OBJECTS := socket.o ctype.o  kstdio.o stdlib.o string.o unistd.o \
	devmgr.o \
	sci.o \
	debug.o storage.o install.o object.o runtime.o \
	abort.o info.o io.o ws.o modules.o signal.o sm.o \
	init.o system.o \
	execve.o 
	
	HAL_OBJECTS := portsx86.o x86.o x86info.o cpuamd.o detect.o \
	hal.o 

	KDRIVERS_OBJECTS := ahci.o \
	ata.o atadma.o atainit.o atairq.o atapci.o atahdd.o \
	channel.o network.o e1000.o \
	pci.o pciinfo.o pciscan.o \
	console.o tty.o tty_io.o pty.o vt.o\
	usb.o \
	video.o vsync.o screen.o r_render.o dialog.o \
	i8042.o keyboard.o mouse.o ps2kbd.o ps2mouse.o \
	apic.o pic.o rtc.o serial.o pit.o  

	KSERVERS_OBJECTS := cf.o format.o pipe.o fs.o disk_r.o disk_w.o search.o \
	bg.o bmp.o button.o char.o createw.o dtext.o font.o pbar.o \
	line.o menu.o mbar.o pixel.o rect.o sbar.o tbar.o wm.o \
	logoff.o logon.o \
	input.o output.o terminal.o \
	desktop.o room.o userenv.o usession.o \
	kgwm.o kgws.o \
	vfs.o 

	MK_OBJECTS := x86cont.o x86fault.o x86start.o \
	dispatch.o pheap.o process.o clone.o queue.o spawn.o \
	tasks.o theap.o thread.o threadi.o ts.o tstack.o \
	callout.o callfar.o ipc.o ipccore.o sem.o \
	memory.o mminfo.o mmpool.o pages.o \
	preempt.o priority.o sched.o schedi.o \
	create.o \
	mk.o 

	REQUEST_OBJECTS := request.o 

	PANIC_OBJECTS   := panic.o 

	REBOOT_OBJECTS  := reboot.o 

	SYS_OBJECTS     := sys.o pump.o sifs.o siws.o sins.o   


#
# == Objects ========
#

	# See the DOOM makefile.
	# All the objects has a prefix to keep the class together.
	# We can do the same for some classes here.

	OBJECTS := $(ENTRY_OBJECTS) \
	$(EXECVE_OBJECTS) \
	$(HAL_OBJECTS) \
	$(KDRIVERS_OBJECTS) \
	$(KSERVERS_OBJECTS) \
	$(MK_OBJECTS) \
	$(REQUEST_OBJECTS) \
	$(PANIC_OBJECTS) \
	$(REBOOT_OBJECTS) \
	$(SYS_OBJECTS)    
	
	
endif


ifeq ($(ARCH),arm)
	# NOTHING FOR NOW
endif


all: kernel-head all-c link-kernel clean

kernel-head:

# The x86 head of the monster.

	$(NASM)  1pump/arch/x86/pumpcore/head_32.asm \
	$(KINCLUDE) \
	-I 1pump/arch/x86/pumpcore/ \
	-f elf -o head_32.o

# all c files.
# order: 0mem, 1pump, 2io and user.

all-c:

#
# == main ======== 
#

	$(CC) -c main.c  $(KINCLUDE) $(CFLAGS) -o main.o


#
# == 0mem ======== 
#

	# main (Architechture independent)
	# It's the higher level of the init sybsystem.
	$(CC) -c 0mem/panic.c    $(KINCLUDE) $(CFLAGS) -o panic.o
	$(CC) -c 0mem/reboot.c   $(KINCLUDE) $(CFLAGS) -o reboot.o
	$(CC) -c 0mem/request.c  $(KINCLUDE) $(CFLAGS) -o request.o

	# == Gramado Core ====
	# Architecture independent layer.

	$(CC) -c 0mem/core/abort.c    $(KINCLUDE) $(CFLAGS) -o abort.o
	$(CC) -c 0mem/core/info.c     $(KINCLUDE) $(CFLAGS) -o info.o
	$(CC) -c 0mem/core/init.c     $(KINCLUDE) $(CFLAGS) -o init.o
	$(CC) -c 0mem/core/install.c  $(KINCLUDE) $(CFLAGS) -o install.o
	$(CC) -c 0mem/core/modules.c  $(KINCLUDE) $(CFLAGS) -o modules.o
	$(CC) -c 0mem/core/runtime.c  $(KINCLUDE) $(CFLAGS) -o runtime.o
	$(CC) -c 0mem/core/sm.c       $(KINCLUDE) $(CFLAGS) -o sm.o
	$(CC) -c 0mem/core/system.c   $(KINCLUDE) $(CFLAGS) -o system.o

	# debug
	$(CC) -c 0mem/core/debug/debug.c  $(KINCLUDE) $(CFLAGS) -o debug.o

	# ob
	$(CC) -c 0mem/core/ob/object.c    $(KINCLUDE) $(CFLAGS) -o object.o


	# ps
	$(CC) -c  0mem/core/ps/pheap.c     $(KINCLUDE)  $(CFLAGS) -o pheap.o
	$(CC) -c  0mem/core/ps/process.c   $(KINCLUDE)  $(CFLAGS) -o process.o
	$(CC) -c  0mem/core/ps/clone.c     $(KINCLUDE)  $(CFLAGS) -o clone.o
	$(CC) -c  0mem/core/ps/queue.c     $(KINCLUDE)  $(CFLAGS) -o queue.o
	$(CC) -c  0mem/core/ps/tasks.c     $(KINCLUDE)  $(CFLAGS) -o tasks.o
	$(CC) -c  0mem/core/ps/theap.c     $(KINCLUDE)  $(CFLAGS) -o theap.o
	$(CC) -c  0mem/core/ps/thread.c    $(KINCLUDE)  $(CFLAGS) -o thread.o
	$(CC) -c  0mem/core/ps/threadi.c   $(KINCLUDE)  $(CFLAGS) -o threadi.o
	$(CC) -c  0mem/core/ps/tstack.c    $(KINCLUDE)  $(CFLAGS) -o tstack.o
	$(CC) -c  0mem/core/ps/execve.c    $(KINCLUDE)  $(CFLAGS) -o execve.o
	$(CC) -c  0mem/core/ps/create.c    $(KINCLUDE)  $(CFLAGS) -o create.o
	$(CC) -c  0mem/core/ps/mk.c        $(KINCLUDE)  $(CFLAGS) -o mk.o   

	# ps/disp
	$(CC) -c 0mem/core/ps/disp/dispatch.c      $(KINCLUDE)  $(CFLAGS) -o dispatch.o
	$(CC) -c 0mem/core/ps/disp/ts.c            $(KINCLUDE)  $(CFLAGS) -o ts.o
	$(CC) -c 0mem/core/ps/disp/spawn.c         $(KINCLUDE)  $(CFLAGS) -o spawn.o
	$(CC) -c 0mem/core/ps/disp/x86/x86cont.c   $(KINCLUDE)  $(CFLAGS) -o x86cont.o
	$(CC) -c 0mem/core/ps/disp/x86/x86start.c  $(KINCLUDE)  $(CFLAGS) -o x86start.o

	# ps/ipc
	$(CC) -c  0mem/core/ps/ipc/callfar.c  $(KINCLUDE)  $(CFLAGS) -o callfar.o
	$(CC) -c  0mem/core/ps/ipc/callout.c  $(KINCLUDE)  $(CFLAGS) -o callout.o
	$(CC) -c  0mem/core/ps/ipc/ipc.c      $(KINCLUDE)  $(CFLAGS) -o ipc.o
	$(CC) -c  0mem/core/ps/ipc/ipccore.c  $(KINCLUDE)  $(CFLAGS) -o ipccore.o
	$(CC) -c  0mem/core/ps/ipc/sem.c      $(KINCLUDE)  $(CFLAGS) -o sem.o

	# ps/sched
	$(CC) -c  0mem/core/ps/sched/preempt.c   $(KINCLUDE) $(CFLAGS) -o preempt.o
	$(CC) -c  0mem/core/ps/sched/priority.c  $(KINCLUDE) $(CFLAGS) -o priority.o
	$(CC) -c  0mem/core/ps/sched/sched.c     $(KINCLUDE) $(CFLAGS) -o sched.o
	$(CC) -c  0mem/core/ps/sched/schedi.c    $(KINCLUDE) $(CFLAGS) -o schedi.o

	# ps/x86
	$(CC) -c 0mem/core/ps/x86/x86fault.c  $(KINCLUDE)  $(CFLAGS) -o x86fault.o


	# 0mem/mm
	$(CC) -c 0mem/mm/memory.c  $(KINCLUDE)  $(CFLAGS) -o memory.o
	$(CC) -c 0mem/mm/mminfo.c  $(KINCLUDE)  $(CFLAGS) -o mminfo.o
	$(CC) -c 0mem/mm/mmpool.c  $(KINCLUDE)  $(CFLAGS) -o mmpool.o
	$(CC) -c 0mem/mm/pages.c   $(KINCLUDE)  $(CFLAGS) -o pages.o

	# 0mem/rtl
	$(CC) -c 0mem/rtl/ctype.c   $(KINCLUDE) $(CFLAGS) -o ctype.o
	$(CC) -c 0mem/rtl/kstdio.c  $(KINCLUDE) $(CFLAGS) -o kstdio.o
	$(CC) -c 0mem/rtl/signal.c  $(KINCLUDE) $(CFLAGS) -o signal.o
	$(CC) -c 0mem/rtl/stdlib.c  $(KINCLUDE) $(CFLAGS) -o stdlib.o
	$(CC) -c 0mem/rtl/string.c  $(KINCLUDE) $(CFLAGS) -o string.o
	$(CC) -c 0mem/rtl/unistd.c  $(KINCLUDE) $(CFLAGS) -o unistd.o

	# fs/sci/fs
	$(CC) -c 0mem/sci/fs/cf.c      $(KINCLUDE) $(CFLAGS) -o cf.o
	$(CC) -c 0mem/sci/fs/format.c  $(KINCLUDE) $(CFLAGS) -o format.o
	$(CC) -c 0mem/sci/fs/fs.c      $(KINCLUDE) $(CFLAGS) -o fs.o
	$(CC) -c 0mem/sci/fs/pipe.c    $(KINCLUDE) $(CFLAGS) -o pipe.o
	$(CC) -c 0mem/sci/fs/search.c  $(KINCLUDE) $(CFLAGS) -o search.o

	# 0mem/sci/fs/sdi
	$(CC) -c 0mem/sci/fs/sdi/disk_r.c  $(KINCLUDE) $(CFLAGS) -o disk_r.o
	$(CC) -c 0mem/sci/fs/sdi/disk_w.c  $(KINCLUDE) $(CFLAGS) -o disk_w.o

	# 0mem/sci/fs/vfs
	$(CC) -c 0mem/sci/fs/vfs/vfs.c     $(KINCLUDE) $(CFLAGS) -o vfs.o

	# net
	# three layers support:
	# socket, protocol and network interface.

	# 0mem/sci/net
	$(CC) -c 0mem/sci/net/socket/socket.c  $(KINCLUDE) $(CFLAGS) -o socket.o
	#$(CC) -c 0mem/sci/net/protocol ...
	$(CC) -c 0mem/sci/net/network/channel.c   $(KINCLUDE) $(CFLAGS) -o channel.o
	$(CC) -c 0mem/sci/net/network/network.c   $(KINCLUDE) $(CFLAGS) -o network.o

	# 0mem/sci/sys
	$(CC) -c 0mem/sci/sys/sys.c   $(KINCLUDE) $(CFLAGS) -o sys.o

	# == SI - Service Interface ==============================

	# 0mem/si
	$(CC) -c 0mem/si/sifs.c  $(KINCLUDE) $(CFLAGS) -o sifs.o
	$(CC) -c 0mem/si/sins.c  $(KINCLUDE) $(CFLAGS) -o sins.o
	$(CC) -c 0mem/si/siws.c  $(KINCLUDE) $(CFLAGS) -o siws.o
	# ...

#
# == 1pump ======== 
#

	$(CC) -c 1pump/pump.c  $(KINCLUDE) $(CFLAGS) -o pump.o

	$(CC) -c 1pump/arch/hal.c           $(KINCLUDE) $(CFLAGS) -o hal.o
	$(CC) -c 1pump/arch/detect.c        $(KINCLUDE) $(CFLAGS) -o detect.o

	# 1pump/arch/x86
	$(CC) -c 1pump/arch/x86/x86init.c   $(KINCLUDE) $(CFLAGS) -o x86init.o
	$(CC) -c 1pump/arch/x86/portsx86.c  $(KINCLUDE) $(CFLAGS) -o portsx86.o
	$(CC) -c 1pump/arch/x86/x86.c       $(KINCLUDE) $(CFLAGS) -o x86.o
	$(CC) -c 1pump/arch/x86/x86info.c   $(KINCLUDE) $(CFLAGS) -o x86info.o   
	$(CC) -c 1pump/arch/x86/apic.c      $(KINCLUDE) $(CFLAGS) -o apic.o
	$(CC) -c 1pump/arch/x86/pic.c       $(KINCLUDE) $(CFLAGS) -o pic.o
	$(CC) -c 1pump/arch/x86/pit.c       $(KINCLUDE) $(CFLAGS) -o pit.o
	$(CC) -c 1pump/arch/x86/rtc.c       $(KINCLUDE) $(CFLAGS) -o rtc.o

	# 1pump/arch/amd
	$(CC) -c 1pump/arch/amd/cpuamd.c    $(KINCLUDE) $(CFLAGS) -o cpuamd.o

#
# == 2io ======== 
#

	## == HWI - Hardware Interface ======================= 
	
	$(CC) -c 2io/io.c      $(KINCLUDE) $(CFLAGS) -o io.o
	$(CC) -c 2io/ws.c      $(KINCLUDE) $(CFLAGS) -o ws.o

	# 2io/bus/pcibus
	$(CC) -c 2io/bus/pcibus/pci.c       $(KINCLUDE) $(CFLAGS) -o pci.o
	$(CC) -c 2io/bus/pcibus/pciinfo.c   $(KINCLUDE) $(CFLAGS) -o pciinfo.o
	$(CC) -c 2io/bus/pcibus/pciscan.c   $(KINCLUDE) $(CFLAGS) -o pciscan.o

	# 2io/bus/usbbus
	$(CC) -c 2io/bus/usbbus/usb.c        $(KINCLUDE) $(CFLAGS) -o usb.o

	# 2io/dev
	$(CC) -c 2io/dev/devmgr.c  $(KINCLUDE) $(CFLAGS) -o devmgr.o
	
	# 2io/dev/blkdev
	$(CC) -c 2io/dev/blkdev/ahci/ahci.c    $(KINCLUDE) $(CFLAGS) -o ahci.o
	$(CC) -c 2io/dev/blkdev/ide/ata.c      $(KINCLUDE) $(CFLAGS) -o ata.o
	$(CC) -c 2io/dev/blkdev/ide/atadma.c   $(KINCLUDE) $(CFLAGS) -o atadma.o
	$(CC) -c 2io/dev/blkdev/ide/atainit.c  $(KINCLUDE) $(CFLAGS) -o atainit.o
	$(CC) -c 2io/dev/blkdev/ide/atairq.c   $(KINCLUDE) $(CFLAGS) -o atairq.o
	$(CC) -c 2io/dev/blkdev/ide/atapci.c   $(KINCLUDE) $(CFLAGS) -o atapci.o
	$(CC) -c 2io/dev/blkdev/ide/atahdd.c   $(KINCLUDE) $(CFLAGS) -o atahdd.o
	$(CC) -c 2io/dev/blkdev/storage/storage.c  $(KINCLUDE) $(CFLAGS) -o storage.o

	# =======================================
	# Console support:
	# The console is responsable for the output.
	# It can be virtual terminal, serial or even network output.
	# ttys are used in char devices and netdevices

	# 2io/dev/tty/chardev
	$(CC) -c 2io/dev/tty/chardev/hid/i8042/i8042.c      $(KINCLUDE) $(CFLAGS) -o i8042.o
	$(CC) -c 2io/dev/tty/chardev/hid/i8042/keyboard.c   $(KINCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c 2io/dev/tty/chardev/hid/i8042/ps2kbd.c     $(KINCLUDE) $(CFLAGS) -o ps2kbd.o
	$(CC) -c 2io/dev/tty/chardev/hid/i8042/mouse.c      $(KINCLUDE) $(CFLAGS) -o mouse.o
	$(CC) -c 2io/dev/tty/chardev/hid/i8042/ps2mouse.c   $(KINCLUDE) $(CFLAGS) -o ps2mouse.o
	$(CC) -c 2io/dev/tty/chardev/hid/render/r_render.c  $(KINCLUDE) $(CFLAGS) -o r_render.o
	$(CC) -c 2io/dev/tty/chardev/hid/screen.c           $(KINCLUDE) $(CFLAGS) -o screen.o
	$(CC) -c 2io/dev/tty/chardev/hid/video.c            $(KINCLUDE) $(CFLAGS) -o video.o
	$(CC) -c 2io/dev/tty/chardev/hid/vsync.c            $(KINCLUDE) $(CFLAGS) -o vsync.o
	$(CC) -c 2io/dev/tty/chardev/serial/serial.c        $(KINCLUDE) $(CFLAGS) -o serial.o

	# 2io/dev/tty/netdev
	$(CC) -c 2io/dev/tty/netdev/e1000/e1000.c   $(KINCLUDE) $(CFLAGS) -o e1000.o

	# tty infra structure
	# 2io/dev/tty
	$(CC) -c 2io/dev/tty/tty_io.c  $(KINCLUDE) $(CFLAGS) -o tty_io.o
	$(CC) -c 2io/dev/tty/tty.c     $(KINCLUDE) $(CFLAGS) -o tty.o
	$(CC) -c 2io/dev/tty/pty.c     $(KINCLUDE) $(CFLAGS) -o pty.o


#
# == user ======== 
#

#
# Controller
#

	# System call interface and user call interface.
	$(CC) -c user/ctrl/sci.c       $(KINCLUDE) $(CFLAGS) -o sci.o
	$(CC) -c user/ctrl/console.c   $(KINCLUDE) $(CFLAGS) -o console.o

	$(CC) -c user/terminal.c  $(KINCLUDE) $(CFLAGS) -o terminal.o
	$(CC) -c user/vt.c        $(KINCLUDE) $(CFLAGS) -o vt.o
	$(CC) -c user/dialog.c    $(KINCLUDE) $(CFLAGS) -o dialog.o
	$(CC) -c user/kgwm.c      $(KINCLUDE) $(CFLAGS) -o kgwm.o
	$(CC) -c user/kgws.c      $(KINCLUDE) $(CFLAGS) -o kgws.o
	$(CC) -c user/wm.c        $(KINCLUDE) $(CFLAGS) -o wm.o

	# data model

	# user/model
	$(CC) -c user/model/font.c  $(KINCLUDE) $(CFLAGS) -o font.o

	# kernel gramado window system.

	# user/view
	$(CC) -c user/view/bg.c       $(KINCLUDE) $(CFLAGS) -o bg.o
	$(CC) -c user/view/bmp.c      $(KINCLUDE) $(CFLAGS) -o bmp.o
	$(CC) -c user/view/button.c   $(KINCLUDE) $(CFLAGS) -o button.o
	$(CC) -c user/view/char.c     $(KINCLUDE) $(CFLAGS) -o char.o
	$(CC) -c user/view/createw.c  $(KINCLUDE) $(CFLAGS) -o createw.o
	$(CC) -c user/view/dtext.c    $(KINCLUDE) $(CFLAGS) -o dtext.o
	$(CC) -c user/view/line.c     $(KINCLUDE) $(CFLAGS) -o line.o
	$(CC) -c user/view/menu.c     $(KINCLUDE) $(CFLAGS) -o menu.o
	$(CC) -c user/view/mbar.c     $(KINCLUDE) $(CFLAGS) -o mbar.o
	$(CC) -c user/view/pixel.c    $(KINCLUDE) $(CFLAGS) -o pixel.o
	$(CC) -c user/view/pbar.c     $(KINCLUDE) $(CFLAGS) -o pbar.o
	$(CC) -c user/view/rect.c     $(KINCLUDE) $(CFLAGS) -o rect.o
	$(CC) -c user/view/sbar.c     $(KINCLUDE) $(CFLAGS) -o sbar.o
	$(CC) -c user/view/tbar.c     $(KINCLUDE) $(CFLAGS) -o tbar.o
	$(CC) -c user/view/input.c    $(KINCLUDE) $(CFLAGS) -o input.o
	$(CC) -c user/view/output.c   $(KINCLUDE) $(CFLAGS) -o output.o

	# user/security
	$(CC) -c user/security/desktop.c   $(KINCLUDE) $(CFLAGS) -o desktop.o
	$(CC) -c user/security/room.c      $(KINCLUDE) $(CFLAGS) -o room.o
	$(CC) -c user/security/userenv.c   $(KINCLUDE) $(CFLAGS) -o userenv.o
	$(CC) -c user/security/usession.c  $(KINCLUDE) $(CFLAGS) -o usession.o
	$(CC) -c user/security/logoff.c    $(KINCLUDE) $(CFLAGS) -o logoff.o
	$(CC) -c user/security/logon.c     $(KINCLUDE) $(CFLAGS) -o logon.o


## Step2 link-kernel-image  - Linking the kernel image.
#kernel-image-link:

link-kernel:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	#debug
	#$(LD) $(LDFLAGS) -T link.ld -o KERNEL.BIN $(OBJECTS) -Map kernel.map    

	$(LD) $(LDFLAGS) -T link.ld -o KERNEL.BIN $(OBJECTS)    

clean:
	rm -rf *.o   
	
	



