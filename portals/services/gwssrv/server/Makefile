
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

LIBC    = ../../../lib/libc03/include/
LIBCOBJ = ../../../lib/libc03/obj

#API02   = ../../../lib/libcore/include/
#APIOBJ  = ../../../lib/libcore/obj


#GWS_INCLUDES  = include/    


#RENDERER = renderer/include/  
#CMDLINE = cmdline/include/   
#TERMINAL  = terminal/include/   




	##
	## Objects
	##
	
	
myObjects = crt0.o main.o stubs.o \
ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
pixel.o line.o rect.o char.o dtext.o createw.o gws.o comp.o window.o \
bmp.o connect.o button.o font.o\
termios.o ioctl.o fcntl.o    



.PHONY: all all-c gws-link finalize clean

all: main.o all-c gws-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c $(CFLAGS) -I $(LIBC) -I $(API02)  -I include/ -I . -o main.o

all-c:

	# gws
	gcc  -c  char.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o char.o
	gcc  -c  comp.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o comp.o
	gcc  -c  createw.c  $(CFLAGS) -I $(LIBC) -I include/ -I .  -o createw.o
	gcc  -c  dtext.c    $(CFLAGS) -I $(LIBC) -I include/ -I .  -o dtext.o
	gcc  -c  line.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o line.o
	gcc  -c  pixel.c    $(CFLAGS) -I $(LIBC) -I include/ -I .  -o pixel.o
	gcc  -c  rect.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o rect.o
	gcc  -c  window.c   $(CFLAGS) -I $(LIBC) -I include/ -I .  -o window.o
	gcc  -c  bmp.c      $(CFLAGS) -I $(LIBC) -I include/ -I .  -o bmp.o
	gcc  -c  connect.c  $(CFLAGS) -I $(LIBC) -I include/ -I .  -o connect.o
	gcc  -c  button.c   $(CFLAGS) -I $(LIBC) -I include/ -I .  -o button.o
	gcc  -c  font.c     $(CFLAGS) -I $(LIBC) -I include/ -I .  -o font.o
	# ...

	# base
	gcc  -c  gws.c $(CFLAGS) -I $(LIBC) -I include/ -I . -o gws.o


	# libc03
	cp $(LIBCOBJ)/crt0.o .
	cp $(LIBCOBJ)/stubs.o .
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


	# libgui
	#cp $(APIOBJ)/api.o .


gws-link:
	ld -m elf_i386 -T ../link.ld -o GWSSRV.BIN $(myObjects) -Map=map.txt   
	 


finalize:
	cp GWSSRV.BIN ../bin

clean:
	-rm *.o
	-rm GWSSRV.BIN 
	
	
