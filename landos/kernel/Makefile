
# todo:
# The first goal of this makefile is 
# mount the assembly files 
# in the folder kernel/1pump/arch/x86_64/pumpcore/
# Evething starts in the file head_64.asm

# See:
# https://gcc.gnu.org/onlinedocs/gcc/x86-Options.html


#original: gramado 32bit
#CFLAGS := -m64 \
#	-std=gnu89 \
#	-nodefaultlibs \
#	-nostdinc \
#	-nostdlib \
#	-static \
#	-fgnu89-inline \
#	-ffreestanding \
#	-fno-builtin \
#	-fno-pie \
#	-fleading-underscore \
#	-fno-stack-protector \
#	-s \
#	-Werror=strict-prototypes    



# test: gramado 64bit
# for user: Just type 'make'
#USER_CFLAGS
CFLAGS := -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs \
	-fno-strict-aliasing -fshort-wchar -fno-PIE \
	-Werror=implicit-function-declaration -Werror=implicit-int \
	-Werror=return-type -Wno-format-security \
	-std=gnu89 \
	-Wmissing-prototypes \
	 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-aliasing  \
	-m64 \
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



# Exported files. Kernel api;
# Used by the kernel modules and user space applications.
USER_INCLUDE   := -I include/uapi/

# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I include/ $(USER_INCLUDE)  



LDFLAGS := -m elf_x86_64


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
fs.o network.o socket.o pipe.o search.o \
disk_r.o disk_w.o \
sys.o \
io.o ws.o \
pixel.o bg.o char.o dtext.o line.o rect.o \
kgws.o kgwm.o vt.o \
desktop.o room.o usession.o logon.o logoff.o userenv.o \
ts.o dispatch.o spawn.o x64cont.o x64fault.o \
sched.o schedi.o \
process.o thread.o threadi.o create.o queue.o mk.o \
memory.o mminfo.o mmpool.o pages.o \
panic.o reboot.o request.o \
sci.o     


PHONY := all
all: kernel-head all-c link-kernel clean

kernel-head:

# The x86 head of the monster.

# provisorio
	nasm 1pump/arch/x86_64/pumpcore/head_64.asm \
	$(KERNEL_INCLUDE) \
	-I 1pump/arch/x86_64/pumpcore/ \
	-f elf64 -o head_64.o


all-c:

#
# == main ======== 
#

	#$(CC) -c main.c  $(KERNEL_INCLUDE) $(CFLAGS) -o main.o
	gcc -c main.c  $(KERNEL_INCLUDE) $(CFLAGS) -o main.o

