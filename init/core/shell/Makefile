
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

head.o:
	nasm  head.s  -felf -o head.o
	
crt0.o:
	gcc  -c  crt0.c -I include/ $(CFLAGS) -o crt0.o 

main.o:
	gcc  -c  main.c -I include/ $(CFLAGS) -o main.o  
	
all-c:	
	
	gcc  -c  main.c -I include/ $(CFLAGS) -o shellui.o
	gcc  -c  main.c -I include/ $(CFLAGS) -o builtins.o
	gcc  -c  main.c -I include/ $(CFLAGS) -o desktop.o
	gcc  -c  main.c -I include/ $(CFLAGS) -o parser.o
	gcc  -c  main.c -I include/ $(CFLAGS) -o net.o
	gcc  -c  main.c -I include/ $(CFLAGS) -o terminal.o	
	
	cp /gramado/lib/api/api.o  /sdk\bin\api.o
	cp /gramado/lib/ctype.o    /sdk\bin\ctype.o
	cp /gramado/lib/stdio.o    /sdk\bin\stdio.o
	cp /gramado/lib/stdlib.o   /sdk\bin\stdlib.o
	cp /gramado/lib/string.o   /sdk\bin\string.o
	cp /gramado/lib/conio.o    /sdk\bin\conio.o
	cp /gramado/lib/wait.o     /sdk\bin\wait.o
	cp /gramado/lib/unistd.o   /sdk\bin\unistd.o	
	
shell-link: 
	ld -m i386pe -T link.ld -o SHELL.BIN $(myObjects) -Map shell_map.s	
	
	@echo "Ok?"
	
	