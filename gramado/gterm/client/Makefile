
# Compiling Noraterm
# 
# history:
#     2019 - Created by Fred Nora and Luciano Gonçalez.


# todo:
# Os aplicativos em /init/core ainda usam PE, assim como o base kernel.
# É desejável que isso mude.


VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
EXTRAVERSION = -rc0
#NAME = Noraterm for gde.


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


#mudaremos a lib de lugar
LIBC    = ../../../lib/libc03/include/
LIBCOBJ = ../../../lib/libc03/obj
API     = ../../../lib/libcore/include/
APIOBJ  = ../../../lib/libcore/obj





	##
	## Objects
	##
	
	
myObjects = crt0.o main.o \
stubs.o \
ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
api.o \
builtins.o desktop.o login.o tests.o cmdline.o \
input.o \
terminal.o termui.o termios.o ioctl.o fcntl.o   


   



.PHONY: all all-c shell-link finalize clean

all: crt0.o main.o all-c shell-link finalize clean
	@echo "Ok?"

head.o:
#	nasm  head.s  -felf -o head.o

crt0.o:
#todo: cancelar o uso desse e usar o que está na libcore.
	gcc  -c  crt0.c -I $(LIBC) -I $(API) -I . $(CFLAGS) -o crt0.o

main.o:
	gcc  -c  main.c -I $(LIBC) -I $(API)   -I . $(CFLAGS) -o main.o

all-c:

#gws
#	gcc  -c  base/char.c     -I $(LIBC) -I $(API)  -I . $(CFLAGS) -o char.o
#	gcc  -c  base/line.c     -I $(LIBC) -I $(API)  -I . $(CFLAGS) -o line.o
#	gcc  -c  base/pixel.c    -I $(LIBC) -I $(API)  -I . $(CFLAGS) -o pixel.o
#	gcc  -c  base/rect.c     -I $(LIBC) -I $(API)  -I . $(CFLAGS) -o rect.o
#	gcc  -c  base/gws.c      -I $(LIBC) -I $(API)  -I . $(CFLAGS) -o gws.o
# ...	


#renderer
#	gcc  -c  base/renderer.c     -I $(LIBC) -I $(API) -I $(TERMINAL) -I $(GWS) -I . $(CFLAGS) -o renderer.o
	
#cmdline
	gcc  -c  base/cmdline.c   -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o cmdline.o
	gcc  -c  base/builtins.c  -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o builtins.o
	gcc  -c  base/tests.c     -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o tests.o
	gcc  -c  base/login.c     -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o login.o


#host
	gcc  -c  base/input.c  -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o input.o
#	gcc  -c  base/output.c  -I $(LIBC) -I $(API)   -I . $(CFLAGS) -o output.o
	
#terminal
	gcc  -c  base/terminal.c  -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o terminal.o
	gcc  -c  base/termui.c    -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o termui.o
	gcc  -c  base/desktop.c   -I $(LIBC) -I $(API)    -I . $(CFLAGS) -o desktop.o	

	
#more
#	gcc  -c  parser.c    -I ../../../include/libc/ $(CFLAGS) -o parser.o
#	gcc  -c  lexer.c     -I ../../../include/libc/ $(CFLAGS) -o lexer.o
#	gcc  -c  net.c       -I ../../../include/libc/ $(CFLAGS) -o net.o



	cp $(APIOBJ)/api.o .
	
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
	cp $(LIBCOBJ)/fcntl.o .
	
	#gws cancelado
#	cp $(GWSOBJ)/pixel.o   .
	

shell-link:
	ld -m elf_i386 -T ../link.ld -o GTERM.BIN $(myObjects)    
	



finalize:
	cp GTERM.BIN ../bin

clean:
	-rm *.o
	-rm GTERM.BIN 
	
