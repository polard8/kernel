:Setup
echo off

    cd c:\sdk\bin 

rem
rem Compila a biblioteca c para user mode.
rem ambiente: Gramado Operating system.
rem

:Compiling
    
	echo { Compiling C library for 32bit User Mode ...
	
	gcc -c c:\norax\lib\libc-src\stdio.c  -I c:\norax\include\libc -o stdio.o
	gcc -c c:\norax\lib\libc-src\stdlib.c -I c:\norax\include\libc -o stdlib.o
	gcc -c c:\norax\lib\libc-src\string.c -I c:\norax\include\libc -o string.o
	gcc -c c:\norax\lib\libc-src\ctype.c  -I c:\norax\include\libc -o ctype.o
	gcc -c c:\norax\lib\libc-src\time.c   -I c:\norax\include\libc -o time.o
	rem ...
	
	echo { Compiling extra files ...
	gcc -c c:\norax\lib\libc-src\conio.c -I c:\norax\include\libc -o conio.o
	
:Moving
    echo { Moving objects ...
	
    move stdio.o  c:\norax\lib\stdio.o
    move stdlib.o c:\norax\lib\stdlib.o
    move string.o c:\norax\lib\string.o
	move ctype.o  c:\norax\lib\ctype.o
    move time.o   c:\norax\lib\time.o

    rem extras ...	
	move conio.o  c:\norax\lib\conio.o
    rem ...
	
:End
    pause
