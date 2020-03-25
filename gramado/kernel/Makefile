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


##
## Objects
##

ifeq ($(ARCH),x86)

	#deveria ser headx86.o
	ENTRY_OBJECTS := boot.o main.o x86init.o 

	EXECVE_OBJECTS := socket.o ctype.o  kstdio.o stdlib.o string.o unistd.o \
	devmgr.o \
	gde_serv.o \
	debug.o storage.o install.o object.o runtime.o \
	abort.o info.o io.o modules.o signal.o sm.o \
	init.o system.o \
	execve.o 
	
	HAL_OBJECTS := cpuamd.o portsx86.o syscall.o x86.o detect.o \
	hal.o 
	
	KDRIVERS_OBJECTS := ahci.o \
	ata.o atadma.o atainit.o atairq.o atapci.o hdd.o \
	channel.o network.o nicintel.o \
	pci.o pciinfo.o pciscan.o \
	tty.o pty.o vt.o\
	usb.o \
	video.o vsync.o screen.o xproc.o \
	i8042.o keyboard.o mouse.o ps2kbd.o ps2mouse.o ldisc.o \
	apic.o pic.o rtc.o serial.o pit.o  
	
	KSERVERS_OBJECTS := cf.o format.o pipe.o fs.o read.o search.o write.o \
	cedge.o bg.o bmp.o button.o char.o createw.o dtext.o font.o grid.o \
	line.o menu.o menubar.o pixel.o rect.o sbar.o toolbar.o wm.o \
	logoff.o \
	logon.o \
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
	PANIC_OBJECTS := panic.o 
	REBOOT_OBJECTS := reboot.o 
	SYS_OBJECTS := sys.o sysio.o syslib.o sysmk.o syssm.o   
	
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



all: all-c link-kernel clean

