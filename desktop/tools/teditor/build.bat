:SetUp
@echo off  

    cd c:\sdk\bin

:Monting
echo -{ ...
echo -{ Creating application TEDITOR.BIN ...

    nasm c:\gramado\desktop\tools\teditor\crt0.asm -f elf -o crt0.o
	
:Compiling	
echo -{ ...
echo -{ Compiling ...

	gcc -c c:\gramado\desktop\tools\teditor\main.c   -I c:\gramado\include\libc -o main.o  
	gcc -c c:\gramado\desktop\tools\teditor\status.c -I c:\gramado\include\libc -o status.o 
	gcc -c c:\gramado\desktop\tools\teditor\topbar.c -I c:\gramado\include\libc -o topbar.o 
 

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
status.o ^
topbar.o   




:Linking  
echo -{ ...
echo -{ Linking objects ... 
   
   ld -T c:\gramado\desktop\tools\teditor\link.ld -o TEDITOR.BIN %myObjects% 
   
   rem Não deletar os objetos.
 
:Moving   
    move TEDITOR.BIN c:\gramado\bin\TEDITOR.BIN
   
:End   
echo End!
	pause