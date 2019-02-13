
#
# Compiling Gramado 0.13 Boot Loader 
# BSD License 
#
# 2018 - Created by Fred Nora.
#      - Adapted from Matheus Castello's script.
#      - Ported from build.bat.
#

VERSION = 0
PATCHLEVEL = 3
SUBLEVEL = 0
EXTRAVERSION = 
NAME = Style


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

myObjects = head.o \
main.o \
loader.o \
init.o \
ports.o \
x86.o \
stdio.o \
stdlib.o \
string.o \
keyboard.o \
pci.o \
hdd.o \
ide.o \
timer.o \
pages.o \
heap.o \
procedure.o \
fs.o \
shell.o \
services.o \
abort.o \
faults.o  


all-bl: bl-x86 link-x86 finalize clean

bl-x86:
	gcc -c src/main.c -I include/ $(CFLAGS) -o main.o 
	
    #echo -{ ...
    #echo -{ Boot Loader - (BL.BIN)

    #rem echo -{ ...
    #echo -{ Loader	
	gcc -c src/loader/loader.c -I include/ $(CFLAGS) -o loader.o	
	
    #rem echo -{ ...
    #echo -{ Core
    #rem head.s
	nasm -I src/core/head/x86/ src/core/head/x86/head.s -f elf -o head.o
	
	#rem c. 
	gcc -c src/core/faults.c  -I include/ $(CFLAGS) -o faults.o
	gcc -c src/core/pages.c   -I include/ $(CFLAGS) -o pages.o
	
	gcc -c src/core/heap.c   -I include/ $(CFLAGS) -o heap.o
	
    #rem echo -{ ...
    #echo -{ Libc
	gcc -c src/libc/stdio.c  -I include/ $(CFLAGS) -o stdio.o
	gcc -c src/libc/string.c -I include/ $(CFLAGS) -o string.o
	
	gcc -c src/libc/stdlib.c  -I include/ $(CFLAGS) -o stdlib.o
		
    #rem echo -{ ...
    #echo -{ Init
	gcc -c src/init/init.c -I include/ $(CFLAGS) -o init.o 		
	
    #rem echo -{ ...
    #echo -{ Sys
	gcc -c src/sys/procedure.c -I include/ $(CFLAGS) -o procedure.o	
	gcc -c src/sys/services.c  -I include/ $(CFLAGS) -o services.o		
	gcc -c src/sys/abort.c     -I include/ $(CFLAGS) -o abort.o		
	
    #rem echo -{ ...
    #echo -{ Arch
	gcc -c src/arch/x86/x86.c               -I include/ $(CFLAGS)  -o x86.o
	gcc -c src/arch/x86/ports.c             -I include/ $(CFLAGS)  -o ports.o 
	gcc -c src/arch/x86/drivers/pci.c       -I include/ $(CFLAGS)  -o pci.o		
	gcc -c src/arch/x86/drivers/keyboard.c  -I include/ $(CFLAGS)  -o keyboard.o
	gcc -c src/arch/x86/drivers/timer.c     -I include/ $(CFLAGS)  -o timer.o	
	
    #rem echo -{ ...
    #echo -{ Fs
	gcc -c src/fs/fs.c -I include/ $(CFLAGS) -o fs.o						

    #rem echo -{ ...
    #echo -{ Shell
	gcc -c src/shell/shell.c -I include/ $(CFLAGS) -o shell.o
	
	
	#
	# #test
	# tentando dar suporte ai controlador IDE.
	# 

	gcc -c src/arch/x86/drivers/ide/hdd.c  -I include/ $(CFLAGS)  -o hdd.o				
	gcc -c src/arch/x86/drivers/ide/ide.c  -I include/ $(CFLAGS)  -o ide.o				

	
	#backup
	#gcc -c src/arch/x86/drivers/hdd.c       -I include/ $(CFLAGS)  -o hdd.o		
	
	
link-x86:
	ld -m i386pe -T link.ld -o BL.BIN $(myObjects) -Map blmap.s
	
	
finalize:
	cp BL.BIN ../../../../bin/boot/
	
clean:
	find . -type f -name '*.o' -delete
	-rm BL.BIN
	
	