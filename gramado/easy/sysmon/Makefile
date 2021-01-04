# sysmon - system monitor for gde.

#history:
#2019 - Created by Fred Nora.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = sysmon


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



LIBC    = ../../../land/medium/rtl/include/
LIBCOBJ = ../../../land/medium/rtl/obj
API     = ../../../land/medium/libcore/include/
APIOBJ  = ../../../land/medium/libcore/obj

	##
	## Objects
	##

myObjects = crt0.o main.o \
ctype.o stdlib.o stdio.o string.o unistd.o \
api.o \
termios.o ioctl.o fcntl.o rtl.o    



.PHONY: all all-c sysmon-link finalize clean

all: main.o all-c sysmon-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c     $(CFLAGS) -I $(LIBC) -I $(API) -o main.o


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

	cp $(LIBCOBJ)/fcntl.o  .
	
	cp $(LIBCOBJ)/rtl.o   .
	cp $(APIOBJ)/api.o      .



sysmon-link:
	ld -m elf_i386 -T ../link.ld -o SYSMON.BIN $(myObjects)    
	
	


finalize:
	cp SYSMON.BIN  ../bin

clean:
	-rm *.o
	-rm SYSMON.BIN 
	
	
