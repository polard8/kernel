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
	SYS_OBJECTS := sys.o pump.o syslib.o sysmk.o syssm.o   


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
	# net
	#
	
	# three layers support:
	# socket, protocol and network interface.

	$(CC) -c net/socket/socket.c  $(KINCLUDE) $(CFLAGS) -o socket.o
	#$(CC) -c net/protocol ...
	$(CC) -c net/network/channel.c   $(KINCLUDE) $(CFLAGS) -o channel.o
	$(CC) -c net/network/network.c   $(KINCLUDE) $(CFLAGS) -o network.o


	##
	## SCI - System Call Interface
	##

	#  /sci - System Call Interface.
	$(CC) -c sci/gde_serv.c $(KINCLUDE) $(CFLAGS) -o gde_serv.o
	$(CC) -c sci/sys/sys.c   $(KINCLUDE) $(CFLAGS) -o sys.o


	# fs
	$(CC) -c fs/cf.c      $(KINCLUDE) $(CFLAGS) -o cf.o
	$(CC) -c fs/format.c  $(KINCLUDE) $(CFLAGS) -o format.o
	$(CC) -c fs/fs.c      $(KINCLUDE) $(CFLAGS) -o fs.o
	$(CC) -c fs/pipe.c    $(KINCLUDE) $(CFLAGS) -o pipe.o
	$(CC) -c fs/read.c    $(KINCLUDE) $(CFLAGS) -o read.o
	$(CC) -c fs/search.c  $(KINCLUDE) $(CFLAGS) -o search.o
	$(CC) -c fs/write.c   $(KINCLUDE) $(CFLAGS) -o write.o

	# fs/vfs
	$(CC) -c fs/vfs/vfs.c     $(KINCLUDE) $(CFLAGS) -o vfs.o

	# Security
	$(CC) -c security/desktop.c   $(KINCLUDE) $(CFLAGS) -o desktop.o
	$(CC) -c security/room.c      $(KINCLUDE) $(CFLAGS) -o room.o
	$(CC) -c security/userenv.c   $(KINCLUDE) $(CFLAGS) -o userenv.o
	$(CC) -c security/usession.c  $(KINCLUDE) $(CFLAGS) -o usession.o


	# storage
	$(CC) -c sm/storage/storage.c   $(KINCLUDE) $(CFLAGS) -o storage.o

	# system
	$(CC) -c sm/system/abort.c    $(KINCLUDE) $(CFLAGS) -o abort.o
	$(CC) -c sm/system/info.c     $(KINCLUDE) $(CFLAGS) -o info.o
	$(CC) -c sm/system/init.c     $(KINCLUDE) $(CFLAGS) -o init.o
	$(CC) -c sm/system/install.c  $(KINCLUDE) $(CFLAGS) -o install.o
	$(CC) -c sm/system/modules.c  $(KINCLUDE) $(CFLAGS) -o modules.o
	$(CC) -c sm/system/runtime.c  $(KINCLUDE) $(CFLAGS) -o runtime.o
	$(CC) -c sm/system/sm.c       $(KINCLUDE) $(CFLAGS) -o sm.o
	$(CC) -c sm/system/system.c   $(KINCLUDE) $(CFLAGS) -o system.o


	# debug
	$(CC) -c sm/debug/debug.c  $(KINCLUDE) $(CFLAGS) -o debug.o

	# ob
	$(CC) -c sm/ob/object.c  $(KINCLUDE) $(CFLAGS) -o object.o

	$(CC) -c sm/syssm.c   $(KINCLUDE) $(CFLAGS) -o syssm.o


	# Window Manager.
	$(CC) -c wm/kgwm.c    $(KINCLUDE) $(CFLAGS) -o kgwm.o
	$(CC) -c wm/logoff.c  $(KINCLUDE) $(CFLAGS) -o logoff.o
	$(CC) -c wm/logon.c   $(KINCLUDE) $(CFLAGS) -o logon.o
	$(CC) -c wm/wm.c      $(KINCLUDE) $(CFLAGS) -o wm.o


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
	$(CC) -c ws/ldisc.c     $(KINCLUDE) $(CFLAGS) -o ldisc.o


	# ps/action
	$(CC) -c  ps/action/dispatch.c  $(KINCLUDE)  $(CFLAGS) -o dispatch.o
	$(CC) -c  ps/action/pheap.c     $(KINCLUDE)  $(CFLAGS) -o pheap.o
	$(CC) -c  ps/action/process.c   $(KINCLUDE)  $(CFLAGS) -o process.o
	$(CC) -c  ps/action/clone.c     $(KINCLUDE)  $(CFLAGS) -o clone.o
	$(CC) -c  ps/action/queue.c     $(KINCLUDE)  $(CFLAGS) -o queue.o
	$(CC) -c  ps/action/spawn.c     $(KINCLUDE)  $(CFLAGS) -o spawn.o
	$(CC) -c  ps/action/tasks.c     $(KINCLUDE)  $(CFLAGS) -o tasks.o
	$(CC) -c  ps/action/theap.c     $(KINCLUDE)  $(CFLAGS) -o theap.o
	$(CC) -c  ps/action/thread.c    $(KINCLUDE)  $(CFLAGS) -o thread.o
	$(CC) -c  ps/action/threadi.c   $(KINCLUDE)  $(CFLAGS) -o threadi.o
	$(CC) -c  ps/action/ts.c        $(KINCLUDE)  $(CFLAGS) -o ts.o
	$(CC) -c  ps/action/tstack.c    $(KINCLUDE)  $(CFLAGS) -o tstack.o
	$(CC) -c  ps/action/execve.c    $(KINCLUDE)  $(CFLAGS) -o execve.o

	# ps/ipc
	$(CC) -c  ps/ipc/callfar.c  $(KINCLUDE)  $(CFLAGS) -o callfar.o
	$(CC) -c  ps/ipc/callout.c  $(KINCLUDE)  $(CFLAGS) -o callout.o
	$(CC) -c  ps/ipc/ipc.c      $(KINCLUDE)  $(CFLAGS) -o ipc.o
	$(CC) -c  ps/ipc/ipccore.c  $(KINCLUDE)  $(CFLAGS) -o ipccore.o
	$(CC) -c  ps/ipc/sem.c      $(KINCLUDE)  $(CFLAGS) -o sem.o

	# ps/sched
	$(CC) -c  ps/sched/preempt.c   $(KINCLUDE) $(CFLAGS) -o preempt.o
	$(CC) -c  ps/sched/priority.c  $(KINCLUDE) $(CFLAGS) -o priority.o
	$(CC) -c  ps/sched/sched.c     $(KINCLUDE) $(CFLAGS) -o sched.o
	$(CC) -c  ps/sched/schedi.c    $(KINCLUDE) $(CFLAGS) -o schedi.o

	# ps -x86 - falling angels.
	$(CC) -c ps/x86/x86cont.c   $(KINCLUDE)  $(CFLAGS) -o x86cont.o
	$(CC) -c ps/x86/x86fault.c  $(KINCLUDE)  $(CFLAGS) -o x86fault.o
	$(CC) -c ps/x86/x86start.c  $(KINCLUDE)  $(CFLAGS) -o x86start.o
	$(CC) -c ps/x86/memory.c    $(KINCLUDE)  $(CFLAGS) -o memory.o
	$(CC) -c ps/x86/mminfo.c    $(KINCLUDE)  $(CFLAGS) -o mminfo.o
	$(CC) -c ps/x86/mmpool.c    $(KINCLUDE)  $(CFLAGS) -o mmpool.o
	$(CC) -c ps/x86/pages.c     $(KINCLUDE)  $(CFLAGS) -o pages.o

	# ps
	$(CC) -c ps/create.c  $(KINCLUDE)  $(CFLAGS) -o create.o
	$(CC) -c ps/mk.c      $(KINCLUDE)  $(CFLAGS) -o mk.o
	$(CC) -c ps/sysmk.c   $(KINCLUDE)  $(CFLAGS) -o sysmk.o


	##
	## ==== HWI - Hardware Interface ==== 
	##

	$(CC) -c hwi/io.c    $(KINCLUDE) $(CFLAGS) -o io.o
	$(CC) -c hwi/pump.c  $(KINCLUDE) $(CFLAGS) -o pump.o


	# klib
	$(CC) -c klib/ctype.c   $(KINCLUDE) $(CFLAGS) -o ctype.o
	$(CC) -c klib/kstdio.c  $(KINCLUDE) $(CFLAGS) -o kstdio.o
	$(CC) -c klib/signal.c  $(KINCLUDE) $(CFLAGS) -o signal.o
	$(CC) -c klib/stdlib.c  $(KINCLUDE) $(CFLAGS) -o stdlib.o
	$(CC) -c klib/string.c  $(KINCLUDE) $(CFLAGS) -o string.o
	$(CC) -c klib/syslib.c  $(KINCLUDE) $(CFLAGS) -o syslib.o
	$(CC) -c klib/unistd.c  $(KINCLUDE) $(CFLAGS) -o unistd.o


	# dd
	$(CC) -c hwi/dd/devmgr.c  $(KINCLUDE) $(CFLAGS) -o devmgr.o


	#
	# ==== nhid ====
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
	$(CC) -c hwi/dd/hid/tty/console.c $(KINCLUDE) $(CFLAGS) -o cedge.o
	$(CC) -c hwi/dd/hid/tty/pty.c     $(KINCLUDE) $(CFLAGS) -o pty.o
	$(CC) -c hwi/dd/hid/tty/tty.c     $(KINCLUDE) $(CFLAGS) -o tty.o
	$(CC) -c hwi/dd/hid/tty/vt.c      $(KINCLUDE) $(CFLAGS) -o vt.o

	# ws
	$(CC) -c hwi/dd/hid/ws/i8042.c     $(KINCLUDE) $(CFLAGS) -o i8042.o
	$(CC) -c hwi/dd/hid/ws/keyboard.c  $(KINCLUDE) $(CFLAGS) -o keyboard.o
	$(CC) -c hwi/dd/hid/ws/mouse.c     $(KINCLUDE) $(CFLAGS) -o mouse.o
	$(CC) -c hwi/dd/hid/ws/ps2kbd.c    $(KINCLUDE) $(CFLAGS) -o ps2kbd.o
	$(CC) -c hwi/dd/hid/ws/ps2mouse.c  $(KINCLUDE) $(CFLAGS) -o ps2mouse.o
	$(CC) -c hwi/dd/hid/ws/vsync.c     $(KINCLUDE) $(CFLAGS) -o vsync.o


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
	
	



