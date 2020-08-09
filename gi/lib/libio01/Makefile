
#history:
#2019 - Created by Fred Nora.


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = libio


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



.PHONY: all all-c gdeio-link finalize clean


all: main.o all-c gdeio-link finalize
	@echo "Ok?"

main.o:
	gcc  -c  libio.c $(CFLAGS) -I include/ -o libio.o 


all-c:

gdeio-link:

finalize:
	-mkdir obj
	-cp libio.o obj/

clean:
	-rm *.o



