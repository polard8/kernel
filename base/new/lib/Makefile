
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
OBJS = ctype.o string.o stdlib.o kstdio.o signal.o unistd.o    


all:

	$(CC) -c ctype.c   $(KERNEL_INCLUDE) $(CFLAGS) -o ctype.o
	$(CC) -c string.c  $(KERNEL_INCLUDE) $(CFLAGS) -o string.o
	$(CC) -c stdlib.c  $(KERNEL_INCLUDE) $(CFLAGS) -o stdlib.o
	$(CC) -c kstdio.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kstdio.o
	$(CC) -c signal.c  $(KERNEL_INCLUDE) $(CFLAGS) -o signal.o
	$(CC) -c unistd.c  $(KERNEL_INCLUDE) $(CFLAGS) -o unistd.o

#link
	$(LD) -r -o archive_lib.o $(OBJS)


# todo: vamos ligar tudo e enviar somente a biblioteca.
	#cp *.o ../
	cp archive_lib.o ../
	rm *.o
	
	













