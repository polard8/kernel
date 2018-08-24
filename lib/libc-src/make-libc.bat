:Setup
echo off

rem
rem Compila a biblioteca c para user mode.
rem ambiente: Gramado Operating system.
rem

:Compiling
    
	echo { Compiling C library for 32bit User Mode ...
	gcc -c stdio.c  -o stdio.o
	gcc -c stdlib.c -o stdlib.o
	gcc -c string.c -o string.o
	gcc -c ctype.c -o ctype.o
	gcc -c time.c -o time.o
	rem ...
	
	echo { Compiling extra files ...
	gcc -c conio.c -o conio.o
	
:Moving
    echo { Moving objects ...
    move stdio.o  obj/stdio.o
    move stdlib.o obj/stdlib.o
    move string.o obj/string.o
	move ctype.o  obj/ctype.o
	
	
    move time.o  obj/time.o

    rem extras ...	
	move conio.o  obj/conio.o
    rem ...
	
:End
    pause
