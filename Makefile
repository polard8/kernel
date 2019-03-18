
# Compiling Gramado on Manjaro Linux.
# BSD License
# SPDX-License-Identifier: GPL-3.0+
# History:
#     2018 - Created by Matheus Castello.
#     2019 - Fred Nora.
#     2019 - Luciano Gonçalez.


#important
#We will have a new name just when the release changes.

VERSION = 0
PATCHLEVEL = 24
SUBLEVEL = 0
EXTRAVERSION = .0
NAME = Ikigai


ARCH ?= x86



# Setup disk:
# For now we're using IDE disk on primary master.
# You can setup this options in:
# arch/x86/boot/bl/include/config/config.h for the boot loader and
# include/kernel/config/config.h for the kernel.



#todo:
#We need to simplify these flags, but it's working.

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
	-s


# bugbug: Não quero essa flag.
#	-fleading-underscore \	

##
## Defines
##

DEFINES =  -DGRAMADO_VERSION=$(VERSION) \
		-DGRAMADO_PATCHLEVEL=$(PATCHLEVEL) \
		-DGRAMADO_SUBLEVEL=$(SUBLEVEL) \
		-DGRAMADO_EXTRAVERSION=\"$(EXTRAVERSION)\" \
		-DGRAMAD0_NAME=\"$(NAME)\"

##
## Objects
##

ifeq ($(ARCH),x86)

	#deveria ser headx86.o
	ENTRY_OBJECTS := head.o x86main.o 
	
	EXECVE_OBJECTS := pipe.o socket.o cedge.o ctype.o  stdio.o stdlib.o string.o unistd.o \
	devmgr.o \
	ldisc.o \
	gde_serv.o \
	debug.o diskvol.o install.o object.o runtime.o \
	abort.o info.o io.o modules.o proc.o signal.o sm.o \
	init.o system.o \
	execve.o 
	
	HAL_OBJECTS := cpuamd.o portsx86.o syscall.o x86.o detect.o \
	hal.o 
	
	KDRIVERS_OBJECTS := ahci.o \
	i8042.o keyboard.o mouse.o ps2kbd.o ps2mouse.o \
	ata.o atadma.o atainit.o atairq.o atapci.o hdd.o \
	channel.o network.o nicintel.o nsocket.o \
	pci.o pciinfo.o pciscan.o \
	tty.o \
	usb.o \
	apic.o pic.o rtc.o screen.o serial.o timer.o video.o vsync.o 

	
	KSERVERS_OBJECTS := cf.o format.o fs.o read.o search.o write.o \
	bg.o bmp.o button.o char.o createw.o dtext.o font.o grid.o \
	line.o menu.o menubar.o pixel.o rect.o sbar.o window.o \
	logoff.o \
	logon.o \
	input.o output.o terminal.o \
	desktop.o room.o userenv.o usession.o \
	kgws.o \
	vfs.o 
	
	
	MK_OBJECTS := x86cont.o x86fault.o x86start.o \
	create.o dispatch.o pheap.o process.o queue.o spawn.o \
	tasks.o theap.o thread.o threadi.o ts.o tstack.o \
	callout.o callfar.o ipc.o ipccore.o sem.o \
	memory.o mminfo.o mmpool.o pages.o \
	preempt.o priority.o sched.o schedi.o \
	mk.o 


	REQUEST_OBJECTS := request.o 
	
	OBJECTS := $(ENTRY_OBJECTS) \
	$(EXECVE_OBJECTS) \
	$(HAL_OBJECTS) \
	$(KDRIVERS_OBJECTS) \
	$(KSERVERS_OBJECTS) \
	$(MK_OBJECTS) \
	$(REQUEST_OBJECTS)
	
endif


ifeq ($(ARCH),arm)
   # NOTHING FOR NOW
endif

  

#not file.
#.PHONY x86

xxx_x86: /mnt/gramadovhd compile-kernel link-x86 vhd-x86 vhd-mount vhd-copy-files vhd-unmount clean

