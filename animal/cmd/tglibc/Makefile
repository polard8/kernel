# app for gde

#history:
#2019 - Created by Fred Nora.


#__stack_chk_fail_local
#se aparecer esse erro tem que incluir a flag -fno-stack-protector

VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = cat

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
	
#salvando original	
#LIBC    = ../../lib/gdelibs/libc01/include/
#LIBCOBJ = ../../lib/gdelibs/libc01/obj
#API01   = ../../lib/gdelibs/api01/include/
#APIOBJ  = ../../lib/gdelibs/api01/obj

LIBC    = ../../lib2/glibc01/include/
LIBCOBJ = ../../lib2/glibc01/obj

#api do gramado.
#API01   = ../../lib/gdelibs/api01/include/
#APIOBJ  = ../../lib/gdelibs/api01/obj


	##
	## Objects
	##

#myObjects = main.o \
#ctype.o \
#stdio.o \
#stdlib.o \
#string.o \
#time.o \
#api.o \
#unistd.o  

myObjects = main.o \
stubs.o \
putch.o \
puts.o \
doprintf.o \
strlen.o \
printf.o \
sprintf.o  




#myObjects = main.o   





.PHONY: all all-c glibct1-link finalize clean

all: main.o all-c glibct1-link finalize clean
	@echo "Ok?"

main.o:
	gcc  -c  main.c  $(CFLAGS) -I $(LIBC)  -o main.o

all-c:
	
#	cp $(APIOBJ)/api.o      .
	
#	cp $(LIBCOBJ)/ctype.o   .
#	cp $(LIBCOBJ)/stdio.o .
#	cp $(LIBCOBJ)/stdlib.o .
#	cp $(LIBCOBJ)/string.o .
#	cp $(LIBCOBJ)/time.o    .
#	cp $(LIBCOBJ)/unistd.o  .

	cp $(LIBCOBJ)/puts.o  .
	cp $(LIBCOBJ)/putch.o  .
	cp $(LIBCOBJ)/stubs.o  .
	cp $(LIBCOBJ)/doprintf.o  .	
	cp $(LIBCOBJ)/strlen.o  .		
	cp $(LIBCOBJ)/printf.o  .	
	cp $(LIBCOBJ)/sprintf.o  .	
	
glibct1-link:
	ld -m elf_i386 -T link.ld -o TGLIBC.BIN $(myObjects) -Map map.s

finalize:
	cp TGLIBC.BIN  ../../bin

clean:
	-rm *.o
	-rm TGLIBC.BIN 
	
	
