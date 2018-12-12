:SetUp
@echo off  

    cd c:\sdk\bin

:Monting
echo -{ ...
echo -{ Creating application GRAMCODE.BIN ...

    nasm c:\gramado\gramcode\crt0.asm -f elf -o crt0.o
	
:Compiling	
echo -{ ...
echo -{ Compiling gramcode ...

	gcc -c c:\gramado\gramcode\main.c   -I c:\gramado\include\libc -o main.o  
	gcc -c c:\gramado\gramcode\status.c -I c:\gramado\include\libc -o status.o 

    copy c:\gramado\lib\ctype.o     c:\sdk\bin\ctype.o 
    copy c:\gramado\lib\stdlib.o    c:\sdk\bin\stdlib.o
    copy c:\gramado\lib\stdio.o     c:\sdk\bin\stdio.o
    copy c:\gramado\lib\string.o    c:\sdk\bin\string.o


    copy c:\gramado\lib\api\api.o c:\sdk\bin\api.o	
	
 
:Objects	
set myObjects=crt0.o ^
main.o ^
ctype.o ^
stdlib.o ^
stdio.o ^
string.o ^
api.o ^
status.o   






:Linking  
echo -{ ...
echo -{ Linking objects ... 
   
   ld -T c:\gramado\gramcode\link.ld -o GRAMCODE.BIN %myObjects% 
   
   rem Não deletar os objetos.
 
:Moving   
    move GRAMCODE.BIN c:\gramado\bin\GRAMCODE.BIN
   
:End   
echo End!
	pause