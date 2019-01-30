
# Compiling Gramado on Manjaro Linux.
# Chamaremos cada alvo que terá seu makefile em sua própria pasta.

# /bin/bash
# SPDX-License-Identifier: GPL-3.0+
# BSD License
#
# History:
# 2018 - Created by Matheus Castello.
# 2019 - Fred Nora.
# 2019 - Luciano Gonçalez.


VERSION = 0
PATCHLEVEL = 10
SUBLEVEL = 0
EXTRAVERSION = -rc0
NAME = ?

#important
#We will have a new name just when the release changes.


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
	
#	-fleading-underscore \
#	-fno-stack-protector \
#	-s

##
## Defines
##

DEFINES = 	-DGRAMADO_VERSION=$(VERSION) \
		-DGRAMADO_PATCHLEVEL=$(PATCHLEVEL) \
		-DGRAMADO_SUBLEVEL=$(SUBLEVEL) \
		-DGRAMADO_EXTRAVERSION=\"$(EXTRAVERSION)\" \
		-DGRAMAD0_NAME=\"$(NAME)\"

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
ahci.o \
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




#importante
#Aqui ficarão os alvos principais, como configurações
#os cripts ficarão em /scripts
#os alvos aqui chama chama os scripts

#ISSO DIZ QUE O ALVO NAO EH ARQUIVO
#É para informar ao make não procurar por um arquivo com esse nome
#.PHONY x86

xxx_x86: /mnt/gramadovhd compile-kernel link-x86 vhd-x86 vhd-mount vhd-copy-files vhd-unmount clean

