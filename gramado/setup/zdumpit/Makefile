# zdumpit
# history:
# 2019 - Created by Fred Nora.

VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = zdumpit

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
API01   = ../../../landlib/libcore/include/
APIOBJ  = ../../../landlib/libcore/obj


# Objects

myObjects = crt0.o ctype.o main.o dumpit.o\
stdio.o \
stdlib.o \
string.o \
time.o \
api.o \
unistd.o \
rtl.o    





.PHONY: all all-c tascii-link finalize clean

all: main.o all-c tascii-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC) -I $(API01) -o main.o
	gcc  -c  dumpit.c  $(CFLAGS) -I $(LIBC) -I $(API01) -o dumpit.o


all-c:
	cp $(LIBCOBJ)/crt0.o  .
	cp $(LIBCOBJ)/rtl.o  .

	cp $(APIOBJ)/api.o      .
	
	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o .
	cp $(LIBCOBJ)/stdlib.o .
	cp $(LIBCOBJ)/string.o .
	cp $(LIBCOBJ)/time.o    .
	cp $(LIBCOBJ)/unistd.o  .



tascii-link:
	ld -m elf_i386 -T ../link.ld -o DUMPIT.BIN $(myObjects)    


finalize:
#	cp DUMPIT.BIN ../../bin

clean:
	-rm *.o
	-rm DUMPIT.BIN 
	
	