#
# == 0mem ======== 
#

	gcc -c 0mem/panic.c    $(KERNEL_INCLUDE) $(CFLAGS) -o panic.o
	gcc -c 0mem/reboot.c   $(KERNEL_INCLUDE) $(CFLAGS) -o reboot.o
	gcc -c 0mem/request.c  $(KERNEL_INCLUDE) $(CFLAGS) -o request.o


	# == Gramado Core ====
	# Architecture independent layer.

	gcc -c 0mem/core/info.c     $(KERNEL_INCLUDE) $(CFLAGS) -o info.o
	gcc -c 0mem/core/init.c     $(KERNEL_INCLUDE) $(CFLAGS) -o init.o
	gcc -c 0mem/core/runtime.c  $(KERNEL_INCLUDE) $(CFLAGS) -o runtime.o
	gcc -c 0mem/core/system.c   $(KERNEL_INCLUDE) $(CFLAGS) -o system.o

	# debug
	gcc -c 0mem/core/debug/debug.c  $(KERNEL_INCLUDE) $(CFLAGS) -o debug.o

	# ps
	gcc -c 0mem/core/ps/process.c  $(KERNEL_INCLUDE) $(CFLAGS) -o process.o
	gcc -c 0mem/core/ps/thread.c   $(KERNEL_INCLUDE) $(CFLAGS) -o thread.o
	gcc -c 0mem/core/ps/threadi.c  $(KERNEL_INCLUDE) $(CFLAGS) -o threadi.o
	gcc -c 0mem/core/ps/create.c   $(KERNEL_INCLUDE) $(CFLAGS) -o create.o
	gcc -c 0mem/core/ps/x86_64/x64fault.c      $(KERNEL_INCLUDE) $(CFLAGS) -o x64fault.o
	gcc -c 0mem/core/ps/queue.c   $(KERNEL_INCLUDE) $(CFLAGS) -o queue.o
	gcc -c 0mem/core/ps/mk.c      $(KERNEL_INCLUDE) $(CFLAGS) -o mk.o

	# ps/disp
	gcc -c 0mem/core/ps/disp/ts.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o ts.o  
	gcc -c 0mem/core/ps/disp/dispatch.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o dispatch.o  
	gcc -c 0mem/core/ps/disp/spawn.c     $(KERNEL_INCLUDE)  $(CFLAGS) -o spawn.o  

	gcc -c 0mem/core/ps/disp/x86_64/x64cont.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o x64cont.o  

	gcc -c 0mem/core/ps/sched/sched.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o sched.o  
	gcc -c 0mem/core/ps/sched/schedi.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o schedi.o  


	# 0mem/mm
	gcc -c 0mem/mm/memory.c  $(KERNEL_INCLUDE) $(CFLAGS) -o memory.o
	gcc -c 0mem/mm/mminfo.c  $(KERNEL_INCLUDE) $(CFLAGS) -o mminfo.o
	gcc -c 0mem/mm/mmpool.c  $(KERNEL_INCLUDE) $(CFLAGS) -o mmpool.o
	gcc -c 0mem/mm/pages.c   $(KERNEL_INCLUDE) $(CFLAGS) -o pages.o


	gcc -c 0mem/sci/net/network/network.c  $(KERNEL_INCLUDE) $(CFLAGS) -o network.o
	gcc -c 0mem/sci/net/socket/socket.c    $(KERNEL_INCLUDE) $(CFLAGS) -o socket.o

	# 0mem/rtl
	gcc -c 0mem/rtl/ctype.c   $(KERNEL_INCLUDE) $(CFLAGS) -o ctype.o
	gcc -c 0mem/rtl/string.c  $(KERNEL_INCLUDE) $(CFLAGS) -o string.o
	gcc -c 0mem/rtl/stdlib.c  $(KERNEL_INCLUDE) $(CFLAGS) -o stdlib.o
	gcc -c 0mem/rtl/kstdio.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kstdio.o
	gcc -c 0mem/rtl/signal.c  $(KERNEL_INCLUDE) $(CFLAGS) -o signal.o
	gcc -c 0mem/rtl/unistd.c  $(KERNEL_INCLUDE) $(CFLAGS) -o unistd.o

	# 0mem/sci/fs
	gcc -c 0mem/sci/fs/fs.c      $(KERNEL_INCLUDE) $(CFLAGS) -o fs.o
	gcc -c 0mem/sci/fs/pipe.c    $(KERNEL_INCLUDE) $(CFLAGS) -o pipe.o
	gcc -c 0mem/sci/fs/search.c  $(KERNEL_INCLUDE) $(CFLAGS) -o search.o

	gcc -c 0mem/sci/fs/sdi/disk_r.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_r.o
	gcc -c 0mem/sci/fs/sdi/disk_w.c  $(KERNEL_INCLUDE) $(CFLAGS) -o disk_w.o

	gcc -c 0mem/sci/sys/sys.c  $(KERNEL_INCLUDE) $(CFLAGS) -o sys.o


#
# == 1pump ======== 
#

	gcc -c 1pump/arch/detect.c  $(KERNEL_INCLUDE) $(CFLAGS) -o detect.o
	gcc -c 1pump/arch/hal.c     $(KERNEL_INCLUDE) $(CFLAGS) -o hal.o


	# 1pump/arch/x86_64
	gcc -c 1pump/arch/x86_64/pit.c      $(KERNEL_INCLUDE) $(CFLAGS) -o pit.o
	gcc -c 1pump/arch/x86_64/ports64.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ports64.o
	gcc -c 1pump/arch/x86_64/rtc.c      $(KERNEL_INCLUDE) $(CFLAGS) -o rtc.o
	gcc -c 1pump/arch/x86_64/x64init.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64init.o
	gcc -c 1pump/arch/x86_64/x64.c      $(KERNEL_INCLUDE) $(CFLAGS) -o x64.o
	gcc -c 1pump/arch/x86_64/x64info.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64info.o