compile-kernel:

	# /entry
	nasm -I kernel/entry/x86/head/ kernel/entry/x86/head/head.s -f elf -o head.o
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
	gcc -c  kernel/mk/pc/ipc/sem.c      -I include/  $(CFLAGS) $(DEFINES) -o sem.o

	# mk/pc/sched
	gcc -c  kernel/mk/pc/sched/sched.c   -I include/ $(CFLAGS) $(DEFINES) -o sched.o
	gcc -c  kernel/mk/pc/sched/schedi.c  -I include/ $(CFLAGS) $(DEFINES) -o schedi.o

	# /mk/pc/mm (memory manager)
	gcc -c  kernel/mk/pc/mm/memory.c  -I include/ $(CFLAGS) $(DEFINES) -o memory.o
	gcc -c  kernel/mk/pc/mm/pages.c   -I include/ $(CFLAGS) $(DEFINES) -o pages.o

	gcc -c  kernel/mk/request.c  -I include/ $(CFLAGS) $(DEFINES) -o request.o
	gcc -c  kernel/mk/arch/x86/x86fault.c  -I include/ $(CFLAGS) $(DEFINES) -o x86fault.o

	# /execve
	gcc -c kernel/execve/execve.c  -I include/ $(CFLAGS) $(DEFINES) -o execve.o

	# crts
	# /execve/crts/libc
	gcc -c kernel/execve/crts/libc/cedge.c   -I include/ $(CFLAGS) $(DEFINES) -o cedge.o
	gcc -c kernel/execve/crts/libc/ctype.c   -I include/ $(CFLAGS) $(DEFINES) -o ctype.o
	gcc -c kernel/execve/crts/libc/stdlib.c  -I include/ $(CFLAGS) $(DEFINES) -o stdlib.o
	gcc -c kernel/execve/crts/libc/stdio.c   -I include/ $(CFLAGS) $(DEFINES) -o stdio.o
	gcc -c kernel/execve/crts/libc/string.c  -I include/ $(CFLAGS) $(DEFINES) -o string.o

	gcc -c kernel/execve/dd/apic.c    -I include/ $(CFLAGS) $(DEFINES) -o apic.o
	
	gcc -c kernel/execve/dd/ide/hdd.c     -I include/ $(CFLAGS) $(DEFINES) -o hdd.o
	gcc -c kernel/execve/dd/ide/disk1.c   -I include/ $(CFLAGS) $(DEFINES) -o disk1.o
	
	gcc -c kernel/execve/dd/pic.c     -I include/ $(CFLAGS) $(DEFINES) -o pic.o
	gcc -c kernel/execve/dd/rtc.c     -I include/ $(CFLAGS) $(DEFINES) -o rtc.o
	gcc -c kernel/execve/dd/screen.c  -I include/ $(CFLAGS) $(DEFINES) -o screen.o
	gcc -c kernel/execve/dd/timer.c   -I include/ $(CFLAGS) $(DEFINES) -o timer.o
	gcc -c kernel/execve/dd/video.c   -I include/ $(CFLAGS) $(DEFINES) -o video.o
	gcc -c kernel/execve/dd/vsync.c   -I include/ $(CFLAGS) $(DEFINES) -o vsync.o

	gcc -c kernel/execve/dd/serial.c  -I include/ $(CFLAGS) $(DEFINES) -o serial.o

	# dd/ahci 
	gcc -c kernel/execve/dd/ahci/ahci.c  -I include/ $(CFLAGS) $(DEFINES) -o ahci.o
	
	# dd/devmgr
	gcc -c kernel/execve/dd/devmgr/devmgr.c  -I include/ $(CFLAGS) $(DEFINES) -o devmgr.o

	# dd/i8042
	gcc -c kernel/execve/dd/i8042/i8042.c     -I include/ $(CFLAGS) $(DEFINES) -o i8042.o
	gcc -c kernel/execve/dd/i8042/keyboard.c  -I include/ $(CFLAGS) $(DEFINES) -o keyboard.o
	gcc -c kernel/execve/dd/i8042/mouse.c     -I include/ $(CFLAGS) $(DEFINES) -o mouse.o
	gcc -c kernel/execve/dd/i8042/ps2kbd.c    -I include/ $(CFLAGS) $(DEFINES) -o ps2kbd.o
	gcc -c kernel/execve/dd/i8042/ps2mouse.c  -I include/ $(CFLAGS) $(DEFINES) -o ps2mouse.o


	# dd/ldisc
	gcc -c kernel/execve/dd/ldisc/ldisc.c  -I include/ $(CFLAGS) $(DEFINES) -o ldisc.o

	# dd/pci
	gcc -c kernel/execve/dd/pci/pci.c  -I include/ $(CFLAGS) $(DEFINES) -o pci.o

	gcc -c kernel/execve/dd/network/intel.c    -I include/ $(CFLAGS) $(DEFINES) -o nicintel.o
	gcc -c kernel/execve/dd/network/network.c  -I include/ $(CFLAGS) $(DEFINES) -o network.o
	gcc -c kernel/execve/dd/network/socket.c   -I include/ $(CFLAGS) $(DEFINES) -o socket.o

	# dd/tty
	gcc -c kernel/execve/dd/tty/tty.c  -I include/ $(CFLAGS) $(DEFINES) -o tty.o

	# dd/usb
	gcc -c kernel/execve/dd/usb/usb.c  -I include/ $(CFLAGS) $(DEFINES) -o usb.o

	# /fs
	gcc -c kernel/execve/fs/fs.c      -I include/ $(CFLAGS) $(DEFINES) -o fs.o
	gcc -c kernel/execve/fs/read.c    -I include/ $(CFLAGS) $(DEFINES) -o read.o
	gcc -c kernel/execve/fs/write.c   -I include/ $(CFLAGS) $(DEFINES) -o write.o
	gcc -c kernel/execve/fs/cf.c      -I include/ $(CFLAGS) $(DEFINES) -o cf.o
	gcc -c kernel/execve/fs/search.c  -I include/ $(CFLAGS) $(DEFINES) -o search.o
	gcc -c kernel/execve/fs/format.c  -I include/ $(CFLAGS) $(DEFINES) -o format.o
	gcc -c kernel/execve/fs/vfs.c     -I include/ $(CFLAGS) $(DEFINES) -o vfs.o

	# /sci
	gcc -c kernel/execve/sci/services.c  -I include/ $(CFLAGS) $(DEFINES) -o services.o

	# /sm
	gcc -c kernel/execve/sm/init/init.c    -I include/ $(CFLAGS) $(DEFINES) -o init.o
	gcc -c kernel/execve/sm/ob/object.c    -I include/ $(CFLAGS) $(DEFINES) -o object.o
	gcc -c kernel/execve/sm/sys/modules.c  -I include/ $(CFLAGS) $(DEFINES) -o modules.o
	gcc -c kernel/execve/sm/sys/proc.c     -I include/ $(CFLAGS) $(DEFINES) -o proc.o
	gcc -c kernel/execve/sm/sys/abort.c    -I include/ $(CFLAGS) $(DEFINES) -o abort.o
	gcc -c kernel/execve/sm/sys/info.c     -I include/ $(CFLAGS) $(DEFINES) -o info.o
	gcc -c kernel/execve/sm/sys/sm.c       -I include/ $(CFLAGS) $(DEFINES) -o sm.o
	gcc -c kernel/execve/sm/sys/channel.c  -I include/ $(CFLAGS) $(DEFINES) -o channel.o
	gcc -c kernel/execve/sm/sys/signal.c   -I include/ $(CFLAGS) $(DEFINES) -o signal.o
	gcc -c kernel/execve/sm/sys/system.c   -I include/ $(CFLAGS) $(DEFINES) -o system.o
	gcc -c kernel/execve/sm/sys/io.c       -I  include/ $(CFLAGS) $(DEFINES) -o io.o
	gcc -c kernel/execve/sm/rt/runtime.c       -I include/ $(CFLAGS) $(DEFINES) -o runtime.o
	gcc -c kernel/execve/sm/disk/diskvol.c     -I include/ $(CFLAGS) $(DEFINES) -o diskvol.o
	gcc -c kernel/execve/sm/install/install.c  -I include/ $(CFLAGS) $(DEFINES) -o install.o
	gcc -c kernel/execve/sm/debug/debug.c      -I include/ $(CFLAGS) $(DEFINES) -o debug.o

	# k\gws\gws
	# Gramado Window Server.
	gcc -c kernel/gws/gws/char.c      -I include/ $(CFLAGS) $(DEFINES) -o char.o
	gcc -c kernel/gws/gws/pixel.c     -I include/ $(CFLAGS) $(DEFINES) -o pixel.o
	gcc -c kernel/gws/gws/line.c      -I include/ $(CFLAGS) $(DEFINES) -o line.o
	gcc -c kernel/gws/gws/rect.c      -I include/ $(CFLAGS) $(DEFINES) -o rect.o
	gcc -c kernel/gws/gws/dtext.c     -I include/ $(CFLAGS) $(DEFINES) -o dtext.o
	gcc -c kernel/gws/gws/font.c      -I include/ $(CFLAGS) $(DEFINES) -o font.o
	gcc -c kernel/gws/gws/createw.c   -I include/ $(CFLAGS) $(DEFINES) -o createw.o
	gcc -c kernel/gws/gws/grid.c      -I include/ $(CFLAGS) $(DEFINES) -o grid.o
	gcc -c kernel/gws/gws/sbar.c      -I include/ $(CFLAGS) $(DEFINES) -o sbar.o
	gcc -c kernel/gws/gws/menubar.c   -I include/ $(CFLAGS) $(DEFINES) -o menubar.o
	gcc -c kernel/gws/gws/menu.c      -I include/ $(CFLAGS) $(DEFINES) -o menu.o
	gcc -c kernel/gws/gws/bmp.c       -I include/ $(CFLAGS) $(DEFINES) -o bmp.o
	gcc -c kernel/gws/gws/button.c    -I include/ $(CFLAGS) $(DEFINES) -o button.o
	gcc -c kernel/gws/gws/bg.c        -I include/ $(CFLAGS) $(DEFINES) -o bg.o
	gcc -c kernel/gws/gws/window.c    -I include/ $(CFLAGS) $(DEFINES) -o window.o

	# gramado logon e logoff
	gcc -c kernel/gws/logon/logon.c    -I include/ $(CFLAGS) $(DEFINES) -o logon.o
	gcc -c kernel/gws/logoff/logoff.c  -I include/ $(CFLAGS) $(DEFINES) -o logoff.o

	# gramado/user
	gcc -c kernel/gws/user/userenv.c   -I include/ $(CFLAGS) $(DEFINES) -o userenv.o
	gcc -c kernel/gws/user/desktop.c   -I include/ $(CFLAGS) $(DEFINES) -o desktop.o
	gcc -c kernel/gws/user/room.c      -I include/ $(CFLAGS) $(DEFINES) -o room.o
	gcc -c kernel/gws/user/usession.c  -I include/ $(CFLAGS) $(DEFINES) -o usession.o

	# *gui (GRAMADO)
	gcc -c kernel/gws/gws.c   -I include/ $(CFLAGS) $(DEFINES) -o gws.o


