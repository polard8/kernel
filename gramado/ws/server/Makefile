
# gws - Gramado Window Server.
# 2020 - Created by Fred Nora.




# todo:
# Os aplicativos em /init/core ainda usam PE, assim como o base kernel.
# É desejável que isso mude.


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
user_ccflags = -m32 \
	-std=gnu89 \
	-nodefaultlibs \
	-nostdinc \
	-nostdlib \
	-static \
	-fgnu89-inline \
	-ffreestanding \
	-fno-builtin \
	-fno-pie \
	-fleading-underscore \
	-fno-stack-protector \
	-s \
	-Werror=strict-prototypes    


# usermode linker flags.
user_ldflags = -m elf_i386 -T ../link.ld




#todo
#path longo. vamos mudar  as libs de lugar para gramado/libs.

LIBC    = ../../../landlib/rtl/include/
LIBCOBJ = ../../../landlib/rtl/obj

#GWS_INCLUDES  = include/    
#RENDERER      = renderer/include/  
#CMDLINE       = cmdline/include/   
#TERMINAL      = terminal/include/   


	##
	## Objects
	##
	

myObjects = crt0.o main.o rtl.o \
ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
r_render.o \
bitblt.o line.o rect.o xxxinput.o char.o dtext.o createw.o gws.o comp.o window.o \
grprim.o sprite.o demos.o bmp.o connect.o button.o font.o\
termios.o ioctl.o fcntl.o    


.PHONY: all all-c gws-link finalize clean

all: main.o all-c gws-link finalize clean
	@echo "Ok?"
main.o:
	$(CC)  -c  main.c $(user_ccflags) -I $(LIBC) -I $(API02)  -I include/ -I . -o main.o
all-c:

	$(CC)  -c view/render/r_render.c  $(user_ccflags) -I $(LIBC) -I include/ -I .  -o r_render.o

	# view-like component

	$(CC)  -c  view/display/bitblt.c    $(user_ccflags) -I $(LIBC) -I include/ -I .  -o bitblt.o

	$(CC)  -c  view/char.c     $(user_ccflags) -I $(LIBC) -I include/ -I .  -o char.o
	$(CC)  -c  view/dtext.c    $(user_ccflags) -I $(LIBC) -I include/ -I .  -o dtext.o
	$(CC)  -c  view/line.c     $(user_ccflags) -I $(LIBC) -I include/ -I .  -o line.o
	$(CC)  -c  view/rect.c     $(user_ccflags) -I $(LIBC) -I include/ -I .  -o rect.o

	$(CC)  -c  view/xxxinput.c  $(user_ccflags) -I $(LIBC) -I include/ -I .  -o xxxinput.o

	$(CC)  -c  view/createw.c  $(user_ccflags) -I $(LIBC) -I include/ -I .  -o createw.o
	$(CC)  -c  view/window.c   $(user_ccflags) -I $(LIBC) -I include/ -I .  -o window.o
	$(CC)  -c  view/button.c   $(user_ccflags) -I $(LIBC) -I include/ -I .  -o button.o
	$(CC)  -c  view/comp.c     $(user_ccflags) -I $(LIBC) -I include/ -I .  -o comp.o

	$(CC)  -c  view/bmp.c      $(user_ccflags) -I $(LIBC) -I include/ -I .  -o bmp.o

	$(CC)  -c  view/grprim.c   $(user_ccflags) -I $(LIBC) -I include/ -I .  -o grprim.o
	$(CC)  -c  view/sprite.c   $(user_ccflags) -I $(LIBC) -I include/ -I .  -o sprite.o

	$(CC)  -c  view/demos.c      $(user_ccflags) -I $(LIBC) -I include/ -I .  -o demos.o
	
	# model-like component
	$(CC)  -c  model/font.c     $(user_ccflags) -I $(LIBC) -I include/ -I .  -o font.o
	$(CC)  -c  model/connect.c  $(user_ccflags) -I $(LIBC) -I include/ -I .  -o connect.o
	$(CC)  -c  model/gws.c      $(user_ccflags) -I $(LIBC) -I include/ -I .  -o gws.o
	# ...

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


gws-link:
	$(LD) $(user_ldflags) -o GWSSRV.BIN $(myObjects)
#	$(LD) -m elf_i386 -T ../link.ld -o GWSSRV.BIN $(myObjects)  

finalize:
	cp GWSSRV.BIN ../bin

clean:
	-rm *.o
	-rm GWSSRV.BIN 
	
	
