
VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = 


CFLAGS = -m64 \
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




.PHONY: all all-c lin8x8-link finalize clean


all: main.o all-c lin8x8-link finalize clean
	@echo "LIN8X8 Ok?"

main.o:


all-c:

	gcc  -c  lin8x8.c   $(CFLAGS) -o lin8x8.o
# ...
	

lin8x8-link:
	ld -m elf_x86_64 -T ../link.ld -o LIN8X8.FON lin8x8.o -Map map.s

finalize:
	-cp LIN8X8.FON ../bin/

clean:
	-rm *.o
	-rm LIN8X8.FON 
	
	
	
	
	

