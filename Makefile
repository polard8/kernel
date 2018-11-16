
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
	-no-pie \
	-fleading-underscore \
	-fno-stack-protector \
	-s


	## 
	## Objects 
	##

myObjects = head.o \
x86main.o \
io.o \
hal.o \
mk.o \
execve.o \
video.o \
screen.o \
runtime.o \
ports.o \
x86.o \
stdio.o \
stdlib.o \
string.o \
tty.o \
init.o \
logon.o \
logoff.o \
cpux86.o \
cpuamd.o \
memory.o \
pages.o \
apic.o \
pic.o \
timer.o \
rtc.o \
keyboard.o \
mouse.o \
ldisc.o \
hdd.o \
pci.o \
usb.o \
devmgr.o \
spawn.o \
callout.o \
callfar.o \
process.o \
pheap.o \
thread.o \
threadi.o \
theap.o \
tstack.o \
create.o \
start.o \
context.o \
tasks.o \
ts.o \
queue.o \
sched.o \
schedi.o \
dispatch.o \
sem.o \
modules.o \
nicintel.o \
network.o \
socket.o \
sm.o \
channel.o \
ipc.o \
read.o \
write.o \
cf.o \
search.o \
format.o \
disk1.o \
diskvol.o \
fs.o \
vfs.o \
cedge.o \
ctype.o \
request.o \
info.o \
signal.o \
system.o \
bg.o \
grid.o \
sbar.o \
menubar.o \
menu.o \
i8042.o \
ps2mouse.o \
ps2kbd.o \
button.o \
char.o \
pixel.o \
line.o \
rect.o \
dtext.o \
font.o \
vsync.o \
bmp.o \
createw.o \
window.o \
desktop.o \
room.o \
usession.o \
gws.o \
object.o \
userenv.o \
proc.o \
syscall.o \
install.o \
debug.o \
abort.o \
faults.o \
services.o  