compile-kernel:

	# /entry
	nasm -I kernel/entry/x86/head/ kernel/entry/x86/head/head.asm -f elf -o head.o
	gcc -c kernel/entry/x86/x86main.c  -I include/ $(CFLAGS) $(DEFINES) -o x86main.o

	# /hal
	gcc -c kernel/hal/hal.c                -I include/ $(CFLAGS) $(DEFINES) -o hal.o
	gcc -c kernel/hal/arch/detect.c        -I include/ $(CFLAGS) $(DEFINES) -o detect.o
	gcc -c kernel/hal/arch/amd/cpuamd.c    -I include/ $(CFLAGS) $(DEFINES) -o cpuamd.o
	gcc -c kernel/hal/arch/x86/portsx86.c  -I include/ $(CFLAGS) $(DEFINES) -o portsx86.o
	gcc -c kernel/hal/arch/x86/syscall.c   -I include/ $(CFLAGS) $(DEFINES) -o syscall.o
	gcc -c kernel/hal/arch/x86/x86.c       -I include/ $(CFLAGS) $(DEFINES) -o x86.o

	# /mk
	gcc -c  kernel/mk/mk.c -I include/  $(CFLAGS) $(DEFINES) -o mk.o

	# /cpu
	gcc -c  kernel/mk/arch/x86/x86cont.c   -I include/  $(CFLAGS) $(DEFINES) -o x86cont.o
	gcc -c  kernel/mk/arch/x86/x86start.c  -I include/  $(CFLAGS) $(DEFINES) -o x86start.o

	# /pc
	gcc -c  kernel/mk/pc/action/ts.c        -I include/  $(CFLAGS) $(DEFINES) -o ts.o
	gcc -c  kernel/mk/pc/action/dispatch.c  -I include/  $(CFLAGS) $(DEFINES) -o dispatch.o
	gcc -c  kernel/mk/pc/action/queue.c     -I include/  $(CFLAGS) $(DEFINES) -o queue.o
	gcc -c  kernel/mk/pc/action/process.c   -I include/  $(CFLAGS) $(DEFINES) -o process.o
	gcc -c  kernel/mk/pc/action/pheap.c     -I include/  $(CFLAGS) $(DEFINES) -o pheap.o
	gcc -c  kernel/mk/pc/action/thread.c    -I include/  $(CFLAGS) $(DEFINES) -o thread.o
	gcc -c  kernel/mk/pc/action/threadi.c   -I include/  $(CFLAGS) $(DEFINES) -o threadi.o
	gcc -c  kernel/mk/pc/action/theap.c     -I include/  $(CFLAGS) $(DEFINES) -o theap.o
	gcc -c  kernel/mk/pc/action/tstack.c    -I include/  $(CFLAGS) $(DEFINES) -o tstack.o
	gcc -c  kernel/mk/pc/action/tasks.c     -I include/  $(CFLAGS) $(DEFINES) -o tasks.o
	gcc -c  kernel/mk/pc/action/create.c    -I include/  $(CFLAGS) $(DEFINES) -o create.o
	gcc -c  kernel/mk/pc/action/spawn.c     -I include/  $(CFLAGS) $(DEFINES) -o spawn.o

	# mk/pc/ipc
	gcc -c  kernel/mk/pc/ipc/callout.c  -I include/  $(CFLAGS) $(DEFINES) -o callout.o
	gcc -c  kernel/mk/pc/ipc/callfar.c  -I include/  $(CFLAGS) $(DEFINES) -o callfar.o
	gcc -c  kernel/mk/pc/ipc/ipc.c      -I include/  $(CFLAGS) $(DEFINES) -o ipc.o
	gcc -c  kernel/mk/pc/ipc/ipccore.c      -I include/  $(CFLAGS) $(DEFINES) -o ipccore.o
	
	gcc -c  kernel/mk/pc/ipc/sem.c      -I include/  $(CFLAGS) $(DEFINES) -o sem.o

	# mk/pc/sched
	gcc -c  kernel/mk/pc/sched/sched.c     -I include/ $(CFLAGS) $(DEFINES) -o sched.o
	gcc -c  kernel/mk/pc/sched/schedi.c    -I include/ $(CFLAGS) $(DEFINES) -o schedi.o
	gcc -c  kernel/mk/pc/sched/preempt.c   -I include/ $(CFLAGS) $(DEFINES) -o preempt.o	
	gcc -c  kernel/mk/pc/sched/priority.c  -I include/ $(CFLAGS) $(DEFINES) -o priority.o
	
	
	
	# /mk/pc/mm (memory manager)
	
	#x86
	gcc -c  kernel/mk/pc/mm/x86/memory.c  -I include/ $(CFLAGS) $(DEFINES) -o memory.o
	gcc -c  kernel/mk/pc/mm/x86/pages.c   -I include/ $(CFLAGS) $(DEFINES) -o pages.o
	gcc -c  kernel/mk/pc/mm/x86/mmpool.c  -I include/ $(CFLAGS) $(DEFINES) -o mmpool.o	
	gcc -c  kernel/mk/pc/mm/x86/mminfo.c  -I include/ $(CFLAGS) $(DEFINES) -o mminfo.o		
	
	#arm
	
	
    #kernel/request
	gcc -c  kernel/request.c  -I include/ $(CFLAGS) $(DEFINES) -o request.o
	
	gcc -c  kernel/mk/arch/x86/x86fault.c  -I include/ $(CFLAGS) $(DEFINES) -o x86fault.o

	# /execve
	gcc -c kernel/execve/execve.c  -I include/ $(CFLAGS) $(DEFINES) -o execve.o

	# crts
	
	#klibc/pipe
	gcc -c kernel/execve/crts/klibc/pipe/pipe.c   -I include/ $(CFLAGS) $(DEFINES) -o pipe.o	
	
	#klibc/socket
	gcc -c kernel/execve/crts/klibc/socket/socket.c   -I include/ $(CFLAGS) $(DEFINES) -o socket.o		
	
	# klibc
	gcc -c kernel/execve/crts/klibc/cedge.c   -I include/ $(CFLAGS) $(DEFINES) -o cedge.o
	gcc -c kernel/execve/crts/klibc/ctype.c   -I include/ $(CFLAGS) $(DEFINES) -o ctype.o
	gcc -c kernel/execve/crts/klibc/stdlib.c  -I include/ $(CFLAGS) $(DEFINES) -o stdlib.o
	gcc -c kernel/execve/crts/klibc/stdio.c   -I include/ $(CFLAGS) $(DEFINES) -o stdio.o
	gcc -c kernel/execve/crts/klibc/string.c  -I include/ $(CFLAGS) $(DEFINES) -o string.o
	gcc -c kernel/execve/crts/klibc/unistd.c  -I include/ $(CFLAGS) $(DEFINES) -o unistd.o

	
	gcc -c kernel/kdrivers/apic.c    -I include/ $(CFLAGS) $(DEFINES) -o apic.o
	gcc -c kernel/kdrivers/pic.c     -I include/ $(CFLAGS) $(DEFINES) -o pic.o
	gcc -c kernel/kdrivers/rtc.c     -I include/ $(CFLAGS) $(DEFINES) -o rtc.o
	gcc -c kernel/kdrivers/screen.c  -I include/ $(CFLAGS) $(DEFINES) -o screen.o
	gcc -c kernel/kdrivers/serial.c  -I include/ $(CFLAGS) $(DEFINES) -o serial.o
	gcc -c kernel/kdrivers/timer.c   -I include/ $(CFLAGS) $(DEFINES) -o timer.o
	gcc -c kernel/kdrivers/video.c   -I include/ $(CFLAGS) $(DEFINES) -o video.o
	gcc -c kernel/kdrivers/vsync.c   -I include/ $(CFLAGS) $(DEFINES) -o vsync.o
	

	# kdrivers/ahci 
	# todo
	gcc -c kernel/kdrivers/ahci/ahci.c  -I include/ $(CFLAGS) $(DEFINES) -o ahci.o
	
	# kdrivers/i8042
	gcc -c kernel/kdrivers/i8042/i8042.c     -I include/ $(CFLAGS) $(DEFINES) -o i8042.o
	gcc -c kernel/kdrivers/i8042/keyboard.c  -I include/ $(CFLAGS) $(DEFINES) -o keyboard.o
	gcc -c kernel/kdrivers/i8042/mouse.c     -I include/ $(CFLAGS) $(DEFINES) -o mouse.o
	gcc -c kernel/kdrivers/i8042/ps2kbd.c    -I include/ $(CFLAGS) $(DEFINES) -o ps2kbd.o
	gcc -c kernel/kdrivers/i8042/ps2mouse.c  -I include/ $(CFLAGS) $(DEFINES) -o ps2mouse.o
	
	
	#ide support
	gcc -c kernel/kdrivers/ide/hdd.c      -I include/ $(CFLAGS) $(DEFINES) -o hdd.o
	gcc -c kernel/kdrivers/ide/ata.c      -I include/ $(CFLAGS) $(DEFINES) -o ata.o
	gcc -c kernel/kdrivers/ide/atainit.c  -I include/ $(CFLAGS) $(DEFINES) -o atainit.o
	gcc -c kernel/kdrivers/ide/atairq.c   -I include/ $(CFLAGS) $(DEFINES) -o atairq.o
	gcc -c kernel/kdrivers/ide/atapci.c   -I include/ $(CFLAGS) $(DEFINES) -o atapci.o	
	gcc -c kernel/kdrivers/ide/atadma.c   -I include/ $(CFLAGS) $(DEFINES) -o atadma.o	
	
	
	# kdrivers/network
	gcc -c kernel/kdrivers/network/channel.c   -I include/ $(CFLAGS) $(DEFINES) -o channel.o
	gcc -c kernel/kdrivers/network/nicintel.c  -I include/ $(CFLAGS) $(DEFINES) -o nicintel.o
	gcc -c kernel/kdrivers/network/network.c   -I include/ $(CFLAGS) $(DEFINES) -o network.o
	gcc -c kernel/kdrivers/network/nsocket.c   -I include/ $(CFLAGS) $(DEFINES) -o nsocket.o	

	# kdrivers/pci
	gcc -c kernel/kdrivers/pci/pci.c  -I include/ $(CFLAGS) $(DEFINES) -o pci.o
	gcc -c kernel/kdrivers/pci/pciscan.c  -I include/ $(CFLAGS) $(DEFINES) -o pciscan.o
	gcc -c kernel/kdrivers/pci/pciinfo.c  -I include/ $(CFLAGS) $(DEFINES) -o pciinfo.o


	# kdrivers/tty
	gcc -c kernel/kdrivers/tty/tty.c  -I include/ $(CFLAGS) $(DEFINES) -o tty.o


	# kdrivers/usb
	gcc -c kernel/kdrivers/usb/usb.c  -I include/ $(CFLAGS) $(DEFINES) -o usb.o
	

	# devmgr
	gcc -c kernel/execve/devmgr/devmgr.c  -I include/ $(CFLAGS) $(DEFINES) -o devmgr.o


	# execve/ldisc
	gcc -c kernel/execve/ldisc/ldisc.c  -I include/ $(CFLAGS) $(DEFINES) -o ldisc.o






	# /fs
	gcc -c kernel/kservers/fs/fs.c      -I include/ $(CFLAGS) $(DEFINES) -o fs.o
	gcc -c kernel/kservers/fs/read.c    -I include/ $(CFLAGS) $(DEFINES) -o read.o
	gcc -c kernel/kservers/fs/write.c   -I include/ $(CFLAGS) $(DEFINES) -o write.o
	gcc -c kernel/kservers/fs/cf.c      -I include/ $(CFLAGS) $(DEFINES) -o cf.o
	gcc -c kernel/kservers/fs/search.c  -I include/ $(CFLAGS) $(DEFINES) -o search.o
	gcc -c kernel/kservers/fs/format.c  -I include/ $(CFLAGS) $(DEFINES) -o format.o
	
	# /vfs
	gcc -c kernel/kservers/vfs/vfs.c     -I include/ $(CFLAGS) $(DEFINES) -o vfs.o

	# /sci/gde
	gcc -c kernel/execve/sci/gde/gde_serv.c    -I include/ $(CFLAGS) $(DEFINES) -o gde_serv.o

	# /sm
	gcc -c kernel/execve/sm/init.c    -I include/ $(CFLAGS) $(DEFINES) -o init.o
	gcc -c kernel/execve/sm/system.c  -I include/ $(CFLAGS) $(DEFINES) -o system.o
	gcc -c kernel/execve/sm/debug/debug.c      -I include/ $(CFLAGS) $(DEFINES) -o debug.o
	gcc -c kernel/execve/sm/disk/diskvol.c     -I include/ $(CFLAGS) $(DEFINES) -o diskvol.o
	gcc -c kernel/execve/sm/install/install.c  -I include/ $(CFLAGS) $(DEFINES) -o install.o	
	gcc -c kernel/execve/sm/ob/object.c        -I include/ $(CFLAGS) $(DEFINES) -o object.o
	gcc -c kernel/execve/sm/rt/runtime.c       -I include/ $(CFLAGS) $(DEFINES) -o runtime.o
	gcc -c kernel/execve/sm/sys/abort.c    -I include/ $(CFLAGS) $(DEFINES) -o abort.o	
	gcc -c kernel/execve/sm/sys/info.c     -I include/ $(CFLAGS) $(DEFINES) -o info.o
	gcc -c kernel/execve/sm/sys/io.c       -I  include/ $(CFLAGS) $(DEFINES) -o io.o
	gcc -c kernel/execve/sm/sys/modules.c  -I include/ $(CFLAGS) $(DEFINES) -o modules.o
	gcc -c kernel/execve/sm/sys/proc.c     -I include/ $(CFLAGS) $(DEFINES) -o proc.o
	gcc -c kernel/execve/sm/sys/signal.c   -I include/ $(CFLAGS) $(DEFINES) -o signal.o
	gcc -c kernel/execve/sm/sys/sm.c       -I include/ $(CFLAGS) $(DEFINES) -o sm.o

	# kservers/kgws - Kernel Gramado Window Server.

	gcc -c kernel/kservers/kgws/kgws/comp/bg.c        -I include/ $(CFLAGS) $(DEFINES) -o bg.o
	gcc -c kernel/kservers/kgws/kgws/comp/bmp.c       -I include/ $(CFLAGS) $(DEFINES) -o bmp.o
	gcc -c kernel/kservers/kgws/kgws/comp/button.c    -I include/ $(CFLAGS) $(DEFINES) -o button.o	
	gcc -c kernel/kservers/kgws/kgws/comp/char.c      -I include/ $(CFLAGS) $(DEFINES) -o char.o
	gcc -c kernel/kservers/kgws/kgws/comp/createw.c   -I include/ $(CFLAGS) $(DEFINES) -o createw.o
	gcc -c kernel/kservers/kgws/kgws/comp/dtext.c     -I include/ $(CFLAGS) $(DEFINES) -o dtext.o
	gcc -c kernel/kservers/kgws/kgws/comp/font.c      -I include/ $(CFLAGS) $(DEFINES) -o font.o
	gcc -c kernel/kservers/kgws/kgws/comp/grid.c      -I include/ $(CFLAGS) $(DEFINES) -o grid.o
	gcc -c kernel/kservers/kgws/kgws/comp/line.c      -I include/ $(CFLAGS) $(DEFINES) -o line.o
	gcc -c kernel/kservers/kgws/kgws/comp/menu.c      -I include/ $(CFLAGS) $(DEFINES) -o menu.o
	gcc -c kernel/kservers/kgws/kgws/comp/menubar.c   -I include/ $(CFLAGS) $(DEFINES) -o menubar.o
	gcc -c kernel/kservers/kgws/kgws/comp/pixel.c     -I include/ $(CFLAGS) $(DEFINES) -o pixel.o
	gcc -c kernel/kservers/kgws/kgws/comp/rect.c      -I include/ $(CFLAGS) $(DEFINES) -o rect.o
	gcc -c kernel/kservers/kgws/kgws/comp/sbar.c      -I include/ $(CFLAGS) $(DEFINES) -o sbar.o
	
	gcc -c kernel/kservers/kgws/kgws/window.c    -I include/ $(CFLAGS) $(DEFINES) -o window.o
	
	gcc -c kernel/kservers/kgws/logon/logon.c    -I include/ $(CFLAGS) $(DEFINES) -o logon.o
	gcc -c kernel/kservers/kgws/logoff/logoff.c  -I include/ $(CFLAGS) $(DEFINES) -o logoff.o

	gcc -c kernel/kservers/kgws/terminal/input.c     -I include/ $(CFLAGS) $(DEFINES) -o input.o
	gcc -c kernel/kservers/kgws/terminal/output.c    -I include/ $(CFLAGS) $(DEFINES) -o output.o
	gcc -c kernel/kservers/kgws/terminal/terminal.c  -I include/ $(CFLAGS) $(DEFINES) -o terminal.o
	
	gcc -c kernel/kservers/kgws/user/userenv.c   -I include/ $(CFLAGS) $(DEFINES) -o userenv.o
	gcc -c kernel/kservers/kgws/user/desktop.c   -I include/ $(CFLAGS) $(DEFINES) -o desktop.o
	gcc -c kernel/kservers/kgws/user/room.c      -I include/ $(CFLAGS) $(DEFINES) -o room.o
	gcc -c kernel/kservers/kgws/user/usession.c  -I include/ $(CFLAGS) $(DEFINES) -o usession.o
	
	gcc -c kernel/kservers/kgws/kgws.c           -I include/ $(CFLAGS) $(DEFINES) -o kgws.o


