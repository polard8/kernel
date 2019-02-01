#todo


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



libc-all:

#:Compiling   
#	echo { Compiling C library for 32bit User Mode ...
	
	gcc -c stdio.c   -I ../../include/libc/ $(CFLAGS) -o stdio.o
	gcc -c stdlib.c  -I ../../include/libc/ $(CFLAGS) -o stdlib.o
	gcc -c string.c  -I ../../include/libc/ $(CFLAGS) -o string.o
	gcc -c ctype.c   -I ../../include/libc/ $(CFLAGS) -o ctype.o
	gcc -c time.c    -I ../../include/libc/ $(CFLAGS) -o time.o

	
#	echo { Compiling extra files ...

	gcc -c conio.c -I ../../include/libc/ $(CFLAGS) -o conio.o
	
#:Moving
#    echo { Moving objects ...
	
	mv stdio.o  ..
	mv stdlib.o .. 
	mv string.o .. 
	mv ctype.o  .. 
	mv time.o   .. 

#    rem extras ...	

	mv conio.o  ..
	
	
	
	
	
	
