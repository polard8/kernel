
# virt/
# Compile all the files and create ar_zcall.o

# Makefile for the kernel syscall support
# and the toplevel functions.
# These are the wrappers that call the workers.

INCLUDE = ../../include

# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I $(INCLUDE)   
STARTUP_INCLUDE := -I x86_64/startup/  

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


# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I $(INCLUDE)

# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -M --print-map:   Print a link map to the standard output.
# LDFLAGS := -m elf_x86_64 -static
LDFLAGS := -m elf_x86_64 -s -x -static  

OBJS = debug.o \
info.o \
panic.o \
reboot.o \
request.o \
system.o \
hv.o \
cali.o \
zero.o \
sys.o \
sci.o \
kmain.o    


all:

# Overall routines.
	$(CC) -c cali/debug.c    $(KERNEL_INCLUDE) $(CFLAGS) -o debug.o
	$(CC) -c cali/info.c     $(KERNEL_INCLUDE) $(CFLAGS) -o info.o
	$(CC) -c cali/panic.c    $(KERNEL_INCLUDE) $(CFLAGS) -o panic.o  
	$(CC) -c cali/reboot.c   $(KERNEL_INCLUDE) $(CFLAGS) -o reboot.o
	$(CC) -c cali/request.c  $(KERNEL_INCLUDE) $(CFLAGS) -o request.o
	$(CC) -c cali/system.c   $(KERNEL_INCLUDE) $(CFLAGS) -o system.o
#	$(CC) -c cali/mod.c      $(KERNEL_INCLUDE) $(CFLAGS) -o mod.o    
	$(CC) -c cali/zero.c     $(KERNEL_INCLUDE)  $(CFLAGS)  -o zero.o
	$(CC) -c cali/cali.c     $(KERNEL_INCLUDE) $(CFLAGS) -o cali.o

# Kernel API.
	$(CC) -c kapi/sys.c   $(KERNEL_INCLUDE)  $(CFLAGS)  -o sys.o


# System Call Interface. (SCI_XXX).
	$(CC) -c sci/sci.c  \
$(KERNEL_INCLUDE)  $(CFLAGS)  -o sci.o    

	$(CC) -c hv.c  $(KERNEL_INCLUDE) $(CFLAGS) -o hv.o

# ----------------------------------------------
# kmain
	$(CC) -c kmain.c   $(KERNEL_INCLUDE) $(CFLAGS) -o kmain.o

# ----------------------------------------------
# link
	$(LD) -r -o ar_zcall.o $(OBJS)
	cp ar_zcall.o ../../

# ----------------------------------------------
# startup
	$(NASM) x86_64/startup/head_64.asm \
	$(KERNEL_INCLUDE) \
	$(STARTUP_INCLUDE) \
	-f elf64 -o head_64.o    

	cp head_64.o ../../

# ----------------------------------------------
	rm *.o
	
clean:
	rm *.o     
	
	