link-x86:
	ld -m i386pe -T kernel/link.ld -o KERNEL.BIN $(myObjects) -Map docs/kmap.s
	# ld -m i386pe -T kernel/link.ld -o KERNEL.BIN $(wildcard *.o) -Map kernel/kmap.s
	# gcc -T kernel/link.ld -fno-pie -no-pie -ffreestanding -nostdlib -o KERNEL.BIN $(myObjects)
    # gcc -T kernel/link.ld -fno-pie -no-pie -ffreestanding -nostdlib -o KERNEL.BIN $(myObjects) -Wl,-Map=kernel/kmap.s -lgcc"

	mv KERNEL.BIN bin/

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
	-I arch/x86/boot/vhd/browser/  arch/x86/boot/vhd/main.asm  -o  GRAMADO.VHD


vhd-mount:
	-sudo umount /mnt/gramadovhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadovhd/

# Copy content to disk
# 1) BM, BL 
# 2) KERNEL 
# 3) INIT, SHELL, TASKMAN
vhd-copy-files:
	sudo cp bin/BM.BIN       /mnt/gramadovhd
	sudo cp bin/BL.BIN       /mnt/gramadovhd
	
	sudo cp bin/KERNEL.BIN   /mnt/gramadovhd
	
	sudo cp bin/INIT.BIN     /mnt/gramadovhd
	sudo cp bin/SHELL.BIN    /mnt/gramadovhd
	sudo cp bin/TASKMAN.BIN  /mnt/gramadovhd
	
