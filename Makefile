# Compiling Gramado on Manjaro Linux.
# BSD License
# SPDX-License-Identifier: GPL-3.0+
# History:
#     2018 - Created by Matheus Castello.
#     2019 - Fred Nora.
#     2019 - Luciano Gonçalez.


VERSION = 1
PATCHLEVEL = 32
SUBLEVEL = 0
EXTRAVERSION = 0
NAME = Light



KERNELVERSION = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)

export KBUILD_IMAGE ?= KERNEL.BIN 


srctree := .
objtree := .
src := $(srctree)
obj := $(objtree)
 
 

# First of all, lemme discribe this documment!
# We just have two parts. The kernel and the extra stuff.

## The kernel stuff.
## Step1 KERNEL.BIN         - Creating the kernel image.
## Step2 kernel-image-link  - Linking the kernel image.
## Step3 /mnt/gramadovhd    - Creating the directory to mount the VHD.
## Step4 vhd-create         - Creating a VHD in Assembly language.
## Step5 vhd-mount          - Mounting the VHD.
## Step6 vhd-copy-files     - Copying files into the mounted VHD.
## Step7 vhd-unmount        - Unmounting the VHD.
## Step8 clean              - Deleting the object files.           

## The extra stuff.
## 1) ISO support.
## 2) HDD support.
## 3) VM support.
## 4) Serial debug support.
## 5) Clean files support.
## 6) Usage support.


# That's our default target when none is given on the command line
PHONY := _all
_all: all

	@echo "That's all!"


ARCH ?= x86


# Make variables (CC, etc...)
#AS		= as
#LD		= ld
#CC		= gcc
#AR		= ar
#OBJCOPY		= objcopy
#OBJDUMP		= objdump
#LEX		= flex
#YACC	= bison
#PERL		= perl
#PYTHON		= python
#PYTHON2		= python2
#PYTHON3		= python3
#RUBY		= ruby






# Setup disk:
# For now we're using IDE disk on primary master.
# You can setup this options in:
# arch/x86/boot/bl/include/config/config.h for the boot loader and
# include/kernel/config/config.h for the kernel.



#tests
CFLAGS = -m32 \
	--std=gnu89 \
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


#TODO TEM O NASM TAMBEM.
KINCLUDE = -I kernel/include/


##
## Defines
##

#
# DEFINES =  -DGRAMADO_VERSION=$(VERSION) \
#		-DGRAMADO_PATCHLEVEL=$(PATCHLEVEL) \
#		-DGRAMADO_SUBLEVEL=$(SUBLEVEL) \
#		-DGRAMADO_EXTRAVERSION=\"$(EXTRAVERSION)\" \
#		-DGRAMAD0_NAME=\"$(NAME)\"


##
## Objects
##

ifeq ($(ARCH),x86)

	#deveria ser headx86.o
	ENTRY_OBJECTS := boot.o main.o x86main.o 

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

#
# Begin.
#

## =============================================================================
## The kernel stuff.
## Step1 KERNEL.BIN         - Creating the kernel image.
## Step2 kernel-image-link  - Linking the kernel image.
## Step3 /mnt/gramadovhd    - Creating the directory to mount the VHD.
## Step4 vhd-create         - Creating a VHD in Assembly language.
## Step5 vhd-mount          - Mounting the VHD.
## Step6 vhd-copy-files     - Copying files into the mounted VHD.
## Step7 vhd-unmount        - Unmounting the VHD.
## Step8 clean              - Deleting the object files.           

PHONY := all

all: KERNEL.BIN kernel-image-link /mnt/gramadovhd  vhd-create vhd-mount vhd-copy-files vhd-unmount clean


	#Giving permitions to run ./run hahaha
	chmod 755 ./run

	@echo "Gramado $(VERSION) $(PATCHLEVEL) $(SUBLEVEL) $(EXTRAVERSION) $(NAME) "
	@echo "Arch x86"


