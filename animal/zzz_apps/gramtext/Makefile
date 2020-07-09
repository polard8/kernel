# gramtext - simple text editor

#history:
#2019 - Created by Fred Nora.



VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION = 
#NAME = gramtext

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
	
	
LIBC    = ../../lib/libcore/include/
LIBCOBJ = ../../lib/libcore/obj
API01   = ../../lib/api02/include/
APIOBJ  = ../../lib/api02/obj


	##
	## Objects
	##

myObjects = crt0.o main.o \
ctype.o \
stdlib.o \
stdio.o \
string.o \
unistd.o \
api.o \
status.o \
termios.o \
ioctl.o \
stubs.o  


.PHONY: all all-c gramtext-link finalize clean

all: main.o all-c gramtext-link finalize clean
	@echo "Ok?"

main.o:

#bugbug: por que estamos usando esse crt0,? usar o padrão.
	gcc  -c  crt0.c    $(CFLAGS) -I $(LIBC) -I $(API01) -o crt0.o
	gcc  -c  main.c    $(CFLAGS) -I $(LIBC) -I $(API01) -o main.o
	gcc  -c  status.c  $(CFLAGS) -I $(LIBC) -I $(API01) -o status.o
	
all-c:

	cp $(LIBCOBJ)/stubs.o   .
	

	
	cp $(LIBCOBJ)/ctype.o   .
	cp $(LIBCOBJ)/stdio.o   .
	cp $(LIBCOBJ)/stdlib.o  .	
	cp $(LIBCOBJ)/string.o  .
	cp $(LIBCOBJ)/time.o    .
	cp $(LIBCOBJ)/unistd.o  .

	cp $(LIBCOBJ)/termios.o  .
	cp $(LIBCOBJ)/ioctl.o  .
	
	cp $(APIOBJ)/api.o      .	


gramtext-link:
	ld -m elf_i386 -T ../link.ld -o GRAMTEXT.BIN $(myObjects)    
	
	

finalize:
	cp GRAMTEXT.BIN  ../../bin

clean:
	-rm *.o
	-rm GRAMTEXT.BIN 
	
	
