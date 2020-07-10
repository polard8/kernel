
# Gramado Core - INIT
# It's a taskman process for Gramado Core environment.

#history:
#2019 - Created by Fred Nora and Luciano Gonçalez.



VERSION = 0
PATCHLEVEL = 1
SUBLEVEL = 0
EXTRAVERSION =
#NAME = taskman


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


# desejamos tirar essa flag.
#	-fleading-underscore \


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




.PHONY: all all-c taskman-link finalize clean

all: crt0.o main.o all-c taskman-link finalize clean
	@echo "Ok?"


crt0.o:
	#gcc  -c  crt0.c -I $(LIBC) -I $(API) $(CFLAGS) -o crt0.o

main.o:
	gcc  -c  main.c -I $(LIBC) -I $(API) $(CFLAGS) -o main.o

all-c:

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

taskman-link:
	ld -m elf_i386 -T ../link.ld -o ZTASKMAN.BIN $(myObjects)   


finalize:
#	cp ZTASKMAN.BIN ../../bin

clean:
	-rm *.o
#	-rm ZTASKMAN.BIN 
	
	
