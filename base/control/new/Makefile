
# todo:
# The first goal of this makefile is 
# mount the assembly files 
# in the folder kernel/1pump/arch/x86_64/pumpcore/
# Evething starts in the file head_64.asm


# Make variables (CC, etc...)
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


#
# Config
#

# verbose
# Quiet compilation or not.
ifndef CONFIG_USE_VERBOSE
	CONFIG_USE_VERBOSE = 0
endif

ifeq ($(CONFIG_USE_VERBOSE),1)
	Q =
else
	Q = @
endif




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
USER_INCLUDE   := -I include/uapi/

# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I include/ $(USER_INCLUDE)  


# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -M --print-map:   Print a link map to the standard output.
# LDFLAGS := -m elf_x86_64 -static
LDFLAGS := -m elf_x86_64 -s -x -static  


# ========================
# Config

#test
#CONFIG_MAIN=y
# ...

# ========================
# Objects
# Classes: Head | Body | Hooks

# Head
objects-y := head_64.o init.o archive_klib.o    
# Body
objects-y += archive_dev.o  
objects-y += archive_fs.o  
objects-y += archive_ke.o  
objects-y += archive_mm.o  
objects-y += archive_net.o  
objects-y += archive_user.o    
# Hooks
objects-y += debug.o  
objects-y += info.o  
objects-y += globals.o  
objects-y += panic.o  
objects-y += reboot.o  
objects-y += request.o  
objects-y += runtime.o  
objects-y += system.o  
objects-y += sys.o    
objects-y += sci.o    

# test
#objects-$(CONFIG_MAIN1) += archive_something.o   
#objects-$(CONFIG_MAIN2) += archive_something.o   
#objects-$(CONFIG_MAIN3) += archive_something.o   
#objects-$(CONFIG_MAIN4) += archive_something.o   


PHONY := all
all: kernel-header kernel-content kernel-footer \
link-kernel \
clean    


# The entrance \o/
# The x86 head of the monster.
kernel-header:
	@echo "Compiling: Compiling kernel header..."

# Head
# head_64.o
# personas: warden, student, visitor.
# unit 0, unit 1, unit 3, unit 4, visitor
	$(NASM) arch/x86_64/entrance/head_64.asm \
	$(KERNEL_INCLUDE) \
	-I arch/x86_64/entrance/ \
	-f elf64 -o head_64.o

# Init
# init.o
	$(CC) -c init.c $(KERNEL_INCLUDE) $(CFLAGS) -o init.o

	$(CC) -c debug.c    $(KERNEL_INCLUDE) $(CFLAGS) -o debug.o
	$(CC) -c info.c     $(KERNEL_INCLUDE) $(CFLAGS) -o info.o
	$(CC) -c globals.c  $(KERNEL_INCLUDE) $(CFLAGS) -o globals.o
	$(CC) -c panic.c    $(KERNEL_INCLUDE) $(CFLAGS) -o panic.o  
	$(CC) -c reboot.c   $(KERNEL_INCLUDE) $(CFLAGS) -o reboot.o
	$(CC) -c request.c  $(KERNEL_INCLUDE) $(CFLAGS) -o request.o
	$(CC) -c runtime.c  $(KERNEL_INCLUDE) $(CFLAGS) -o runtime.o
	$(CC) -c system.c   $(KERNEL_INCLUDE) $(CFLAGS) -o system.o

# sys_xxx()
	$(CC) -c sys/sys.c $(KERNEL_INCLUDE) $(CFLAGS) -o sys.o

# Systemcall interface.
# sci.o
# unit 2 (xapx)
	$(CC) -c arch/x86_64/entrance/sci.c \
	$(KERNEL_INCLUDE) \
	$(CFLAGS) \
	-o sci.o    

# ring0 libc.
# klib/
	$(MAKE) -C klib/

kernel-content:
	@echo "Compiling: Compiling kernel content ..."
	$(MAKE) -C dev/
	$(MAKE) -C fs/
	$(MAKE) -C ke/
	$(MAKE) -C mm/
	$(MAKE) -C net/
kernel-footer:
	@echo "Compiling: Compiling kernel footer ..."
	$(MAKE) -C user/
	# ...
link-kernel:
	@echo "Linking: Linking the kernel image ..."
	$(LD) $(LDFLAGS) -T arch/x86_64/link.ld -o KERNEL.BIN $(objects-y)    
clean:
	rm -rf *.o   
	@echo "~clean"

