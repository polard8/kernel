# Compiling KERNEL.BIN
# 2020 - Fred Nora.

ARCH ?= x86
#ARCH ?= x86_64



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
	nasm init/x86/boot.asm -I init/x86/ -f elf -o boot.o

	# main (Architechture independent)
	gcc -c init/main.c $(KINCLUDE) $(CFLAGS) -o main.o

	# x86 initialization
	gcc -c init/x86/x86init.c  $(KINCLUDE) $(CFLAGS) -o x86init.o


	#
	# sysio/hal
	#

	gcc -c sysio/hal/hal.c                $(KINCLUDE) $(CFLAGS) -o hal.o
	gcc -c sysio/hal/arch/detect.c        $(KINCLUDE) $(CFLAGS) -o detect.o
	gcc -c sysio/hal/arch/amd/cpuamd.c    $(KINCLUDE) $(CFLAGS) -o cpuamd.o
	gcc -c sysio/hal/arch/x86/portsx86.c  $(KINCLUDE) $(CFLAGS) -o portsx86.o
	gcc -c sysio/hal/arch/x86/syscall.c   $(KINCLUDE) $(CFLAGS) -o syscall.o
	gcc -c sysio/hal/arch/x86/x86.c       $(KINCLUDE) $(CFLAGS) -o x86.o


	# x86
	gcc -c  sysmk/ps/arch/x86/x86cont.c   $(KINCLUDE)  $(CFLAGS) -o x86cont.o
	gcc -c  sysmk/ps/arch/x86/x86fault.c  $(KINCLUDE)  $(CFLAGS) -o x86fault.o
	gcc -c  sysmk/ps/arch/x86/x86start.c  $(KINCLUDE)  $(CFLAGS) -o x86start.o
	
	# ps/action
	gcc -c  sysmk/ps/action/dispatch.c  $(KINCLUDE)  $(CFLAGS) -o dispatch.o
	gcc -c  sysmk/ps/action/pheap.c     $(KINCLUDE)  $(CFLAGS) -o pheap.o
	gcc -c  sysmk/ps/action/process.c   $(KINCLUDE)  $(CFLAGS) -o process.o
	gcc -c  sysmk/ps/action/clone.c      $(KINCLUDE)  $(CFLAGS) -o clone.o
	gcc -c  sysmk/ps/action/queue.c     $(KINCLUDE)  $(CFLAGS) -o queue.o
	gcc -c  sysmk/ps/action/spawn.c     $(KINCLUDE)  $(CFLAGS) -o spawn.o
	gcc -c  sysmk/ps/action/tasks.c     $(KINCLUDE)  $(CFLAGS) -o tasks.o
	gcc -c  sysmk/ps/action/theap.c     $(KINCLUDE)  $(CFLAGS) -o theap.o
	gcc -c  sysmk/ps/action/thread.c    $(KINCLUDE)  $(CFLAGS) -o thread.o
	gcc -c  sysmk/ps/action/threadi.c   $(KINCLUDE)  $(CFLAGS) -o threadi.o
	gcc -c  sysmk/ps/action/ts.c        $(KINCLUDE)  $(CFLAGS) -o ts.o
	gcc -c  sysmk/ps/action/tstack.c    $(KINCLUDE)  $(CFLAGS) -o tstack.o
	gcc -c sysmk/ps/action/execve.c  $(KINCLUDE) $(CFLAGS) -o execve.o

	# ps/ipc
	gcc -c  sysmk/ps/ipc/callfar.c  $(KINCLUDE)  $(CFLAGS) -o callfar.o
	gcc -c  sysmk/ps/ipc/callout.c  $(KINCLUDE)  $(CFLAGS) -o callout.o
	gcc -c  sysmk/ps/ipc/ipc.c      $(KINCLUDE)  $(CFLAGS) -o ipc.o
	gcc -c  sysmk/ps/ipc/ipccore.c  $(KINCLUDE)  $(CFLAGS) -o ipccore.o
	gcc -c  sysmk/ps/ipc/sem.c      $(KINCLUDE)  $(CFLAGS) -o sem.o

	# ps/mm
	gcc -c  sysmk/ps/mm/x86/memory.c  $(KINCLUDE) $(CFLAGS) -o memory.o
	gcc -c  sysmk/ps/mm/x86/mminfo.c  $(KINCLUDE) $(CFLAGS) -o mminfo.o
	gcc -c  sysmk/ps/mm/x86/mmpool.c  $(KINCLUDE) $(CFLAGS) -o mmpool.o
	gcc -c  sysmk/ps/mm/x86/pages.c   $(KINCLUDE) $(CFLAGS) -o pages.o

	# ps/sched
	gcc -c  sysmk/ps/sched/preempt.c   $(KINCLUDE) $(CFLAGS) -o preempt.o
	gcc -c  sysmk/ps/sched/priority.c  $(KINCLUDE) $(CFLAGS) -o priority.o
	gcc -c  sysmk/ps/sched/sched.c     $(KINCLUDE) $(CFLAGS) -o sched.o
	gcc -c  sysmk/ps/sched/schedi.c    $(KINCLUDE) $(CFLAGS) -o schedi.o


	# mk
	gcc -c sysmk/create.c  $(KINCLUDE)  $(CFLAGS) -o create.o
	gcc -c sysmk/mk.c      $(KINCLUDE)  $(CFLAGS) -o mk.o


	#kernel
	gcc -c  request.c  $(KINCLUDE) $(CFLAGS) -o request.o
	gcc -c  panic.c    $(KINCLUDE) $(CFLAGS) -o panic.o
	gcc -c  reboot.c   $(KINCLUDE) $(CFLAGS) -o reboot.o


	# fs
	gcc -c sci/fs/pipe.c    $(KINCLUDE) $(CFLAGS) -o pipe.o

	# libcore
	gcc -c syslib/libcore/ctype.c   $(KINCLUDE) $(CFLAGS) -o ctype.o
	gcc -c syslib/libcore/kstdio.c  $(KINCLUDE) $(CFLAGS) -o kstdio.o
	gcc -c syslib/libcore/stdlib.c  $(KINCLUDE) $(CFLAGS) -o stdlib.o
	gcc -c syslib/libcore/string.c  $(KINCLUDE) $(CFLAGS) -o string.o
	gcc -c syslib/libcore/unistd.c  $(KINCLUDE) $(CFLAGS) -o unistd.o

	# rtc
	gcc -c sysio/kdrivers/rtc/rtc.c     $(KINCLUDE) $(CFLAGS) -o rtc.o

	# serial
	gcc -c sysio/kdrivers/serial/serial.c  $(KINCLUDE) $(CFLAGS) -o serial.o


	# x86
	gcc -c sysio/kdrivers/arch/x86/apic.c  $(KINCLUDE) $(CFLAGS) -o apic.o
	gcc -c sysio/kdrivers/arch/x86/pic.c   $(KINCLUDE) $(CFLAGS) -o pic.o
	gcc -c sysio/kdrivers/arch/x86/pit.c   $(KINCLUDE) $(CFLAGS) -o pit.o
	

	# ahci 
	gcc -c sysio/kdrivers/ahci/ahci.c  $(KINCLUDE) $(CFLAGS) -o ahci.o
	
		
	# ide
	gcc -c sysio/kdrivers/ide/hdd.c      $(KINCLUDE) $(CFLAGS) -o hdd.o
	gcc -c sysio/kdrivers/ide/ata.c      $(KINCLUDE) $(CFLAGS) -o ata.o
	gcc -c sysio/kdrivers/ide/atainit.c  $(KINCLUDE) $(CFLAGS) -o atainit.o
	gcc -c sysio/kdrivers/ide/atairq.c   $(KINCLUDE) $(CFLAGS) -o atairq.o
	gcc -c sysio/kdrivers/ide/atapci.c   $(KINCLUDE) $(CFLAGS) -o atapci.o	
	gcc -c sysio/kdrivers/ide/atadma.c   $(KINCLUDE) $(CFLAGS) -o atadma.o	


	# net
	gcc -c net/network/nicintel.c  $(KINCLUDE) $(CFLAGS) -o nicintel.o
	gcc -c net/network/channel.c   $(KINCLUDE) $(CFLAGS) -o channel.o
	gcc -c net/network/network.c   $(KINCLUDE) $(CFLAGS) -o network.o
	gcc -c net/socket.c            $(KINCLUDE) $(CFLAGS) -o socket.o	


	# pci
	gcc -c sysio/kdrivers/pci/pci.c      $(KINCLUDE) $(CFLAGS) -o pci.o
	gcc -c sysio/kdrivers/pci/pciscan.c  $(KINCLUDE) $(CFLAGS) -o pciscan.o
	gcc -c sysio/kdrivers/pci/pciinfo.c  $(KINCLUDE) $(CFLAGS) -o pciinfo.o


	# tty
	gcc -c sysio/kdrivers/tty/console.c $(KINCLUDE) $(CFLAGS) -o cedge.o
	gcc -c sysio/kdrivers/tty/tty.c     $(KINCLUDE) $(CFLAGS) -o tty.o
	gcc -c sysio/kdrivers/tty/pty.c     $(KINCLUDE) $(CFLAGS) -o pty.o
	gcc -c sysio/kdrivers/tty/vt.c  $(KINCLUDE) $(CFLAGS) -o vt.o

	# usb
	gcc -c sysio/kdrivers/usb/usb.c   $(KINCLUDE) $(CFLAGS) -o usb.o
	
	
	# devices
	gcc -c sysio/devmgr.c  $(KINCLUDE) $(CFLAGS) -o devmgr.o


	# fs
	gcc -c sci/fs/fs.c      $(KINCLUDE) $(CFLAGS) -o fs.o
	gcc -c sci/fs/vfs.c     $(KINCLUDE) $(CFLAGS) -o vfs.o
	gcc -c sci/fs/cf.c      $(KINCLUDE) $(CFLAGS) -o cf.o
	gcc -c sci/fs/read.c    $(KINCLUDE) $(CFLAGS) -o read.o
	gcc -c sci/fs/write.c   $(KINCLUDE) $(CFLAGS) -o write.o
	gcc -c sci/fs/search.c  $(KINCLUDE) $(CFLAGS) -o search.o
	gcc -c sci/fs/format.c  $(KINCLUDE) $(CFLAGS) -o format.o
	

	# storage
	gcc -c syssm/storage/storage.c   $(KINCLUDE) $(CFLAGS) -o storage.o


	# system
	gcc -c syssm/system/abort.c    $(KINCLUDE) $(CFLAGS) -o abort.o
	gcc -c syssm/system/info.c     $(KINCLUDE) $(CFLAGS) -o info.o
	gcc -c syssm/system/init.c     $(KINCLUDE) $(CFLAGS) -o init.o
	gcc -c syssm/system/install.c  $(KINCLUDE) $(CFLAGS) -o install.o
	gcc -c syssm/system/modules.c  $(KINCLUDE) $(CFLAGS) -o modules.o
	gcc -c syssm/system/runtime.c  $(KINCLUDE) $(CFLAGS) -o runtime.o
	gcc -c syssm/system/signal.c   $(KINCLUDE) $(CFLAGS) -o signal.o
	gcc -c syssm/system/sm.c       $(KINCLUDE) $(CFLAGS) -o sm.o
	gcc -c syssm/system/system.c   $(KINCLUDE) $(CFLAGS) -o system.o


	#debug
	gcc -c syssm/debug/debug.c  $(KINCLUDE) $(CFLAGS) -o debug.o

	#io
	gcc -c sysio/io.c  $(KINCLUDE) $(CFLAGS) -o io.o

	#ob
	gcc -c syssm/ob/object.c  $(KINCLUDE) $(CFLAGS) -o object.o


	# Window Manager.
	gcc -c wm/kgwm.c    $(KINCLUDE) $(CFLAGS) -o kgwm.o
	gcc -c wm/wm.c      $(KINCLUDE) $(CFLAGS) -o wm.o
	gcc -c wm/logon.c   $(KINCLUDE) $(CFLAGS) -o logon.o
	gcc -c wm/logoff.c  $(KINCLUDE) $(CFLAGS) -o logoff.o
	

	# Window Server.
	gcc -c ws/bg.c       $(KINCLUDE) $(CFLAGS) -o bg.o
	gcc -c ws/bmp.c      $(KINCLUDE) $(CFLAGS) -o bmp.o
	gcc -c ws/button.c   $(KINCLUDE) $(CFLAGS) -o button.o
	gcc -c ws/char.c     $(KINCLUDE) $(CFLAGS) -o char.o
	gcc -c ws/createw.c  $(KINCLUDE) $(CFLAGS) -o createw.o
	gcc -c ws/dtext.c    $(KINCLUDE) $(CFLAGS) -o dtext.o
	gcc -c ws/font.c     $(KINCLUDE) $(CFLAGS) -o font.o
	gcc -c ws/grid.c     $(KINCLUDE) $(CFLAGS) -o grid.o
	gcc -c ws/line.c     $(KINCLUDE) $(CFLAGS) -o line.o
	gcc -c ws/menu.c     $(KINCLUDE) $(CFLAGS) -o menu.o
	gcc -c ws/menubar.c  $(KINCLUDE) $(CFLAGS) -o menubar.o
	gcc -c ws/pixel.c     $(KINCLUDE) $(CFLAGS) -o pixel.o
	gcc -c ws/rect.c      $(KINCLUDE) $(CFLAGS) -o rect.o
	gcc -c ws/sbar.c      $(KINCLUDE) $(CFLAGS) -o sbar.o
	gcc -c ws/toolbar.c   $(KINCLUDE) $(CFLAGS) -o toolbar.o
	gcc -c ws/input.c     $(KINCLUDE) $(CFLAGS) -o input.o
	gcc -c ws/output.c    $(KINCLUDE) $(CFLAGS) -o output.o
	gcc -c ws/terminal.c  $(KINCLUDE) $(CFLAGS) -o terminal.o
	gcc -c ws/kgws.c      $(KINCLUDE) $(CFLAGS) -o kgws.o
	gcc -c ws/xproc.c   $(KINCLUDE) $(CFLAGS) -o xproc.o
	gcc -c ws/screen.c  $(KINCLUDE) $(CFLAGS) -o screen.o
	gcc -c ws/video.c   $(KINCLUDE) $(CFLAGS) -o video.o
	gcc -c ws/vsync.c   $(KINCLUDE) $(CFLAGS) -o vsync.o
	gcc -c ws/i8042.c     $(KINCLUDE) $(CFLAGS) -o i8042.o
	gcc -c ws/keyboard.c  $(KINCLUDE) $(CFLAGS) -o keyboard.o
	gcc -c ws/mouse.c     $(KINCLUDE) $(CFLAGS) -o mouse.o
	gcc -c ws/ps2kbd.c    $(KINCLUDE) $(CFLAGS) -o ps2kbd.o
	gcc -c ws/ps2mouse.c  $(KINCLUDE) $(CFLAGS) -o ps2mouse.o
	gcc -c ws/ldisc.c     $(KINCLUDE) $(CFLAGS) -o ldisc.o


	# Security
	gcc -c security/desktop.c   $(KINCLUDE) $(CFLAGS) -o desktop.o
	gcc -c security/room.c      $(KINCLUDE) $(CFLAGS) -o room.o
	gcc -c security/userenv.c   $(KINCLUDE) $(CFLAGS) -o userenv.o
	gcc -c security/usession.c  $(KINCLUDE) $(CFLAGS) -o usession.o


	#
	#  /sci - System Call Interface.
	#
	
	gcc -c sci/gde_serv.c $(KINCLUDE) $(CFLAGS) -o gde_serv.o
	
	# services.
	gcc -c sci/sys/sys.c   $(KINCLUDE) $(CFLAGS) -o sys.o
	gcc -c sysio/sysio.c   $(KINCLUDE) $(CFLAGS) -o sysio.o
	gcc -c syslib/syslib.c $(KINCLUDE) $(CFLAGS) -o syslib.o
	gcc -c sysmk/sysmk.c   $(KINCLUDE) $(CFLAGS) -o sysmk.o
	gcc -c syssm/syssm.c   $(KINCLUDE) $(CFLAGS) -o syssm.o
	

## Step2 link-kernel-image  - Linking the kernel image.
#kernel-image-link:

link-kernel:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	ld $(LDFLAGS) -T link.ld -o KERNEL.BIN $(OBJECTS)   
#	mv KERNEL.BIN ../bin/boot/

clean:
	rm -rf *.o   
	
	



