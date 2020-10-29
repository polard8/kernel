
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
	
	


#mudaremos a lib de lugar
LIBC    = ../../../ge/rtl/include/
LIBCOBJ = ../../../ge/rtl/obj

API     = ../libcore/include/
APIOBJ  = ../libcore/obj



	##
	## Objects
	##
	
	
myObjects = crt0.o main.o \
rtl.o \
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
	gcc  -c  crt0.c $(CFLAGS) -I $(LIBC) -I $(API) -I .  -o crt0.o

main.o:
	gcc  -c  main.c $(CFLAGS) -I $(LIBC) -I $(API) -I .  -o main.o

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
	gcc  -c  base/cmdline.c   $(CFLAGS) -I $(LIBC) -I $(API)  -I .  -o cmdline.o
	gcc  -c  base/builtins.c  $(CFLAGS) -I $(LIBC) -I $(API)  -I .  -o builtins.o
	gcc  -c  base/tests.c     $(CFLAGS) -I $(LIBC) -I $(API)  -I .  -o tests.o
	gcc  -c  base/login.c     $(CFLAGS) -I $(LIBC) -I $(API)  -I .  -o login.o


#host
	gcc  -c  base/input.c  $(CFLAGS) -I $(LIBC) -I $(API)    -I . -o input.o
#	gcc  -c  base/output.c  -I $(LIBC) -I $(API)   -I . $(CFLAGS) -o output.o
	
#terminal
	gcc  -c  base/terminal.c  $(CFLAGS) -I $(LIBC) -I $(API) -I . -o terminal.o
	gcc  -c  base/termui.c    $(CFLAGS) -I $(LIBC) -I $(API) -I . -o termui.o
	gcc  -c  base/desktop.c   $(CFLAGS) -I $(LIBC) -I $(API) -I . -o desktop.o	

	
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
	
	cp $(LIBCOBJ)/rtl.o .
	
	cp $(LIBCOBJ)/socket.o .

	cp $(LIBCOBJ)/signal.o .
	
	cp $(LIBCOBJ)/termios.o .
	cp $(LIBCOBJ)/ioctl.o .
	cp $(LIBCOBJ)/fcntl.o .
	
	#gws cancelado
#	cp $(GWSOBJ)/pixel.o   .
	

shell-link:
	ld -m elf_i386 -T ../link.ld -o NORATERM.BIN $(myObjects)    
	
	
	
	


finalize:
	cp NORATERM.BIN ../bin

clean:
	-rm *.o
	-rm NORATERM.BIN 
	
	
