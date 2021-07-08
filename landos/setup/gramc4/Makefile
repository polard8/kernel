#reboot command for gde
#history:
#2019 - Created by Fred Nora.
#todo:
#fazer um makefile pra compilar o shell
#obs: #bugbug tem que arrumas as coisas aqui.

VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = reboot

#todo:
#We need to simplify these flags

CFLAGS = -m64 \
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
	


LIBC    = ../../../landlib/rtl/include/
LIBCOBJ = ../../../landlib/rtl/obj
API02   = ../libcore/include/
APIOBJ  = ../libcore/obj


	##
	## Objects
	##

myObjects = crt0.o gramc4.o \
ctype.o stdio.o stdlib.o string.o time.o \
api.o \
unistd.o strtol.o strtoul.o fscanf.o fcntl.o termios.o \
ioctl.o wait.o rtl.o    


.PHONY: all all-c jackpot-link finalize clean

all: c4.o all-c jackpot-link finalize clean
	@echo "Ok?"

c4.o:
	gcc  -c  gramc4.c  -Wall  $(CFLAGS) -I $(LIBC) -I $(API02) -o gramc4.o


all-c:


	cp $(LIBCOBJ)/crt0.o   .
	cp $(LIBCOBJ)/rtl.o  .
	
	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o .
	cp $(LIBCOBJ)/stdlib.o .
	cp $(LIBCOBJ)/string.o .
	cp $(LIBCOBJ)/time.o    .
	cp $(LIBCOBJ)/unistd.o  .

#	cp $(LIBCOBJ)/math.o  .
	cp $(LIBCOBJ)/fscanf.o  .

	cp $(LIBCOBJ)/strtol.o  .
	cp $(LIBCOBJ)/strtoul.o  .
	
	cp $(LIBCOBJ)/fcntl.o  .
	cp $(LIBCOBJ)/termios.o  .
	cp $(LIBCOBJ)/ioctl.o  .
	
	cp $(LIBCOBJ)/wait.o .

	cp $(APIOBJ)/api.o      .



jackpot-link:
	ld -m elf_i386 -T ../link.ld -o GRAMC4.BIN $(myObjects)    
	

finalize:
	cp GRAMC4.BIN ../bin 

clean:
	-rm *.o
	-rm GRAMC4.BIN 
	
	
