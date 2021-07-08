# library for virtual terminals


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = libvt

#todo:
#We need to simplify these flags

CFLAGS = -m64 \
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


.PHONY: all all-c libvt-link finalize clean


all: main.o all-c libvt-link finalize clean
	@echo "libvt Ok?"

main.o:
#	gcc  -c  gde.c $(CFLAGS) -o gde.o

all-c:

	gcc  -c  libvt.c   $(CFLAGS) -I ../libvt/include/ -o libvt.o


#create 'ar'
libvt-link:
#	ld -m i386pe -T link.ld -o JACKPOT.BIN $(myObjects) -Map app_map.s

finalize:
#	cp JACKPOT.BIN  ../../../bin
	-mkdir obj/
	-cp *.o obj/
	
clean:
	-rm *.o
	
	

