
#history:
#2019 - Created by Fred Nora.


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = gdeio


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



.PHONY: all all-c gdeio-link finalize clean


all: main.o all-c gdeio-link finalize
	@echo "Ok?"

main.o:
	gcc  -c  gdeio.c $(CFLAGS) -I include/ -o gdeio.o

all-c:


gdeio-link:


finalize:
	-mkdir obj
	-cp gdeio.o obj/

clean:
	-rm *.o
	
	

