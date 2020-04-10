
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


CFLAGS = -m32 \
	--std=gnu89 \
	-nodefaultlibs \
	-nostdinc \
	-nostdlib \
	-static \
	-fgnu89-inline \
	-ffreestanding \
	-fno-builtin \
	-fno-pie \
	-no-pie \
	-fno-stack-protector \
	-s



#todo
#path longo. vamos mudar  as libs de lugar para gramado/libs.

LIBC    = ../../../lib/libc03/include/
LIBCOBJ = ../../../lib/libc03/obj
API02   = ../../../lib/libgui/include/
APIOBJ  = ../../../lib/libgui/obj


GWS_INCLUDES  = include/    


#RENDERER = renderer/include/  
#CMDLINE = cmdline/include/   
#TERMINAL  = terminal/include/   




	##
	## Objects
	##
	
	
myObjects = crt0.o main.o stubs.o \
ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
api.o \
pixel.o line.o rect.o char.o dtext.o createw.o gws.o comp.o window.o \
bmp.o \
termios.o ioctl.o fcntl.o    



.PHONY: all all-c gws-link finalize clean

all: main.o all-c gws-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c -I $(LIBC) -I $(API02)  -I $(GWS_INCLUDES) -I . $(CFLAGS) -o main.o

all-c:

	# gws
	gcc  -c  char.c     -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o char.o
	gcc  -c  comp.c     -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o comp.o
	gcc  -c  createw.c  -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o createw.o
	gcc  -c  dtext.c    -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o dtext.o
	gcc  -c  line.c     -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o line.o
	gcc  -c  pixel.c    -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o pixel.o
	gcc  -c  rect.c     -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o rect.o
	gcc  -c  window.c   -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o window.o
	gcc  -c  bmp.c      -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o bmp.o
	# ...


	# base
	gcc  -c  gws.c      -I $(LIBC) -I $(API02)   -I $(GWS_INCLUDES) -I . $(CFLAGS) -o gws.o


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
	cp $(APIOBJ)/api.o .



gws-link:
	ld -m elf_i386 -T ../link.ld -o GWS.BIN $(myObjects)    


finalize:
	cp GWS.BIN ../bin

clean:
	-rm *.o
	-rm GWS.BIN 
	
	