#
# == 2io ======== 
#

	gcc -c 2io/io.c  $(KERNEL_INCLUDE) $(CFLAGS) -o io.o
	gcc -c 2io/ws.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ws.o

	# 2io/bus/pcibus/
	gcc -c 2io/bus/pcibus/pci.c     $(KERNEL_INCLUDE) $(CFLAGS) -o pci.o
	gcc -c 2io/bus/pcibus/pciinfo.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciinfo.o
	gcc -c 2io/bus/pcibus/pciscan.c $(KERNEL_INCLUDE) $(CFLAGS) -o pciscan.o



	# 2io/dev/
	gcc -c 2io/dev/devmgr.c  $(KERNEL_INCLUDE) $(CFLAGS) -o devmgr.o 
	gcc -c 2io/dev/serial.c  $(KERNEL_INCLUDE) $(CFLAGS) -o serial.o

	# 2io/dev/blkdev
	gcc -c 2io/dev/blkdev/storage.c  $(KERNEL_INCLUDE) $(CFLAGS) -o storage.o 

	# 2io/dev/blkdev/ide
	gcc -c 2io/dev/blkdev/ide/ata.c      $(KERNEL_INCLUDE) $(CFLAGS) -o ata.o 
	gcc -c 2io/dev/blkdev/ide/atadma.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atadma.o 
	gcc -c 2io/dev/blkdev/ide/atahdd.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atahdd.o 
	gcc -c 2io/dev/blkdev/ide/atainit.c  $(KERNEL_INCLUDE) $(CFLAGS) -o atainit.o 
	gcc -c 2io/dev/blkdev/ide/atairq.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atairq.o 
	gcc -c 2io/dev/blkdev/ide/atapci.c   $(KERNEL_INCLUDE) $(CFLAGS) -o atapci.o 

	# 2io/dev/tty/
	gcc -c 2io/dev/tty/tty.c  $(KERNEL_INCLUDE) $(CFLAGS) -o tty.o

	# 2io/dev/graphics
	gcc -c 2io/dev/graphics/video.c   $(KERNEL_INCLUDE) $(CFLAGS) -o video.o
	gcc -c 2io/dev/graphics/vsync.c   $(KERNEL_INCLUDE) $(CFLAGS) -o vsync.o
	gcc -c 2io/dev/graphics/screen.c  $(KERNEL_INCLUDE) $(CFLAGS) -o screen.o

	# 2io/dev/hid
	gcc -c 2io/dev/hid/i8042.c     $(KERNEL_INCLUDE) $(CFLAGS) -o i8042.o
	gcc -c 2io/dev/hid/ps2kbd.c    $(KERNEL_INCLUDE) $(CFLAGS) -o ps2kbd.o
	gcc -c 2io/dev/hid/ps2mouse.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ps2mouse.o
	gcc -c 2io/dev/hid/keyboard.c  $(KERNEL_INCLUDE) $(CFLAGS) -o keyboard.o
	gcc -c 2io/dev/hid/mouse.c     $(KERNEL_INCLUDE) $(CFLAGS) -o mouse.o


#
# == user ======== 
#

	gcc -c user/kgws.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kgws.o
	gcc -c user/kgwm.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kgwm.o

	gcc -c user/vt.c   $(KERNEL_INCLUDE) $(CFLAGS) -o vt.o

	# ctrl
	gcc -c user/ctrl/console.c  $(KERNEL_INCLUDE) $(CFLAGS) -o console.o
	gcc -c user/ctrl/sci.c      $(KERNEL_INCLUDE) $(CFLAGS) -o sci.o

	# user/model
	gcc -c user/model/font.c  $(KERNEL_INCLUDE) $(CFLAGS) -o font.o


	# user/security
	gcc -c user/security/desktop.c   $(KERNEL_INCLUDE) $(CFLAGS) -o desktop.o
	gcc -c user/security/room.c      $(KERNEL_INCLUDE) $(CFLAGS) -o room.o
	gcc -c user/security/usession.c  $(KERNEL_INCLUDE) $(CFLAGS) -o usession.o
	gcc -c user/security/logoff.c    $(KERNEL_INCLUDE) $(CFLAGS) -o logoff.o
	gcc -c user/security/logon.c     $(KERNEL_INCLUDE) $(CFLAGS) -o logon.o
	gcc -c user/security/userenv.c   $(KERNEL_INCLUDE) $(CFLAGS) -o userenv.o


	# user/view
	gcc -c user/view/bg.c     $(KERNEL_INCLUDE) $(CFLAGS) -o bg.o
	gcc -c user/view/char.c   $(KERNEL_INCLUDE) $(CFLAGS) -o char.o
	gcc -c user/view/dtext.c  $(KERNEL_INCLUDE) $(CFLAGS) -o dtext.o
	gcc -c user/view/line.c   $(KERNEL_INCLUDE) $(CFLAGS) -o line.o
	gcc -c user/view/pixel.c  $(KERNEL_INCLUDE) $(CFLAGS) -o pixel.o
	gcc -c user/view/rect.c   $(KERNEL_INCLUDE) $(CFLAGS) -o rect.o
    # ...


link-kernel:
	@echo "================================="
	@echo "(Step 2) Linking the kernel image ..."

	$(LD) $(LDFLAGS) -T link.ld -o KERNEL.BIN $(OBJECTS)  

clean:
	rm -rf *.o   

