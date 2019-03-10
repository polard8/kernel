
# Compiling Gramado Core Shell.
# Shell/GWS
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
#NAME = Gramado Core Shell


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


LIBC    = ../../../../lib/gdelibs/libc02/include/
LIBCOBJ = ../../../../lib/gdelibs/libc02/obj


API01   = ../../../../lib/gdelibs/api01/include/
APIOBJ  = ../../../../lib/gdelibs/api01/obj


GWS    = gws/include/   
#GWSOBJ = gws/obj cancelado



	##
	## Objects
	##
	
	
myObjects = crt0.o main.o \
stubs.o \
ctype.o stdio.o stdlib.o string.o conio.o socket.o signal.o unistd.o \
api.o \
shellui.o builtins.o desktop.o login.o tests.o \
pixel.o line.o rect.o char.o gws.o    




.PHONY: all all-c shell-link finalize clean

all: crt0.o main.o all-c shell-link finalize clean
	@echo "Ok?"

head.o:
#	nasm  head.s  -felf -o head.o

crt0.o:
	gcc  -c  crt0.c -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o crt0.o

main.o:
	gcc  -c  main.c -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o main.o

all-c:
	gcc  -c  shellui.c   -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o shellui.o
	gcc  -c  builtins.c  -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o builtins.o
	gcc  -c  login.c     -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o login.o
	gcc  -c  tests.c     -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o tests.o
	gcc  -c  desktop.c   -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o desktop.o	
	
#gws
	gcc  -c  gws/src/gws/char.c     -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o char.o
	gcc  -c  gws/src/gws/line.c     -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o line.o
	gcc  -c  gws/src/gws/pixel.c    -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o pixel.o
	gcc  -c  gws/src/gws/rect.c     -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o rect.o
	gcc  -c  gws/src/gws.c          -I $(LIBC) -I $(API01) -I $(GWS) $(CFLAGS) -o gws.o
# ...	
	
	
#	gcc  -c  parser.c    -I ../../../include/libc/ $(CFLAGS) -o parser.o
#	gcc  -c  lexer.c     -I ../../../include/libc/ $(CFLAGS) -o lexer.o
#	gcc  -c  net.c       -I ../../../include/libc/ $(CFLAGS) -o net.o
#	gcc  -c  terminal.c  -I ../../../include/libc/ $(CFLAGS) -o terminal.o

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
	
	
	#gws cancelado
#	cp $(GWSOBJ)/pixel.o   .
	

shell-link:
	ld -m elf_i386 -T link.ld -o SHELL.BIN $(myObjects) -Map shell_map.s


finalize:
	cp SHELL.BIN ../../../../bin/boot/

clean:
	-rm *.o
	-rm SHELL.BIN 
	
	
