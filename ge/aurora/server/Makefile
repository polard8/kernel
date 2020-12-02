
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


#CFLAGS = -m32 \
#	--std=gnu89 \
#	-nodefaultlibs \
#	-nostdinc \
#	-nostdlib \
#	-static \
#	-fgnu89-inline \
#	-ffreestanding \
#	-fno-builtin \
#	-fno-pie \
#	-no-pie \
#	-fno-stack-protector \
#	-s



CFLAGS = -m32 \
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
	


#todo
#path longo. vamos mudar  as libs de lugar para gramado/libs.

LIBC    = ../../../ge/rtl/include/
LIBCOBJ = ../../../ge/rtl/obj


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
pixel.o line.o rect.o char.o dtext.o createw.o gws.o comp.o window.o \
grprim.o sprite.o demos.o bmp.o connect.o button.o font.o\
termios.o ioctl.o fcntl.o    



.PHONY: all all-c gws-link finalize clean

all: main.o all-c gws-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c $(CFLAGS) -I $(LIBC) -I $(API02)  -I include/ -I . -o main.o

all-c:

	gcc  -c  render/r_render.c    $(CFLAGS) -I $(LIBC) -I include/ -I .  -o r_render.o
	
	# view-like component
	gcc  -c  view/pixel.c    $(CFLAGS) -I $(LIBC) -I include/ -I .  -o pixel.o
	gcc  -c  view/char.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o char.o
	gcc  -c  view/dtext.c    $(CFLAGS) -I $(LIBC) -I include/ -I .  -o dtext.o
	gcc  -c  view/line.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o line.o
	gcc  -c  view/rect.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o rect.o
	gcc  -c  view/createw.c  $(CFLAGS) -I $(LIBC) -I include/ -I .  -o createw.o
	gcc  -c  view/window.c   $(CFLAGS) -I $(LIBC) -I include/ -I .  -o window.o
	gcc  -c  view/button.c   $(CFLAGS) -I $(LIBC) -I include/ -I .  -o button.o
	gcc  -c  view/comp.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o comp.o

	gcc  -c  view/bmp.c      $(CFLAGS) -I $(LIBC) -I include/ -I .  -o bmp.o

	gcc  -c  view/grprim.c   $(CFLAGS) -I $(LIBC) -I include/ -I .  -o grprim.o
	gcc  -c  view/sprite.c   $(CFLAGS) -I $(LIBC) -I include/ -I .  -o sprite.o

	gcc  -c  view/demos.c      $(CFLAGS) -I $(LIBC) -I include/ -I .  -o demos.o
	
	# model-like component
	gcc  -c  model/font.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o font.o
	gcc  -c  model/connect.c  $(CFLAGS) -I $(LIBC) -I include/ -I .  -o connect.o
	gcc  -c  model/gws.c      $(CFLAGS) -I $(LIBC) -I include/ -I .  -o gws.o
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
	ld -m elf_i386 -T ../link.ld -o GWSSRV.BIN $(myObjects)  
	

finalize:
	cp GWSSRV.BIN ../bin

clean:
	-rm *.o
	-rm GWSSRV.BIN 
	
	
