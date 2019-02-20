#libc01


VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
EXTRAVERSION = -rc0
NAME = Gramado LibC


#STATIC_LIB = obj/lib/libc01.a
#SHARED_LIB = obj/lib/libc01.so


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
.PHONY: all all-c libc01-link finalize clean

#all: main.o all-c jackpot-link finalize clean
all: main.o all-c libc01-link finalize clean
	@echo "Ok?"

main.o:
#	gcc  -c  gde.c $(CFLAGS) -o gde.o

all-c:

#/ctype
	gcc  -c  ctype/ctype.c   $(CFLAGS) -I include/ -o ctype.o	
		
#/socket
#	gcc  -c  socket.c    $(CFLAGS) -I include/ -o socket.o


#/stdio 
	gcc  -c  stdio/stdio.c   $(CFLAGS) -I include/ -o stdio.o	
	
#/stdlib
	gcc  -c  stdlib/stdlib.c  $(CFLAGS) -I include/ -o stdlib.o	
	
#/stubs	
	gcc  -c  stubs/stubs.c   $(CFLAGS) -I include/ -o stubs.o		
	
#/unistd
	gcc  -c  unistd/unistd.c  $(CFLAGS) -I include/ -o unistd.o	
	
	
	
# outros	
	gcc  -c  conio.c   $(CFLAGS) -I include/ -o conio.o
	gcc  -c  string.c  $(CFLAGS) -I include/ -o string.o	
	gcc  -c  time.c    $(CFLAGS) -I include/ -o time.o	
	gcc  -c  wait.c    $(CFLAGS) -I include/ -o wait.o		
	
	gcc  -c  math.c    $(CFLAGS) -I include/ -o math.o			
	
#...	
		

#create 'ar'
libc01-link:
#	ld -m i386pe -T link.ld -o JACKPOT.BIN $(myObjects) -Map app_map.s

finalize:
#	cp JACKPOT.BIN  ../../../bin
	-mkdir obj/
	-cp *.o obj/
	
clean:
	-rm *.o

	
	

