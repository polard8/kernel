
# todo:
# The first goal of this makefile is 
# mount the assembly files 
# in the folder kernel/1pump/arch/x86_64/pumpcore/
# Evething starts in the file head_64.asm

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
	-fleading-underscore \
	-fno-stack-protector \
	-s \
	-Werror=strict-prototypes    


KINCLUDE = -I include/


# ========================
# Objects

OBJECTS := head_64.o main.o x64init.o \
ctype.o kstdio.o stdlib.o string.o unistd.o runtime.o system.o signal.o \
init.o debug.o info.o \
ports64.o pit.o rtc.o x64.o x64info.o hal.o detect.o \
pci.o pciinfo.o pciscan.o devmgr.o\
console.o tty.o video.o vsync.o screen.o serial.o \
storage.o \
ata.o atadma.o atahdd.o atainit.o atairq.o atapci.o \
i8042.o ps2kbd.o ps2mouse.o keyboard.o mouse.o \
font.o \
fs.o socket.o pipe.o search.o \
disk_r.o disk_w.o \
sys.o \
io.o ws.o \
pixel.o bg.o char.o dtext.o line.o rect.o \
kgws.o kgwm.o vt.o \
desktop.o room.o userenv.o usession.o \
ts.o dispatch.o spawn.o x64cont.o x64fault.o \
sched.o schedi.o \
process.o thread.o threadi.o create.o queue.o mk.o \
memory.o mminfo.o mmpool.o pages.o \
panic.o reboot.o request.o    



all: kernel-head all-c link-kernel clean

kernel-head:

# The x86 head of the monster.

# provisorio
	nasm 1pump/arch/x86_64/pumpcore/head_64.asm \
	$(KINCLUDE) \
	-I 1pump/arch/x86_64/pumpcore/ \
	-f elf64 -o head_64.o


all-c:

#
# == main ======== 
#

	#$(CC) -c main.c  $(KINCLUDE) $(CFLAGS) -o main.o
	gcc -c main.c  $(KINCLUDE) $(CFLAGS) -o main.o

