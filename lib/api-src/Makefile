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
	-fno-stack-protector \
	-s
	
#	-fleading-underscore \
#	-fno-stack-protector \
#	-s

make-all:
	gcc -c src/api.c -I include/ $(CFLAGS) -o api.o
	
	mv api.o ../api/
	
	

	
	
	
		
	
	