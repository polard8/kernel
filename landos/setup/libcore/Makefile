#api01


VERSION = 0
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION =
#NAME = jackpot

#todo:
#We need to simplify these flags

#CFLAGS = -m32 \
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
	


#.PHONY: all all-c jackpot-link finalize clean
.PHONY: all all-c api01-link finalize clean

#all: main.o all-c jackpot-link finalize clean
all: main.o all-c api01-link finalize clean
	@echo "Ok?"

main.o:
# nothing

all-c:

	gcc  -c  api.c   $(CFLAGS) -I include/ -I ../../../landlib/rtl/include/ -o api.o


#create 'ar'
api01-link:
# nothing


finalize:
	-mkdir obj/
	-cp *.o obj/
	
clean:
	-rm *.o
	
	

