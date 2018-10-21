:SetUp
@echo off  

:Monting
echo -{ ...
echo -{ Creating application OPER1.BIN ...

    cd c:\sdk\bin
	
:Compiling	
echo -{ ...
echo -{ Compiling ...
	gcc  -c  c:\gramado\tests\operators\main.c -I c:\gramado\include\libc  -o main.o  
	
    copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
    copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
    copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
    copy c:\gramado\lib\time.o	  c:\sdk\bin\time.o
 
:Objects	
set myObjects=main.o ^
stdio.o ^
ctype.o ^
string.o 

 


:Linking  
echo -{ ...
echo -{ Linking objects ... 

   ld -T  c:\gramado\tests\operators\link.ld -o OPER1.BIN %myObjects%  -Map c:\gramado\tests\operators\map.s
   
   rem Não deletar os objetos.
 
:Moving
   
   move OPER1.BIN c:\gramado\bin\OPER1.BIN
   
:End   
echo End!
	pause