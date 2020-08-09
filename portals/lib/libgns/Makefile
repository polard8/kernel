
# Client-side library for gws window server.
# 2020 - Created by Fred Nora.


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = libgws - Client-side library for gws window server.


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


LIBS  = -I. -I ../libc03/include/



.PHONY: all all-c gws-link finalize clean



all: main.o all-c gws-link finalize clean
	@echo "Ok?"

main.o:
#nothing


   # vamos incluir a libcore do mesmo modo que a api incluiu.
   # Porém acho que a api não usou recursos da libcore;

all-c:
	#gcc -c connect.c  $(CFLAGS) $(LIBS) -o connect.o
	#gcc -c events.c   $(CFLAGS) $(LIBS) -o events.o
	#gcc -c rw.c       $(CFLAGS) $(LIBS) -o rw.o
	
	gcc -c gns.c      $(CFLAGS) $(LIBS) -o gns.o




#create 'ar'
gws-link:
#nothing.


finalize:
	-mkdir obj/
	-cp *.o obj/
	
clean:
	-rm *.o
	
	

