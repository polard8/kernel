
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



OBJS = kgws.o \
kgwm.o \
vt.o \
console.o \
font.o \
desktop.o room.o usession.o \
logoff.o logon.o \
userenv.o \
bg.o \
char.o \
dtext.o \
line.o \
pixel.o \
rect.o    



all:


	$(CC) -c kgws.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kgws.o
	$(CC) -c kgwm.c  $(KERNEL_INCLUDE) $(CFLAGS) -o kgwm.o


	$(CC) -c vt.c   $(KERNEL_INCLUDE) $(CFLAGS) -o vt.o
	$(CC) -c ctrl/console.c  $(KERNEL_INCLUDE) $(CFLAGS) -o console.o 
	$(CC) -c model/font.c  $(KERNEL_INCLUDE) $(CFLAGS) -o font.o


	# security
	$(CC) -c security/desktop.c   $(KERNEL_INCLUDE) $(CFLAGS) -o desktop.o
	$(CC) -c security/room.c      $(KERNEL_INCLUDE) $(CFLAGS) -o room.o
	$(CC) -c security/usession.c  $(KERNEL_INCLUDE) $(CFLAGS) -o usession.o
	$(CC) -c security/logoff.c    $(KERNEL_INCLUDE) $(CFLAGS) -o logoff.o
	$(CC) -c security/logon.c     $(KERNEL_INCLUDE) $(CFLAGS) -o logon.o
	$(CC) -c security/userenv.c   $(KERNEL_INCLUDE) $(CFLAGS) -o userenv.o


	# view
	$(CC) -c view/bg.c     $(KERNEL_INCLUDE) $(CFLAGS) -o bg.o
	$(CC) -c view/char.c   $(KERNEL_INCLUDE) $(CFLAGS) -o char.o
	$(CC) -c view/dtext.c  $(KERNEL_INCLUDE) $(CFLAGS) -o dtext.o
	$(CC) -c view/line.c   $(KERNEL_INCLUDE) $(CFLAGS) -o line.o
	$(CC) -c view/pixel.c  $(KERNEL_INCLUDE) $(CFLAGS) -o pixel.o
	$(CC) -c view/rect.c   $(KERNEL_INCLUDE) $(CFLAGS) -o rect.o
    # ...


#link
	$(LD) -r -o archive_user.o $(OBJS)


# todo: vamos ligar tudo e enviar somente a biblioteca.
	#cp *.o ../
	cp archive_user.o ../
	rm *.o