#
# == 0mem ======== 
#

	gcc -c 0mem/panic.c    $(KINCLUDE) $(CFLAGS) -o panic.o
	gcc -c 0mem/reboot.c   $(KINCLUDE) $(CFLAGS) -o reboot.o
	gcc -c 0mem/request.c  $(KINCLUDE) $(CFLAGS) -o request.o


	# == Gramado Core ====
	# Architecture independent layer.

	gcc -c 0mem/core/info.c     $(KINCLUDE) $(CFLAGS) -o info.o
	gcc -c 0mem/core/init.c     $(KINCLUDE) $(CFLAGS) -o init.o
	gcc -c 0mem/core/runtime.c  $(KINCLUDE) $(CFLAGS) -o runtime.o
	gcc -c 0mem/core/system.c   $(KINCLUDE) $(CFLAGS) -o system.o

	# debug
	gcc -c 0mem/core/debug/debug.c  $(KINCLUDE) $(CFLAGS) -o debug.o

	# ps
	gcc -c 0mem/core/ps/process.c  $(KINCLUDE) $(CFLAGS) -o process.o
	gcc -c 0mem/core/ps/thread.c   $(KINCLUDE) $(CFLAGS) -o thread.o
	gcc -c 0mem/core/ps/threadi.c  $(KINCLUDE) $(CFLAGS) -o threadi.o
	gcc -c 0mem/core/ps/create.c   $(KINCLUDE) $(CFLAGS) -o create.o
	gcc -c 0mem/core/ps/x86_64/x64fault.c      $(KINCLUDE) $(CFLAGS) -o x64fault.o
	gcc -c 0mem/core/ps/queue.c  $(KINCLUDE) $(CFLAGS) -o queue.o
	gcc -c 0mem/core/ps/mk.c  $(KINCLUDE) $(CFLAGS) -o mk.o

	# ps/disp
	gcc -c 0mem/core/ps/disp/ts.c   $(KINCLUDE)  $(CFLAGS) -o ts.o  
	gcc -c 0mem/core/ps/disp/dispatch.c  $(KINCLUDE)  $(CFLAGS) -o dispatch.o  
	gcc -c 0mem/core/ps/disp/spawn.c     $(KINCLUDE)  $(CFLAGS) -o spawn.o  

	gcc -c 0mem/core/ps/disp/x86_64/x64cont.c   $(KINCLUDE)  $(CFLAGS) -o x64cont.o  

	gcc -c 0mem/core/ps/sched/sched.c   $(KINCLUDE)  $(CFLAGS) -o sched.o  
	gcc -c 0mem/core/ps/sched/schedi.c  $(KINCLUDE)  $(CFLAGS) -o schedi.o  


	# 0mem/mm
	gcc -c 0mem/mm/memory.c  $(KINCLUDE) $(CFLAGS) -o memory.o
	gcc -c 0mem/mm/mminfo.c  $(KINCLUDE) $(CFLAGS) -o mminfo.o
	gcc -c 0mem/mm/mmpool.c  $(KINCLUDE) $(CFLAGS) -o mmpool.o
	gcc -c 0mem/mm/pages.c   $(KINCLUDE) $(CFLAGS) -o pages.o


	gcc -c 0mem/sci/net/socket/socket.c  $(KINCLUDE) $(CFLAGS) -o socket.o

	# 0mem/rtl
	gcc -c 0mem/rtl/ctype.c   $(KINCLUDE) $(CFLAGS) -o ctype.o
	gcc -c 0mem/rtl/string.c  $(KINCLUDE) $(CFLAGS) -o string.o
	gcc -c 0mem/rtl/stdlib.c  $(KINCLUDE) $(CFLAGS) -o stdlib.o
	gcc -c 0mem/rtl/kstdio.c  $(KINCLUDE) $(CFLAGS) -o kstdio.o
	gcc -c 0mem/rtl/signal.c  $(KINCLUDE) $(CFLAGS) -o signal.o
	gcc -c 0mem/rtl/unistd.c  $(KINCLUDE) $(CFLAGS) -o unistd.o

	# 0mem/sci/fs
	gcc -c 0mem/sci/fs/fs.c      $(KINCLUDE) $(CFLAGS) -o fs.o
	gcc -c 0mem/sci/fs/pipe.c    $(KINCLUDE) $(CFLAGS) -o pipe.o
	gcc -c 0mem/sci/fs/search.c  $(KINCLUDE) $(CFLAGS) -o search.o

	gcc -c 0mem/sci/fs/sdi/disk_r.c  $(KINCLUDE) $(CFLAGS) -o disk_r.o
	gcc -c 0mem/sci/fs/sdi/disk_w.c  $(KINCLUDE) $(CFLAGS) -o disk_w.o

	gcc -c 0mem/sci/sys/sys.c  $(KINCLUDE) $(CFLAGS) -o sys.o


#
# == 1pump ======== 
#

	gcc -c 1pump/arch/detect.c  $(KINCLUDE) $(CFLAGS) -o detect.o
	gcc -c 1pump/arch/hal.c     $(KINCLUDE) $(CFLAGS) -o hal.o


	# 1pump/arch/x86_64
	gcc -c 1pump/arch/x86_64/pit.c      $(KINCLUDE) $(CFLAGS) -o pit.o
	gcc -c 1pump/arch/x86_64/ports64.c  $(KINCLUDE) $(CFLAGS) -o ports64.o
	gcc -c 1pump/arch/x86_64/rtc.c      $(KINCLUDE) $(CFLAGS) -o rtc.o
	gcc -c 1pump/arch/x86_64/x64init.c  $(KINCLUDE) $(CFLAGS) -o x64init.o
	gcc -c 1pump/arch/x86_64/x64.c      $(KINCLUDE) $(CFLAGS) -o x64.o
	gcc -c 1pump/arch/x86_64/x64info.c  $(KINCLUDE) $(CFLAGS) -o x64info.o