link-x86:
	ld -m elf_i386 -T kernel/link.ld -o KERNEL.BIN $(OBJECTS) -Map docs/kmap.s


#move
	mv KERNEL.BIN bin/boot/

vhd-x86:
	nasm -I arch/x86/boot/vhd/stage1/ \
	-I arch/x86/boot/vhd/vbr/ \
	-I arch/x86/boot/vhd/footer/ arch/x86/boot/vhd/main.asm  -o  GRAMADO.VHD


vhd-mount:
	-sudo umount /mnt/gramadovhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadovhd/

# Copy content to disk
# 1) BM, BL 
# 2) KERNEL 
# 3) INIT, SHELL, TASKMAN
vhd-copy-files:
	
#
# ======== Files in the root dir. ========
#

	sudo cp bin/boot/BM.BIN       /mnt/gramadovhd
	sudo cp bin/boot/BL.BIN       /mnt/gramadovhd
	
# user/config
	sudo cp user/config/USER.TXT /mnt/gramadovhd
	sudo cp user/config/INIT.TXT /mnt/gramadovhd
	sudo cp user/config/GUI.TXT  /mnt/gramadovhd
	sudo cp user/config/GRAMADO.TXT /mnt/gramadovhd
	
# bitmaps
	sudo cp kernel/kservers/kgws/bmp/APP.BMP       /mnt/gramadovhd
	sudo cp kernel/kservers/kgws/bmp/BMP1.BMP      /mnt/gramadovhd
	sudo cp kernel/kservers/kgws/bmp/CURSOR.BMP    /mnt/gramadovhd
	-sudo cp kernel/kservers/kgws/bmp/DENNIS.BMP   /mnt/gramadovhd
	sudo cp kernel/kservers/kgws/bmp/FILE.BMP      /mnt/gramadovhd
	sudo cp kernel/kservers/kgws/bmp/FOLDER.BMP    /mnt/gramadovhd
	-sudo cp kernel/kservers/kgws/bmp/GRAMADO.BMP  /mnt/gramadovhd
	sudo cp kernel/kservers/kgws/bmp/MOUSE.BMP     /mnt/gramadovhd
	sudo cp kernel/kservers/kgws/bmp/TERMINAL.BMP  /mnt/gramadovhd


