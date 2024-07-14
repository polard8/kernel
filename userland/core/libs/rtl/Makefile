# rtl
# libc for Gramado 64bit ring3 part.
# 2019 - Created by Fred Nora.

VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION = 0
NAME = rtl

# Target operating system.

TARGETOS ?= gramado
#TARGETOS ?= linux

#STATIC_LIB = obj/lib/libc03.a
#SHARED_LIB = obj/lib/libc03.so

# Gramado!
ifeq ($(TARGETOS),gramado)

CFLAGS := \
	-Wall \
	-Wundef \
	-Wmissing-prototypes \
	-Wno-uninitialized \
	-Wno-format-security \
	-Wno-trigraphs \
	-Werror=strict-prototypes \
	-Werror=implicit-function-declaration \
	-Werror=implicit-int \
	-Werror=return-type \
	-std=gnu89 \
	-m64 \
	-s \
	-static \
	-fcommon \
	-fgnu89-inline \
	-finline-functions \
	-fshort-wchar \
	-ffreestanding \
	-fleading-underscore \
	-fstrict-overflow \
	-nostdlib \
	-nodefaultlibs \
	-nostdinc \
	-fno-builtin \
	-fno-stack-protector \
	-fno-strict-aliasing \
	-fno-PIE \
	-fno-pie \
	-fno-omit-frame-pointer \
	-fno-optimize-sibling-calls \
	-mno-red-zone \
	#-mno-mmx -mno-sse -mno-sse2   

endif

LIBS = -I . -I include/  


.PHONY: all libc-header libc-content libc-footer link install clean

all: libc-header libc-content libc-footer \
link install clean    

	@echo "Ok?"

libc-header:
# student
	gcc  -c  entrance/student/crt0.c  $(CFLAGS) $(LIBS) -o crt0.o
# visitor
	gcc -c entrance/visitor/rtl.c  $(CFLAGS) $(LIBS) -o rtl.o

libc-content:

	gcc  -c  ctype.c    $(CFLAGS)  $(LIBS) -o ctype.o
	gcc  -c  fcntl.c    $(CFLAGS)  $(LIBS) -o fcntl.o
	gcc  -c  mmap.c     $(CFLAGS)  $(LIBS) -o mmap.o
	gcc  -c  fscanf.c   $(CFLAGS)  $(LIBS) -o fscanf.o
	gcc  -c  ioctl.c    $(CFLAGS)  $(LIBS) -o ioctl.o
	gcc  -c  signal.c   $(CFLAGS)  $(LIBS) -o signal.o
	gcc  -c  socket.c   $(CFLAGS)  $(LIBS) -o socket.o
	gcc  -c  stdio.c    $(CFLAGS)  $(LIBS) -o stdio.o
	gcc  -c  stdlib.c   $(CFLAGS)  $(LIBS) -o stdlib.o
	gcc  -c  termios.c  $(CFLAGS)  $(LIBS) -o termios.o
	gcc  -c  unistd.c   $(CFLAGS)  $(LIBS) -o unistd.o
	gcc  -c  conio.c    $(CFLAGS)  $(LIBS) -o conio.o
	gcc  -c  string.c   $(CFLAGS)  $(LIBS) -o string.o
	gcc  -c  time.c     $(CFLAGS)  $(LIBS) -o time.o
	gcc  -c  wait.c     $(CFLAGS)  $(LIBS) -o wait.o
	gcc  -c  math.c      $(CFLAGS)  $(LIBS) -o math.o
	gcc  -c  strtoul.c   $(CFLAGS)  $(LIBS) -o strtoul.o
	gcc  -c  strtol.c    $(CFLAGS)  $(LIBS) -o strtol.o
	gcc  -c  err.c       $(CFLAGS)  $(LIBS) -o err.o
	gcc  -c  locale.c    $(CFLAGS)  $(LIBS) -o locale.o
	gcc  -c  assert.c    $(CFLAGS)  $(LIBS) -o assert.o
	gcc  -c  pty.c       $(CFLAGS)  $(LIBS) -o pty.o
	gcc  -c  tty.c       $(CFLAGS)  $(LIBS) -o tty.o
	gcc  -c  _split.c    $(CFLAGS)  $(LIBS) -o _split.o
	gcc  -c  linkaddr.c  $(CFLAGS)  $(LIBS) -o linkaddr.o

	gcc  -c  sched.c  $(CFLAGS)  $(LIBS) -o sched.o

	gcc  -c  inet.c  $(CFLAGS)  $(LIBS) -o inet.o

# ...


#tests 
#	gcc  -c  tests/test1.c   $(CFLAGS) -I. -I include/ -o test1.o
 
# test
# entry point para a biblioteca compartilhada. .so

	#gcc  -c  socrt0.c -fno-stack-protector -fpic -mno-red-zone -DEFI_FUNCTION_WRAPPER  $(CFLAGS)  $(LIBS) -o socrt0.o	
	#gcc  -c  somain.c -fno-stack-protector -fpic -mno-red-zone -DEFI_FUNCTION_WRAPPER  $(CFLAGS)  $(LIBS) -o somain.o	

#ifeq ($(TARGETOS),gramado)
#	gcc  -c  sysdeps/gramado/gramado.c  $(CFLAGS)  $(LIBS) -o gramado.o
#endif

#ifeq ($(TARGETOS),linux)
#	gcc  -c  sysdeps/gramado/linux.c  $(CFLAGS)  $(LIBS) -o linux.o
#endif

libc-footer:
# Nothing for now!

# create 'ar'
# #todo: 
# We need a new ld file.
link:
#	ar rc LIBC03.A $(OBJECTS)
#	ld -m elf_i386 socrt0.o somain.o -nostdlib -T elf_ia32_efi.lds -shared -znocombreloc -Bsymbolic -L . -l:LIBC03.A -o LIBC03.SO -Map map.s
	#$(LD) -r -o archive_rtl.o 
install:
	-mkdir         obj/
	-cp *.o        obj/
	#-cp LIBC03.A  obj/
	#-cp LIBC03.SO obj/
clean:
	-rm *.o
	-rm *.A
	-rm *.SO
clean2:
	-rm obj/*.o


