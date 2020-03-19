
# Gramado Core - INIT
# It's a init process for Gramado Core environment.

VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
EXTRAVERSION =
#NAME = Init


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
	
	


API     = ../../lib/api02/include/
APIOBJ  = ../../lib/api02/obj
LIBC    = ../../lib/libcore/include/
LIBCOBJ = ../../lib/libcore/obj




	#
	# Objects
	#

myObjects = crt0.o main.o \
api.o \
ctype.o \
stdio.o \
stdlib.o \
string.o \
conio.o \
unistd.o \
termios.o \
ioctl.o \
stubs.o    



.PHONY: all all-c shell-link finalize clean

all: crt0.o main.o all-c shell-link finalize clean
	@echo "Init Ok?"

head.o:
	# Nothing.

crt0.o:
	#gcc  -c  crt0.c -I $(LIBC) -I $(API) $(CFLAGS) -o crt0.o

main.o:
	gcc  -c  main.c -I $(LIBC) -I $(API) $(CFLAGS) -o main.o

all-c:

# We need some api and libc objects.

	cp $(LIBCOBJ)/crt0.o .
	cp $(LIBCOBJ)/stubs.o .	

	cp $(LIBCOBJ)/ctype.o .
	cp $(LIBCOBJ)/stdio.o .
	cp $(LIBCOBJ)/stdlib.o .
	cp $(LIBCOBJ)/string.o .
	cp $(LIBCOBJ)/conio.o .
	cp $(LIBCOBJ)/unistd.o .

	cp $(LIBCOBJ)/termios.o .
	cp $(LIBCOBJ)/ioctl.o .
	
	cp $(APIOBJ)/api.o .

shell-link:
	ld -m elf_i386 -T link.ld -o ZINIT.BIN $(myObjects) -Map map.s


finalize:
	cp ZINIT.BIN  ../../bin

clean:
	-rm *.o
	-rm ZINIT.BIN 
	

