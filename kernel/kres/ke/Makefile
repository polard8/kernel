
# ke/
# Compile all the files and create ar_ke.o

# Makefile for the kernel executive support.
# It handles the thread stuff, just like,
# dispaching, scheduling, tasswitching.
# It handles the process stuff.
# It also handles the system initialization,

INCLUDE = ../../include

AS	= as
LD	= ld
CC	= gcc
AR	= ar
MAKE	= make
NASM	= nasm
OBJCOPY	= objcopy
OBJDUMP	= objdump
#LEX	= flex
#YACC	= bison
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

# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I $(INCLUDE)

# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -M --print-map:   Print a link map to the standard output.
# LDFLAGS := -m elf_x86_64 -static
LDFLAGS := -m elf_x86_64 -s -x -static  

# Everything is a file.
OBJS = process.o plib.o thread.o tlib.o \
msg.o \
create.o clone.o \
detect.o \
ke.o \
hal.o \
apic.o apictim.o ioapic.o \
pit.o ports64.o rtc.o \
x64.o x64info.o x64init.o x64mi.o x64nmi.o x64smp.o \
queue.o \
ts.o dispatch.o spawn.o x64cont.o \
sched.o schedi.o schedq.o    


all:

# ---------------------
# intake/
# process, thread, dispatcher and scheduler.

	$(CC) -c intake/msg.c      $(KERNEL_INCLUDE) $(CFLAGS) -o msg.o
	$(CC) -c intake/process.c  $(KERNEL_INCLUDE) $(CFLAGS) -o process.o
	$(CC) -c intake/plib.c     $(KERNEL_INCLUDE) $(CFLAGS) -o plib.o
	$(CC) -c intake/thread.c   $(KERNEL_INCLUDE) $(CFLAGS) -o thread.o
	$(CC) -c intake/tlib.c     $(KERNEL_INCLUDE) $(CFLAGS) -o tlib.o
	$(CC) -c intake/create.c   $(KERNEL_INCLUDE) $(CFLAGS) -o create.o
	$(CC) -c intake/clone.c    $(KERNEL_INCLUDE) $(CFLAGS) -o clone.o

	$(CC) -c intake/disp/ts.c              $(KERNEL_INCLUDE)  $(CFLAGS) -o ts.o  
	$(CC) -c intake/disp/dispatch.c        $(KERNEL_INCLUDE)  $(CFLAGS) -o dispatch.o  
	$(CC) -c intake/disp/spawn.c           $(KERNEL_INCLUDE)  $(CFLAGS) -o spawn.o  
	$(CC) -c intake/disp/x86_64/x64cont.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o x64cont.o  

	$(CC) -c intake/sched/sched.c   $(KERNEL_INCLUDE)  $(CFLAGS) -o sched.o  
	$(CC) -c intake/sched/schedi.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o schedi.o  
	$(CC) -c intake/sched/schedq.c  $(KERNEL_INCLUDE)  $(CFLAGS) -o schedq.o  

# ---------------------
# arch/x86_64/

	$(CC) -c arch/x86_64/detect.c  $(KERNEL_INCLUDE) $(CFLAGS) -o detect.o

# SMP support
	$(CC) -c arch/x86_64/smp/apic.c     $(KERNEL_INCLUDE) $(CFLAGS) -o apic.o
	$(CC) -c arch/x86_64/smp/apictim.c  $(KERNEL_INCLUDE) $(CFLAGS) -o apictim.o
	$(CC) -c arch/x86_64/smp/ioapic.c   $(KERNEL_INCLUDE) $(CFLAGS) -o ioapic.o
	$(CC) -c arch/x86_64/smp/x64smp.c   $(KERNEL_INCLUDE) $(CFLAGS) -o x64smp.o

# Legacy low level stuff
	$(CC) -c arch/x86_64/ports64.c  $(KERNEL_INCLUDE) $(CFLAGS) -o ports64.o
	#$(CC) -c arch/x86_64/pic.c     $(KERNEL_INCLUDE) $(CFLAGS) -o pic.o
	$(CC) -c arch/x86_64/pit.c      $(KERNEL_INCLUDE) $(CFLAGS) -o pit.o
	$(CC) -c arch/x86_64/rtc.c      $(KERNEL_INCLUDE) $(CFLAGS) -o rtc.o

# Overview
	$(CC) -c arch/x86_64/x64.c      $(KERNEL_INCLUDE) $(CFLAGS) -o x64.o
	$(CC) -c arch/x86_64/x64info.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64info.o
	$(CC) -c arch/x86_64/x64init.c  $(KERNEL_INCLUDE) $(CFLAGS) -o x64init.o
	$(CC) -c arch/x86_64/x64mi.c    $(KERNEL_INCLUDE) $(CFLAGS) -o x64mi.o
	$(CC) -c arch/x86_64/x64nmi.c   $(KERNEL_INCLUDE) $(CFLAGS) -o x64nmi.o

#--------

	$(CC) -c queue.c  $(KERNEL_INCLUDE) $(CFLAGS) -o queue.o
	$(CC) -c ke.c     $(KERNEL_INCLUDE) $(CFLAGS) -o ke.o
	$(CC) -c hal.c    $(KERNEL_INCLUDE) $(CFLAGS) -o hal.o

# link
	$(LD) -r -o ar_ke.o $(OBJS)
	cp ar_ke.o ../../
	rm *.o
	
clean:
	rm *.o

