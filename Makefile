
# help me:
# This script is running very well,
# but we need to fix something to have a 
# fully working Linux experience.

# 
# SPDX-License-Identifier: GPL-3.0+ 

VERSION = 0
PATCHLEVEL = 3
SUBLEVEL = 0
EXTRAVERSION = 
NAME = Style

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
	-fleading-underscore \
	-fno-stack-protector \
	-s
	
x86:
	# entry
	nasm -I kernel/entry/x86/head/ kernel/entry/x86/head/head.s -f elf -o head.o
	gcc -c kernel/entry/x86/x86main.c -I include/ $(CFLAGS) -o x86main.o

	# hal
	gcc -c kernel/hal/hal.c -I include/ $(CFLAGS) -o hal.o

	# mk
	gcc -c  kernel/mk/mk.c -I include/  $(CFLAGS) -o mk.o

	# cpu
	gcc -c  kernel/mk/cpu/context.c  -I include/  $(CFLAGS) -o context.o
	gcc -c  kernel/mk/cpu/start.c    -I include/  $(CFLAGS) -o start.o

	# pc
	gcc -c  kernel/mk/pc/action/ts.c        -I include/  $(CFLAGS) -o ts.o	
	gcc -c  kernel/mk/pc/action/dispatch.c  -I include/  $(CFLAGS) -o dispatch.o	
	gcc -c  kernel/mk/pc/action/queue.c     -I include/  $(CFLAGS) -o queue.o
	gcc -c  kernel/mk/pc/action/process.c   -I include/  $(CFLAGS) -o process.o
	gcc -c  kernel/mk/pc/action/pheap.c     -I include/  $(CFLAGS) -o pheap.o	
	gcc -c  kernel/mk/pc/action/thread.c    -I include/  $(CFLAGS) -o thread.o		
	gcc -c  kernel/mk/pc/action/threadi.c   -I include/  $(CFLAGS) -o threadi.o
	gcc -c  kernel/mk/pc/action/theap.c     -I include/  $(CFLAGS) -o theap.o
	gcc -c  kernel/mk/pc/action/tstack.c    -I include/  $(CFLAGS) -o tstack.o	
	gcc -c  kernel/mk/pc/action/tasks.c     -I include/  $(CFLAGS) -o tasks.o	
	gcc -c  kernel/mk/pc/action/create.c    -I include/  $(CFLAGS) -o create.o
	gcc -c  kernel/mk/pc/action/spawn.c     -I include/  $(CFLAGS) -o spawn.o

	# mk/pc/ipc 
	gcc -c  kernel/mk/pc/ipc/callout.c  -I include/  $(CFLAGS) -o callout.o
	gcc -c  kernel/mk/pc/ipc/callfar.c  -I include/  $(CFLAGS) -o callfar.o
	gcc -c  kernel/mk/pc/ipc/ipc.c      -I include/  $(CFLAGS) -o ipc.o	
	gcc -c  kernel/mk/pc/ipc/sem.c      -I include/  $(CFLAGS) -o sem.o

	# mk/pc/sched
	gcc -c  kernel/mk/pc/sched/sched.c  -I include/ $(CFLAGS) -o sched.o
	gcc -c  kernel/mk/pc/sched/schedi.c -I include/ $(CFLAGS) -o schedi.o    	

	# /mk/pc/mm (memory manager)
	gcc -c  kernel/mk/pc/mm/memory.c  -I include/ $(CFLAGS) -o memory.o    
	
	# /mk/pc/mm (memory manager)
	gcc -c  kernel/mk/pc/mm/pages.c   -I include/ $(CFLAGS) -o pages.o 	
	gcc -c  kernel/mk/request.c -I include/ $(CFLAGS) -o request.o	
	gcc -c  kernel/mk/faults.c  -I include/ $(CFLAGS) -o faults.o

	# /execve
	gcc -c kernel/execve/execve.c  -I include/ $(CFLAGS) -o execve.o	

	# crts
	# /execve/crts/libc
	gcc -c kernel/execve/crts/libc/cedge.c  -I include/ $(CFLAGS) -o cedge.o	
	gcc -c kernel/execve/crts/libc/ctype.c  -I include/ $(CFLAGS) -o ctype.o	
	gcc -c kernel/execve/crts/libc/stdlib.c -I include/ $(CFLAGS) -o stdlib.o
	gcc -c kernel/execve/crts/libc/stdio.c  -I include/ $(CFLAGS) -o stdio.o
	gcc -c kernel/execve/crts/libc/string.c -I include/ $(CFLAGS) -o string.o	

	# services - System Call Interface.  
	gcc -c kernel/execve/sci/services.c  -I include/ $(CFLAGS) -o services.o		

	# execve/dd

	# sm
	# /execve/init
	gcc -c kernel/execve/dd/sm/init/init.c -I include/ $(CFLAGS) -o init.o
	# /execve/sm/ob
	gcc -c kernel/execve/dd/sm/ob/object.c -I include/ $(CFLAGS) -o object.o		
	# /execve/network
	gcc -c kernel/execve/dd/sm/network/intel.c     -I include/ $(CFLAGS) -o nicintel.o
	gcc -c kernel/execve/dd/sm/network/network.c -I include/ $(CFLAGS) -o network.o
	gcc -c kernel/execve/dd/sm/network/socket.c  -I include/ $(CFLAGS) -o socket.o
	# System Management.

	# /execve/sm/sys
	# system
	gcc -c kernel/execve/dd/sm/sys/modules.c  -I include/ $(CFLAGS) -o modules.o
	# procedure
	gcc -c kernel/execve/dd/sm/sys/proc.c     -I include/ $(CFLAGS) -o proc.o	
	# abort
	gcc -c kernel/execve/dd/sm/sys/abort.c    -I include/ $(CFLAGS) -o abort.o		
	# info
	gcc -c kernel/execve/dd/sm/sys/info.c     -I include/ $(CFLAGS) -o info.o	
	# server manager
	gcc -c kernel/execve/dd/sm/sys/sm.c       -I include/ $(CFLAGS) -o sm.o
	# channel
	gcc -c kernel/execve/dd/sm/sys/channel.c  -I include/ $(CFLAGS) -o channel.o	
	# signal
	gcc -c kernel/execve/dd/sm/sys/signal.c   -I include/ $(CFLAGS) -o signal.o	
	# system
	gcc -c kernel/execve/dd/sm/sys/system.c   -I include/ $(CFLAGS) -o system.o
	# io
	gcc -c kernel/execve/dd/sm/sys/io.c       -I include/ $(CFLAGS) -o io.o	

	# sm
	# /execve/rt (runtime)
	gcc -c kernel/execve/dd/sm/rt/runtime.c   -I include/ $(CFLAGS) -o runtime.o

	# tty
	gcc -c kernel/execve/dd/tty/tty.c         -I include/ $(CFLAGS) -o tty.o		

	# sm
	# /execve/sm/disk

	# colocando o código do nelson em 3rdparty
	gcc -c 3rdparty/kernel/disk/disk1.c   -I include/ $(CFLAGS) -o disk1.o

	# o volume vira disk para absorver o código do fred que esta no código acima.
	# gcc -c kernel/execve/dd/sm/disk/volume.c -I include/ $(CFLAGS) -o volume.o	
	gcc -c kernel/execve/dd/sm/disk/disk.c -I include/ $(CFLAGS) -o disk.o

	# sm
	gcc -c kernel/execve/dd/sm/install/install.c -I include/ $(CFLAGS) -o install.o    

	# sm
	# /execve/debug
	gcc -c kernel/execve/dd/sm/debug/debug.c -I include/ $(CFLAGS) -o debug.o	

	gcc -c kernel/execve/dd/device/device.c  -I include/ $(CFLAGS) -o device.o

	# (unblocked) legados (K2).
	gcc -c kernel/execve/dd/unb/video.c     -I include/ $(CFLAGS) -o video.o  
	gcc -c kernel/execve/dd/unb/screen.c    -I include/ $(CFLAGS) -o screen.o 	
	gcc -c kernel/execve/dd/unb/keyboard.c  -I include/ $(CFLAGS) -o keyboard.o
	gcc -c kernel/execve/dd/unb/mouse.c     -I include/ $(CFLAGS) -o mouse.o  	
	gcc -c kernel/execve/dd/unb/ldisc.c     -I include/ $(CFLAGS) -o ldisc.o    	
	gcc -c kernel/execve/dd/unb/hdd.c       -I include/ $(CFLAGS) -o hdd.o	
	gcc -c kernel/execve/dd/unb/pic.c       -I include/ $(CFLAGS) -o pic.o 
	gcc -c kernel/execve/dd/unb/timer.c     -I include/ $(CFLAGS) -o timer.o	
	gcc -c kernel/execve/dd/unb/rtc.c       -I include/ $(CFLAGS) -o rtc.o
	gcc -c kernel/execve/dd/unb/vsync.c     -I include/ $(CFLAGS) -o vsync.o 
	gcc -c kernel/execve/dd/unb/arch/x86/syscall.c  -I include/ $(CFLAGS) -o syscall.o		
	gcc -c kernel/execve/dd/unb/arch/x86/cpux86.c   -I include/ $(CFLAGS) -o cpux86.o 
	gcc -c kernel/execve/dd/unb/arch/x86/x86.c      -I include/ $(CFLAGS) -o x86.o	
	gcc -c kernel/execve/dd/unb/arch/x86/ports.c    -I include/ $(CFLAGS) -o ports.o 	
	gcc -c kernel/execve/dd/unb/arch/amd/cpuamd.c   -I include/ $(CFLAGS) -o cpuamd.o 	    

	# (blocked) (K1).
	gcc -c kernel/execve/dd/b/pci.c  -I include/ $(CFLAGS) -o pci.o
	gcc -c kernel/execve/dd/b/usb.c  -I include/ $(CFLAGS) -o usb.o
	gcc -c kernel/execve/dd/b/apic.c -I include/ $(CFLAGS) -o apic.o 

	# File system

	# /execve/fs
	gcc -c kernel/execve/fs/fs.c     -I include/ $(CFLAGS) -o fs.o						
	gcc -c kernel/execve/fs/read.c   -I include/ $(CFLAGS) -o read.o			
	gcc -c kernel/execve/fs/write.c  -I include/ $(CFLAGS) -o write.o			
	gcc -c kernel/execve/fs/cf.c     -I include/ $(CFLAGS) -o cf.o			
	gcc -c kernel/execve/fs/search.c -I include/ $(CFLAGS) -o search.o			
	gcc -c kernel/execve/fs/format.c -I include/ $(CFLAGS) -o format.o	
	gcc -c kernel/execve/fs/vfs.c    -I include/ $(CFLAGS) -o vfs.o

	# k\gws\gws	
	# Gramado Window Server.
	gcc -c kernel/gws/gws/char.c     -I include/ $(CFLAGS) -o char.o
	gcc -c kernel/gws/gws/pixel.c    -I include/ $(CFLAGS) -o pixel.o 
	gcc -c kernel/gws/gws/line.c     -I include/ $(CFLAGS) -o line.o	
	gcc -c kernel/gws/gws/rect.c     -I include/ $(CFLAGS) -o rect.o 
	gcc -c kernel/gws/gws/dtext.c    -I include/ $(CFLAGS) -o dtext.o
	gcc -c kernel/gws/gws/font.c     -I include/ $(CFLAGS) -o font.o	
	gcc -c kernel/gws/gws/createw.c  -I include/ $(CFLAGS) -o createw.o    
	gcc -c kernel/gws/gws/grid.c     -I include/ $(CFLAGS) -o grid.o 
	gcc -c kernel/gws/gws/sbar.c     -I include/ $(CFLAGS) -o sbar.o 
	gcc -c kernel/gws/gws/menubar.c   -I include/ $(CFLAGS) -o menubar.o 
	gcc -c kernel/gws/gws/menu.c      -I include/ $(CFLAGS) -o menu.o 
	gcc -c kernel/gws/gws/bmp.c       -I include/ $(CFLAGS) -o bmp.o 
	gcc -c kernel/gws/gws/button.c    -I include/ $(CFLAGS) -o button.o 
	gcc -c kernel/gws/gws/mbox.c      -I include/ $(CFLAGS) -o mbox.o
	gcc -c kernel/gws/gws/dbox.c      -I include/ $(CFLAGS) -o dbox.o
	gcc -c kernel/gws/gws/bg.c        -I include/ $(CFLAGS) -o bg.o  
	gcc -c kernel/gws/gws/window.c    -I include/ $(CFLAGS) -o window.o    
	gcc -c kernel/gws/gws/desktop.c   -I include/ $(CFLAGS) -o desktop.o  
	gcc -c kernel/gws/gws/wstation.c  -I include/ $(CFLAGS) -o wstation.o    
	gcc -c kernel/gws/gws/usession.c  -I include/ $(CFLAGS) -o usession.o        

	# gramado logon e logoff
	gcc -c kernel/gws/logon/logon.c    -I include/ $(CFLAGS) -o logon.o 
	gcc -c kernel/gws/logoff/logoff.c  -I include/ $(CFLAGS) -o logoff.o 

	# gramado/user
	gcc -c kernel/gws/user/userenv.c   -I include/ $(CFLAGS) -o userenv.o 	

	# *gui (GRAMADO)
	gcc -c kernel/gws/gws.c   -I include/ $(CFLAGS) -o gws.o

link-x86:
	ld -m i386pe -T kernel/link.ld -o KERNEL.BIN $(wildcard *.o) -Map kernel/kmap.s

vhd-x86:
	nasm -I arch/x86/boot/vhd/stage1/ \
	-I arch/x86/boot/vhd/stage2/ \
	-I arch/x86/boot/vhd/stage2/lib16/ \
	-I arch/x86/boot/vhd/stage2/include/ \
	-I arch/x86/boot/vhd/msm/ \
	-I arch/x86/boot/vhd/msm/lib32/ \
	-I arch/x86/boot/vhd/msm/include/ \
	-I arch/x86/boot/vhd/msm/kernel/ \
	-I arch/x86/boot/vhd/msm/fs/ \
	-I arch/x86/boot/vhd/msm/shell/ \
	-I arch/x86/boot/vhd/msm/drivers/ \
	-I arch/x86/boot/vhd/bl/ \
	-I arch/x86/boot/vhd/kernel/ \
	-I arch/x86/boot/vhd/browser/  arch/x86/boot/vhd/main.asm -f bin  -o  GRAMADO.VHD

clean:
	find . -type f -name '*.o' -delete
