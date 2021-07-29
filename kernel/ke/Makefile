
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


# test: gramado 64bit
# See: https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html
CFLAGS := \
	-Wall \
	-Wundef \
	-Wmissing-prototypes \
	-Wno-uninitialized \
	-Wno-format-security \
	-Wno-trigraphs \
	-Werror=strict-prototypes \
	-Werror=implicit-function-declaration \
	-Werror=implicit-int \
	-Werror=return-type \
	-std=gnu89 \
	-m64 \
	-s \
	-static \
	-fcommon \
	-fgnu89-inline \
	-finline-functions \
	-fshort-wchar \
	-ffreestanding \
	-fleading-underscore \
	-fstrict-overflow \
	-nostdlib \
	-nodefaultlibs \
	-nostdinc \
	-fno-builtin \
	-fno-stack-protector \
	-fno-strict-aliasing \
	-fno-PIE \
	-fno-pie \
	-fno-omit-frame-pointer \
	-fno-optimize-sibling-calls    


# Exported files. Kernel api;
# Used by the kernel modules and user space applications.
USER_INCLUDE   := -I ../include/uapi/


# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I ../include/ $(USER_INCLUDE)  


# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -M --print-map:   Print a link map to the standard output.
# LDFLAGS := -m elf_x86_64 -static
LDFLAGS := -m elf_x86_64 -s -x -static  



# Everything is a file.
OBJS = process.o plib.o thread.o tlib.o \
create.o clone.o \
panic.o \
reboot.o \
request.o \
detect.o \
hal.o \
pit.o \
ports64.o \
rtc.o \
x64init.o x64.o x64info.o x64fault.o \
queue.o \
mk.o \
ts.o dispatch.o spawn.o x64cont.o \
sched.o schedi.o \
info.o \
sysinit.o \
runtime.o \
system.o \
debug.o \
sys.o    



all:

	# arch
	$(CC) -c arch/x86_64/x64init.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64init.o

	# hal
	$(CC) -c hal/hal.c             $(KERNEL_INCLUDE) $(CFLAGS) -o hal.o
	$(CC) -c hal/detect.c          $(KERNEL_INCLUDE) $(CFLAGS) -o detect.o
	$(CC) -c hal/x86_64/pit.c      $(KERNEL_INCLUDE) $(CFLAGS) -o pit.o
	$(CC) -c hal/x86_64/ports64.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ports64.o
	$(CC) -c hal/x86_64/rtc.c      $(KERNEL_INCLUDE) $(CFLAGS) -o rtc.o
	$(CC) -c hal/x86_64/x64.c      $(KERNEL_INCLUDE) $(CFLAGS) -o x64.o
	$(CC) -c hal/x86_64/x64info.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64info.o

	$(CC) -c ps/process.c  $(KERNEL_INCLUDE) $(CFLAGS) -o process.o
	$(CC) -c ps/plib.c     $(KERNEL_INCLUDE) $(CFLAGS) -o plib.o

	$(CC) -c ps/thread.c  $(KERNEL_INCLUDE) $(CFLAGS) -o thread.o
	$(CC) -c ps/tlib.c    $(KERNEL_INCLUDE) $(CFLAGS) -o tlib.o

	$(CC) -c ps/create.c    $(KERNEL_INCLUDE) $(CFLAGS) -o create.o
	$(CC) -c ps/clone.c     $(KERNEL_INCLUDE) $(CFLAGS) -o clone.o
	$(CC) -c ps/x86_64/x64fault.c      $(KERNEL_INCLUDE) $(CFLAGS) -o x64fault.o
	$(CC) -c ps/queue.c    $(KERNEL_INCLUDE) $(CFLAGS) -o queue.o
	$(CC) -c ps/mk.c       $(KERNEL_INCLUDE) $(CFLAGS) -o mk.o

	$(CC) -c ps/disp/ts.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o ts.o  
	$(CC) -c ps/disp/dispatch.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o dispatch.o  
	$(CC) -c ps/disp/spawn.c     $(KERNEL_INCLUDE)  $(CFLAGS) -o spawn.o  
	$(CC) -c ps/disp/x86_64/x64cont.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o x64cont.o  

	$(CC) -c ps/sched/sched.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o sched.o  
	$(CC) -c ps/sched/schedi.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o schedi.o  


	$(CC) -c panic.c    $(KERNEL_INCLUDE) $(CFLAGS) -o panic.o  
	$(CC) -c reboot.c   $(KERNEL_INCLUDE) $(CFLAGS) -o reboot.o
	$(CC) -c request.c  $(KERNEL_INCLUDE) $(CFLAGS) -o request.o
	$(CC) -c info.c     $(KERNEL_INCLUDE) $(CFLAGS) -o info.o
	$(CC) -c sysinit.c  $(KERNEL_INCLUDE) $(CFLAGS) -o sysinit.o
	$(CC) -c runtime.c  $(KERNEL_INCLUDE) $(CFLAGS) -o runtime.o
	$(CC) -c system.c   $(KERNEL_INCLUDE) $(CFLAGS) -o system.o
	$(CC) -c debug.c    $(KERNEL_INCLUDE) $(CFLAGS) -o debug.o
	$(CC) -c sys.c      $(KERNEL_INCLUDE) $(CFLAGS) -o sys.o


#link
	$(LD) -r -o archive_ke.o $(OBJS)


# todo: vamos ligar tudo e enviar somente a biblioteca.
	#cp *.o ../
	cp archive_ke.o ../
	rm *.o













