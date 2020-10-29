
#history:
#2019 - Created by Fred Nora.

# Testando a libc3
# Tentando colocar os caracteres em stdout ao invés de pintá-los na tela.


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = 

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
	


LIBC    = ../../../../ge/rtl/include/
LIBCOBJ = ../../../../ge/rtl/obj


	##
	## Objects
	##

myObjects = crt0.o main.o \
ctype.o \
stdio.o \
fcntl.o \
stdlib.o \
string.o \
time.o \
unistd.o \
termios.o \
ioctl.o \
rtl.o    




.PHONY: all all-c hello3-link finalize clean

all: main.o all-c hello3-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC)  -o main.o

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
	

hello3-link:
	ld -m elf_i386 -T ../link.ld -o HELLO3.BIN $(myObjects)    



finalize:
	cp HELLO3.BIN ../bin

clean:
	-rm *.o
	-rm HELLO3.BIN 
	
	
