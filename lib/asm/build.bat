:Setup
echo off

    cd c:\sdk\bin 


:Compiling
    
	echo { Compiling asm lib in 32bit
	
	nasm c:\gramado\lib\asm\asm.inc -f elf -o asm.o
	
:Moving
    echo { Moving objects ...
	
    move asm.o  c:\gramado\lib\asm.o

	
:End
    pause