## Step1 KERNEL.BIN         - Creating the kernel image.
KERNEL.BIN: 
	@echo "================================="
	@echo "(Step 1) Creating the kernel image ..."

	# /entry
	
	nasm kernel/sci/arch/x86/entry/head/boot.asm -I kernel/sci/arch/x86/entry/head/ -f elf -o boot.o

	gcc -c kernel/sci/arch/x86/entry/x86main.c  $(KINCLUDE) $(CFLAGS) -o x86main.o
	
    #main
	gcc -c kernel/main.c $(KINCLUDE) $(CFLAGS) -o main.o

	# /hal
	gcc -c kernel/sysio/hal/hal.c                $(KINCLUDE) $(CFLAGS) -o hal.o
	gcc -c kernel/sysio/hal/arch/detect.c        $(KINCLUDE) $(CFLAGS) -o detect.o
	gcc -c kernel/sysio/hal/arch/amd/cpuamd.c    $(KINCLUDE) $(CFLAGS) -o cpuamd.o
	gcc -c kernel/sysio/hal/arch/x86/portsx86.c  $(KINCLUDE) $(CFLAGS) -o portsx86.o
	gcc -c kernel/sysio/hal/arch/x86/syscall.c   $(KINCLUDE) $(CFLAGS) -o syscall.o
	gcc -c kernel/sysio/hal/arch/x86/x86.c       $(KINCLUDE) $(CFLAGS) -o x86.o

	# /mk
	gcc -c  kernel/sysmk/mk.c $(KINCLUDE)  $(CFLAGS) -o mk.o

	# /ps/arch
	gcc -c  kernel/sysmk/ps/arch/x86/x86cont.c   $(KINCLUDE)  $(CFLAGS) -o x86cont.o
	gcc -c  kernel/sysmk/ps/arch/x86/x86fault.c  $(KINCLUDE)  $(CFLAGS) -o x86fault.o
	gcc -c  kernel/sysmk/ps/arch/x86/x86start.c  $(KINCLUDE)  $(CFLAGS) -o x86start.o

	# /ps/action
	gcc -c  kernel/sysmk/ps/action/dispatch.c  $(KINCLUDE)  $(CFLAGS) -o dispatch.o
	gcc -c  kernel/sysmk/ps/action/pheap.c     $(KINCLUDE)  $(CFLAGS) -o pheap.o
	
	gcc -c  kernel/sysmk/ps/action/process.c   $(KINCLUDE)  $(CFLAGS) -o process.o
	gcc -c  kernel/sysmk/ps/action/clone.c      $(KINCLUDE)  $(CFLAGS) -o clone.o
	
	gcc -c  kernel/sysmk/ps/action/queue.c     $(KINCLUDE)  $(CFLAGS) -o queue.o
	gcc -c  kernel/sysmk/ps/action/spawn.c     $(KINCLUDE)  $(CFLAGS) -o spawn.o
	gcc -c  kernel/sysmk/ps/action/tasks.c     $(KINCLUDE)  $(CFLAGS) -o tasks.o
	gcc -c  kernel/sysmk/ps/action/theap.c     $(KINCLUDE)  $(CFLAGS) -o theap.o
	gcc -c  kernel/sysmk/ps/action/thread.c    $(KINCLUDE)  $(CFLAGS) -o thread.o
	gcc -c  kernel/sysmk/ps/action/threadi.c   $(KINCLUDE)  $(CFLAGS) -o threadi.o
	gcc -c  kernel/sysmk/ps/action/ts.c        $(KINCLUDE)  $(CFLAGS) -o ts.o
	gcc -c  kernel/sysmk/ps/action/tstack.c    $(KINCLUDE)  $(CFLAGS) -o tstack.o

	# /ps/ipc
	gcc -c  kernel/sysmk/ps/ipc/callfar.c  $(KINCLUDE)  $(CFLAGS) -o callfar.o
	gcc -c  kernel/sysmk/ps/ipc/callout.c  $(KINCLUDE)  $(CFLAGS) -o callout.o
	gcc -c  kernel/sysmk/ps/ipc/ipc.c      $(KINCLUDE)  $(CFLAGS) -o ipc.o
	gcc -c  kernel/sysmk/ps/ipc/ipccore.c  $(KINCLUDE)  $(CFLAGS) -o ipccore.o
	gcc -c  kernel/sysmk/ps/ipc/sem.c      $(KINCLUDE)  $(CFLAGS) -o sem.o


	# /ps/mm (memory manager)

	#x86
	gcc -c  kernel/sysmk/ps/mm/x86/memory.c  $(KINCLUDE) $(CFLAGS) -o memory.o
	gcc -c  kernel/sysmk/ps/mm/x86/mminfo.c  $(KINCLUDE) $(CFLAGS) -o mminfo.o
	gcc -c  kernel/sysmk/ps/mm/x86/mmpool.c  $(KINCLUDE) $(CFLAGS) -o mmpool.o
	gcc -c  kernel/sysmk/ps/mm/x86/pages.c   $(KINCLUDE) $(CFLAGS) -o pages.o

	#arm

	# /ps/sched
	gcc -c  kernel/sysmk/ps/sched/preempt.c   $(KINCLUDE) $(CFLAGS) -o preempt.o
	gcc -c  kernel/sysmk/ps/sched/priority.c  $(KINCLUDE) $(CFLAGS) -o priority.o
	gcc -c  kernel/sysmk/ps/sched/sched.c     $(KINCLUDE) $(CFLAGS) -o sched.o
	gcc -c  kernel/sysmk/ps/sched/schedi.c    $(KINCLUDE) $(CFLAGS) -o schedi.o

	#sysmk
	gcc -c kernel/sysmk/create.c  $(KINCLUDE)  $(CFLAGS) -o create.o

	#kernel
	gcc -c  kernel/request.c  $(KINCLUDE) $(CFLAGS) -o request.o
	gcc -c  kernel/panic.c    $(KINCLUDE) $(CFLAGS) -o panic.o
	gcc -c  kernel/reboot.c   $(KINCLUDE) $(CFLAGS) -o reboot.o


	# /execve
	gcc -c kernel/syssm/execve/execve.c  $(KINCLUDE) $(CFLAGS) -o execve.o


	# kernel/syslib/libcore
	gcc -c kernel/sci/fs/pipe.c    $(KINCLUDE) $(CFLAGS) -o pipe.o

	gcc -c kernel/syslib/libcore/ctype.c   $(KINCLUDE) $(CFLAGS) -o ctype.o
	gcc -c kernel/syslib/libcore/kstdio.c  $(KINCLUDE) $(CFLAGS) -o kstdio.o
	gcc -c kernel/syslib/libcore/stdlib.c  $(KINCLUDE) $(CFLAGS) -o stdlib.o
	gcc -c kernel/syslib/libcore/string.c  $(KINCLUDE) $(CFLAGS) -o string.o
	gcc -c kernel/syslib/libcore/unistd.c  $(KINCLUDE) $(CFLAGS) -o unistd.o

	# kdrivers rtc
	gcc -c kernel/sysio/kdrivers/rtc/rtc.c     $(KINCLUDE) $(CFLAGS) -o rtc.o

	# kdrivers serial
	gcc -c kernel/sysio/kdrivers/serial/serial.c  $(KINCLUDE) $(CFLAGS) -o serial.o


	# kdrivers x86
	gcc -c kernel/sysio/kdrivers/arch/x86/apic.c  $(KINCLUDE) $(CFLAGS) -o apic.o
	gcc -c kernel/sysio/kdrivers/arch/x86/pic.c   $(KINCLUDE) $(CFLAGS) -o pic.o
	gcc -c kernel/sysio/kdrivers/arch/x86/pit.c   $(KINCLUDE) $(CFLAGS) -o pit.o
	

	# kdrivers/ahci 
	# todo
	gcc -c kernel/sysio/kdrivers/ahci/ahci.c  $(KINCLUDE) $(CFLAGS) -o ahci.o
	
		
	#ide support
	gcc -c kernel/sysio/kdrivers/ide/hdd.c      $(KINCLUDE) $(CFLAGS) -o hdd.o
	gcc -c kernel/sysio/kdrivers/ide/ata.c      $(KINCLUDE) $(CFLAGS) -o ata.o
	gcc -c kernel/sysio/kdrivers/ide/atainit.c  $(KINCLUDE) $(CFLAGS) -o atainit.o
	gcc -c kernel/sysio/kdrivers/ide/atairq.c   $(KINCLUDE) $(CFLAGS) -o atairq.o
	gcc -c kernel/sysio/kdrivers/ide/atapci.c   $(KINCLUDE) $(CFLAGS) -o atapci.o	
	gcc -c kernel/sysio/kdrivers/ide/atadma.c   $(KINCLUDE) $(CFLAGS) -o atadma.o	


	# kdrivers/network

	gcc -c kernel/sysio/kdrivers/network/nicintel.c  $(KINCLUDE) $(CFLAGS) -o nicintel.o



	# net
	gcc -c kernel/net/network/channel.c  $(KINCLUDE) $(CFLAGS) -o channel.o
	gcc -c kernel/net/network/network.c  $(KINCLUDE) $(CFLAGS) -o network.o


	# net - socket - main access point
	gcc -c kernel/net/socket.c   $(KINCLUDE) $(CFLAGS) -o socket.o	


	# kdrivers/pci
	gcc -c kernel/sysio/kdrivers/pci/pci.c      $(KINCLUDE) $(CFLAGS) -o pci.o
	gcc -c kernel/sysio/kdrivers/pci/pciscan.c  $(KINCLUDE) $(CFLAGS) -o pciscan.o
	gcc -c kernel/sysio/kdrivers/pci/pciinfo.c  $(KINCLUDE) $(CFLAGS) -o pciinfo.o



	# kdrivers/tty
	gcc -c kernel/sysio/kdrivers/tty/console.c $(KINCLUDE) $(CFLAGS) -o cedge.o
	gcc -c kernel/sysio/kdrivers/tty/tty.c     $(KINCLUDE) $(CFLAGS) -o tty.o
	gcc -c kernel/sysio/kdrivers/tty/pty.c     $(KINCLUDE) $(CFLAGS) -o pty.o

	gcc -c kernel/sysio/kdrivers/tty/vt.c  $(KINCLUDE) $(CFLAGS) -o vt.o

	# kdrivers/usb
	gcc -c kernel/sysio/kdrivers/usb/usb.c   $(KINCLUDE) $(CFLAGS) -o usb.o
	
	# kdrivers/x
	gcc -c kernel/sysio/kdrivers/x/xproc.c   $(KINCLUDE) $(CFLAGS) -o xproc.o

	# kdrivers/x/video
	gcc -c kernel/sysio/kdrivers/x/video/screen.c  $(KINCLUDE) $(CFLAGS) -o screen.o
	gcc -c kernel/sysio/kdrivers/x/video/video.c   $(KINCLUDE) $(CFLAGS) -o video.o
	gcc -c kernel/sysio/kdrivers/x/video/vsync.c   $(KINCLUDE) $(CFLAGS) -o vsync.o


	# kdrivers/x/i8042
	gcc -c kernel/sysio/kdrivers/x/i8042/i8042.c     $(KINCLUDE) $(CFLAGS) -o i8042.o
	gcc -c kernel/sysio/kdrivers/x/i8042/keyboard.c  $(KINCLUDE) $(CFLAGS) -o keyboard.o
	gcc -c kernel/sysio/kdrivers/x/i8042/mouse.c     $(KINCLUDE) $(CFLAGS) -o mouse.o
	gcc -c kernel/sysio/kdrivers/x/i8042/ps2kbd.c    $(KINCLUDE) $(CFLAGS) -o ps2kbd.o
	gcc -c kernel/sysio/kdrivers/x/i8042/ps2mouse.c  $(KINCLUDE) $(CFLAGS) -o ps2mouse.o
	gcc -c kernel/sysio/kdrivers/x/i8042/ldisc.c     $(KINCLUDE) $(CFLAGS) -o ldisc.o


	# devices/
	gcc -c kernel/sysio/devmgr.c  $(KINCLUDE) $(CFLAGS) -o devmgr.o



	# sci/fs
	gcc -c kernel/sci/fs/fs.c   $(KINCLUDE) $(CFLAGS) -o fs.o
	gcc -c kernel/sci/fs/vfs.c  $(KINCLUDE) $(CFLAGS) -o vfs.o
	gcc -c kernel/sci/fs/cf.c   $(KINCLUDE) $(CFLAGS) -o cf.o
	

	gcc -c kernel/sysio/kservers/fs/read.c    $(KINCLUDE) $(CFLAGS) -o read.o
	gcc -c kernel/sysio/kservers/fs/write.c   $(KINCLUDE) $(CFLAGS) -o write.o
	gcc -c kernel/sysio/kservers/fs/search.c  $(KINCLUDE) $(CFLAGS) -o search.o
	gcc -c kernel/sysio/kservers/fs/format.c  $(KINCLUDE) $(CFLAGS) -o format.o
	






	# /sm
	gcc -c kernel/syssm/execve/sm/init.c    $(KINCLUDE) $(CFLAGS) -o init.o
	gcc -c kernel/syssm/execve/sm/system.c  $(KINCLUDE) $(CFLAGS) -o system.o
	
	gcc -c kernel/syssm/storage/storage.c   $(KINCLUDE) $(CFLAGS) -o storage.o

	gcc -c kernel/syssm/execve/sm/install/install.c  $(KINCLUDE) $(CFLAGS) -o install.o
	gcc -c kernel/syssm/execve/sm/rt/runtime.c       $(KINCLUDE) $(CFLAGS) -o runtime.o
	gcc -c kernel/syssm/execve/sm/sys/abort.c    $(KINCLUDE) $(CFLAGS) -o abort.o
	gcc -c kernel/syssm/execve/sm/sys/info.c     $(KINCLUDE) $(CFLAGS) -o info.o
	gcc -c kernel/syssm/execve/sm/sys/modules.c  $(KINCLUDE) $(CFLAGS) -o modules.o
	gcc -c kernel/syssm/execve/sm/sys/signal.c   $(KINCLUDE) $(CFLAGS) -o signal.o
	gcc -c kernel/syssm/execve/sm/sys/sm.c       $(KINCLUDE) $(CFLAGS) -o sm.o