x86:
	gcc -c kernel/3rdparty/kernel/disk/disk1.c   -I include/ $(CFLAGS) -o disk1.o

	# /entry
	nasm -I kernel/entry/x86/head/ kernel/entry/x86/head/head.s -f elf -o head.o
	gcc -c kernel/entry/x86/x86main.c  -I include/ $(CFLAGS) -o x86main.o

	# /hal
	gcc -c kernel/hal/hal.c -I include/ $(CFLAGS) -o hal.o
	
	
	gcc -c kernel/hal/arch/x86/syscall.c   -I include/ $(CFLAGS) -o syscall.o		
	gcc -c kernel/hal/arch/x86/cpux86.c    -I include/ $(CFLAGS) -o cpux86.o 
    gcc -c kernel/hal/arch/x86/x86.c       -I include/ $(CFLAGS) -o x86.o	
	gcc -c kernel/hal/arch/x86/ports.c     -I include/ $(CFLAGS) -o ports.o 	
	gcc -c kernel/hal/arch/amd/cpuamd.c    -I include/ $(CFLAGS) -o cpuamd.o 		
	
	# /mk
	gcc -c  kernel/mk/mk.c -I include/  $(CFLAGS) -o mk.o

	# /cpu
	gcc -c  kernel/mk/cpu/context.c  -I include/  $(CFLAGS) -o context.o
	gcc -c  kernel/mk/cpu/start.c    -I include/  $(CFLAGS) -o start.o

	# /pc
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
	gcc -c  kernel/mk/pc/sched/sched.c   -I include/ $(CFLAGS) -o sched.o
	gcc -c  kernel/mk/pc/sched/schedi.c  -I include/ $(CFLAGS) -o schedi.o    	

	# /mk/pc/mm (memory manager)
	gcc -c  kernel/mk/pc/mm/memory.c  -I include/ $(CFLAGS) -o memory.o    
	gcc -c  kernel/mk/pc/mm/pages.c   -I include/ $(CFLAGS) -o pages.o 	
	
	gcc -c  kernel/mk/request.c      -I include/ $(CFLAGS) -o request.o	
	gcc -c  kernel/mk/faults.c       -I include/ $(CFLAGS) -o faults.o

	# /execve
	gcc -c kernel/execve/execve.c  -I include/ $(CFLAGS) -o execve.o	

	# crts
	# /execve/crts/libc
	gcc -c kernel/execve/crts/libc/cedge.c   -I include/ $(CFLAGS) -o cedge.o	
	gcc -c kernel/execve/crts/libc/ctype.c   -I include/ $(CFLAGS) -o ctype.o	
	gcc -c kernel/execve/crts/libc/stdlib.c  -I include/ $(CFLAGS) -o stdlib.o
	gcc -c kernel/execve/crts/libc/stdio.c   -I include/ $(CFLAGS) -o stdio.o
	gcc -c kernel/execve/crts/libc/string.c  -I include/ $(CFLAGS) -o string.o	

	
	
	gcc -c kernel/execve/dd/apic.c    -I include/ $(CFLAGS) -o apic.o 
	gcc -c kernel/execve/dd/hdd.c     -I include/ $(CFLAGS) -o hdd.o		
	gcc -c kernel/execve/dd/pic.c     -I include/ $(CFLAGS) -o pic.o 	
	gcc -c kernel/execve/dd/rtc.c     -I include/ $(CFLAGS) -o rtc.o	
	gcc -c kernel/execve/dd/screen.c  -I include/ $(CFLAGS) -o screen.o 	
	gcc -c kernel/execve/dd/timer.c   -I include/ $(CFLAGS) -o timer.o	
	gcc -c kernel/execve/dd/video.c   -I include/ $(CFLAGS) -o video.o  	
	gcc -c kernel/execve/dd/vsync.c   -I include/ $(CFLAGS) -o vsync.o 	
	
	
	# dd/devmgr
	gcc -c kernel/execve/dd/devmgr/devmgr.c  -I include/ $(CFLAGS) -o devmgr.o	
	
	
	
	#dd/i8042
	gcc -c kernel/execve/dd/i8042/i8042.c     -I include/ $(CFLAGS) -o i8042.o
	gcc -c kernel/execve/dd/i8042/ps2mouse.c  -I include/ $(CFLAGS) -o ps2mouse.o
	gcc -c kernel/execve/dd/i8042/ps2kbd.c    -I include/ $(CFLAGS) -o ps2kbd.o  	
	gcc -c kernel/execve/dd/i8042/keyboard.c  -I include/ $(CFLAGS) -o keyboard.o
	gcc -c kernel/execve/dd/i8042/mouse.c     -I include/ $(CFLAGS) -o mouse.o  		
	
	#dd/ldisc
	gcc -c kernel/execve/dd/ldisc/ldisc.c     -I include/ $(CFLAGS) -o ldisc.o 
		
	#dd/pci
	gcc -c kernel/execve/dd/pci/pci.c      -I include/ $(CFLAGS) -o pci.o  
	
	
	gcc -c kernel/execve/dd/network/intel.c    -I include/ $(CFLAGS) -o nicintel.o
	gcc -c kernel/execve/dd/network/network.c  -I include/ $(CFLAGS) -o network.o
	gcc -c kernel/execve/dd/network/socket.c   -I include/ $(CFLAGS) -o socket.o
	
	# dd/tty
	gcc -c kernel/execve/dd/tty/tty.c     -I include/ $(CFLAGS) -o tty.o		

	# dd/usb
	gcc -c kernel/execve/dd/usb/usb.c   -I include/ $(CFLAGS) -o usb.o		


	# /fs
	gcc -c kernel/execve/fs/fs.c      -I include/ $(CFLAGS) -o fs.o	
	gcc -c kernel/execve/fs/read.c    -I include/ $(CFLAGS) -o read.o	
	gcc -c kernel/execve/fs/write.c   -I include/ $(CFLAGS) -o write.o	
	gcc -c kernel/execve/fs/cf.c      -I include/ $(CFLAGS) -o cf.o	
	gcc -c kernel/execve/fs/search.c  -I include/ $(CFLAGS) -o search.o	
	gcc -c kernel/execve/fs/format.c  -I include/ $(CFLAGS) -o format.o	
	gcc -c kernel/execve/fs/vfs.c     -I include/ $(CFLAGS) -o vfs.o	

	# /sci
	gcc -c kernel/execve/sci/services.c  -I include/ $(CFLAGS) -o services.o	
	
	#/sm
	gcc -c kernel/execve/sm/init/init.c        -I include/ $(CFLAGS) -o init.o
	gcc -c kernel/execve/sm/ob/object.c        -I include/ $(CFLAGS) -o object.o		
	gcc -c kernel/execve/sm/sys/modules.c  -I include/ $(CFLAGS) -o modules.o
	gcc -c kernel/execve/sm/sys/proc.c     -I include/ $(CFLAGS) -o proc.o	
	gcc -c kernel/execve/sm/sys/abort.c    -I include/ $(CFLAGS) -o abort.o	
	gcc -c kernel/execve/sm/sys/info.c     -I include/ $(CFLAGS) -o info.o	
	gcc -c kernel/execve/sm/sys/sm.c       -I include/ $(CFLAGS) -o sm.o
	gcc -c kernel/execve/sm/sys/channel.c  -I include/ $(CFLAGS) -o channel.o	
	gcc -c kernel/execve/sm/sys/signal.c   -I include/ $(CFLAGS) -o signal.o	
	gcc -c kernel/execve/sm/sys/system.c   -I include/ $(CFLAGS) -o system.o
	gcc -c kernel/execve/sm/sys/io.c       -I  include/ $(CFLAGS) -o io.o	
	gcc -c kernel/execve/dd/sm/rt/runtime.c   -I include/ $(CFLAGS) -o runtime.o
	gcc -c kernel/execve/dd/sm/disk/diskvol.c    -I include/ $(CFLAGS) -o diskvol.o
	gcc -c kernel/execve/dd/sm/install/install.c  -I include/ $(CFLAGS) -o install.o    
	gcc -c kernel/execve/dd/sm/debug/debug.c      -I include/ $(CFLAGS) -o debug.o	
	
	
	#rem echo ~{ ...
	#echo ~{ ux1 /gws \o/	

	# k\gws\gws	
	# Gramado Window Server.
	gcc -c kernel/gws/gws/char.c      -I include/ $(CFLAGS) -o char.o
	gcc -c kernel/gws/gws/pixel.c     -I include/ $(CFLAGS) -o pixel.o 
	gcc -c kernel/gws/gws/line.c      -I include/ $(CFLAGS) -o line.o
	gcc -c kernel/gws/gws/rect.c      -I include/ $(CFLAGS) -o rect.o 
	gcc -c kernel/gws/gws/dtext.c     -I include/ $(CFLAGS) -o dtext.o
	gcc -c kernel/gws/gws/font.c      -I include/ $(CFLAGS) -o font.o
	gcc -c kernel/gws/gws/createw.c   -I include/ $(CFLAGS) -o createw.o    
	gcc -c kernel/gws/gws/grid.c      -I include/ $(CFLAGS) -o grid.o 
	gcc -c kernel/gws/gws/sbar.c      -I include/ $(CFLAGS) -o sbar.o 
	gcc -c kernel/gws/gws/menubar.c   -I include/ $(CFLAGS) -o menubar.o 
	gcc -c kernel/gws/gws/menu.c      -I include/ $(CFLAGS) -o menu.o 
	gcc -c kernel/gws/gws/bmp.c       -I include/ $(CFLAGS) -o bmp.o 
	gcc -c kernel/gws/gws/button.c    -I include/ $(CFLAGS) -o button.o 
	gcc -c kernel/gws/gws/bg.c        -I include/ $(CFLAGS) -o bg.o  
	gcc -c kernel/gws/gws/window.c    -I include/ $(CFLAGS) -o window.o    
	

	# gramado logon e logoff
	gcc -c kernel/gws/logon/logon.c    -I include/ $(CFLAGS) -o logon.o 
	gcc -c kernel/gws/logoff/logoff.c  -I include/ $(CFLAGS) -o logoff.o 

	# gramado/user
	gcc -c kernel/gws/user/userenv.c   -I include/ $(CFLAGS) -o userenv.o 	
	gcc -c kernel/gws/user/desktop.c   -I include/ $(CFLAGS) -o desktop.o  
	gcc -c kernel/gws/user/room.c      -I include/ $(CFLAGS) -o room.o 
	gcc -c kernel/gws/user/usession.c  -I include/ $(CFLAGS) -o usession.o 

	# *gui (GRAMADO)
	gcc -c kernel/gws/gws.c   -I include/ $(CFLAGS) -o gws.o 
	
	#bugbug:
	#todo: usar uma lista ordenada de objetos.
	
