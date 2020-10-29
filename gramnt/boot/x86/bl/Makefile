
#
# Compiling Gramado Boot Loader 1.0 
# BSD License 
#
# 2018 - Created by Fred Nora.
#      - Adapted from Matheus Castello's script.
#

VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION = 
NAME = Graload


# we do not need these flags. 

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


	## 
	## Objects 
	##

myObjects = head.o main.o \
loader.o \
init.o \
ports.o \
x86.o \
stdio.o \
stdlib.o \
string.o \
keyboard.o pci.o hdd.o ide.o timer.o \
pages.o \
heap.o \
procedure.o \
fs.o \
shell.o \
r_render.o \
abort.o \
faults.o  


all-bl: bl-x86 link-x86 finalize clean

bl-x86:

    # Head
	nasm  -I x86/  x86/head.s -f elf -o head.o

    # main
	gcc -c main.c -I include/ $(CFLAGS) -o main.o 

    # init
	gcc -c init.c -I include/ $(CFLAGS) -o init.o 

    # libc
	gcc -c stdio.c   -I include/ $(CFLAGS) -o stdio.o
	gcc -c string.c  -I include/ $(CFLAGS) -o string.o
	gcc -c stdlib.c  -I include/ $(CFLAGS) -o stdlib.o

	#x86
	gcc -c x86/faults.c  -I include/ $(CFLAGS)  -o faults.o
	gcc -c x86/x86.c     -I include/ $(CFLAGS)  -o x86.o
	gcc -c x86/ports.c   -I include/ $(CFLAGS)  -o ports.o 


	# mm
	gcc -c pages.c   -I include/ $(CFLAGS) -o pages.o	
	gcc -c heap.c    -I include/ $(CFLAGS) -o heap.o


    #Sys
	gcc -c procedure.c -I include/ $(CFLAGS) -o procedure.o
	gcc -c abort.c     -I include/ $(CFLAGS) -o abort.o


    #Shell
	gcc -c shell.c -I include/ $(CFLAGS) -o shell.o

    #fs
	gcc -c fs/fs.c     -I include/ $(CFLAGS) -o fs.o
	gcc -c fs/loader.c -I include/ $(CFLAGS) -o loader.o


	gcc -c render/r_render.c  -I include/ $(CFLAGS) -o r_render.o

    # dd
	gcc -c dd/pci.c       -I include/ $(CFLAGS)  -o pci.o
	gcc -c dd/keyboard.c  -I include/ $(CFLAGS)  -o keyboard.o
	gcc -c dd/timer.c     -I include/ $(CFLAGS)  -o timer.o
	gcc -c dd/hdd.c       -I include/ $(CFLAGS)  -o hdd.o
	gcc -c dd/ide.c       -I include/ $(CFLAGS)  -o ide.o


	
link-x86:
	ld -m i386pe -T link.ld -o BL.BIN $(myObjects)    


finalize:
	cp BL.BIN ../bin/


clean:
	find . -type f -name '*.o' -delete
	-rm BL.BIN
	
clean2:
	-rm BL.BIN
	
	
		
