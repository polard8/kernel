:SetUp
@echo off  


    cd c:\sdk\bin

:Monting
echo -{ ...
echo -{ Creating application TGFE.BIN ...
echo -{ ( test gramado file explorer )

    nasm c:\gramado\tests\tgfe\crt0.asm -f elf -o crt0.o
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc -c c:\gramado\tests\tgfe\main.c    -I c:\gramado\include\libc -o main.o  
	gcc -c c:\gramado\tests\tgfe\status.c  -I c:\gramado\include\libc -o status.o 
	gcc -c c:\gramado\tests\tgfe\addrbar.c  -I c:\gramado\include\libc -o addrbar.o 
 
    
	copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
	copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
    copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
	
	copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o
 
:Objects	
set myObjects=crt0.o ^
main.o ^
ctype.o ^
stdlib.o ^
stdio.o ^
string.o ^
api.o ^
status.o ^
addrbar.o   




:Linking  
echo -{ ...
echo -{ Linking objects ... 
   ld -T c:\gramado\tests\tgfe\link.ld -o TGFE.BIN %myObjects% -Map  test_map.s
   
   rem Não deletar os objetos.
 
:Moving   
    move TGFE.BIN c:\gramado\bin\TGFE.BIN 
   
:End   
echo End!
	pause