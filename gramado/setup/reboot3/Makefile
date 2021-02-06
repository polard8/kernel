# reboot2
# A small reboot gui application
#history:
#2019 - Created by Fred Nora.

VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = reboot2

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


# libs

LIBC    = ../../../landlib/rtl/include/
LIBCOBJ = ../../../landlib/rtl/obj
API     = ../../../landlib/libcore/include/
APIOBJ  = ../../../landlib/libcore/obj


# Objects

myObjects = crt0.o main.o \
ctype.o stdlib.o stdio.o string.o unistd.o \
api.o \
termios.o ioctl.o fcntl.o rtl.o    



.PHONY: all all-c app-link finalize clean

all: main.o all-c app-link finalize clean
	@echo "Ok?"

main.o:

	gcc -c  main.c  $(CFLAGS) -I $(LIBC) -I $(API) -o main.o


	
all-c:

	cp $(LIBCOBJ)/crt0.o   .
	
	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o   .
	cp $(LIBCOBJ)/stdlib.o  .
	cp $(LIBCOBJ)/string.o  .
	cp $(LIBCOBJ)/time.o    .
	cp $(LIBCOBJ)/unistd.o  .

	cp $(LIBCOBJ)/termios.o  .
	cp $(LIBCOBJ)/ioctl.o  .
	
	cp $(LIBCOBJ)/rtl.o   .
	cp $(LIBCOBJ)/fcntl.o   .
	
	cp $(APIOBJ)/api.o      .


app-link:
	ld -m elf_i386 -T ../link.ld -o REBOOT3.BIN  $(myObjects)    

finalize:
	cp REBOOT3.BIN  ../bin

clean:
	-rm *.o
	-rm REBOOT3.BIN 
	
