
# libc02
# libc version 0.2 for GDE project
# 2019 - Created by Fred Nora.


VERSION = 0
PATCHLEVEL = 2
SUBLEVEL = 0
EXTRAVERSION = -rc0
NAME = Gramado LibC


# Target operating system.

TARGETOS ?= gramado
#TARGETOS ?= linux


#STATIC_LIB = obj/lib/libc02.a
#SHARED_LIB = obj/lib/libc02.so


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

#	-fleading-underscore \
#	-fno-stack-protector \
#	-s


#.PHONY: all all-c jackpot-link finalize clean
.PHONY: all all-c libc-link finalize clean

#all: main.o all-c jackpot-link finalize clean
all: main.o all-c libc-link finalize clean
	@echo "Ok?"

main.o:
#	nothing...

all-c:

#/ctype
	gcc  -c  ctype/ctype.c    $(CFLAGS) -I. -I include/ -o ctype.o
	
#/fscanf
	gcc  -c  fscanf/fscanf.c  $(CFLAGS) -I. -I include/ -o fscanf.o

#/signal
	gcc  -c  signal/signal.c  $(CFLAGS) -I. -I include/ -o signal.o
	
#/socket
	gcc  -c  socket/socket.c  $(CFLAGS) -I. -I include/ -o socket.o

#/stdio 
	gcc  -c  stdio/stdio.c    $(CFLAGS) -I. -I include/ -o stdio.o	
	
#/stdlib
	gcc  -c  stdlib/stdlib.c  $(CFLAGS) -I. -I include/ -o stdlib.o	
	
#/stubs	
	gcc  -c  stubs/stubs.c    $(CFLAGS) -I. -I include/ -o stubs.o		
	
#/unistd
	gcc  -c  unistd/unistd.c  $(CFLAGS) -I. -I include/ -o unistd.o	
	
	
	
# outros	
	gcc  -c  conio.c   $(CFLAGS) -I. -I include/ -o conio.o
	gcc  -c  string.c  $(CFLAGS) -I. -I include/ -o string.o	
	gcc  -c  time.c    $(CFLAGS) -I. -I include/ -o time.o	
	gcc  -c  wait.c    $(CFLAGS) -I. -I include/ -o wait.o		
	gcc  -c  math.c    $(CFLAGS) -I. -I include/ -o math.o			
#...	

 
# test
# entry point para a biblioteca compartilhada. .so

	gcc  -c  socrt0.c -fno-stack-protector -fpic -mno-red-zone  -DEFI_FUNCTION_WRAPPER  $(CFLAGS) -I. -I include/ -o socrt0.o	
	gcc  -c  somain.c -fno-stack-protector -fpic -mno-red-zone  -DEFI_FUNCTION_WRAPPER  $(CFLAGS) -I. -I include/ -o somain.o	

	
#ifeq ($(TARGETOS),gramado)
#	gcc  -c  sysdeps/gramado/gramado.c  $(CFLAGS) -I. -I include/ -o gramado.o			
#endif

#ifeq ($(TARGETOS),linux)
#	gcc  -c  sysdeps/gramado/linux.c  $(CFLAGS) -I. -I include/ -o linux.o	
#endif	

	

#create 'ar'
libc-link:
	ar rc LIBC02.A $(OBJECTS)
	ld -m elf_i386 socrt0.o somain.o -nostdlib -T elf_ia32_efi.lds -shared -znocombreloc -Bsymbolic -L . -l:LIBC02.A -o LIBC02.SO -Map map.s

finalize:
#	cp JACKPOT.BIN  ../../../bin
	-mkdir obj/
	-cp *.o obj/
	-cp LIBC02.A obj/
	-cp LIBC02.SO obj/
	
	
	
clean:
	-rm *.o
	-rm *.A
	-rm *.SO
	
	

	
	

