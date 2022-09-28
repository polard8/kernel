#

#history:
#2019 - Created by Fred Nora.

#todo:
#fazer um makefile pra compilar o shell
#obs: #bugbug tem que arrumas as coisas aqui.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = 

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


#test
LIBGWS    = ../../lib/libgws/include/
LIBGWSOBJ = ../../lib/libgws/obj


	##
	## Objects
	##

myObjects = crt0.o main.o stubs.o \
ctype.o \
stdio.o \
fcntl.o \
stdlib.o \
string.o \
unistd.o \
termios.o \
ioctl.o \
socket.o \
gws.o connect.o events.o rw.o    








.PHONY: all all-c hello-link finalize clean

all: main.o all-c hello-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC) -I $(LIBGWS) -o main.o

all-c:

	cp $(LIBCOBJ)/crt0.o   .
	cp $(LIBCOBJ)/stubs.o  .

	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o .
	cp $(LIBCOBJ)/fcntl.o .
	cp $(LIBCOBJ)/stdlib.o .
	cp $(LIBCOBJ)/string.o .
	cp $(LIBCOBJ)/unistd.o  .

	cp $(LIBCOBJ)/termios.o  .
	cp $(LIBCOBJ)/ioctl.o  .
	cp $(LIBCOBJ)/socket.o  .


	cp $(LIBGWSOBJ)/connect.o .
	cp $(LIBGWSOBJ)/events.o .
	cp $(LIBGWSOBJ)/gws.o .
	cp $(LIBGWSOBJ)/rw.o .
	
	
hello-link:
	ld -m elf_i386 -T ../link.ld -o S2.BIN $(myObjects)    



finalize:
	cp S2.BIN  ../bin

clean:
	-rm *.o
	-rm S2.BIN 
	
	