# fonts
	sudo cp bin/NC2.FON /mnt/gramadovhd	
	
#Get available apps
	-sudo cp ../gde/bin/GRAMCODE.BIN  /mnt/gramadovhd 
	-sudo cp ../gde/bin/GRAMTEXT.BIN  /mnt/gramadovhd 
	-sudo cp ../gde/bin/GFE.BIN       /mnt/gramadovhd 
	-sudo cp ../gde/bin/SPR.BIN       /mnt/gramadovhd 
	
	-sudo cp ../gde/bin/GDEINIT.BIN   /mnt/gramadovhd 	
	-sudo cp ../gde/bin/GDESHELL.BIN  /mnt/gramadovhd 
	-sudo cp ../gde/bin/GDETM.BIN     /mnt/gramadovhd 
	
	-sudo cp ../gde/bin/JACKPOT.BIN   /mnt/gramadovhd 
	-sudo cp ../gde/bin/CAT.BIN       /mnt/gramadovhd 
	-sudo cp ../gde/bin/GLIBCT1.BIN   /mnt/gramadovhd 

#...
	
	
#
# ======== Creating the all the folders in root dir ========
#		

# Creating standard folders
	-sudo mkdir /mnt/gramadovhd/BIN
	-sudo mkdir /mnt/gramadovhd/BOOT
	-sudo mkdir /mnt/gramadovhd/DEV
	-sudo mkdir /mnt/gramadovhd/EFI
	-sudo mkdir /mnt/gramadovhd/EFI/BOOT	
	-sudo mkdir /mnt/gramadovhd/GDE
	-sudo mkdir /mnt/gramadovhd/GDE/BIN		
	-sudo mkdir /mnt/gramadovhd/HOME
	-sudo mkdir /mnt/gramadovhd/LIB	
	-sudo mkdir /mnt/gramadovhd/MNT
	-sudo mkdir /mnt/gramadovhd/TMP


