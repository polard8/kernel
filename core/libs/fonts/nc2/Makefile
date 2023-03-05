
VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = jackpot

#todo:
#We need to simplify these flags

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

#	-fleading-underscore \
#	-fno-stack-protector \
#	-s


#.PHONY: all all-c jackpot-link finalize clean
.PHONY: all all-c nc2-link finalize clean

#all: main.o all-c jackpot-link finalize clean
all: main.o all-c nc2-link finalize clean
	@echo "nc2 Ok?"

main.o:
#	gcc  -c  gde.c $(CFLAGS) -o gde.o

all-c:

	gcc  -c  nc2.c   $(CFLAGS) -o nc2.o
# ...
	

#create 'ar'
nc2-link:
	ld -m elf_x86_64 -T ../link.ld -o NC2.FON nc2.o -Map map.s

finalize:
	-cp NC2.FON ../bin/

clean:
	-rm *.o
	-rm NC2.FON 
	
	
	
	
	