#debug
	gcc -c kernel/syssm/debug/debug.c  $(KINCLUDE) $(CFLAGS) -o debug.o

#io
	gcc -c kernel/sysio/io.c  $(KINCLUDE) $(CFLAGS) -o io.o

#ob
	gcc -c kernel/syssm/ob/object.c  $(KINCLUDE) $(CFLAGS) -o object.o


	# kservers/kgwm - Kernel Gramado Window Manager.

	gcc -c kernel/sysio/kservers/kgwm/kgwm.c  $(KINCLUDE) $(CFLAGS) -o kgwm.o
	gcc -c kernel/sysio/kservers/kgwm/wm.c    $(KINCLUDE) $(CFLAGS) -o wm.o


	# kservers/kgws - Kernel Gramado Window Server.

	gcc -c kernel/sysio/kservers/kgws/kgws/comp/bg.c       $(KINCLUDE) $(CFLAGS) -o bg.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/bmp.c      $(KINCLUDE) $(CFLAGS) -o bmp.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/button.c   $(KINCLUDE) $(CFLAGS) -o button.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/char.c     $(KINCLUDE) $(CFLAGS) -o char.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/createw.c  $(KINCLUDE) $(CFLAGS) -o createw.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/dtext.c    $(KINCLUDE) $(CFLAGS) -o dtext.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/font.c     $(KINCLUDE) $(CFLAGS) -o font.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/grid.c     $(KINCLUDE) $(CFLAGS) -o grid.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/line.c     $(KINCLUDE) $(CFLAGS) -o line.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/menu.c     $(KINCLUDE) $(CFLAGS) -o menu.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/menubar.c  $(KINCLUDE) $(CFLAGS) -o menubar.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/pixel.c    $(KINCLUDE) $(CFLAGS) -o pixel.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/rect.c     $(KINCLUDE) $(CFLAGS) -o rect.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/sbar.c     $(KINCLUDE) $(CFLAGS) -o sbar.o
	gcc -c kernel/sysio/kservers/kgws/kgws/comp/toolbar.c  $(KINCLUDE) $(CFLAGS) -o toolbar.o

	
	gcc -c kernel/sysio/kservers/kgws/logon/logon.c    $(KINCLUDE) $(CFLAGS) -o logon.o
	gcc -c kernel/sysio/kservers/kgws/logoff/logoff.c  $(KINCLUDE) $(CFLAGS) -o logoff.o

	gcc -c kernel/sysio/kservers/kgws/terminal/input.c     $(KINCLUDE) $(CFLAGS) -o input.o
	gcc -c kernel/sysio/kservers/kgws/terminal/output.c    $(KINCLUDE) $(CFLAGS) -o output.o
	gcc -c kernel/sysio/kservers/kgws/terminal/terminal.c  $(KINCLUDE) $(CFLAGS) -o terminal.o



	#
	# Security
	#


	gcc -c kernel/security/desktop.c   $(KINCLUDE) $(CFLAGS) -o desktop.o
	gcc -c kernel/security/room.c      $(KINCLUDE) $(CFLAGS) -o room.o
	gcc -c kernel/security/userenv.c   $(KINCLUDE) $(CFLAGS) -o userenv.o
	gcc -c kernel/security/usession.c  $(KINCLUDE) $(CFLAGS) -o usession.o



	gcc -c kernel/sysio/kservers/kgws/kgws.c $(KINCLUDE) $(CFLAGS) -o kgws.o



	#
	#  /sci - System Call Interface.
	#
	
	gcc -c kernel/sci/gde_serv.c $(KINCLUDE) $(CFLAGS) -o gde_serv.o
	
	# services.
	gcc -c kernel/sci/sys/sys.c   $(KINCLUDE) $(CFLAGS) -o sys.o
	gcc -c kernel/sysio/sysio.c   $(KINCLUDE) $(CFLAGS) -o sysio.o
	gcc -c kernel/syslib/syslib.c $(KINCLUDE) $(CFLAGS) -o syslib.o
	gcc -c kernel/sysmk/sysmk.c   $(KINCLUDE) $(CFLAGS) -o sysmk.o
	gcc -c kernel/syssm/syssm.c   $(KINCLUDE) $(CFLAGS) -o syssm.o
	
	