# configs
	sudo cp arch/x86/boot/vhd/INIT.TXT /mnt/gramadovhd
	sudo cp arch/x86/boot/vhd/USER.TXT /mnt/gramadovhd

# bitmaps
	sudo cp arch/x86/boot/vhd/images/BMP1.BMP      /mnt/gramadovhd
	sudo cp arch/x86/boot/vhd/images/MOUSE.BMP     /mnt/gramadovhd
	sudo cp arch/x86/boot/vhd/images/APP.BMP       /mnt/gramadovhd
	sudo cp arch/x86/boot/vhd/images/FILE.BMP      /mnt/gramadovhd
	sudo cp arch/x86/boot/vhd/images/FOLDER.BMP    /mnt/gramadovhd
	sudo cp arch/x86/boot/vhd/images/TERMINAL.BMP  /mnt/gramadovhd
	sudo cp arch/x86/boot/vhd/images/CURSOR.BMP    /mnt/gramadovhd
	
	-sudo cp arch/x86/boot/vhd/images/DENNIS.BMP    /mnt/gramadovhd
	
# fonts
	sudo cp bin/NC2.FON /mnt/gramadovhd
	
#gde suppport
	-sudo mkdir /mnt/gramadovhd/gde
	-sudo mkdir /mnt/gramadovhd/gde/bin	
	-sudo cp ../gde/bin/* /mnt/gramadovhd/gde/bin 
	
	
	
#Get available apps
#	-sudo cp ../gde/apps/gt/chasm/build/CHTEST.BIN /mnt/gramadovhd 
	-sudo cp ../gde/bin/GRAMCODE.BIN /mnt/gramadovhd 
	-sudo cp ../gde/bin/GDESHELL.BIN /mnt/gramadovhd 
	-sudo cp ../gde/bin/SPR.BIN /mnt/gramadovhd 
	-sudo cp ../gde/bin/CHASM32.BIN /mnt/gramadovhd 
	
	-sudo cp arch/x86/boot/vhd/tests/TEST1.ASM /mnt/gramadovhd

# umount
vhd-unmount:
	sudo umount /mnt/gramadovhd

/mnt/gramadovhd:
	sudo mkdir /mnt/gramadovhd

clean:
	-rm *.o

	@echo "Success?"