link-x86:
	ld -m i386pe -T kernel/link.ld -o KERNEL.BIN $(myObjects) -Map kernel/kmap.s
	# ld -m i386pe -T kernel/link.ld -o KERNEL.BIN $(wildcard *.o) -Map kernel/kmap.s
	# gcc -T kernel/link.ld -fno-pie -no-pie -ffreestanding -nostdlib -o KERNEL.BIN $(myObjects)
    # gcc -T kernel/link.ld -fno-pie -no-pie -ffreestanding -nostdlib -o KERNEL.BIN $(myObjects) -Wl,-Map=kernel/kmap.s -lgcc"
	
	
vhd-x86:
	nasm -I c:/gramado/arch/x86/boot/vhd/stage1/ \
	-I c:/gramado/arch/x86/boot/vhd/stage2/ \
	-I c:/gramado/arch/x86/boot/vhd/stage2/lib16/ \
	-I c:/gramado/arch/x86/boot/vhd/stage2/include/ \
	-I c:/gramado/arch/x86/boot/vhd/msm/ \
	-I c:/gramado/arch/x86/boot/vhd/msm/lib32/ \
	-I c:/gramado/arch/x86/boot/vhd/msm/include/ \
	-I c:/gramado/arch/x86/boot/vhd/msm/kernel/ \
	-I c:/gramado/arch/x86/boot/vhd/msm/fs/ \
	-I c:/gramado/arch/x86/boot/vhd/msm/shell/ \
	-I c:/gramado/arch/x86/boot/vhd/msm/drivers/ \
	-I c:/gramado/arch/x86/boot/vhd/bl/ \
	-I c:/gramado/arch/x86/boot/vhd/kernel/ \
	-I c:/gramado/arch/x86/boot/vhd/browser/  c:/gramado/arch/x86/boot/vhd/main.asm  -o  GRAMADO.VHD

clean:
	find . -type f -name '*.o' -delete
