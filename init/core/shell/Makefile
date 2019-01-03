
#todo:
#fazer um makefile pra compilar o shell
#obs: #bugbug tem que arrumas as coisas aqui.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = GramadoShell

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
	-fleading-underscore \
	-fno-stack-protector \
	-s


	##
	## Objects
	##

myObjects = head.o \
crt0.o \
main.o \
shellui.o \
api.o \
ctype.o \
stdio.o \
stdlib.o \
string.o \
conio.o \
unistd.o \
builtins.o \
desktop.o \
parser.o \
lexer.o \
wait.o \
net.o \
terminal.o



all: head.o crt0.o main.o all-c shell-link
	@echo "Ok?"

head.o:
	nasm  head.s  -felf -o head.o

crt0.o:
	gcc  -c  crt0.c -I ../../../include/libc/ $(CFLAGS) -o crt0.o

main.o:
	gcc  -c  main.c -I ../../../include/libc/ $(CFLAGS) -o main.o

all-c:
	gcc  -c  shellui.c   -I ../../../include/libc/ $(CFLAGS) -o shellui.o
	gcc  -c  builtins.c  -I ../../../include/libc/ $(CFLAGS) -o builtins.o
	gcc  -c  desktop.c   -I ../../../include/libc/ $(CFLAGS) -o desktop.o
	gcc  -c  parser.c    -I ../../../include/libc/ $(CFLAGS) -o parser.o
	gcc  -c  lexer.c    -I ../../../include/libc/ $(CFLAGS) -o lexer.o
	gcc  -c  net.c       -I ../../../include/libc/ $(CFLAGS) -o net.o
	gcc  -c  terminal.c  -I ../../../include/libc/ $(CFLAGS) -o terminal.o

	cp ../../../lib/api/api.o .
	cp ../../../lib/ctype.o .
	cp ../../../lib/stdio.o .
	cp ../../../lib/stdlib.o .
	cp ../../../lib/string.o .
	cp ../../../lib/conio.o .
	cp ../../../lib/wait.o .
	cp ../../../lib/unistd.o .

shell-link:
	ld -m i386pe -T link.ld -o SHELL.BIN $(myObjects) -Map shell_map.s

clean:
	-rm *.o shell_map.s
