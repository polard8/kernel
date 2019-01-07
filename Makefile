
# I'm working on this script to compile Holambra kernel
# and put it into the VHD.

#
# /bin/bash
# SPDX-License-Identifier: GPL-3.0+
# BSD License
#
# History:
# 2018 - Created by Matheus Castello.
# 2019 - Fred Nora.
# 2019 - Luciano Gonçalez.


VERSION = 0
PATCHLEVEL = 4
SUBLEVEL = 0
EXTRAVERSION =
NAME = Style

#todo:
#We need to simplify these flags

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
portsx86.o \
x86.o \
stdio.o \
stdlib.o \
string.o \
tty.o \
init.o \
logon.o \
logoff.o \
detect.o \
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
x86start.o \
x86cont.o \
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
serial.o \
debug.o \
abort.o \
x86fault.o \
services.o



# check dependencies this works only in debian based distros
#if [ $(dpkg-query -W -f='${Status}' nasm 2>/dev/null | grep -c "ok installed") -eq 0 ];
#then
	# sudo apt-get install nasm
#fi

#if [ $(dpkg-query -W -f='${Status}' binutils 2>/dev/null | grep -c "ok installed") -eq 0 ];
#then
	# sudo apt-get install binutils
#fi

#if [ $(dpkg-query -W -f='${Status}' gcc 2>/dev/null | grep -c "ok installed") -eq 0 ];
#then
	# sudo apt-get install gcc
#fi

#if [ $(dpkg-query -W -f='${Status}' make 2>/dev/null | grep -c "ok installed") -eq 0 ];
#then
	# sudo apt-get install make
#fi

    #ISSO DIZ QUE O ALVO NAO EH ARQUIVO
	#É para informar ao make não procurar por um arquivo com esse nome

	#.PHONY x86

xxx_x86: /mnt/holambravhd compile-kernel link-x86 vhd-x86 vhd-mount vhd-copy-files vhd-unmount clean

compile-kernel:
	gcc -c kernel/3rdparty/kernel/disk/disk1.c   -I include/ $(CFLAGS) -o disk1.o

	# /entry
	nasm -I kernel/entry/x86/head/ kernel/entry/x86/head/head.s -f elf -o head.o
	gcc -c kernel/entry/x86/x86main.c  -I include/ $(CFLAGS) -o x86main.o

	# /hal
	gcc -c kernel/hal/hal.c                -I include/ $(CFLAGS) -o hal.o
	gcc -c kernel/hal/arch/detect.c        -I include/ $(CFLAGS) -o detect.o
	gcc -c kernel/hal/arch/amd/cpuamd.c    -I include/ $(CFLAGS) -o cpuamd.o
	gcc -c kernel/hal/arch/x86/portsx86.c  -I include/ $(CFLAGS) -o portsx86.o
	gcc -c kernel/hal/arch/x86/syscall.c   -I include/ $(CFLAGS) -o syscall.o
	gcc -c kernel/hal/arch/x86/x86.c       -I include/ $(CFLAGS) -o x86.o

	# /mk
	gcc -c  kernel/mk/mk.c -I include/  $(CFLAGS) -o mk.o

	# /cpu
	gcc -c  kernel/mk/arch/x86/x86cont.c   -I include/  $(CFLAGS) -o x86cont.o
	gcc -c  kernel/mk/arch/x86/x86start.c  -I include/  $(CFLAGS) -o x86start.o

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

	gcc -c  kernel/mk/request.c  -I include/ $(CFLAGS) -o request.o
	gcc -c  kernel/mk/arch/x86/x86fault.c  -I include/ $(CFLAGS) -o x86fault.o

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

	gcc -c kernel/execve/dd/serial.c  -I include/ $(CFLAGS) -o serial.o

	# dd/devmgr
	gcc -c kernel/execve/dd/devmgr/devmgr.c  -I include/ $(CFLAGS) -o devmgr.o

	#dd/i8042
	gcc -c kernel/execve/dd/i8042/i8042.c     -I include/ $(CFLAGS) -o i8042.o
	gcc -c kernel/execve/dd/i8042/keyboard.c  -I include/ $(CFLAGS) -o keyboard.o
	gcc -c kernel/execve/dd/i8042/mouse.c     -I include/ $(CFLAGS) -o mouse.o
	gcc -c kernel/execve/dd/i8042/ps2kbd.c    -I include/ $(CFLAGS) -o ps2kbd.o
	gcc -c kernel/execve/dd/i8042/ps2mouse.c  -I include/ $(CFLAGS) -o ps2mouse.o


	#dd/ldisc
	gcc -c kernel/execve/dd/ldisc/ldisc.c  -I include/ $(CFLAGS) -o ldisc.o

	#dd/pci
	gcc -c kernel/execve/dd/pci/pci.c  -I include/ $(CFLAGS) -o pci.o

	gcc -c kernel/execve/dd/network/intel.c    -I include/ $(CFLAGS) -o nicintel.o
	gcc -c kernel/execve/dd/network/network.c  -I include/ $(CFLAGS) -o network.o
	gcc -c kernel/execve/dd/network/socket.c   -I include/ $(CFLAGS) -o socket.o

	# dd/tty
	gcc -c kernel/execve/dd/tty/tty.c  -I include/ $(CFLAGS) -o tty.o

	# dd/usb
	gcc -c kernel/execve/dd/usb/usb.c  -I include/ $(CFLAGS) -o usb.o

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
	gcc -c kernel/execve/sm/init/init.c    -I include/ $(CFLAGS) -o init.o
	gcc -c kernel/execve/sm/ob/object.c    -I include/ $(CFLAGS) -o object.o
	gcc -c kernel/execve/sm/sys/modules.c  -I include/ $(CFLAGS) -o modules.o
	gcc -c kernel/execve/sm/sys/proc.c     -I include/ $(CFLAGS) -o proc.o
	gcc -c kernel/execve/sm/sys/abort.c    -I include/ $(CFLAGS) -o abort.o
	gcc -c kernel/execve/sm/sys/info.c     -I include/ $(CFLAGS) -o info.o
	gcc -c kernel/execve/sm/sys/sm.c       -I include/ $(CFLAGS) -o sm.o
	gcc -c kernel/execve/sm/sys/channel.c  -I include/ $(CFLAGS) -o channel.o
	gcc -c kernel/execve/sm/sys/signal.c   -I include/ $(CFLAGS) -o signal.o
	gcc -c kernel/execve/sm/sys/system.c   -I include/ $(CFLAGS) -o system.o
	gcc -c kernel/execve/sm/sys/io.c       -I  include/ $(CFLAGS) -o io.o
	gcc -c kernel/execve/sm/rt/runtime.c       -I include/ $(CFLAGS) -o runtime.o
	gcc -c kernel/execve/sm/disk/diskvol.c     -I include/ $(CFLAGS) -o diskvol.o
	gcc -c kernel/execve/sm/install/install.c  -I include/ $(CFLAGS) -o install.o
	gcc -c kernel/execve/sm/debug/debug.c      -I include/ $(CFLAGS) -o debug.o

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
	ld -m i386pe -T kernel/link.ld -o KERNEL.BIN $(myObjects) -Map kmap.s
	# ld -m i386pe -T kernel/link.ld -o KERNEL.BIN $(wildcard *.o) -Map kernel/kmap.s
	# gcc -T kernel/link.ld -fno-pie -no-pie -ffreestanding -nostdlib -o KERNEL.BIN $(myObjects)
    # gcc -T kernel/link.ld -fno-pie -no-pie -ffreestanding -nostdlib -o KERNEL.BIN $(myObjects) -Wl,-Map=kernel/kmap.s -lgcc"

	mv KERNEL.BIN bin/
