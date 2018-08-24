:Setup
@echo off  

rem
rem Nelson Cole 2 font.
rem Baseada na fonte Nelson Cole.
rem

:Compiling
echo -{ API
echo -{ ...
echo -{ Compiling nc2.c
    gcc -c nc2.c -o nc2.o  
    rem Nothing.
	
:Linking
    ld -T link.ld -o NC2.FON nc2.o -Map  test_map.s	
	
:Moving
echo -{ ...
echo -{ Moving ...	
    rem move *.o obj/
	
:End
echo -{ ...
echo Done!
    pause