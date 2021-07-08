
# Client-side library for gws window server.
# 2020 - Created by Fred Nora.


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = libgws - Client-side library for gws window server.


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


LIBS  = -I. -I ../../rtl/include/




.PHONY: all all-c finalize clean

all: all-c finalize clean
	@echo "Ok?"

all-c:
	gcc -c gns.c      $(CFLAGS) $(LIBS) -o gns.o

	#gcc -c connect.c  $(CFLAGS) $(LIBS) -o connect.o
	#gcc -c events.c   $(CFLAGS) $(LIBS) -o events.o
	#gcc -c rw.c       $(CFLAGS) $(LIBS) -o rw.o

finalize:
	-mkdir obj/
	-cp *.o obj/
	
clean:
	-rm *.o
	
	