## Step2 link-kernel-image  - Linking the kernel image.
kernel-image-link:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	ld -m elf_i386 -T kernel/link.ld -o KERNEL.BIN $(OBJECTS) -Map docs/KERNEL.MAP
	mv KERNEL.BIN bin/boot/



## Step3 /mnt/gramadovhd    - Creating the directory to mount the VHD.
/mnt/gramadovhd:
	@echo "================================="
	@echo "(Step 3) Creating the directory to mount the VHD ..."

	sudo mkdir /mnt/gramadovhd


## Step4 vhd-create         - Creating a VHD in Assembly language.
vhd-create:
	@echo "================================="
	@echo "(Step 4) Creating a VHD in Assembly language ..."

	nasm prek/arch/x86/boot/vhd/main.asm -I prek/arch/x86/boot/vhd/ -o GRAMADO.VHD    
	
	 


## Step5 vhd-mount          - Mounting the VHD.
vhd-mount:
	@echo "================================="
	@echo "(Step 5) Mounting the VHD ..."

	-sudo umount /mnt/gramadovhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadovhd/


## Step6 vhd-copy-files     - Copying files into the mounted VHD.
vhd-copy-files:
	@echo "================================="
	@echo "(Step 6) Copying files into the mounted VHD ..."


	# Create folders in the new mounted disk.
	sudo mkdir /mnt/gramadovhd/BIN
	sudo mkdir /mnt/gramadovhd/BOOT
	sudo mkdir /mnt/gramadovhd/DEV
	sudo mkdir /mnt/gramadovhd/DEV/PTS
	sudo mkdir /mnt/gramadovhd/EFI
	sudo mkdir /mnt/gramadovhd/EFI/BOOT
	sudo mkdir /mnt/gramadovhd/ETC
	sudo mkdir /mnt/gramadovhd/GARDEN
	sudo mkdir /mnt/gramadovhd/GARDEN/BIN
	sudo mkdir /mnt/gramadovhd/HOME
	sudo mkdir /mnt/gramadovhd/LIB
	sudo mkdir /mnt/gramadovhd/MNT
	sudo mkdir /mnt/gramadovhd/SBIN
	sudo mkdir /mnt/gramadovhd/TMP


