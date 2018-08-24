:Setup
@echo off  

rem
rem Nelson Cole 2 font.
rem Baseada na fonte Nelson Cole.
rem

    cd c:\sdk\bin

	
:Compiling
echo -{ API
echo -{ ...
echo -{ Compiling nc2.c
    gcc -c c:\gramado\lib\fonts\nc2\nc2.c -o nc2.o  
    rem Nothing.
	
:Linking
    ld -T c:\gramado\lib\fonts\nc2\link.ld -o NC2.FON nc2.o -Map  test_map.s	
	
:Moving
echo -{ ...
echo -{ Moving ...	
    rem move *.o obj/
	copy NC2.FON c:\gramado\bin\NC2.FON 
	
	
:End
echo -{ ...
echo Done!
    pause