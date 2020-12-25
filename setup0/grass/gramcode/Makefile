# gramcode - text editor for gramado os.

#history:
#2019 - Created by Fred Nora.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = gramcode


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




LIBC    = ../../../ge/rtl/include/
LIBCOBJ = ../../../ge/rtl/obj
API     = ../../../ge/libcore/include/
APIOBJ  = ../../../ge/libcore/obj


	##
	## Objects
	##

myObjects = crt0.o main.o \
ctype.o stdlib.o stdio.o string.o unistd.o \
api.o \
sbar.o \
termios.o ioctl.o fcntl.o \
rtl.o    



.PHONY: all all-c gramcode-link finalize clean

all: main.o all-c gramcode-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC) -I $(API) -o main.o
	gcc  -c  sbar.c  $(CFLAGS) -I $(LIBC) -I $(API) -o sbar.o


all-c:

	cp $(LIBCOBJ)/crt0.o    .
	cp $(LIBCOBJ)/rtl.o     .
	
	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o   .
	cp $(LIBCOBJ)/stdlib.o  .
	cp $(LIBCOBJ)/string.o  .
	cp $(LIBCOBJ)/time.o    .
	cp $(LIBCOBJ)/unistd.o  .
	
	cp $(LIBCOBJ)/termios.o  .
	cp $(LIBCOBJ)/ioctl.o  .
	cp $(LIBCOBJ)/fcntl.o  .
	cp $(APIOBJ)/api.o      .


gramcode-link:
	ld -m elf_i386 -T ../link.ld -o GRAMCODE.BIN $(myObjects)    
	
	


finalize:
	cp GRAMCODE.BIN  ../bin

clean:
	-rm *.o
	-rm GRAMCODE.BIN 
	
	
