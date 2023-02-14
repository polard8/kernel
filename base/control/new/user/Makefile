
# user/
# Compile all the files and create ar_user.o

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

OBJS = desktop.o room.o usession.o \
logoff.o logon.o \
userenv.o    

all:

#security
	$(CC) -c desktop.c   $(KERNEL_INCLUDE) $(CFLAGS) -o desktop.o
	$(CC) -c room.c      $(KERNEL_INCLUDE) $(CFLAGS) -o room.o
	$(CC) -c usession.c  $(KERNEL_INCLUDE) $(CFLAGS) -o usession.o

	$(CC) -c logoff.c    $(KERNEL_INCLUDE) $(CFLAGS) -o logoff.o
	$(CC) -c logon.c     $(KERNEL_INCLUDE) $(CFLAGS) -o logon.o

	$(CC) -c userenv.c   $(KERNEL_INCLUDE) $(CFLAGS) -o userenv.o

# link
	$(LD) -r -o ar_user.o $(OBJS)
	cp ar_user.o ../
	rm *.o
	
clean:
	rm *.o     
	
	