# clean the output trash
	# make clean

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
	-I arch/x86/boot/vhd/browser/  arch/x86/boot/vhd/main.asm  -o  HOLAMBRA.VHD


# mount
	#sudo mkdir /mnt/noraxvhd
	#sudo mkdir /mnt/noraxvhd
	#sudo mount -o loop,offset=32256 NORAX.VHD /mnt/noraxvhd/

vhd-mount:
	-sudo umount /mnt/holambravhd
	sudo mount -t vfat -o loop,offset=32256 HOLAMBRA.VHD /mnt/holambravhd/

##
# Copy content to disk
##
vhd-copy-files:
	sudo cp bin/BM.BIN       /mnt/holambravhd
	sudo cp bin/BL.BIN       /mnt/holambravhd
	sudo cp bin/KERNEL.BIN   /mnt/holambravhd
	sudo cp bin/INIT.BIN     /mnt/holambravhd
	sudo cp bin/SHELL.BIN    /mnt/holambravhd
	sudo cp bin/TASKMAN.BIN  /mnt/holambravhd
	
	sudo cp bin/JACKPOT.BIN  /mnt/holambravhd
	sudo cp bin/TASCII.BIN   /mnt/holambravhd
	sudo cp bin/CHTEST.BIN   /mnt/holambravhd
	
# configs
	sudo cp arch/x86/boot/vhd/INIT.TXT /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/USER.TXT /mnt/holambravhd

# bitmaps
	sudo cp arch/x86/boot/vhd/images/BMP1.BMP      /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/MOUSE.BMP     /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/DENNIS.BMP    /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/APP.BMP       /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/FILE.BMP      /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/FOLDER.BMP    /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/TERMINAL.BMP  /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/CURSOR.BMP    /mnt/holambravhd

# fonts
	sudo cp bin/NC2.FON /mnt/holambravhd

	# sudo cp bin/FCLASS.BIN   /mnt/noraxvhd
	# sudo cp bin/GRAMCC.BIN   /mnt/noraxvhd
	# sudo cp bin/JACKPOT.BIN  /mnt/noraxvhd
	# sudo cp bin/TASCII.BIN   /mnt/noraxvhd
	# sudo cp bin/TEDITOR.BIN  /mnt/noraxvhd
	# sudo cp bin/TGFE.BIN     /mnt/noraxvhd

# umount
vhd-unmount:
	sudo umount /mnt/holambravhd




/mnt/holambravhd:
	sudo mkdir /mnt/holambravhd

clean:
	#find . -type f -name '*.o' -delete
	-rm *.o

	@echo "Success?"
