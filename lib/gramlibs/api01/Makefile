#api01


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
	-fno-stack-protector \
	-s

#	-fleading-underscore \
#	-fno-stack-protector \
#	-s


#.PHONY: all all-c jackpot-link finalize clean
.PHONY: all all-c api01-link finalize clean

#all: main.o all-c jackpot-link finalize clean
all: main.o all-c api01-link finalize clean
	@echo "Ok?"

main.o:
#	gcc  -c  gde.c $(CFLAGS) -o gde.o

all-c:

	gcc  -c  api.c   $(CFLAGS) -I ../libc01/include/ -o api.o
#	gcc  -c  ctype.c   $(CFLAGS) -I include/ -o ctype.o	
#	gcc  -c  stdio.c   $(CFLAGS) -I include/ -o stdio.o	
#	gcc  -c  stdlib.c  $(CFLAGS) -I include/ -o stdlib.o	
#	gcc  -c  string.c  $(CFLAGS) -I include/ -o string.o	
#	gcc  -c  time.c    $(CFLAGS) -I include/ -o time.o	
#	gcc  -c  unistd.c  $(CFLAGS) -I include/ -o unistd.o	
#	gcc  -c  wait.c    $(CFLAGS) -I include/ -o wait.o	
	
#	cp ../../lib/libc01/obj/ctype.o   .
#	cp ../../lib/libc01/obj/stdio.o   .
#	cp ../../lib/libc01/obj/stdlib.o  .	
#	cp ../../lib/libc01/obj/string.o  .
#	cp ../../lib/libc01/obj/time.o    .
	
	#todo
#	cp ../../lib/api01/obj/api.o      .
	
#	cp ../../lib/libc01/obj/unistd.o  .
	

#create 'ar'
api01-link:
#	ld -m i386pe -T link.ld -o JACKPOT.BIN $(myObjects) -Map app_map.s

finalize:
#	cp JACKPOT.BIN  ../../../bin
	-mkdir obj/
	-cp *.o obj/
	
clean:
#	-rm *.o
#	-rm JACKPOT.BIN 
	
	

