.SUFFIXES: .asm

# defines
MAKEFILE=Makefile
MAKEDEP=$(MAKEFILE)
INCDIR	=./include
NASM	=nasm -f elf -i$(INCDIR)/

# __stack_chk_fail_local
# Se aparecer esse erro tem que incluir a flag -fno-stack-protector
# talvez o stack protector foi incluido no gcc depois que essa versão da glibc foi criada.

#CC	=gcc -m32 -g -Wall -W -O2 -nostdinc -fno-builtin -I$(INCDIR)
CC	=gcc -m32 -g -Wall -W -O2 -nostdinc -fno-builtin -fno-stack-protector -I$(INCDIR)

STDIO	=stdio/doprintf.o stdio/delay.o stdio/printf.o stdio/sprintf.o stdio/puts.o stdio/putch.o stdio/cls.o stdio/getch.o stdio/getkey.o stdio/gotoxy.o stdio/setcolor.o stdio/beep.o stdio/open.o stdio/close.o stdio/read.o 
STRING	=string/memsetw.o string/memcpy.o string/strlen.o string/strcpy.o string/strncpy.o string/strcat.o string/memset.o string/strcmp.o string/strdup.o
X86	=x86/inportb.o x86/outportb.o x86/disable.o x86/enable.o x86/dma.o
STDLIB  =stdlib/memory.o stdlib/exit.o stdlib/schedule.o stdlib/strtol.o stdlib/atoi.o stdlib/itoa.o
UNISTD  =unistd/sleep.o unistd/fcntl.o
SOCKET  =socket/connect.o socket/socket.o socket/send.o socket/gethostbyname.o socket/htons.o socket/recv.o socket/bind.o socket/listen.o socket/accept.o
SIGNAL  =signal/signal.o
VFS     =vfs/mount.o

#Incluido por Fred Nora.
STUBS   =stubs/stubs.o    



OBJS	=$(STDIO) $(STRING) $(X86) $(STDLIB) $(UNISTD) $(SOCKET) $(SIGNAL) $(VFS) $(STUBS)

# targets
all: libc.a

clean:
	rm -f libc.a $(OBJS)
	rm obj/*.o

# implicit rules
.asm.o:
	$(NASM) -o$@ $<

.c.o:
	$(CC) -c -o$@ $<

# dependencies
stdio/doprintf.o:	stdio/doprintf.c	$(MAKEDEP)
stdio/printf.o:		stdio/printf.c		$(MAKEDEP)
stdio/sprintf.o:	stdio/sprintf.c		$(MAKEDEP)
stdio/puts.o:		stdio/puts.c		$(MAKEDEP)
stdio/putch.o:		stdio/putch.c		$(MAKEDEP)
stdio/delay.o:		stdio/delay.c		$(MAKEDEP)
stdio/cls.o:		stdio/cls.c			$(MAKEDEP)
stdio/getch.o:		stdio/getch.c		$(MAKEDEP)
stdio/getkey.o:		stdio/getkey.c		$(MAKEDEP)
stdio/gotoxy.o:		stdio/gotoxy.c		$(MAKEDEP)
stdio/setcolor.o:	stdio/setcolor.c	$(MAKEDEP)
stdio/beep.o:		stdio/beep.c		$(MAKEDEP)
stdio/open.o:		stdio/open.c		$(MAKEDEP)
stdio/close.o:		stdio/close.c		$(MAKEDEP)
stdio/read.o:		stdio/read.c		$(MAKEDEP)
stdlib/memory.o:	stdlib/memory.c		$(MAKEDEP)
stdlib/exit.o:		stdlib/exit.c		$(MAKEDEP)
stdlib/schedule.o:	stdlib/schedule.c	$(MAKEDEP)
stdlib/strtol.o:	stdlib/strtol.c		$(MAKEDEP)
stdlib/atoi.o:		stdlib/atoi.c		$(MAKEDEP)
stdlib/itoa.o:		stdlib/itoa.c		$(MAKEDEP)
unistd/sleep.o:		unistd/sleep.c		$(MAKEDEP)
unistd/fcntl.o:		unistd/fcntl.c		$(MAKEDEP)
string/memsetw.o:	string/memsetw.c	$(MAKEDEP)
string/memcpy.o:	string/memcpy.c		$(MAKEDEP)
string/strlen.o:	string/strlen.c		$(MAKEDEP)
string/strcpy.o:	string/strcpy.c		$(MAKEDEP)
string/strncpy.o:	string/strncpy.c	$(MAKEDEP)
string/strcat.o:	string/strcat.c		$(MAKEDEP)
string/strcmp.o:	string/strcmp.c		$(MAKEDEP)
string/strdup.o:	string/strdup.c		$(MAKEDEP)
string/memset.o:	string/memset.c		$(MAKEDEP)
x86/dma.o:			x86/dma.c			$(MAKEDEP)
x86/inportb.o:		x86/inportb.c		$(MAKEDEP)
x86/outportb.o:		x86/outportb.c		$(MAKEDEP)
x86/disable.o:		x86/disable.c		$(MAKEDEP)
x86/enable.o:		x86/enable.c		$(MAKEDEP)
socket/connect.o:	socket/connect.c	$(MAKEDEP)
socket/socket.o:	socket/socket.c		$(MAKEDEP)
socket/send.o:		socket/send.c		$(MAKEDEP)
socket/gethostbyname.o:	socket/gethostbyname.c	$(MAKEDEP)
socket/htons.o:		socket/htons.c		$(MAKEDEP)
socket/recv.o:		socket/recv.c		$(MAKEDEP)
socket/bind.o:		socket/bind.c		$(MAKEDEP)
socket/listen.o:	socket/listen.c		$(MAKEDEP)
socket/accept.o:	socket/accept.c		$(MAKEDEP)
signal/signal.o:	signal/signal.c		$(MAKEDEP)
vfs/mount.o:		vfs/mount.c			$(MAKEDEP)
stubs/stubs.o:		stubs/stubs.c		$(MAKEDEP)



# explicit rules
libc.a:	$(OBJS) $(MAKEDEP)
	ar rcs libc.a $(OBJS)
	-cp $(OBJS) obj/
	
	
