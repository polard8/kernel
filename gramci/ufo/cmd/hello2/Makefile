
#history:
#2019 - Created by Fred Nora.

#testando a libc3
#tentando colocar os caracteres em stdout ao invés d epintá-los na tela.


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = tascii

#todo:
#We need to simplify these flags

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
	


LIBC    = ../../../../rtl/include/
LIBCOBJ = ../../../../rtl/obj

#API01   = ../../lib/api01/include/
#APIOBJ  = ../../lib/api01/obj


	##
	## Objects
	##

myObjects = crt0.o main.o \
ctype.o stdio.o fcntl.o stdlib.o string.o time.o \
unistd.o termios.o ioctl.o rtl.o    



.PHONY: all all-c hello2-link finalize clean

all: main.o all-c hello2-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC) -o main.o


all-c:

	cp $(LIBCOBJ)/crt0.o  .
	cp $(LIBCOBJ)/rtl.o  .

	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o .
	cp $(LIBCOBJ)/fcntl.o .
	cp $(LIBCOBJ)/stdlib.o .
	cp $(LIBCOBJ)/string.o .
	cp $(LIBCOBJ)/time.o    .
	cp $(LIBCOBJ)/unistd.o  .
	
	cp $(LIBCOBJ)/termios.o  .
	cp $(LIBCOBJ)/ioctl.o  .


hello2-link:
	ld -m elf_i386 -T ../link.ld -o HELLO2.BIN $(myObjects)    


	

finalize:
	cp HELLO2.BIN ../bin

clean:
	-rm *.o
	-rm HELLO2.BIN 
	
	
