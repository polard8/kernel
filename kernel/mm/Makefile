
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



OBJS = memory.o mminfo.o mmpool.o pages.o \
info.o \
init.o \
runtime.o \
system.o \
debug.o \
network.o \
socket.o \
ctype.o string.o stdlib.o kstdio.o signal.o unistd.o \
sys.o    



all:

	$(CC) -c memory.c  $(KERNEL_INCLUDE) $(CFLAGS) -o memory.o
	$(CC) -c mminfo.c  $(KERNEL_INCLUDE) $(CFLAGS) -o mminfo.o
	$(CC) -c mmpool.c  $(KERNEL_INCLUDE) $(CFLAGS) -o mmpool.o
	$(CC) -c pages.c   $(KERNEL_INCLUDE) $(CFLAGS) -o pages.o

	$(CC) -c core/info.c     $(KERNEL_INCLUDE) $(CFLAGS) -o info.o
	$(CC) -c core/init.c     $(KERNEL_INCLUDE) $(CFLAGS) -o init.o
	$(CC) -c core/runtime.c  $(KERNEL_INCLUDE) $(CFLAGS) -o runtime.o
	$(CC) -c core/system.c   $(KERNEL_INCLUDE) $(CFLAGS) -o system.o

	$(CC) -c core/debug/debug.c  $(KERNEL_INCLUDE) $(CFLAGS) -o debug.o

	$(CC) -c sci/net/network/network.c  $(KERNEL_INCLUDE) $(CFLAGS) -o network.o
	$(CC) -c sci/net/socket/socket.c    $(KERNEL_INCLUDE) $(CFLAGS) -o socket.o

	$(CC) -c rtl/ctype.c   $(KERNEL_INCLUDE) $(CFLAGS) -o ctype.o
	$(CC) -c rtl/string.c  $(KERNEL_INCLUDE) $(CFLAGS) -o string.o
	$(CC) -c rtl/stdlib.c  $(KERNEL_INCLUDE) $(CFLAGS) -o stdlib.o
	$(CC) -c rtl/kstdio.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kstdio.o
	$(CC) -c rtl/signal.c  $(KERNEL_INCLUDE) $(CFLAGS) -o signal.o
	$(CC) -c rtl/unistd.c  $(KERNEL_INCLUDE) $(CFLAGS) -o unistd.o

	$(CC) -c sci/sys/sys.c  $(KERNEL_INCLUDE) $(CFLAGS) -o sys.o


#link
	$(LD) -r -o archive_mm.o $(OBJS)


# todo: vamos ligar tudo e enviar somente a biblioteca.
	#cp *.o ../
	cp archive_mm.o ../
	rm *.o
	
	













