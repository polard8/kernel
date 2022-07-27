
# ring0 application.
# #bugbug:
# We don't want syscalls from ring0.
# #todo:
# Check if crt0 initialization is making some ring0 syscall.

VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
EXTRAVERSION = 
#NAME = GWS

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


# usermode cross compiler flags.
user_ccflags = \
	-Wall \
	-Wundef \
	-Wmissing-prototypes \
	-Wno-uninitialized \
	-Wno-format-security \
	-Wno-trigraphs \
	-Werror=strict-prototypes \
	-Werror=implicit-function-declaration \
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
	

# usermode linker flags.
user_ldflags = -m elf_x86_64 -T x86_64/link_r0.ld

#todo
#path longo. vamos mudar  as libs de lugar para gramado/libs.

LIBC              = ../../../comtier/lib/rtl/include/
LIBCOBJ           = ../../../comtier/lib/rtl/obj
WS_INCLUDES       = include/ 
WS_INCLUDES_LOCAL = .


#
# Objects
#


#head
#myObjects = crt0.o main.o rtl.o \
#ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
#termios.o ioctl.o fcntl.o    

myObjects = crt0.o main.o    


.PHONY: all all-c gws-link finalize clean

all: crt0.o main.o all-c gws-link finalize clean
	@echo "Ok?"
	
crt0.o:
	$(CC)  -c  crt0.c  $(user_ccflags) -I . -o crt0.o

main.o:
	$(CC)  -c  main.c  $(user_ccflags) -I . -o main.o

all-c:

# == imported objects =============================

# rtl/


gws-link:
	$(LD) $(user_ldflags) -o MOD0.BIN $(myObjects)
#	$(LD) -m elf_i386 -T ../link.ld -o GWSSRV.BIN $(myObjects)  
finalize:
	#cp MOD0.BIN ../../bin
clean:
	-rm *.o
	#-rm MOD0.BIN 
	

