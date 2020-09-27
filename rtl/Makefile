
# libc03
# libc version 0.3 for GDE project
# 2019 - Created by Fred Nora.


VERSION = 0
PATCHLEVEL = 3
SUBLEVEL = 0
EXTRAVERSION = -rc0
NAME = Gramado LibC


# Target operating system.

TARGETOS ?= gramado
#TARGETOS ?= linux


#STATIC_LIB = obj/lib/libc03.a
#SHARED_LIB = obj/lib/libc03.so



# Gramado!
ifeq ($(TARGETOS),gramado)

#	CFLAGS = -m32 \
#	--std=gnu89 \
#	-nodefaultlibs \
#	-nostdinc \
#	-nostdlib \
#	-static \
#	-fgnu89-inline \
#	-ffreestanding \
#	-fno-builtin \
#	-fno-pie \
#	-no-pie \
#	-fno-stack-protector \
#	-s


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
	


	
endif




.PHONY: all all-c libc-link finalize clean

all: all-c libc-link finalize clean
	@echo "Ok?"

all-c:

#/crts
	gcc  -c  crts/crt0.c    $(CFLAGS) -I. -I include/ -o crt0.o
	
#/ctype
	gcc  -c  ctype/ctype.c    $(CFLAGS) -I. -I include/ -o ctype.o
	
#/fcntl
	gcc  -c  fcntl/fcntl.c  $(CFLAGS) -I. -I include/ -o fcntl.o

#/fscanf
	gcc  -c  mmap/mmap.c  $(CFLAGS) -I. -I include/ -o mmap.o

#/mmap
	gcc  -c  fscanf/fscanf.c  $(CFLAGS) -I. -I include/ -o fscanf.o

#/ioctl
	gcc  -c  ioctl/ioctl.c  $(CFLAGS) -I. -I include/ -o ioctl.o

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
	
#/unistd
	gcc  -c  termios/termios.c  $(CFLAGS) -I. -I include/ -o termios.o

# outros	
	gcc  -c  conio.c   $(CFLAGS) -I. -I include/ -o conio.o
	gcc  -c  string.c  $(CFLAGS) -I. -I include/ -o string.o
	gcc  -c  time.c    $(CFLAGS) -I. -I include/ -o time.o
	gcc  -c  wait.c    $(CFLAGS) -I. -I include/ -o wait.o
	gcc  -c  math.c    $(CFLAGS) -I. -I include/ -o math.o
	
	gcc  -c  strtoul.c  $(CFLAGS) -I. -I include/ -o strtoul.o
	gcc  -c  strtol.c   $(CFLAGS) -I. -I include/ -o strtol.o
	
	gcc  -c  err.c    $(CFLAGS) -I. -I include/ -o err.o
	gcc  -c  locale.c    $(CFLAGS) -I. -I include/ -o locale.o
	
	gcc  -c  assert.c    $(CFLAGS) -I. -I include/ -o assert.o
	
	gcc  -c  pty.c    $(CFLAGS) -I. -I include/ -o pty.o
	gcc  -c  tty.c    $(CFLAGS) -I. -I include/ -o tty.o

	gcc  -c  _split.c    $(CFLAGS) -I. -I include/ -o _split.o
	
	gcc  -c  linkaddr.c    $(CFLAGS) -I. -I include/ -o linkaddr.o
	
#...	

#tests 
#	gcc  -c  tests/test1.c   $(CFLAGS) -I. -I include/ -o test1.o
 
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

	

# create 'ar'
# #todo: 
# We need a new ld file.
libc-link:

#	ar rc LIBC03.A $(OBJECTS)
#	ld -m elf_i386 socrt0.o somain.o -nostdlib -T elf_ia32_efi.lds -shared -znocombreloc -Bsymbolic -L . -l:LIBC03.A -o LIBC03.SO -Map map.s


finalize:
	-mkdir obj/
	-cp *.o obj/
	-cp LIBC03.A obj/
	-cp LIBC03.SO obj/


clean:
	-rm *.o
	-rm *.A
	-rm *.SO
	

