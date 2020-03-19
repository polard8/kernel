
# gws - Gramado Window Server.

# Compiling gws
# history:



# todo:
# Os aplicativos em /init/core ainda usam PE, assim como o base kernel.
# É desejável que isso mude.


VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
EXTRAVERSION = -rc0
#NAME = gws for garden


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


LIBC    = ../../lib/libcore/include/
LIBCOBJ = ../../lib/libcore/obj
API02   = ../../lib/libgui/include/
APIOBJ  = ../../lib/libgui/obj


GWS  = gwscore/include/   


#RENDERER = renderer/include/  
#CMDLINE = cmdline/include/   
#TERMINAL  = terminal/include/   




	##
	## Objects
	##
	
	
myObjects = crt0.o main.o \
stubs.o \
ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
api.o \
pixel.o line.o rect.o char.o dtext.o createw.o gws.o comp.o \
termios.o ioctl.o    






.PHONY: all all-c shell-link finalize clean

all: crt0.o main.o all-c shell-link finalize clean
	@echo "Ok?"

head.o:
#	nasm  head.s  -felf -o head.o

crt0.o:
	#gcc  -c  arch/x86/crt0.c -I $(LIBC) -I $(API02)  -I $(GWS) -I . $(CFLAGS) -o crt0.o

main.o:
	gcc  -c  main.c -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o main.o

all-c:

#gws
	gcc  -c  gwscore/src/gws/char.c     -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o char.o
	gcc  -c  gwscore/src/gws/line.c     -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o line.o
	gcc  -c  gwscore/src/gws/pixel.c    -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o pixel.o
	gcc  -c  gwscore/src/gws/rect.c     -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o rect.o
	gcc  -c  gwscore/src/gws/dtext.c    -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o dtext.o
	gcc  -c  gwscore/src/gws/createw.c  -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o createw.o
	gcc  -c  gwscore/src/gws.c          -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o gws.o
	gcc  -c  gwscore/src/comp.c         -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o comp.o
# ...	



#renderer
#	gcc  -c  renderer/src/renderer.c     -I $(LIBC) -I $(API02) -I $(TERMINAL) -I $(GWS) -I . $(CFLAGS) -o renderer.o
	
#cmdline
#	gcc  -c  cmdline/src/cmdline.c   -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o cmdline.o
#	gcc  -c  cmdline/src/builtins.c  -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o builtins.o
#	gcc  -c  cmdline/src/tests.c     -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o tests.o
#	gcc  -c  cmdline/src/login.c     -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o login.o
	

#host
#	gcc  -c  host/src/input.c  -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o input.o
#	gcc  -c  host/src/output.c  -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o output.o
	
#terminal
#	gcc  -c  terminal/src/terminal.c  -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o terminal.o
#	gcc  -c  terminal/src/termui.c    -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o termui.o
#	gcc  -c  terminal/src/desktop.c   -I $(LIBC) -I $(API02)   -I $(GWS) -I . $(CFLAGS) -o desktop.o	

	
#more
#	gcc  -c  parser.c    -I ../../../include/libc/ $(CFLAGS) -o parser.o
#	gcc  -c  lexer.c     -I ../../../include/libc/ $(CFLAGS) -o lexer.o
#	gcc  -c  net.c       -I ../../../include/libc/ $(CFLAGS) -o net.o



	cp $(APIOBJ)/api.o .
	
	cp $(LIBCOBJ)/crt0.o .
		
	cp $(LIBCOBJ)/ctype.o .
	cp $(LIBCOBJ)/stdio.o .
	cp $(LIBCOBJ)/stdlib.o .
	cp $(LIBCOBJ)/string.o .
	cp $(LIBCOBJ)/conio.o .
#	cp ../../../lib/wait.o .

	cp $(LIBCOBJ)/unistd.o .
	
	cp $(LIBCOBJ)/stubs.o .
	
	cp $(LIBCOBJ)/socket.o .

	cp $(LIBCOBJ)/signal.o .
	
	cp $(LIBCOBJ)/termios.o .
	cp $(LIBCOBJ)/ioctl.o .
	
	#gws cancelado
#	cp $(GWSOBJ)/pixel.o   .
	

shell-link:
	ld -m elf_i386 -T link.ld -o GWS.BIN $(myObjects) -Map app_map.s


finalize:
	cp GWS.BIN ../../bin

clean:
	-rm *.o
	-rm GWS.BIN 
	
	
