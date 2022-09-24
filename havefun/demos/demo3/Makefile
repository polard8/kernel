

# Make variables (CC, etc...)
AS	= as
LD	= ld
CC	= gcc
AR	= ar
MAKE	= make
NASM	= nasm
OBJCOPY	= objcopy
OBJDUMP	= objdump
LEX	= flex
YACC	= bison
PERL	= perl
PYTHON	= python
PYTHON2	= python2
PYTHON3	= python3
RUBY	= ruby


# usermode cross compiler flags.
user_ccflags = -Wall
#user_ccflags += -O3
user_ccflags += -Wundef
user_ccflags += -Wmissing-prototypes
user_ccflags += -Wno-uninitialized
user_ccflags += -Wno-format-security
user_ccflags += -Wno-trigraphs
user_ccflags += -Werror=strict-prototypes
user_ccflags += -Werror=implicit-function-declaration
user_ccflags += -Werror=return-type
user_ccflags += -std=gnu89
user_ccflags += -m64
user_ccflags += -s
user_ccflags += -static
user_ccflags += -fcommon
user_ccflags += -fgnu89-inline
user_ccflags += -finline-functions
user_ccflags += -fshort-wchar
user_ccflags += -ffreestanding
user_ccflags += -fleading-underscore
user_ccflags += -fstrict-overflow
user_ccflags += -nostdlib
user_ccflags += -nodefaultlibs
user_ccflags += -nostdinc
user_ccflags += -fno-builtin
user_ccflags += -fno-stack-protector
user_ccflags += -fno-strict-aliasing
user_ccflags += -fno-PIE
user_ccflags += -fno-pie
user_ccflags += -fno-omit-frame-pointer
user_ccflags += -fno-optimize-sibling-calls    
	

user_ldflags = -m elf_x86_64 -T ../../link.ld

#todo
#path longo. vamos mudar  as libs de lugar para gramado/libs.

LIBC     = ../../libs/rtl/include/
LIBCOBJ  = ../../libs/rtl/obj

LIBGD     = ../../libs/libgd/include/
LIBGDOBJ  = ../../libs/libgd/obj

ENG3_INCLUDES      = ../../eng3/include/ 
#WS_INCLUDES_LOCAL = .

#.PHONY: all
all:

	$(CC) -c demo3.c $(user_ccflags) \
-I $(LIBC) -I $(LIBGD) -I $(ENG3_INCLUDES) -I . \
-o demo3.o

	cp ../../eng3/eng3.o  .
	cp $(LIBCOBJ)/crt0.o .
#gws-link:
	$(LD) $(user_ldflags) -o DEMO3.BIN crt0.o demo3.o eng3.o
#finalize:
	cp DEMO3.BIN  ../../bin
	-rm *.o
	-rm DEMO3.BIN 
clean:
	-rm *.o
	-rm DEMO3.BIN 