#
# == 2io ======== 
#

	gcc -c 2io/io.c  $(KINCLUDE) $(CFLAGS) -o io.o
	gcc -c 2io/ws.c  $(KINCLUDE) $(CFLAGS) -o ws.o

	# 2io/bus/pcibus/
	gcc -c 2io/bus/pcibus/pci.c     $(KINCLUDE) $(CFLAGS) -o pci.o
	gcc -c 2io/bus/pcibus/pciinfo.c $(KINCLUDE) $(CFLAGS) -o pciinfo.o
	gcc -c 2io/bus/pcibus/pciscan.c $(KINCLUDE) $(CFLAGS) -o pciscan.o



	# 2io/dev/
	gcc -c 2io/dev/devmgr.c  $(KINCLUDE) $(CFLAGS) -o devmgr.o 
	gcc -c 2io/dev/serial.c  $(KINCLUDE) $(CFLAGS) -o serial.o

	# 2io/dev/blkdev
	gcc -c 2io/dev/blkdev/storage.c  $(KINCLUDE) $(CFLAGS) -o storage.o 

	# 2io/dev/blkdev/ide
	gcc -c 2io/dev/blkdev/ide/ata.c      $(KINCLUDE) $(CFLAGS) -o ata.o 
	gcc -c 2io/dev/blkdev/ide/atadma.c   $(KINCLUDE) $(CFLAGS) -o atadma.o 
	gcc -c 2io/dev/blkdev/ide/atahdd.c   $(KINCLUDE) $(CFLAGS) -o atahdd.o 
	gcc -c 2io/dev/blkdev/ide/atainit.c  $(KINCLUDE) $(CFLAGS) -o atainit.o 
	gcc -c 2io/dev/blkdev/ide/atairq.c   $(KINCLUDE) $(CFLAGS) -o atairq.o 
	gcc -c 2io/dev/blkdev/ide/atapci.c   $(KINCLUDE) $(CFLAGS) -o atapci.o 

	# 2io/dev/tty/
	gcc -c 2io/dev/tty/tty.c  $(KINCLUDE) $(CFLAGS) -o tty.o

	# 2io/dev/graphics
	gcc -c 2io/dev/graphics/video.c   $(KINCLUDE) $(CFLAGS) -o video.o
	gcc -c 2io/dev/graphics/vsync.c   $(KINCLUDE) $(CFLAGS) -o vsync.o
	gcc -c 2io/dev/graphics/screen.c  $(KINCLUDE) $(CFLAGS) -o screen.o

	# 2io/dev/hid
	gcc -c 2io/dev/hid/i8042.c     $(KINCLUDE) $(CFLAGS) -o i8042.o
	gcc -c 2io/dev/hid/ps2kbd.c    $(KINCLUDE) $(CFLAGS) -o ps2kbd.o
	gcc -c 2io/dev/hid/ps2mouse.c  $(KINCLUDE) $(CFLAGS) -o ps2mouse.o
	gcc -c 2io/dev/hid/keyboard.c  $(KINCLUDE) $(CFLAGS) -o keyboard.o
	gcc -c 2io/dev/hid/mouse.c     $(KINCLUDE) $(CFLAGS) -o mouse.o


#
# == user ======== 
#

	gcc -c user/kgws.c  $(KINCLUDE) $(CFLAGS) -o kgws.o
	gcc -c user/kgwm.c  $(KINCLUDE) $(CFLAGS) -o kgwm.o

	gcc -c user/vt.c   $(KINCLUDE) $(CFLAGS) -o vt.o

	# ctrl
	gcc -c user/ctrl/console.c   $(KINCLUDE) $(CFLAGS) -o console.o

	# user/model
	gcc -c user/model/font.c  $(KINCLUDE) $(CFLAGS) -o font.o

	# user/security
	gcc -c user/security/desktop.c   $(KINCLUDE) $(CFLAGS) -o desktop.o
	gcc -c user/security/room.c      $(KINCLUDE) $(CFLAGS) -o room.o
	gcc -c user/security/usession.c  $(KINCLUDE) $(CFLAGS) -o usession.o
	gcc -c user/security/userenv.c   $(KINCLUDE) $(CFLAGS) -o userenv.o

	# user/view
	gcc -c user/view/bg.c     $(KINCLUDE) $(CFLAGS) -o bg.o
	gcc -c user/view/char.c   $(KINCLUDE) $(CFLAGS) -o char.o
	gcc -c user/view/dtext.c  $(KINCLUDE) $(CFLAGS) -o dtext.o
	gcc -c user/view/line.c   $(KINCLUDE) $(CFLAGS) -o line.o
	gcc -c user/view/pixel.c  $(KINCLUDE) $(CFLAGS) -o pixel.o
	gcc -c user/view/rect.c   $(KINCLUDE) $(CFLAGS) -o rect.o
    # ...


link-kernel:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	$(LD) $(LDFLAGS) -T link.ld -o KERNEL.BIN $(OBJECTS)    

clean:
	rm -rf *.o   
