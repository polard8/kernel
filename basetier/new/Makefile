
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
# Objects (This is a test)
# We need classes: head | always | optional

# head
objects-y := head_64.o init.o newos.o archive_lib.o    

objects-y += archive_ke.o archive_mm.o archive_drivers.o archive_fs.o \
archive_net.o archive_user.o    

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
	@echo "Compiling: Compiling kernel header ..."

	# personas: warden, student, visitor.
	# unit 0, unit 1, unit 3, unit 4, visitor
	$(NASM) entrance/warden/unit0/x86_64/head_64.asm \
	$(KERNEL_INCLUDE) \
	-I entrance/warden/unit0/x86_64/ \
	-I entrance/student/unit1/x86_64/ \
	-I entrance/student/unit3/x86_64/ \
	-I entrance/warden/unit4/x86_64/ \
	-I entrance/visitor/x86_64/ \
	-f elf64 -o head_64.o

	# unit 2 (xapx)
	$(CC) -c entrance/visitor/x86_64/sci.c \
	$(KERNEL_INCLUDE) \
	$(CFLAGS) \
	-o sci.o    

# init
	$(CC) -c init.c  $(KERNEL_INCLUDE) $(CFLAGS) -o init.o

# Interface.
	$(CC) -c newos.c  $(KERNEL_INCLUDE) $(CFLAGS) -o newos.o

# lib
	$(Q) $(MAKE) -C lib/

kernel-content:
	@echo "Compiling: Compiling kernel content ..."
	$(Q) $(MAKE) -C ke/
	$(Q) $(MAKE) -C mm/
	$(Q) $(MAKE) -C drivers/
	$(Q) $(MAKE) -C fs/

kernel-footer:
	@echo "Compiling: Compiling kernel footer ..."
	$(Q) $(MAKE) -C net/
	$(Q) $(MAKE) -C user/
	# ...

link-kernel:
	@echo "Linking: Linking the kernel image ..."

	$(LD) $(LDFLAGS) -T arch/x86_64/link.ld -o KERNEL.BIN $(objects-y)    

clean:
	rm -rf *.o   


