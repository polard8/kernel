
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

#myObjects = main.o \
#ctype.o \
#stdio.o \
#stdlib.o \
#string.o \
#time.o \
#api.o \
#unistd.o  



#.PHONY: all all-c jackpot-link finalize clean
.PHONY: all all-c gde-link finalize clean

#all: main.o all-c jackpot-link finalize clean
all: main.o all-c gde-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  gde.c $(CFLAGS) -o gde.o

all-c:

	gcc  -c  gdeapi.c $(CFLAGS) -o gdeapi.o
	gcc  -c  gdelib.c $(CFLAGS) -o gdelib.o	

#	cp ../../lib/libc01/obj/ctype.o   .
#	cp ../../lib/libc01/obj/stdio.o   .
#	cp ../../lib/libc01/obj/stdlib.o  .	
#	cp ../../lib/libc01/obj/string.o  .
#	cp ../../lib/libc01/obj/time.o    .
	
	#todo
#	cp ../../lib/api01/obj/api.o      .
	
#	cp ../../lib/libc01/obj/unistd.o  .
	


gde-link:
#	ld -m i386pe -T link.ld -o JACKPOT.BIN $(myObjects) -Map app_map.s

finalize:
#	cp JACKPOT.BIN  ../../../bin

clean:
#	-rm *.o
#	-rm JACKPOT.BIN 
	
	

