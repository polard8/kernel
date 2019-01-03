
#history:
#2019 - Created by Fred Nora.

#todo:
#fazer um makefile pra compilar o shell
#obs: #bugbug tem que arrumas as coisas aqui.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = jackpot

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

myObjects = main.o \
ctype.o \
stdio.o \
stdlib.o \
string.o \
time.o \
api.o \
unistd.o  



.PHONY: all all-c jackpot-link finalize clean

all: main.o all-c jackpot-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c -I ../../include/libc/ $(CFLAGS) -o main.o

all-c:
	cp ../../lib/ctype.o .
	cp ../../lib/stdio.o .
	cp ../../lib/stdlib.o .	
	cp ../../lib/string.o .
	cp ../../lib/time.o .
	cp ../../lib/api/api.o .
	cp ../../lib/unistd.o .
	


jackpot-link:
	ld -m i386pe -T link.ld -o JACKPOT.BIN $(myObjects) -Map app_map.s

finalize:
	cp JACKPOT.BIN ../../bin

clean:
	-rm *.o
	-rm JACKPOT.BIN 
	
	
