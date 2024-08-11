# Compiling Gramado Boot Loader
# BLGRAM.BIN
# 2018 - Created by Fred Nora.
#      - Adapted from Matheus Castello's script.
# todo:
# The goal here is to create a 64bit boot loader.
# The will loader a 64bit kernel image.

linkTarget = BLGRAM.BIN 

VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION = 
NAME = GramadoBootLoader

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

# We do not need these flags. 
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
	-fleading-underscore \
	-fno-stack-protector \
	-s


#myIncludes = -I ./ -I include/  
myIncludes = -I ./ 

# Objects 
myObjects = head.o main.o globals.o \
loader.o init.o ports.o x86.o \
stdio.o stdlib.o string.o \
keyboard.o pci.o hdd.o ide.o storage.o timer.o \
pages.o \
heap.o \
proced.o \
fs.o \
shell.o \
r_render.o \
abort.o \
faults.o    


all-bl: bl-x86 link-x86 finalize clean

bl-x86:

# Head
	$(NASM)  -I x86/  x86/head.s -f elf -o head.o
# main
	$(CC) -c main.c    $(myIncludes) $(CFLAGS) -o main.o 
	$(CC) -c globals.c $(myIncludes) $(CFLAGS) -o globals.o 
# init
	$(CC) -c init.c $(myIncludes) $(CFLAGS) -o init.o 
# libc
	$(CC) -c libs/stdio.c  $(myIncludes) $(CFLAGS) -o stdio.o
	$(CC) -c libs/string.c $(myIncludes) $(CFLAGS) -o string.o
	$(CC) -c libs/stdlib.c $(myIncludes) $(CFLAGS) -o stdlib.o
#x86
	$(CC) -c x86/faults.c $(myIncludes) $(CFLAGS)  -o faults.o
	$(CC) -c x86/x86.c    $(myIncludes) $(CFLAGS)  -o x86.o
	$(CC) -c x86/ports.c  $(myIncludes) $(CFLAGS)  -o ports.o 
# mm
	$(CC) -c mm/pages.c $(myIncludes) $(CFLAGS) -o pages.o
	$(CC) -c mm/heap.c  $(myIncludes) $(CFLAGS) -o heap.o
#Sys
	$(CC) -c proced.c $(myIncludes) $(CFLAGS) -o proced.o
	$(CC) -c abort.c  $(myIncludes) $(CFLAGS) -o abort.o
#Shell
	$(CC) -c shell.c $(myIncludes) $(CFLAGS) -o shell.o
#fs
	$(CC) -c fs/fs.c     $(myIncludes) $(CFLAGS) -o fs.o
	$(CC) -c fs/loader.c $(myIncludes) $(CFLAGS) -o loader.o

	$(CC) -c render/r_render.c $(myIncludes) $(CFLAGS) -o r_render.o

# dd

	$(CC) -c dd/pci.c $(myIncludes) $(CFLAGS)  -o pci.o
	$(CC) -c dd/keyboard.c $(myIncludes) $(CFLAGS)  -o keyboard.o
	$(CC) -c dd/timer.c    $(myIncludes) $(CFLAGS)  -o timer.o
	$(CC) -c dd/hdd.c      $(myIncludes) $(CFLAGS)  -o hdd.o
	$(CC) -c dd/ide.c      $(myIncludes) $(CFLAGS)  -o ide.o
	$(CC) -c dd/storage.c  $(myIncludes) $(CFLAGS)  -o storage.o

#todo:
# Change to 32bit ELF. Maybe.
link-x86:
	$(LD) -m i386pe -T x86/link.ld -o $(linkTarget) $(myObjects)    
finalize:
	cp $(linkTarget) ../bin/
clean:
	find . -type f -name '*.o' -delete
	-rm $(linkTarget)
clean2:
	-rm $(linkTarget)
	