#
# ======== Files in the BIN/ folder. ========
#	

	-sudo cp ../gde/bin/*                       /mnt/gramadovhd/BIN 
	
#
# ======== Files in the BOOT/ folder. ========
#	

# principais.
# Serão carregados por bl.bin. 
	sudo cp bin/boot/KERNEL.BIN   /mnt/gramadovhd/BOOT
	sudo cp bin/boot/INIT.BIN     /mnt/gramadovhd/BOOT
	sudo cp bin/boot/SHELL.BIN    /mnt/gramadovhd/BOOT
	sudo cp bin/boot/TASKMAN.BIN  /mnt/gramadovhd/BOOT

#colocaremos drivers e servidores na pasta boot/
#	sudo cp bin/drivers/??.BIN       /mnt/gramadovhd/BOOT	
#	sudo cp bin/servers/??.BIN       /mnt/gramadovhd/BOOT


#
# ======== Files in the EFI/ folder. ========
#	
	
#test efi
#	-sudo cp arch/x86/boot/efi/BOOTIA32.EFI  /mnt/gramadovhd/EFI/BOOT

#
# ======== Files in the GDE/ folder. ========
#	

#gde
	-sudo cp arch/x86/boot/vhd/tests/TEST1.ASM  /mnt/gramadovhd/GDE
	-sudo cp ../gde/bin/*                       /mnt/gramadovhd/GDE/BIN 
	

#
# ======== Files in the LIB/ folder. ========
#	
	
	-sudo cp arch/x86/boot/vhd/tests/TEST1.ASM  /mnt/gramadovhd/LIB
	

#
# ======== Files in the TMP/ folder. ========
#	

	-sudo cp arch/x86/boot/vhd/tests/TEST1.ASM  /mnt/gramadovhd/TMP
	
	

	


# umount
vhd-unmount:
	sudo umount /mnt/gramadovhd

/mnt/gramadovhd:
	sudo mkdir /mnt/gramadovhd

clean:
	-rm *.o

	@echo "Success?"
	
	
# test
# todo
# Create a .ISO file using nasm.
makeiso-x86:
	#todo:  
	#nasm -I arch/x86/boot/iso/stage1/ \
	#-I arch/x86/boot/iso/???/  arch/x86/boot/iso/main.asm  -o  GRAMADO.ISO
	
	@echo "#todo Create ISO using nasm"
	
# ISO
# Mount stage1.bin file with nasm.
# Create a .ISO file and move all the content of the /bin folder
# into the .ISO file.
geniso-x86:
	
	#stage1
	nasm arch/x86/boot/iso/stage1/stage1.asm -f bin -o stage1.bin
	cp stage1.bin bin/boot/gramado/
	rm stage1.bin

	#.ISO
	mkisofs -R -J -c boot/gramado/boot.catalog -b boot/gramado/stage1.bin -no-emul-boot -boot-load-size 4 -boot-info-table -o GRAMADO.ISO bin
	
	@echo "iso Success?"	
	
	
	
