
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
objects-y := head_64.o kmain.o init.o zero.o ar_crt.o  
# Body
objects-y += ar_dev.o  
objects-y += ar_fs.o  
objects-y += ar_ke.o  
objects-y += ar_mm.o  
objects-y += ar_net.o  
objects-y += ar_user.o    
# Hooks
objects-y += debug.o  
objects-y += info.o  
objects-y += globals.o  
objects-y += panic.o  
objects-y += reboot.o  
objects-y += request.o  
objects-y += system.o  
objects-y += sys.o    
objects-y += mod.o    
objects-y += sci.o    


PHONY := all
all: k1 k2 k3 \
link-kernel \
clean    

# The boot \o/
# The x86 head of the monster.
k1:
#kernel-header:
# Top layer.

	@echo "Compiling: Compiling kernel header..."

# top
# Head
# head_64.o
	$(NASM) boot/head/x86_64/head_64.asm \
	$(KERNEL_INCLUDE) \
	-I boot/head/x86_64/ \
	-f elf64 -o head_64.o

# top
# Ring0 libc.
# crt/
	$(MAKE) -C crt/

	$(CC) -c globals.c  $(KERNEL_INCLUDE) $(CFLAGS) -o globals.o
	$(CC) -c init.c $(KERNEL_INCLUDE) $(CFLAGS) -o init.o
	$(CC) -c kmain.c $(KERNEL_INCLUDE) $(CFLAGS) -o kmain.o

k2:
#kernel-content:
# Middle layer.
 
	@echo "Compiling: Compiling kernel content ..."

	$(MAKE) -C dev/
	$(MAKE) -C fs/
	$(MAKE) -C ke/
	$(MAKE) -C mm/
	$(MAKE) -C net/

k3:
#kernel-footer:
# Bottom layer.

	@echo "Compiling: Compiling kernel footer ..."
	$(MAKE) -C user/
	# ...

	$(CC) -c zero/info.c     $(KERNEL_INCLUDE) $(CFLAGS) -o info.o
	$(CC) -c zero/debug.c    $(KERNEL_INCLUDE) $(CFLAGS) -o debug.o
	$(CC) -c zero/reboot.c   $(KERNEL_INCLUDE) $(CFLAGS) -o reboot.o
	$(CC) -c zero/panic.c    $(KERNEL_INCLUDE) $(CFLAGS) -o panic.o  
	$(CC) -c zero/request.c  $(KERNEL_INCLUDE) $(CFLAGS) -o request.o
	$(CC) -c zero/sys/system.c   $(KERNEL_INCLUDE) $(CFLAGS) -o system.o
	$(CC) -c zero/sys/sys.c  $(KERNEL_INCLUDE) $(CFLAGS) -o sys.o

# Initializations
	$(CC) -c zero/zero.c  $(KERNEL_INCLUDE) $(CFLAGS) -o zero.o

# Module interface.
# mod.o
	$(CC) -c zero/mod/mod.c \
	$(KERNEL_INCLUDE) \
	$(CFLAGS) \
	-o mod.o    

# Systemcall interface.
# sci.o
	$(CC) -c zero/visitor/sci.c \
	$(KERNEL_INCLUDE) \
	$(CFLAGS) \
	-o sci.o    


link-kernel:
	@echo "Linking: Linking the kernel image ..."
	$(LD) $(LDFLAGS) -T boot/head/x86_64/link.ld -o KERNEL.BIN $(objects-y)    
clean:
	rm -rf *.o   
	@echo "~clean"

