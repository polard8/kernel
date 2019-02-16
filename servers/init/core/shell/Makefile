
# Gramado Kernel Shell.
# A mini-shell to setup and test the kernel functionalities.

#history:
#2019 - Created by Fred Nora and Luciano Gonçalez.


# todo:
# Os aplicativos em /init/core ainda usam PE, assim como o base kernel.
# É desejável que isso mude.


VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
EXTRAVERSION =
#NAME = gramado Kernel Shell


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
	
#	-fleading-underscore \
#	-fno-stack-protector \
#	-s


# desejamos tirar essa flag.
#	-fleading-underscore \


LIBC    = ../../../../lib/gdelibs/libc01/include/
LIBCOBJ = ../../../../lib/gdelibs/libc01/obj

API01   = ../../../../lib/gdelibs/api01/include/
APIOBJ  = ../../../../lib/gdelibs/api01/obj

	##
	## Objects
	##
#myObjects = head.o \



myObjects = crt0.o \
main.o \
shellui.o \
api.o \
ctype.o \
stdio.o \
stdlib.o \
string.o \
conio.o \
builtins.o \
desktop.o \
unistd.o \
login.o   




.PHONY: all all-c shell-link finalize clean

all: crt0.o main.o all-c shell-link finalize clean
	@echo "Ok?"

head.o:
#	nasm  head.s  -felf -o head.o

crt0.o:
	gcc  -c  crt0.c -I $(LIBC) -I $(API01) $(CFLAGS) -o crt0.o

main.o:
	gcc  -c  main.c -I $(LIBC) -I $(API01) $(CFLAGS) -o main.o

all-c:
	gcc  -c  shellui.c   -I $(LIBC) -I $(API01) $(CFLAGS) -o shellui.o
	gcc  -c  builtins.c  -I $(LIBC) -I $(API01) $(CFLAGS) -o builtins.o
	gcc  -c  desktop.c   -I $(LIBC) -I $(API01) $(CFLAGS) -o desktop.o
	gcc  -c  login.c     -I $(LIBC) -I $(API01) $(CFLAGS) -o login.o	
	
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

shell-link:
	ld -m elf_i386 -T link.ld -o SHELL.BIN $(myObjects) -Map shell_map.s


finalize:
	cp SHELL.BIN ../../../../bin/init/

clean:
	-rm *.o
	-rm SHELL.BIN 
	
	
