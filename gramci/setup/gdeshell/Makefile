# shell para o gde

#history:
#2019 - Created by Fred Nora and Luciano Gonçalez.

#todo:
#fazer um makefile pra compilar o shell
#obs: #bugbug tem que arrumas as coisas aqui.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = shell  

#todo:
#We need to simplify these flags

#CFLAGS = -m32 \
#	--std=gnu89 \
#	-nodefaultlibs \
#	-nostdinc \
#	-nostdlib \
#	-static \
#	-fgnu89-inline \
#	-ffreestanding \
#	-fno-builtin \
#	-fno-pie \
#	-no-pie \
#	-fno-stack-protector \
#	-s


CFLAGS = -m32 \
	-std=gnu89 \
	-nodefaultlibs \
	-nostdinc \
	-nostdlib \
	-static \
	-fgnu89-inline \
	-ffreestanding \
	-fno-builtin \
	-fno-pie \
	-fleading-underscore \
	-fno-stack-protector \
	-s \
	-Werror=strict-prototypes    
	



# depois vamos mudar  alib de lugar.
LIB     = ../../lib/libc03/include/
LIBOBJ  = ../../lib/libc03/obj
API     = ../../lib/libcore/include/
APIOBJ  = ../../lib/libcore/obj


	#
	# == Objects =================================
	#

myObjects = crt0.o main.o net.o shellui.o \
api.o \
ctype.o stdio.o stdlib.o string.o conio.o \
builtins.o \
tests.o \
unistd.o socket.o wait.o termios.o ioctl.o fcntl.o \
stubs.o    



.PHONY: all all-c shell-link finalize clean

all: main.o all-c shell-link finalize clean
	@echo "Ok?"


main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIB) -I $(API) -o main.o


all-c:

	gcc  -c  shellui.c   $(CFLAGS) -I $(LIB) -I $(API)  -o shellui.o
	gcc  -c  builtins.c  $(CFLAGS) -I $(LIB) -I $(API)  -o builtins.o
	gcc  -c  tests.c     $(CFLAGS) -I $(LIB) -I $(API)  -o tests.o
	gcc  -c  net.c       $(CFLAGS) -I $(LIB) -I $(API)  -o net.o


# Getting objects from libcore.
	cp $(LIBOBJ)/crt0.o .
	cp $(LIBOBJ)/stubs.o .
	cp $(LIBOBJ)/ctype.o   .
	cp $(LIBOBJ)/stdio.o .
	cp $(LIBOBJ)/stdlib.o .
	cp $(LIBOBJ)/string.o .
	cp $(LIBOBJ)/conio.o .
	cp $(LIBOBJ)/wait.o .
	cp $(LIBOBJ)/unistd.o .
	cp $(LIBOBJ)/socket.o .
	cp $(LIBOBJ)/termios.o .
	cp $(LIBOBJ)/ioctl.o .
	cp $(LIBOBJ)/fcntl.o .
	
# Getting api objects.
	cp $(APIOBJ)/api.o      .


shell-link:
	ld -m elf_i386 -T ../link.ld -o GDESHELL.BIN $(myObjects)    

	

finalize:
	cp GDESHELL.BIN ../bin

clean:
	-rm *.o
	-rm GDESHELL.BIN 
	
	
