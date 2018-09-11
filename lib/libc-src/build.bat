:Setup
echo off

    cd c:\sdk\bin 

rem
rem Compila a biblioteca c para user mode.
rem ambiente: Gramado Operating system.
rem

:Compiling
    
	echo { Compiling C library for 32bit User Mode ...
	
	gcc -c c:\gramado\lib\libc-src\stdio.c  -I c:\gramado\include\libc -o stdio.o
	gcc -c c:\gramado\lib\libc-src\stdlib.c -I c:\gramado\include\libc -o stdlib.o
	gcc -c c:\gramado\lib\libc-src\string.c -I c:\gramado\include\libc -o string.o
	gcc -c c:\gramado\lib\libc-src\ctype.c  -I c:\gramado\include\libc -o ctype.o
	gcc -c c:\gramado\lib\libc-src\time.c   -I c:\gramado\include\libc -o time.o
	rem ...
	
	echo { Compiling extra files ...
	gcc -c c:\gramado\lib\libc-src\conio.c -I c:\gramado\include\libc -o conio.o
	
:Moving
    echo { Moving objects ...
	
    move stdio.o  c:\gramado\lib\stdio.o
    move stdlib.o c:\gramado\lib\stdlib.o
    move string.o c:\gramado\lib\string.o
	move ctype.o  c:\gramado\lib\ctype.o
    move time.o   c:\gramado\lib\time.o

    rem extras ...	
	move conio.o  c:\gramado\lib\conio.o
    rem ...
	
:End
    pause
