
INCLUDE = ../../../include
# Internal files
# Used to build the kernel.
KERNEL_INCLUDE := -I $(INCLUDE)   

STARTUP_INCLUDE := -I startup/  

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

all:

# ----------------------------------------------
# startup
	$(NASM) startup/head_64.asm \
	$(KERNEL_INCLUDE) \
	$(STARTUP_INCLUDE) \
	-f elf64 -o head_64.o    

	cp head_64.o ../../../

	rm *.o
	











