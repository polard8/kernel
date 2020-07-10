# gdeterm

#todo:
#fazer um makefile pra compilar o shell
#obs: #bugbug tem que arrumas as coisas aqui.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME =   

#todo:
#We need to simplify these flags

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



#LIBC    = ../../lib/gdelibs/libc01/include/
#LIBCOBJ = ../../lib/gdelibs/libc01/obj
#API01   = ../../lib/gdelibs/api01/include/
#APIOBJ  = ../../lib/gdelibs/api01/obj

LIBC    = ../../lib/libc02/include/
LIBCOBJ = ../../lib/libc02/obj
API02   = ../../lib/api02/include/
APIOBJ  = ../../lib/api02/obj




	##
	## Objects
	##

myObjects = crt0.o \
main.o \
termui.o \
api.o \
ctype.o \
stdio.o \
stdlib.o \
string.o \
conio.o \
builtins.o \
desktop.o \
unistd.o \
stubs.o    



.PHONY: all all-c shell-link finalize clean

all: crt0.o main.o all-c shell-link finalize clean
	@echo "Ok?"

#head.o:
#	nasm  head.s  -felf -o head.o

crt0.o:
	gcc  -c  crt0.c  $(CFLAGS) -I $(LIBC) -I $(API02) -o crt0.o

main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC) -I $(API02) -o main.o

all-c:
	gcc  -c  termui.c   -I $(LIBC) -I $(API02)  $(CFLAGS) -o termui.o
	gcc  -c  builtins.c  -I $(LIBC) -I $(API02)  $(CFLAGS) -o builtins.o
	gcc  -c  desktop.c   -I $(LIBC) -I $(API02)  $(CFLAGS) -o desktop.o
	
#	gcc  -c  parser.c    -I ../../../lib/libc01/include/ -I ../../../lib/api01/include/ $(CFLAGS) -o parser.o
#	gcc  -c  lexer.c     -I ../../../lib/libc01/include/ -I ../../../lib/api01/include/ $(CFLAGS) -o lexer.o
#	gcc  -c  net.c       -I ../../../lib/libc01/include/ -I ../../../lib/api01/include/ $(CFLAGS) -o net.o
#	gcc  -c  terminal.c  -I ../../../lib/libc01/include/ -I ../../../lib/api01/include/ $(CFLAGS) -o terminal.o

	cp $(APIOBJ)/api.o      .

	cp $(LIBCOBJ)/ctype.o     .
	cp $(LIBCOBJ)/stdio.o     .
	cp $(LIBCOBJ)/stdlib.o    .
	cp $(LIBCOBJ)/string.o    .
	cp $(LIBCOBJ)/conio.o     .
	cp $(LIBCOBJ)/wait.o      .
	cp $(LIBCOBJ)/unistd.o    .
	cp $(LIBCOBJ)/stubs.o     .


shell-link:
	ld -m elf_i386 -T ../link.ld -o GDETERM.BIN $(myObjects)   
	
	

finalize:
	cp GDETERM.BIN ../../bin

clean:
	-rm *.o
	-rm GDETERM.BIN 