all-c:

	#
	# init/
	#

	# x86 boot
	$(NASM) init/x86/boot.asm -I init/x86/ -f elf -o boot.o

	# main (Architechture independent)
	$(CC) -c init/main.c $(KINCLUDE) $(CFLAGS) -o main.o

	# x86 initialization
	$(CC) -c init/x86/x86init.c  $(KINCLUDE) $(CFLAGS) -o x86init.o

	# sysio/hal
	$(CC) -c sysio/hal/hal.c                $(KINCLUDE) $(CFLAGS) -o hal.o
	$(CC) -c sysio/hal/arch/detect.c        $(KINCLUDE) $(CFLAGS) -o detect.o
	$(CC) -c sysio/hal/arch/amd/cpuamd.c    $(KINCLUDE) $(CFLAGS) -o cpuamd.o
	$(CC) -c sysio/hal/arch/x86/portsx86.c  $(KINCLUDE) $(CFLAGS) -o portsx86.o
	$(CC) -c sysio/hal/arch/x86/syscall.c   $(KINCLUDE) $(CFLAGS) -o syscall.o
	$(CC) -c sysio/hal/arch/x86/x86.c       $(KINCLUDE) $(CFLAGS) -o x86.o


	# x86
	$(CC) -c  sysmk/ps/arch/x86/x86cont.c   $(KINCLUDE)  $(CFLAGS) -o x86cont.o
	$(CC) -c  sysmk/ps/arch/x86/x86fault.c  $(KINCLUDE)  $(CFLAGS) -o x86fault.o
	$(CC) -c  sysmk/ps/arch/x86/x86start.c  $(KINCLUDE)  $(CFLAGS) -o x86start.o

	# ps/action
	$(CC) -c  sysmk/ps/action/dispatch.c  $(KINCLUDE)  $(CFLAGS) -o dispatch.o
	$(CC) -c  sysmk/ps/action/pheap.c     $(KINCLUDE)  $(CFLAGS) -o pheap.o
	$(CC) -c  sysmk/ps/action/process.c   $(KINCLUDE)  $(CFLAGS) -o process.o
	$(CC) -c  sysmk/ps/action/clone.c     $(KINCLUDE)  $(CFLAGS) -o clone.o
	$(CC) -c  sysmk/ps/action/queue.c     $(KINCLUDE)  $(CFLAGS) -o queue.o
	$(CC) -c  sysmk/ps/action/spawn.c     $(KINCLUDE)  $(CFLAGS) -o spawn.o
	$(CC) -c  sysmk/ps/action/tasks.c     $(KINCLUDE)  $(CFLAGS) -o tasks.o
	$(CC) -c  sysmk/ps/action/theap.c     $(KINCLUDE)  $(CFLAGS) -o theap.o
	$(CC) -c  sysmk/ps/action/thread.c    $(KINCLUDE)  $(CFLAGS) -o thread.o
	$(CC) -c  sysmk/ps/action/threadi.c   $(KINCLUDE)  $(CFLAGS) -o threadi.o
	$(CC) -c  sysmk/ps/action/ts.c        $(KINCLUDE)  $(CFLAGS) -o ts.o
	$(CC) -c  sysmk/ps/action/tstack.c    $(KINCLUDE)  $(CFLAGS) -o tstack.o
	$(CC) -c sysmk/ps/action/execve.c     $(KINCLUDE) $(CFLAGS) -o execve.o

	# ps/ipc
	$(CC) -c  sysmk/ps/ipc/callfar.c  $(KINCLUDE)  $(CFLAGS) -o callfar.o
	$(CC) -c  sysmk/ps/ipc/callout.c  $(KINCLUDE)  $(CFLAGS) -o callout.o
	$(CC) -c  sysmk/ps/ipc/ipc.c      $(KINCLUDE)  $(CFLAGS) -o ipc.o
	$(CC) -c  sysmk/ps/ipc/ipccore.c  $(KINCLUDE)  $(CFLAGS) -o ipccore.o
	$(CC) -c  sysmk/ps/ipc/sem.c      $(KINCLUDE)  $(CFLAGS) -o sem.o

	# ps/mm
	$(CC) -c  sysmk/ps/mm/x86/memory.c  $(KINCLUDE) $(CFLAGS) -o memory.o
	$(CC) -c  sysmk/ps/mm/x86/mminfo.c  $(KINCLUDE) $(CFLAGS) -o mminfo.o
	$(CC) -c  sysmk/ps/mm/x86/mmpool.c  $(KINCLUDE) $(CFLAGS) -o mmpool.o
	$(CC) -c  sysmk/ps/mm/x86/pages.c   $(KINCLUDE) $(CFLAGS) -o pages.o

	# ps/sched
	$(CC) -c  sysmk/ps/sched/preempt.c   $(KINCLUDE) $(CFLAGS) -o preempt.o
	$(CC) -c  sysmk/ps/sched/priority.c  $(KINCLUDE) $(CFLAGS) -o priority.o
	$(CC) -c  sysmk/ps/sched/sched.c     $(KINCLUDE) $(CFLAGS) -o sched.o
	$(CC) -c  sysmk/ps/sched/schedi.c    $(KINCLUDE) $(CFLAGS) -o schedi.o


	# mk
	$(CC) -c sysmk/create.c  $(KINCLUDE)  $(CFLAGS) -o create.o
	$(CC) -c sysmk/mk.c      $(KINCLUDE)  $(CFLAGS) -o mk.o

	#kernel
	$(CC) -c  request.c  $(KINCLUDE) $(CFLAGS) -o request.o
	$(CC) -c  panic.c    $(KINCLUDE) $(CFLAGS) -o panic.o
	$(CC) -c  reboot.c   $(KINCLUDE) $(CFLAGS) -o reboot.o

	# fs
	$(CC) -c sci/fs/pipe.c    $(KINCLUDE) $(CFLAGS) -o pipe.o

	# libcore
	$(CC) -c syslib/libcore/ctype.c   $(KINCLUDE) $(CFLAGS) -o ctype.o
	$(CC) -c syslib/libcore/kstdio.c  $(KINCLUDE) $(CFLAGS) -o kstdio.o
	$(CC) -c syslib/libcore/stdlib.c  $(KINCLUDE) $(CFLAGS) -o stdlib.o
	$(CC) -c syslib/libcore/string.c  $(KINCLUDE) $(CFLAGS) -o string.o
	$(CC) -c syslib/libcore/unistd.c  $(KINCLUDE) $(CFLAGS) -o unistd.o

	# rtc
	$(CC) -c sysio/kdrivers/rtc/rtc.c     $(KINCLUDE) $(CFLAGS) -o rtc.o

	# serial
	$(CC) -c sysio/kdrivers/serial/serial.c  $(KINCLUDE) $(CFLAGS) -o serial.o

	# x86
	$(CC) -c sysio/kdrivers/arch/x86/apic.c  $(KINCLUDE) $(CFLAGS) -o apic.o
	$(CC) -c sysio/kdrivers/arch/x86/pic.c   $(KINCLUDE) $(CFLAGS) -o pic.o
	$(CC) -c sysio/kdrivers/arch/x86/pit.c   $(KINCLUDE) $(CFLAGS) -o pit.o

	# ahci 
	$(CC) -c sysio/kdrivers/ahci/ahci.c  $(KINCLUDE) $(CFLAGS) -o ahci.o

	# ide
	$(CC) -c sysio/kdrivers/ide/hdd.c      $(KINCLUDE) $(CFLAGS) -o hdd.o
	$(CC) -c sysio/kdrivers/ide/ata.c      $(KINCLUDE) $(CFLAGS) -o ata.o
	$(CC) -c sysio/kdrivers/ide/atainit.c  $(KINCLUDE) $(CFLAGS) -o atainit.o
	$(CC) -c sysio/kdrivers/ide/atairq.c   $(KINCLUDE) $(CFLAGS) -o atairq.o
	$(CC) -c sysio/kdrivers/ide/atapci.c   $(KINCLUDE) $(CFLAGS) -o atapci.o
	$(CC) -c sysio/kdrivers/ide/atadma.c   $(KINCLUDE) $(CFLAGS) -o atadma.o

	# net
	$(CC) -c net/network/nicintel.c  $(KINCLUDE) $(CFLAGS) -o nicintel.o
	$(CC) -c net/network/channel.c   $(KINCLUDE) $(CFLAGS) -o channel.o
	$(CC) -c net/network/network.c   $(KINCLUDE) $(CFLAGS) -o network.o
	$(CC) -c net/socket.c            $(KINCLUDE) $(CFLAGS) -o socket.o	

	# pci
	$(CC) -c sysio/kdrivers/pci/pci.c      $(KINCLUDE) $(CFLAGS) -o pci.o
	$(CC) -c sysio/kdrivers/pci/pciscan.c  $(KINCLUDE) $(CFLAGS) -o pciscan.o
	$(CC) -c sysio/kdrivers/pci/pciinfo.c  $(KINCLUDE) $(CFLAGS) -o pciinfo.o


	# tty
	$(CC) -c sysio/kdrivers/tty/console.c $(KINCLUDE) $(CFLAGS) -o cedge.o
	$(CC) -c sysio/kdrivers/tty/tty.c     $(KINCLUDE) $(CFLAGS) -o tty.o
	$(CC) -c sysio/kdrivers/tty/pty.c     $(KINCLUDE) $(CFLAGS) -o pty.o
	$(CC) -c sysio/kdrivers/tty/vt.c  $(KINCLUDE) $(CFLAGS) -o vt.o

	# usb
	$(CC) -c sysio/kdrivers/usb/usb.c   $(KINCLUDE) $(CFLAGS) -o usb.o
	
	
	# devices
	$(CC) -c sysio/devmgr.c  $(KINCLUDE) $(CFLAGS) -o devmgr.o

	# fs
	$(CC) -c sci/fs/fs.c      $(KINCLUDE) $(CFLAGS) -o fs.o
	$(CC) -c sci/fs/vfs.c     $(KINCLUDE) $(CFLAGS) -o vfs.o
	$(CC) -c sci/fs/cf.c      $(KINCLUDE) $(CFLAGS) -o cf.o
	$(CC) -c sci/fs/read.c    $(KINCLUDE) $(CFLAGS) -o read.o
	$(CC) -c sci/fs/write.c   $(KINCLUDE) $(CFLAGS) -o write.o
	$(CC) -c sci/fs/search.c  $(KINCLUDE) $(CFLAGS) -o search.o
	$(CC) -c sci/fs/format.c  $(KINCLUDE) $(CFLAGS) -o format.o

	# storage
	$(CC) -c syssm/storage/storage.c   $(KINCLUDE) $(CFLAGS) -o storage.o

	# system
	$(CC) -c syssm/system/abort.c    $(KINCLUDE) $(CFLAGS) -o abort.o
	$(CC) -c syssm/system/info.c     $(KINCLUDE) $(CFLAGS) -o info.o
	$(CC) -c syssm/system/init.c     $(KINCLUDE) $(CFLAGS) -o init.o
	$(CC) -c syssm/system/install.c  $(KINCLUDE) $(CFLAGS) -o install.o
	$(CC) -c syssm/system/modules.c  $(KINCLUDE) $(CFLAGS) -o modules.o
	$(CC) -c syssm/system/runtime.c  $(KINCLUDE) $(CFLAGS) -o runtime.o
	$(CC) -c syssm/system/signal.c   $(KINCLUDE) $(CFLAGS) -o signal.o
	$(CC) -c syssm/system/sm.c       $(KINCLUDE) $(CFLAGS) -o sm.o
	$(CC) -c syssm/system/system.c   $(KINCLUDE) $(CFLAGS) -o system.o

	# debug
	$(CC) -c syssm/debug/debug.c  $(KINCLUDE) $(CFLAGS) -o debug.o

	# io
	$(CC) -c sysio/io.c  $(KINCLUDE) $(CFLAGS) -o io.o

	# ob
	$(CC) -c syssm/ob/object.c  $(KINCLUDE) $(CFLAGS) -o object.o


	# Window Manager.
	$(CC) -c wm/kgwm.c    $(KINCLUDE) $(CFLAGS) -o kgwm.o
	$(CC) -c wm/wm.c      $(KINCLUDE) $(CFLAGS) -o wm.o
	$(CC) -c wm/logon.c   $(KINCLUDE) $(CFLAGS) -o logon.o
	$(CC) -c wm/logoff.c  $(KINCLUDE) $(CFLAGS) -o logoff.o

	# Window Server.
	$(CC) -c ws/bg.c        $(KINCLUDE) $(CFLAGS) -o bg.o
	$(CC) -c ws/bmp.c       $(KINCLUDE) $(CFLAGS) -o bmp.o
	$(CC) -c ws/button.c    $(KINCLUDE) $(CFLAGS) -o button.o
	$(CC) -c ws/char.c      $(KINCLUDE) $(CFLAGS) -o char.o
	$(CC) -c ws/createw.c   $(KINCLUDE) $(CFLAGS) -o createw.o
	$(CC) -c ws/dtext.c     $(KINCLUDE) $(CFLAGS) -o dtext.o
	$(CC) -c ws/font.c      $(KINCLUDE) $(CFLAGS) -o font.o
	$(CC) -c ws/grid.c      $(KINCLUDE) $(CFLAGS) -o grid.o
	$(CC) -c ws/line.c      $(KINCLUDE) $(CFLAGS) -o line.o
	$(CC) -c ws/menu.c      $(KINCLUDE) $(CFLAGS) -o menu.o
	$(CC) -c ws/menubar.c   $(KINCLUDE) $(CFLAGS) -o menubar.o
	$(CC) -c ws/pixel.c     $(KINCLUDE) $(CFLAGS) -o pixel.o
	$(CC) -c ws/rect.c      $(KINCLUDE) $(CFLAGS) -o rect.o
	$(CC) -c ws/sbar.c      $(KINCLUDE) $(CFLAGS) -o sbar.o
	$(CC) -c ws/toolbar.c   $(KINCLUDE) $(CFLAGS) -o toolbar.o
	$(CC) -c ws/input.c     $(KINCLUDE) $(CFLAGS) -o input.o
	$(CC) -c ws/output.c    $(KINCLUDE) $(CFLAGS) -o output.o
	$(CC) -c ws/terminal.c  $(KINCLUDE) $(CFLAGS) -o terminal.o
	$(CC) -c ws/kgws.c      $(KINCLUDE) $(CFLAGS) -o kgws.o
	$(CC) -c ws/xproc.c     $(KINCLUDE) $(CFLAGS) -o xproc.o
	$(CC) -c ws/screen.c    $(KINCLUDE) $(CFLAGS) -o screen.o
	$(CC) -c ws/video.c     $(KINCLUDE) $(CFLAGS) -o video.o
	$(CC) -c ws/vsync.c     $(KINCLUDE) $(CFLAGS) -o vsync.o
	$(CC) -c ws/i8042.c     $(KINCLUDE) $(CFLAGS) -o i8042.o
	$(CC) -c ws/keyboard.c  $(KINCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c ws/mouse.c     $(KINCLUDE) $(CFLAGS) -o mouse.o
	$(CC) -c ws/ps2kbd.c    $(KINCLUDE) $(CFLAGS) -o ps2kbd.o
	$(CC) -c ws/ps2mouse.c  $(KINCLUDE) $(CFLAGS) -o ps2mouse.o
	$(CC) -c ws/ldisc.c     $(KINCLUDE) $(CFLAGS) -o ldisc.o


	# Security
	$(CC) -c security/desktop.c   $(KINCLUDE) $(CFLAGS) -o desktop.o
	$(CC) -c security/room.c      $(KINCLUDE) $(CFLAGS) -o room.o
	$(CC) -c security/userenv.c   $(KINCLUDE) $(CFLAGS) -o userenv.o
	$(CC) -c security/usession.c  $(KINCLUDE) $(CFLAGS) -o usession.o


	#
	#  /sci - System Call Interface.
	#
	
	$(CC) -c sci/gde_serv.c $(KINCLUDE) $(CFLAGS) -o gde_serv.o
	
	# services.
	$(CC) -c sci/sys/sys.c   $(KINCLUDE) $(CFLAGS) -o sys.o
	$(CC) -c sysio/sysio.c   $(KINCLUDE) $(CFLAGS) -o sysio.o
	$(CC) -c syslib/syslib.c $(KINCLUDE) $(CFLAGS) -o syslib.o
	$(CC) -c sysmk/sysmk.c   $(KINCLUDE) $(CFLAGS) -o sysmk.o
	$(CC) -c syssm/syssm.c   $(KINCLUDE) $(CFLAGS) -o syssm.o
	

## Step2 link-kernel-image  - Linking the kernel image.
#kernel-image-link:

link-kernel:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	$(LD) $(LDFLAGS) -T link.ld -o KERNEL.BIN $(OBJECTS)   

clean:
	rm -rf *.o   
	
	