#
# ======== Files in the root dir. ========
#

# bin/boot
	sudo cp bin/boot/BM.BIN       /mnt/gramadovhd
	sudo cp bin/boot/BL.BIN       /mnt/gramadovhd

	sudo cp init/base/bin/INIT2.BIN      /mnt/gramadovhd
	sudo cp init/base/bin/INIT2.BIN      /mnt/gramadovhd/BOOT
	

#base
	sudo cp base/GRAMADO.TXT        /mnt/gramadovhd
	

#base dev files.
	-sudo cp base/dev/LOOP0           /mnt/gramadovhd
	-sudo cp base/dev/NULL            /mnt/gramadovhd
	-sudo cp base/dev/SDA             /mnt/gramadovhd

	
#base ini files
	sudo cp base/ini/GUI.INI         /mnt/gramadovhd
	sudo cp base/ini/INIT.INI        /mnt/gramadovhd
	sudo cp base/ini/USER.INI        /mnt/gramadovhd


#base fonts
	sudo cp  base/res/fonts/NC2.FON        /mnt/gramadovhd
	sudo cp  base/res/fonts/LIN8X8.FON     /mnt/gramadovhd
	sudo cp  base/res/fonts/LIN8X16.FON    /mnt/gramadovhd
#...


#base Cursors
	sudo cp  base/res/cursors/CURSOR.BMP    /mnt/gramadovhd
	sudo cp  base/res/cursors/MOUSE.BMP     /mnt/gramadovhd
	
