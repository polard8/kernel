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
	
	HAL_OBJECTS := cpuamd.o portsx86.o x86.o x86info.o detect.o \
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
	SYS_OBJECTS := sys.o pump.o sifs.o siws.o sins.o   


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

	##
	## ==== TOP ==== 
	##

	# main (Architechture independent)
	# It's the higher level of the init sybsystem.
	$(CC) -c main.c $(KINCLUDE) $(CFLAGS) -o main.o
	# kernel
	$(CC) -c request.c  $(KINCLUDE) $(CFLAGS) -o request.o
	$(CC) -c panic.c    $(KINCLUDE) $(CFLAGS) -o panic.o
	$(CC) -c reboot.c   $(KINCLUDE) $(CFLAGS) -o reboot.o


	#
	# == SI - Service Interface ==============================
	#

	$(CC) -c si/sifs.c  $(KINCLUDE) $(CFLAGS) -o sifs.o
	$(CC) -c si/sins.c  $(KINCLUDE) $(CFLAGS) -o sins.o
	$(CC) -c si/siws.c  $(KINCLUDE) $(CFLAGS) -o siws.o
	#...


	#
	# == SCI - System Call Interface ==============================
	#

	# posix - (Interface to give ring0 support for posix libc)
	$(CC) -c sci/posix/ctype.c   $(KINCLUDE) $(CFLAGS) -o ctype.o
	$(CC) -c sci/posix/kstdio.c  $(KINCLUDE) $(CFLAGS) -o kstdio.o
	$(CC) -c sci/posix/signal.c  $(KINCLUDE) $(CFLAGS) -o signal.o
	$(CC) -c sci/posix/stdlib.c  $(KINCLUDE) $(CFLAGS) -o stdlib.o
	$(CC) -c sci/posix/string.c  $(KINCLUDE) $(CFLAGS) -o string.o
	$(CC) -c sci/posix/unistd.c  $(KINCLUDE) $(CFLAGS) -o unistd.o

	$(CC) -c sci/sys/sys.c   $(KINCLUDE) $(CFLAGS) -o sys.o

	$(CC) -c sci/gde_serv.c $(KINCLUDE) $(CFLAGS) -o gde_serv.o

	# fs/vfs
	$(CC) -c sci/fs/vfs/vfs.c     $(KINCLUDE) $(CFLAGS) -o vfs.o
	
	# fs
	$(CC) -c sci/fs/cf.c      $(KINCLUDE) $(CFLAGS) -o cf.o
	$(CC) -c sci/fs/format.c  $(KINCLUDE) $(CFLAGS) -o format.o
	$(CC) -c sci/fs/fs.c      $(KINCLUDE) $(CFLAGS) -o fs.o
	$(CC) -c sci/fs/pipe.c    $(KINCLUDE) $(CFLAGS) -o pipe.o
	$(CC) -c sci/fs/read.c    $(KINCLUDE) $(CFLAGS) -o read.o
	$(CC) -c sci/fs/search.c  $(KINCLUDE) $(CFLAGS) -o search.o
	$(CC) -c sci/fs/write.c   $(KINCLUDE) $(CFLAGS) -o write.o

	# net
	# three layers support:
	# socket, protocol and network interface.

	$(CC) -c sci/net/socket/socket.c  $(KINCLUDE) $(CFLAGS) -o socket.o
	#$(CC) -c sci/net/protocol ...
	$(CC) -c sci/net/network/channel.c   $(KINCLUDE) $(CFLAGS) -o channel.o
	$(CC) -c sci/net/network/network.c   $(KINCLUDE) $(CFLAGS) -o network.o

    #Window system ring 0 support.
	# Window Manager.
	$(CC) -c sci/windows/kgwm.c    $(KINCLUDE) $(CFLAGS) -o kgwm.o
	$(CC) -c sci/windows/logoff.c  $(KINCLUDE) $(CFLAGS) -o logoff.o
	$(CC) -c sci/windows/logon.c   $(KINCLUDE) $(CFLAGS) -o logon.o
	$(CC) -c sci/windows/wm.c      $(KINCLUDE) $(CFLAGS) -o wm.o
	# Window Server.
	$(CC) -c sci/windows/bg.c        $(KINCLUDE) $(CFLAGS) -o bg.o
	$(CC) -c sci/windows/bmp.c       $(KINCLUDE) $(CFLAGS) -o bmp.o
	$(CC) -c sci/windows/button.c    $(KINCLUDE) $(CFLAGS) -o button.o
	$(CC) -c sci/windows/char.c      $(KINCLUDE) $(CFLAGS) -o char.o
	$(CC) -c sci/windows/createw.c   $(KINCLUDE) $(CFLAGS) -o createw.o
	$(CC) -c sci/windows/dtext.c     $(KINCLUDE) $(CFLAGS) -o dtext.o
	$(CC) -c sci/windows/font.c      $(KINCLUDE) $(CFLAGS) -o font.o
	$(CC) -c sci/windows/grid.c      $(KINCLUDE) $(CFLAGS) -o grid.o
	$(CC) -c sci/windows/line.c      $(KINCLUDE) $(CFLAGS) -o line.o
	$(CC) -c sci/windows/menu.c      $(KINCLUDE) $(CFLAGS) -o menu.o
	$(CC) -c sci/windows/menubar.c   $(KINCLUDE) $(CFLAGS) -o menubar.o
	$(CC) -c sci/windows/pixel.c     $(KINCLUDE) $(CFLAGS) -o pixel.o
	$(CC) -c sci/windows/rect.c      $(KINCLUDE) $(CFLAGS) -o rect.o
	$(CC) -c sci/windows/sbar.c      $(KINCLUDE) $(CFLAGS) -o sbar.o
	$(CC) -c sci/windows/toolbar.c   $(KINCLUDE) $(CFLAGS) -o toolbar.o
	$(CC) -c sci/windows/kgws.c      $(KINCLUDE) $(CFLAGS) -o kgws.o
	$(CC) -c sci/windows/xproc.c     $(KINCLUDE) $(CFLAGS) -o xproc.o


	#
	# == Gramado Core =================================================
	#
	
	# Architecture independent layer.


	$(CC) -c core/security/desktop.c   $(KINCLUDE) $(CFLAGS) -o desktop.o
	$(CC) -c core/security/room.c      $(KINCLUDE) $(CFLAGS) -o room.o
	$(CC) -c core/security/userenv.c   $(KINCLUDE) $(CFLAGS) -o userenv.o
	$(CC) -c core/security/usession.c  $(KINCLUDE) $(CFLAGS) -o usession.o

	$(CC) -c core/debug/debug.c      $(KINCLUDE) $(CFLAGS) -o debug.o

	$(CC) -c core/ob/object.c        $(KINCLUDE) $(CFLAGS) -o object.o

	$(CC) -c core/storage/storage.c  $(KINCLUDE) $(CFLAGS) -o storage.o
	$(CC) -c core/abort.c    $(KINCLUDE) $(CFLAGS) -o abort.o
	$(CC) -c core/info.c     $(KINCLUDE) $(CFLAGS) -o info.o
	$(CC) -c core/init.c     $(KINCLUDE) $(CFLAGS) -o init.o
	$(CC) -c core/install.c  $(KINCLUDE) $(CFLAGS) -o install.o
	$(CC) -c core/modules.c  $(KINCLUDE) $(CFLAGS) -o modules.o
	$(CC) -c core/runtime.c  $(KINCLUDE) $(CFLAGS) -o runtime.o
	$(CC) -c core/sm.c       $(KINCLUDE) $(CFLAGS) -o sm.o
	$(CC) -c core/system.c   $(KINCLUDE) $(CFLAGS) -o system.o


	# ps/action
	$(CC) -c  core/ps/action/dispatch.c  $(KINCLUDE)  $(CFLAGS) -o dispatch.o
	$(CC) -c  core/ps/action/pheap.c     $(KINCLUDE)  $(CFLAGS) -o pheap.o
	$(CC) -c  core/ps/action/process.c   $(KINCLUDE)  $(CFLAGS) -o process.o
	$(CC) -c  core/ps/action/clone.c     $(KINCLUDE)  $(CFLAGS) -o clone.o
	$(CC) -c  core/ps/action/queue.c     $(KINCLUDE)  $(CFLAGS) -o queue.o
	$(CC) -c  core/ps/action/spawn.c     $(KINCLUDE)  $(CFLAGS) -o spawn.o
	$(CC) -c  core/ps/action/tasks.c     $(KINCLUDE)  $(CFLAGS) -o tasks.o
	$(CC) -c  core/ps/action/theap.c     $(KINCLUDE)  $(CFLAGS) -o theap.o
	$(CC) -c  core/ps/action/thread.c    $(KINCLUDE)  $(CFLAGS) -o thread.o
	$(CC) -c  core/ps/action/threadi.c   $(KINCLUDE)  $(CFLAGS) -o threadi.o
	$(CC) -c  core/ps/action/ts.c        $(KINCLUDE)  $(CFLAGS) -o ts.o
	$(CC) -c  core/ps/action/tstack.c    $(KINCLUDE)  $(CFLAGS) -o tstack.o
	$(CC) -c  core/ps/action/execve.c    $(KINCLUDE)  $(CFLAGS) -o execve.o

	# ps/ipc
	$(CC) -c  core/ps/ipc/callfar.c  $(KINCLUDE)  $(CFLAGS) -o callfar.o
	$(CC) -c  core/ps/ipc/callout.c  $(KINCLUDE)  $(CFLAGS) -o callout.o
	$(CC) -c  core/ps/ipc/ipc.c      $(KINCLUDE)  $(CFLAGS) -o ipc.o
	$(CC) -c  core/ps/ipc/ipccore.c  $(KINCLUDE)  $(CFLAGS) -o ipccore.o
	$(CC) -c  core/ps/ipc/sem.c      $(KINCLUDE)  $(CFLAGS) -o sem.o

	# ps/sched
	$(CC) -c  core/ps/sched/preempt.c   $(KINCLUDE) $(CFLAGS) -o preempt.o
	$(CC) -c  core/ps/sched/priority.c  $(KINCLUDE) $(CFLAGS) -o priority.o
	$(CC) -c  core/ps/sched/sched.c     $(KINCLUDE) $(CFLAGS) -o sched.o
	$(CC) -c  core/ps/sched/schedi.c    $(KINCLUDE) $(CFLAGS) -o schedi.o

	# ps -x86 - falling angels.
	$(CC) -c core/ps/x86/x86cont.c   $(KINCLUDE)  $(CFLAGS) -o x86cont.o
	$(CC) -c core/ps/x86/x86fault.c  $(KINCLUDE)  $(CFLAGS) -o x86fault.o
	$(CC) -c core/ps/x86/x86start.c  $(KINCLUDE)  $(CFLAGS) -o x86start.o
	$(CC) -c core/ps/x86/memory.c    $(KINCLUDE)  $(CFLAGS) -o memory.o
	$(CC) -c core/ps/x86/mminfo.c    $(KINCLUDE)  $(CFLAGS) -o mminfo.o
	$(CC) -c core/ps/x86/mmpool.c    $(KINCLUDE)  $(CFLAGS) -o mmpool.o
	$(CC) -c core/ps/x86/pages.c     $(KINCLUDE)  $(CFLAGS) -o pages.o

	# ps
	$(CC) -c core/ps/create.c  $(KINCLUDE)  $(CFLAGS) -o create.o
	$(CC) -c core/ps/mk.c      $(KINCLUDE)  $(CFLAGS) -o mk.o






	##
	## == HWI - Hardware Interface ======================= 
	##

	$(CC) -c hwi/io.c    $(KINCLUDE) $(CFLAGS) -o io.o
	$(CC) -c hwi/pump.c  $(KINCLUDE) $(CFLAGS) -o pump.o

	# dd
	$(CC) -c hwi/dd/devmgr.c  $(KINCLUDE) $(CFLAGS) -o devmgr.o



	#
	# == nhid ====
	#

	# ahci 
	$(CC) -c hwi/dd/nhid/ahci/ahci.c  $(KINCLUDE) $(CFLAGS) -o ahci.o
	
	# x86
	$(CC) -c hwi/dd/nhid/arch/x86/apic.c  $(KINCLUDE) $(CFLAGS) -o apic.o
	$(CC) -c hwi/dd/nhid/arch/x86/pic.c   $(KINCLUDE) $(CFLAGS) -o pic.o
	$(CC) -c hwi/dd/nhid/arch/x86/pit.c   $(KINCLUDE) $(CFLAGS) -o pit.o
	
	# hal
	$(CC) -c hwi/hal/hal.c                $(KINCLUDE) $(CFLAGS) -o hal.o
	$(CC) -c hwi/hal/arch/detect.c        $(KINCLUDE) $(CFLAGS) -o detect.o
	$(CC) -c hwi/hal/arch/amd/cpuamd.c    $(KINCLUDE) $(CFLAGS) -o cpuamd.o
	$(CC) -c hwi/hal/arch/x86/portsx86.c  $(KINCLUDE) $(CFLAGS) -o portsx86.o
	$(CC) -c hwi/hal/arch/x86/x86.c       $(KINCLUDE) $(CFLAGS) -o x86.o
	$(CC) -c hwi/hal/arch/x86/x86info.c   $(KINCLUDE) $(CFLAGS) -o x86info.o   


	# ide
	$(CC) -c hwi/dd/nhid/ide/ata.c      $(KINCLUDE) $(CFLAGS) -o ata.o
	$(CC) -c hwi/dd/nhid/ide/atadma.c   $(KINCLUDE) $(CFLAGS) -o atadma.o
	$(CC) -c hwi/dd/nhid/ide/atainit.c  $(KINCLUDE) $(CFLAGS) -o atainit.o
	$(CC) -c hwi/dd/nhid/ide/atairq.c   $(KINCLUDE) $(CFLAGS) -o atairq.o
	$(CC) -c hwi/dd/nhid/ide/atapci.c   $(KINCLUDE) $(CFLAGS) -o atapci.o
	$(CC) -c hwi/dd/nhid/ide/hdd.c      $(KINCLUDE) $(CFLAGS) -o hdd.o

	# net
	$(CC) -c hwi/dd/nhid/net/nicintel.c  $(KINCLUDE) $(CFLAGS) -o nicintel.o

	# rtc
	$(CC) -c hwi/dd/nhid/rtc/rtc.c     $(KINCLUDE) $(CFLAGS) -o rtc.o

	# serial
	$(CC) -c hwi/dd/nhid/serial/serial.c  $(KINCLUDE) $(CFLAGS) -o serial.o

	# pci
	$(CC) -c hwi/dd/nhid/pci/pci.c      $(KINCLUDE) $(CFLAGS) -o pci.o
	$(CC) -c hwi/dd/nhid/pci/pciinfo.c  $(KINCLUDE) $(CFLAGS) -o pciinfo.o
	$(CC) -c hwi/dd/nhid/pci/pciscan.c  $(KINCLUDE) $(CFLAGS) -o pciscan.o

	# usb
	$(CC) -c hwi/dd/nhid/usb/usb.c   $(KINCLUDE) $(CFLAGS) -o usb.o


	#
	# ==== hid ====
	# 

	# tty
	$(CC) -c hwi/tty/console.c   $(KINCLUDE) $(CFLAGS) -o cedge.o
	$(CC) -c hwi/tty/pty.c       $(KINCLUDE) $(CFLAGS) -o pty.o
	$(CC) -c hwi/tty/tty.c       $(KINCLUDE) $(CFLAGS) -o tty.o
	$(CC) -c hwi/tty/vt.c        $(KINCLUDE) $(CFLAGS) -o vt.o
	$(CC) -c hwi/tty/terminal.c  $(KINCLUDE) $(CFLAGS) -o terminal.o
	$(CC) -c hwi/tty/ldisc.c     $(KINCLUDE) $(CFLAGS) -o ldisc.o
	

	# hid - Human Interface Devices.
	# video, mouse, keyboard.
	$(CC) -c hwi/dd/hid/i8042.c     $(KINCLUDE) $(CFLAGS) -o i8042.o
	$(CC) -c hwi/dd/hid/keyboard.c  $(KINCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c hwi/dd/hid/mouse.c     $(KINCLUDE) $(CFLAGS) -o mouse.o
	$(CC) -c hwi/dd/hid/ps2kbd.c    $(KINCLUDE) $(CFLAGS) -o ps2kbd.o
	$(CC) -c hwi/dd/hid/ps2mouse.c  $(KINCLUDE) $(CFLAGS) -o ps2mouse.o
	$(CC) -c hwi/dd/hid/vsync.c     $(KINCLUDE) $(CFLAGS) -o vsync.o
	$(CC) -c hwi/dd/hid/input.c     $(KINCLUDE) $(CFLAGS) -o input.o
	$(CC) -c hwi/dd/hid/output.c    $(KINCLUDE) $(CFLAGS) -o output.o
	$(CC) -c hwi/dd/hid/screen.c    $(KINCLUDE) $(CFLAGS) -o screen.o
	$(CC) -c hwi/dd/hid/video.c     $(KINCLUDE) $(CFLAGS) -o video.o


	# x86 initialization
	$(CC) -c hwi/init/x86/x86init.c  $(KINCLUDE) $(CFLAGS) -o x86init.o

	# x86 boot
	$(NASM) hwi/init/x86/boot.asm -I hwi/init/x86/ -f elf -o boot.o



	#(CC) -c protocol ...



## Step2 link-kernel-image  - Linking the kernel image.
#kernel-image-link:

link-kernel:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	$(LD) $(LDFLAGS) -T link.ld -o KERNEL.BIN $(OBJECTS)    



clean:
	rm -rf *.o   
	
	



