
#history:
#2019 - Created by Fred Nora.

#todo:
#fazer um makefile pra compilar o shell
#obs: #bugbug tem que arrumas as coisas aqui.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = INIT

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
main.o \
stdio.o \
ctype.o \
string.o \
stdlib.o \
unistd.o \
api.o  



.PHONY: all all-c shell-link finalize clean

all: head.o main.o all-c shell-link finalize clean
	@echo "Ok?"

head.o:
	nasm  head.s  -felf -o head.o

main.o:
	gcc  -c  main.c -I ../../../include/libc/ $(CFLAGS) -o main.o

all-c:
	cp ../../../lib/stdio.o .
	cp ../../../lib/string.o .
	cp ../../../lib/ctype.o .
	cp ../../../lib/stdlib.o .
	cp ../../../lib/api/api.o .
	cp ../../../lib/unistd.o .

shell-link:
	ld -m i386pe -T link.ld -o INIT.BIN $(myObjects) -Map init_map.s

finalize:
	cp INIT.BIN ../../../bin

clean:
	-rm *.o
	-rm INIT.BIN 
	
	
