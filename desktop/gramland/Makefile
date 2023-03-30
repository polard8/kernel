
# GRAMLAND.BIN
# GWS - Gramland Window Server.
# 2020 - Created by Fred Nora.


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
CFLAGS = -Wall
#CFLAGS += -O3
CFLAGS += -Wundef
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wno-uninitialized
CFLAGS += -Wno-format-security
CFLAGS += -Wno-trigraphs
CFLAGS += -Werror=strict-prototypes
CFLAGS += -Werror=implicit-function-declaration
CFLAGS += -Werror=return-type
CFLAGS += -std=gnu89
CFLAGS += -m64
CFLAGS += -s
CFLAGS += -static
CFLAGS += -fcommon
CFLAGS += -fgnu89-inline
CFLAGS += -finline-functions
CFLAGS += -fshort-wchar
CFLAGS += -ffreestanding
CFLAGS += -fleading-underscore
CFLAGS += -fstrict-overflow
CFLAGS += -nostdlib
CFLAGS += -nodefaultlibs
CFLAGS += -nostdinc
CFLAGS += -fno-builtin
CFLAGS += -fno-stack-protector
CFLAGS += -fno-strict-aliasing
CFLAGS += -fno-PIE
CFLAGS += -fno-pie
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -fno-optimize-sibling-calls    

#todo
#path longo. vamos mudar  as libs de lugar para gramado/libs.
LIBC        = ../libs/rtl/include/
LIBCOBJ     = ../libs/rtl/obj
LIBDISP     = ../libs/libdisp/include/
LIBDISPOBJ  = ../libs/libdisp/obj

CINCLUDES  = -I $(LIBC)  
CINCLUDES += -I $(LIBDISP)
CINCLUDES += -I .    

# Link support.
linkTarget = GRAMLAND.BIN
linkFlags  = -m elf_x86_64 -T ../link.ld

# Objects
myObjects = crt0.o main.o callback.o rtl.o \
ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
termios.o ioctl.o fcntl.o    

myObjects += globals.o 
myObjects += libdisp.o

myObjects += archive_basics1.o
myObjects += archive_basics2.o
myObjects += archive_fx.o    
myObjects += archive_extra.o    
myObjects += menu.o   
myObjects += wm.o   

.PHONY: all all-c gws-link finalize clean

all: main.o all-c gws-link finalize clean
	@echo "Ok?"
main.o:
	$(CC) -c  main.c      $(CFLAGS) $(CINCLUDES) -o main.o
	$(CC) -c  globals.c   $(CFLAGS) $(CINCLUDES) -o globals.o
	$(CC) -c  callback.c  $(CFLAGS) $(CINCLUDES) -o callback.o
all-c:

#basics1
	$(CC)  -c  rtl/char.c   $(CFLAGS) $(CINCLUDES) -o char.o
	$(CC)  -c  rtl/dtext.c  $(CFLAGS) $(CINCLUDES) -o dtext.o
	$(LD) -r -o archive_basics1.o char.o dtext.o 

	$(CC)  -c  rtl/line.c  $(CFLAGS) $(CINCLUDES) -o line.o
	$(CC)  -c  rtl/rect.c  $(CFLAGS) $(CINCLUDES) -o rect.o
	$(CC)  -c  ui/window.c   $(CFLAGS) $(CINCLUDES) -o window.o
	$(CC)  -c  rtl/bitblt.c  $(CFLAGS) $(CINCLUDES) -o bitblt.o
	$(CC)  -c  ui/painter.c  $(CFLAGS) $(CINCLUDES) -o painter.o
	$(CC)  -c  gws.c       $(CFLAGS) $(CINCLUDES) -o gws.o
	$(CC)  -c comp/comp.c  $(CFLAGS) $(CINCLUDES) -o comp.o
	$(CC)  -c  bmp.c       $(CFLAGS) $(CINCLUDES) -o bmp.o
	$(CC)  -c  os/connect.c   $(CFLAGS) $(CINCLUDES) -o connect.o
	$(CC)  -c  button.c    $(CFLAGS) $(CINCLUDES) -o button.o
	$(LD) -r -o archive_basics2.o \
line.o rect.o window.o bitblt.o painter.o gws.o comp.o bmp.o connect.o button.o

#fx
	$(CC)  -c  rtl/grprim.c    $(CFLAGS) $(CINCLUDES) -o grprim.o
	$(CC)  -c  sprite.c    $(CFLAGS) $(CINCLUDES) -o sprite.o
	$(CC)  -c  demos.c     $(CFLAGS) $(CINCLUDES) -o demos.o
	$(LD) -r -o archive_fx.o  grprim.o sprite.o demos.o 

#extra
	$(CC)  -c grinput.c  $(CFLAGS) $(CINCLUDES) -o grinput.o
	$(CC)  -c ui/font.c    $(CFLAGS) $(CINCLUDES) -o font.o
	$(LD) -r -o archive_extra.o grinput.o font.o 

	$(CC)  -c ui/menu.c  $(CFLAGS) $(CINCLUDES) -o menu.o
	$(CC)  -c ui/wm.c    $(CFLAGS) $(CINCLUDES) -o wm.o

#
# == imported objects =============================
#

# rtl/
	cp $(LIBCOBJ)/crt0.o .
	cp $(LIBCOBJ)/rtl.o .

	cp $(LIBCOBJ)/ctype.o .
	cp $(LIBCOBJ)/stdio.o .
	cp $(LIBCOBJ)/stdlib.o .
	cp $(LIBCOBJ)/string.o .
	cp $(LIBCOBJ)/conio.o .
	cp $(LIBCOBJ)/unistd.o .
	cp $(LIBCOBJ)/socket.o .
	cp $(LIBCOBJ)/signal.o .
	cp $(LIBCOBJ)/termios.o .
	cp $(LIBCOBJ)/ioctl.o .
	cp $(LIBCOBJ)/fcntl.o .

	cp $(LIBDISPOBJ)/libdisp.o .

gws-link:
	$(LD) $(linkFlags) -o $(linkTarget) $(myObjects)
finalize:
	cp $(linkTarget) bin/
clean:
	-rm *.o
	-rm $(linkTarget)
	