#base Icons
	sudo cp  base/res/icons/APP.BMP       /mnt/gramadovhd
	sudo cp  base/res/icons/BMP1.BMP      /mnt/gramadovhd
	sudo cp  base/res/icons/FILE.BMP      /mnt/gramadovhd
	sudo cp  base/res/icons/FOLDER.BMP    /mnt/gramadovhd
	sudo cp  base/res/icons/TERMINAL.BMP  /mnt/gramadovhd


#base Images
#	-sudo cp base/res/images/DENNIS.BMP    /mnt/gramadovhd
#	-sudo cp base/res/images/DENNIS2.BMP   /mnt/gramadovhd


#base  Tests
#	-sudo cp base/tests/*.C      /mnt/gramadovhd
	-sudo cp base/tests/*.CPP    /mnt/gramadovhd
#	-sudo cp base/tests/*.LUA    /mnt/gramadovhd


#base Wallpapers
#	-sudo cp base/res/wall/GRAMADO.BMP   /mnt/gramadovhd

#docs
	sudo cp docs/*.TXT        /mnt/gramadovhd



# garden

	#gwin
#	-sudo cp userland/ul1/garden/bin/GWINMGR.BIN   /mnt/gramadovhd



# servers
	-sudo cp servers/bin/GWS.BIN  /mnt/gramadovhd

#	-sudo cp userland/ul1/garden/bin/GWM.BIN       /mnt/gramadovhd


	#apps
	-sudo cp apps/bin/ILIINIT.BIN   /mnt/gramadovhd

#	-sudo cp apps/bin/GLOGON.BIN    /mnt/gramadovhd

#apps
	-sudo cp apps/bin/NORATERM.BIN  /mnt/gramadovhd


#	-sudo cp userland/ul1/garden/bin/GDETERM.BIN   /mnt/gramadovhd 

#apps
	sudo cp apps/bin/GDESHELL.BIN  /mnt/gramadovhd 


	-sudo cp apps/bin/GRAMCODE.BIN  /mnt/gramadovhd 
#	-sudo cp userland/ul1/garden/bin/GRAMTEXT.BIN  /mnt/gramadovhd 
	-sudo cp apps/bin/GFE.BIN       /mnt/gramadovhd 
	-sudo cp apps/bin/SPR.BIN       /mnt/gramadovhd 
	-sudo cp apps/bin/SYSMON.BIN    /mnt/gramadovhd
	-sudo cp apps/bin/REBOOT2.BIN   /mnt/gramadovhd
	-sudo cp apps/bin/LAUNCHER.BIN  /mnt/gramadovhd
#	-sudo cp userland/ul1/garden/bin/WINTEST.BIN   /mnt/gramadovhd 
#	-sudo cp userland/ul1/garden/bin/GDEINIT.BIN   /mnt/gramadovhd 
#	-sudo cp userland/ul1/garden/bin/GDETM.BIN     /mnt/gramadovhd 
	-sudo cp apps/bin/GDEWM.BIN     /mnt/gramadovhd


# cmd
	-sudo cp cmd/bin/TRUE.BIN      /mnt/gramadovhd
	-sudo cp cmd/bin/FALSE.BIN     /mnt/gramadovhd
	-sudo cp cmd/bin/CAT.BIN       /mnt/gramadovhd
	-sudo cp cmd/bin/ECHO.BIN      /mnt/gramadovhd
	-sudo cp cmd/bin/SUM.BIN       /mnt/gramadovhd
	-sudo cp cmd/bin/SPLIT.BIN     /mnt/gramadovhd
	-sudo cp cmd/bin/CMP.BIN       /mnt/gramadovhd
	-sudo cp cmd/bin/SHOWFUN.BIN   /mnt/gramadovhd
	-sudo cp cmd/bin/S1.BIN        /mnt/gramadovhd
	-sudo cp cmd/bin/S2.BIN        /mnt/gramadovhd


#	-sudo cp userland/ul2/atacama/bin/DUMPIT.BIN    /mnt/gramadovhd

	-sudo cp cmd/bin/HELLO.BIN     /mnt/gramadovhd
	-sudo cp cmd/bin/HELLO2.BIN    /mnt/gramadovhd
	-sudo cp cmd/bin/HELLO3.BIN    /mnt/gramadovhd

	-sudo cp cmd/bin/JACKPOT.BIN   /mnt/gramadovhd
#	-sudo cp userland/ul2/atacama/bin/LISP.BIN      /mnt/gramadovhd

	-sudo cp cmd/bin/REBOOT.BIN    /mnt/gramadovhd

#	-sudo cp userland/ul2/atacama/bin/TASCII.BIN    /mnt/gramadovhd
#	-sudo cp userland/ul2/atacama/bin/GLIBCT1.BIN   /mnt/gramadovhd 
#	-sudo cp userland/ul2/atacama/bin/SHELL3.BIN    /mnt/gramadovhd


# atacama/gt/gramcc
#	-sudo cp userland/ul2/atacama/bin/GRAM.BIN      /mnt/gramadovhd 
#	-sudo cp userland/ul2/atacama/bin/GRAMC.BIN     /mnt/gramadovhd 

# 3rd party
# Each app has your own folder.
#	-sudo cp userland/ul2/atacama/bin/LUA.BIN       /mnt/gramadovhd
#	-sudo cp userland/ul2/atacama/bin/BISON125.BIN  /mnt/gramadovhd
#	-sudo cp userland/ul2/atacama/bin/FASM.BIN      /mnt/gramadovhd
#...


#
# ======== Files in the BIN/ folder. ========
#

# bugbug
# Suspendendo isso por falta de espaço na partição.

	#-sudo cp userland/ul1/garden/bin/*         /mnt/gramadovhd/BIN 
	#-sudo cp userland/ul2/atacama/bin/*        /mnt/gramadovhd/BIN 

#	-sudo cp userland/ul2/atacama/bin/HELLO3.BIN  /mnt/gramadovhd/BIN 
	
#
# ======== Files in the /BOOT/ folder. ========
#

	sudo cp bin/boot/KERNEL.BIN   /mnt/gramadovhd
	sudo cp bin/boot/KERNEL.BIN   /mnt/gramadovhd/BOOT
	sudo cp bin/boot/BM.BIN       /mnt/gramadovhd/BOOT
	sudo cp bin/boot/BL.BIN       /mnt/gramadovhd/BOOT


#colocaremos drivers e servidores na pasta boot/
#	sudo cp bin/drivers/??.BIN       /mnt/gramadovhd/BOOT	
#	sudo cp bin/servers/??.BIN       /mnt/gramadovhd/BOOT


#
# ======== Files in the /DEV/ folder. ========
#

# TTY SERIAL DEVICES
#	-sudo cp user/config/TTYS0     /mnt/gramadovhd/DEV
#	-sudo cp user/config/TTYS1     /mnt/gramadovhd/DEV
#	-sudo cp user/config/TTYS2     /mnt/gramadovhd/DEV
#	-sudo cp user/config/TTYS3     /mnt/gramadovhd/DEV

# VIRTUAL CONSOLES
#	-sudo cp user/config/TTY0     /mnt/gramadovhd/DEV
#	-sudo cp user/config/TTY1     /mnt/gramadovhd/DEV
#	-sudo cp user/config/TTY2     /mnt/gramadovhd/DEV
#	-sudo cp user/config/TTY3     /mnt/gramadovhd/DEV
# ...

# NULL
#	-sudo cp user/config/NULL     /mnt/gramadovhd/DEV

# PSEUDO TERMINAL
#	-sudo cp user/config/0        /mnt/gramadovhd/DEV/PTS
#	-sudo cp user/config/1        /mnt/gramadovhd/DEV/PTS
#	-sudo cp user/config/PTMX     /mnt/gramadovhd/DEV/PTS


#
# ======== Files in the /EFI/ folder. ========
#
	
#test efi
#	-sudo cp arch/x86/boot/efi/BOOTIA32.EFI  /mnt/gramadovhd/EFI/BOOT

#
# ======== Files in the /GARDEN/ folder. ========
#

#garden
#	-sudo cp arch/x86/boot/vhd/tests/TEST1.ASM  /mnt/gramadovhd/GARDEN
#	-sudo cp userland/ul1/garden/bin/*                    /mnt/gramadovhd/GARDEN/BIN 


#
# ======== Files in the /LIB/ folder. ========
#	
	
#	-sudo cp arch/x86/boot/vhd/tests/TEST1.ASM  /mnt/gramadovhd/LIB
	

#
# ======== Files in the SBIN/ folder. ========
#
#	-sudo cp userland/ul2/atacama/bin/HELLO3.BIN  /mnt/gramadovhd/SBIN 

#
# ======== Files in the /TMP/ folder. ========
#	

	-sudo cp base/tests/TEST1.C  /mnt/gramadovhd/TMP



## Step7 vhd-unmount        - Unmounting the VHD.
vhd-unmount:
	@echo "================================="
	@echo "(Step 7) Unmounting the VHD ..."

	sudo umount /mnt/gramadovhd


## Step8 clean              - Deleting the object files.           
clean:
	@echo "================================="
	@echo "(Step 8) Deleting the object files ..."

	-rm *.o
	@echo "Success?"


## ====================================================================================
## The extra stuff.
## 1) ISO support.
## 2) HDD support.
## 3) VM support.
## 4) Serial debug support.
## 5) Clean files support.
## 6) Usage support.
	
#
# ======== ISO ======== 
#

# test
# todo
# Create a .ISO file using nasm.
makeiso-x86:
	#todo:  
	#nasm -I arch/x86/boot/iso/stage1/ \
	#-I prek/arch/x86/boot/iso/???/  prek/arch/x86/boot/iso/main.asm  -o  GRAMADO.ISO
	
	@echo "#todo Create ISO using nasm"
	
# ISO
# Mount stage1.bin file with nasm.
# Create a .ISO file and move all the content of the /bin folder
# into the .ISO file.
geniso-x86:
	
	#stage1
	nasm prek/arch/x86/boot/iso/stage1/stage1.asm -f bin -o stage1.bin
	cp stage1.bin bin/boot/gramado/
	rm stage1.bin

	#.ISO
	mkisofs -R -J -c boot/gramado/boot.catalog -b boot/gramado/stage1.bin -no-emul-boot -boot-load-size 4 -boot-info-table -o GRAMADO.ISO bin
	
	@echo "iso Success?"	




#
# ======== HDD ========
#

	
hdd-mount:
	-sudo umount /mnt/gramadohdd
	sudo mount -t vfat -o loop,offset=32256 /dev/sda /mnt/gramadohdd/
#	sudo mount -t vfat -o loop,offset=32256 /dev/sdb /mnt/gramadohdd/
	
hdd-unmount:
	-sudo umount /mnt/gramadohdd
	
hdd-copy-kernel:
	sudo cp bin/boot/KERNEL.BIN /mnt/gramadohdd/BOOT 

danger-hdd-clone-vhd:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
#	sudo dd if=./GRAMADO.VHD of=/dev/sdb




#
# ======== VM ========
#


# Oracle Virtual Box 
oracle-virtual-box-test:
	VBoxManage startvm "Gramado"

# qemu 
qemu-test:
	qemu-system-x86_64 -hda GRAMADO.VHD -m 512 -serial stdio 
#	qemu-system-x86_64 -hda GRAMADO.VHD -m 128 -device e1000 -show-cursor -serial stdio -device e1000





#install-kvm-qemu:
#	sudo pacman -S virt-manager qemu vde2 ebtables dnsmasq bridge-utils openbsd-netcat



#
# ======== SERIAL DEBUG ========
#

serial-debug:
	cat ./docs/sdebug.txt
	

#
# ======== CLEAN ========
#

clean2:
	-rm *.ISO
	-rm *.VHD

clean3:
#	-rm apps/bin/*.BIN
	-rm cmd/bin/*.BIN


clean-userland-base:
#	-rm userland/base/bin/*.o
#	-rm userland/base/bin/*.BIN



clean-garden:
#	-rm userland/ul1/garden/bin/*.o
#	-rm userland/ul1/garden/bin/*.BIN


clean-atacama:
#	-rm userland/ul2/atacama/bin/*.o
#	-rm userland/ul2/atacama/bin/*.BIN




kernel-version:
	@echo $(KERNELVERSION)

image-name:
	@echo $(KBUILD_IMAGE)


#
# #test
# make lib
#

#userland:


#
# ======== USAGE ========
#

usage:
	@echo "> make"
	@echo "> make clean"
	@echo "> make clean2"
	@echo "> make qemu-test"
	@echo "> make oracle-virtual-box-test"
	@echo "> make vhd-mount"
	@echo "> make vhd-unmount"
	@echo "..."

