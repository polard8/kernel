# lisp for gde
# Trying to port this thing.

VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = gde lisp

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


LIBC    = ../../lib/libc03/include/
LIBCOBJ = ../../lib/libc03/obj

API     = ../../lib/api02/include/
APIOBJ  = ../../lib/api02/obj


	##
	## Objects
	##

myObjects = crt0.o main.o \
ctype.o \
stdio.o \
stdlib.o \
string.o \
time.o \
unistd.o \
termios.o \
fcntl.o \
ioctl.o \
stubs.o    



.PHONY: all all-c jackpot-link finalize clean

all: main.o all-c jackpot-link finalize clean
	@echo "Ok?"

main.o:
#	gcc  -c  crt0.c  $(CFLAGS) -I $(LIBC) -I $(API) -o crt0.o
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC) -I $(API) -o main.o

all-c:

	cp $(LIBCOBJ)/crt0.o   .
	
	cp $(LIBCOBJ)/stubs.o   .
		
	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o   .
	cp $(LIBCOBJ)/stdlib.o  .
	cp $(LIBCOBJ)/string.o  .
	cp $(LIBCOBJ)/time.o    .
	cp $(LIBCOBJ)/unistd.o  .
	cp $(LIBCOBJ)/termios.o  .
	cp $(LIBCOBJ)/fcntl.o  .
	cp $(LIBCOBJ)/ioctl.o  .


jackpot-link:
	ld -m elf_i386 -T ../link.ld -o LISP.BIN $(myObjects) 

finalize:
	cp LISP.BIN  ../bin

clean:
	-rm *.o
	-rm LISP.BIN 


